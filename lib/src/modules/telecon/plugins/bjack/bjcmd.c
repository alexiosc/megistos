/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: bjcmd.c                                                          **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: command specific functions                                    **
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
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/10/17 09:18:30  valis
 * fixed bug which did not implement cards numbered with 10
 * card_sign() and card_value() now are placed in the cards.c library
 * changed bj_hand() to show cards as drawings
 * changed bj_hit() to show new card as drawing
 *
 * Revision 0.6  1999/09/20 21:41:27  valis
 * added support for 2 different prompts (bell, w/out bell)
 *
 * Revision 0.5  1999/09/04 13:57:57  valis
 * first stable release, tidy up source code
 *
 * Revision 0.4  1999/09/01 22:18:56  valis
 * command RULES has introduced, INFO has changed
 * bj_off has changed to return void
 * flags introduced instead of ints in bj_player structure
 *
 * Revision 0.3  1999/08/28 18:18:37  valis
 * support for bbs prompt subsystem
 * logging functions implemented
 *
 * Revision 0.2  1999/08/24 11:56:34  valis
 * made indipendable of bj_ver.h
 * added option not to charge sysops, various improvements
 *
 * Revision 0.1  1999/08/24 09:15:07  valis
 * file emerged from the split of bjutil.c
 * initial revision. adequate.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#include <megistos/bjconf.h>
#include <megistos/bjack.h>
#include <megistos/bjintrfc.h>

#include <megistos/cards.h>

#ifdef BBSPROMPTS

#ifdef MEGISTOS_BBS
#include <megistos/mbk_bjack.h>
#endif

#else
#include <megistos/bjmsg.h>

#endif				/* BBSPROMPTS */


static const char rcsinfo[] =
    "$Id$";


void
bj_parse_command (char *s, enum bj_cmd *cmd, int *i)
{
	char    ss[50];

	sscanf (s, "%s", ss);
	if (!strcasecmp (ss, "on")) {
		*cmd = BJ_ON;
		if (sscanf (s, "%*s %i", i) == EOF)
			*i = -1;
		return;
	}
	if (!strcasecmp (ss, "off")) {
		*cmd = BJ_OFF;
		return;
	}
	if (!strcasecmp (ss, "exit")) {
		*cmd = BJ_EXIT;
		return;
	}
	if (!strcasecmp (ss, "bet")) {
		*cmd = BJ_BET;
		if (sscanf (s, "%*s %i", i) == EOF)
			*i = -1;
		return;
	}
	if (!strcasecmp (ss, "raise")) {
		*cmd = BJ_RAISE;
		if (sscanf (s, "%*s %i", i) == EOF)
			*i = -1;
		return;
	}
	if (!strcasecmp (ss, "call")) {
		*cmd = BJ_CALL;
		return;
	}
	if (!strcasecmp (ss, "fold")) {
		*cmd = BJ_FOLD;
		return;
	}
	if (!strcasecmp (ss, "pot")) {
		*cmd = BJ_POT;
		return;
	}
	if (!strcasecmp (ss, "hit")) {
		*cmd = BJ_HIT;
		return;
	}
	if (!strcasecmp (ss, "stay")) {
		*cmd = BJ_STAY;
		return;
	}
	if (!strcasecmp (ss, "hand")) {
		*cmd = BJ_HAND;
		return;
	}
	if (!strcasecmp (ss, "turn")) {
		*cmd = BJ_TURN;
		return;
	}
	if (!strcasecmp (ss, "help")) {
		*cmd = BJ_HELP;
		return;
	}
	if (!strcasecmp (ss, "rules")) {
		*cmd = BJ_RULES;
		return;
	}
	if (!strcasecmp (ss, "info")) {
		*cmd = BJ_INFO;
		return;
	}
	if (!strcasecmp (ss, "scan")) {
		*cmd = BJ_SCAN;
		return;
	}
	if (!strcasecmp (ss, "bell")) {
		*cmd = BJ_BELL;
		if (sscanf (s, "%*s %i", i) == EOF)
			*i = -1;
		return;
	}
#ifdef CHEATS
	if (!strcasecmp (ss, "showdeck")) {
		*cmd = BJ_SDECK;
		return;
	}
	if (!strcasecmp (ss, "give")) {
		char    c;
		int     j;
		char    ar[] = "234576789AJQK";

		*cmd = BJ_GIVE_CARD;
		sscanf (s, "%*s %c", &c);

		for (j = 0; j < 13; j++) {
			if (ar[j] == c)
				break;
		}

		*i = (int) ar[j];
	}
#endif

#ifdef DEVEL
	if (!strcasecmp (ss, "start")) {
		*cmd = BJ_START;
		return;
	}
	if (!strcasecmp (ss, "debug")) {
		*cmd = BJ_DEBUG;
		if (sscanf (s, "%*s %i", i) == EOF)
			*i = -1;
		return;
	}
#endif

}

