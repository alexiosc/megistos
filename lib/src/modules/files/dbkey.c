/*****************************************************************************\
 **                                                                         **
 **  FILE:     dbkey.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1998, Version 0.1                                 **
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
 * Slight changes to addkeywords() to make it more generic.
 * Added deletekeyword() and delfilekeywords(), a wrapper for
 * deletekeyword().
 *
 * Revision 0.4  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Added keywordfind() to locate a keyword. Added functions
 * keygetfirst() and keygetnext() that go through the keywords
 * for one specific file.
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


static int id_dbkey;


void
dbkeyopen ()
{
	d_dbfpath (mkfname (FILELIBDBDIR));
	d_dbdpath (mkfname (FILELIBDBDIR));
	if (d_open ("dbkey", "s") != S_OKAY) {
		error_fatal ("Cannot open keyword database (db_status %d).",
			     db_status);
	}
	d_dbget (&id_dbkey);
}


void
addkeywords (char *s, int approved, struct fileidx *f)
{
	struct keywordidx k;
	char   *cp;

	d_dbset (id_dbkey);

	cp = strtok (s, " ");
	while (cp) {

		strcpy (k.keyword, cp);
		strcpy (k.fname, f->fname);
		k.klibnum = f->flibnum;
		k.approved = approved;

		/*print("KEY=(%s), FNAME=(%s), LIB=%d\n",k.keyword,k.fname,k.klibnum); */

		if (d_fillnew (KEYWORDIDX, &k) != S_OKAY) {
			error_fatal ("Typhoon call failed with db_status=%d",
				     db_status);
		}

		cp = strtok (NULL, " ");
	}
}


void
addkeyword (struct keywordidx *kw)
{
	d_dbset (id_dbkey);
	if (d_fillnew (KEYWORDIDX, kw) == S_OKAY)
		return;
	else
		error_fatal ("Typhoon call failed with db_status=%d",
			     db_status);
}


void
deletekeyword (int libnum, char *fname, int approved, char *keyword)
{
	struct filekey k;

	bzero (&k, sizeof (k));
	k.approved = approved;
	k.klibnum = libnum;
	strcpy (k.keyword, keyword);
	strcpy (k.fname, fname);

	if (d_keyfind (FILEKEY, &k) == S_NOTFOUND)
		return;

	if (db_status != S_OKAY)
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);

	if (d_keyread (&k) != S_OKAY)
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);

	if (d_delete () != S_OKAY) {
		error_fatal ("Typhoon call failed with db_status=%d",
			     db_status);
	}
}


int
keywordfind (int libnum, char *keyword, struct maintkey *k)
{
	d_dbset (id_dbkey);
	bzero (k, sizeof (k));
	k->approved = 1;
	k->klibnum = libnum;
	strcpy (k->keyword, keyword);
	k->fname[0] = 1;
	k->fname[0] = 0;

	if (d_keyfind (MAINTKEY, k) == S_NOTFOUND)
		if (d_keynext (MAINTKEY) == S_NOTFOUND)
			return 0;

	if (db_status != S_OKAY)
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);

	if (d_keyread (k) != S_OKAY)
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);

	return libnum == k->klibnum;
}


int
keygetfirst (int libnum, struct maintkey *k)
{
	d_dbset (id_dbkey);
	bzero (k, sizeof (k));
	k->approved = 1;
	k->klibnum = libnum;
	k->keyword[0] = 1;
	k->keyword[1] = 0;
	k->fname[0] = 1;
	k->fname[0] = 0;
	if (d_keyfind (MAINTKEY, k) == S_NOTFOUND)
		if (d_keynext (MAINTKEY) == S_NOTFOUND)
			return 0;

	if (db_status != S_OKAY)
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);

	if (d_keyread (k) != S_OKAY)
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);

	return libnum == k->klibnum;
}


int
keygetnext (int libnum, struct maintkey *k)
{
	d_dbset (id_dbkey);
	if (d_keyfind (MAINTKEY, k) == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY)
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);

	if (d_keynext (MAINTKEY) == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY)
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);

	if (d_keyread (k) != S_OKAY)
		error_fatal ("Typhoon call 3 failed with db_status=%d",
			     db_status);

	return k->klibnum == libnum;
}


int
keyindexfirst (struct indexkey *k)
{
	d_dbset (id_dbkey);
	bzero (k, sizeof (k));
	if (d_keyfrst (INDEXKEY) == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY)
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);

	if (d_keyread (k) != S_OKAY)
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);

	return 1;
}


int
keyindexnext (struct indexkey *k)
{
	d_dbset (id_dbkey);
	if (d_keyfind (INDEXKEY, k) == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY)
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);

	if (d_keynext (INDEXKEY) == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY)
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);

	if (d_keyread (k) != S_OKAY)
		error_fatal ("Typhoon call 3 failed with db_status=%d",
			     db_status);

	return 1;
}


int
keyfilefirst (int libnum, char *fname, int approved, struct filekey *k)
{
	d_dbset (id_dbkey);
	bzero (k, sizeof (k));
	k->approved = approved;
	k->klibnum = libnum;
	strcpy (k->fname, fname);
	k->keyword[0] = 1;
	k->keyword[0] = 0;

	if (d_keyfind (FILEKEY, k) == S_NOTFOUND)
		if (d_keynext (FILEKEY) == S_NOTFOUND)
			return 0;

	if (db_status != S_OKAY)
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);

	if (d_keyread (k) != S_OKAY)
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);

	return libnum == k->klibnum && !strcmp (k->fname, fname) &&
	    approved == k->approved;
}


int
keyfilenext (int libnum, char *fname, int approved, struct filekey *k)
{
	d_dbset (id_dbkey);
	if (d_keyfind (FILEKEY, k) == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY)
		error_fatal ("Typhoon call 1 failed with db_status=%d",
			     db_status);

	if (d_keynext (FILEKEY) == S_NOTFOUND)
		return 0;
	else if (db_status != S_OKAY)
		error_fatal ("Typhoon call 2 failed with db_status=%d",
			     db_status);

	if (d_keyread (k) != S_OKAY)
		error_fatal ("Typhoon call 3 failed with db_status=%d",
			     db_status);

	return k->klibnum == libnum && !strcmp (k->fname, fname) &&
	    k->approved == approved;
}


void
delfilekeywords (struct libidx *l, struct fileidx *f)
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
		char    k[8192], *cp;

		strcpy (k, keystg);
		for (cp = strtok (k, " "); cp; cp = strtok (NULL, " ")) {
			deletekeyword (l->libnum, f->fname, f->approved, cp);
		}
	}
}


/* End of File */
