/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: cards.h                                                          **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: card-drawing header file                                      **
 **  NOTES: This is a global card drawing library                           **
 **                                                                         **
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
 * Special thanks to Antonis Stamboulis (Xplosion) for providing me source 
 * for the card drawing functions. I have used his primary source files with
 * slight modifications. (er 17-Oct-1999)
 *
 */

/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 15:00:09  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:54  alexios
 * Initial checkin.
 *
 * Revision 1.0  1999/10/17 09:17:49  valis
 * Initial revision
 *
 *
 */

#ifndef __CARDS_H
#define __CARDS_H

char card_value(int cardidx);
char card_sign(int cardidx);
void map_cards(int *array, int count);
void draw_cards(int *array, int count);
char *buf_index(int index);

#endif	/* __CARDS_H */
