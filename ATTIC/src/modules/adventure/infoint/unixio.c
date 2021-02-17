/*****************************************************************************\
 **                                                                         **
 **  FILE:     unixio.c                                                     **
 **  AUTHORS:  Mark Howell (howell_ma@movies.enet.dec.com)                  **
 **            Alexios (porting to Megistos, adding some bells & whistles)  **
 **  PURPOSE:  Run Infocom games in a nice BBS environment.                 **
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
 **                                                                         **
 **  ORIGINAL CONDITION OF USE:                                             **
 **                                                                         **
 **  You are expressly forbidden to use this program if in so doing you     **
 **  violate the copyright notice supplied with the original Infocom game.  **
 **                                                                         **
 **  LICENSE AGREEMENT:                                                     **
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
 * $Id: unixio.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: unixio.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/24 20:30:29  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:15  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/08/13 16:59:43  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id: unixio.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";




#define WANT_TERMIOS_H 1
#define WANT_SIGNAL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_TIME_H 1
#include <megistos/bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_adventure.h"

#include "ztypes.h"


static int current_row = 1;
static int current_col = 1;
static int saved_row;
static int saved_col;
static int cursor_saved = OFF;


#define BELL 7


static int wait_for_char ();
static int read_key ();

extern int tgetent ();
extern int tgetnum ();
extern char *tgetstr ();
extern char *tgoto ();
extern void tputs ();



void
initialize_screen ()
{
	/*  int row, col; */

	if (screen_cols == 0)
		screen_cols = DEFAULT_COLS;
	if (screen_rows == 0)
		screen_rows = DEFAULT_ROWS;
	clear_screen ();

	/*  
	   row = screen_rows / 2;
	   col = (screen_cols - (sizeof ("The story is loading...") - 1)) / 2;
	   move_cursor (row, col);
	   display_string ("The story is loading..."); fflush (stdout);
	 */

	h_interpreter = INTERP_MSDOS;	/* Alexios: no, we most certainly are NOT! :-) */
}



void
restart_screen ()
{
	cursor_saved = OFF;
	if (h_type < V4) {
		set_byte (H_CONFIG, (get_byte (H_CONFIG) | CONFIG_WINDOWS));
	} else {
		set_byte (H_CONFIG,
			  (get_byte (H_CONFIG) | CONFIG_EMPHASIS |
			   CONFIG_WINDOWS));
	}


	/* Force graphics off as we can't do them */

	set_word (H_FLAGS, (get_word (H_FLAGS) & (~GRAPHICS_FLAG)));

}



void
reset_screen ()
{
	delete_status_window ();
	select_text_window ();
	set_attribute (NORMAL);
}



void
clear_screen ()
{
	print ("\e[H\e[2J");
	current_row = 1;
	current_col = 1;
}



void
select_status_window ()
{
	save_cursor_position ();
}



void
select_text_window ()
{
	/* For simplicity in handling BBS global commands and other I/O, the
	   cursor is always at the bottom of the text window. It looks a bit
	   awkward on very large text consoles like my current 144x54, but
	   it does simplify things massively and most people won't even
	   notice. */

	/* restore_cursor_position(); */
	print ("\e[%d;1H\e[K", screen_rows);
	current_row = screen_rows;
}



void
create_status_window ()
{
	move_cursor (screen_rows - 1, 1);
}



void
delete_status_window ()
{
	int     row, col;

	get_cursor_position (&row, &col);
	print ("\e[%d;%dH", screen_rows, 1);
	move_cursor (row, col);
}



void
clear_line ()
{
	print ("\e[K");
}



void
clear_text_window ()
{
	int     i, row, col;

	get_cursor_position (&row, &col);
	for (i = status_size + 1; i <= screen_rows; i++) {
		move_cursor (i, 1);
		clear_line ();
	}
	move_cursor (row, col);
}



void
clear_status_window ()
{
	int     i, row, col;

	get_cursor_position (&row, &col);
	for (i = status_size; i; i--) {
		move_cursor (i, 1);
		clear_line ();
	}

	move_cursor (row, col);
}



void
move_cursor (int row, int col)
{
	print ("\e[%d;%dH", row, col);
	fflush (stdout);
	current_row = row;
	current_col = col;
}



void
get_cursor_position (int *row, int *col)
{
	*row = current_row;
	*col = current_col;
}



void
save_cursor_position ()
{
	if (cursor_saved == OFF) {
		get_cursor_position (&saved_row, &saved_col);
		cursor_saved = ON;
	}
}



void
restore_cursor_position ()
{
	if (cursor_saved == ON) {
		move_cursor (saved_row, saved_col);
		cursor_saved = OFF;
	}
}



