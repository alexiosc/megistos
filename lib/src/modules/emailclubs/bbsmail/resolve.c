/*****************************************************************************\
 **                                                                         **
 **  FILE:     resolve.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **            D, August 1996, Version 2.0                                  **
 **  PURPOSE:  Resolve recipient of email message (auto-forwarding etc. )   **
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
 * Revision 1.5  2003/12/29 07:51:38  alexios
 * Adjusted #includes; changed all instances of struct message to message_t.
 *
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  1998/12/27 16:31:55  alexios
 * Added autoconf support. Migrated to new locking scheme.
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
    "$Id$";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "bbsmail.h"
#include <mbk/mbk_emailclubs.h>


void
resolverecipient (char *s, char *by)
{
	char    original[256], fname[256], lock[256];
	int     n = 0, maxn = msg_int (MAXBNCE, 1, 100);
	struct emailuser user;
	FILE   *fp;

	if (strchr (s, '%') || strchr (s, '@'))
		return;

	strcpy (original, s);
	strcpy (by, s);

	for (;;) {
		strcpy (fname, mkfname ("%s/%s", MSGUSRDIR, s));
		sprintf (lock, ECUSERLOCK, s);

		if ((lock_wait (lock, 20)) == LKR_TIMEOUT)
			return;
		lock_place (lock, "reading");

		if ((fp = fopen (fname, "r")) == NULL) {
			lock_rm (lock);
			return;
		}
		if (fread (&user, sizeof (struct emailuser), 1, fp) != 1) {
			fclose (fp);
			lock_rm (lock);
			return;
		}
		fclose (fp);
		lock_rm (lock);
		if (!user.forwardto[0])
			return;
		if (!strcmp (s, user.forwardto))
			return;
		strcpy (by, s);
		strcpy (s, user.forwardto);
/*    print("BY:  %s, TO: %s\n",by,s); */
		if (!strcmp (original, s))
			return;
		if (++n > maxn)
			return;
	}
}


void
checkautofw (message_t *msg)
{
	char    original[256], temp[256];

	resolverecipient (msg->to, original);
	if (strcmp (original, msg->to)) {
		sprintf (temp, "%s %s %s", HST_AUTOFW, original, msg->history);
		strncpy (msg->history, temp, sizeof (msg->history));
		msg->flags |= MSF_AUTOFW;
	}
}


/* End of File */
