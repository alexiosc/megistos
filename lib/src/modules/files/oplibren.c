/*****************************************************************************\
 **                                                                         **
 **  FILE:     oplibren.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Rename a library.                                            **
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
 * Revision 1.5  2003/12/27 08:59:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:11  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/07/18 21:27:24  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_FCNTL_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "files.h"
#include "mbk_files.h"


int
listpeerlibs ()
{
	struct libidx l;
	int     p;
	int     res;
	char    gt[20];

	prompt (LIBLSTH);

	if (!libreadnum (library.parent, &l)) {
		error_fatal ("Unable to get parent lib, libnum=%d",
			     library.parent);
	}
	p = l.parent;


	gt[0] = 0;

	do {
		res = libgetchild (library.parent, gt, &l);
		if (res) {
			if (getlibaccess (&l, ACC_VISIBLE))
				prompt (LIBLSTL, leafname (l.fullname),
					l.numfiles, l.numbytes >> 10, l.descr);
		}
		if (fmt_lastresult == PAUSE_QUIT)
			break;
		strcpy (gt, l.keyname);
	} while (res);

	prompt (LIBLSTF);

	return fmt_lastresult != PAUSE_QUIT;
}


static int
getnewlibname (char *s)
{
	char   *i, c;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				listsublibs ();
				cnc_end ();
				continue;
			}
			i = cnc_word ();
		} else {
			prompt (OLRNASK);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 0;
			}
			if (sameas (margv[0], "?")) {
				listpeerlibs ();
				cnc_end ();
				continue;
			}
		}
		if (strlen (i) > sizeof (library.keyname) - 1) {
			prompt (OCRE2LN, sizeof (library.keyname) - 1);
		} else if (strspn (i, FNAMECHARS) != strlen (i)) {
			prompt (OCRECHR);
		} else
			break;
	}
	strcpy (s, i);
	return 1;
}


void
op_libren ()
{
	char    s[256];

	print ("not implemented\n");
	return;

	/* Refuse to rename the main library */

	if (!nesting (library.fullname)) {
		prompt (OLRNNMN);
		cnc_end ();
		return;
	}

	for (;;) {
		if (!getnewlibname (s))
			return;

		if (libexists (s, library.parent)) {
			prompt (OLRNERR);
			cnc_end ();
			continue;
		} else
			break;
	}

	/* Rename the library */

}


/* End of File */
