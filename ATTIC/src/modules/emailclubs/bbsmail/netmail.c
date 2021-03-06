/*****************************************************************************\
 **                                                                         **
 **  FILE:     netmail.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **            D, August 1996, Version 2.0                                  **
 **  PURPOSE:  Dispatch Internet mail.                                      **
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
 * $Id: netmail.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: netmail.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/29 07:51:38  alexios
 * Adjusted #includes; changed all instances of struct message to message_t.
 *
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.4  1999/07/18 22:07:59  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.3  1998/12/27 16:31:55  alexios
 * Added autoconf support.
 *
 * Revision 1.2  1998/07/24 10:29:57  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:17:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 11:23:40  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id: netmail.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <megistos/bbsinclude.h>

#include <megistos/bbs.h>
#include "bbsmail.h"
#include <mbk/mbk_emailclubs.h>



void
handlenetmail (message_t *msg, char *srcname)
{
	char    command[256], buffer[8192];
	FILE   *fp;
	struct stat st;
	useracc_t uacc;
	char    fatt[256];

	st.st_size = 0;
	stat (srcname, &st);

	if (!msg->fatt[0])
		sprintf (fatt, FILEATTACHMENT, msg->msgno);
	else
		strcpy (fatt, msg->fatt);

	usr_loadaccount (msg->from, &uacc);
#ifdef GREEK
	latinize (uacc.username);
#endif /* GREEK */

	if ((msg->flags & MSF_FILEATT) == 0) {
		sprintf (command, "cat - %s |%s %s",
			 srcname, msg_get (SENDMAIL), msg->to);
	} else {
		char    tmp[256];

		sprintf (tmp,
			 mkfname (EMAILATTDIR "/" FILEATTACHMENT, msg->msgno));
		sprintf (command, "uuencode <%s %s >/tmp/mailatt%05d", tmp,
			 fatt, getpid ());
		system (command);
		sprintf (command, "cat - %s /tmp/mailatt%05d|%s %s",
			 srcname, getpid (), msg_get (SENDMAIL), msg->to);
	}
	if ((fp = popen (command, "w")) == NULL) {
		error_logsys ("Unable to spawn %s pipe", msg_get (SENDMAIL));
		exit (1);
	}
	sprompt (buffer, NMSGHDR, uacc.username, msg->from, msg->subject,
		 msg->history, msg->flags & MSF_FILEATT ? fatt : "No",
		 msg->msgno, msg->flags & MSF_RECEIPT ? "Yes" : "No",
		 st.st_size);
	fprintf (fp, buffer);
	pclose (fp);
	sysvar->nmessages++;
}


void
checknetmail (message_t *msg, char *srcname)
{

#ifdef DEBUG
	printf ("Checking for netmail...\n");
#endif

	if (strchr (msg->to, '@') || strchr (msg->to, '%')) {
		handlenetmail (msg, srcname);
	}
}



/* End of File */
