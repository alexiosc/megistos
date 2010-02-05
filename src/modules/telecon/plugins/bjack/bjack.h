/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: bjack.h                                                          **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: main header file                                              **
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
 * $Id: bjack.h,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: bjack.h,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.12  1999/10/17 09:18:30  valis
 * *** empty log message ***
 *
 * Revision 0.11  1999/09/20 21:41:27  valis
 * added support for 2 different prompts (bell, w/out bell)
 *
 * Revision 0.10  1999/09/04 13:57:57  valis
 * first stable release, tidy up source code
 *
 * Revision 0.9  1999/09/01 22:34:38  valis
 * bjfXXXX flags introduced
 * reference to MSG_HELP removed
 *
 * Revision 0.8  1999/08/28 18:18:37  valis
 * support for bbs prompt subsystem
 * logging functions implemented
 *
 * Revision 0.7  1999/08/24 11:56:34  valis
 * P_EPAUSE_WARN added
 *
 * Revision 0.6  1999/08/24 08:51:23  valis
 * module parameters prefixed with P_ added
 * debug command added
 * changed bj_new_player to return pointer to new player record
 *
 * Revision 0.5  1999/08/22 17:32:51  bbs
 * some improvements, timing control, almost adequate
 *
 * Revision 0.4  1999/08/19 12:16:22  valis
 * various improvements
 *
 * Revision 0.3  1999/08/06 21:49:39  valis
 * prototypes for bj_on() and bj_off()
 *
 * Revision 0.2  1999/08/06 21:22:23  valis
 * simple multiplay available, card deck
 *
 * Revision 0.1  1999/08/06 20:08:01  valis
 * first working revision
 *
 */


#ifndef __BJ_H
#define __BJ_H


/* the module identification string */
extern const char MODULE_ID[];


/* definitions of game status */
#define STAT_NOGAME	0
#define STAT_NEWGAME	1
#define STAT_BETTING	2
#define STAT_HITTING	3
#define STAT_WINNER	4


/* player flags */
#define bjfSEX		0x00000001	/* player sex, 1=male   */
#define bjfPLAY		0x00000002	/* active, 1=play       */
#define bjfSTAY		0x00000004	/* stay, 1=stay         */
#define bjfNOCHARGE	0x00000008	/* 1=do not charge      */
#define bjfWIN		0x00000010	/* 1=player won         */
#define bjfPFIX		0x00000020	/* 0=pfix1, 1=pfix2     */
#define bjfFORCE	0x00000080	/* forced once          */


#define bj_logmsg(f...)	_bj_logmsg(__FILE__, __LINE__, __FUNCTION__, ##f)
void    _bj_logmsg (char *file, int line, char *func, char *format, ...);


/* extern declarations of module global variables (initialized from bjack.msg) */
extern int P_WDOG_EXP;		/* module watchdog timer limit          */
extern int P_TICK_EXP;		/* user watchdog timer limit            */
extern int P_PAUSE_EXP;		/* pause between games timer            */
extern int P_PAUSE_WARN;	/* timer tick for next game             */
extern int P_EPAUSE_WARN;	/* enable next game notices             */
extern int P_WARN_EXP;		/* max number of inactivity warn        */
extern int P_SYSOPS_NOCHARGE;	/* sysops don't charged enable          */
extern int P_SYSTEM_PERC;	/* percent of pot that goes to the system */
extern int P_MIN_CREDITS;	/* min credits to join game             */
extern int P_MAX_BET;		/* maximum bet a player can do          */
extern int P_LIGHT_CREDITS;	/* 'light' credits                      */
extern int P_MIN_PLAYERS;	/* min player number to begin           */
extern int P_MAX_PLAYERS;	/* max player number can join           */
extern int P_SYSOPS_DEBUG;	/* sysop can see debug info             */


extern int watchdog_timer;	/* if this counter expires, quit program                        */
extern int tick_timer;		/* if this counter expires, alert user                          */
extern int pause_timer;		/* if this counter expires, begin a new game, ignore if 0       */
extern int tick_warn;		/* number of times same user has been warned                    */



#ifdef BBSPROMPTS

#ifdef MEGISTOS_BBS

#ifdef LOGDIR
#undef LOGDIR
#endif

/* include the BBS logging dir */
#include <megistos/config.h>
#include <megistos/prompts.h>
extern promptblock_t *msg;

#endif				/* MEGISTOS_BBS */

#endif				/* BBSPROMPTS */

