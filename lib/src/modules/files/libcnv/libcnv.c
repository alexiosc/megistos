/*****************************************************************************\
 **                                                                         **
 **  FILE:     libcnv.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 library DATabases to Megistos format.      **
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
 * Revision 0.4  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Added a system() call to sync(8) the disks before exiting
 * from the converter.
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
#define WANT_GETOPT_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include <megistos/bbs.h>
#include <megistos/config.h>
#include <megistos/cnvutils.h>
#include <megistos/libcnv.h>
#include <megistos/files.h>


static void
print_endian_warning ()
{
	short int tmp1 = 0xbeef;
	unsigned char *tmp2 = (char *) &tmp1;

	if (*tmp2 == 0xbe)
		printf ("This is a big endian machine, will swab() ints.\n");
}


static void
syntax ()
{
	fprintf (stderr,
		 "libcnv: convert MajorBBS 5.xx file library databases to Megistos format.\n\n"
		 "Syntax: libcnv options.\n\nOptions:\n"
		 "  -u lib  or  --under lib: put converted libraries under given\n"
		 "        library. The library will be created under Main, if necessary.\n"
		 "        Give its SHORT pathname. Defaults to Major.\n\n"
		 "  -b dir   or  --basedir dir: make library directories under the\n"
		 "        supplied directory. By default, new directories are made under\n"
		 "        the parent libary's directory (see -u).\n\n"
		 "  -m dir   or  --majordir dir: read Major databases from specified directory.\n"
		 "        Defaults to the current directory.\n\n"
		 "  -k key   or  --key key: initially lock all libraries with the given key.\n"
		 "        Key 129 (account \"Sysop\" only) is the default key.\n\n");
	exit (1);
}


static struct option long_options[] = {
	{"under", 1, 0, 'u'},
	{"basedir", 1, 0, 'b'},
	{"majordir", 1, 0, 'm'},
	{"key", 1, 0, 'k'},
	{0, 0, 0, 0}
};


static char *arg_under = "Major";
static char *arg_basedir = NULL;
static char *arg_majordir = ".";
static int arg_key = 129;


static void
parseopts (int argc, char **argv)
{
	int     c;

	while (1) {
		int     option_index = 0;

		c = getopt_long (argc, argv, "u:b:m:k:", long_options,
				 &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 'u':
			arg_under = strdup (optarg);
			break;
		case 'b':
			arg_basedir = strdup (optarg);
			break;
		case 'm':
			arg_majordir = strdup (optarg);
			break;
		case 'k':
			arg_key = atoi (optarg);
			if (arg_key < 0 || arg_key > 129) {
				fprintf (stderr,
					 "An access key (-k or --key) is a number between 0 and 129 inclusive.\n\n");
				syntax ();
			}
			break;
		default:
			syntax ();
		}
	}
}


int
cnvmain (int argc, char **argv)
{
	mod_setprogname (argv[0]);
	parseopts (argc, argv);
	print_endian_warning ();

	msg = msg_open ("files");
	readsettings ();

	dblibopen ();
	dbkeyopen ();
	dbfileopen ();

	libsig (arg_under, arg_basedir, arg_majordir, arg_key);
	libfil (arg_majordir);
	libkey (arg_majordir);

	printf ("Syncing disks...\n");
	system ("sync");

	printf
	    ("\nREMEMBER: it's entirely your responsibility to physically copy\n"
	     "the files to their proper directories.\n\n");

	return 0;
}


/* End of File */
