/*****************************************************************************\
 **                                                                         **
 **  FILE:     utils.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95, Version 0.5 alpha                               **
 **  PURPOSE:  The Visual Editor utility functions                          **
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
 * Revision 1.5  2003/12/24 19:44:11  alexios
 * Curses fixes.
 *
 * Revision 1.4  2003/12/23 23:20:22  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/08/13 17:10:05  alexios
 * Fixed things so that user inactivity timers are reset to handle
 * slightly borken (sic) telnet line timeouts. This is useless but
 * harmless, since emud handles these timeouts.
 *
 * Revision 0.5  1998/12/27 16:35:48  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 12:01:28  alexios
 * No changes.
 *
 * Revision 0.3  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
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


struct line *
vised_getline (int line)
{
	struct line *l;
	int     i;

	if (line <= 0)
		line = 1;
	if (line > numlines)
		line = numlines;
	for (i = 1, l = first; i != line && l; i++, l = l->next);
	return l;
}


void
insertline (struct line *afterline, char *s)
{
	struct line *new = (struct line *) alcmem (sizeof (struct line));

	if (!new)
		return;
	new->text = (char *) alcmem (MAXLEN);
	strncpy (new->text, s, MAXLEN);
	if (!afterline)
		new->next = first;
	else {
		new->next = afterline->next;
		afterline->next = new;
	}
	if (!first || !afterline)
		first = new;
	if (!new->next)
		last = new;
	numlines++;
	numbytes += strlen (s) + 1;
}


void
deleteline (int num)
{
	struct line *l = NULL, *p = NULL;

	if (num > 1) {
		p = vised_getline (num - 1);
		l = p->next;
	} else
		l = vised_getline (num);
	if (first == l)
		first = l->next;
	if (!l->next)
		last = p;
	if (p)
		p->next = l->next;
	numbytes -= strlen (l->text) + 1;
	free (l->text);
	free (l);
	numlines--;
}


void
centerline ()
{
	int     c = (LINES - 3) / 2;

	if (cy - c < 1)
		c = cy - 1;
	toprow = cy - c;
	top = vised_getline (toprow);
}


void
gotoline (int line, int column)
{
	struct line *l;
	int     i;

	if (line <= 0)
		line = 1;
	if (line > numlines)
		line = numlines;
	for (i = 1, l = first; (i != line) && l; i++, l = l->next);
	cy = i;
	current = l;
	if (column < 0)
		cx = strlen (current->text);
	centerline ();
}


void
movecursor (int dy, int dx)
{
	if (dx == -1) {
		if (--cx < 0) {
			if (cy > 1)
				dx = 2;
			else
				cx = 0;
			dy--;
		} else if (cx < leftcol) {
			leftcol = max (leftcol - hscrinc, 0);
			showtext (-(cy - toprow + 1));
		}
	} else if (dx == 1) {
		if (++cx > strlen (current->text)) {
			if (cy < numlines)
				dx = -2;
			else
				cx = strlen (current->text);
			dy++;
		} else if ((cx - leftcol) >= COLS) {
			leftcol += hscrinc;
			showtext (-(cy - toprow + 1));
		}
	}

	if (dy == -1) {
		if (leftcol) {
			leftcol = 0;
			showtext (-(cy - toprow + 1));
		}
		if (--cy < 1)
			cy = 1;
		current = vised_getline (cy);
		if (cy < toprow) {
			toprow = max (toprow - vscrinc, 1);
			top = vised_getline (toprow);
			showtext (0);
		}
	} else if (dy == 1) {
		if (leftcol) {
			leftcol = 0;
			showtext (-(cy - toprow + 1));
		}
		if (++cy > numlines + 1)
			cy = numlines + 1;
		if (cy == numlines + 1) {
			if (numbytes < maxsize) {
				insertline (last, "");
				current = last;
			} else {
				cy--;
				bel (ERRSIZ);
			}
		} else
			current = vised_getline (cy);
		if (((signed) cy - (signed) ((signed) LINES - 3)) >=
		    (signed) toprow) {
			toprow = min (toprow + vscrinc, numlines);
			top = vised_getline (toprow);
			showtext (0);
		}
	}

	if (dx == -2) {
		cx = 0;
		if (leftcol) {
			leftcol = 0;
			showtext (-(cy - toprow + 1));
		}
	} else if (dx == 2) {
		cx = strlen (current->text);
		if (cx >= COLS) {
			leftcol = strlen (current->text) - COLS + 1;
			showtext (-(cy - toprow + 1));
		}
	}

	if ((leftcol == 0) && current && (strlen (current->text) >= COLS)
	    && (cx >= COLS)) {
		leftcol = cx - COLS + 1;
		showtext (0);
	}

	putcursor ();
	refresh ();
}


void
movepage (int incr)
{
	int     t = toprow, c = cy;

	toprow += incr;
	cy += incr;
	if (cy > numlines)
		cy = numlines;
	if (toprow < 1) {
		toprow = 1;
		cy = 1;
		current = top = vised_getline (toprow);
	} else if (toprow > numlines) {
		current = vised_getline (cy = numlines);
		centerline ();
	} else {
		current = vised_getline (cy);
		top = vised_getline (toprow);
	}

	if (current && (strlen (current->text) >= COLS) && (cx >= COLS)) {
		leftcol = cx - COLS + 1;
		showtext (-(cy - toprow + 1));
	}

	if (t != toprow && c != cy) {
		showtext (0);
		putcursor ();
		refresh ();
	}
	while (mygetch () != ERR);
}


int
getlinenum (struct line *l)
{
	int     i;

	for (i = 0; l; l = l->next, i++);
	return numlines - i + 1;
}


void
counttext ()
{
	struct line *l;

	numlines = 0;
	numbytes = 0;
	for (l = first; l; l = l->next) {
		numlines++;
		numbytes += strlen (l->text) + 1;
	}
}


char   *
getstg (char *def, int maxlen)
{
	int     startx, starty;
	int     cp = 0;
	int     erase = 1;
	static char text[1024];
	int     c, draw = 1;

	getyx (stdscr, starty, startx);

	strcpy (text, def);
	cp = strlen (text);
	for (;;) {
		if (draw) {
			draw = 0;
			move (starty, startx);
			cleartoeol ();
			mvaddstr (starty, startx, text);
			move (starty, startx + cp);
			refresh ();
		}
		while ((c = mygetch ()) == ERR)
			usleep (20000);
		if (c == 3 || c == 27) {
			strcpy (text, "X");
			return text;
		}

		switch (c) {
		case 10:
		case 13:
			return text;
		case 8:
		case 127:
		case KEY_BACKSPACE:
			if (cp) {
				strcpy (&text[cp - 1], &text[cp]);
				cp--;
				draw = 1;
			}
			break;
		case CTRL ('D'):
			if (erase) {
				erase = 0;
				text[0] = cp = 0;
				draw = 1;
			} else {
				strcpy (&text[cp], &text[cp + 1]);
				draw = 1;
				break;
			}
		case CTRL ('B'):
		case KEY_LEFT:
			if (cp) {
				cp--;
				draw = 1;
			}
			erase = 0;
			break;
		case CTRL ('F'):
		case KEY_RIGHT:
			if (cp < strlen (text)) {
				cp++;
				draw = 1;
			}
			erase = 0;
			break;
		case CTRL ('A'):
		case KEY_HOME:
			cp = 0;
			draw = 1;
			erase = 0;
			break;
		case CTRL ('E'):
		case KEY_END:
			cp = strlen (text);
			draw = 1;
			erase = 0;
			break;
		default:
			if (erase) {
				erase = 0;
				text[0] = cp = 0;
			}
			if (strlen (text) < maxlen && c >= 32 && c <= 255) {
				char    temp[1024];

				strcpy (temp, &text[cp]);
				text[cp++] = c;
				text[cp] = 0;
				strcat (text, temp);
				draw = 1;
			}
		}
	}
}


static int colorxl[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };


void
printansi (char *s)
{
	unsigned char c;
	char    parms[1024], *cp, *ep;
	int     state = 0, len = 0, n, y, x, sx = 0, sy = 0;
	int     fg = 7, bg = 0, bold = 0, a = 0x07;
	char   *msg_buffer = s;
	int     cursorx, cursory;

	attr (a);
	while ((c = *msg_buffer++) != 0) {
		if (c == 13)
			continue;
		if (c == 27 && !state)
			state = 1;
		else if (c == '\n') {
			getyx (stdscr, cursory, cursorx);
			move (cursory = cursory + 1, cursorx = 0);
		} else if (c == '[' && state == 1) {
			state = 2;
			len = 0;
			parms[0] = 0;
		} else if (state == 2) {
			if (isdigit (c) || c == ';') {
				parms[len++] = c;
				parms[len] = 0;
				parms[len + 1] = 0;
				len = len % 77;
			} else {
				state = 0;
				switch (c) {
				case 'A':
					n = atoi (parms);
					if (!n)
						n++;
					getyx (stdscr, cursory, cursorx);
					move (cursory - n, cursorx);
					break;
				case 'B':
					n = atoi (parms);
					if (!n)
						n++;
					getyx (stdscr, cursory, cursorx);
					move (min (LINES, cursory + n),
					      cursorx);
					break;
				case 'C':
					n = atoi (parms);
					if (!n)
						n++;
					getyx (stdscr, cursory, cursorx);
					move (cursory,
					      min (COLS, cursorx + n));
					break;
				case 'D':
					n = atoi (parms);
					if (!n)
						n++;
					getyx (stdscr, cursory, cursorx);
					move (cursory, cursorx - n);
					break;
				case 'H':
					x = y = 0;
					sscanf (parms, "%d;%d", &x, &y);
					if (x)
						x--;
					if (y)
						y--;
					move (x, y);
					break;
				case 'J':
					clear ();
					move (0, 0);
					break;
				case 'K':
					cleartoeol ();
					break;
					{
						int     i;

						getyx (stdscr, cursory,
						       cursorx);
						for (i = cursorx; i < COLS;
						     i++)
							addch (' ');
						move (cursory, cursorx);
					}
					break;
				case 'm':
					cp = ep = parms;
					while (*cp) {
						while (*ep && *ep != ';')
							ep++;
						*(ep++) = 0;
						n = atoi (cp);
						switch (n) {
						case 0:
							attr (a = 0x07);
							fg = 7;
							bg = 0;
							bold = 0;
							break;
						case 1:
							a |= 0x08;
							attr (a);
							bold = 1;
							break;
						case 2:
							a &= ~0x08;
							attr (a);
							break;
						case 4:
							a &= ~0x07;
							a |= 0x01;
							attr (a);
							fg = 4;
							break;
						case 5:
							a |= 0x80;
							attron (A_BLINK);
							break;
						case 7:
							{
								int     f =
								    (a & 0x07)
								    << 4;
								int     b =
								    (a & 0x70)
								    >> 4;
								a &= ~0x77;
								a |= f + b;
								attr (a);
								n = fg;
								fg = bg;
								bg = n;
							}
							break;
						case 21:
						case 22:
							a &= ~0x08;
							attr (a);
							bold = 0;
							break;
						case 25:
							a &= ~0x80;
							attr (a);
							break;
						default:
							if (n >= 30 && n <= 37) {
								fg = colorxl[n
									     -
									     30];
								a &= ~0x07;
								a |= fg;
								attr (a);
							} else if (n >= 40 &&
								   n <= 47) {
								bg = (colorxl
								      [n -
								       40]) <<
								    4;
								a &= ~0x70;
								a |= bg;
								attr (a);
							}
						}
						cp = ep;
					}
					break;
				case 's':
					getyx (stdscr, cursory, cursorx);
					sx = cursorx;
					sy = cursory;
					break;
				case 'u':
					move (sy, sx);
					break;
				}
			}
		} else if (!state)
			addch (c);
	}
}


attr_t
attr (int cga_attr)
{
	int     fg = cga_attr & 0x07;
	int     bg = (cga_attr & 0x70) >> 4;

	attrset (0);
	if (fg == 0 && bg == 0 && (cga_attr & 8)) {
		if (cga_attr & 0x80)
			attron (A_BLINK);
		attron (COLOR_PAIR (7) + A_DIM);
	} else {
		if (cga_attr & 0x08)
			attron (A_BOLD);
		if (cga_attr & 0x80)
			attron (A_BLINK);
		attron (COLOR_PAIR ((bg * 8 + fg)));
	}

	return getattrs (stdscr);
}


void
cleartoeol ()
{
	int     i, y, x;

	getyx (stdscr, y, x);
	for (i = x; i < COLS; i++)
		addch (' ');
	move (y, x);
}


void
maskblock (int x1, int y1, int x2, int y2, unsigned char a)
{
	int     y;
	attr_t  ca;

	if (x1 < 0 && x2 < 0)
		return;
	if (x1 >= COLS && x2 >= COLS)
		return;
	if (y1 < 0 && y2 < 0)
		return;
	if (y1 >= LINES && y2 >= LINES)
		return;
	x1 = min (COLS - 1, max (0, x1));
	y1 = min (LINES - 1, max (0, y1));
	x2 = min (COLS - 1, max (0, x2));
	y2 = min (LINES - 1, max (0, y2));

	ca = attr (a);
	for (y = y1; y <= y2; y++) {
#if 0
		for (x = x1; x <= x2; x++) {
			mvaddch (y, x,
				 (unsigned char) (stdscr->_line[y].
						  text[x] & 0xff));
		}
#endif

		mvchgat (y, x1, x2 - x1 + 1,
			 ca & A_ATTRIBUTES,
			 PAIR_NUMBER (ca),
			 NULL);
	}
}


/* End of File */
