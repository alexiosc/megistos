/*****************************************************************************\
 **                                                                         **
 **  FILE:     opdescr.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Edit file descriptions.                                      **
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
#include <megistos/files.h>
#include <megistos/mbk/mbk_files.h>


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


void
op_descr ()
{
	char   *spec;
	int     numfiles;
	struct filerec *fr;
	struct fileidx f;
	int     i;

	if (library.flags & LBF_OSDIR) {
		prompt (ODESOS);
		cnc_end ();
		return;
	}

	if ((spec = getfilenames (ODESASK)) == NULL)
		return;
	numfiles = expandspec (spec, 1);
	if (numfiles == 0) {
		prompt (ODESERR);
		cnc_end ();
		return;
	}

	fr = firstfile ();
	i = 1;
	while (fr) {
		if (!fileread (library.libnum, fr->fname, 1, &f))
			if (!fileread (library.libnum, fr->fname, 0, &f))
				continue;

		prompt (ODESFIL, f.fname, i, numfiles, f.summary);
		cnc_end ();
		inp_get (sizeof (f.summary) - 1);
		inp_raw ();
		if (strlen (inp_buffer)) {
			if (inp_isX (inp_buffer))
				break;

			bzero (f.summary, sizeof (f.summary));
			strncpy (f.summary, inp_buffer, sizeof (f.summary));
			fileupdate (&f);
		}

		i++;
		fr = nextfile ();
	}

	reset_filearray ();
}


static void
editdescr (struct fileidx *f)
{
	int     fd;
	char    fname[256];
	struct stat st;

	sprintf (fname, TMPDIR "/des-%05d", getpid ());

	if ((fd = open (fname, O_WRONLY | O_CREAT, 0600)) < 0) {
		error_fatalsys ("Unable to open() %s for writing.", fname);
	}
	write (fd, f->description, strlen (f->description));
	close (fd);

	if (editor (fname, deslen) || stat (fname, &st))
		return;

	stat (fname, &st);
	bzero (f->description, sizeof (f->description));
	if ((fd = open (fname, O_RDONLY)) < 0) {
		error_fatalsys ("Unable to open() %s for reading.", fname);
	}
	read (fd, f->description, min (st.st_size, sizeof (f->description)));
	f->descrlen = strlen (f->description) + 1;
	close (fd);
	unlink (fname);
	fileupdate (f);
	return;
}


void
op_long ()
{
	char   *spec;
	int     numfiles;
	struct filerec *fr;
	struct fileidx f;
	int     i;

	if (library.flags & LBF_OSDIR) {
		prompt (OLONOS);
		cnc_end ();
		return;
	}

	if ((spec = getfilenames (OLONASK)) == NULL)
		return;
	numfiles = expandspec (spec, 1);
	if (numfiles == 0) {
		prompt (OLONERR);
		cnc_end ();
		return;
	}

	fr = firstfile ();
	i = 1;
	while (fr) {
		if (!fileread (library.libnum, fr->fname, 1, &f))
			if (!fileread (library.libnum, fr->fname, 0, &f))
				continue;

		for (;;) {
			int     yes, res;

			prompt (OLONINF, i, numfiles);
			fileinfo (&library, &f);
			inp_setflags (INF_HELP);
			res = get_bool (&yes, OLONCONT, 0, OLONCND, 0);
			inp_clearflags (INF_HELP);
			if (res < 0)
				continue;
			if (res == 0)
				goto done;
			if (yes)
				editdescr (&f);
			break;
		}

		i++;
		fr = nextfile ();
	}

      done:
	reset_filearray ();
}


/* End of File */
