/*****************************************************************************\
 **                                                                         **
 **  FILE:     scan.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 96, Version 0.5                                      **
 **  PURPOSE:  Teleconferences, channel scanning functins                   **
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
 * Revision 1.5  2003/12/27 12:29:38  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/07/18 21:48:36  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.7  1998/12/27 16:10:27  alexios
 * Added autoconf support. Minor bug fixes.
 *
 * Revision 0.6  1998/08/14 11:51:24  alexios
 * Removed the "DONE" markers from updated functions.
 *
 * Revision 0.5  1998/08/14 11:45:25  alexios
 * Migrated to the new channel engine.
 *
 * Revision 0.4  1998/08/11 10:21:33  alexios
 * Minor changes.
 *
 * Revision 0.3  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "telecon.h"
#include "mbk_telecon.h"


static int scan = 0;
static char scanfname[256];
static int numusers, scanpos;
static struct dirent **users = NULL;


static int
usrselect_all (const struct dirent *d)
{
	return d->d_name[0] != '.';
}

static int
usrselect_present (const struct dirent *d)
{
	return d->d_name[0] != '.' && d->d_name[strlen (d->d_name) - 1] == '+';
}

static int
usrselect_absent (const struct dirent *d)
{
	return d->d_name[0] != '.' && d->d_name[strlen (d->d_name) - 1] == '-';
}


struct chanhdr *
begscan (char *channel, int mode)
{
	static struct chanhdr c;
	struct stat st;
	char    fname[256];
	FILE   *fp;
	int     i;

	sprintf (fname, "%s/%s", mkfname (TELEDIR), mkchfn (channel));

	if (stat (fname, &st))
		return NULL;

	scanpos = 0;
	if (users != NULL) {
		for (i = 0; i < numusers; i++)
			free (users[i]);
		free (users);
	}
	users = NULL;
	numusers = 0;
	switch (mode) {
	case TSM_PRESENT:
		numusers =
		    scandir (fname, &users, usrselect_present, alphasort);
		break;
	case TSM_ABSENT:
		numusers =
		    scandir (fname, &users, usrselect_absent, alphasort);
		break;
	case TSM_ALL:
	default:
		numusers = scandir (fname, &users, usrselect_all, alphasort);
		break;
	}
	strcpy (scanfname, fname);

	if (channel[0] == 0)
		return NULL;

	sprintf (fname, "%s/%s/.header", mkfname (TELEDIR), mkchfn (channel));
	if ((fp = fopen (fname, "r")) == NULL) {
		error_fatalsys ("Unable to open channel header %s (chan=%s)",
				fname, channel);
	}
	if (fread (&c, sizeof (c), 1, fp) != 1) {
		int     i = errno;

		fclose (fp);
		errno = i;
		error_fatalsys ("Unable to read channel file %s", fname);
	}
	fclose (fp);

	scan = 1;

	return &c;
}


struct chanusr *
getscan ()
{
	static struct chanusr u;
	FILE   *fp;
	char    fname[256];

	if (scanpos >= numusers)
		return NULL;

	sprintf (fname, "%s/%s", scanfname, users[scanpos]->d_name);
	if ((fp = fopen (fname, "r")) == NULL) {
		scanpos++;

		/* Recursively get the next user if this one doesn't exist */
		return getscan ();
	}

	if (fread (&u, sizeof (u), 1, fp) != 1) {
		error_fatalsys ("Unable to read channel user %s", fname);
	}

	fclose (fp);

	/* Delete leftover channel files for users who aren't on-line now */

	{
		char    userid[64];

		strcpy (userid, users[scanpos]->d_name);
		userid[strlen (userid) - 1] = 0;
		if (!usr_insys (userid, 0)) {
			unlink (fname);
			return getscan ();
		}
	}

	scanpos++;
	return &u;
}


void
endscan ()
{
	int     i;

	if (users != NULL) {
		for (i = 0; i < numusers; i++)
			free (users[i]);
		free (users);
	}
	users = NULL;
	numusers = 0;
}


/* End of File */
