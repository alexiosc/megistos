/*****************************************************************************\
 **                                                                         **
 **  FILE:     substvars.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 0.5                                    **
 **  PURPOSE:  Teleconferences, define local substitution variables         **
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
 * Revision 0.4  1999/07/18 21:48:36  alexios
 * Fixed slight but sneaky bug in declaring the subst vars.
 *
 * Revision 0.3  1998/12/27 16:10:27  alexios
 * Added autoconf support.
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "telecon.h"


static char *svnomm, *svnomf;
static char *svgenm, *svgenf;
static char *svdatm, *svdatf;
static char *svaccm, *svaccf;
extern char fx_target[24], fx_targetsex;
extern int fx_targetcol;


char   *
sv_usrcol ()
{
	static char buf[16];

	sprintf (buf, "\033[%sm", colours[thisuseraux.colour]);
	return buf;
}


char   *
sv_artnom ()
{
	return (thisuseracc.sex == USX_MALE) ? svnomm : svnomf;
}


char   *
sv_artgen ()
{
	return (thisuseracc.sex == USX_MALE) ? svgenm : svgenf;
}


char   *
sv_artdat ()
{
	return (thisuseracc.sex == USX_MALE) ? svdatm : svdatf;
}


char   *
sv_artacc ()
{
	return (thisuseracc.sex == USX_MALE) ? svaccm : svaccf;
}


char   *
sv_othuid ()
{
	return fx_target;
}


char   *
sv_othcol ()
{
	static char buf[16];

	sprintf (buf, "\033[%sm", colours[fx_targetcol]);
	return buf;
}


char   *
sv_othnom ()
{
	return (fx_targetsex == USX_MALE) ? svnomm : svnomf;
}


char   *
sv_othgen ()
{
	return (fx_targetsex == USX_MALE) ? svgenm : svgenf;
}


char   *
sv_othdat ()
{
	return (fx_targetsex == USX_MALE) ? svdatm : svdatf;
}


char   *
sv_othacc ()
{
	return (fx_targetsex == USX_MALE) ? svaccm : svaccf;
}


void
initvars ()
{
	struct substvar table[] = {
		{"@USRCOL@", sv_usrcol, NULL},
		{"@ARTNOM@", sv_artnom, NULL},
		{"@ARTGEN@", sv_artgen, NULL},
		{"@ARTDAT@", sv_artdat, NULL},
		{"@ARTACC@", sv_artacc, NULL},
		{"@OTHUID@", sv_othuid, NULL},
		{"@OTHCOL@", sv_othcol, NULL},
		{"@OTHNOM@", sv_othnom, NULL},
		{"@OTHGEN@", sv_othgen, NULL},
		{"@OTHDAT@", sv_othdat, NULL},
		{"@OTHACC@", sv_othacc, NULL},
		{"", NULL, NULL}
	};
	int     i = 0;

	while (table[i].varname[0]) {
		out_addsubstvar (table[i].varname, table[i].varcalc);
		i++;
	}

	svnomm = strdup (msg_get (SVNOMM));
	svnomf = strdup (msg_get (SVNOMF));
	svgenm = strdup (msg_get (SVGENM));
	svgenf = strdup (msg_get (SVGENF));
	svdatm = strdup (msg_get (SVDATM));
	svdatf = strdup (msg_get (SVDATF));
	svaccm = strdup (msg_get (SVACCM));
	svaccf = strdup (msg_get (SVACCF));
}


/* End of File */
