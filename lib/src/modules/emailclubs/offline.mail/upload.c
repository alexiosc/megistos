/*****************************************************************************\
 **                                                                         **
 **  FILE:     upload.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Handle incoming reply packets                                **
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
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/18 21:44:48  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.6  1998/12/27 15:48:12  alexios
 * Added autoconf support. Fixed bug that wouldn't auto-translate
 * the subject of messages.
 *
 * Revision 0.5  1998/08/11 10:17:19  alexios
 * Translate incoming messages. Fixed slight reply bug.
 *
 * Revision 0.4  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:16:47  alexios
 * Added code to check the CRC-32 and lengths of uploaded
 * messages. If a message has already been uploaded, the user
 * is asked whether they want it sent anyway or not. This should
 * avoid duplicate message uploads to the system, while still
 * allowing the persistent user to do it.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/offline.mail.h>
#include <megistos/../../mailer.h>
#include <megistos/mbk_offline.mail.h>


#define __MAILER_UNAMBIGUOUS__
#include <megistos/mbk_mailer.h>

#define __EMAILCLUBS_UNAMBIGUOUS__
#include <megistos/mbk_emailclubs.h>


static char qwkbuf[128];
static struct qwkhdr qwkhdr;
static char tmp[256];
static struct message msg;
static int blocks;
static int conf;
static int charge;
static int isctlmsg;
FILE   *rep;


static void
readbuf ()
{
	if (!fread (qwkbuf, 128, 1, rep)) {
		if (!feof (rep))
			error_fatalsys ("Unable to read from reply packet.");
	}
}


static int
msgsel (const struct dirent *d)
{
	return strlen (d->d_name) > 4 &&
	    sameas (&(((char *) d->d_name)[strlen (d->d_name) - 4]), ".MSG");
}


static int
checkbbsid ()
{
	/* Check the BBSID of the reply packet, abort if not the same as ours */

	char   *cp;

	readbuf ();
	if ((cp = strchr (qwkbuf, 32)) != NULL) {
		*cp = 0;
		if (!sameas (qwkbuf, bbsid)) {
			prompt (BADID, qwkbuf, bbsid);
			return -1;
		}
	} else
		error_fatal ("Malformed reply packet.");

	return 0;
}


static char *
zonk (char *s, int len)
{
	int     i;

	for (i = len - 1; i && ((s[i] == ' ') || (s[i] == 0)); i--)
		s[i] = 0;
	return s;
}


static void
initqwkhdr ()
{
	strcpy (msg.from, thisuseracc.userid);

	/* Copy and (if necessary) translate the subject */
	memcpy (msg.subject, qwkhdr.subject,
		sizeof (qwkhdr.subject) +
		(usepass ? sizeof (qwkhdr.password) : 0));
	zonk (msg.subject, sizeof (msg.subject));
	xlate_in (msg.subject);

	if (sameto ("RRR", msg.subject)) {
		strcpy (tmp, &msg.subject[3]);
		bzero (msg.subject, sizeof (msg.subject));
		strcpy (msg.subject, tmp);
		msg.flags |= MSF_RECEIPT;
	}
	blocks = atoi (qwkhdr.blocks);
}


static int
setupclub ()
{
	if (!sscanf (qwkhdr.number, "%d", &conf)) {
		prompt (REPTB, "?", "?");
		prompt (REPTBMF);
		return 0;
	}

	if (conf && !getclubid (conf)) {
		prompt (REPTB, "?", "?");
		prompt (REPTBUS);
		if (!getclub (tmp, ASKCLUB, ASKCLBR, 0, 1)) {
			prompt (REPHD);
			prompt (REPTB, "?", "?");
			prompt (REPTBCN);
			return 0;
		}
		if (sameas (tmp, omceml)) {
			msg.club[0] = 0;
			conf = 0;
		} else {
			strcpy (msg.club, tmp);
			loadclubhdr (tmp);
		}
	} else if (conf)
		strcpy (msg.club, clubhdr.club);
	setclub (msg.club);
	return 1;
}