void
bj_execute_command (struct bj_player *player, enum bj_cmd cmd, int i)
{
#ifdef COMMAND_LOG
	bj_logmsg ("- Status %s executing %s (i=%i)", stat_names[STATUS],
		   cmd_names[cmd], i);
#endif

/* if user is not registered then he is only allowed to use some specific commands */
	if ((player == NULL) && (!((cmd == BJ_ON) || (cmd == BJ_HELP) ||
				   (cmd == BJ_RULES) || (cmd == BJ_INFO) ||
				   (cmd == BJ_DEBUG)
				   || (cmd == BJ_SCAN)	/* this is asked by Stelios Ioannou (Gigas) */
				 ))) {
		bj_broadcast_msg (BJM_NOPART, 0, bj_userid);
		return;
	}

	switch (cmd) {
	case BJ_NO_CMD:
		bj_broadcast_msg (BJM_ERCMD, 0, player->userid);
		break;

/* miscellaneous commands */
	case BJ_ON:
		bj_on (player, i);
		break;
	case BJ_OFF:
		bj_off (player);
		break;

	case BJ_EXIT:
		break;
	case BJ_HELP:
		bj_broadcast_msg (BJM_HELP, 0, bj_userid);
		break;
	case BJ_RULES:
		bj_broadcast_msg (BJM_RULES, 0, bj_userid, P_MIN_PLAYERS,
				  P_PAUSE_EXP, P_TICK_EXP, P_WARN_EXP);
		break;
	case BJ_INFO:
		bj_broadcast_msg (BJM_INFO, 0, bj_userid, MODULE_ID);
		break;

	case BJ_POT:
		bj_pot (player);
		break;
	case BJ_TURN:
		bj_turn (player);
		break;
	case BJ_SCAN:
		bj_scan (bj_userid /*player */ );
		break;
	case BJ_HAND:
		bj_hand (player);
		break;

	case BJ_BET:
		if (bj_bet (player, i))
			bj_next_player ();
		break;
	case BJ_RAISE:
		if (bj_raise (player, i))
			bj_next_player ();
		break;
	case BJ_CALL:
		if (bj_call (player))
			bj_next_player ();
		break;
	case BJ_FOLD:
		if (bj_fold (player))
			bj_next_player ();
		break;
	case BJ_HIT:
		if (bj_hit (player))
			bj_next_player ();
		break;
	case BJ_STAY:
		if (bj_stay (player))
			bj_next_player ();
		break;

	case BJ_BELL:{
			if (player->flags & bjfPFIX)
				player->flags &= ~bjfPFIX;
			else
				player->flags |= bjfPFIX;

			bj_broadcast_msg (BJM_BELL, 0, player->userid,
					  bj_get_pfix (0, BJM_BELLACT,
						       (player->
							flags & bjfPFIX) ==
						       0));
		}
		break;

#ifdef CHEATS
	case BJ_SDECK:
		bj_show_deck (player);
		break;
	case BJ_GIVE_CARD:
		bj_give_card (player, i);
		break;
#endif


#ifdef DEVEL
	case BJ_START:
		if (STATUS == STAT_NOGAME)
			STATUS = STAT_NEWGAME;
		break;
	case BJ_DEBUG:
		bj_debug (bj_userid, i);
		break;
#endif

	};
}

