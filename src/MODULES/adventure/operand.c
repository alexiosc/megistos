/*****************************************************************************\
 **                                                                         **
 **  FILE:     operand.c                                                    **
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
 * Revision 1.2  2001/04/16 21:56:31  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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
 * operand.c
 *
 * Operand manipulation routines
 *
 */

#include "ztypes.h"

/*
 * load_operand
 *
 * Load an operand, either: a variable, popped from the stack or a literal.
 *
 */

zword_t load_operand (int type)
{
  zword_t operand;
  
  if (type) {
    
    /* Type 1: byte literal, or type 2: operand specifier */
    
    operand = (zword_t) read_code_byte ();
    if (type == 2) {
      
      /* If operand specifier non-zero then it's a variable, otherwise
	 it's the top of the stack */
      
      if (operand)
	operand = load_variable (operand);
      else
	operand = stack[sp++];
    }
  } else
    
    /* Type 0: word literal */
    
    operand = read_code_word ();
  
  return (operand);
  
}



/*
 * store_operand
 *
 * Store an operand, either as a variable pushed on the stack.
 *
 */

void store_operand (zword_t operand)
{
  zbyte_t specifier;
  
  /* Read operand specifier byte */
  
  specifier = read_code_byte ();
  
  /* If operand specifier non-zero then it's a variable, otherwise it's the
     pushed on the stack */
  
  if (specifier)
    store_variable (specifier, operand);
  else
    stack[--sp] = operand;
  
}



/*
 * load_variable
 *
 * Load a variable, either: a stack local variable, a global variable or the top
 * of the stack.
 *
 */

zword_t load_variable (int number)
{
  zword_t variable;
  
  if (number) {
    if (number < 16)
      
      /* number in range 1 - 15, it's a stack local variable */
      
      variable = stack[fp - (number - 1)];
    else
      
      /* number > 15, it's a global variable */
      
      variable = get_word (h_globals_offset + ((number - 16) * 2));
  } else
    
    /* number = 0, get from top of stack */
    
    variable = stack[sp];
  
  return (variable);
  
}



/*
 * store_variable
 *
 * Store a variable, either: a stack local variable, a global variable or the top
 * of the stack.
 *
 */

void store_variable (int number, zword_t variable)
{
  
  if (number) {
    if (number < 16)
      
      /* number in range 1 - 15, it's a stack local variable */
      
      stack[fp - (number - 1)] = variable;
    else
      
      /* number > 15, it's a global variable */
      
      set_word (h_globals_offset + ((number - 16) * 2), variable);
  } else
    
    /* number = 0, get from top of stack */
    
    stack[sp] = variable;
  
}



/*
 * conditional_jump
 *
 * Take a jump after an instruction based on the flag, either true or false. The
 * jump can be modified by the change logic flag. Normally jumps are taken
 * when the flag is true. When the change logic flag is set then the jump is
 * taken when flag is false. A PC relative jump can also be taken. This jump can
 * either be a positive or negative byte or word range jump. An additional
 * feature is the return option. If the jump offset is zero or one then that
 * literal value is passed to the return instruction, instead of a jump being
 * taken. Complicated or what!
 *
 */

void conditional_jump (int flag)
{
  zbyte_t specifier;
  zword_t offset;
  
  /* Read the specifier byte */
  
  specifier = read_code_byte ();
  
  /* If the reverse logic flag is set then reverse the flag */
  
  if (specifier & 0x80)
    flag = (flag) ? 0 : 1;
  
  /* Jump offset is in bottom 6 bits */
  
  offset = (zword_t) specifier & 0x3f;
  
  /* If the byte range jump flag is not set then load another offset byte */
  
  if ((specifier & 0x40) == 0) {
    
    /* Add extra offset byte to existing shifted offset */
    
    offset = (offset << 8) + read_code_byte ();
    
    /* If top bit of offset is set then propogate the sign bit */
    
    if (offset & 0x2000)
      offset |= 0xc000;
  }
  
  /* If the flag is false then do the jump */
  
  if (flag == 0){
    
    /* If offset equals 0 or 1 return that value instead */
    
    if (offset == 0 || offset == 1) ret (offset);
    else {     
      /* Add offset to PC */
      
      pc = (unsigned long) (pc + (short) offset - 2);
    }
  }
}
