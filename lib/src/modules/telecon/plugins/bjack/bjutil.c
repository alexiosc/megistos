/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: bjutil.c                                                         **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: various functions                                             **
 **  NOTES: all game functions prefixed with bj_                            **
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
 * Revision 1.4  2003/12/25 08:26:19  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.12  1999/10/17 09:18:30  valis
 * *** empty log message ***
 *
 * Revision 0.11  1999/09/20 21:43:19  valis
 * changed command exit
 *
 * Revision 0.10  1999/09/04 13:57:57  valis
 * first stable release, tidy up source code
 *
 * Revision 0.9  1999/09/01 22:18:56  valis
 * bj_check_players introduced but left unfinished
 * bug in bj_off() could kill the plugin, fixed
 * bug in bj_new_player() could kill the plugin, fixed
 * bj_loop is slightly modified, check of CUR_PLAYERS and user_advanced
 *  is done outside the main if-loop
 * flag to kick player out of the game introduced
 * channel name is also logged
 *
 * Revision 0.8  1999/08/28 18:18:37  valis
 * support for bbs prompt subsystem
 * logging functions implemented
 *
 * Revision 0.7  1999/08/24 11:56:34  valis
 * changes in bj_init(), bj_init_game() and bj_end_game()
 * added bj_loop() it is independent of any system call
 *
 * Revision 0.6  1999/08/24 09:06:22  valis
 * file split in 2, blackjack commands oriented functions moved to bjcmd.c
 * player sex support
 * changed bj_new_player to return pointer to new player record
 *
 * Revision 0.5  1999/08/22 17:29:25  bbs
 * major improvements, added timing control, generally it is almost working
 *
 * Revision 0.3  1999/08/06 21:50:07  valis
 * bj_off removes player from linked list
 *
 * Revision 0.2  1999/08/06 21:22:35  valis
 * simple multiplay available, card deck
 *
 * Revision 0.1  1999/08/06 20:08:30  valis
 * first working revision
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <time.h>


#include "bjconf.h"
#include "bjack.h"
#include "bjintrfc.h"

#include "wdog.h"

#ifdef BBSPROMPTS

#ifdef MEGISTOS_BBS
#include "mbk_bjack.h"
#endif

#else
#include "bjmsg.h"

#endif				/* BBSPROMPTS */


static const char rcsinfo[] =
    "$Id$";


int
user_advanced (void)
{
	if (advance_user) {
		advance_user = 0;
		return 1;
	} else
		return 0;
}

/* return pointer to player, if he is registered to play */
struct bj_player *
bj_ingame (char *bjuser)
{
	struct bj_player *pl;

	pl = player_list;
	while (pl != NULL) {
		if (!strcasecmp (pl->userid, bjuser))
			return pl;
		pl = pl->next;
	}

	return NULL;
}


/* this is a very important function (!) */
void
bj_next_player (void)
{
	struct bj_player *pl;


	pl = c_player;

	do {
		c_player = c_player->next;
		if (c_player == NULL)
			c_player = player_list;	// fold up to the beginning of the list 

		if (c_player == NULL)
			break;



/* we can exit loop and return c_player iff : we are STAT_BETTING and returned to the original 
   user or c_player must bet (player->bet < current_bet) */

		if ((STATUS == STAT_BETTING) && ((c_player->flags & bjfPLAY)
						 || ((c_player == pl) &&
						     (c_player->bet <
						      current_bet))))
			break;


/* we can exit loop and return c_player iff : we are STAT_HITTING and returned to the original
   user or c_player has not stayed (can hit a card) */

		if ((STATUS == STAT_HITTING) && (c_player->flags & bjfPLAY)
		    && ((!(c_player->flags & bjfSTAY)) || (c_player == pl)))

			break;


/* if all the still playing players have stayed search for winner */
		if ((STATUS == STAT_HITTING) && (stay_count == play_count))
			break;

/* all the players have quited! */
		if ((STATUS == STAT_BETTING) && (!play_count))
			break;

	} while (1);


/* if we are STAT_HITTING and all active players stayed search winner */
	if ((STATUS == STAT_HITTING) && (stay_count == play_count)) {
		STATUS = STAT_WINNER;
		return;
	}

	if ((!play_count) || (c_player == NULL)) {
		bj_broadcast_msg (0, BJM_ALLQUIT, "");
		bj_end_game ();
		return;
	}


/* if we are STAT_BETTING and c_player->bet==current_bet and current_bet!=0 then
	we have a fold up. Because each player plays in turn linearly, it means that a
	whole betting round has finished and we can start hitting cards */

	if ((c_player->bet == current_bet) && (STATUS == STAT_BETTING) &&
	    (current_bet)) {
		bj_broadcast_msg (0, BJM_BEGHIT, "");

		STATUS = STAT_HITTING;

/* get the first available player from the beginning of the list */
		c_player = player_list;
		if (!(c_player->flags & bjfPLAY))
			bj_next_player ();
	}

/* c_player advanced, update timers */
	advance_user = 1;
	tick_warn = 0;
	tick_timer = time (0) + P_TICK_EXP;
}