static int
setuprecipient ()
{
	isctlmsg = 0;
	if (!sscanf (qwkhdr.whoto, "%s", tmp)) {
		prompt (REPTB, "", conf ? clubhdr.club : omceml);
		prompt (REPTBNR);
		if (!get_userid
		    (tmp, conf ? ASKSRCP : ASKERCP, UNKUSR, 0, 0, 0)) {
			prompt (REPHD);
			prompt (REPTB, "", conf ? clubhdr.club : omceml);
			prompt (REPTBCN);
			return 0;
		}
		strcpy (msg.to, tmp);
	} else if (sameas (tmp, ctlname[0]) || sameas (tmp, ctlname[1]) ||
		   sameas (tmp, ctlname[2]) || sameas (tmp, ctlname[3]) ||
		   sameas (tmp, ctlname[4]) || sameas (tmp, ctlname[5])) {
		isctlmsg = 1;
		strcpy (msg.to, ctlname[0]);
	} else if (sameas (tmp, allnam)) {
		strcpy (msg.to, MSG_ALL);
	} else {
		if (!usr_exists (tmp)) {
			prompt (REPTB, tmp, conf ? clubhdr.club : omceml);
			prompt (REPTBUU);
			if (!get_userid
			    (tmp, conf ? ASKSRCP : ASKERCP, UNKUSR, 0, 0, 0)) {
				prompt (REPHD);
				prompt (REPTB, tmp,
					conf ? clubhdr.club : omceml);
				prompt (REPTBCN);
				return 0;
			} else
				prompt (REPHD);
		}
		strcpy (msg.to, tmp);
	}
	return 1;
}


static int
checkperms ()
{
	if (conf && getclubax (&thisuseracc, clubhdr.club) < CAX_WRITE) {
		prompt (REPTBNA);
		return 0;
	}
	return 1;
}


static int
checkcreds ()
{
	charge = conf ? clubhdr.postchg : wrtchg;
	if (!usr_canpay (charge)) {
		prompt (REPTBCR);
		return 0;
	}
	return 1;
}


static int
checkprivclub ()
{
	if (conf && (qwkhdr.status == STATUS_P || qwkhdr.status == STATUS_PR)) {
		prompt (REPTBES);
		for (;;) {
			char    c;
			int     res =
			    get_menu (&c, 1, 0, ASKEORS, ASKERR, "EPC", 0, 0);
			if (!res) {
				prompt (ASKERR);
				continue;
			} else
				switch (c) {
				case 'E':
					conf = 0;
					bzero (msg.club, sizeof (msg.club));
					prompt (REPHD);
					prompt (REPTB,
						sameas (msg.to,
							MSG_ALL) ?
						msg_getunit (REPTBALL,
							     1) : msg.to,
						conf ? clubhdr.club : omceml);
					return 1;
				case 'P':
					qwkhdr.status = STATUS_N;
					prompt (REPHD);
					prompt (REPTB,
						sameas (msg.to,
							MSG_ALL) ?
						msg_getunit (REPTBALL,
							     1) : msg.to,
						conf ? clubhdr.club : omceml);
					return 1;
				case 'C':
					prompt (REPHD);
					prompt (REPTB,
						sameas (msg.to,
							MSG_ALL) ?
						msg_getunit (REPTBALL,
							     1) : msg.to,
						conf ? clubhdr.club : omceml);
					prompt (REPTBCN);
					return 0;
				}
		}
	}
	return 1;		/* just to get rid of the warning */
}


