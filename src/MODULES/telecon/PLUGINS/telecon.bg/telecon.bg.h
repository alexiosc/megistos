/*****************************************************************************\
 **                                                                         **
 **  FILE:     telecon.bg.h                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 99                                                 **
 **  PURPOSE:  Interface to telecon.bg                                      **
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
 * Revision 1.1  2001/04/16 15:00:16  alexios
 * Initial revision
 *
 * Revision 1.0  1999/08/13 17:03:41  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define rnd6() (1+((rand()>>16)%6))



extern char player[2][24];	/* The players' user IDs */
extern char sex[2];		/* The players' sexes */

extern char fx_prompt[8192];	/* Temp buffer for injoths */



extern int cturn;		/* Whose turn is it? */



void bg_set_players(int num_players); /* 1 or 2 only, of course */

void bg_initialise();

void bg_firstroll();

void bg_board(int player_num);	/* 0 or 1 */
