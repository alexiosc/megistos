/*****************************************************************************\
 **                                                                         **
 **  FILE:     opmove.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Move files from one library to another.                      **
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
 * $Id: opmove.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: opmove.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/02/29 18:05:28  alexios
 * Silenced a gcc-3 warning.
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
    "$Id: opmove.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";


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


static int
gettargetlibname (struct libidx *l)
{
	char   *i, c;
	struct libidx lib;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				libtree ();
				cnc_end ();
				continue;
			}
			i = cnc_word ();
		} else {
			prompt (OMOVTRG);
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
				libtree ();
				cnc_end ();
				continue;
			}
		}
		if (sameas (i, "..")) {
			if (nesting (library.fullname) == 0) {
				prompt (SELNPR);
				cnc_end ();
				continue;
			} else
				return 2;
		} else if (sameas (i, "/") || sameas (i, "\\")) {
			if (!libread (libmain, 0, &lib)) {
				error_fatal ("Unable to find main library!");
			} else
				goto enter;
		} else {
			if (!nesting (i)) {
				if (!libread (i, library.libnum, &lib) ||
				    !getlibaccess (&lib, ACC_VISIBLE)) {
					prompt (OMOVTR2);
					cnc_end ();
					continue;
				} else
					goto enter;
			} else {
				char    s[256];
				char   *cp;

				strcpy (s, i);
				if (!libread (libmain, 0, &lib)) {
					error_fatal
					    ("Unable to find main library!");
				}
				cp = strtok (i, "/\\");
				while (cp) {
					if (!strlen (cp))
						continue;
					if (!libread (cp, lib.libnum, &lib) ||
					    !getlibaccess (&lib,
							   ACC_VISIBLE)) {
						prompt (OMOVTR2);
						cnc_end ();
						goto outerloop;
					}
					cp = strtok (NULL, "/\\");
				}
			}
		}
		break;
	outerloop: ;
	}

      enter:
	memcpy (l, &lib, sizeof (lib));

	return 1;
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
		prompt (OMOVOKD, f->fname);
	} else
		prompt (OMOVOK, f->fname);
}


static void
copyfilekeywords (struct libidx *l, struct fileidx *f, struct fileidx *ft)
{
	struct filekey k;
	int     morekeys, keys = 0;
	char    keystg[8192];

	keystg[0] = 0;
	morekeys = keyfilefirst (l->libnum, f->fname, f->approved, &k);
	while (morekeys) {
		char    tmp[32];

		keys++;
		sprintf (tmp, "%s ", k.keyword);
		strcat (keystg, tmp);
		morekeys = keyfilenext (l->libnum, f->fname, f->approved, &k);
	}
	if (keys) {
		addkeywords (keystg, ft->approved, ft);
	}
}


static
    int
domove (struct fileidx *f, int mode, struct libidx *target)
{
	char    fname[512], fname2[512];
	struct stat st;
	struct fileidx tf;

	sprintf (fname, "%s/%s", library.dir, f->fname);
	stat (fname, &st);

	/* Check if the target library has enough space */

	if (target->numfiles > target->filelimit) {
		prompt (OMOVFAIL);
		cnc_end ();
		return 0;
	}
	if (target->numbytes + st.st_size >= (target->libsizelimit << 20)) {
		prompt (OMOVFAIL);
		cnc_end ();
		return 0;
	}


	/* Check if the file already exists in the target lib */

	if (fileexists (target->libnum, f->fname, 0) ||
	    fileexists (target->libnum, f->fname, 1)) {
		prompt (OMOVEXT, f->fname);
		return 1;
	}


	/* Physically Copy the file (try a hard link first) */

	sprintf (fname2, "%s/%s", target->dir, f->fname);
	if (link (fname, fname2))
		fcopy (fname, fname2);


	/* Add the database entry for the target file */

	memcpy (&tf, f, sizeof (tf));
	tf.flibnum = target->libnum;
	filecreate (&tf);
	libinstfile (target, &tf, st.st_size, LIF_ADD);

	/* Add keywords */

	copyfilekeywords (&library, f, &tf);


	/* Delete the old file */

	dodelete (f, mode);
	libinstfile (&library, f, st.st_size, LIF_DEL);

	if (mode) {
		unlink (fname);
		prompt (OMOVOKD, f->fname);
	} else
		prompt (OMOVOK, f->fname);

	return 1;
}


void
op_move ()
{
	char   *spec;
	int     numfiles;
	struct filerec *fr;
	struct fileidx f;
	int     i, all = 0, mode = 0;
	char    c;
	struct libidx target;

	if ((spec = getfilenames (OMOVASK)) == NULL)
		return;
	numfiles = expandspec (spec, 1);
	if (numfiles == 0) {
		prompt (OMOVERR);
		cnc_end ();
		return;
	} else if (numfiles > 1) {
		prompt (OMOVNUM, numfiles);
	}

	for (;;) {
		switch (gettargetlibname (&target)) {
		case 0:
			return;
		case 2:
			if (!libreadnum (library.parent, &target))
				return;
		}

		if (target.libnum == library.libnum) {
			cnc_end ();
			prompt (OMOVTR1);
			continue;
		}

		if (target.flags & LBF_READONLY) {
			prompt (OMOVTR4);
			cnc_end ();
			continue;
		}

		break;
	}

	cnc_end ();
	if (!mode)
		if (!get_bool (&mode, OMOVMOD, OMOVMOD, 0, 0))
			return;

	if (library.flags & LBF_OSDIR) {
		prompt (OMOVOS);
		mode = 1;
	}

	fr = firstfile ();
	i = 1;
	while (fr) {
		if (!fileread (library.libnum, fr->fname, 1, &f))
			if (!fileread (library.libnum, fr->fname, 0, &f))
				continue;

		for (;;) {
			int     res;

			if (!all) {
				prompt (OMOVINF, i, numfiles);
				fileinfo (&library, &f);

				inp_setflags (INF_HELP);
				res =
				    get_menu (&c, 0, 0, OMOVMNU, 0, "YNA", 0,
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

			if (c == 'Y') {
				res = domove (&f, mode, &target);
				if (!res)
					goto done;
			}
			break;
		}

		i++;
		fr = nextfile ();
	}

      done:
	reset_filearray ();
}


/* End of File */
