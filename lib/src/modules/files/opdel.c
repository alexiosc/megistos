/*****************************************************************************\
 **                                                                         **
 **  FILE:     opdel.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Delete/retire files.                                         **
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


static char *
getfilenames (int pr)
{
	static char fn[256];

	for (;;) {
		if (cnc_more ()) {
			strcpy (fn, cnc_word ());
		} else {
			prompt (pr);
			inp_get (sizeof (fn) - 1);
			strcpy (fn, inp_buffer);
		}

		if (inp_isX (fn))
			return NULL;
		else if (!strlen (fn)) {
			cnc_end ();
			continue;
		} else if (!strcmp (fn, "?")) {
			listapproved ();
			cnc_end ();
			continue;
		} else
			break;
	}

	return fn;
}


static
    void
dodelete (struct fileidx *f, int mode)
{
	char    fname[512];
	struct stat st;

	delfilekeywords (&library, f);
	filedelete (f);

	sprintf (fname, "%s/%s", library.dir, f->fname);
	stat (fname, &st);
	libinstfile (&library, f, st.st_size, LIF_DEL);

	if (mode) {
		unlink (fname);
		prompt (ODELOKD, f->fname);
	} else
		prompt (ODELOK, f->fname);
}


void
op_del ()
{
	char   *spec;
	int     numfiles;
	struct filerec *fr;
	struct fileidx f;
	int     i, mode = 0, all = 0;
	char    c;

	if (library.flags & LBF_OSDIR) {
		prompt (ODELOS);
		mode = 1;
	}

	if ((spec = getfilenames (ODELASK)) == NULL)
		return;
	numfiles = expandspec (spec, 1);
	if (numfiles == 0) {
		prompt (ODELERR);
		cnc_end ();
		return;
	} else if (numfiles > 0) {
		prompt (ODELNUM, numfiles);
	}

	cnc_end ();
	if (!mode)
		if (!get_bool (&mode, ODELMOD, ODELMOD, 0, 0))
			return;

	fr = firstfile ();
	i = 1;
	while (fr) {
		if (!fileread (library.libnum, fr->fname, 1, &f))
			if (!fileread (library.libnum, fr->fname, 0, &f))
				continue;

		for (;;) {
			int     res;

			if (!all) {
				prompt (ODELINF, i, numfiles);
				fileinfo (&library, &f);
				inp_setflags (INF_HELP);
				res =
				    get_menu (&c, 0, 0, ODELMNU, 0, "YNA", 0,
					      0);
				inp_clearflags (INF_HELP);
				if (res < 0)
					continue;
				if (res == 0)
					goto done;
				if (c == 'A') {
					all = 1;
					c = 'Y';
				}
			} else
				c = 'Y';

			if (c == 'Y')
				dodelete (&f, mode);
			break;
		}

		i++;
		fr = nextfile ();
	}

      done:
	reset_filearray ();
}


/* End of File */
