/*****************************************************************************\
 **                                                                         **
 **  FILE:     edit.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95, Version 0.5 alpha                               **
 **  PURPOSE:  The Visual Editor editing functions                          **
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
 * Revision 1.6  2003/12/29 07:50:12  alexios
 * Renamed getline() to vised_getline() to disambiguate it from a GNU
 * extension in stdio.h.
 *
 * Revision 1.5  2003/12/24 19:43:34  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/23 23:20:22  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/08/13 17:10:05  alexios
 * Fixed things so that user inactivity timers are reset to handle
 * slightly borken (sic) telnet line timeouts. This is useless but
 * harmless, since emud handles these timeouts.
 *
 * Revision 0.6  1998/12/27 16:35:48  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/14 12:01:28  alexios
 * Fixed very slight wrap-around bug that caused a wrapped-
 * around space to be removed.
 *
 * Revision 0.4  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/09/12 13:41:18  alexios
 * Slight fixes with block beginning/end coordinates.
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
inschar (int c, int update)
{
	int     insp = min (cx, strlen (current->text));
	char    line[MAXLEN];
	int     oldnumbytes = numbytes;

	if (numbytes >= maxsize) {
		bel (ERRSIZ);
		return;
	}

	if (!insertmode) {
		if (insp >= rmargin && NOWRAP) {
			formatline ();
			if (c == 32)
				return;
		}
		strcpy (line, current->text);
		numbytes -= strlen (line);
		line[insp] = c;
		if (insp >= strlen (current->text))
			line[insp + 1] = 0;
		numbytes += strlen (line);
		if (numbytes > maxsize) {
			numbytes = oldnumbytes;
			bel (ERRSIZ);
			return;
		}
		strcpy (current->text, line);
		if (update)
			showtext (cy - toprow + 1);
		cx++;
		if (update) {
			putcursor ();
			refresh ();
		}
	} else {
		if (insp >= rmargin /*&& NOWRAP */ ) {
			formatline ();
			insp = strlen (current->text);
			/*if(c==32)return; */
		}
		if (strlen (current->text) >= rmargin /*&& NOWRAP */ ) {
			bel (0);
			insertline (current, &current->text[cx]);
			numbytes -= strlen (&current->text[cx]);
			current->text[cx] = 0;
			if (update)
				showtext (0);
		}
		strcpy (line, current->text);
		numbytes -= strlen (line);
		line[insp] = c;

		if (insp >= strlen (line))
			line[insp + 1] = 0;
		else
			strcpy (&line[insp + 1], &current->text[insp]);
		numbytes += strlen (line);
		if (numbytes > maxsize) {
			numbytes = oldnumbytes;
			bel (ERRSIZ);
			return;
		}
		strcpy (current->text, line);

		if (update)
			showtext (cy - toprow + 1);
		cx++;

		if ((cx - leftcol) >= COLS) {
			leftcol += hscrinc;
			showtext (-(cy - toprow + 1));
		}

		if (update) {
			putcursor ();
			refresh ();
		}
	}
}


void
splitline ()
{
	if (numbytes >= maxsize) {
		bel (ERRSIZ);
		return;
	}

	insertline (current, &current->text[cx]);
	numbytes -= strlen (&current->text[cx]);
	current->text[cx] = 0;
	movecursor (1, -2);
	showtext (-(cy - toprow));
}


void
newline ()
{
	if (cy == numlines) {
		kby = kky = 1;
		kbx = kkx = 0;
		if (numbytes >= maxsize) {
			bel (ERRSIZ);
			return;
		} else {
			insertline (last, "");
		}
	}
	if (insertmode) {
		kby = kky = 1;
		kbx = kkx = 0;
		splitline ();
	} else
		movecursor (1, -2);
}


void
joinlines (int target)
{
	struct line *l1, *l2;
	int     num;

	if (target < 1 || target == numlines)
		return;
	l1 = vised_getline (target);
	l2 = vised_getline (target + 1);
	num = rmargin - strlen (l1->text);
	if (num <= 0)
		return;
	cx = strlen (l1->text);
	if ((signed) num >= (signed) strlen (l2->text)) {
		strcat (l1->text, l2->text);
		numbytes += strlen (l2->text);
		deleteline (target + 1);
		top = vised_getline (toprow);
		cy = target;
		if (cy == toprow)
			current = top;
		else
			current = vised_getline (cy);
	} else {
		char    temp[1024];

		strcpy (temp, l2->text);
		strcpy (l2->text, &temp[num]);
		temp[num] = 0;
		strcat (l1->text, temp);
		cy = target;
	}
	current = vised_getline (cy);
	if (cy < toprow)
		centerline ();
	showtext (0);
}


void
backspace ()
{
	if (insertmode) {
		if (!cx) {
			joinlines (cy - 1);
			return;
		}
		movecursor (0, -1);
		strcpy (&current->text[cx], &current->text[cx + 1]);
		numbytes--;
		showtext (cy - toprow + 1);
		showtext (cy);
	} else
		movecursor (0, -1);
}


void
delline ()
{
	deleteline (cy);
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
	showtext (0);
	showtext (-(cy - toprow + 1));
	movecursor (0, -2);
	while (mygetch () != ERR);
}


void
deletechar ()
{
	if (cx < strlen (current->text)) {
		strcpy (&current->text[cx], &current->text[cx + 1]);
		numbytes--;
		showtext (cy - toprow + 1);
		showtext (cy);
	} else
		joinlines (cy);
}


/* End of File */
