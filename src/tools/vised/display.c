/*****************************************************************************\
 **                                                                         **
 **  FILE:     display.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95, Version 0.5 alpha                               **
 **  PURPOSE:  The Visual Editor display functions                          **
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
 * $Id: display.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: display.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
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
 * Revision 0.7  1998/12/27 16:35:48  alexios
 * Added autoconf support.
 *
 * Revision 0.6  1998/08/14 12:01:28  alexios
 * No changes.
 *
 * Revision 0.5  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 10:50:43  alexios
 * Stopped using xlgetmsg() and reverted to getmst() since emud
 * now performs all translations itself.
 *
 * Revision 0.3  1997/09/12 13:41:18  alexios
 * Used xlgetmsg() to get translated prompt blocks, instead of
 * the raw ones used previously. Stopped using the visual library
 * because it was causing lots of errors -- used raw ncurses
 * instead. Performed numerous other fixes and changes to
 * accommodate for this change in libraries.
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
    "$Id: display.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";



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

static int err = 0;


void
putcursor ()
{
	move (cy - toprow + 1,
	      min (cx, current ? strlen (current->text) : 9999) - leftcol);
}


void
bel (int error)
{
	char    c = 7;

	write (0, &c, 1);
	err = error;
	if (error) {
		move (0, 0);
		switch (error) {
		default:
			printansi (msg_get (error));
		}
	}
}


void
showstatus ()
{
	char    line[1024];

	if (!err) {
		move (0, 0);
		sprintf (line, statust,
			 min (cx + 1,
			      current ? max (1,
					     strlen (current->text)) : 9999),
			 cy, numbytes, maxsize, stins[insertmode],
			 stformat[formatmode], rmargin);
		printansi (line);
	}
	err = 0;

	move (LINES - 2, 0);
	switch (metamode) {
	case 1:
		printansi (statusm);
		break;
	case 2:
		printansi (statuso);
		break;
	case 3:
		printansi (statusk);
		break;
	default:
		printansi (statusb);
	}

	putcursor ();
	refresh ();
}


void
showtext (int num)
{
	struct line *l;
	int     i;
	char    line[1024];

	for (i = 1, l = top; l && i < LINES - 2; l = l->next, i++) {
		int     j, ln = i + toprow - 1;

		if (leftcol && (i == (cy - toprow + 1))) {
			strcpy (line, &(l->text[leftcol]));
			line[COLS] = 0;
		} else
			strncpy (line, l->text, COLS + 1);

		attr (cfgtxt + (cbgtxt << 4));
		for (j = 0; line[j] && j < qtemaxc; j++)
			if (strchr (qtechrs, line[j])) {
				attr (cfgqte + (cbgqte << 4));
				break;
			}

		move (i, 0);
		if (!num || (i == num) || ((num < 0) && ((-num) <= i))) {
			int     j;

			cleartoeol ();
			for (j = 0; line[j]; j++)
				if (line[j] >= 0 && line[j] < 32)
					line[j] = '?';
			mvaddstr (i, 0, line);
			if (BLOCK) {
				int     a = cfgblk + (cbgblk << 4);

				if (ln == kby && kbx < strlen (line))
					maskblock (kbx, i,
						   (kby ==
						    kky) ? kkx -
						   1 : strlen (line) - 1, i,
						   a);
				else if (ln > kby && (ln == kky - (kkx == 0))
					 && kkx)
					maskblock (0, i, kkx - 1, i, a);
				else if (ln > kby && ln <= kky - 1 &&
					 strlen (line))
					maskblock (0, i, strlen (line) - 1, i,
						   a);
			}
			if (fl && ln == fy)
				maskblock (fx, i, fx + fl - 1, i,
					   cfgfnd + (cbgfnd << 4));

		}
		attr (cfgtxt + (cbgtxt << 4));
	}

	attr (cfgtxt + (cbgtxt << 4));
	if (!num)
		for (; i < LINES - 2; i++) {
			move (i, 0);
			cleartoeol ();
		}

	putcursor ();
	refresh ();
}


void
noblock ()
{
	int     i = BLOCK;

	kby = kky = 1;
	kbx = kkx = 0;
	if (i)
		showtext (0);
}


/* End of File */