void
bj_on (struct bj_player *player, int i)
{
	struct bj_player *pl;

	if (bj_ingame (bj_userid) != NULL) {
		bj_broadcast_msg (BJM_MULTJOIN, 0, bj_userid);
		return;
	}


	if ((P_MAX_PLAYERS) && (CUR_PLAYERS == P_MAX_PLAYERS)) {
		bj_broadcast_msg (BJM_NOMOREPL, 0, bj_userid);
		return;
	}


	pl = bj_new_player (bj_userid, 5000);
	bj_broadcast_msg (BJM_YJOIN, BJM_OJOIN, bj_userid,
			  bj_get_pfix (0, BJM_MPLAYER, (pl->flags & bjfSEX)),
			  bj_userid);

	if (i == 1)
		bj_execute_command (pl, BJ_BELL, 0);
}

void
bj_off (struct bj_player *player)
{
	struct bj_player *pl, *prev;

	if (player == NULL)
		return;

	player->flags &= ~bjfPLAY;
	play_count--;
	CUR_PLAYERS--;

	bj_broadcast_msg (BJM_YOFF, BJM_OOFF, player->userid,
			  bj_get_pfix (0, BJM_MPLAYER,
				       (player->flags & bjfSEX)),
			  player->userid);

	pl = player_list;
	prev = NULL;
	do {
		if (!strcmp (pl->userid, player->userid)) {

			if (pl == player_list) {
				player_list = pl->next;
			} else {
				if (pl == player_list_tail) {	/* we are the list tail, fix this */
					player_list_tail = prev;
					player_list_tail->next = NULL;
				} else {
					prev->next = player->next;	/* fix link */
				}
			}

			if ((c_player != NULL) &&
			    (!strcmp (player->userid, c_player->userid)))
				bj_next_player ();

			free (player);
			return;
		}
		prev = pl;
		pl = pl->next;
	} while (pl != NULL);

	bj_broadcast_msg (0, BJM_CNTDEALLOC, "");

//      exit(0);                /* this is hard, it will kick everybody to hell! */
}


int
bj_bet (struct bj_player *player, int bet)
{
	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return 0;
	}

	if (STATUS != STAT_BETTING) {
		bj_broadcast_msg (BJM_CNTBET, 0, player->userid);
		return 0;
	}


	if (strcasecmp (c_player->userid, player->userid)) {
		bj_broadcast_msg (BJM_WAITBET, 0, player->userid);
		return 0;
	}

	if (bet > P_MAX_BET) {
		bj_broadcast_msg (BJM_TOOHIGH, 0, player->userid, P_MAX_BET);
		return 0;
	}

	if (bet < 1) {
		bj_broadcast_msg (BJM_TOOLOW, 0, player->userid);
		return 0;
	}

	if (((bj_player_credits (player) - bet) >= P_MIN_CREDITS)
	    || (P_SYSOPS_NOCHARGE && (player->flags & bjfNOCHARGE))) {
		if ((player->bet + bet) >= current_bet) {

			if ((player->bet + bet) > current_bet)
				current_bet = player->bet + bet;

			total_bets += bet;
			bj_post_credits (player, -bet);
			player->bet += bet;

			bj_broadcast_msg (BJM_YBETCRED, BJM_OBETCRED,
					  player->userid, bet, bj_get_pfix (0,
									    BJM_MPLAYER,
									    (player->
									     flags
									     &
									     bjfSEX)),
					  player->userid, bet);

			return 1;

		} else
			bj_broadcast_msg (BJM_MINBET, 0, player->userid,
					  current_bet - player->bet);

	} else
		bj_broadcast_msg (BJM_NOCRED, 0, player->userid);

	return 0;
}

int
bj_raise (struct bj_player *player, int bet)
{
	int     bt;


	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return 0;
	}

	if (STATUS != STAT_BETTING) {
		bj_broadcast_msg (BJM_CNTRAISE, 0, player->userid);
		return 0;
	}

	if (strcasecmp (c_player->userid, player->userid)) {
		bj_broadcast_msg (BJM_WAITRAISE, 0, player->userid);

		return 0;
	}

	if (bet > P_MAX_BET) {
		bj_broadcast_msg (BJM_TOOHIGH, 0, player->userid, P_MAX_BET);
		return 0;
	}

	if (bet < 1) {
		bj_broadcast_msg (BJM_TOOLOW, 0, player->userid);
		return 0;
	}


