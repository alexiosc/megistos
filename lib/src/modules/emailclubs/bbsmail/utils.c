/*****************************************************************************\
 **                                                                         **
 **  FILE:     utils.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **            D, August 1996, Version 2.0                                  **
 **  PURPOSE:  Various support functions for bbsmail                        **
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
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.7  2000/01/08 12:47:02  alexios
 * Fixed bug that got the originating BBS field wrong in the
 * IHAVE records.
 *
 * Revision 1.6  1999/08/13 17:09:41  alexios
 * Commented out debugging information.
 *
 * Revision 1.5  1999/07/28 23:19:38  alexios
 * Slight changes and one minor bug fixed.
 *
 * Revision 1.4  1999/07/18 22:07:59  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Added code for
 * the new IHAVE database.
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
    "$Id$";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/bbsmail.h>
#include <megistos/ihavedb.h>
#include <megistos/typhoon.h>
#include <megistos/mbk_emailclubs.h>


void
bbsencrypt (char *buf, int size, int key)
{
	char    longkey[4] = { 0, 0, 0, 0 };
	register char smallkey;
	register int i;

	if (!key)
		return;		/* club messages (key=0) aren't encrypted */
	memcpy (longkey, &key, sizeof (int));
	smallkey = (longkey[0] ^ longkey[1] ^ longkey[2] ^ longkey[3]);
	for (i = 0; i < size; i++)
		buf[i] ^= smallkey;
}


void
addihave (struct message *msg)
{
	struct ihaverec ihave;

	mkdir (mkfname (IHAVEDIR), 0777);	/* Paranoia mode and a silly thing to do */
	d_dbfpath (mkfname (IHAVEDIR));
	d_dbdpath (mkfname (IHAVEDIR));
	if (d_open ("ihavedb", "s") != S_OKAY) {
		error_log ("Cannot open ihave database (db_status %d)\n",
			   db_status);
		return;
	}

	bzero (&ihave, sizeof (ihave));

	ihave.time = time (NULL);
	strcpy (ihave.bbs, msg->origbbs);
	strcpy (ihave.msgid, msg->msgid);
	strcpy (ihave.club, msg->club);	/* The message always comes from a club */
	strcpy (ihave.orgclub, msg->origclub);
	ihave.num = msg->msgno;
	ihave.type = IHT_MESSAGE;

	d_fillnew (IHAVEREC, &ihave);	/* Add it to the database */

#if 0
	{
		int     i = 1;

		/*struct netqueryc c; */
		d_keyfrst (NETQUERYC);
		do {
			d_recread (&ihave);
			fprintf (stderr, "%2d. %s/%s/%s --> %s/%d\n",
				 i++, ihave.bbs, ihave.orgclub, ihave.msgid,
				 ihave.club, ihave.num);
		} while (d_keynext (NETQUERYC) == S_OKAY);
	}
#endif

	d_close ();		/* And close the database */
}


void
copyatt (int copymode, struct message *msg, int email, char *attachment)
{
	if (copymode && msg->flags & MSF_FILEATT) {
		char    attname[256];

		/* Generate the attachment name */

		if (email)
			strcpy (attname,
				mkfname (EMAILATTDIR "/" FILEATTACHMENT,
					 msg->msgno));
		else
			strcpy (attname,
				mkfname ("%s/%s/%s/" FILEATTACHMENT, MSGSDIR,
					 msg->club, MSGATTDIR, msg->msgno));


		/* Debugging info */

#ifdef DEBUG
		printf ("The name of the file attachment is '%s'.\n", attname);
#endif

		switch (copymode) {
		case 1:
			/* Copy by hard-link */

			if (link (attachment, attname)) {
				error_logsys
				    ("Unable to make hard link %s->%s",
				     attname, attachment);
				exit (1);
			}
			break;
		case 2:
			/* Copy by symlink */

			if (symlink (attachment, attname)) {
				error_logsys ("Unable to make symlink %s->%s",
					      attname, attachment);
				exit (1);
			}
			break;
		case 3:
			{
				FILE   *fp, *fp2;
				int     count;
				char    buff[8192];

				/* Normal copy */

				if ((fp = fopen (attname, "w")) == NULL) {
					error_logsys ("Unable to create %s",
						      attname);
					fclose (fp);
					exit (1);
				}

				if ((fp2 = fopen (attachment, "r")) == NULL) {
					error_logsys ("Unable to open %s",
						      attachment);
					fclose (fp2);
					fclose (fp);
					exit (1);
				}

				while ((count =
					fread (&buff, 1, sizeof (buff),
					       fp2)) > 0) {
					if (fwrite (&buff, 1, count, fp) !=
					    count) {
						error_logsys
						    ("Unable to write %s",
						     attname);
						fclose (fp2);
						fclose (fp);
						exit (1);
					}
				}

				fclose (fp2);
				fclose (fp);
				break;
			}
		}

		/* Adjust permissions and ownership */

		chmod (attname, 0660);

		if ((!getuid ()) || (!getpid ())) {
			char    command[256];

			sprintf (command, "chown -f bbs.bbs %s >&/dev/null",
				 attname);
			system (command);
		}
	}
}


/* End of File */