void
set_attribute (int attribute)
{
	if (attribute == NORMAL) {
		print ("\e[0m");
		set_colours (0, 0);
	}

	if (attribute & REVERSE) {
		print ("\e[7m");
		set_colours (0, 0);
	}

	if (attribute & BOLD) {
		print ("\e[1m");
		set_colours (0, 0);
	}

	if (attribute & EMPHASIS) {
		print ("\e[4m");
		set_colours (0, 0);
	}

	if (attribute & FIXED_FONT) {
	}
}



#if 0
static void
display_string (char *s)
{
	/* Ye gawds, what an awful kludge! A hacky, ugly formatting system inside the
	   Megistos one. Bletcherous, but necessary as the Z-Machine can do things we
	   can't -- better format using the provided, simple thing just to be
	   sure. */

	while (*s)
		display_char (*s++);
}
#endif


void
display_char (int c)
{
	write (1, &c, 1);	/* As low as they go... Bit sluggish, though. */

	if (++current_col > screen_cols)
		current_col = screen_cols;
}



void
scroll_line ()
{
	int     row, col;

	get_cursor_position (&row, &col);
	if (row < screen_rows) {
		display_char ('\n');
	} else {
		move_cursor (status_size + 1, 1);
		print ("\e[M");
		fflush (stdout);
		move_cursor (row, 1);
	}

	current_col = 1;
	if (++current_row > screen_rows)
		current_row = screen_rows;
}



int
input_character (int timeout)
{
	struct timeval tv;
	struct timezone tz;

	gettimeofday (&tv, &tz);

	tv.tv_sec += timeout;

	fflush (stdout);

	if (timeout && wait_for_char (&tv))
		return (-1);

	return read_key ();
}



int
input_line (int buflen, char *buffer, int timeout, int *read_size)
{
	/* Since we don't know what the Z-Machine does, we take the safe approach and
	   declare the user's busy between calls to input_line. In most games, the
	   user will be available most of the time anyway. */

	thisuseronl.flags &= ~OLF_BUSY;


	/* The loop is necessary because we don't want to return blank lines to the
	   Z-Machine if the user has just used some BBS global command like
	   /#. Instead of returning the like to the game which would say something to
	   the effect of "I beg your pardon?" below each page, /#, etc, we simply
	   loop until actual inp_buffer to the game is available. For realism, a > prompt
	   is also printed. */

	do {
		inp_clearflags (INF_REPROMPT);
		if (timeout)
			inp_timeout (timeout, 0);	/* Set optional timeout */
		out_setflags (OFL_WAITTOCLEAR);
		inp_get (buflen - 1);
		out_clearflags (OFL_WAITTOCLEAR);
		if (inp_reprompt ())
			print ("\e[0m>\n");
		else if (margc == 1 && inp_isX (margv[0])) {
			int     yes;

			if ((get_bool (&yes, XCONFRM, 0, 0, 0) == 0) ||
			    (yes == 0)) {
				inp_setflags (INF_REPROMPT);
				print ("\n\e[0m>\n");
				continue;
			}
			exit (0);
		}
	} while (inp_reprompt ());


	thisuseronl.flags |= OLF_BUSY;	/* Ok, we're going busy again. */

	/* Copy the inp_buffer buffer to the Z-Machine's buffer and return it. */

	inp_raw ();
	memcpy (&buffer[*read_size], inp_buffer,
		min (strlen (inp_buffer), buflen - strlen (inp_buffer)));
	*read_size += strlen (inp_buffer);
	scroll_line ();
	return '\r';
}



static int
wait_for_char (struct timeval *timeout)
{
	int     nfds, status;
	fd_set  readfds;
	struct timeval tv;
	struct timezone tz;

	/* UGLY code, this */

	gettimeofday (&tv, &tz);

	if (tv.tv_sec >= timeout->tv_sec && tv.tv_usec >= timeout->tv_usec)
		return (-1);

	tv.tv_sec = timeout->tv_sec - tv.tv_sec;
	if (timeout->tv_usec < tv.tv_usec) {
		tv.tv_sec--;
		tv.tv_usec = (timeout->tv_usec + 1000000) - tv.tv_usec;
	} else {
		tv.tv_usec = timeout->tv_usec - tv.tv_usec;
	}

	nfds = getdtablesize ();
	FD_ZERO (&readfds);
	FD_SET (fileno (stdin), &readfds);

	status = select (nfds, &readfds, NULL, NULL, &tv);
	if (status < 0) {
		perror ("select");
		return (-1);
	}

	if (status == 0)
		return (-1);
	else
		return (0);
}



static int
read_key ()
{
	char    c;

	/* Plain single character entry for key-for-key interaction */

	read (0, &c, 1);
	if (c == 127)
		c = '\b';
	else if (c == '\n')
		c = '\r';
	return c;
}


/* End of File */
