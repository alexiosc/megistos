/*****************************************************************************\
 **                                                                         **
 **  FILE:     math.c                                                       **
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
 * math.c
 *
 * Arithmetic, compare and logical instructions
 *
 */

#include "ztypes.h"

/*
 * add
 *
 * Add two operands
 *
 */

void
add (zword_t a, zword_t b)
{
	store_operand (a + b);
}



/*
 * subtract
 *
 * Subtract two operands
 *
 */

void
subtract (zword_t a, zword_t b)
{
	store_operand (a - b);
}



/*
 * multiply
 *
 * Multiply two operands
 *
 */

void
multiply (zword_t a, zword_t b)
{
	store_operand (a * b);
}



/*
 * divide
 *
 * Divide two operands
 *
 */

void
divide (zword_t a, zword_t b)
{
	store_operand (a / b);
}



/*
 * remainder
 *
 * Modulus divide two operands
 *
 */

void
remainder (zword_t a, zword_t b)
{
	store_operand (a % b);
}



/*
 * shift
 *
 * Shift +/- n bits
 *
 */

void
shift (zword_t a, zword_t b)
{
	if ((short) b > 0)
		store_operand (a << (short) b);
	else
		store_operand (a >> abs ((short) b));
}




/*
 * arith_shift
 *
 * Aritmetic shift +/- n bits
 *
 */

void
arith_shift (zword_t a, zword_t b)
{
	if ((short) b > 0)
		store_operand (a << (short) b);
	else if ((short) a > 0)
		store_operand (a >> abs ((short) b));
	else
		store_operand (~((~a) >> abs ((short) b)));
}



/*
 * or
 *
 * Logical OR
 *
 */

void
or (zword_t a, zword_t b)
{
	store_operand (a | b);
}



/*
 * not
 *
 * Logical NOT
 *
 */

void
not (zword_t a)
{
	store_operand (~a);
}



/*
 * and
 *
 * Logical AND
 *
 */

void
and (zword_t a, zword_t b)
{
	store_operand (a & b);
}



/*
 * zip_random
 *
 * Return random number between 1 and operand
 *
 */

void
zip_random (zword_t a)
{
	if (a == 0)
		store_operand (0);
	else if (a & 0x8000) {	/* (a < 0) - used to set seed with #RANDOM */
		srand ((unsigned int) abs (a));
		store_operand (0);
	} else			/* (a > 0) */
		store_operand (((zword_t) rand () % a) + 1);
}



/*
 * test
 *
 * Jump if operand 2 bit mask not set in operand 1
 *
 */


void
test (zword_t a, zword_t b)
{
	conditional_jump (((~a) & b) == 0);
}



/*
 * compare_zero
 *
 * Compare operand against zero
 *
 */

void
compare_zero (zword_t a)
{
	conditional_jump (a == 0);
}



/*
 * compare_je
 *
 * Jump if operand 1 is equal to any other operand
 *
 */

void
compare_je (int count, zword_t * operand)
{
	int     i;

	for (i = 1; i < count; i++)
		if (operand[0] == operand[i]) {
			conditional_jump (TRUE);
			return;
		}
	conditional_jump (FALSE);

}



/*
 * compare_jl
 *
 * Jump if operand 1 is less than operand 2
 *
 */

void
compare_jl (zword_t a, zword_t b)
{
	conditional_jump ((short) a < (short) b);
}



/*
 * compare_jg
 *
 * Jump if operand 1 is greater than operand 2
 *
 */

void
compare_jg (zword_t a, zword_t b)
{
	conditional_jump ((short) a > (short) b);
}


/* End of File */
