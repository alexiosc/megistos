/*****************************************************************************\
 **                                                                         **
 **  FILE:    filearray.c                                                   **
 **  AUTHORS: Alexios                                                       **
 **  PURPOSE: Download files, expand wildcards and mark files for dnload.   **
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
 * Revision 1.2  2000/01/06 10:37:25  alexios
 * Added support for locating files and expanding wildcards
 * within OS-only libraries.
 *
 * Revision 1.1  1999/07/18 21:29:45  alexios
 * Major changes for completeness and correctness.
 *
 * Revision 1.0  1998/12/27 15:39:26  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#define WANT_REGEX_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/files.h>
#include <megistos/mbk_files.h>


#define DELTA 10


static int numfiles = 0;
static int currentfile = 0;
static int arraysize = 0;
static int totalsize = 0;
static int totalcharge = 0;
static int totaltimesec = 0;

static struct filerec *files = NULL;


int
gettotalcharge ()
{
	return totalcharge;
}


void
reset_filearray ()
{
	free (files);
	files = NULL;
	numfiles = arraysize = 0;
}


struct filerec *
firstfile ()
{
	if (numfiles == 0)
		return NULL;	/* Should never happen */
	currentfile = 1;
	return &(files[0]);
}


struct filerec *
nextfile ()
{
	if (currentfile >= numfiles)
		return NULL;
	return &(files[currentfile++]);
}


static void
grow_array ()
{
	if (files == NULL || numfiles >= arraysize) {
		struct filerec *tmp;

		arraysize += DELTA;
		tmp = alcmem (arraysize * sizeof (struct filerec));
		bzero (tmp, sizeof (tmp));
		if (files != NULL) {
			memcpy (tmp, files,
				sizeof (struct filerec) * numfiles);
			free (files);
		}
		files = tmp;
	}
}


static void
add_file (char *fname, char *summary, int size)
{
	grow_array ();
	files[numfiles].size = size;
	strcpy (files[numfiles].summary, summary);
	strcpy (files[numfiles++].fname, fname);
}


static int
os_shdnlinfo (char *f, char *summary, int quiet)
{
	char    fname[1024];
	struct stat st;
	int     t, c;

	sprintf (fname, "%s/%s", library.dir, f);
	bzero (&st, sizeof (st));
	stat (fname, &st);

	t = calcxfertime (st.st_size, 1);
	c = calccharge (st.st_size, &library);

	if (fmt_lastresult != PAUSE_QUIT)
		if (!quiet)
			prompt (DNLSIL, f, st.st_size, t / 60, t % 60, c,
				summary);
	return st.st_size;
}


static int
shdnlinfo (struct fileidx *f, int quiet)
{
	return os_shdnlinfo (f->fname, f->summary, quiet);
}


static int
idx_expandspec (char *s, int quiet)
{
	struct fileidx f;
	int     grovel = islibop (&library);
	int     size;

	reset_filearray ();	/* Fresh Horse! */

	totalsize = totalcharge = totaltimesec = 0;

	if (strcspn (s, "*?[]") == strlen (s)) {
		/* No wildcards, downloading single file */

		if (!fileread (library.libnum, s, 1, &f)) {
			if (grovel) {
				if (!fileread (library.libnum, s, 0, &f)) {
					if (!quiet)
						prompt (DNLNF, s);
					return 0;
				}
			} else
				return 0;
		}
		add_file (f.fname, f.summary, size = fileinfo (&library, &f));
		totalsize += size;
		totalcharge += calccharge (size, &library);
		totaltimesec += calcxfertime (size, 1);
	} else {
		int     morefiles;
		int     approved;
		int     first = 1;

		if (!quiet)
			prompt (DNLWAIT);
		if (!mkwildcard (s))
			return 0;
		for (approved = 1; approved >= (grovel ? 0 : 1); approved--) {
			morefiles =
			    filegetfirst (library.libnum, &f, approved);
			while (morefiles) {
				char    tmp[24];
				int     len = strlen (f.fname);

				strcpy (tmp, f.fname);
				lcase (tmp);
				if (f.approved != approved ||
				    f.flibnum != library.libnum)
					break;
				if ((len =
				     re_search (regexp, tmp, len, 0, len,
						NULL)) >= 0) {
					if (first) {
						if (!quiet)
							prompt (DNLSIH);
						first = 0;
					}
					add_file (f.fname, f.summary, size =
						  shdnlinfo (&f, quiet));
					totalsize += size;
					totaltimesec += calcxfertime (size, 1);
				}
				morefiles = filegetnext (library.libnum, &f);
			}
		}

		if (!first) {
			int     t = calcxfertime (totalsize, 1);

			totalcharge = calccharge (totalsize, &library);
			totalcharge += (numfiles - 1) * library.dnlcharge;
			if (fmt_lastresult != PAUSE_QUIT)
				if (!quiet)
					prompt (DNLSIF, numfiles, totalsize,
						t / 60, t % 60, totalcharge);
		} else {
			if (!quiet)
				prompt (DNLNFM, s);
			return 0;
		}
	}
	return numfiles;
}


