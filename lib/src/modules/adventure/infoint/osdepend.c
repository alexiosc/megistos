/*****************************************************************************\
 **                                                                         **
 **  FILE:     osdepend.c                                                   **
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
 * $Id$
 *
 * $Log$
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
    "$Id$";

/*
 * osdepend.c
 *
 * All non screen specific operating system dependent routines.
 *
 * Olaf Barthel 28-Jul-1992
 *
 */

#include <stdlib.h>
#include <unistd.h>
#include <bbs.h>

#include <megistos/ztypes.h>



char   *storybasename;



/* File names will be O/S dependent */

#define SAVE_NAME   "story.sav"	/* Default save name */
#define SCRIPT_NAME "story.lis"	/* Default script name */
#define RECORD_NAME "record.lis"	/* Default record name */



/*
 * process_arguments
 *
 * Do any argument preprocessing necessary before the game is
 * started. This may include selecting a specific game file or
 * setting interface-specific options.
 *
 */

void
process_arguments (int argc, char *argv[])
{
	int     c, errflg = 0;

	/* Parse the options */

	while ((c = getopt (argc, argv, "hl:c:r:t:")) != EOF) {
		switch (c) {
		case 'l':	/* lines */
			screen_rows = atoi (optarg);
			break;
		case 'c':	/* columns */
			screen_cols = atoi (optarg);
			break;
		case 'r':	/* right margin */
			right_margin = atoi (optarg);
			break;
		case 't':	/* top margin */
			top_margin = atoi (optarg);
			break;
		case 'h':
		case '?':
		default:
			errflg++;
		}
	}

	/* Display usage */

	if (errflg || optind >= argc) {
		fprintf (stderr, "usage: %s [options...] story-file\n\n",
			 argv[0]);
		fprintf (stderr,
			 "%s - an Infocom story file interpreter. Version 2.0 by Mark Howell\n",
			 argv[0]);
		fprintf (stderr,
			 "Linux patches by: Sander van Malssen & Neptho T.\n");
		fprintf (stderr, "Megistos port by: Alexios Chouchoulas.\n");
		fprintf (stderr, "Plays type 1 to 5 Infocom games.\n\n");
		fprintf (stderr, "\t-l n lines in display\n");
		fprintf (stderr, "\t-c n columns in display\n");
		fprintf (stderr, "\t-r n text right margin (default = %d)\n",
			 DEFAULT_RIGHT_MARGIN);
		fprintf (stderr, "\t-t n text top margin (default = %d)\n",
			 DEFAULT_TOP_MARGIN);
		exit (1);
	}

	/* Strip leading directories */
	if ((storybasename = strrchr (argv[optind], '/')))
		storybasename++;
	else
		storybasename = argv[optind];

	/* Open the story file */
	open_story (argv[optind]);
}



/*
 * file_cleanup
 *
 * Perform actions when a file is successfully closed. Flag can be one of:
 * GAME_SAVE, GAME_RESTORE, GAME_SCRIPT.
 *
 */

void
file_cleanup (const char *file_name, int flag)
{
	/* or maybe not. :-) */
}


/*
 * sound
 *
 * Play a sound file or a note.
 *
 * argc = 1: argv[0] = note# (range 1 - 3)
 *
 *           Play note.
 *
 * argc = 2: argv[0] = 0
 *           argv[1] = 3
 *
 *           Stop playing current sound.
 *
 * argc = 2: argv[0] = 0
 *           argv[1] = 4
 *
 *           Free allocated resources.
 *
 * argc = 3: argv[0] = ID# of sound file to replay.
 *           argv[1] = 2
 *           argv[2] = Volume to replay sound with, this value
 *                     can range between 1 and 8.
 *
 * argc = 4: argv[0] = ID# of sound file to replay.
 *           argv[1] = 2
 *           argv[2] = Control information
 *           argv[3] = Volume information
 *
 *           Volume information:
 *
 *               0x34FB -> Fade sound in
 *               0x3507 -> Fade sound out
 *               other  -> Replay sound at maximum volume
 *
 *           Control information:
 *
 *               This word is divided into two bytes,
 *               the upper byte determines the number of
 *               cycles to play the sound (e.g. how many
 *               times a clock chimes or a dog barks).
 *               The meaning of the lower byte is yet to
 *               be discovered :)
 *
 */

void
sound (int argc, zword_t * argv)
{

	/* Supply default parameters */

	if (argc < 4)
		argv[3] = 0;
	if (argc < 3)
		argv[2] = 0xff;
	if (argc < 2)
		argv[1] = 2;

	/* Generic bell sounder */

	if (argc == 1 || argv[1] == 2)
		display_char ('\007');
}



/*
 * get_file_name
 *
 * Return the name of a file. Flag can be one of:
 *    GAME_SAVE    - Save file (write only)
 *    GAME_RESTORE - Save file (read only)
 *    GAME_SCRIPT  - Script file (write only)
 *    GAME_RECORD  - Keystroke record file (write only)
 *    GAME_PLABACK - Keystroke record file (read only)
 *
 */