void
bj_init (void)
{

/* initialize some module variables */
#ifdef BBSPROMPTS
	msg_set (msg);

	P_WDOG_EXP = msg_int (BJV_WDOGEXP, 0, 32768);
	P_TICK_EXP = msg_int (BJV_TICKEXP, 0, 32768);
	P_PAUSE_EXP = msg_int (BJV_PAUSEEXP, 0, 32768);
	P_EPAUSE_WARN = msg_bool (BJV_EPAUSEWARN);
	P_PAUSE_WARN = msg_int (BJV_PAUSEWARN, 0, 32768);
	P_WARN_EXP = msg_int (BJV_WARNEXP, 0, 10);
	P_SYSOPS_NOCHARGE = msg_bool (BJV_SYSOPS_NOCHARGE);

	P_SYSTEM_PERC = msg_int (BJV_SYSTEM_PERC, 0, 100);
	P_MIN_CREDITS = msg_int (BJV_MIN_CRED, 0, 32768);
	P_MAX_BET = msg_int (BJV_MAX_BET, 0, 10000);
	P_LIGHT_CREDITS = msg_int (BJV_LIGHT_CRED, 0, 32768);
	P_MIN_PLAYERS = msg_int (BJV_MIN_PLAYERS, 1, 5);
	P_MAX_PLAYERS = msg_int (BJV_MAX_PLAYERS, 0, 32768);

	P_SYSOPS_DEBUG = msg_bool (BJV_SYSOPS_DEBUG);

#else
	P_WDOG_EXP = atoi (bj_get_prompt (BJV_WDOGEXP));
	P_TICK_EXP = atoi (bj_get_prompt (BJV_TICKEXP));
	P_PAUSE_EXP = atoi (bj_get_prompt (BJV_PAUSEEXP));
	P_PAUSE_WARN = atoi (bj_get_prompt (BJV_PAUSEWARN));
	P_EPAUSE_WARN = atoi (bj_get_prompt (BJV_EPAUSEWARN));
	P_WARN_EXP = atoi (bj_get_prompt (BJV_WARNEXP));
	P_SYSOPS_NOCHARGE = atoi (bj_get_prompt (BJV_SYSOPS_NOCHARGE));

	P_SYSTEM_PERC = atoi (bj_get_prompt (BJV_SYSTEM_PERC));
	P_MIN_CREDITS = atoi (bj_get_prompt (BJV_MIN_CRED));
	P_MAX_BET = atoi (bj_get_prompt (BJV_MAX_BET));
	P_LIGHT_CREDITS = atoi (bj_get_prompt (BJV_LIGHT_CRED));
	P_MIN_PLAYERS = atoi (bj_get_prompt (BJV_MIN_PLAYERS));

	P_MAX_PLAYERS = atoi (bj_get_prompt (BJV_MAX_PLAYERS));
	P_SYSOPS_DEBUG = atoi (bj_get_prompt (BJV_SYSOPS_DEBUG));

#endif

	player_list = NULL;
	player_list_tail = NULL;

	CUR_PLAYERS = 0;

	bj_end_game ();		/* do some initializations */

/* initiate just for being sure */
	advance_user = 0;
}


void
bj_check_players (void)
{
	struct bj_player *pl, *npl;

	pl = player_list;
	while (pl != NULL) {
		npl = pl->next;
		if (!tlcuidxref (pl->userid, 1)) {
			bj_broadcast_msg (0, BJM_PLNOINTELE, "", pl->userid);
//                      bj_off(pl);
		}
		pl = npl;
	}
}


void
bj_init_game (void)
{
	bj_end_game ();

/*	bj_check_players(); */


	bj_broadcast_msg (0, BJM_NEWGAME, "");
	bj_deal_cards ();

	STATUS = STAT_BETTING;
	c_player = player_list;

	advance_user = 1;
	pause_timer = 0;
}

