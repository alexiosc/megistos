/*****************************************************************************\
 **                                                                         **
 **  FILE:     telecon.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences                                              **
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
 **                                                                         **
 **  This program is free software; you  can redistribute it and/or modify  **
 **  it under the terms of the GNU  General Public License as published by  **
 **  the Free Software Foundation; either version 2 of the License, or (at  **
 **  your option) any later version.                                        **
 **                                                                         **
 **  This program is distributed  in the hope  that it will be useful, but  **
 **  WITHOUT    ANY WARRANTY;   without  even  the    implied warranty  of  **
 **  MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.   See the GNU  **
 **  General Public License for more details.                               **
 **                                                                         **
 **  You  should have received a copy   of the GNU  General Public License  **
 **  along with    this program;  if   not, write  to  the   Free Software  **
 **  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/02/29 17:59:45  alexios
 * Minor permission/file location issues fixed to account for the new infrastructure.
 *
 * Revision 1.5  2003/12/27 12:29:38  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/28 23:13:16  alexios
 * Made the aux structure non-volatile by saving it before
 * exiting teleconferences and reloading when re-entering.
 *
 * Revision 0.5  1998/12/27 16:10:27  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Added code to better parse inp_buffer commands.
 *
 * Revision 0.4  1998/08/14 11:45:25  alexios
 * Fixed slight log-out bug.
 *
 * Revision 0.3  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "telecon.h"
#include "mbk_telecon.h"


void
run ()
{
	int     i;
	char   *cp;

	memset (&thisuseraux, 0, sizeof (struct usraux));

	msg_set (msg);
	if (!key_owns (&thisuseracc, entrkey)) {
		prompt (DENIED);
		return;
	}

	if (thisuseraux.magic != TELEAUX_MAGIC) {
		char    fname[256];
		FILE   *fp;

		sprintf (fname, "/tmp/teleaux-%s", thisuseracc.userid);

		if ((fp = fopen (fname, "r")) != NULL) {
			if (fread (&thisuseraux, sizeof (struct usraux), 1, fp)
			    != 1) {
				error_logsys
				    ("Unable to read from temporary aux file %s",
				     fname);
			}
			fclose (fp);
		}
	}

	if (thisuseraux.magic != TELEAUX_MAGIC) {
		bzero (&thisuseraux, sizeof (struct usraux));
		thisuseraux.magic = TELEAUX_MAGIC;
		thisuseraux.chatparty[0] = 0;
		thisuseraux.lastinvitation = 0;
		thisuseraux.plugin[0] = 0;
		thisuseraux.pluginq = -1;
	}

	msg_set (msg);
	prompt (INTRO);

	if (!thisuseronl.telecountdown) {
		thisuseronl.telecountdown = -1;
		if (!LIVE) {
			if (!npaymx) {
				prompt (NOTALK);
				thisuseronl.telecountdown = -2;
			} else if (npaymx > 0) {
				prompt (NLVTALK, npaymx,
					msg_getunit (TIMSNG, npaymx));
				thisuseronl.telecountdown = npaymx;
			}
		}
	} else if (LIVE)
		thisuseronl.telecountdown = -1;

	thisuseronl.flags &= ~OLF_BUSY;
	if (thisuseronl.flags & OLF_MMCONCAT)
		thisuseronl.flags &= ~OLF_MMCONCAT;
	thisuseronl.flags |= OLF_INTELECON;

	if ((i = loadtlcuser (thisuseracc.userid, &tlcu)) == 0)
		makenewuser ();

	thisuseraux.interval = tlcu.chatinterval * 60;
	thisuseraux.colour = tlcu.colour;
	thisuseraux.actions = tlcu.actions;

	if (thisuseronl.telechan[0]) {
		int     ax;

		ax = getusrax (thisuseronl.telechan, thisuseracc.userid);
		if ((ax & CUF_ACCESS) == 0) {
			prompt (ENTRBCH, thisuseronl.telechan);
			strcpy (thisuseronl.telechan, MAINCHAN);
		}
	} else if (i) {
		strcpy (thisuseronl.telechan,
			tlcu.flags & TLF_STARTMAIN ? MAINCHAN : thisuseracc.
			userid);
	} else
		strcpy (thisuseronl.telechan, MAINCHAN);

	enterchannel (thisuseronl.telechan);

	thisuseraux.numentries++;

	msg_set (msg);
	userent (ENTTLC);

	showinfo ();

	for (;;) {
		if (thisuseronl.telecountdown == -1) {
			prompt ((thisuseraux.
				 access & CUF_READONLY) ? PROMPT2 : PROMPT1,
				getcolour ());
		} else if (thisuseronl.telecountdown > 0) {
			prompt (PROMPT3, thisuseronl.telecountdown,
				getcolour ());
		} else if (thisuseronl.telecountdown == -2)
			prompt (PROMPT2, getcolour ());

		cnc_end ();

		if ((time (0) - thisuseraux.entrytick) >= TELETICK) {
			thisuseronl.flags &= ~OLF_INHIBITGO;
			thisuseraux.numentries = 0;
			thisuseraux.entrytick = time (0);
		}
		if (thisuseraux.numentries > maxcht)
			thisuseronl.flags |= OLF_INHIBITGO;

		inp_get (tinpsz);

		if (inp_reprompt ()) {
			int     action = thisuseraux.action;

			thisuseraux.action = 0;
			switch (action) {
			case ACT_DROPMAIN:
				droptomain ();
				break;
			case ACT_STARTCHAT:
				startchat ();
				break;
			}
		}

		inp_raw ();

		for (cp = inp_buffer; isspace (*cp); cp++);

		if (inp_isX (cp)) {
			if (!checktick ())
				continue;
			prompt (LEAVE);
			break;
		} else if (inp_reprompt ()) {
			continue;
		} else if (!cp[0]) {
			showinfo ();
		} else if (!strcmp (cp, "?")) {
			prompt (TLCHELP);
			cnc_end ();
		} else if (sameas (cp, "EDIT")) {
			editprefs ();
		} else if (sameas (cp, "SCAN") || sameas (cp, "/S")) {
			chanscan ();
		} else if (sameto ("JOIN ", cp) || sameas ("JOIN", cp) ||
			   sameto ("/J ", cp) || sameas ("/J", cp)) {
			joinchan (cp);
		} else if (sameas ("UNLIST", cp)) {
			flagunlist (1);
		} else if (sameas ("LIST", cp)) {
			flagunlist (0);
		} else if (sameto ("INVITE ", cp) || sameas ("INVITE", cp) ||
			   sameto ("/I ", cp) || sameas ("/I", cp)) {
			invite (cp);
		} else if (sameto ("UNINVITE ", cp) || sameas ("UNINVITE", cp)
			   || sameto ("/U ", cp) || sameas ("/U", cp)) {
			uninvite (cp);
		} else if (sameto ("READONLY ", cp) || sameas ("READONLY", cp)
			   || sameto ("/RO ", cp) || sameas ("/RO", cp)) {
			invitero (cp);
		} else if (sameto ("SQUELCH ", cp) || sameas ("SQUELCH", cp)) {
			squelch (cp);
		} else if (sameto ("UNSQUELCH ", cp) ||
			   sameas ("UNSQUELCH", cp)) {
			unsquelch (cp);
		} else if (sameto ("TOPIC ", cp) || sameas ("TOPIC", cp)) {
			topic (cp);
		} else if (sameto ("CHAT ", cp) || sameas ("CHAT", cp)) {
			chat (cp);
		} else if (sameto ("ACTION ", cp) || sameas ("ACTION", cp) ||
			   sameto ("/A ", cp) || sameas ("/A", cp)) {
			actionctl (cp);
		} else if (sameas ("PLUGINS", cp)) {
			listplugins ();
		} else if (handleplugins (cp)) {
			continue;
		} else if (thisuseronl.telecountdown == -2) {	/* CAN'T TALK ANY MORE */
			prompt (NLVNAX);
		} else if (thisuseronl.flags & OLF_INVISIBLE) {	/* CAN'T TALK IF INVIS */
			prompt (INVIS);
			cnc_end ();
		} else if (handleaction (cp)) {
			continue;
		} else if ((cp[0] == '/') || sameto ("WHISPER TO ", cp)) {
			whisper (cp);
			countdown ();
		} else if ((cp[0] == '\\') || cp[0] == '>' ||
			   sameto ("SAY TO ", cp)) {
			sayto (cp);
			countdown ();
		} else {
			say (cp);
			countdown ();
		}
	}
}