/* the credits must be betted are, the difference to reach current bet, plus the amount raised */
	bt = current_bet - player->bet + bet;

	if (((bj_player_credits (player) - bt) >= P_MIN_CREDITS)
	    || (P_SYSOPS_NOCHARGE && (player->flags & bjfNOCHARGE))) {

		current_bet += bet;
		total_bets += bt;
		bj_post_credits (player, -bt);
		player->bet += bt;

		bj_broadcast_msg (BJM_YRAISE, BJM_ORAISE, player->userid, bet,
				  bj_get_pfix (0, BJM_MPLAYER,
					       (player->flags & bjfSEX)),
				  player->userid, bet);

		return 1;

	} else
		bj_broadcast_msg (BJM_NOCRED, 0, player->userid);

	return 0;
}

int
bj_call (struct bj_player *player)
{
	int     bt;

	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return 0;
	}

	if (STATUS != STAT_BETTING) {
		bj_broadcast_msg (BJM_CNTCALL, 0, player->userid);

		return 0;
	}

	if (strcasecmp (c_player->userid, player->userid)) {
		bj_broadcast_msg (BJM_WAITCALL, 0, player->userid);

		return 0;
	}

	if (((bj_player_credits (player) - (current_bet - player->bet)) >=
	     P_MIN_CREDITS)
	    || (P_SYSOPS_NOCHARGE && (player->flags & bjfNOCHARGE))) {

		bt = current_bet - player->bet;
		total_bets += bt;
		bj_post_credits (player, -bt);
		player->bet += bt;

		bj_broadcast_msg (BJM_YCALL, BJM_OCALL, player->userid,
				  bj_get_pfix (0, BJM_MPLAYER,
					       (player->flags & bjfSEX)),
				  player->userid);

		return 1;

	} else
		bj_broadcast_msg (BJM_NOCRED, 0, player->userid);

	return 0;
}

void
bj_pot (struct bj_player *player)
{
	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return;
	}

	bj_broadcast_msg (BJM_SEEPOT, 0, player->userid, total_bets);
}

void
bj_turn (struct bj_player *player)
{
	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return;
	}

	if (c_player == player)
		bj_broadcast_msg (BJM_YTURN, 0, player->userid);
	else
		bj_broadcast_msg (BJM_OTURN, 0, player->userid,
				  c_player->userid);
}

void
bj_scan (char *bjuser)
{
	struct bj_player *pl;
	char    buffer[2048], buf[256], buf1[10];;


	strcpy (buffer, "\n");
	strcat (buffer, bj_get_prompt (BJM_SCANHEADER));
	strcat (buffer, bj_get_prompt (BJM_SCANLINE));

	pl = player_list;
	while (pl != NULL) {
		strcpy (buf1, "-");
		if (!strcasecmp (bjuser, pl->userid))
			sprintf (buf1, "%i", bj_player_credits (pl));


		sprintf (buf, bj_get_prompt (BJM_SCANREC), pl->userid, buf1,
			 (pl->flags & bjfPLAY) ? '*' : ' ',
			 (pl->flags & bjfSTAY) ? '+' : ' ');
		strcat (buffer, buf);

		pl = pl->next;
	}

	sprintf (buf, "%s", bj_get_prompt (BJM_SCANLINE));
	strcat (buffer, buf);

	bj_broadcast_msg (BJM_STRING, 0, bjuser, buffer);
}

int
bj_fold (struct bj_player *player)
{
	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return 0;
	}

	if (STATUS != STAT_BETTING) {
		bj_broadcast_msg (BJM_CNTFOLD, 0, player->userid);
		return 0;
	}

	if (strcasecmp (c_player->userid, player->userid)) {
		bj_broadcast_msg (BJM_WAITFOLD, 0, player->userid);
		return 0;
	}

	player->bet = 0;
	player->flags &= ~bjfPLAY;
	play_count--;

	bj_broadcast_msg (BJM_YFOLD, BJM_OFOLD, player->userid,
			  bj_get_pfix (0, BJM_MPLAYER,
				       (player->flags & bjfSEX)),
			  player->userid);

	return 1;
}

/***************************/
/* card specific functions */
/***************************/

int
bj_card_sum (struct bj_player *player)
{
	int     i, sum, ace;
	char    t1, t2;

	sum = ace = 0;
	for (i = 0; i < player->cards_count; i++) {
		t1 = card_sign (player->cards[i]);
		t2 = card_value (player->cards[i]);

		if (t2 <= '9') {
			if (t2 == '0')
				sum += 10;
			else
				sum += (int) (t2 - '0');
		}

		if (t2 >= 'A') {
			sum += 10;

			if (t2 == 'A') {
				sum += 1;
				ace++;
			}
		}
	}

	while ((sum > 21) && (ace > 0)) {
		ace--;
		sum -= 10;
	}

	return sum;
}