void
bj_end_game (void)
{
	struct bj_player *pl;

	play_count = 0;

	pl = player_list;
	while (pl != NULL) {
		play_count++;

		pl->flags |= bjfPLAY;
		pl->flags &= ~(bjfSTAY | bjfWIN);

		pl->bet = 0;
		pl->cards_count = 0;
		memset (pl->cards, 0x00, sizeof (pl->cards));

		pl = pl->next;
	}

	current_bet = 0;
	total_bets = 0;
	stay_count = 0;

	STATUS = STAT_NOGAME;
	c_player = NULL;
	pause_timer = time (0) + P_PAUSE_EXP;
}


struct bj_player *
bj_new_player (char *userid, int cred)
{
	struct bj_player *pl;

	CUR_PLAYERS++;

	pl = malloc (sizeof (struct bj_player));

	if (pl == NULL) {
		bj_broadcast_msg (0, BJM_STRING, "", "NO FREE MEMORY");
		bj_logmsg ("ERROR: Could not allocate memory for player %s",
			   userid);

		exit (EXIT_FAILURE);
	}

	if (player_list == NULL) {
		player_list = pl;
		player_list_tail = pl;
	} else {
		player_list_tail->next = pl;
		player_list_tail = pl;
	}

	pl->next = NULL;

	strcpy (pl->userid, userid);
	pl->credits = cred;
	pl->bet = 0;
	pl->cards_count = 0;
	memset (pl->cards, 0x00, 12 * sizeof (int));

	play_count++;

	pl->flags = 0;		/* clear the field */

	pl->flags |= bj_player_sex (pl);
	pl->flags |= bj_player_nocharge (pl);

	return pl;
}





