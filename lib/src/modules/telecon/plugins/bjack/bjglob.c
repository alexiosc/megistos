/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: bjglob.c                                                         **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: all global variables are declared here                        **
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
 * $Id$
 *
 * $Log$
 * Revision 1.5  2003/12/27 12:29:38  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.11  1999/10/17 09:18:30  valis
 * *** empty log message ***
 *
 * Revision 0.10  1999/09/20 21:43:19  valis
 * added support for 2 different prompts
 *
 * Revision 0.9  1999/09/04 13:57:57  valis
 * first stable release, tidy up source code,
 * some useless variables removed
 *
 * Revision 0.8  1999/09/01 22:18:56  valis
 * removed reference to MSG_HELP
 *
 * Revision 0.7  1999/08/28 18:18:37  valis
 * support for bbs prompt subsystem
 * logging functions implemented
 *
 * Revision 0.6  1999/08/24 11:56:34  valis
 * P_EPAUSE_WARN added
 *
 * Revision 0.5  1999/08/24 08:51:23  valis
 * module parameters prefixed with P_ added
 *
 * Revision 0.4  1999/08/22 17:33:46  bbs
 * timer variables added
 *
 * Revision 0.3  1999/08/19 12:16:44  valis
 * various improvements
 *
 * Revision 0.2  1999/08/06 21:22:33  valis
 * simple multiplay available, card deck
 *
 * Revision 0.1  1999/08/06 20:08:15  valis
 * first working revision
 *
 */

#include <time.h>
#include <stdio.h>

#include "bjconf.h"
#include "bjack.h"
#include "bjintrfc.h"


static const char rcsinfo[] =
    "$Id$";


char    cmd_names[][10] =
    { "no_cmd", "on", "off", "bet", "raise", "call", "fold", "pot",
	"hit", "stay", "hand", "turn", "help", "rules", "scan", "exit", "info",
	    "bell"
#ifdef CHEATS
	    , "sdeck", "scard"
#endif
#ifdef DEVEL
	    , "start", "debug"
#endif
};

char    stat_names[][10] =
    { "NOGAME", "NEWGAME", "BETTING", "HITTING", "WINNER" };


int     P_WDOG_EXP;
int     P_TICK_EXP;
int     P_PAUSE_EXP;
int     P_PAUSE_WARN;
int     P_EPAUSE_WARN;
int     P_WARN_EXP;
int     P_SYSOPS_NOCHARGE;
int     P_SYSTEM_PERC;
int     P_MIN_CREDITS;
int     P_MAX_BET;
int     P_LIGHT_CREDITS;
int     P_MIN_PLAYERS;
int     P_MAX_PLAYERS;
int     P_SYSOPS_DEBUG;

#ifdef BBSPROMPTS
promptblock_t *msg = NULL;
#endif

int     total_bets = 0;
int     current_bet = 0;
int     CUR_PLAYERS = 0;
int     play_count = 0;		/* number of players still playing */
int     stay_count = 0;		/* number of players that have stayed */
int     advance_user = 0;
char    bj_userid[24];
char   *bj_channel;
struct bj_player *player_list;
struct bj_player *player_list_tail;
struct bj_player *c_player;
int     STATUS;

int     watchdog_timer = 0;
int     tick_timer = 0;
int     pause_timer = 0;
int     tick_warn = 0;
int     card_deck[52];
int     card_index;




/* End of File */