static int
checkemailall ()
{
	if (!conf && !strcmp (msg.to, MSG_ALL)) {
		prompt (REPTBAE);
		prompt (EMLALL);
		if (!get_userid (tmp, ASKERCP, UNKUSR, 0, 0, 0)) {
			prompt (REPHD);
			prompt (REPTB,
				sameas (msg.to,
					MSG_ALL) ? msg_getunit (REPTBALL,
								1) : msg.to,
				conf ? clubhdr.club : omceml);
			prompt (REPTBCN);
			return 0;
		} else {
			prompt (REPHD);
			prompt (REPTB,
				sameas (msg.to,
					MSG_ALL) ? msg_getunit (REPTBALL,
								1) : msg.to,
				conf ? clubhdr.club : omceml);
		}
		strcpy (msg.to, tmp);
	}
	return 1;
}


static int
checkpublrrr ()
{
	if (conf && msg.flags & MSF_RECEIPT) {
		prompt (REPTBPR);
		for (;;) {
			char    c;
			int     res =
			    get_menu (&c, 1, 0, ASKRORS, ASKERR, "EPC", 0, 0);
			if (!res) {
				prompt (ASKERR);
				continue;
			} else
				switch (c) {
				case 'E':
					conf = 0;
					bzero (msg.club, sizeof (msg.club));
					prompt (REPHD);
					prompt (REPTB,
						sameas (msg.to,
							MSG_ALL) ?
						msg_getunit (REPTBALL,
							     1) : msg.to,
						conf ? clubhdr.club : omceml);
					return 1;
				case 'P':
					msg.flags &= ~MSF_RECEIPT;
					prompt (REPHD);
					prompt (REPTB,
						sameas (msg.to,
							MSG_ALL) ?
						msg_getunit (REPTBALL,
							     1) : msg.to,
						conf ? clubhdr.club : omceml);
					return 1;
				case 'C':
					prompt (REPHD);
					prompt (REPTB,
						sameas (msg.to,
							MSG_ALL) ?
						msg_getunit (REPTBALL,
							     1) : msg.to,
						conf ? clubhdr.club : omceml);
					prompt (REPTBCN);
					return 0;
				}
		}
	}
	return 1;
}


static int
setuphist ()
{
	struct message org;
	int     ref;

	/* Reply entry */

	zonk (qwkhdr.reference, sizeof (qwkhdr.reference));
	if (strlen (qwkhdr.reference)) {
		if (!sscanf (qwkhdr.reference, "%d", &ref)) {
			prompt (REPTB, "?", "?");
			prompt (REPTBMF);
			return 0;
		}

		/* It seems some readers specify "0" if a message isn't a reply */
		if (ref) {
			bzero (&org, sizeof (org));
			getmsgheader (ref, &org);

			/* Set the message up as a reply, as well */

			if (ref == org.msgno) {
				sprintf (msg.history, "%s %s/%d", HST_REPLY,
					 conf ? clubhdr.club : EMAILCLUBNAME,
					 org.msgno);
				msg.flags |= MSF_REPLY;
				msg.replyto = ref;
			}
		}
	}

	/* Off-line entry (always the last one) */

	addhistory (msg.history, HST_OFFLINE, sizeof (msg.history));
	return 1;
}


static int
askdupl ()
{
	int     yes = 0;

	prompt (REPTBAG);

	while (!get_bool (&yes, ASKDUPL, ASKERR, ASKDUPD, 0))
		prompt (ASKERR);

	prompt (REPHD);
	prompt (REPTB,
		sameas (msg.to, MSG_ALL) ? msg_getunit (REPTBALL, 1) : msg.to,
		conf ? clubhdr.club : omceml);
	if (!yes)
		prompt (REPTBCN);
	return yes;
}