int
bj_get_rand (int min, int max)
{
	return ((int)
		((float) (max - min) * rand () / ((float) RAND_MAX + 1.0))) +
	    min;
}


int
bj_hit (struct bj_player *player)
{
	int     card, i;
	char    buffer[250];

	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return 0;
	}

	if (STATUS != STAT_HITTING) {
		bj_broadcast_msg (BJM_CNTHIT, 0, player->userid);
		return 0;
	}

	if (strcasecmp (c_player->userid, player->userid)) {
		bj_broadcast_msg (BJM_WAITHIT, 0, player->userid);
		return 0;
	}

	card = bj_get_card ();
	player->cards[player->cards_count] = card;
	player->cards_count++;

	map_cards (&card, 1);
	strcpy (buffer, "\n");
	for (i = 0; i < 7; i++) {
		strcat (buffer, buf_index (i));
		strcat (buffer, "\n");
	}


	bj_broadcast_msg (BJM_YHIT, BJM_OHIT, player->userid, buffer,
			  bj_get_pfix (0, BJM_MPLAYER,
				       (player->flags & bjfSEX)),
			  player->userid);

	if (bj_card_sum (player) > 21) {
		bj_broadcast_msg (BJM_YBURN, BJM_OBURN, player->userid,
				  bj_get_pfix (0, BJM_MPLAYER,
					       (player->flags & bjfSEX)),
				  player->userid);

		player->flags &= ~bjfPLAY;
		play_count--;

		return 1;
	}
	return 0;
}


void
bj_hand (struct bj_player *player)
{
	int     i;
	char    buffer[4096], buf[150];

	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return;
	}

	if (player->cards_count == 0) {
		bj_broadcast_msg (BJM_NOCARDS, 0, player->userid);
		return;
	}


	map_cards (player->cards, player->cards_count);
	strcpy (buffer, "\n");

	for (i = 0;; i++) {
/*		bj_logmsg("getting buf_index(%i)", i);*/
		strcpy (buf, buf_index (i));
		if (strlen (buf) > 0) {
			strcat (buffer, buf);
			strcat (buffer, "\n");
		} else
			break;
	}

	sprintf (buf, bj_get_prompt (BJM_CARDSUM), bj_card_sum (player));

	strcat (buffer, buf);
	bj_broadcast_msg (BJM_STRING, 0, player->userid, buffer);
}

/**********************/


int
bj_stay (struct bj_player *player)
{
	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return 0;
	}

	if (strcasecmp (c_player->userid, player->userid)) {
		bj_broadcast_msg (BJM_WAITSTAY, 0, player->userid);
		return 0;
	}

	if (STATUS != STAT_HITTING) {
		bj_broadcast_msg (BJM_CNTSTAY, 0, player->userid);
		return 0;
	}

	bj_broadcast_msg (BJM_YSTAY, BJM_OSTAY, player->userid,
			  bj_get_pfix (0, BJM_MPLAYER, player->flags & bjfSEX),
			  player->userid);

	player->flags |= bjfSTAY;
	stay_count++;

	return 1;
}


int
bj_find_winner (void)
{
	struct bj_player *pl;
	int     card_sum = 0;
	int     i = 0, j = 0;
	char    buffer[512];


	pl = player_list;

	while (pl != NULL) {
		if ((pl->flags & bjfSTAY) && (bj_card_sum (pl) > card_sum))
			card_sum = bj_card_sum (pl);

		pl = pl->next;
	}

	if (!card_sum) {
		bj_broadcast_msg (0, BJM_NOWINNER, "");
		return 0;
	}

	pl = player_list;
	while (pl != NULL) {
		if ((pl->flags & bjfSTAY) && (bj_card_sum (pl) == card_sum)) {
			pl->flags |= bjfWIN;
			i++;
		}
		pl = pl->next;
	}


	strcpy (buffer, "");

	pl = player_list;
	while (pl != NULL) {
		if (pl->flags & bjfWIN) {
			j++;

			sprintf (buffer, "%s %s %s %s", buffer,
				 ((j >
				   1) ? ((j ==
					  i) ? bj_get_prompt (BJM_AND) : "\b,")
				  : "\b"), bj_get_pfix (0, BJM_SMTHE,
							(pl->flags & bjfSEX)),
				 pl->userid);
		}

		pl = pl->next;
	}

	bj_broadcast_msg (0, BJM_WINNERS, "",
			  bj_get_pfix (0, BJM_SWON, (j == 1)), buffer,
			  card_sum);


	total_bets = ((100 - P_SYSTEM_PERC) * total_bets / 100);
	j = total_bets / i;

	pl = player_list;
	while (pl != NULL) {
		if (pl->flags & bjfWIN) {
			bj_post_credits (pl, j);
			bj_broadcast_msg (BJM_YGETCRED, 0, pl->userid, j);
		}
		pl = pl->next;
	}


	return i;
}

