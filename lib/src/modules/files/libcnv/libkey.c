/*****************************************************************************\
 **                                                                         **
 **  FILE:     libkey.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 file DATabases to Megistos format.         **
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
 * $Id$
 *
 * $Log$
 * Revision 1.4  2003/12/24 20:12:12  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.2  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include <megistos/bbs.h>
#include <megistos/config.h>
#include <megistos/cnvutils.h>
#include <megistos/files.h>


void
libkey (char *arg_majordir)
{
	FILE   *fp;
	char    rec[16384], c, *fname = rec;
	int     reclen;
	int     num = 0;
	struct libidx lib;
	struct keywordidx keyword;

	bzero (&lib, sizeof (lib));

	sprintf (fname, "%s/libkwd.txt", arg_majordir ? arg_majordir : ".");
	fp = fopen (fname, "r");
	if (fp == NULL) {
		sprintf (fname, "%s/LIBKWD.TXT",
			 arg_majordir ? arg_majordir : ".");
		if ((fp = fopen (fname, "r")) == NULL) {
			fprintf (stderr,
				 "libcnv: libkey(): unable to find libkwd.txt or LIBKWD.TXT.\n");
			exit (1);
		}
	}

	printf ("\nInstalling Keywords... ");
	fflush (stdout);

	while (!feof (fp)) {
		if (fscanf (fp, "%d\n", &reclen) == 0) {
			if (feof (fp))
				break;
			fprintf (stderr,
				 "libcnv: libkey(): unable to parse record length. Corrupted file?\n");
			exit (1);
		}
		if (feof (fp))
			break;
		fgetc (fp);	/* Get rid of the comma after the record length */

		if (fread (rec, reclen, 1, fp) != 1) {
			fprintf (stderr,
				 "libcnv: libkey(): unable to read record around pos=%ld.\n",
				 ftell (fp));
			exit (1);
		}

		bzero (&keyword, sizeof (keyword));

		/* Major has some REALLY strange use for keywords, some kind of timestamp
		   which we don't want. All those seem to have a keyword starting with a
		   blank, which is forbidden to the normal ones. We use it to tell them
		   apart. */

		if (!isspace (rec[23]))
			strcpy (keyword.keyword, &rec[23]);
		else
			goto skipnl;

		strcpy (keyword.fname, lcase (&rec[10]));
		keyword.approved = toupper (rec[0]) == 'A';

		/* Convert the Major LIB string to our own libnum index */

		if (!sameas (&rec[1], lib.keyname)) {
			char    tmp[10];

			strcpy (tmp, &rec[1]);
			if (libread (tmp, library.libnum, &lib) != 1) {
				printf
				    ("\nWarning: Library %s doesn't exist. Skipping key %s.\n",
				     lib.fullname, keyword.keyword);
			}
		}
		keyword.klibnum = lib.libnum;

		/* Major adds one extra keyword per file, that actually contains the file's
		   name as a keyword. This is used to speed up searchin, but we don't need
		   it due to different design. So we skip those keywords as well. */

		if (!strcmp (keyword.fname, keyword.keyword))
			goto skipnl;

		addkeyword (&keyword);

		/* DONE! */
		if ((++num % 100) == 0) {
			printf ("%d ", num);
			fflush (stdout);
		}

	      skipnl:
		do
			c = fgetc (fp);
		while (c == '\n' || c == '\r' || c == 26);
		ungetc (c, fp);
	}
	printf ("\n\nInstalled %d keywords.\n", num);

}


/* End of File */
