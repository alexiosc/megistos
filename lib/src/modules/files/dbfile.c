/*****************************************************************************\
 **                                                                         **
 **  FILE:     dbfile.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 1997, Version 0.1                                **
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
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 08:59:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:29:45  alexios
 * Minor paranoia checks/bug fixes.
 *
 * Revision 0.4  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Changed the interface a bit. Added some more paranoia checks.
 * Added a pair of functions filegetoldest() and
 * filegetnextoldest() to traverse files chronologically.
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


static int id_dbfile;


void
dbfileopen ()
{
	d_dbfpath (mkfname (FILELIBDBDIR));
	d_dbdpath (mkfname (FILELIBDBDIR));
	if (d_open ("dbfile", "s") != S_OKAY) {
		error_fatal ("Cannot open file index database (db_status %d).",
			     db_status);
	}
	d_dbget (&id_dbfile);
}


void
filecreate (struct fileidx *file)
{
	d_dbset (id_dbfile);
	if (d_fillnew (FILEIDX, file) == S_OKAY)
		return;
	else
		error_fatal ("Typhoon call failed with db_status=%d",
			     db_status);
}


void
filedelete (struct fileidx *file)
{
	if (fileexists (file->flibnum, file->fname, file->approved)) {
		if (d_delete () != S_OKAY) {
			error_fatal ("Typhoon call failed with db_status=%d",
				     db_status);
		}
	}
}


void
fileupdate (struct fileidx *file)
{
	if (!fileexists (file->flibnum, file->fname, file->approved)) {
		filecreate (file);
	} else {
		if (d_recwrite (file) != S_OKAY)
			error_fatal ("Typhoon call failed with db_status=%d",
				     db_status);
	}
}


int
fileexists (int libnum, char *fname, int approved)
{
	struct statlibfn key;

	d_dbset (id_dbfile);
	bzero (&key, sizeof (key));
	key.flibnum = libnum;
	strcpy (key.fname, fname);
	key.approved = approved;
	d_keyfind (STATLIBFN, &key);
	if (db_status == S_OKAY)
		return 1;
	else if (db_status != S_NOTFOUND) {
		error_fatal ("Typhoon call failed with db_status=%d",
			     db_status);
	}
	return 0;
}


int
fileread (int libnum, char *fname, int approved, struct fileidx *f)
{
	struct statlibfn key;

	d_dbset (id_dbfile);
	bzero (&key, sizeof (key));
	key.flibnum = libnum;
	strcpy (key.fname, fname);
	key.approved = approved;
	d_keyfind (STATLIBFN, &key);
	if (db_status == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY) {
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);
	}

	d_recread (f);
	if (db_status != S_OKAY) {
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);
	} else
		return 1;

	return 0;		/* Dummy */
}


int
filegetfirst (int libnum, struct fileidx *file, int approved)
{
	/* Set a reasonable key */

	struct statlibfn s;

	s.approved = approved;
	s.flibnum = libnum;
	s.fname[0] = 1;
	s.fname[1] = 0;

	d_dbset (id_dbfile);
	d_keyfind (STATLIBFN, &s);
	if (db_status != S_OKAY)
		d_keynext (STATLIBFN);
	if (db_status == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY) {
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);
	}
	if (d_recread (file) != S_OKAY) {
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);
	}
	return (libnum == file->flibnum) && (approved == file->approved);
}


int
filegetnext (int libnum, struct fileidx *file)
{
	struct statlibfn s;

	s.approved = file->approved;
	s.flibnum = file->flibnum;
	strcpy (s.fname, file->fname);

	d_dbset (id_dbfile);
	d_keyfind (STATLIBFN, &s);
	d_keynext (STATLIBFN);
	if (db_status == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY) {
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);
	}
	if (d_recread (file) != S_OKAY) {
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);
	}
	return file->flibnum == libnum && s.approved == file->approved;
}


int
filegetoldest (int libnum, time_t newer_than, int approved,
	       struct fileidx *file)
{
	struct timelib tl;

	tl.approved = approved;
	tl.flibnum = libnum;
	tl.timestamp = newer_than;

	d_dbset (id_dbfile);
	d_keyfind (TIMELIB, &tl);
	if (db_status != S_OKAY)
		d_keyprev (TIMELIB);
	if (db_status == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY) {
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);
	}
	if (d_recread (file) != S_OKAY) {
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);
	}
	return (libnum == file->flibnum) && (approved == file->approved);
}


int
filegetnextoldest (int libnum, struct fileidx *file)
{
	struct timelib tl;

	bzero (&tl, sizeof (tl));
	tl.approved = file->approved;
	tl.flibnum = file->flibnum;
	tl.timestamp = file->timestamp;
	strcpy (tl.fname, file->fname);

	d_dbset (id_dbfile);
	d_keyfind (TIMELIB, &tl);
	d_keynext (TIMELIB);
	if (db_status == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY) {
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);
	}
	if (d_recread (file) != S_OKAY) {
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);
	}
	return file->flibnum == libnum && tl.approved == file->approved;
}


/* End of File */