static char *match_to;


static int
insensitive_match (const struct dirent *d)
{
	return sameas (match_to, (char *) d->d_name);
}


static int
os_expandspec (char *s, int quiet)
{
	int     size;

	reset_filearray ();	/* Fresh Horse! */

	totalsize = totalcharge = totaltimesec = 0;

	if (strcspn (s, "*?[]") == strlen (s)) {
		int     i, j;
		struct dirent **d = NULL;


		/* No wildcards, downloading single file */

		match_to = s;
		if ((j =
		     scandir (library.dir, &d, insensitive_match,
			      alphasort)) == 0) {
			if (d)
				free (d);
			if (!quiet)
				prompt (DNLNF, s);
			return 0;
		}

		/* Add any file(s) to the file array (we're not assuming that, just because
		   there are no wildcards, only one file matches. Sure, it doesn't make
		   sense, but better safe than sorry -- and it doesn't waste any real
		   computing power anyway). */

		for (i = 0; i < j; i++) {
			char    fname[1024];
			struct stat st;

			sprintf (fname, "%s/%s", library.dir, d[i]->d_name);
			if (stat (fname, &st) == 0) {
				add_file (d[i]->d_name, osfdesc, st.st_size);
				totalsize += st.st_size;
				totalcharge +=
				    calccharge (st.st_size, &library);
				totaltimesec += calcxfertime (st.st_size, 1);
			}
			free (d[i]);
		}
		free (d);
	} else {
		DIR    *dp;
		struct dirent *d;
		int     first = 1;

		/* Open the library directory */

		if ((dp = opendir (library.dir)) == NULL) {
			error_fatalsys
			    ("Unable to open library %s (directory: %s)",
			     library.fullname, library.dir);
		}

		if (!quiet)
			prompt (DNLWAIT);
		if (!mkwildcard (s))
			return 0;

		while ((d = readdir (dp)) != NULL) {
			char    tmp[24];
			int     len = strlen (d->d_name);

			strcpy (tmp, d->d_name);
			lcase (tmp);

			if ((len =
			     re_search (regexp, tmp, len, 0, len,
					NULL)) >= 0) {
				if (first) {
					if (!quiet)
						prompt (DNLSIH);
					first = 0;
				}

				size =
				    os_shdnlinfo (d->d_name, osfdesc, quiet);
				add_file (d->d_name, osfdesc, size);
				totalsize += size;
				totaltimesec += calcxfertime (size, 1);
			}
		}

		closedir (dp);

		if (!first) {
			int     t = calcxfertime (totalsize, 1);

			totalcharge = calccharge (totalsize, &library);
			totalcharge += (numfiles - 1) * library.dnlcharge;
			if (fmt_lastresult != PAUSE_QUIT)
				if (!quiet)
					prompt (DNLSIF, numfiles, totalsize,
						t / 60, t % 60, totalcharge);
		} else {
			if (!quiet)
				prompt (DNLNFM, s);
			return 0;
		}
	}
	return 1;
}


int
expandspec (char *s, int quiet)
{
	if (library.flags & LBF_OSDIR)
		return os_expandspec (s, quiet);
	return idx_expandspec (s, quiet);
}


/* End of File */