#ifndef LOGFILE
#define LOGFILE	mkfname(LOGDIR"/bjack.log")
#endif


#ifdef DEBUG
#define debug(s)	bj_broadcast_msg(0, BJM_STRING, "", s)
#else
#define debug(s)	;
#endif



/* BlackJack commands */
enum bj_cmd {
	BJ_NO_CMD, BJ_ON, BJ_OFF, BJ_BET, BJ_RAISE, BJ_CALL, BJ_FOLD, BJ_POT,
	BJ_HIT, BJ_STAY, BJ_HAND, BJ_TURN, BJ_HELP, BJ_RULES, BJ_SCAN, BJ_EXIT,
	BJ_INFO, BJ_BELL
#ifdef CHEATS
	    , BJ_SDECK, BJ_GIVE_CARD
#endif
#ifdef DEVEL
	    , BJ_START, BJ_DEBUG
#endif
};


extern char cmd_names[][10];	/* command names                */
extern char stat_names[][10];	/* status condition names       */
extern int total_bets;		/* total credits betted so far  */
extern int current_bet;		/* maximum bet so far           */
extern struct bj_player *c_player;	/* pointer to current player    */
extern struct bj_player *player_list;	/* players linked list          */
extern struct bj_player *player_list_tail;	/* add new users here           */
extern int STATUS;		/* game status                  */
extern char bj_userid[];	/* name of player given command */
extern char *bj_channel;	/* name of current channel      */
extern int play_count;		/* players still playing        */
extern int stay_count;		/* players having stayed        */
extern int CUR_PLAYERS;		/* current number of players    */

extern int advance_user;

/* the player record	*/
struct bj_player {
	char    userid[24];	/* the user id */
	int     flags;		/* flags, bitmap, 31 bits are enough (I think)
				   fields:
				   #0 = sex, 1 for man, 0 for woman,
				   #1 = play, 1 for playing, 0 for not playing
				   #2 = stay, 1 for stayed, 0 for not stayed
				   #3 = won, 1 for won, 0 for not won
				   #4 = nocharge, 0 for not charged, 0 for charged
				   #7 = already forced to fold/stay once
				 */
	int     credits;	/* player credits               */
	int     bet;		/* how much player has bet      */
	int     cards[12];	/* player cards                 */
	int     cards_count;	/* number of cards player has   */

	struct bj_player *next;
};

extern int card_deck[52];	/* randmoly-ordered deck of 52 cards */
extern int card_index;		/* index to card_deck[] for next card to be dealt */


/* function prototypes */

/* bjutil.c */

	/* return value of advanced_user, then zero the variable */
int     user_advanced (void);

	/* initialize module */
void    bj_init (void);

	/* initialize to begin game */
void    bj_init_game (void);

	/* initialize for next game */
void    bj_end_game (void);

	/* create a record for new player */
struct bj_player *bj_new_player (char *userid, int cred);

	/* parse command in s */
void    bj_parse_command (char *s, enum bj_cmd *cmd, int *i);

	/* execute command */
void    bj_execute_command (struct bj_player *player, enum bj_cmd cmd, int i);


	/* return pointer to player entry, if name is registered */
struct bj_player *bj_ingame (char *bjuser);

	/* put next player to play in c_player */
void    bj_next_player (void);

	/* the main blackjack loop */
void    bj_loop (void);


/* bjcmd.c */

	/* the following commands, do what their name says */
void    bj_on (struct bj_player *player, int i);
void    bj_off (struct bj_player *player);
int     bj_bet (struct bj_player *player, int bet);
int     bj_raise (struct bj_player *player, int bet);
int     bj_call (struct bj_player *player);
void    bj_pot (struct bj_player *player);
void    bj_turn (struct bj_player *player);
void    bj_scan (char *bjuser);
int     bj_fold (struct bj_player *player);
int     bj_hit (struct bj_player *player);
void    bj_hand (struct bj_player *player);
int     bj_stay (struct bj_player *player);

	/* search for winners */
int     bj_find_winner (void);

	/* randomly shuffle the card deck */
void    deck_shuffle (void);

	/* return the next card available */
int     bj_get_card (void);

	/* deal first 2 cards, and tkae off 'light' credits */
void    bj_deal_cards (void);



#ifdef DEVEL
void    bj_debug (char *bjuser, int i);
#endif

#ifdef CHEATS
void    bj_show_deck (struct bj_player *player);
void    bj_give_card (struct bj_player *player, int i);
#endif

#endif


/* End of File */
