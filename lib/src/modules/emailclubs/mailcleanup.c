/*****************************************************************************\
 **                                                                         **
 **  FILE:     mailcleanup.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95                                              **
 **  PURPOSE:  Perform cleanup on email and club messages                   **
 **  NOTES:    Actions performed:                                           **
 **            email: delete old messages                                   **
 **            clubs: delete old messages if applicable,                    **
 **                   sync club statistics (msgs, files, blts, unapp, etc)  **
 **                   repost periodic messages                              **
 **                   reindex messages                                      **
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
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.4  1998/12/27 15:17:13  alexios
 * Added autoconf support.
 *
 * Revision 1.3  1998/08/11 09:59:43  alexios
 * Made sure msg num of next email is higher than any existing
 * email.
 *
 * Revision 1.2  1998/07/24 10:08:19  alexios
 * Upgraded to version 0.6 of library.
 *
 * Revision 1.1  1997/11/06 20:09:02  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/30 12:52:57  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRINGS_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mailcleanup.h"
#include "mbk_emailclubs.h"






int     dayssince = 1;
int     numusers = 0;
int     nummodified = 0;

int     emllif;


void
cleanup_init ()
{
	char    fname[256];
	FILE   *fp;
	int     cof = cofdate (today ());
	promptblock_t *msg;

	printf ("Email/Clubs cleanup\n\n");

	mod_init (INI_TTYNUM | INI_OUTPUT | INI_SYSVARS | INI_ERRMSGS |
		  INI_CLASSES);

	msg = msg_open ("emailclubs");

	emllif = msg_int (EMLLIF, -1, 32767);

	msg_close (msg);

	sprintf (fname, "%s/%s", mkfname (MSGSDIR), DAYSSINCEFILE);
	if ((fp = fopen (fname, "r")) != NULL) {
		int     i;

		if (fscanf (fp, "%d\n", &i) == 1) {
			dayssince = cof - i;
			if (dayssince < 0)
				dayssince = 1;
		}
		fclose (fp);
	}
	if ((fp = fopen (fname, "w")) != NULL) {
		fprintf (fp, "%d\n", cof);
		fclose (fp);
	}
	chmod (fname, 0660);
	printf ("Days since last cleanup: %d\n\n", dayssince);
}



void
emailcleanup ()
{
	char    fname[256];
	DIR    *dp;
	struct dirent *dir;
	message_t msg;
	FILE   *fp;
	int     ctoday = cofdate (today ());
	int     emldel = 0, emldelb = 0;
	int     maxmsgno = 0;

	if (dayssince < 1) {
		printf ("emailcleanup(): no need to cleanup email yet.\n");
		return;
	} else
		printf ("E-Mail cleanup...\n");

	strcpy (fname, mkfname (EMAILDIR));
	if ((dp = opendir (fname)) == NULL) {
		printf
		    ("emailcleanup(): can't open directory %s, cleanup not done\n",
		     fname);
		return;
	}

	sysvar->emsgslive = 0;
	while ((dir = readdir (dp)) != NULL) {
		if (!isdigit (dir->d_name[0]))
			continue;
		sprintf (fname, "%s/%s", mkfname (EMAILDIR), dir->d_name);

		if ((fp = fopen (fname, "r")) == NULL)
			continue;

		memset (&msg, 0, sizeof (msg));
		if (fread (&msg, sizeof (msg), 1, fp) != 1) {
			fclose (fp);
			continue;
		}
		fclose (fp);

		if (emllif >= 0) {
			if ((ctoday - cofdate (msg.crdate)) > emllif) {
				struct stat st;

				if (!stat (fname, &st))
					emldelb += st.st_size;
				emldel++;
				unlink (fname);
				strcpy (fname,
					mkfname (EMAILATTDIR "/"
						 FILEATTACHMENT, msg.msgno));
				if (!stat (fname, &st))
					if (st.st_nlink == 1)
						emldelb += st.st_size;
				unlink (fname);
			} else
				sysvar->emsgslive++;
		}
	}

	/* Paranoia check: make sure club's msgno pointer points beyond
	   last message in area */

	if (sysvar->emessages < maxmsgno)
		sysvar->emessages = maxmsgno;


	closedir (dp);
	printf ("\nemailcleanup(): killed %d old email message(s)\n", emldel);
	printf ("                freed %d byte(s)\n", emldelb);
	printf ("                There are %d active message(s) now\n\n",
		sysvar->emsgslive);
}


void    doreindex ();


int
handler_cleanup (int argc, char *argv[])
{
	cleanup_init ();
	emailcleanup ();
	clubcleanup ();
	doreindex ();
	return 0;
}


/* End of File */
