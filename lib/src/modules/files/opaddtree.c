/*****************************************************************************\
 **                                                                         **
 **  FILE:     opaddtree.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  The CREATE operation                                         **
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
 * Revision 1.4  2003/12/24 20:12:12  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  2000/01/06 10:36:59  alexios
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
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "files.h"
#include "mbk_files.h"


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
			prompt (OADTASK);
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


static int
getdir (char *s)
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
			prompt (OADTDIR);
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
		}
		if (i[0] != '/') {
			prompt (OADTDR);
			cnc_end ();
			continue;
		} else
			break;
	}
	strcpy (s, i);
	return 1;
}


char   *dir;

static int
dirselect (const struct dirent *d)
{
	char    fname[1024];
	struct stat st;

	sprintf (fname, "%s/%s", dir, d->d_name);
	if (!(strcmp (d->d_name, ".") && strcmp (d->d_name, "..")))
		return 0;
	if (stat (fname, &st))
		return 0;
	return S_ISDIR (st.st_mode);
}



static void
addtree (struct libidx *lib)
{
	int     i, j;
	struct dirent **d = NULL;

	dir = lib->dir;

	j = scandir (lib->dir, &d, dirselect, alphasort);
	if (j <= 0 || d == NULL)
		return;

	for (i = 0; i < j; i++) {
		struct libidx tmp;

		bzero (&tmp, sizeof (tmp));
		strcpy (tmp.keyname, d[i]->d_name);
		free (d[i]);

		sprintf (tmp.fullname, "%s/%s", lib->fullname, tmp.keyname);
		sprintf (tmp.dir, "%s/%s", lib->dir, tmp.keyname);
		tmp.parent = lib->libnum;
		lcase (tmp.keyname);


		prompt (OADTCRE, tmp.fullname);

		mklib (&tmp, 0, LBF_OSDIR | LBF_NOINDEX);
		addtree (&tmp);
	}

	free (d);
}


void
op_addtree ()
{
	char    s[1024], tmp[1024];
	struct libidx lib;

	if (nesting (library.fullname) > maxnest) {
		prompt (OCRENST, maxnest);
		return;
	}

	for (;;) {
		if (!getnewlibname (s))
			return;

		if (libexists (s, library.libnum)) {
			prompt (OCREEXS, s);
			cnc_end ();
			continue;
		} else
			break;
	}

	memcpy (&lib, &library, sizeof (lib));

	strcpy (lib.keyname, s);
	lowerc (lib.keyname);
	sprintf (lib.fullname, "%s/%s", library.fullname, s);
	sprintf (lib.dir, "%s/%s", library.dir, s);
	lib.descr[0] = 0;
	lib.parent = library.libnum;
	lib.numfiles = lib.numbytes = lib.numunapp = lib.bytesunapp = 0;
	bzero (lib.uploadsperday, sizeof (lib.uploadsperday));
	bzero (lib.bytesperday, sizeof (lib.bytesperday));
	strcpy (tmp, s);
	if (findclub (tmp))
		strcpy (lib.club, tmp);

	for (;;) {
		struct stat st;

		if (!getdir (s))
			return;
		if (stat (s, &st)) {
			prompt (OADTDR2, s);
			cnc_end ();
		} else if (!S_ISDIR (st.st_mode)) {
			prompt (OADTDR2);
			cnc_end ();
		}
		break;
	}
	strcpy (lib.dir, s);

	mklib (&lib, 0, LBF_OSDIR | LBF_NOINDEX);
	prompt (OCREOK, lib.fullname);
	enterlib (lib.libnum, 0);

	addtree (&lib);

	enterlib (lib.libnum, 0);
}


/* End of File */