static int dont_write_aux = 0;

void
done ()
{
	static int circular = 0;

	thisuseronl.flags &= ~OLF_INHIBITGO;

	if (thisuseraux.magic == TELEAUX_MAGIC) {
		char    fname[256];
		FILE   *fp = NULL;

		sprintf (fname, "/tmp/teleaux-%s", thisuseracc.userid);
		if (dont_write_aux) {
			unlink (fname);
		} else if ((fp = fopen (fname, "w")) == NULL) {
			error_logsys ("Unable to save temporary aux file %s",
				      fname);
		} else {
			if (fwrite
			    (&thisuseraux, sizeof (struct usraux), 1,
			     fp) != 1) {
				error_logsys
				    ("Unable to write to temporary aux file %s",
				     fname);
			}
		}
		fclose (fp);
	}

	if (!circular) {
		circular++;
		if (!thisuseraux.chatting) {
			if (thisuseronl.telechan[0])
				userexit (LFTTLC);
		} else {
			struct msqid_ds buf;

			msgctl (thisuseraux.chatid, IPC_RMID, &buf);
		}
		if (thisuseronl.telechan[0])
			leavechannel ();
		thisuseronl.flags &= ~OLF_INTELECON;
	}
	msg_close (msg);
}


void
logout ()
{
	char    command[256];

	killpersonalchannel ();
	leavechannels ();
	sprintf (command, "\\rm -rf %s/%s >&/dev/null",
		 mkfname (TELEDIR), thisuseracc.userid);
	system (command);
	dont_write_aux = 1;
}


