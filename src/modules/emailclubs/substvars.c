/*****************************************************************************\
 **                                                                         **
 **  FILE:     substvars.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1995, Version 0.5                                    **
 **  PURPOSE:  Substitution variables used in the Email/Clubs modules       **
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
 * $Id: substvars.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: substvars.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/25 13:33:28  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1999/07/18 21:21:38  alexios
 * Fixed sneaky little bug in substvar code.
 *
 * Revision 0.3  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: substvars.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_emailclubs.h"
#include "email.h"


static char *
sv_club ()
{
	return clubhdr.club;
}


static char *
sv_clubid ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.clubid);
	return conv;
}


static char *
sv_clubdesc ()
{
	return clubhdr.descr;
}


static char *
sv_clubop ()
{
	return clubhdr.clubop;
}


static char *
sv_clubcrdate ()
{
	static char conv[32];

	sprintf (conv, "%s", strdate (clubhdr.crdate));
	return conv;
}


static char *
sv_clubcrtime ()
{
	static char conv[32];

	sprintf (conv, "%s", strtime (clubhdr.crtime, 0));
	return conv;
}


static char *
sv_clubmsgs ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.nmsgs);
	return conv;
}


static char *
sv_clubfiles ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.nfiles);
	return conv;
}


static char *
sv_clubper ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.nper);
	return conv;
}


static char *
sv_clubblts ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.nblts);
	return conv;
}


static char *
sv_clubw4app ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.nfunapp);
	return conv;
}


static char *
sv_clubmsglife ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.msglife);
	return conv;
}


static char *
sv_clubpostchg ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.postchg);
	return conv;
}


static char *
sv_clubuplchg ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.uploadchg);
	return conv;
}


static char *
sv_clubdnlchg ()
{
	static char conv[32];

	sprintf (conv, "%d", clubhdr.dnloadchg);
	return conv;
}


static char *
sv_clubrate ()
{
	static char conv[32];
	int     i =
	    (clubhdr.credspermin ==
	     -1) ? thisuseronl.credspermin : clubhdr.credspermin;
	sprintf (conv, "%d.%02d", i / 100, i % 100);
	return conv;
}


void
initecsubstvars ()
{
	struct substvar table[] = {
		{"@CLUB@", sv_club, NULL},
		{"@CLUBID@", sv_clubid, NULL},
		{"@CLUBDESC@", sv_clubdesc, NULL},
		{"@CLUBOP@", sv_clubop, NULL},
		{"@CLUBCRDATE@", sv_clubcrdate, NULL},
		{"@CLUBCRTIME@", sv_clubcrtime, NULL},

		{"@CLUBMSGS@", sv_clubmsgs, NULL},
		{"@CLUBFILES@", sv_clubfiles, NULL},
		{"@CLUBPER@", sv_clubper, NULL},
		{"@CLUBBLTS@", sv_clubblts, NULL},
		{"@CLUBW4APP@", sv_clubw4app, NULL},

		{"@CLUBMSGLIFE@", sv_clubmsglife, NULL},
		{"@CLUBPOSTCHG@", sv_clubpostchg, NULL},
		{"@CLUBUPLCHG@", sv_clubuplchg, NULL},
		{"@CLUBDNLCHG@", sv_clubdnlchg, NULL},
		{"@CLUBRATE@", sv_clubrate, NULL},
		{"", NULL, NULL}
	};

	int     i = 0;

	while (table[i].varname[0]) {
		out_addsubstvar (table[i].varname, table[i].varcalc);
		i++;
	}
}


/* End of File */
