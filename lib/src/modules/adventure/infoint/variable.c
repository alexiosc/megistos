/*****************************************************************************\
 **                                                                         **
 **  FILE:     variable.c                                                   **
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
    "$Id$";



/*
 * variable.c
 *
 * Variable manipulation routines
 *
 */

#include "ztypes.h"



/*
 * load
 *
 * Load and store a variable value.
 *
 */



void
load (zword_t variable)
{
	store_operand (load_variable (variable));
}



/*
 * push_var
 *
 * Push a value onto the stack
 *
 */

void
push_var (zword_t value)
{
	stack[--sp] = value;
}



/*
 * pop_var
 *
 * Pop a variable from the stack.
 *
 */

void
pop_var (zword_t variable)
{
	store_variable (variable, stack[sp++]);
}



/*
 * increment
 *
 * Increment a variable.
 *
 */

void
increment (zword_t variable)
{
	store_variable (variable, load_variable (variable) + 1);
}



/*
 * decrement
 *
 * Decrement a variable.
 *
 */

void
decrement (zword_t variable)
{
	store_variable (variable, load_variable (variable) - 1);
}



/*
 * increment_check
 *
 * Increment a variable and then check its value against a target.
 *
 */

void
increment_check (zword_t variable, zword_t target)
{
	short   value;

	value = (short) load_variable (variable);
	store_variable (variable, ++value);
	conditional_jump (value > (short) target);
}



/*
 * decrement_check
 *
 * Decrement a variable and then check its value against a target.
 *
 */

void
decrement_check (zword_t variable, zword_t target)
{
	short   value;

	value = (short) load_variable (variable);
	store_variable (variable, --value);
	conditional_jump (value < (short) target);

}


/* End of File */
