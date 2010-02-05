/*****************************************************************************\
 **                                                                         **
 **  FILE:     msghdr.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **            D, August 1996, Version 2.0                                  **
 **  PURPOSE:  Functions dealing with message headers                       **
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
 * $Id: msghdr.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: msghdr.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/05/21 20:04:51  alexios
 * Removed hardwired, system(3)-based chown operation to bbs.bbs in
 * favour of using the chown(2) system call and the appropriate BBS
 * instance UID and GIDs. This may fix serious permission-related bugs.
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
 * Revision 1.5  1999/07/28 23:19:38  alexios
 * Refuse to touch the date and time of creation of a message
 * if it came from the network.
 *
 * Revision 1.4  1999/07/18 22:07:59  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Changed message
 * ID code to reflect its use in the new IHAVE database.
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
    "$Id: msghdr.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";



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
readmsghdr (char *fname, message_t *msg)
{
	FILE   *fp;

	if ((fp = fopen (fname, "r")) == NULL) {
		error_fatalsys ("Unable to open mail header file %s (%d)",
				fname, errno);
	}

	if (fread (msg, sizeof (message_t), 1, fp) != 1) {
		fclose (fp);
		error_fatalsys ("Unable to read mail header file %s", fname);
		exit (1);
	}

	fclose (fp);
}


void
writemsghdr (char *fname, message_t *msg)
{
	FILE   *fp;

#ifdef DEBUG
	printf ("Dumping new mail header back to header file...\n");
	printf ("Club:    (%s)\n", msg->club);
	printf ("From:    (%s)\n", msg->from);
	printf ("To:      (%s)\n", msg->to);
	printf ("Subject: (%s)\n", msg->subject);
	printf ("History: (%s)\n", msg->history);
	printf ("Fatt:    (%s)\n", msg->fatt);
	printf ("Msgno:   (%ld)\n", msg->msgno);
	printf ("flags:   (%lx)\n", msg->flags);
	printf ("\n");
#endif

	if ((fp = fopen (fname, "w")) == NULL) {
		error_logsys ("Unable to create %s", fname);
		fclose (fp);
		exit (1);
	}
	if (fwrite (msg, sizeof (message_t), 1, fp) != 1) {
		error_logsys ("Unable to write %s", fname);
		exit (1);
	}
	fclose (fp);
}



void
preparemsghdr (message_t *msg, int email)
{
	/* Don't touch the date of network messages */

	if ((msg->flags & MSF_NET) == 0) {
		msg->crdate = today ();
		msg->crtime = now ();
	}
	msg->replies = msg->timesread = 0;
	if (email) {
		randomize ();
		while (!msg->cryptkey)
			msg->cryptkey = rnd (1 << 30);
	} else
		msg->cryptkey = 0;

	/* Don't touch the net message vector if it's already there */

	if (!msg->origbbs[0]) {
		strcpy (msg->origbbs, bbscode);
		strcpy (msg->origclub, msg->club);
		sprintf (msg->msgid, "%d.%08x%04x", msg->msgno, (int) time (NULL), (int) getpid ());	/* As unique as things go */
	}

	if (!msg->fatt[0])
		sprintf (msg->fatt, "%d.att", msg->msgno);
}


void
writemessage (char *srcname, message_t *msg, int email)
{
	char    msgname[256], lock[256], buff[8192];
	FILE   *fp, *fp2;
	int     count;

	/* Wait for locks to clear */

	sprintf (lock, CLUBLOCK, (email ? EMAILCLUBNAME : msg->club));
	if (lock_wait (lock, 5) == LKR_TIMEOUT) {
		if (usercaller)
			prompt (TIMEOUT1);
		if (lock_wait (lock, 55) == LKR_TIMEOUT) {
			if (usercaller)
				prompt (TIMEOUT2);
			error_log ("Timed out (60 sec) waiting for %s", lock);
			exit (1);
		}
	}


	/* Lock it */

	lock_place (lock, "adding");


	/* Generate the filename */

	if (email)
		strcpy (msgname,
			mkfname (EMAILDIR "/" MESSAGEFILE, msg->msgno));
	else
		strcpy (msgname,
			mkfname ("%s/%s/" MESSAGEFILE, MSGSDIR, msg->club,
				 msg->msgno));


	/* Write the message header */

	if ((fp = fopen (msgname, "w")) == NULL) {
		error_logsys ("Unable to create %s", msgname);
		lock_rm (lock);
		fclose (fp);
		exit (1);
	}

	if (fwrite (msg, sizeof (message_t), 1, fp) != 1) {
		error_logsys ("Unable to write %s", msgname);
		lock_rm (lock);
		exit (1);
	}


	/* Debugging info */

#ifdef DEBUG
	printf ("Gonna save the message body as '%s'.\n", msgname);
#endif


	/* Now copy the message body */

	if ((fp2 = fopen (srcname, "r")) == NULL) {
		error_logsys ("Unable to open %s", srcname);
		lock_rm (lock);
		fclose (fp2);
		fclose (fp);
		exit (1);
	}

	while ((count = fread (&buff, 1, sizeof (buff), fp2)) > 0) {
		bbsencrypt (buff, sizeof (buff), msg->cryptkey);
		if (fwrite (&buff, 1, count, fp) != count) {
			error_logsys ("Unable to write %s", msgname);
			lock_rm (lock);
			fclose (fp2);
			fclose (fp);
			exit (1);
		}
	}


	/* Remove the lock, close the files and adjust permissions */

	lock_rm (lock);
	fclose (fp2);
	fclose (fp);
	chmod (msgname, 0660);


	/* Adjust ownership if we're the super-user */

	if ((!getuid ()) || (!getgid ())) chown (msgname, bbs_uid, bbs_gid);
}






/* End of File */
