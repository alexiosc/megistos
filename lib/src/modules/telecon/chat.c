/*****************************************************************************\
 **                                                                         **
 **  FILE:     chat.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 0.5                                    **
 **  PURPOSE:  One-on-one chats                                             **
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
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/18 21:48:36  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.6  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/14 11:45:25  alexios
 * Reset inactivity inside chats, so users aren't inadvertently
 * kicked out when they're not even idle. Made both flavours of
 * backspace work (ASCII 8 and 127).
 *
 * Revision 0.4  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/03 00:43:24  alexios
 * Changed all instances of xlwrite() to write(), since emud
 * now handles all translations.
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


struct chatmsgbuf {
	long    mtype;
	char    s[128];
};


void
chat (char *s)
{
	char    userid[2048] = { 0 };
	int     i;

	i = sscanf (s, "%*s %s", userid);

	if ((i < 1) || sameas (userid, "?")) {
		prompt (CHTHELP);
		return;
	}

	if (!key_owns (&thisuseracc, chtkey)) {
		prompt (CHTNAX);
		return;
	}

	if (!tlcuidxref (userid, 0)) {
		prompt (CHTUID, userid);
		return;
	}

	if (!usr_insys (userid, 0) || !(othruseronl.flags & OLF_INTELECON)) {
		prompt (CHTUID, userid);
		return;
	}

	if (!strcmp (userid, thisuseracc.userid)) {
		prompt (CHTSLF);
		return;
	}

	if (!key_owns (&othruseracc, chtkey)) {
		prompt (CHTONX, userid);
		return;
	}

	if (othruseraux.chatting) {
		prompt (CHTALR,
			msg_getunit (CHTM, othruseracc.sex == USX_MALE),
			userid);
		return;
	}

	if (sameas (othruseraux.chatparty, thisuseracc.userid)) {
		if (othruseronl.flags & OLF_BUSY) {
			prompt (CHTUNOT, othruseronl.userid);
			return;
		}
		strcpy (thisuseraux.chatparty, othruseracc.userid);
		originatechat (othruseracc.userid);
		startchat ();
		return;
	} else if (!key_owns (&thisuseracc, ichtkey)) {
		prompt (CHTNIN);
		return;
	} else {
		int     t = time (NULL);
		int     dt = t - othruseraux.lastinvitation;

		if (dt < othruseraux.interval) {
			int     i = (othruseraux.interval - dt) / 60 + 1;
			char   *sex, *mins;

			sex =
			    strdup (msg_getunit
				    (CHTM, othruseracc.sex == USX_MALE));
			mins = strdup (msg_getunit (CHTMINS, i));
			prompt (CHTFRQ, sex, userid, i, mins);
			free (sex);
			free (mins);
			return;
		}

		strcpy (thisuseraux.chatparty, userid);
		othruseraux.lastinvitation = t;

		{
			char   *his;
			int     lang = othruseracc.language - 1;

			his =
			    strdup (msg_getunit
				    (CHTHIS, thisuseracc.sex == USX_MALE));
			sprompt_other (othrshm, out_buffer, CHTREQ,
				       msg_getunitl (CHTM,
						     thisuseracc.sex ==
						     USX_MALE, lang),
				       thisuseracc.userid, his,
				       thisuseracc.userid);
			if (!usr_injoth (&othruseronl, out_buffer, 0)) {
				prompt (CHTUNOT, othruseronl.userid);
				free (his);
				return;
			}
			free (his);
		}

		prompt (CHTROK,
			msg_getunit (CHTM, othruseracc.sex == USX_MALE),
			userid);
	}
}


static int samechan;
char    othuid[24], othsex;


static char *
fx_chatnotify (struct chanusr *u)
{
	int     lang = othruseracc.language - 1;

	if (!strcmp (u->userid, othuid))
		return NULL;
	if (samechan) {
		char   *sex =
		    strdup (msg_getunitl
			    (CHTM, thisuseracc.sex == USX_MALE, lang));
		char   *sex2 =
		    strdup (msg_getunitl (CHTWITHM, othsex == USX_MALE, lang));
		sprintf (out_buffer, msg_getl (CHTNOT2, lang), sex,
			 thisuseracc.userid, sex2, othuid);
		free (sex);
		free (sex2);
	} else {
		char   *sex =
		    strdup (msg_getunitl (CHTM, othsex == USX_MALE, lang));
		sprintf (out_buffer, msg_getl (CHTNOT1, lang), sex, othuid);
		free (sex);
	}
	return out_buffer;
}


static void
notify ()
{
	int     lang = othruseracc.language - 1;

	prompt (CHTENT);

	sprompt_other (othrshm, out_buffer, CHTACC,
		       msg_getunitl (CHTM, thisuseracc.sex == USX_MALE, lang),
		       thisuseracc.userid);
	usr_injoth (&othruseronl, out_buffer, 0);

	if (!strcmp (thisuseronl.telechan, othruseronl.telechan)) {
		strcpy (othuid, othruseracc.userid);
		othsex = othruseracc.sex;
		samechan = 1;
		broadcast (fx_chatnotify);
	} else {
		char   *othchan = strdup (othruseronl.telechan);

		samechan = 0;

		strcpy (othuid, othruseracc.userid);
		othsex = othruseracc.sex;
		broadcastchn (othchan, fx_chatnotify);

		strcpy (othuid, thisuseracc.userid);
		othsex = thisuseracc.sex;
		broadcast (fx_chatnotify);
		free (othchan);
	}
}


static void
arrangecolours ()
{
	struct tlcuser tlcu;
	int     c1, c2;

	if (!loadtlcuser (thisuseracc.userid, &tlcu)) {
		error_fatal ("Unable to load tlcuser %s", thisuseracc.userid);
	}
	c1 = tlcu.colour;

	if (!loadtlcuser (othruseracc.userid, &tlcu)) {
		error_fatal ("Unable to load tlcuser %s", othruseracc.userid);
	}
	c2 = tlcu.colour;

	if (c1 != c2) {
		thisuseraux.colour = c1;
		othruseraux.colour = c2;
	} else {
		thisuseraux.colour = chatcol1;
		othruseraux.colour = chatcol2;
	}
}


void
originatechat (char *userid)
{
	char    tmp[24];
	int     id;

	strcpy (tmp, userid);
	notify ();
	usr_insys (tmp, 0);

	id = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0777);
	if (id < 0) {
		error_fatal ("Unable to allocate IPC message queue for chat.");
	} else
		thisuseraux.chatid = othruseraux.chatid = id;

	arrangecolours ();

	thisuseraux.chatting = 1;
	othruseraux.chatting = 2;

	sendaction (othruseracc.userid, ACT_STARTCHAT);
}


void
startchat ()
{
	int     state = 1, count = 0, setcolour = -1, n;
	struct chatmsgbuf msg;
	char    s[32];

	setusrax (curchannel, thisuseracc.userid, 0, CUF_CHATTING,
		  CUF_PRESENT);

	usr_insys (thisuseraux.chatparty, 0);

	if (thisuseraux.chatting == 2)
		prompt (CHTENT);

	inp_nonblock ();

	for (; othruseraux.chatting && state != 3;) {
		usleep (25000);
		count = (count + 1) % 4;
		if (!count && state == 1)
			if (inp_acceptinjoth ())
				setcolour = -1;

		if ((n = read (fileno (stdin), s, sizeof (s) - 1)) > 0) {

			inp_resetidle ();

			if (setcolour != 0) {
				setcolour = 0;
				sprintf (msg.s, "\033[%sm",
					 colours[thisuseraux.colour]);
				write (fileno (stdout), msg.s, strlen (msg.s));
			}

			{
				int     i, j;

				for (i = 0, j = 0; i < n; i++, j++) {
					if (!state &&
					    ((s[i] == 13) || s[i] == 10)) {
						s[i] = '\n';
						state = 1;
#ifdef GREEK
					} else if (state == 1 &&
						   (s[i] == -82 || s[i] == -107
						    || toupper (s[i]) ==
						    'X')) {
#else
					} else if (state == 1 &&
						   (toupper (s[i]) == 'X')) {
#endif
						state = 2;
					} else if (state == 2 &&
						   ((s[i] == 13) ||
						    s[i] == 10)) {
						state = 3;
					} else
						state = 0;

					switch (s[i]) {
					case 8:
					case 127:
						msg.s[j++] = 8;
						msg.s[j++] = 32;
						msg.s[j] = 8;
						break;
					default:
						msg.s[j] = s[i];
					}
				}
				msg.s[j] = 0;
			}

			msg.mtype = othruseraux.chatting;
			if (msgsnd
			    (thisuseraux.chatid, (struct msg_buffer *) &msg,
			     n = (strlen (msg.s) + 1), 0))
				break;
			write (fileno (stdout), msg.s, n);
		}
		if ((n =
		     msgrcv (thisuseraux.chatid, (struct msg_buffer *) &msg,
			     sizeof (msg.s) - 1, thisuseraux.chatting,
			     IPC_NOWAIT)) > 0) {
			if (setcolour != 1) {
				setcolour = 1;
				sprintf (s, "\033[%sm",
					 colours[othruseraux.colour]);
				write (fileno (stdout), s, strlen (s));
			}
			{
				char    c = msg.s[strlen (msg.s) - 1];

				if ((c == '\n' || c == '\r') && (state == 0))
					state = 1;
				else
					state = 0;
			}
			write (fileno (stdout), msg.s, n);
			fflush (stdout);
		}
	}

	inp_block ();

	finishchat ();
}


void
finishchat ()
{
	prompt (CHTEXT);

	setusrax (curchannel, thisuseracc.userid, 0, CUF_PRESENT,
		  CUF_CHATTING);

	if (thisuseraux.chatting == 1) {
		struct msqid_ds buf;
		int     i = msgctl (thisuseraux.chatid, IPC_RMID, &buf);

		if (i) {
			error_fatalsys
			    ("Unable to destroy IPC message queue.");
		}
	}
	thisuseraux.chatting = 0;
	thisuseraux.chatparty[0] = 0;
	if (loadtlcuser (thisuseracc.userid, &tlcu))
		thisuseraux.colour = tlcu.colour;

	enterchannel (curchannel);
	userent (ENTCHT);
	showinfo ();
}


/* End of File */
