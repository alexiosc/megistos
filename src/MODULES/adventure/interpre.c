/*****************************************************************************\
 **                                                                         **
 **  FILE:     interpre.c                                                   **
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
 * Revision 1.1  2001/04/16 14:54:34  alexios
 * Initial revision
 *
 * Revision 1.0  1999/08/13 16:59:43  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif

/*
 * interpre.c
 *
 * Main interpreter loop
 *
 */

#include <bbs.h>
#include "ztypes.h"

static int halt = FALSE;

/*
 * interpret
 *
 * Interpret Z code
 *
 */

int interpret ()
{
  zbyte_t opcode;
  zword_t specifier, operand[8];
  int maxoperands, count, extended, i;
  
  interpreter_status = 1;
  
  /* Loop until HALT instruction executed */
  
  for (interpreter_state = RUN; interpreter_state == RUN && halt == FALSE; ) {
    
    /* Load opcode and set operand count */
    
    opcode = read_code_byte ();
    if (h_type > V4 && opcode == 0xbe) {
      opcode = read_code_byte ();
      extended = TRUE;
    } else
      extended = FALSE;
    count = 0;
    
    /* Multiple operand instructions */
    
    if ((opcode < 0x80 || opcode > 0xc0) || extended == TRUE) {
      
      /* Two operand class, load both operands */
      
      if (opcode < 0x80 && extended == FALSE) {
	operand[count++] = load_operand ((opcode & 0x40) ? 2 : 1);
	operand[count++] = load_operand ((opcode & 0x20) ? 2 : 1);
	opcode &= 0x1f;
      } else {
	
	/* Variable operand class, load operand specifier */
	
	opcode &= 0x3f;
	if (opcode == 0x2c || opcode == 0x3a) { /* Extended CALL instruction */
	  specifier = read_code_word ();
	  maxoperands = 8;
	} else {
	  specifier = read_code_byte ();
	  maxoperands = 4;
	}
	
	/* Load operands */
	
	for (i = (maxoperands - 1) * 2; i >= 0; i -= 2)
	  if (((specifier >> i) & 0x03) != 3)
	    operand[count++] = load_operand ((specifier >> i) & 0x03);
	  else
	    i = 0;
      }
      
      if (extended == TRUE)
	switch ((char) opcode) {
	  
	  /* Extended operand instructions */
	  
	case 0x00: save (); break;
	case 0x01: restore (); break;
	case 0x02: shift (operand[0], operand[1]); break;
	case 0x03: arith_shift (operand[0], operand[1]); break;
	case 0x04: set_font_attribute (operand[0]); break;
	  
	case 0x09: undo_save (); break;
	case 0x0a: undo_restore (); break;
	  
	default: fatal ("Illegal operation");
	}
      else
	switch ((char) opcode) {
	  
	  /* Two or multiple operand instructions */
	  
	case 0x01: compare_je (count, operand); break;
	case 0x02: compare_jl (operand[0], operand[1]); break;
	case 0x03: compare_jg (operand[0], operand[1]); break;
	case 0x04: decrement_check (operand[0], operand[1]); break;
	case 0x05: increment_check (operand[0], operand[1]); break;
	case 0x06: compare_parent_object (operand[0], operand[1]); break;
	case 0x07: test (operand[0], operand[1]); break;
	case 0x08: or (operand[0], operand[1]); break;
	case 0x09: and (operand[0], operand[1]); break;
	case 0x0a: test_attr (operand[0], operand[1]); break;
	case 0x0b: set_attr (operand[0], operand[1]); break;
	case 0x0c: clear_attr (operand[0], operand[1]); break;
	case 0x0d: store_variable (operand[0], operand[1]); break;
	case 0x0e: insert_object (operand[0], operand[1]); break;
	case 0x0f: load_word (operand[0], operand[1]); break;
	case 0x10: load_byte (operand[0], operand[1]); break;
	case 0x11: load_property (operand[0], operand[1]); break;
	case 0x12: load_property_address (operand[0], operand[1]); break;
	case 0x13: load_next_property (operand[0], operand[1]); break;
	case 0x14: add (operand[0], operand[1]); break;
	case 0x15: subtract (operand[0], operand[1]); break;
	case 0x16: multiply (operand[0], operand[1]); break;
	case 0x17: divide (operand[0], operand[1]); break;
	case 0x18: remainder (operand[0], operand[1]); break;
	case 0x19: call (count, operand, FUNCTION); break;
	case 0x1a: call (count, operand, PROCEDURE); break;
	case 0x1b: set_colour_attribute (operand[0], operand[1]); break;
	case 0x1c: unwind (operand[0], operand[1]); break;
	  
	  /* Multiple operand instructions */
	  
	case 0x20: call (count, operand, FUNCTION); break;
	case 0x21: store_word (operand[0], operand[1], operand[2]); break;
	case 0x22: store_byte (operand[0], operand[1], operand[2]); break;
	case 0x23: store_property (operand[0], operand[1], operand[2]); break;
	case 0x24: read_line (count, operand); break;
	case 0x25: print_character (operand[0]); break;
	case 0x26: print_number (operand[0]); break;
	case 0x27: zip_random (operand[0]); break;
	case 0x28: push_var (operand[0]); break;
	case 0x29: pop_var (operand[0]); break;
	case 0x2a: set_status_size (operand[0]); break;
	case 0x2b: select_window (operand[0]); break;
	case 0x2c: call (count, operand, FUNCTION); break;
	case 0x2d: erase_window (operand[0]); break;
	case 0x2e: erase_line (operand[0]); break;
	case 0x2f: set_cursor_position (operand[0], operand[1]); break;
	  
	case 0x31: set_video_attribute (operand[0]); break;
	case 0x32: set_format_mode (operand[0]); break;
	case 0x33: set_print_modes (operand[0], operand[1]); break;
	case 0x34: open_playback (operand[0]); break;
	case 0x35: sound (count, operand); break;
	case 0x36: read_character (count, operand); break;
	case 0x37: scan_data (count, operand); break;
	case 0x38: not (operand[0]); break;
	case 0x39: call (count, operand, PROCEDURE); break;
	case 0x3a: call (count, operand, PROCEDURE); break;
	case 0x3b: tokenise (count, operand); break;
	case 0x3c: encode (operand[0], operand[1], operand[2], operand[3]); break;
	case 0x3d: move_data (operand[0], operand[1], operand[2]); break;
	case 0x3e: print_window (count, operand); break;
	case 0x3f: check_argument (operand[0]); break;
	  
	default: fatal ("Illegal operation");
	}
    } else {
      
      /* Single operand class, load operand and execute instruction */
      
      if (opcode < 0xb0) {
	operand[0] = load_operand ((opcode >> 4) & 0x03);
	switch ((char) opcode & 0x0f) {
	case 0x00: compare_zero (operand[0]); break;
	case 0x01: load_next_object (operand[0]); break;
	case 0x02: load_child_object (operand[0]); break;
	case 0x03: load_parent_object (operand[0]); break;
	case 0x04: load_property_length (operand[0]); break;
	case 0x05: increment (operand[0]); break;
	case 0x06: decrement (operand[0]); break;
	case 0x07: print_offset (operand[0]); break;
	case 0x08: call (1, operand, FUNCTION); break;
	case 0x09: remove_object (operand[0]); break;
	case 0x0a: print_object (operand[0]); break;
	case 0x0b: ret (operand[0]); break;
	case 0x0c: jump (operand[0]); break;
	case 0x0d: print_address (operand[0]); break;
	case 0x0e: load (operand[0]); break;
	case 0x0f:
	  if (h_type > V4)
	    call (1, operand, PROCEDURE);
	  else
	    not (operand[0]);
	  break;
	}
      } else {
	
	/* Zero operand class, execute instruction */
	
	switch ((char) opcode & 0x0f) {
	case 0x00: ret (TRUE); break;
	case 0x01: ret (FALSE); break;
	case 0x02: print_literal (); break;
	case 0x03: println_return (); break;
	  
	case 0x05: save (); break;
	case 0x06: restore (); break;
	case 0x07: restart (); break;
	case 0x08: ret (stack[sp++]); break;
	case 0x09: get_fp (); break;
	case 0x0a: halt = TRUE; break;
	case 0x0b: new_line (); break;
	case 0x0c: display_status_line (); break;
	case 0x0d: verify (); break;
	  
	case 0x0f: conditional_jump (TRUE); break;
	  
	default: fatal ("Illegal operation");
	}
      }
    }
  }
  
  return (interpreter_status);
}