static int
checkcrc (char *body)
{
	unsigned long crc;
	int     len;
	int     i, add = 0;

	cksumstg (body, &crc, &len);

	for (i = 0; i < NUMOLDMSGS; i++) {
		if (prefs.oldcrc[i] == crc && prefs.oldlen[i] == len) {
			if (!askdupl ())
				return 0;
			else
				add = 0;
		}
	}


	/* If necessary, store the new CRC for later */

	if (add) {
		memcpy (&(userqwk.oldcrc[1]), &(userqwk.oldcrc[0]),
			sizeof (userqwk.oldcrc[0] * (NUMOLDREP - 1)));
		userqwk.oldcrc[NUMOLDREP - 1] = crc;

		memcpy (&(userqwk.oldlen[1]), &(userqwk.oldlen[0]),
			sizeof (userqwk.oldlen[0] * (NUMOLDREP - 1)));
		userqwk.oldlen[NUMOLDREP - 1] = len;
	}
	return 1;
}


void
dobody (char *fname)
{
	int     size = blocks * 128 + 1;
	unsigned char *body = alcmem (size + 1);
	int     i;
	FILE   *fp;

	bzero (body, size);
	for (i = 0; i < blocks - 1; i++) {
		readbuf ();
		memcpy (&body[i * 128], qwkbuf, 128);
	}
	body[size - 1] = 0;
	zonk (body, size - 1);
	if (strlen (body) > msglen) {
		prompt (REPTB2B, msglen);
		return;
	}

	/* Check if the message has already been uploaded */

	if (!checkcrc (body))
		return;

	/* Now find out what the end-of-line character is and translate */

	if (strchr (body, EOL_GREEKQWK)) {
		/* A GreekQWK message, translate ASCII EOL_GREEKQWK -> ASCII 10 */

		char    x[256];

		memcpy (x, &kbdxlation[xlationtable], 256);
		x[EOL_GREEKQWK] = '\n';
		faststgxlate (body, x);
	} else {

		/* Have to assume it's a standard QWK message */

		char    x[256];

		memcpy (x, &kbdxlation[xlationtable], 256);
		x[EOL_QWK] = '\n';
		faststgxlate (body, x);
	}

	if (body[strlen (body) - 1] != '\n')
		strcat (body, "\n");

	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Unable to open %s for writing", fname);
	}

	if (write (fileno (fp), body, strlen (body)) != strlen (body)) {
		error_fatalsys ("Unable to write to %s", fname);
	}

	fclose (fp);
}


static void
doheader (char *header)
{
	FILE   *fp;

	if ((fp = fopen (header, "w")) == NULL) {
		error_fatalsys ("Unable to create message header %s", header);
	}
	if (fwrite (&msg, sizeof (msg), 1, fp) != 1) {
		fclose (fp);
		error_fatalsys ("Unable to write message header %s", header);
	}
	fclose (fp);
}


void
skip ()
{
	int     i;

	for (i = 1; i < blocks; i++)
		readbuf ();
}


static int
controlmsg ()
{
	if (sameas (msg.subject, "CONFIG")) {
		prompt (NOCFMSG);
		return 0;
	}

	return handlecontrolmsg (&qwkhdr, &msg);
}


