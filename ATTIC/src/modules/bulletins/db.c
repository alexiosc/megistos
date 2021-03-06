/*****************************************************************************\
 **                                                                         **
 **  FILE:     db.c                                                         **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Database functions for the bulletin reader.                  **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id: db.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: db.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:15  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: db.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <libtyphoon/typhoon.h>
#include <megistos/bbs.h>
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


void
dbopen ()
{
	d_dbfpath (mkfname (BLTDBDIR));
	d_dbdpath (mkfname (BLTDBDIR));
	if (d_open ("bltidx", "s") != S_OKAY) {
		error_fatal ("Unable to open Bulletin database (db_status %d)",
			     db_status);
	}
}


void
dbclose ()
{
	d_close ();
}


int
dbgetfirst ()
{
	d_keyfrst (NUM);
	if (db_status == S_OKAY) {
		int     res;

		d_keyread (&res);
		if (db_status == S_OKAY)
			return res;
	} else if (db_status == S_NOTFOUND)
		return 0;

	error_fatal ("Freak error (db_status=%d), argh argh.", db_status);
	return -1;		/* just to get rid of the warning */
}


int
dbgetlast ()
{
	d_keylast (NUM);
	if (db_status == S_OKAY) {
		int     res;

		d_keyread (&res);
		if (db_status == S_OKAY)
			return res;
	} else if (db_status == S_NOTFOUND)
		return 0;

	error_fatal ("Freak error (db_status=%d), argh argh.", db_status);
	return -1;		/* just to get rid of the warning */
}


int
dbins (struct bltidx *blt)
{
	d_fillnew (BLTIDX, blt);
	/*if(db_status==S_OKAY)return; */
	/*error_fatal("Unable to insert new bulletin (db_status=%d).",db_status); */
	return db_status == S_OKAY;
}


int
dbexists (char *area, char *fname)
{
	struct fnamec key;

	strcpy (key.area, area);
	strcpy (key.fname, fname);
	d_keyfind (FNAMEC, &key);
	return db_status == S_OKAY;
}


void
dbget (struct bltidx *blt)
{
	d_recread (blt);
	if (db_status != S_OKAY) {
		error_fatal ("Unable to get current record (db_status=%d).",
			     db_status);
	}
}


int
dblistfind (char *club, int num)
{
	struct numc numc;

	strcpy (numc.area, club);
	numc.num = 1;
	d_keyfind (NUMC, &numc);
	if (db_status != S_OKAY)
		d_keynext (NUMC);
	return db_status == S_OKAY;
}


int
dbfound ()
{
	return db_status == S_OKAY;
}


int
dblistfirst ()
{
	d_keyfrst (NUMC);
	return db_status == S_OKAY;
}


int
dblistlast ()
{
	d_keylast (NUMC);
	return db_status == S_OKAY;
}


int
dblistnext ()
{
	d_keynext (NUMC);
	return db_status == S_OKAY;
}


int
dblistprev ()
{
	d_keyprev (NUMC);
	return db_status == S_OKAY;
}


int
dbnumexists (int num)
{
	d_keyfind (NUM, &num);
	return db_status == S_OKAY;
}


int
dbchkambiguity (char *fname)
{
	struct fnamec key;

	strcpy (key.fname, fname);
	strcpy (key.area, "");

	d_keyfind (FNAMEC, &key);
	if (db_status != S_OKAY)
		d_keynext (FNAMEC);
	d_keyread (&key);
	if (!sameas (key.fname, fname))
		return 0;
	if (db_status != S_OKAY)
		return 0;

	d_keynext (FNAMEC);
	if (db_status != S_OKAY)
		return 1;

	d_keyread (&key);
	if (!sameas (key.fname, fname))
		return 1;
	return 2;
}


int
dbupdate (struct bltidx *blt)
{
	if (!dbexists (blt->area, blt->fname))
		return 0;
	d_recwrite (blt);
	return db_status == S_OKAY;
}


int
dbdelete ()
{
	d_delete ();
	return db_status == S_OKAY;
}


/* End of File */
