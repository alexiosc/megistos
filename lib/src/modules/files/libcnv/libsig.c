/*****************************************************************************\
 **                                                                         **
 **  FILE:     libsig.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 library DATabases to Megistos format.      **
 **  NOTES:    This is NOT guarranteed to work on anything but MajorBBS     **
 **            version 5.31, for which it was written. Read ../README.      **
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
 * Revision 0.3  2000/01/06 10:37:25  alexios
 * Modified calls to mklib to reflect new third argument.
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


static char basedir[512];

static void
mkreadme (char *dirname, char *descr)
{
	char    tmp[1024];
	FILE   *fp;

	mkdir (basedir, 0700);
	sprintf (tmp, "%s/%s", basedir, dirname);
	mkdir (tmp, 0700);

	sprintf (tmp, "%s/%s/%s", basedir, dirname, rdmefil);
	if (!strlen (descr))
		return;
	if ((fp = fopen (tmp, "w")) == NULL) {
		fprintf (stderr, "libcnv: mkreadme(): Unable to create %s\n",
			 tmp);
		exit (1);
	}

	fputs (descr, fp);
	fclose (fp);
}


int
mkparentlib (char *libname, char *dirname, int key)
{
	int     res;
	char    tmp[256];

	makemainlib ();
	res = libread (libmain, 0, &library);
	if (res != 1) {
		fprintf (stderr, "Whoa! Library \"%s\" not found!\n", libmain);
		exit (1);
	}

	strcpy (tmp, libname);
	res = libread (tmp, library.libnum, &library);
	if (res != 1) {
		struct libidx lib;

		printf ("Creating library %s/%s...\n", libmain, libname);
		bzero (&lib, sizeof (lib));

		strcpy (lib.keyname, leafname (libname));
		sprintf (lib.fullname, "%s/%s", libmain, libname);

		if (dirname != NULL)
			strcpy (lib.dir, dirname);
		else
			sprintf (lib.dir, "%s/%s", library.dir, libname);
		printf ("Physical directories created under %s\n", lib.dir);
		strcpy (basedir, lib.dir);

		strcpy (lib.descr, "MajorBBS 5.xx Converted Libraries");
		lib.parent = library.libnum;
		lib.readkey = lib.downloadkey = lib.uploadkey =
		    lib.overwritekey = key;

		mklib (&lib, 0, 0);

		memcpy (&library, &lib, sizeof (library));
		return lib.libnum;
	}

	printf ("Library %s/%s found, will install under it.\n", libmain,
		libname);
	strcpy (basedir, library.dir);
	return library.libnum;
}


void
libsig (char *arg_under, char *arg_basedir, char *arg_majordir, int arg_key)
{
	FILE   *fp;
	char    rec[16384], c, *fname = rec;
	int     reclen;
	int     num = 0;
	struct libidx lib;

	sprintf (fname, "%s/libsig.txt", arg_majordir ? arg_majordir : ".");
	fp = fopen (fname, "r");
	if (fp == NULL) {
		sprintf (fname, "%s/LIBSIG.TXT",
			 arg_majordir ? arg_majordir : ".");
		if ((fp = fopen (fname, "r")) == NULL) {
			fprintf (stderr,
				 "libcnv: libsig(): unable to find libsig.txt or LIBSIG.TXT.\n");
			exit (1);
		}
	}

	mkparentlib (arg_under == NULL ? "Major" : arg_under, arg_basedir,
		     arg_key);
	printf ("Installing under %s\n", library.fullname);

	while (!feof (fp)) {
		if (fscanf (fp, "%d\n", &reclen) == 0) {
			if (feof (fp))
				break;
			fprintf (stderr,
				 "libcnv: libsig(): unable to parse record length. Corrupted file?\n");
			exit (1);
		}
		if (feof (fp))
			break;
		fgetc (fp);	/* Get rid of the comma after the record length */

		if (fread (rec, reclen, 1, fp) != 1) {
			fprintf (stderr,
				 "libcnv: libsig(): unable to read record around pos=%ld.\n",
				 ftell (fp));
			exit (1);
		}

		bzero (&lib, sizeof (lib));

		sprintf (lib.fullname, "%s/%s", library.fullname, rec);
		strcpy (lib.keyname, lcase (rec));
		sprintf (lib.dir, "%s/%s", library.dir, rec);


		/* BASICS */

		strcpy (lib.passwd, &rec[19]);	/* The password */
		strcpy (lib.descr, &rec[29]);	/* Short description */
		lib.parent = library.libnum;	/* Set the parent library */

		/* TIMESTAMP */

		lib.crdate = convert_date (stg2short (&rec[424]));
		lib.crtime = convert_time (stg2short (&rec[426]));

		/* SECURITY */

		/* Access keys */
		lib.readkey = lib.downloadkey = lib.uploadkey =
		    lib.overwritekey = arg_key;
		strcpy (lib.libops[0], &rec[9]);	/* The library's operator */

		/* LIMITS */

		lib.filelimit = stg2int (&rec[392]);	/* Max files */
		lib.filesizelimit = stg2int (&rec[400]) / 1000;	/* Max file size in Kb */
		lib.libsizelimit = stg2int (&rec[396]) / 1000000;	/* Max total size in Mb */
		/* Actually, we use "fake" Kb and Mb (base 10 rather than 2), because this
		   seems to be the way Sysops and MBBS sees it */

		/* CHARGES */

		lib.dnlcharge = stg2int (&rec[450]);	/* Download charge per file */
		lib.uplcharge = defuchg;	/* Set default upload charge -- MBBS doesn't have this */
		lib.rebate = rec[471];	/* Uploader royalties as a single byte 0-100 */

		/* STATISTICS */

		lib.numfiles = stg2int (&rec[404]);	/* Number of approved files */
		lib.numbytes = stg2int (&rec[408]);	/* Number of approved bytes */
		lib.numunapp = stg2int (&rec[412]);	/* Number of unapproved files */
		lib.bytesunapp = stg2int (&rec[416]);	/* Number of unapproved bytes */

		/* FLAGS */
		{
			int     flags = stg2short (&rec[428]);
			int     newflags = 0;

			if (flags & 0x100)
				newflags |= LBF_READONLY;	/* Read-only LIB */
			if (flags & 0x200)
				newflags |= LBF_NOINDEX;	/* Don't make indices */
			if (flags & 0x400)
				newflags |= LBF_DNLAUD;	/* Audit downloads */
			if (flags & 0x800)
				newflags |= LBF_UPLAUD;	/* Audit uploads */
			if ((flags & 0x1000) == 0)
				newflags |= LBF_LOCKUPL;	/* Password on uploads */
			if ((flags & 0x2000) == 0)
				newflags |= LBF_LOCKDNL;	/* Passwd on downloads */
			if (flags & 0x8000)
				newflags |= LBF_OSDIR;	/* OS LIB */
			lib.flags = newflags;
		}

		{
			struct libidx tmplib;

			if (libread (lib.keyname, library.libnum, &tmplib) ==
			    1) {
				printf
				    ("Warning: library %s already exists. Will install to it anyway.\n",
				     lib.fullname);
			} else
				mklib (&lib, 1, 0);
		}

		/* MAKE THE LIB BANNER */
		mkreadme (rec, &rec[70]);

		/* DONE! */
		num++;
		do
			c = fgetc (fp);
		while (c == '\n' || c == '\r' || c == 26);
		ungetc (c, fp);
	}
	printf ("Created %d libraries.\n", num);
}


/* End of File */
