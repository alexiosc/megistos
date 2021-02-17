/*****************************************************************************\
 **                                                                         **
 **  FILE:     oplimits.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  The LIMITS command                                           **
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
 * $Id: oplimits.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: oplimits.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
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
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
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
    "$Id: oplimits.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "files.h"
#include "mbk_files.h"




static void
update_limits (struct libidx *lib, int libnum, int *changes, int recursive)
{
	struct libidx l;
	int     res;

	if (lib->libnum == libnum) {
		libupdate (lib);
	}

	if (!recursive)
		return;
	else if (lib->libnum == libnum)
		goto children;

	if (!libreadnum (libnum, &l))
		return;

	if (!adminlock (libnum)) {
		prompt (OLIMREC2, l.fullname);
	} else {
		int     i;

		for (i = 0; i < 3; i++) {
			if (!changes[i])
				continue;
			switch (i) {
			case 0:
				l.filelimit = lib->filelimit;
				break;
			case 1:
				l.filesizelimit = lib->filesizelimit;
				break;
			default:
				l.libsizelimit = lib->libsizelimit;
				break;
			}
		}

		libupdate (&l);

		prompt (OLIMREC1, l.fullname);
	}

	libnum = l.libnum;

      children:
	res = libgetchild (libnum, "", &l);
	while (res) {
		char    keyname[20];

		update_limits (lib, l.libnum, changes, recursive);
		strcpy (keyname, l.keyname);
		res = libgetchild (libnum, keyname, &l);
	}
}


void
op_limits ()
{
	int     i;
	struct libidx lib;
	int     changes[3];
	int     recursive = 0;

	memcpy (&lib, &library, sizeof (lib));
	if (!adminlock (lib.libnum))
		return;

	sprintf (inp_buffer, "%d\n%d\n%d\noff\nOK\nCANCEL\n",
		 lib.filelimit, lib.filesizelimit, lib.libsizelimit);

	if (dialog_run ("files", OLIMVT, OLIMLT, inp_buffer, MAXINPLEN) != 0) {
		error_log ("Unable to run data entry subsystem");
		adminunlock ();
		return;
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[6], "OK") || sameas (margv[4], margv[6])) {
		for (i = 0; i < 7; i++) {
			char   *s = margv[i];

			switch (i) {
			case 0:
				changes[i] = lib.filelimit != atoi (s);
				lib.filelimit = atoi (s);
				break;
			case 1:
				changes[i] = lib.filesizelimit != atoi (s);
				lib.filesizelimit = atoi (s);
				break;
			case 2:
				changes[i] = lib.libsizelimit != atoi (s);
				lib.libsizelimit = atoi (s);
				break;
			case 3:
				if ((recursive = sameas (s, "on")) != 0)
					prompt (OLIMREC);
				break;
			}
		}
	} else {
		prompt (OPCAN);
		adminunlock ();
		return;
	}

	memcpy (&library, &lib, sizeof (library));

	update_limits (&lib, lib.libnum, changes, recursive);

	adminunlock ();
	return;
}



/* End of File */