int
get_file_name (char *file_name, char *default_name, int flag)
{
	char    buffer[127 + 2];	/* 127 is the biggest positive char */
	int     status = 0;

	/* If no default file name then supply the standard name */

	if (default_name[0] == '\0') {
		if (flag == GAME_SCRIPT) {
			strcpy (default_name, SCRIPT_NAME);
		} else if (flag == GAME_RECORD || flag == GAME_PLAYBACK) {
			strcpy (default_name, RECORD_NAME);
		} else		/* (flag == GAME_SAVE || flag == GAME_RESTORE) */
			strcpy (default_name, storybasename);
		strcat (default_name, ".sav");
	}


	/* Prompt for the file name */

	output_line ("Enter a file name.");
	output_string ("(Default is \"");
	output_string (default_name);
	output_string ("\"): ");

	buffer[0] = 127;
	buffer[1] = 0;
	(void) get_line (buffer, 0, 0);


	/* Copy file name from the inp_buffer buffer */

	strcpy (file_name, (h_type > V4) ? &buffer[2] : &buffer[1]);


	/* If nothing typed then use the default name */

	if (file_name[0] == '\0')
		strcpy (file_name, default_name);


	/* Check if we are going to overwrite the file */

	if (flag == GAME_SAVE || flag == GAME_SCRIPT || flag == GAME_RECORD) {
		FILE   *tfp;
		char    c;

		/* Try to access the file */

		tfp = fopen (file_name, "r");
		if (tfp != NULL) {
			fclose (tfp);

			/* If it succeeded then prompt to overwrite */

			output_line
			    ("You are about to write over an existing file.");
			output_string ("Proceed? (Y/N) ");

			do {
				c = (char) input_character (0);
				c = (char) toupper (c);
			} while (c != 'Y' && c != 'N');

			output_char (c);
			output_new_line ();

			/* If no overwrite then fail the routine */

			if (c == 'N')
				status = 1;
		}
	}


	{
		char   *cp;

		for (cp = file_name; *cp; cp++)
			if (*cp == '/')
				*cp = '_';
	}


	/* Record the file name if it was OK */

	if (status == 0)
		record_line (file_name);

	return (status);

}



/*
 * fit_line
 *
 * This routine determines whether a line of text will still fit
 * on the screen.
 *
 * line : Line of text to test.
 * pos  : Length of text line (in characters).
 * max  : Maximum number of characters to fit on the screen.
 *
 */

int
fit_line (const char *line_buffer, int pos, int max)
{
	return (pos < max);
}



/*
 * print_status
 *
 * Print the status line (type 3 games only).
 *
 * argv[0] : Location name
 * argv[1] : Moves/Time
 * argv[2] : Score
 *
 * Depending on how many arguments are passed to this routine
 * it is to print the status line. The rendering attributes
 * and the status line window will be have been activated
 * when this routine is called. It is to return FALSE if it
 * cannot render the status line in which case the interpreter
 * will use display_char() to render it on its own.
 *
 * This routine has been provided in order to support
 * proportional-spaced fonts.
 *
 */

int
print_status (int argc, char *argv[])
{
	return (FALSE);
}



/*
 * set_font
 *
 * Set a new character font. Font can be either be:
 *
 *    TEXT_FONT (1)     = normal text character font
 *    GRAPHICS_FONT (3) = graphical character font
 *
 */

void
set_font (int font_type)
{
}



/*
 * set_colours
 *
 * Sets screen foreground and background colours.
 *
 */

static int fg, bg;

void
set_colours (int foreground, int background)
{
	if (foreground > 0) {
		fg = foreground;
		bg = background;
		if (fg == 1)
			fg = 7;
		else
			fg--;
		if (bg == 1)
			bg = 0;
		else
			bg--;
	}
	print ("\e[%d;%dm", 29 + fg, 39 + bg);
}



/*
 * codes_to_text
 *
 * Translate Z-code characters to machine specific characters. These characters
 * include line drawing characters and international characters.
 *
 * The routine takes one of the Z-code characters from the following table and
 * writes the machine specific text replacement. The target replacement buffer
 * is defined by MAX_TEXT_SIZE in ztypes.h. The replacement text should be in a
 * normal C, zero terminated, string.
 *
 * Return 0 if a translation was available, otherwise 1.
 *
 *  Arrow characters (0x18 - 0x1b):
 *
 *  0x18 Up arrow
 *  0x19 Down arrow
 *  0x1a Right arrow
 *  0x1b Left arrow
 *
 *  International characters (0x9b - 0xa3):
 *
 *  0x9b a umlaut (ae)
 *  0x9c o umlaut (oe)
 *  0x9d u umlaut (ue)
 *  0x9e A umlaut (Ae)
 *  0x9f O umlaut (Oe)
 *  0xa0 U umlaut (Ue)
 *  0xa1 sz (ss)
 *  0xa2 open quote (>>)
 *  0xa3 close quota (<<)
 *
 *  Line drawing characters (0xb3 - 0xda):
 *
 *  0xb3 vertical line (|)
 *  0xba double vertical line (#)
 *  0xc4 horizontal line (-)
 *  0xcd double horizontal line (=)
 *  all other are corner pieces (+)
 *
 */

int
codes_to_text (int c, char *s)
{
	return c;
}


/* End of File */


/* End of File */
