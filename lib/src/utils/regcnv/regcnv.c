/*****************************************************************************\
 **                                                                         **
 **  FILE:     regcnv.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 user registry Megistos format.             **
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
 * Revision 1.2  1998/12/27 16:40:53  alexios
 * Added autoconf support.
 *
 * Revision 1.1  1998/07/24 10:33:08  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.0  1998/07/16 23:14:59  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";



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



void    convert (char *, char *, int);



static int bigendian = 0;


static void
print_endian_warning ()
{
	short int eat = 0xbeef;	/* moo */
	unsigned char *tmp2 = (char *) &eat;

	if (*tmp2 == 0xbe) {
		printf
		    ("Argh, this is a big endian machine! This won't work properly.\n");
		bigendian = 1;
		exit (1);
	}
}


static void
syntax ()
{
	fprintf (stderr,
		 "regcnv: convert MajorBBS 5.xx user registry database to Megistos format.\n\n"
		 "Syntax: regcnv options.\n\nOptions:\n"
		 "  -u dir   or  --regdir dir:   put registry files under the supplied\n"
		 "        directory. By default, entries are made in the current directory.\n\n"
		 "  -m dir   or  --majordir dir: read Major databases from specified directory.\n"
		 "        Defaults to the current directory.\n\n"
		 "  -t temp or  --temp templ:    set registry template number (0-2, default: 0)\n\n");
	exit (1);
}


static struct option long_options[] = {
	{"regdir", 1, 0, 'u'},
	{"majordir", 1, 0, 'm'},
	{"templ", 1, 0, 't'},
	{0, 0, 0, 0}
};


static char *arg_usrdir = ".";
static char *arg_majordir = ".";
static int arg_templ = 0;


static void
parseopts (int argc, char **argv)
{
	int     c;

	while (1) {
		int     option_index = 0;

		c = getopt_long (argc, argv, "u:m:c:fU:", long_options,
				 &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 'u':
			arg_usrdir = strdup (optarg);
			break;
		case 'm':
			arg_majordir = strdup (optarg);
			break;
		case 't':
			arg_templ = atoi (optarg);
			if (arg_templ < 0 || arg_templ > 2) {
				fprintf (stderr,
					 "Template number should be between 0 and 2.\n");
			} else
				break;
		default:
			syntax ();
		}
	}
}


int
main (int argc, char **argv)
{
	mod_setprogname (argv[0]);
	parseopts (argc, argv);
	print_endian_warning ();

	convert (arg_usrdir, arg_majordir, arg_templ);

	printf ("Syncing disks...\n");
	fflush (stdout);
	system ("sync");

	printf ("\nREMEMBER:\n\n"
		"  * It's entirely your responsibility to physically copy\n"
		"    the user registry files to %s.\n\n",
		mkfname (REGISTRYDIR));

	return 0;
}


/* End of File */
