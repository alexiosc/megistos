/*****************************************************************************\
 **                                                                         **
 **  FILE:     dblib.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  Typhoon database stuff                                       **
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
 * Revision 1.5  2003/12/27 08:59:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Added libdelete(). Fixed bug in libgetchild().
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
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
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include <libtyphoon/typhoon.h>
#include <megistos/bbs.h>
#include "files.h"


struct libidx library;
static int id_dblib;


void
dblibopen ()
{
	d_dbfpath (mkfname (FILELIBDBDIR));
	d_dbdpath (mkfname (FILELIBDBDIR));
	if (d_open ("dblib", "s") != S_OKAY) {
		error_fatal
		    ("Cannot open file library database (db_status %d).",
		     db_status);
	}
	d_dbget (&id_dblib);
}


int
libgetfirst (struct libidx *lib)
{
	d_dbset (id_dblib);
	if (d_keyfrst (LIBNUM) == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY || d_recread (lib) != S_OKAY) {
		error_fatal ("Typhoon call failed with db_status=%d",
			     db_status);
	}
	return 1;
}


int
libgetnext (struct libidx *lib)
{
	d_dbset (id_dblib);

	if (d_keyfind (LIBNUM, &(lib->libnum)) == S_NOTFOUND)
		return 0;
	if (db_status != S_OKAY) {
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);
	}

	if (d_keynext (LIBNUM) == S_NOTFOUND)
		return 0;
	if (db_status != S_OKAY) {
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);
	}

	if (d_recread (lib) != S_OKAY) {
		error_fatal ("Typhoon call 3 failed with db_status=%d",
			     db_status);
	}
	return 1;
}


int
libexists (char *s, int parent)
{
	struct namep n;

	d_dbset (id_dblib);
	n.parent = parent;
	strcpy (n.keyname, s);
	lowerc (n.keyname);
	d_keyfind (NAMEP, &n);

	if (db_status == S_OKAY) {
		struct libidx l;

		if (d_recread (&l) == S_OKAY) {
			strcpy (s, leafname (l.fullname));
		}
		return 1;
	} else if (db_status == S_NOTFOUND)
		return 0;
	error_fatal ("Typhoon call failed with db_status=%d", db_status);
	return -1;		/* Gets rid of warning */
}


int
libdelete (int libnum)
{
	if (libexistsnum (libnum)) {
		if (d_delete () != S_OKAY) {
			error_fatal ("Typhoon call failed with db_status=%d",
				     db_status);
		}
		return 1;
	}
	return 0;
}


int
libexistsnum (int num)
{
	d_dbset (id_dblib);
	d_keyfind (LIBNUM, &num);
	if (db_status == S_OKAY)
		return 1;
	else if (db_status == S_NOTFOUND)
		return 0;
	error_fatal ("Typhoon call failed with db_status=%d", db_status);
	return -1;		/* Gets rid of warning */
}


int
libread (char *s, int parent, struct libidx *library)
{
	d_dbset (id_dblib);
	if (!libexists (s, parent))
		return 0;
	d_recread (library);
	if (db_status == S_OKAY)
		return 1;
	error_fatal ("Typhoon call failed with db_status=%d", db_status);
	return -1;		/* Gets rid of warning */
}


int
libreadnum (int num, struct libidx *library)
{
	d_dbset (id_dblib);
	if (!libexistsnum (num))
		return 0;
	d_recread (library);
	if (db_status == S_OKAY)
		return 1;
	error_fatal ("Typhoon call failed with db_status=%d", db_status);
	return -1;		/* Gets rid of warning */
}


void
libcreate (struct libidx *lib)
{
	d_dbset (id_dblib);
	if (d_fillnew (LIBIDX, lib) == S_OKAY)
		return;
	else
		error_fatal ("Typhoon call failed with db_status=%d",
			     db_status);
}


int
libmaxnum ()
{
	int     retval = 0;

	d_dbset (id_dblib);
	if (d_keylast (LIBNUM) == S_OKAY) {
		d_keyread (&retval);
		if (db_status != S_OKAY) {
			error_fatal
			    ("Unable to read maximum LIBNUM key (db_status=%d)",
			     db_status);
		}
	}
	return retval;
}


int
libgetchild (int parent, char *_namegt, struct libidx *l)
{
	char    namegt[512];
	struct namep n;

	strcpy (namegt, _namegt);

	/*  print("---@@ libgetchild(%d, \"%s\", l);\n",parent,namegt); */
	bzero (&n, sizeof (n));
	d_dbset (id_dblib);
	n.parent = parent;
	strcpy (n.keyname, namegt);

	d_keyfind (NAMEP, &n);
	if (db_status != S_OKAY && db_status != S_NOTFOUND)
		return 0;
	if (d_keynext (NAMEP) != S_OKAY)
		return 0;
	bzero (l, sizeof (struct libidx));
	if (d_recread (l) != S_OKAY)
		return 0;
	return (l->parent == parent) && (strcmp (l->keyname, namegt) > 0);
}


int
libupdate (struct libidx *lib)
{
	d_dbset (id_dblib);
	if (!libexistsnum (lib->libnum))
		return 0;
	d_recwrite (lib);
	return 1;
}


void
libinstfile (struct libidx *lib, struct fileidx *f, int bytes, int add)
{
	char    lock[256];

	sprintf (lock, LIBUPDLOCK, lib->libnum);
	if (lock_wait (lock, 10) > 0) {
		error_fatal ("Timeout waiting for library \"%s\" update lock.",
			     lib->keyname);
	}

	lock_place (lock, "libinstfile");

	if (!libreadnum (lib->libnum, lib)) {
		error_fatal ("Library %s disappeared despite lock!",
			     lib->keyname);
	}

	if (f->approved) {
		if (add) {
			lib->numfiles++;
			lib->numbytes += bytes;
			lib->uploadsperday[0]++;
			lib->bytesperday[0] += bytes;
		} else {
			lib->numfiles--;
			lib->numbytes -= bytes;
			lib->uploadsperday[0]--;
			lib->bytesperday[0] -= bytes;
		}
	} else {
		if (add) {
			lib->numunapp++;
			lib->bytesunapp += bytes;
		} else {
			lib->numunapp--;
			lib->bytesunapp -= bytes;
		}
	}

	/* Fix some awkward situations -- Files will be recounted during
	   cleanup, anyway */

	lib->numfiles = max (0, lib->numfiles);
	lib->numbytes = max (0, lib->numbytes);
	lib->numunapp = max (0, lib->numunapp);
	lib->bytesunapp = max (0, lib->bytesunapp);

	/* Now write the library and release the lock */

	if (!libupdate (lib)) {
		error_fatal ("Library %s disappeared despite lock!",
			     lib->keyname);
	}

	lock_rm (lock);
}


/* End of File */
