/*****************************************************************************\
 **                                                                         **
 **  FILE:     opedit.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  The EDIT operation                                           **
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


static void
update_edit (struct libidx *lib,
	     char *olddir, int libnum, int *changes, int recursive)
{
	struct libidx l;
	int     statedir = 0, res;

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
		prompt (OEDIREC3, l.fullname);
	} else {
		int     i;

		for (i = 0; i < 4; i++) {
			if (!changes[i])
				continue;
			switch (i) {
			case 0:
				strcpy (l.descr, lib->descr);
				break;
			case 1:
				strcpy (l.passwd, lib->passwd);
				break;
			case 2:
				strcpy (l.club, lib->club);
				break;
			default:
				if (sameto (olddir, l.dir)) {
					char    newdir[256];

					sprintf (newdir, "%s/%s", lib->dir,
						 &l.dir[strlen (olddir)]);
					strcpy (l.dir, zonkdir (newdir));
					statedir = 1;
				}
			}
		}

		libupdate (&l);

		prompt (OEDIREC1 + statedir, l.fullname, l.dir);
	}

	libnum = l.libnum;

      children:
	res = libgetchild (libnum, "", &l);
	while (res) {
		char    keyname[20];

		update_edit (lib, olddir, l.libnum, changes, recursive);
		strcpy (keyname, l.keyname);
		res = libgetchild (libnum, keyname, &l);
	}
}


void
op_edit ()
{
	int     i;
	struct libidx lib;
	int     changes[4];
	int     recursive = 0;

	memcpy (&lib, &library, sizeof (lib));
	if (!adminlock (lib.libnum))
		return;
	bzero (changes, sizeof (changes));

	sprintf (inp_buffer, "%s\n%s\n%s\n%s\noff\nOK\nCANCEL\n",
		 lib.descr, lib.passwd, lib.club, lib.dir);

	if (dialog_run ("files", OEDIVT, OEDILT, inp_buffer, MAXINPLEN) != 0) {
		error_log ("Unable to run data entry subsystem");
		adminunlock ();
		return;
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[7], "OK") || sameas (margv[5], margv[7])) {
		for (i = 0; i < 8; i++) {
			char   *s = margv[i];

			if (i == 0) {
				if (strcmp (lib.descr, s))
					changes[i] = 1;
				strcpy (lib.descr, s);
			} else if (i == 1) {
				if (strcmp (lib.passwd, s))
					changes[i] = 1;
				strcpy (lib.passwd, s);
			} else if (i == 2) {
				if ((!masterlibop) && strcmp (library.club, s)) {
					prompt (OEDINOP1);
				} else {
					if (s[0]) {
						if (findclub (s))
							strcpy (lib.club, s);
						else
							prompt (OCRECNE, s);
					} else
						bzero (lib.club,
						       sizeof (lib.club));
					if (strcmp (library.club, lib.club))
						changes[i] = 1;
				}
			} else if (i == 3) {
				if ((!masterlibop) &&
				    strcmp (library.dir, lib.dir)) {
					prompt (OEDINOP2);
				} else {
					strcpy (lib.dir, zonkdir (s));
					if (strcmp (library.dir, lib.dir))
						changes[i] = 1;
				}
			} else if (i == 4) {
				if ((recursive = sameas (s, "on")) != 0)
					prompt (OEDIREC);
			}
		}
	} else {
		prompt (OPCAN);
		adminunlock ();
		return;
	}

	update_edit (&lib, library.dir, lib.libnum, changes, recursive);

	memcpy (&library, &lib, sizeof (library));

	adminunlock ();
	return;
}




/* End of File */
