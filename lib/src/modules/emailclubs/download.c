/*****************************************************************************\
 **                                                                         **
 **  FILE:     download.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **  PURPOSE:  Download file attachments                                    **
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
 * Revision 0.6  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/11 10:03:22  alexios
 * Migrated file transfer calls to the new format.
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 16:54:26  alexios
 * Changed calls to setaudit() so the new auditing scheme is
 * used.
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_emailclubs.h"
#include "email.h"


void
downloadatt (message_t *msg)
{
	struct stat st;
	char    nameless[256], fname[256], dnlname[256], command[256];
	char    descr[256], dnldir[256];
	char    audit[4][80];
	int     noname, i;

	if ((msg->flags & MSF_FILEATT) == 0)
		return;

	if (msg->club[0]) {
		int     i = getclubax (&thisuseracc, msg->club);

		if ((msg->flags & MSF_APPROVD) == 0) {
			prompt (ATTNAP);
			if (i < CAX_COOP)
				return;
		} else if (i < CAX_DNLOAD) {
			prompt (ATTNAX);
			return;
		}
	}

	if (!usr_canpay (dnlchg)) {
		prompt (DNLNCRD);
		return;
	} else
		usr_chargecredits (dnlchg);

	sprintf (nameless, "%d.att", msg->msgno);
	noname = sameas (msg->fatt, nameless);
	sprintf (fname, "%s/%s/" MSGATTDIR "/%s", mkfname (MSGSDIR),
		 msg->club[0] ? msg->club : EMAILDIRNAME, nameless);

	if (stat (fname, &st)) {
		prompt (ATTNF, msg->club[0] ? msg->club : EMAILCLUBNAME,
			msg->msgno);
		return;
	}

	if (noname)
		prompt (ATTMNT1, st.st_size);
	else
		prompt (ATTMNT2, msg->fatt, st.st_size);

	if (!get_bool (&i, ATTDNL, ATTERR, ATTDEF, 0))
		return;
	if (!i)
		return;

	sprintf (dnldir, TMPDIR "/dnlatt%d%lx", getpid (), time (0));
	sprintf (dnlname, "%s/%s", dnldir, msg->fatt);
	sprintf (command, "(mkdir %s && ln -s %s %s) >&/dev/null",
		 dnldir, fname, dnlname);

	if (system (command)) {
		prompt (ATTIO);
		return;
	}

	sprintf (descr, msg_get (ATTDESC),
		 msg->club[0] ? msg->club : EMAILCLUBNAME, msg->msgno);

	strcpy (audit[0], AUS_ESDNLS);
	sprintf (audit[1], AUD_ESDNLS,
		 thisuseracc.userid, msg->club[0] ? msg->club : EMAILCLUBNAME,
		 (int) msg->msgno);
	strcpy (audit[2], AUS_ESDNLF);
	sprintf (audit[3], AUD_ESDNLF,
		 thisuseracc.userid, msg->club[0] ? msg->club : EMAILCLUBNAME,
		 (int) msg->msgno);
	xfer_setaudit (AUT_ESDNLS, audit[0], audit[1], AUT_ESDNLF, audit[2],
		       audit[3]);

	xfer_add (FXM_DOWNLOAD, dnlname, descr, dnlchg, -1);

	xfer_run ();
	msg->timesdnl++;
	xfer_kill_list ();
	cnc_end ();
	system (STTYBIN " -echo start undef stop undef intr undef susp undef");
}


/* End of File */
