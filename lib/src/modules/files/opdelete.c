/*****************************************************************************\
 **                                                                         **
 **  FILE:     opdelete.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  The DELETE operation                                         **
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
 * Revision 1.4  2003/12/24 20:12:12  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1999/07/18 21:29:45  alexios
 * Major changes.
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
#include <megistos/files.h>
#include <megistos/mbk/mbk_files.h>


static int
getdellibname (char *s)
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
			prompt (OLDLASK);
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
				listsublibs ();
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


static void
delkeywords (struct libidx *l)
{
	struct fileidx f;
	int     approved;

	for (approved = 0; approved <= 1; approved++) {
		if (filegetfirst (l->libnum, &f, approved)) {
			do {
				delfilekeywords (l, &f);

			} while (filegetnext (l->libnum, &f));
		}
	}
}



static void
delfiles (struct libidx *l)
{
	struct fileidx f;
	int     approved;

	for (approved = 0; approved <= 1; approved++) {
		if (filegetfirst (l->libnum, &f, approved)) {
			do {
				char    fname[512];
				struct stat st;

				bzero (&st, sizeof (st));
				sprintf (fname, "%s/%s", l->dir, f.fname);
				stat (fname, &st);
				libinstfile (l, &f, st.st_size, LIF_DEL);
			} while (filegetnext (l->libnum, &f));
		}
	}
}



void
op_delete ()
{
	char    s[20];
	struct libidx lib, tmp;

	for (;;) {
		cnc_end ();
		if (!getdellibname (s))
			return;

		if (!libread (s, library.libnum, &lib)) {
			prompt (OLDLNEX, s);
			cnc_end ();
			continue;
		} else
			break;
	}

	/* Refuse to delete the main library */

	if (sameas (lib.fullname, libmain)) {
		prompt (OLDLMAI, libmain);
	}


	/* Refuse to delete the library if it has sublibraries */

	if (libgetchild (lib.libnum, "", &tmp)) {
		prompt (OLDLSUB);
		cnc_end ();
		return;
	}


	/* First delete keywords */

	prompt (OLDLKEY);
	delkeywords (&lib);

	/* Then delete all the files */

	prompt (OLDLFIL);
	delfiles (&lib);

	/* And, finally, delete the library */

	libdelete (lib.libnum);
}


/* End of File */
