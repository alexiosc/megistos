/*****************************************************************************\
 **                                                                         **
 **  FILE:     substvar.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  Substitution variables for the libraries                     **
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
 * $Id: substvars.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: substvars.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 08:59:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  2000/01/06 10:37:25  alexios
 * Fixed silly but strange bug where the creation date would be
 * formatted as time, ending up in very strange times (eg 30:00:00).
 *
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Fixed sneaky bug in substvar code.
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Added variable @ENTRIESPERPAGE@ for the search dialog.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: substvars.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "files.h"
#include "mbk_files.h"


static char *
sv_libnum ()
{
	static char conv[32];

	sprintf (conv, "%d", library.libnum);
	return conv;
}


static char *
sv_lib ()
{
	return leafname (library.fullname);
}


static char *
sv_libfull ()
{
	return library.fullname;
}


static char *
sv_libdir ()
{
	return library.dir;
}


static char *
sv_libclub ()
{
	return library.club;
}


static char *
sv_libdevice ()
{
	static char conv[12];

	sprintf (conv, "%02x:%02x", (library.device & 0xff00) >> 8,
		 library.device & 0xff);
	return conv;
}


static char *
sv_libdescr ()
{
	return library.descr;
}


static char *
sv_libcrdate ()
{
	static char conv[12];

	strncpy (conv, strdate (library.crdate), 12);
	return conv;
}


static char *
sv_libcrtime ()
{
	static char conv[9];

	strncpy (conv, strtime (library.crtime, 1), 9);
	return conv;
}


static char *oplhdr, *oplcomma, *opllast, *oplftr, *oplnone;

static char *
sv_libops ()
{
	static char conv[256];
	int     i, c;

	for (i = c = 0; i < 5; i++) {
		c += ((library.libops[i][0] != 0) &&
		      !sameas (library.libops[i], SYSOP));
	}
	if (!c)
		return oplnone;
	else {
		strcpy (conv, oplhdr);
		for (i = 0; c; i++) {
			if (library.libops[i][0]) {
				c--;
				strcat (conv, library.libops[i]);
				if (c > 1)
					strcat (conv, oplcomma);
				else if (c == 1)
					strcat (conv, opllast);
			}
		}
		strcat (conv, oplftr);
	}
	return conv;
}


static char *
sv_libfilelimit ()
{
	static char conv[32];

	sprintf (conv, "%d", library.filelimit);
	return conv;
}


static char *
sv_libfsizelimit ()
{
	static char conv[32];

	sprintf (conv, "%d", library.filesizelimit);
	return conv;
}


static char *
sv_liblsizelimit ()
{
	static char conv[32];

	sprintf (conv, "%d", library.libsizelimit);
	return conv;
}


static char *
sv_libnumfiles ()
{
	static char conv[32];

	sprintf (conv, "%d", library.numfiles);
	return conv;
}


static char *
sv_libnumbytes ()
{
	static char conv[32];

	sprintf (conv, "%d", library.numbytes);
	return conv;
}


static char *
sv_libnumkbytes ()
{
	static char conv[32];

	sprintf (conv, "%d", library.numbytes >> 10);
	return conv;
}


static char *
sv_libnummbytes ()
{
	static char conv[32];

	sprintf (conv, "%d", library.numbytes >> 20);
	return conv;
}


static char *
sv_libnumunapp ()
{
	static char conv[32];

	sprintf (conv, "%d", library.numunapp);
	return conv;
}


static char *
sv_libbytesunapp ()
{
	static char conv[32];

	sprintf (conv, "%d", library.bytesunapp);
	return conv;
}


static char *
sv_libkbytesunapp ()
{
	static char conv[32];

	sprintf (conv, "%d", library.bytesunapp >> 10);
	return conv;
}


static char *
sv_libmbytesunapp ()
{
	static char conv[32];

	sprintf (conv, "%d", library.bytesunapp >> 20);
	return conv;
}


static char *
sv_libuplstoday ()
{
	static char conv[32];

	sprintf (conv, "%d", library.uploadsperday[0]);
	return conv;
}


static char *
sv_libuplsweek ()
{
	int     i, s;
	static char conv[32];

	for (i = s = 0; i < 7; i++)
		s += library.uploadsperday[i];
	sprintf (conv, "%d", s);
	return conv;
}


static char *
sv_libkuplstoday ()
{
	static char conv[32];

	sprintf (conv, "%d", library.bytesperday[0] >> 10);
	return conv;
}


static char *
sv_libkuplsweek ()
{
	int     i, s;
	static char conv[32];

	for (i = s = 0; i < 7; i++)
		s += library.bytesperday[i];
	sprintf (conv, "%d", s >> 10);
	return conv;
}


static char *
sv_libchupl ()
{
	static char conv[32];

	sprintf (conv, "%d", library.uplcharge);
	return conv;
}


static char *
sv_libchdnl ()
{
	static char conv[32];

	sprintf (conv, "%d", library.dnlcharge);
	return conv;
}


static char *
sv_librebate ()
{
	static char conv[32];

	sprintf (conv, "%d%%", library.rebate);
	return conv;
}


static char *
sv_maxkeyw ()
{
	static char conv[32];

	sprintf (conv, "%d", maxkeyw);
	return conv;
}


static char *
sv_deslen ()
{
	static char conv[32];

	sprintf (conv, "%d", deslen);
	return conv;
}


static char *
sv_entriesperpage ()
{
	static char conv[32];

	sprintf (conv, "%d", srlstln);
	return conv;
}


void
initlibsubstvars ()
{
	struct substvar table[] = {
		{"@LIBNUM@", sv_libnum, NULL},
		{"@LIB@", sv_lib, NULL},
		{"@LIBFULL@", sv_libfull, NULL},
		{"@LIBDIR@", sv_libdir, NULL},
		{"@LIBCLUB@", sv_libclub, NULL},
		{"@LIBDEVICE@", sv_libdevice, NULL},
		{"@LIBDESCR@", sv_libdescr, NULL},
		{"@LIBCRDATE@", sv_libcrdate, NULL},
		{"@LIBCRTIME@", sv_libcrtime, NULL},
		{"@LIBOPS@", sv_libops, NULL},
		{"@LIBFILELIMIT@", sv_libfilelimit, NULL},
		{"@LIBFSIZELIMIT@", sv_libfsizelimit, NULL},
		{"@LIBLSIZELIMIT@", sv_liblsizelimit, NULL},
		{"@LIBNUMFILES@", sv_libnumfiles, NULL},
		{"@LIBNUMBYTES@", sv_libnumbytes, NULL},
		{"@LIBNUMKBYTES@", sv_libnumkbytes, NULL},
		{"@LIBNUMMBYTES@", sv_libnummbytes, NULL},
		{"@LIBNUMUNAPP@", sv_libnumunapp, NULL},
		{"@LIBBYTESUNAPP@", sv_libbytesunapp, NULL},
		{"@LIBKBYTESUNAPP@", sv_libkbytesunapp, NULL},
		{"@LIBMBYTESUNAPP@", sv_libmbytesunapp, NULL},
		{"@LIBUPLSTODAY@", sv_libuplstoday, NULL},
		{"@LIBUPLSWEEK@", sv_libuplsweek, NULL},
		{"@LIBKUPLSTODAY@", sv_libkuplstoday, NULL},
		{"@LIBKUPLSWEEK@", sv_libkuplsweek, NULL},
		{"@LIBCHUPL@", sv_libchupl, NULL},
		{"@LIBCHDNL@", sv_libchdnl, NULL},
		{"@LIBREBATE@", sv_librebate, NULL},
		{"@MAXKEYW@", sv_maxkeyw, NULL},
		{"@DESLEN@", sv_deslen, NULL},
		{"@ENTRIESPERPAGE@", sv_entriesperpage, NULL},
		{"", NULL, NULL}
	};

	int     i = 0;

	while (table[i].varname[0]) {
		out_addsubstvar (table[i].varname, table[i].varcalc);
		i++;
	}

	oplhdr = msg_string (OPLHDR);
	oplcomma = msg_string (OPLCOMMA);
	opllast = msg_string (OPLLAST);
	oplftr = msg_string (OPLFTR);
	oplnone = msg_string (OPLNONE);
}


/* End of File */
