/*****************************************************************************\
 **                                                                         **
 **  FILE:     iterate.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1999.                                                **
 **  PURPOSE:  Iterate import systems.                                      **
 **  NOTES:    See syntax() function for the syntax of this program.        **
 **                                                                         **
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
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
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
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include <megistos/netclub.h>



static int
rsysselect (const struct dirent *d)
{
	if (d->d_name[strlen (d->d_name) - 1] == '~')
		return 0;
	return d->d_name[0] != '.';
}



void
iterate ()
{
	struct dirent **systems;
	char    fname[512];
	int     n, i;

	n = scandir (mkfname (MSGSDIR "/..netimport"), &systems, rsysselect,
		     alphasort);
	for (i = 0; i < n; free (systems[i]), i++) {
		char   *cp = systems[i]->d_name;

		strcpy (fname, mkfname (MSGSDIR "/..netimport/%s", cp));
		*(strrchr (cp, ':')) = '/';

		if (debug)
			fprintf (stderr, "System: fname=(%s) sysname=(%s)\n",
				 fname, cp);
		if (sys != NULL && !sameas (cp, sys))
			continue;

		switch (mode) {
		case MODE_REPORT:
			print_report (fname, cp);
			break;
		case MODE_LISTCLUBS:
			list_clubs (fname, cp);
			break;
		case MODE_CLUBINFO:
			club_info (fname, cp, clubname);
			break;
		case MODE_SYNC:
			club_sync (fname, cp);
			break;
		default:
			fprintf (stderr,
				 "Paranoia check failed, bailing out.\n");
			exit (0);
		}

	}
	free (systems);
}


/* End of File */
