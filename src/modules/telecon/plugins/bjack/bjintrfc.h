/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: bjintrfc.h                                                       **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: interface header file                                         **
 **  NOTES:                                                                 **
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
 * $Id: bjintrfc.h,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: bjintrfc.h,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:38  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/09/04 13:57:57  valis
 * first stable release, tidy up source code,
 * references to LINUX_CONSOLE removed
 *
 * Revision 0.6  1999/09/01 22:18:56  valis
 * pfix_prompt can keep up to 3 pre/post-fixes
 *
 * Revision 0.5  1999/08/28 18:18:37  valis
 * support for bbs prompt subsystem
 * logging functions implemented
 *
 * Revision 0.4  1999/08/24 12:18:04  bbs
 * added bj_get_cmd()
 *
 * Revision 1.4  1999/08/24 11:56:34  valis
 * added bj_get_cmd()
 *
 */


#ifndef __BJINTRFC_H
#define __BJINTRFC_H

#ifdef MEGISTOS_BBS

#include <megistos/bbs.h>
#include <telecon.h>
#include <teleconplugins.h>

#endif				/* MEGISTOS_BBS */

#include "bjack.h"


/* blackjack message record */
struct bj_message_r {
	char    userid[40];
	char    other_msg[2048];
	char    this_msg[2048];
} bj_message;

extern char temp_prompt[];	/* temporary store for prompts          */
extern char pfix_prompt[3][];	/* temporary store for pre/post-fixes   */

/* function prototypes */

/* interface.c */

	/* broadcast message to current and other users */
void    bj_broadcast_msg (int this_idx, int other_idx, char *userid, ...);

	/* return player credits */
int     bj_player_credits (struct bj_player *player);

	/* post credits to user */
void    bj_post_credits (struct bj_player *player, int credits);

	/* return player sex */
int     bj_player_sex (struct bj_player *player);

	/* return 1 if player cannot be charged */
int     bj_player_nocharge (struct bj_player *player);

	/* return >0 if command available, place command in text */
int     bj_get_cmd (char *userid, char *text);

	/* return index'th prompt */
char   *bj_get_prompt (int index);

	/* return index'th prompt if value=0 otherwise return index+1'th */
char   *bj_get_pfix (int pidx, int index, int value);


#endif				/* __BJINTRFC_H */


/* End of File */
