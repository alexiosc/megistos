/*****************************************************************************\
 **                                                                         **
 **  FILE:     fileops.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 1997, Version 0.1                                **
 **  PURPOSE:  Operations on library files (copy, move etc)                 **
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
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support. Migrated to the new locking functions.
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
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "files.h"
#include "mbk_files.h"
#define __ARCHIVERS_UNAMBIGUOUS__
#include <mbk/mbk_archivers.h>


static int numdevs[16];
static int *slowdevs[16];


void
saveslowdevs ()
{
	FILE   *fp = fopen (mkfname (SLOWDEVFILE), "w");
	int     i;

	if (fp == NULL) {
		error_fatalsys ("Unable to open %s for writing.",
				mkfname (SLOWDEVFILE));
	}

	for (i = 0; i < 16; i++) {
		if (fwrite (&numdevs[i], sizeof (int), 1, fp) != 1) {
			error_fatalsys ("Unable to write to %s",
					mkfname (SLOWDEVFILE));
		}

		if (numdevs[i] == 0)
			continue;

		if (fwrite (slowdevs[i], sizeof (int), numdevs[i], fp) !=
		    numdevs[i]) {
			error_fatalsys ("Unable to write to %s",
					mkfname (SLOWDEVFILE));
		}
	}

	/*
	   {
	   int a,b;
	   print("Saving...\n");
	   for(a=0;a<16;a++){
	   print("Group %2d (#%2d): ",a,numdevs[a]);
	   if(numdevs[a]==0){
	   print("\n");
	   continue;
	   }
	   for(b=0;b<numdevs[a];b++)print("0x%04x ",slowdevs[a][b]);
	   print("\n");
	   }
	   }
	 */

	fclose (fp);
}


void
loadslowdevs ()
{
	FILE   *fp = fopen (mkfname (SLOWDEVFILE), "r");
	int     i;

	if (fp == NULL) {
		error_fatalsys ("Unable to open %s for reading.",
				mkfname (SLOWDEVFILE));
	}

	for (i = 0; i < 16; i++) {
		if (fread (&numdevs[i], sizeof (int), 1, fp) != 1) {
			error_fatalsys ("Unable to read from %s",
					mkfname (SLOWDEVFILE));
		}

		if (numdevs[i] == 0) {
			slowdevs[i] = NULL;
			continue;
		}

		slowdevs[i] = alcmem (numdevs[i] * sizeof (int));
		if (fread (slowdevs[i], sizeof (int), numdevs[i], fp) !=
		    numdevs[i]) {
			error_fatalsys ("Unable to write to %s",
					mkfname (SLOWDEVFILE));
		}

	}

	/*
	   {
	   int a,b;
	   print("Loading...\n");
	   for(a=0;a<16;a++){
	   print("Group %2d (#%2d, %p): ",a,numdevs[a],slowdevs[a]);
	   if(numdevs[a]==0){
	   print("\n");
	   continue;
	   }
	   for(b=0;b<numdevs[a];b++)print("0x%04x ",slowdevs[a][b]);
	   print("\n");
	   }
	   }
	 */

	fclose (fp);
}


void
initslowdevs ()
{
	struct stat st1, st2;
	char    fname[256];
	int     i;


	/* Check if we need to reprocess the table */

	sprintf (fname, "%s/files.mbk", mkfname (MBKDIR));
	if (stat (fname, &st1)) {
		error_fatalsys ("Sanity check failed: unable to stat %s",
				fname);
	}

	if (stat (mkfname (SLOWDEVFILE), &st2))
		st2.st_mtime = 0;

	if (st1.st_mtime < st2.st_mtime) {
		loadslowdevs ();
		return;
	}


	/* Process all 16 groups */

	bzero (numdevs, sizeof (numdevs));
	bzero (slowdevs, sizeof (slowdevs));

	for (i = 0; i < 15; i++) {
		char    command[256];
		FILE   *pp;
		int     devs[512], ndevs = 0;

		if (!strlen (msg_get (SLOWDEV0 + i)))
			continue;

		sprintf (command,
			 "echo %s|tr \" \" \"\\012\" 2>/dev/null 2>/dev/null",
			 msg_get (SLOWDEV0 + i));
		if ((pp = popen (command, "r")) == NULL) {
			error_fatalsys
			    ("Unable to pipe-in wildcard expansion!");
		}

		memset (devs, -1, sizeof (devs));
		ndevs = 0;
		while (!feof (pp)) {
			char    line[1024], *cp;
			struct stat st;

			if (!fgets (line, sizeof (line), pp))
				break;
			if ((cp = strchr (line, '\n')) != NULL)
				*cp = 0;

			if (!stat (line, &st)) {
				if (!S_ISBLK (st.st_mode)) {
					error_fatal
					    ("\"%s\" in group SLOWDEV%c is not a block device",
					     line,
					     i + (i < 10 ? '0' : ('A' - 10)));
				}

				if (ndevs >= (sizeof (devs) / sizeof (int))) {
					error_fatal
					    ("Too many devices (>=512) in group SLOWDEV%c",
					     i + (i < 10 ? '0' : ('A' - 10)));
				}
				devs[ndevs++] = st.st_rdev;
			}
		}

		slowdevs[i] = alcmem (ndevs * sizeof (int));
		memcpy (slowdevs[i], devs, sizeof (int) * ndevs);
		numdevs[i] = ndevs;

		pclose (pp);
	}

	saveslowdevs ();
}


static int lastlibnum = -1, lastgroup = -1;


int
getlibgroup (struct libidx *lib)
{
	int     a, b;

	if (lib->libnum == lastlibnum)
		return lastgroup;
	lastlibnum = lib->libnum;
	for (a = 0; a < 16; a++) {
		if (numdevs[a] == 0)
			continue;
		for (b = 0; b < numdevs[a]; b++)
			if (lib->device == slowdevs[a][b])
				return lastgroup = a;
	}
	return lastgroup = -1;	/* -1 means lib is not on a slow device */
}


int
checkliblock (struct libidx *lib)
{
	int     group = getlibgroup (lib);

	if (group < 0)
		return 0;
	else {
		char    fname[256], dummy[256];

		sprintf (fname, SLOWDEVLOCK, group);
		return lock_check (fname, dummy);
	}
	return 0;		/* Never happens */
}


int
obtainliblock (struct libidx *lib, int timeout, char *reason)
{
	char    fname[256], dummy[256];
	int     group = getlibgroup (lib);

	if (group < 0)
		return 1;

	sprintf (fname, SLOWDEVLOCK, group);

	if (lock_check (fname, dummy) > 0) {
		prompt (LIBWLCK);
		if (lock_wait (fname, timeout) == LKR_TIMEOUT) {
			prompt (LIBFLCK);
			return 0;
		}
	}
	lock_place (fname, reason);
	return 1;
}


void
rmliblock (struct libidx *lib)
{
	int     group = getlibgroup (lib);
	char    fname[256];

	if (group < 0)
		return;
	sprintf (fname, SLOWDEVLOCK, group);
	lock_rm (fname);
}


int
installfile (char *source, char *finalname, struct libidx *lib)
{
	char    target[1024];
	int     res = 1;

	prompt (FILEINST);
	if (!obtainliblock (lib, sldevto, "installing"))
		return 0;
	sprintf (target, "%s/%s", lib->dir, finalname);
	if (fcopy (source, target))
		res = 0;
	rmliblock (lib);
	return res;
}


/* End of File */