/******************************************/
/* The BlackJack main loop ****************/
/******************************************/
void
bj_loop (void)
{
	int     n;
	char    s[200];
	int     i;
	enum bj_cmd cmd;
	struct bj_player *cmd_player;

	int     temp = 0;

	do {
		cmd = BJ_NO_CMD;

		if (STATUS == STAT_NEWGAME) {
			if (CUR_PLAYERS >= P_MIN_PLAYERS) {
				bj_init_game ();
				tick_timer = time (0) + P_TICK_EXP;
			}
		}

		if (STATUS == STAT_WINNER) {
			bj_find_winner ();
			bj_end_game ();
			continue;
		}

		if ((user_advanced ()) && (c_player != NULL)) {
			if (STATUS == STAT_BETTING)
				bj_broadcast_msg (BJM_YTURNBET, 0,
						  c_player->userid);
			else if (STATUS == STAT_HITTING)
				bj_broadcast_msg (BJM_YTURNHIT, 0,
						  c_player->userid);
		}

		/*if(check_watchdog())
		   bj_logmsg("Control check received and answered");                // check for control check! 
		 */

		n = bj_get_cmd (bj_userid, s);
		if (n > 0) {
			watchdog_timer = time (0) + P_WDOG_EXP;	/* update watchdog timer */
			/*check_watchdog(); */

			i = -1;
			cmd = BJ_NO_CMD;

			bj_parse_command (s, &cmd, &i);

			cmd_player = bj_ingame (bj_userid);


			/* special care should be taken. A new player is not yet registered in the player_list
			   so we must allow him to enter even if cmd_player is NULL */


			if (((STATUS == STAT_HITTING) && (cmd == BJ_HIT))
			    && (!strcasecmp (c_player->userid, bj_userid))) {
				tick_timer = time (0) + P_TICK_EXP;
			}

			bj_execute_command (cmd_player, cmd, i);

			if ((cmd == BJ_EXIT) &&
			    (!strcasecmp (bj_userid, "valis"))) {
				bj_broadcast_msg (0, BJM_STRING, "",
						  "--- DEBUG: Finishing BLACKJACK\n");
				break;
			} else
				cmd = BJ_NO_CMD;

		}

		if (CUR_PLAYERS == 0) {
			STATUS = STAT_NOGAME;
			c_player = player_list = player_list_tail = NULL;
			cmd = BJ_EXIT;
		}

		if (user_advanced ()) {
			if (STATUS == STAT_BETTING)
				bj_broadcast_msg (BJM_YTURNBET, 0,
						  c_player->userid);
			else if (STATUS == STAT_HITTING)
				bj_broadcast_msg (BJM_YTURNHIT, 0,
						  c_player->userid);
		}

		if (time (0) > watchdog_timer) {
			bj_broadcast_msg (0, BJM_INACTIVITY, "");
			bj_logmsg
			    ("Long inactivity period - plugin commits suicide");
			break;
		}

		if ((time (0) > tick_timer) &&
		    ((STATUS == STAT_BETTING) || (STATUS == STAT_HITTING))) {
			if (c_player != NULL) {
				tick_warn++;
				if (tick_warn > P_WARN_EXP) {

					bj_broadcast_msg (BJM_WARNEXP, 0,
							  c_player->userid,
							  bj_get_pfix (0,
								       BJM_MINACTIVE,
								       (c_player->
									flags &
									bjfSEX)));



					if (c_player->flags & bjfFORCE) {
						bj_broadcast_msg (0,
								  BJM_OFORCEOFF,
								  "",
								  bj_get_pfix
								  (0,
								   BJM_MPLAYER,
								   (c_player->
								    flags &
								    bjfSEX)),
								  c_player->
								  userid);

#ifdef FORCE_LOG
						bj_logmsg
						    ("*FORCE* Player %s forced to quit",
						     c_player->userid);
#endif

						bj_off (c_player);
						tick_warn = 0;

						continue;
					}


					switch (STATUS) {
					case STAT_BETTING:
						bj_broadcast_msg
						    (BJM_YFORCEFOLD,
						     BJM_OFORCEFOLD,
						     c_player->userid,
						     bj_get_pfix (0,
								  BJM_MPLAYER,
								  (c_player->
								   flags &
								   bjfSEX)),
						     c_player->userid,
						     bj_get_pfix (1,
								  BJM_MINACTIVE,
								  (c_player->
								   flags &
								   bjfSEX)));

						bj_fold (c_player);
#ifdef FORCE_LOG
						bj_logmsg
						    ("*FORCE* Player %s forced to fold",
						     c_player->userid);
#endif
						break;

					case STAT_HITTING:
						bj_broadcast_msg
						    (BJM_YFORCESTAY,
						     BJM_OFORCESTAY,
						     c_player->userid,
						     bj_get_pfix (0,
								  BJM_MPLAYER,
								  (c_player->
								   flags &
								   bjfSEX)),
						     c_player->userid,
						     bj_get_pfix (1,
								  BJM_MINACTIVE,
								  (c_player->
								   flags &
								   bjfSEX)));

						bj_stay (c_player);
#ifdef FORCE_LOG
						bj_logmsg
						    ("*FORCE* Player %s forced to stay",
						     c_player->userid);
#endif
						break;
					}
					tick_warn = 0;	/* zero counter */
					c_player->flags |= bjfFORCE;	/* set the flag and kick out on next */

					bj_next_player ();
					continue;
				}

				bj_broadcast_msg (BJM_TICK, 0,
						  c_player->userid);
				tick_timer = time (0) + P_TICK_EXP;
				advance_user = 1;
			}
		}

		if ((CUR_PLAYERS) && (pause_timer)
		    && (((pause_timer - time (0)) % P_PAUSE_WARN == 0) ||
			(cmd == BJ_ON))) {

			/* inform every other user that joins about the time... */
			if (cmd == BJ_ON)
				temp = 0;

			if ((!temp) && (CUR_PLAYERS < P_MIN_PLAYERS)) {
				bj_broadcast_msg (0, BJM_WAITMORE, "",
						  P_MIN_PLAYERS);
				temp = 1;
				pause_timer = time (0) + P_PAUSE_EXP;
				continue;
			}

			if (!temp) {
				if (pause_timer <= time (0))
					bj_broadcast_msg (0, BJM_STARTNOW, "");
				else if (P_EPAUSE_WARN)
					bj_broadcast_msg (0, BJM_START, "",
							  pause_timer -
							  time (0));

				temp = 1;
			}
		} else
			temp = 0;

		if ((pause_timer) && (time (0) > pause_timer) &&
		    (STATUS == STAT_NOGAME))
			STATUS = STAT_NEWGAME;

		usleep (50000);

	} while (cmd != BJ_EXIT);
}


void
_bj_logmsg (char *file, int line, char *func, char *format, ...)
{
	va_list args;
	FILE   *fp;
	struct tm *dt;
	time_t  t;
	char    datetime[64];

	if ((fp = fopen (LOGFILE, "a")) == NULL)
		return;
	t = time (0);
	dt = localtime (&t);
	strftime (datetime, sizeof (datetime), "%d/%m/%Y %H:%M:%S", dt);

#ifdef VERBOSE_LOG
	fprintf (fp, "%s [%s:%d %20s] {%s} (%s): ", datetime, file, line, func,
		 bj_channel, ((bj_userid[0] == 0) ? "unknown" : bj_userid));
#else
	fprintf (fp, "%s [%s:%d] {%s} (%s): ", datetime, file, line,
		 bj_channel, ((bj_userid[0] == 0) ? "unknown" : bj_userid));
#endif

	va_start (args, format);

	vfprintf (fp, format, args);
	va_end (args);

	fputc ('\n', fp);
	fclose (fp);
}




/* End of File */
