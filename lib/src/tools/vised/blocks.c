/*****************************************************************************\
 **                                                                         **
 **  FILE:     blocks.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95, Version 0.5 alpha                               **
 **  PURPOSE:  The Visual Editor block functions                            **
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
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2003/12/29 07:50:12  alexios
 * Renamed getline() to vised_getline() to disambiguate it from a GNU
 * extension in stdio.h.
 *
 * Revision 1.5  2003/12/24 19:43:34  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1998/12/27 16:35:48  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/14 12:01:28  alexios
 * No changes.
 *
 * Revision 0.4  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/09/12 13:41:18  alexios
 * Lots of changes to fix bugs. Got rid of blockmove() and
 * replaced it with a blockcopy() and blockdel() in succession.
 * Blockcopy() will now not copy a block inside itself. A couple
 * of other small but important fixes.
 *
 * Revision 0.2  1997/08/31 09:23:15  alexios
 * Removed calls to the visual library, replaced them with ncurses
 * calls.
 *
 * Revision 0.1  1997/08/28 11:26:56  alexios
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
#define WANT_TIME_H 1
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "vised.h"
#include "mbk_vised.h"


void
delblock ()
{
	int     i, join = 0;

	if (!BLOCK)
		return;

	current = vised_getline (cy = kby);
	cx = kbx;

	if (kby == kky) {
		struct line *l = vised_getline (kby);

		numbytes -= strlen (l->text);
		strcpy (&l->text[kbx], &l->text[kkx]);
		numbytes += strlen (l->text);
		noblock ();
		return;
	}

	for (i = kky; i >= kby; i--) {
		if (i == kby && kbx) {
			struct line *l = vised_getline (i);

			numbytes -= strlen (l->text);
			l->text[kbx] = 0;
			numbytes += strlen (l->text);
			current = vised_getline (cy = kby);
			cx = kby;
			join++;
		} else if (i == kky && kkx) {
			struct line *l = vised_getline (i);

			numbytes -= strlen (l->text);
			strcpy (l->text, &l->text[kkx]);
			numbytes += strlen (l->text);
			join++;
		} else
			deleteline (i);
	}
	if ((cy - toprow + 1) < 1 || (cy - toprow + 1) >= LINES - 2)
		centerline ();
	kby = kky = 1;
	kbx = kkx = 0;
	if (join == 2)
		joinlines (cy);
	else
		noblock ();

	top = vised_getline (toprow);
	if (cy == toprow)
		current = top;
	else
		current = vised_getline (cy);
	cx = 0;
	if (cy > numlines) {
		insertline (last, "");
		current = last;
	} else if (!numlines)
		insertline (NULL, "");
	if (cy == 1 && numlines == 1)
		centerline ();
}


void
copyblock (int move)
{
	int     i;
	char    line[1024];
	struct line *l, *insp;

	if (!BLOCK)
		return;
	if (cy > kby && cy < (kky - (kkx == 0)))
		return;
	if (cy == kby && cx >= kbx)
		return;
	if (cy == (kky - (kkx == 0)) && cx < kkx)
		return;

	l = vised_getline (kby);
	if (cx) {
		splitline ();
	}
	if (cy == 1)
		insp = NULL;
	else
		insp = vised_getline (cy - 1);

	for (i = kby; i <= (kky - (kkx == 0)); i++) {
		if (i == kby && kby == kky && kkx > 0) {
			strcpy (line, &l->text[kbx]);
			line[kkx - kbx] = 0;
		} else if (i == kby)
			strcpy (line, &l->text[kbx]);
		else if (kkx > 0 && i == (kky - (kkx == 0))) {
			strcpy (line, l->text);
			line[kkx] = 0;
		} else
			strcpy (line, l->text);

		if (!move && (numbytes + strlen (line) + 1 > maxsize)) {
			bel (ERRSIZ);
			break;
		}
		insertline (insp, line);
		insp = insp->next;
		l = l->next;
	}
	cy = getlinenum (insp);
	current = insp;
	cx = strlen (line);
	if ((cy - toprow + 1) < 1 || (cy - toprow + 1) >= LINES - 2)
		centerline ();
	if (move) {
		int     x = cx;
		struct line *c = current;

		delblock ();
		gotoline (getlinenum (c), x);
	}
	noblock ();
	showtext (0);
}


/* End of File */
