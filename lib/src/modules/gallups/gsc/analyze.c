/*****************************************************************************\
 **                                                                         **
 **  FILE:      analyze.c                                                   **
 **  AUTHORS:   Vangelis Rokas (Valis)                                      **
 **  PURPOSE:   Gallups Script Compiler                                     **
 **  NOTES:     Analyze and validate a gallups data file                    **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.4  2003/12/31 06:59:19  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  2000/09/27 18:35:06  bbs
 * *** empty log message ***
 *
 * Revision 1.1  2000/09/21 18:15:54  bbs
 * Gallups Script Compiler
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#include <stdio.h>
#include <string.h>

#include <megistos/gsc.h>

#if defined(__BORLANDC__)
#  include "glps-bcc.h"
#else
#  include "gallups.h"
#endif


char    tabchar[10];
char   *
gettab (int n)
{
	memset (tabchar, 0, 10);
	memset (tabchar, '\t', n);
	return tabchar;
};

int     tab = 0;

#define show	printf("%s", gettab(tab));printf


void
analyze (char *filename)
{
	FILE   *fp;
	char   *s, s1[256];
	int     i;
	struct question *q;
	struct answer *a;

	ginfo = &gallupsinfo;

	show ("Loading gallup data file %s\n", filename);
	_loadgallup (filename, filename, &gallupsinfo);
	show ("%i questions\n", gnumq (ginfo));

	for (i = 0; i < gnumq (ginfo); i++) {
		q = &questions[i];

		show ("Question %i\n", i + 1);

		tab++;
		switch (qtyp (q)) {
		case GQ_NUMBER:
			strcpy (s1, "number");
			break;
		case GQ_FREETEXT:
			strcpy (s1, "text");
			break;
		case GQ_SELECT:
			strcpy (s1, "select");
			break;
		case GQ_COMBO:
			strcpy (s1, "combo");
			break;
		}

		show ("type = %s\n", s1);
		tab--;
	}
}



/* End of File */
