/*****************************************************************************\
 **                                                                         **
 **  FILE:     opcreate.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  The CREATE operation                                         **
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
 * Revision 0.5  2000/01/06 10:37:25  alexios
 * Modified calls to mklib to reflect new third argument.
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
#include "files.h"
#include "mbk_files.h"


static int
getnewlibname (char *s)
{
	char   *i, c;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				listsublibs ();
				cnc_end ();
				continue;
			}
			i = cnc_word ();
		} else {
			prompt (OCREASK);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 0;
			}
			if (sameas (margv[0], "?")) {
				listsublibs ();
				cnc_end ();
				continue;
			}
		}
		if (strlen (i) > sizeof (library.keyname) - 1) {
			prompt (OCRE2LN, sizeof (library.keyname) - 1);
		} else if (strspn (i, FNAMECHARS) != strlen (i)) {
			prompt (OCRECHR);
		} else
			break;
	}
	strcpy (s, i);
	return 1;
}


static int
edit (struct libidx *lib)
{
	sprintf (inp_buffer, "%s\n%s\n%s\n%s\nOK\nCANCEL\n",
		 lib->descr, lib->passwd, lib->club, lib->dir);

	if (dialog_run ("files", OCREVT, OCRELT, inp_buffer, MAXINPLEN) != 0) {
		error_log ("Unable to run data entry subsystem");
		return 0;
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[6], "OK") || sameas (margv[6], margv[4])) {
		bzero (lib->descr, sizeof (lib->descr));
		strncpy (lib->descr, margv[0], sizeof (lib->descr) - 1);

		bzero (lib->passwd, sizeof (lib->passwd));
		strncpy (lib->passwd, margv[1], sizeof (lib->passwd) - 1);

		bzero (lib->club, sizeof (lib->club));
		if (strlen (margv[2])) {
			if (findclub (margv[2]))
				strncpy (lib->club, margv[2],
					 sizeof (lib->club) - 1);
			else
				prompt (OCRECNE, margv[2]);
		}

		bzero (lib->dir, sizeof (lib->dir));
		strncpy (lib->dir, zonkdir (margv[3]), sizeof (lib->dir) - 1);
	} else {
		prompt (OPCAN);
		return 0;
	}

	return 1;
}


void
op_create ()
{
	char    s[20], tmp[20];
	struct libidx lib;

	if (nesting (library.fullname) > maxnest) {
		prompt (OCRENST, maxnest);
		return;
	}

	for (;;) {
		if (!getnewlibname (s))
			return;

		if (libexists (s, library.libnum)) {
			prompt (OCREEXS, s);
			cnc_end ();
			continue;
		} else
			break;
	}

	memcpy (&lib, &library, sizeof (lib));

	strcpy (lib.keyname, s);
	lowerc (lib.keyname);
	sprintf (lib.fullname, "%s/%s", library.fullname, s);
	sprintf (lib.dir, "%s/%s", library.dir, s);
	lib.descr[0] = 0;
	lib.parent = library.libnum;
	lib.numfiles = lib.numbytes = lib.numunapp = lib.bytesunapp = 0;
	bzero (lib.uploadsperday, sizeof (lib.uploadsperday));
	bzero (lib.bytesperday, sizeof (lib.bytesperday));
	strcpy (tmp, s);
	if (findclub (tmp))
		strcpy (lib.club, tmp);

	if (!edit (&lib))
		return;

	mklib (&lib, 0, 0);
	prompt (OCREOK, lib.fullname);
	enterlib (lib.libnum, 0);
}


/* End of File */
