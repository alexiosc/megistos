/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubwrite.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1995                                               **
 **  PURPOSE:  Writing a club message                                       **
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
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/25 13:33:28  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:21:38  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support. Changes for the new locking functions.
 *
 * Revision 0.3  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
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
#define WANT_TIME_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_emailclubs.h"
#include "email.h"
#include "clubs.h"


void
clubwrite ()
{
	message_t msg, checkmsg;
	struct stat st;
	char    body[256], header[256], command[1024];
	FILE   *fp;
	int     attachment = 0;
	int     cleanupattachment = 1, killit = 0;
	int     clubmsg = 1;
	uint32  original = 0;
	char    attfile[256], *cp;

	if (getclubax (&thisuseracc, clubhdr.club) < CAX_WRITE) {
		prompt (WCNAXES);
		return;
	}

	if (!usr_canpay (clubhdr.postchg)) {
		prompt (WCNCRDS);
		return;
	}

	memset (&msg, 0, sizeof (msg));
	strcpy (msg.from, thisuseracc.userid);
	strcpy (msg.club, clubhdr.club);
	strcpy (clubdir, clubhdr.club);

	/* Get message recipient */

	if (!getclubrecipient (WCWHO, WCUNKID, WCHELP, msg.to))
		return;
	if (sameas (MSG_ALL, msg.to))
		prompt (WCRCPALL);
	else
		prompt (WCRCPOK, msg.to);


	/* Get message subject */

	if (!getsubject (msg.subject))
		return;


	/* Edit the message body */

	sprintf (body, TMPDIR "/B%d%08lx", getpid (), time (0));
	appendsignature (body);
	sprintf (header, TMPDIR "/H%d%08lx", getpid (), time (0));

	if (editor (body, msglen) || stat (body, &st)) {
		unlink (body);
		unlink (header);
		cnc_end ();
		return;
	} else
		cnc_end ();


	/* Ask for file attachment */

	if ((getclubax (&thisuseracc, clubhdr.club) >= CAX_UPLOAD) &&
	    usr_canpay (clubhdr.uploadchg)) {
		for (;;) {
			if (!askyesno
			    (&attachment, WCATT, WCRRSEL, clubhdr.uploadchg)) {
				if (confirmcancel ()) {
					unlink (body);
					unlink (header);
					return;
				} else
					continue;
			} else
				break;
		}

		if (attachment) {
			uploadatt (attfile,
				   clubmsg ? clubhdr.msgno +
				   1 : sysvar->emessages + 1);
			if (attfile[0]) {
				usr_chargecredits (clubhdr.uploadchg);
				msg.flags |= MSF_FILEATT;
				if (getclubax (&thisuseracc, msg.club) >=
				    CAX_COOP) {
					prompt (WCATTAPP);
					msg.flags |= MSF_APPROVD;
				} else {
					char    lock[256];

					prompt (WCATTNAP);
					sprintf (lock, CLUBLOCK, msg.club);
					if (lock_wait (lock, 10) ==
					    LKR_TIMEOUT)
						return;
					lock_place (lock, "updating");
					loadclubhdr (msg.club);
					clubhdr.nfunapp++;
					saveclubhdr (&clubhdr);
					lock_rm (lock);
				}
			}

			cp = getattname (msg.subject, clubhdr.msgno + 1);
			if (!cp) {
				unlink (body);
				unlink (header);
				unlink (attfile);
				return;
			} else
				strcpy (msg.fatt, cp);
		}
	}

	/* Check if user has enough credits */

	if (!usr_canpay (clubhdr.postchg)) {
		prompt (WCRNEC);
		killit = 1;
	}

	/* Mail the message */

	if ((fp = fopen (header, "w")) == NULL) {
		error_fatalsys ("Unable to create message header %s", header);
	}
	if (fwrite (&msg, sizeof (msg), 1, fp) != 1) {
		int     i = errno;

		fclose (fp);
		errno = i;
		error_fatalsys ("Unable to write message header %s", header);
	}
	fclose (fp);

	if (!attfile[0])
		sprintf (command, "%s %s %s", mkfname (BBSMAILBIN), header,
			 body);
	else
		sprintf (command, "%s %s %s -%c %s",
			 mkfname (BBSMAILBIN), header, body, 'c', attfile);
	system (command);


	/* Notify the user(s) */

	if ((fp = fopen (header, "r")) == NULL) {
		error_fatalsys ("Unable to read message header %s", header);
	}
	if (fread (&checkmsg, sizeof (msg), 1, fp) != 1) {
		int     i = errno;

		fclose (fp);
		errno = i;
		error_fatalsys ("Unable to read message header %s", header);
	}
	fclose (fp);

	if (checkmsg.msgno) {
		prompt (WECONFS, checkmsg.club, checkmsg.msgno);

		if (usr_insys (checkmsg.to, 1)) {
			sprompt_other (othrshm, out_buffer, WCRNOT,
				       checkmsg.from, checkmsg.club,
				       checkmsg.subject);
			if (usr_injoth (&othruseronl, out_buffer, 0))
				prompt (WENOTFD, othruseronl.userid);
		}
	}


	/* Clean up */

	usr_chargecredits (clubhdr.postchg);
	thisuseracc.msgswritten++;
	unlink (header);
	if (attfile[0] && cleanupattachment) {
		unlink (attfile);
		sprintf (attfile, "%s/%s/" MSGATTDIR "/" FILEATTACHMENT,
			 mkfname (MSGSDIR),
			 clubmsg ? clubhdr.club : EMAILDIRNAME, original);
	}
	unlink (body);
}


/* End of File */
