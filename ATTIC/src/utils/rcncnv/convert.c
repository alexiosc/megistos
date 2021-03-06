/*****************************************************************************\
 **                                                                         **
 **  FILE:     convert.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 "recent" to Megistos format.               **
 **  NOTES:    This is NOT guarranteed to work on anything but MajorBBS     **
 **            version 5.31, for which it was written.                      **
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
\*****************************************************************************/


/*
 * $Id: convert.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: convert.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/23 08:14:06  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1998/12/27 16:40:35  alexios
 * Added autoconf support.
 *
 * Revision 1.0  1998/08/14 12:03:41  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id: convert.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_PWD_H 1
#define WANT_GRP_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include <megistos/bbs.h>



#define RECENT_RECLEN 166



void
convert (char *arg_dir, char *arg_majordir)
{
	FILE   *fp;
	char    rec[16384], c, *fname = rec;
	int     reclen;
	int     num = 0;
	useracc_t uacc;
	char    uid[32];

	/* Start conversion */

	sprintf (fname, "%s/recent.txt", arg_majordir ? arg_majordir : ".");
	fp = fopen (fname, "r");
	if (fp == NULL) {
		sprintf (fname, "%s/RECENT.TXT",
			 arg_majordir ? arg_majordir : ".");
		if ((fp = fopen (fname, "r")) == NULL) {
			fprintf (stderr,
				 "rcncnv: convert(): unable to find recent.txt or "
				 "RECENT.TXT.\n");
			exit (1);
		}
	}

	while (!feof (fp)) {
		if (fscanf (fp, "%d\n", &reclen) == 0) {
			if (feof (fp))
				break;
			fprintf (stderr,
				 "rcncnv: convert(): unable to parse record length. "
				 "Corrupted file?\n");
			exit (1);
		}
		if (feof (fp))
			break;
		fgetc (fp);	/* Get rid of the comma after the record length */

		if (reclen != RECENT_RECLEN) {
			fprintf (stderr,
				 "rcncnv: convert(): record length isn't %d. "
				 "Is this a v5.31 file?\n", RECENT_RECLEN);
			exit (1);
		}

		if (fread (rec, reclen, 1, fp) != 1) {
			fprintf (stderr,
				 "rcncnv: convert(): unable to read record around "
				 "pos=%ld.\n", ftell (fp));
			exit (1);
		}

		strcpy (uid, rec);

		{
			char    fname[256];
			FILE   *fp;

			sprintf (fname, "%s/%s", arg_dir, uid);
			if ((fp = fopen (fname, "r")) == NULL)
				continue;
			if (fread (&uacc, sizeof (uacc), 1, fp) != 1) {
				int     i = errno;

				fprintf (stderr,
					 "rcncnv: unable to read %s (errno=%d)\n",
					 fname, i);
				exit (1);
			}
			fclose (fp);

			uacc.connections = *((int *) (&rec[10]));

			if ((fp = fopen (fname, "w")) == NULL) {
				int     i = errno;

				fprintf (stderr,
					 "rcncnv: unable to open %s (errno=%d)\n",
					 fname, i);
				exit (1);
			}
			if (fwrite (&uacc, sizeof (uacc), 1, fp) != 1) {
				int     i = errno;

				fprintf (stderr,
					 "rcncnv: unable to write %s (errno=%d)\n",
					 fname, i);
				exit (1);
			}
			fclose (fp);
		}


		/* DONE! */
		num++;
		do
			c = fgetc (fp);
		while (c == '\n' || c == '\r' || c == 26);
		ungetc (c, fp);
	}

	printf ("\n\nUpdated %d users.\n", num);
}


/* End of File */
