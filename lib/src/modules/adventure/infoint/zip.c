/*****************************************************************************\
 **                                                                         **
 **  FILE:     zip.c                                                        **
 **  AUTHORS:  Mark Howell (howell_ma@movies.enet.dec.com)                  **
 **            Alexios (porting to Megistos, adding some bells & whistles)  **
 **  PURPOSE:  Run Infocom games in a nice BBS environment.                 **
 **  NOTES:    Please read author's comments below this banner              **
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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/08/13 16:59:43  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif

/*
 * zip.c
 *
 * Z code interpreter main routine. Plays Infocom type 1, 2, 3, 4 and 5 games.
 *
 * Usage: zip [options] story-file-name
 *
 * options are:
 *
 *    -l n - number of lines in display
 *    -c n - number of columns in display
 *    -r n - right margin (default = 0)
 *    -t n - top margin (default = 0)
 *
 * This is a no bells and whistles Infocom interpreter for type 1 to 5 games.
 * It will automatically detect which type of game you want to play. It should
 * support all type 1 to 5 features and is based loosely on the MS-DOS version
 * with enhancements to aid portability. Read the readme.1st file for
 * information on building this program on your favourite operating system.
 * Please mail me, at the address below, if you find bugs in the code.
 *
 * Special thanks to David Doherty and Olaf Barthel for testing this program
 * and providing invaluable help and code to aid its portability.
 *
 * Mark Howell 10-Mar-93 V2.0 howell_ma@movies.enet.dec.com
 *
 * Disclaimer:
 *
 * You are expressly forbidden to use this program if in so doing you violate
 * the copyright notice supplied with the original Infocom game.
 *
 */



#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include <bbs.h>
#include "ztypes.h"



static void configure (zbyte_t, zbyte_t);



void
done()
{
  mod_done(INI_ALL);
  exit(0);
}



void
settermios()
{
  static struct termios setterm;
  
  tcgetattr(0,&setterm);
  
  /* Cause Ctrl-C to generate SIGINT */
  
  setterm.c_lflag|=ISIG;
  setterm.c_cc[VINTR]=3;
  setterm.c_cc[VMIN]=1;
  
  /* Set the terminal */
  
  tcsetattr(0,TCSANOW,&setterm);
  tcsetattr(1,TCSANOW,&setterm);
  tcsetattr(2,TCSANOW,&setterm);
}



promptblock_t *msg;


static void
init()
{
  mod_init(INI_ALL);
  msg=msg_open("adventure");
  msg_setlanguage(thisuseracc.language);
  screen_cols=thisuseracc.scnwidth;
  screen_rows=thisuseracc.scnheight;
  settermios();
  signal(SIGINT,done);
  out_clearflags(OFL_WAITTOCLEAR);
}



/*
 * main
 *
 * Initialise environment, start interpreter, clean up.
 *
 */


int main (int argc, char *argv[])
{
  init();
  process_arguments (argc, argv);
  configure (V1, V8);
  initialize_screen ();
  load_cache ();
  restart ();
  interpret ();
  unload_cache ();
  close_story ();
  close_script ();
  return 0;
}



/*
 * configure
 *
 * Initialise global and type specific variables.
 *
 */

static void configure (zbyte_t min_version, zbyte_t max_version)
{
  zbyte_t header[PAGE_SIZE];
  
  read_page (0, header);
  datap = header;
  
  h_type = get_byte (H_TYPE);

  /* Hack, add support for V6 (?) V7 and V8 games. */
  if (h_type == 6) { h_type=V5; story_scaler = 6; }
  if (h_type == 7) { h_type=V5; story_scaler = 7; }
  if (h_type == 8) { h_type=V5; story_scaler = 8; }

  if (h_type < min_version || h_type > max_version ||
      (get_byte (H_CONFIG) & CONFIG_BYTE_SWAPPED))
    error_fatal("Wrong game or version.");
  
  if (h_type < V4) {
    story_scaler = 2;
    story_shift = 1;
    property_mask = P3_MAX_PROPERTIES - 1;
    property_size_mask = 0xe0;
  } else {
    story_scaler = 4;
    story_shift = 2;
    property_mask = P4_MAX_PROPERTIES - 1;
    property_size_mask = 0x3f;
  }
  
  h_config = get_byte (H_CONFIG);
  h_version = get_word (H_VERSION);
  h_data_size = get_word (H_DATA_SIZE);
  h_start_pc = get_word (H_START_PC);
  h_words_offset = get_word (H_WORDS_OFFSET);
  h_objects_offset = get_word (H_OBJECTS_OFFSET);
  h_globals_offset = get_word (H_GLOBALS_OFFSET);
  h_restart_size = get_word (H_RESTART_SIZE);
  h_flags = get_word (H_FLAGS);
  h_synonyms_offset = get_word (H_SYNONYMS_OFFSET);
  h_file_size = get_word (H_FILE_SIZE);
  if (h_file_size == 0)
    h_file_size = get_story_size ();
  h_checksum = get_word (H_CHECKSUM);
  h_alternate_alphabet_offset = get_word (H_ALTERNATE_ALPHABET_OFFSET);
  
  datap = NULL;
}
