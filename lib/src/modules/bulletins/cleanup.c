/*****************************************************************************\
 **                                                                         **
 **  FILE:     cleanup.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.5                                    **
 **  PURPOSE:  Renumber the bulletins.                                      **
 **  NOTES:                                                                 **
 **                                                                         **
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
 * Revision 1.6  2004/02/29 18:09:28  alexios
 * Include file changes.
 *
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:15  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1999/07/18 21:19:18  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added autoconf support. Fixed stupid bug that wouldn't update
 * the number of bulletins in the club header. Various small
 * fixes, too.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
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
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_UNISTD_H 1
#define WANT_DIRENT_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"
#include <libtyphoon/typhoon.h>


static void
resetclubs ()
{
	char    fname[256];
	DIR    *dp;
	struct dirent *dir;
	struct clubheader club;
	FILE   *fp;

	strcpy (fname, mkfname (CLUBHDRDIR));
	if ((dp = opendir (fname)) == NULL) {
		error_fatalsys ("Can't open directory %s\n", fname);
	}

	while ((dir = readdir (dp)) != NULL) {
		if (dir->d_name[0] != 'h')
			continue;
		sprintf (fname, "%s/%s", mkfname (CLUBHDRDIR), dir->d_name);
		if ((fp = fopen (fname, "r")) == NULL) {
			error_fatalsys ("Error while opening club header %s",
					fname);
			continue;
		}

		/* Read the header */

		memset (&club, 0, sizeof (club));
		if (fread (&club, sizeof (club), 1, fp) != 1) {
			int     i = errno;

			printf ("Error while reading header (errno=%d)\n", i);
			fclose (fp);
			continue;
		}
		fclose (fp);
		if ((fp = fopen (fname, "w")) == NULL) {
			error_fatalsys ("Error while opening club header %s",
					fname);
			continue;
		}

		club.nblts = 0;

		/* Write the header */

		if (fwrite (&club, sizeof (club), 1, fp) != 1) {
			int     i = errno;

			printf ("Error while writing header (errno=%d)\n", i);
			fclose (fp);
			continue;
		}
		fclose (fp);
	}

	closedir (dp);
}


static void
updateheader (char *oldclub, int count)
{
	char    fname[256];
	FILE   *fp;
	struct clubheader club;

	/* Open the header of the club */

	sprintf (fname, "%s/h%s", mkfname (CLUBHDRDIR), oldclub);
	if ((fp = fopen (fname, "r+")) == NULL) {
		printf ("Error while opening club header %s (errno=%d)\n",
			fname, errno);
		return;
	}

	/* Read the header */

	memset (&club, 0, sizeof (club));
	if (fread (&club, sizeof (club), 1, fp) != 1) {
		printf ("Error while reading club header %s (errno=%d)\n",
			fname, errno);
		fclose (fp);
		return;
	}
	fclose (fp);
	if ((fp = fopen (fname, "w")) == NULL) {
		printf ("Error while opening club header %s (errno=%d)\n",
			fname, errno);
		return;
	}

	club.nblts = count;

	/* Write the header */

	if (fwrite (&club, sizeof (club), 1, fp) != 1) {
		printf ("Error while writing header (errno=%d)\n", errno);
		fclose (fp);
		return;
	}
	fclose (fp);
}


int
cleanup (int argc, char **argv)
{
	FILE   *fp;
	char    fname[256];
	int     dayssince = 1, cof = cofdate (today ());
	char    oldclub[64];
	int     count = 0;

	printf ("Bulletin cleanup\n\n");

	oldclub[0] = 0;
	sprintf (fname, "%s/..LAST.CLEANUP.BULLETINS", mkfname (MSGSDIR));
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

	if (dayssince < 1) {
		printf ("Cleanup not done yet.\n");
		return 0;
	}


	resetclubs ();

	{
		int     num, i = 0;
		FILE   *fp;
		char    fname[256];

		sprintf (fname, TMPDIR "/blt%lx", time (0));
		if ((fp = fopen (fname, "w")) == NULL) {
			printf ("Unable to open temp file\n");
			return 0;
		}

		dbopen ();

		if (!dblistfirst ()) {
			printf ("Empty database.\n");
			fclose (fp);
			unlink (fname);
			return 0;
		}

		num = 1;
		do {
			struct bltidx blt;

			dbget (&blt);
			blt.num = num++;
			if (fwrite (&blt, sizeof (blt), 1, fp) != 1) {
				int     i = errno;

				printf
				    ("FATAL! Unable to go on with bulletin cleanup (errno=%d, errno=%s).",
				     i, strerror (i));
				fclose (fp);
				unlink (fname);
				return 0;
			}
			i++;
		} while (dblistnext ());

		fclose (fp);
		chmod (fname, 0400);


		/* Delete everything in the database */

		dblistfirst ();
		do
			d_delete ();
		while (dblistnext ());


		/* Now put them back together again. */

		if ((fp = fopen (fname, "r")) == NULL) {
			printf ("FATAL ERROR, BULLETIN INDEX LOST.\n");
			return 0;
		}


		num = 1;
		for (; i > 0; i--) {
			struct bltidx blt;

			if (fread (&blt, sizeof (blt), 1, fp) != 1) {
				printf
				    ("FATAL ERROR, UNABLE TO READ FROM TEMPORARY BULLETIN INDEX\n");
				fclose (fp);
				return 0;
			}

			blt.num = num++;
			d_fillnew (BLTIDX, &blt);

			/* Count bulletins in the current club and update club header */

			if (!sameas (blt.area, oldclub)) {
				if (strlen (oldclub))
					updateheader (oldclub, count);
				strcpy (oldclub, blt.area);
				count = 1;
			} else
				count++;
		}


		if (strlen (oldclub))
			updateheader (oldclub, count);

		fclose (fp);
		chmod (fname, 0600);
		unlink (fname);

		printf ("%d Bulletin(s) in database.\n\n", num - 1);
	}

	printf ("Bulletin cleanup done.\n\n");

	return 0;
}


/* End of File */