/* search for the next available card with value of i, and give it to player */
void
bj_give_card (struct bj_player *player, int i)
{
	while (1) {
		if (card_value (card_deck[card_index++]) == i) {
			card_index--;
			bj_hit (player);
			return;
		}
	}
}

/**************************/
/* deck oriented function */
/**************************/

void
bj_show_deck (struct bj_player *player)
{
	int     i, j;
	char    t1, t2;
	char    buffer[2048], buf[50];

	if (STATUS == STAT_NOGAME) {
		bj_broadcast_msg (BJM_NOGAME, 0, player->userid);
		return;
	}

	strcpy (buffer, "\n");

	j = 0;
	for (i = 0; i < 52; i++) {
		t1 = card_sign (card_deck[(card_index + i) % 52]);
		t2 = card_value (card_deck[(card_index + i) % 52]);
		j++;

/*		sprintf(buf, bj_get_prompt( BJM_CARD ) , t1, t2);*/
		strcat (buffer, buf);
	}
	strcat (buffer, "\n");

	bj_broadcast_msg (BJM_STRING, 0, player->userid, buffer);
}



void
shuffle_deck (void)
{				/* structure from Major */
	int     i, temp, swap;

	for (i = 0; i < 52; i++)
		card_deck[i] = i;

	for (i = 0; i < 51; i++) {	/* well, lets hope this works! */
		temp = card_deck[i];
		swap = bj_get_rand (i, 52);
		card_deck[i] = card_deck[swap];
		card_deck[swap] = temp;
	}

	card_index = 0;
}

/* return the card number of the next card in the deck and advance index */
int
bj_get_card (void)
{
	int     i;

	i = card_deck[card_index++];
	if (card_index == 52)
		shuffle_deck ();

	return i;
}

void
bj_deal_cards ()
{
	struct bj_player *pl;

	shuffle_deck ();

	pl = player_list;
	while (pl != NULL) {
		pl->cards[pl->cards_count++] = bj_get_card ();	/* this works because pl->cards[] is */
		pl->cards[pl->cards_count++] = bj_get_card ();	/* always zero based */

		bj_post_credits (pl, -P_LIGHT_CREDITS);
		bj_broadcast_msg (BJM_LIGHT, 0, pl->userid, P_LIGHT_CREDITS);
		total_bets += P_LIGHT_CREDITS;

		pl = pl->next;

	}
}

#ifdef DEVEL
void
bj_debug (char *bjuser, int i)
{
	char    buffer[8192], buf[100];
	struct bj_player *pl;

	strcpy (buffer, "\n--- DEBUGGING INFO \033!F-");

	pl = bj_ingame (bjuser);

	if (P_SYSOPS_DEBUG) {
		switch (i) {
		case 1:{
				sprintf (buf, "\nCurrent player name : %s\n",
					 bjuser);
				strcat (buffer, buf);
				if (pl != NULL) {
					sprint (buf, "Prefix #%i\n",
						(pl->flags & bjfPFIX) ? 2 : 1);
					strcat (buffer, buf);
				}
			};
			break;
		case 2:{
				sprintf (buf, "\nRandom number (1-100) : %i\n",
					 bj_get_rand (1, 100));
				strcat (buffer, buf);
			};
			break;
		}

		strcat (buffer, "\033!F-\n");

		bj_broadcast_msg (BJM_STRING, 0, bjuser, buffer);
	}
}
#endif


/* End of File */
