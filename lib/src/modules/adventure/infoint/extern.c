/*****************************************************************************\
 **                                                                         **
 **  FILE:     extern.c                                                     **
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
 * Revision 1.5  2003/12/24 20:30:30  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:16  alexios
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
 * extern.c
 *
 * Global data.
 *
 */

#include "ztypes.h"

/* Game header data */

zbyte_t h_type = 0;
zbyte_t h_config = 0;
zword_t h_version = 0;
zword_t h_data_size = 0;
zword_t h_start_pc = 0;
zword_t h_words_offset = 0;
zword_t h_objects_offset = 0;
zword_t h_globals_offset = 0;
zword_t h_restart_size = 0;
zword_t h_flags = 0;
zword_t h_synonyms_offset = 0;
zword_t h_file_size = 0;
zword_t h_checksum = 0;
zbyte_t h_interpreter = INTERP_MSDOS;
zbyte_t h_interpreter_version = 'B';	/* Interpreter version 2 */
zword_t h_alternate_alphabet_offset = 0;

/* Game version specific data */

int     story_scaler = 0;
int     story_shift = 0;
int     property_mask = 0;
int     property_size_mask = 0;

/* Stack and PC data */

zword_t stack[STACK_SIZE];
zword_t sp = STACK_SIZE;
zword_t fp = STACK_SIZE - 1;
unsigned long pc = 0;
int     interpreter_state = RUN;
int     interpreter_status = 0;

/* Data region data */

unsigned int data_size = 0;
zbyte_t *datap = NULL;
zbyte_t *undo_datap = NULL;

/* Screen size data */

int     screen_rows = 0;
int     screen_cols = 0;
int     right_margin = DEFAULT_RIGHT_MARGIN;
int     top_margin = DEFAULT_TOP_MARGIN;

/* Current window data */

int     screen_window = TEXT_WINDOW;

/* Formatting and output control data */

int     formatting = ON;
int     outputting = ON;
int     redirecting = OFF;
int     scripting_disable = OFF;
int     scripting = OFF;
int     recording = OFF;
int     replaying = OFF;
int     font = 1;

/* Status region data */

int     status_active = OFF;
int     status_size = 0;

/* Text output buffer data */

int     lines_written = 0;
int     status_pos = 0;

/* Dynamic buffer data */

char   *line = NULL;
char   *status_line = NULL;

/* Character translation tables */

char    lookup_table[3][26];


/* End of File */