static int
processmsg ()
{
	int     retval = 0;
	char    bodyfname[256], headerfname[256], command[256];

	bzero (&msg, sizeof (msg));


	/* Set up a few easy fields */

	initqwkhdr ();


	/* Setup the conference number and club name */

	if (!setupclub ())
		goto skip;


	/* Setup the recipient of the message */

	if (!setuprecipient ())
		goto skip;


	/* Print a table entry now that we have all necessary data */

	prompt (REPTB,
		sameas (msg.to, MSG_ALL) ? msg_getunit (REPTBALL, 1) : msg.to,
		conf ? clubhdr.club : omceml);


	/* Check if message is inactive (erased, usually) */

	/*
	   if(qwkhdr.active!=MSG_ACT){
	   prompt(REPTBIN);
	   retval=0;
	   goto skip;
	   }
	 */

	/* Is this a control message? If yes, process it */

	if (isctlmsg)
		return controlmsg (msg);


	/* Check for write permissions in the club */

	if (!checkperms ())
		goto skip;


	/* Check if user has enough credits to post to the club */

	if (!checkcreds ())
		goto skip;


	/* Check for attempts to post private messages in clubs */

	if (!checkprivclub ())
		goto skip;


	/* Check for attempts to post Email messages to ALL */

	if (!checkemailall ())
		goto skip;


	/* Public message with return receipt requested */

	if (!checkpublrrr ())
		goto skip;


	/* Set up the history field for the message */

	if (!setuphist ())
		goto skip;


	/* Done with the header, read the message body and prepare for posting */

	sprintf (bodyfname, TMPDIR "/B%d", getpid ());
	sprintf (headerfname, TMPDIR "/H%d", getpid ());
	dobody (bodyfname);
	doheader (headerfname);


	/* All is well, post it */

	sprintf (command, "%s %s %s", mkfname (BBSMAILBIN), headerfname,
		 bodyfname);
	if (system (command)) {
		error_fatal ("Command %s failed", command);
	}
	usr_chargecredits (charge);
	thisuseracc.msgswritten++;

	unlink (bodyfname);
	unlink (headerfname);


	/* Notify the sender */

	bzero (command, sizeof (command));
	memcpy (command, qwkhdr.from, sizeof (qwkhdr.from));
	zonk (command, sizeof (qwkhdr.from));

	if (msg.flags & MSF_RECEIPT)
		prompt (REPTBRR);
	else if (!sameas (command, thisuseracc.userid)) {
		prompt (REPTBAS, thisuseracc.userid);
	} else
		prompt (REPTBOK);


	/* Notify the recipient, if on-line */

	if (!(thisuseronl.flags & OLF_INVISIBLE) && usr_insys (msg.to, 0)) {
		if (conf)
			sprompt_other (othrshm, out_buffer, SIGINJ,
				       thisuseracc.userid,
				       msg.subject, clubhdr.club);
		else
			sprompt_other (othrshm, out_buffer, EMLINJ,
				       thisuseracc.userid, msg.subject);

		usr_injoth (&othruseronl, out_buffer, 0);
	}

	return 1;


	/* Exit in various ways */

	return retval;

      skip:
	skip ();
	return 0;
}


static int
process (char *fname)
{
	int     nummsgs = 0, numsuccessful = 0;

	if ((rep = fopen (fname, "r")) == NULL) {
		error_intsys ("Unable to open reply packet %s for reading!",
			      fname);
		return -1;
	}

	if (checkbbsid ())
		return -1;

	prompt (REPHD);

	while (!feof (rep)) {
		int     res;

		readbuf ();
		if (feof (rep) || ferror (rep))
			break;
		memcpy (&qwkhdr, &qwkbuf, sizeof (qwkhdr));
		res = processmsg ();
		if (res < 0)
			return -1;
		else if (res == 1)
			nummsgs++, numsuccessful++;
		else
			nummsgs++;
	}

	prompt (ENDUL, numsuccessful, nummsgs, msg_getunit (MSGSNG, nummsgs));

	return 0;
}


void static
mkxlation ()
{
	if (!loadprefs (USERQWK, &userqwk)) {
		error_fatal ("Unable to read user mailer preferences for %s",
			     thisuseracc.userid);
	}

	readxlation ();
	xlationtable = (userqwk.flags & OMF_TR) >> OMF_SHIFT;
}


int
omupload ()
{
	int     i, j, res;
	struct dirent **d = NULL;

	mkxlation ();

	openreqdb ();
	loadclubids ();
	startqsc ();

	j = scandir (".", &d, msgsel, alphasort);
	if (!j) {
		if (d)
			free (d);
		prompt (NOMSGS, bbsid, thisuseracc.userid);
		return -1;
	}

	for (res = i = 0; i < j; i++) {
		if (!res)
			res = process (d[i]->d_name);
		free (d[i]);
	}

	free (d);
	doneclubids ();
	updateqsc ();
	saveqsc ();
	doneqsc ();

	return res;
}


/* End of File */
