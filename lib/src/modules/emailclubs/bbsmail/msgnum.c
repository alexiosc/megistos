/*****************************************************************************\
 **                                                                         **
 **  FILE:     msgnum.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **            D, August 1996, Version 2.0                                  **
 **  PURPOSE:  Find a message number for the new message.                   **
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
 * Added autoconf support. Migrated to new locking style.
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
getemsgnum (message_t *msg)
{
	char    chkname[256];
	struct stat st;

	/* Wait for lock to clear */

	if (lock_wait (NEMESSAGELOCK, 5) == LKR_TIMEOUT) {
		if (usercaller)
			prompt (TIMEOUT1);
		if (lock_wait (NEMESSAGELOCK, 55) == LKR_TIMEOUT) {
			if (usercaller)
				prompt (TIMEOUT2);
			error_log ("Timed out (60 sec) waiting for %s",
				   NEMESSAGELOCK);
			exit (1);
		}
	}

	/* Lock the area */

	lock_place (NEMESSAGELOCK, "seeking");


	/* Get the next message number in a paranoid but safe way */

	do {
		sysvar->emessages++;
		strcpy (chkname,
			mkfname ("%s/" MESSAGEFILE, EMAILDIR,
				 sysvar->emessages));
	} while (!stat (chkname, &st));


	/* Remove the lock */

	lock_rm (NEMESSAGELOCK);


	/* Set the message number in the header */

	msg->msgno = sysvar->emessages;


	/* Debugging info */

#ifdef DEBUG
	printf ("Right... This should be email message #%d\n",
		sysvar->emessages);
#endif
}



void
getcmsgnum (message_t *msg)
{
	struct clubheader clubhdr;
	FILE   *fp;
	char    fname[256], chkname[256];
	struct stat st;

	/* Read the club header */

	strcpy (fname, mkfname ("%s/h%s", CLUBHDRDIR, msg->club));
	if ((fp = fopen (fname, "r")) == NULL) {
		error_logsys ("Unable to open %s", fname);
		exit (1);
	}

	if (fread (&clubhdr, sizeof (clubhdr), 1, fp) != 1) {
		error_logsys ("Unable to read %s", fname);
		fclose (fp);
		exit (1);
	}
	fclose (fp);


	/* Wait for club lock to clear */

	sprintf (fname, CLUBLOCK, clubhdr.club);
	if (lock_wait (fname, 5) == LKR_TIMEOUT) {
		if (usercaller)
			prompt (TIMEOUT1);
		if (lock_wait (fname, 55) == LKR_TIMEOUT) {
			if (usercaller)
				prompt (TIMEOUT2);
			error_log ("Timed out (60 sec) waiting for %s",
				   NEMESSAGELOCK);
			exit (1);
		}
	}


	/* Place the lock */

	lock_place (fname, "seeking");


	/* Good old paranoid way of calculating next msg number */

	do {
		clubhdr.msgno++;
		strcpy (chkname,
			mkfname ("%s/%s/" MESSAGEFILE, MSGSDIR, clubhdr.club,
				 clubhdr.msgno));
	} while (!stat (chkname, &st));


	/* Update the club header as well */

	clubhdr.nmsgs++;
	if (msg->flags & MSF_FILEATT) {
		clubhdr.nfiles++;
		if ((msg->flags & MSF_APPROVD) == 0)
			clubhdr.nfunapp++;
	}


	/* And write the club header back */

	strcpy (fname, mkfname ("%s/h%s", CLUBHDRDIR, msg->club));
	if ((fp = fopen (fname, "w")) == NULL) {
		error_logsys ("Unable to create %s", fname);
		exit (1);
	}

	if (fwrite (&clubhdr, sizeof (clubhdr), 1, fp) != 1) {
		error_logsys ("Unable to write %s", fname);
		fclose (fp);
		exit (1);
	}
	fclose (fp);


	/* Done with the club header, remove the lock */

	lock_rm (fname);


	/* Store the message number in the header */

	msg->msgno = clubhdr.msgno;


	/* And increase the total number of club messages written */

	sysvar->sigmessages++;


	/* Debugging info */

#ifdef DEBUG
	printf ("Right... This should be club %s message #%ld\n", clubhdr.club,
		msg->msgno);
#endif
}


/* End of File */
