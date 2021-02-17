/*****************************************************************************\
 **                                                                         **
 **  FILE:     help.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 94                                               **
 **  PURPOSE:  Display help when in visual mode                             **
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
 * $Id: help.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: help.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/05/22 19:29:39  alexios
 * Added a workaround for a TERMIOS bug that corrupts the TERMIOS when
 * field help is shown.
 *
 * Revision 1.5  2003/12/24 18:32:08  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 16:30:50  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:29:41  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:02:58  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:35:04  alexios
 * Added the fieldhelp() function.
 *
 * Revision 0.1  1997/08/28 11:21:38  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: help.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_NCURSES_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "bbsdialog.h"
#include "mbk_bbsdialog.h"


static void
showhelp (WINDOW * win)
{
	unsigned char c;
	char    parms[80], *cp, *ep;
	int     state = 0, len = 0, n, y, x, sx = 0, sy = 0;
	int     fg = 7, bg = 0, bold = 0;
	char   *bufp = msg_get (VHELP);

	while (*bufp) {
		c = *bufp++;
		if (c == 13)
			continue;
		if (c == 27 && !state)
			state = 1;
		else if (c == '[' && state == 1) {
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
					getyx (win, y, x);
					wmove (win, y - n, x);
					break;
				case 'B':
					n = atoi (parms);
					if (!n)
						n++;
					getyx (win, y, x);
					wmove (win, y + n, x);
					break;
				case 'C':
					n = atoi (parms);
					if (!n)
						n++;
					getyx (win, y, x);
					wmove (win, y, x + n);
					break;
				case 'D':
					n = atoi (parms);
					if (!n)
						n++;
					getyx (win, y, x);
					wmove (win, y, x - n);
					break;
				case 'H':
					x = y = 0;
					sscanf (parms, "%d;%d", &x, &y);
					if (x)
						x--;
					if (y)
						y--;
					wmove (win, y, x);
					break;
				case 'J':
					werase (win);
					wmove (win, 0, 0);
					break;
				case 'K':
					wclrtoeol (win);
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
							wattrset (win, 0);
							fg = 7;
							bg = 0;
							bold = 0;
							break;
						case 1:
							wattron (win, A_BOLD);
							bold = 1;
							break;
						case 2:
							wattroff (win, A_BOLD);
							break;
						case 4:
							wattron (win,
								 A_UNDERLINE);
							fg = 4;
							break;
						case 5:
							wattron (win, A_BLINK);
							break;
						case 7:
							wattron (win,
								 A_REVERSE);
							n = fg;
							fg = bg;
							bg = n;
							break;
						case 21:
						case 22:
							wattron (win, A_BOLD);
							bold = 0;
							break;
						case 24:
							wattroff (win,
								  A_UNDERLINE);
							break;
						case 25:
							wattroff (win,
								  A_BLINK);
							break;
						case 27:
							wattroff (win,
								  A_REVERSE);
							n = fg;
							fg = bg;
							bg = n;
							break;
						default:
							if (n >= 30 && n <= 37) {
								fg = n - 30;
								wattron (win,
									 COLOR_PAIR
									 ((bg *
									   8 +
									   fg)));
							} else if (n >= 40 &&
								   n <= 47) {
								bg = n - 40;
								wattron (win,
									 COLOR_PAIR
									 ((bg *
									   8 +
									   fg)));
							}
						}
						cp = ep;
					}
					break;
				case 's':
					getyx (win, sy, sx);
					break;
				case 'u':
					wmove (win, sy, sx);
					break;
				}
			}
		} else if (!state)
			waddch (win, c);
	}
}

void
visualhelp ()
{
	WINDOW *helpwin = newwin (0, 0, 0, 0);

	wattrset (stdscr, A_NORMAL);
	attrset (A_NORMAL);
	wattrset (helpwin, A_NORMAL);
	wmove (helpwin, 0, 0);
/*  addch(32);
  refresh(); */
/*  touchwin(helpwin); */
/*  wclear(helpwin); */

	msg_set (msg);
	showhelp (helpwin);
	msg_reset ();

	wrefresh (helpwin);
	getch ();
	wattrset (helpwin, A_NORMAL);

	werase (helpwin);
	delwin (helpwin);
	touchwin (stdscr);
	wrefresh (stdscr);
	refresh ();
}


void
fieldhelp (int field)
{
	struct termios newtermios;

	tcgetattr (0, &newtermios);
	system ("stty sane");

	out_setflags (OFL_AFTERINPUT);
	print ("\033[2J");
	msg_set (msg);
	prompt (FHHDR);
	if (object[field].b.type == OBJ_BUTTON)
		prompt (FHBUTN);
	else {
		msg_set (templates);
		prompt (ltnum + 1 + field);
		msg_set (msg);
	}
	prompt (FHFTR);
	getch ();

	tcsetattr (0, TCSANOW, &newtermios);

	clearok (stdscr, 1);
	refresh ();
}


/* End of File */
