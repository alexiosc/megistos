/*****************************************************************************\
 **                                                                         **
 **  FILE:     security.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  Security-related functions                                   **
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
 * $Id$
 *
 * $Log$
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1998/12/27 14:31:03  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";

#include <bbsinclude.h>
#include "useracc.h"
#include "config.h"
#include "miscfx.h"



int
hassysaxs (useracc_t * user, int index)
{
	if (index < 0 || index > (sizeof (user->sysaxs) * 32))
		return 0;
	return (user->sysaxs[index / 32] & (1 << (index % 32))) != 0;
}


bbskey_t *
key_make (bbskey_t * userkeys, bbskey_t * classkeys, bbskey_t * combokeys)
{
	int     i;

	for (i = 0; i < KEYLENGTH; i++)
		combokeys[i] = userkeys[i] | classkeys[i];
	return combokeys;
}


int
key_exists (bbskey_t * keys, int key)
{
	if (!key)
		return 1;
	if (key < 0 || key > (32 * KEYLENGTH))
		return 0;
	key--;
	return (keys[key / 32] & (1 << (key % 32))) != 0;
}


int
key_owns (useracc_t * user, int key)
{
	bbskey_t combo[KEYLENGTH];
	classrec_t *class = cls_find (user->curclss);

	if (!key)
		return 1;
	if (key == (32 * KEYLENGTH + 1))
		return (sameas (user->userid, SYSOP));
	if (hassysaxs (user, USY_MASTERKEY))
		return 1;
	key_make (user->keys, class->keys, combo);
	return (key_exists (combo, key));
}


void
key_set (bbskey_t * keys, int key, int set)
{
	if (key < 1 || key > (32 * KEYLENGTH))
		return;
	key--;
	if (set)
		keys[key / 32] |= (1 << (key % 32));
	else
		keys[key / 32] &= ~(1 << (key % 32));
}