int
handler_run (int argc, char *argv[])
{
	atexit (done);
	initactions ();
	initplugins ();
	init ();
	initvars ();
	run ();
	return 0;
}


int
handler_logout (int argc, char *argv[])
{
	atexit (done);
	initactions ();
	initplugins ();
	init ();
	initvars ();
	logout ();
	return 0;
}


int
handler_userdel (int argc, char **argv)
{
	char   *victim = argv[2], fname[1024];

	if (strcmp (argv[1], "--userdel") || argc != 3) {
		fprintf (stderr, "User deletion handler: syntax error\n");
		return 1;
	}

	if (!usr_exists (victim)) {
		fprintf (stderr,
			 "User deletion handler: user %s does not exist\n",
			 victim);
		return 1;
	}

	sprintf (fname, "%s/%s", mkfname (TELEUSRDIR), victim);
	unlink (fname);

	return 0;
}


mod_info_t mod_info_telecon = {
	"telecon",
	"Teleconferences",
	"Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
	"Chat rooms, multiplayer games, and other multiuser interactive features.",
	RCS_VER,
	"1.0",
	{0, NULL}
	,			/* Login handler */
	{0, handler_run}
	,			/* Interactive handler */
	{10, handler_logout}
	,			/* Logout handler */
	{0, NULL}
	,			/* Hangup handler */
	{0, NULL}
	,			/* Cleanup handler */
	{50, handler_userdel}	/* Delete user handler */
};


int
main (int argc, char *argv[])
{
	mod_setinfo (&mod_info_telecon);
	return mod_main (argc, argv);
}


/* End of File */
