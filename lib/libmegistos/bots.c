/*****************************************************************************\
 **                                                                         **
 **  FILE:     bots.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Functions pertaining to bots.                                **
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
 * Revision 1.3  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.2  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.1  2001/04/22 15:24:15  alexios
 * Initial checkin.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRINGS_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>



/* Escape sequences like "\nXXX " where XXX is a three digit number */

char   *
bot_escape (char *s)
{
	char   *cp;

	for (cp = s; *cp; cp++) {
		if (strlen (cp) >= 6 && (*cp) == '\n' && isdigit (*(cp + 1)) &&
		    isdigit (*(cp + 2)) && isdigit (*(cp + 3)) &&
		    isspace (*(cp + 4))) {
			*cp = '\33';
		}
	}
	return s;
}


char   *
bot_unescape (char *s)
{
	char   *cp;

	for (cp = s; *cp; cp++) {
		if (strlen (cp) >= 6 && (*cp) == '\33' && isdigit (*(cp + 1))
		    && isdigit (*(cp + 2)) && isdigit (*(cp + 3)) &&
		    isspace (*(cp + 4))) {
			*cp = '\n';
		}
	}
	return s;
}
