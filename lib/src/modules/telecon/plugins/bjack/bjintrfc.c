/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: bjintrfc.c                                                       **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: interface file with the BBS program                           **
 **  NOTES: current only Megistos BBS is implemented                        **
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
 * Revision 0.8  1999/09/20 21:43:19  valis
 * added support for 2 different prompts
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
 * Revision 0.4  1999/08/24 12:11:53  valis
 * added bj_get_cmd()
 *
 * Revision 1.4  1999/08/24 11:56:34  valis
 * added bj_get_cmd()
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/ipc.h>
#include <sys/msg.h>


static const char rcsinfo[] =
    "$Id$";


#ifdef MEGISTOS_BBS

#ifdef LOGDIR
#undef LOGDIR
#endif

#include <megistos/bbs.h>
#include <telecon.h>
#include <teleconplugins.h>

#endif				/* MEGISTOS_BBS */


#include "bjconf.h"
#include "bjack.h"
#include "bjintrfc.h"

#ifdef BBSPROMPTS

#ifdef MEGISTOS_BBS
#include "mbk_bjack.h"
#endif

#else
#include "bjmsg.h"

#endif				/* BBSPROMPTS */


char    temp_prompt[8192];
char    pfix_prompt[3][50];	/* define 3 arrays for pre/post-fixes */
char    buffer[4096], buf1[4096];


char   *
bj_get_prompt (int index)
{

	strcpy (temp_prompt, "");
	if (!index)
		return temp_prompt;

#ifdef BBSPROMPTS
	msg_set (msg);
	strcpy (temp_prompt, msg_get (index));

#ifdef DEBUG_LOG
	bj_logmsg ("--- bj_get_prompt(): read #%i len=%i text=%s", index,
		   strlen (temp_prompt), temp_prompt);
#endif

	return temp_prompt;
#else
	return BJ_PROMPTS[index];
#endif
}


char   *
bj_get_pfix (int pidx, int index, int value)
{

	strcpy (pfix_prompt[pidx], "");
	if (!index)
		return pfix_prompt[pidx];

#ifdef BBSPROMPTS
	msg_set (msg);

/* if value=1 then get message (index), otherwise get message (index+1) */
	strcpy (pfix_prompt[pidx], msg_getunit (index, value));

#ifdef DEBUG_LOG
	bj_logmsg ("--- bj_get_pfix: read #%i len=%i text=%s", index,
		   strlen (pfix_prompt[pidx]), pfix_prompt[pidx]);
#endif

	return pfix_prompt[pidx];
#else
	return BJ_PROMPTS[index];
#endif
}

char   *
fx_bj_msg (struct chanusr *u)
{
	struct bj_player *pl;

	pl = player_list;
	while (pl != NULL) {
		if (!strcasecmp (pl->userid, u->userid))
			break;
		pl = pl->next;
	}

	if (!strcasecmp (bj_message.userid, u->userid)) {
		sprint (out_buffer, bj_message.this_msg);
		return ((out_buffer[0]) ? out_buffer : NULL);
	} else {
		sprint (out_buffer, bj_message.other_msg);
		return ((pl ==
			 NULL) ? NULL : out_buffer[0] ? out_buffer : NULL);
	}
}


void
bj_broadcast_msg (int this_idx, int other_idx, char *userid, ...)
{
	va_list va_l;

	char   *buf2;

	strcpy (buf1, "");

	if (this_idx > 0)
		strcat (buf1, bj_get_prompt (this_idx));

	strcat (buf1, "~~");

	if (other_idx > 0)
		strcat (buf1, bj_get_prompt (other_idx));


	strcpy (buffer, "");
	va_start (va_l, userid);
	vsprintf (out_buffer, buf1, va_l);
	sprint (buffer, out_buffer);
	va_end (va_l);

	buf2 = buffer;

/* restore the two concatenated strings */
	strcpy (bj_message.this_msg, strsep (&buf2, "~~"));
	while (*buf2 == '~')
		buf2++;		/* eliminate the tildes */


	strcpy (bj_message.other_msg, buf2);
	strcpy (bj_message.userid, userid);


/*	
	if (bj_message.this_msg[0]) {
		sprintf(buffer, "\033!(%s\033!)", bj_message.this_msg);
		strcpy(bj_message.this_msg, buffer);
	}
	
	if (bj_message.other_msg[0]) {
		sprintf(buffer, "\033!(%s\033!)", bj_message.other_msg);
		strcpy(bj_message.other_msg, buffer);
	}
*/

	broadcastchnall (bj_channel, fx_bj_msg, 1);
}


/*******************************************************************/
/* The following functions are specific to the BBS program running */
/*  One must edit them accordingly to work for other BBS programs  */
/*******************************************************************/


/* returns the credits that a player owns. It should call the apropriate library function */
int
bj_player_credits (struct bj_player *player)
{

#ifdef FAKE_POSTING

	return player->credits;

#else

#ifdef MEGISTOS_BBS
	useracc user, *uacc = &user;

	if (!usr_insys (player->userid, 0))
		usr_loadaccount (player->userid, uacc);
	else
		uacc = &othruseracc;
	if (!uacc)
		return 0;

	return uacc->credits;

#endif				/* MEGISTOS_BBS */

#endif				/* FAKE_POSTING */
}


/* posts a user some credits (+/-). It should call the apropriate library function */
void
bj_post_credits (struct bj_player *player, int credits)
{

#ifdef FAKE_POSTING
	player->credits += credits;

#else

#ifdef MEGISTOS_BBS

/* do not charge the damn sysops */
	if ((player->flags & bjfNOCHARGE) != 0)
		return;


/* this is extremely dangerous */
	loadsysvars ();

/* this is the  Megistos library function to post credits to a user */
	usr_postcredits (player->userid, credits, 0);

/* we done the first, shall we stop here? */
	savesysvars ();

#endif				/* MEGISTOS_BBS */

#endif				/* FAKE_POSTING */


/* log all credit postings for security reasons */
#ifdef POST_LOG

#ifdef FAKE_POSTING
	bj_logmsg ("*FAKE* Posting player %s [%i] credits", player->userid,
		   credits);
#else
	bj_logmsg ("*REAL* Posting player %s [%i] credits", player->userid,
		   credits);
#endif

/* NOTE: Logging is done after the library calls to ensure credit posting (!) */

#endif				/* POST_LOG */
}


/* return 1 for male, 0 for female (hope there won't be a third sex...) */
int
bj_player_sex (struct bj_player *player)
{
#ifdef MEGISTOS_BBS
	useracc_t user, *uacc = &user;

	if (!usr_insys (player->userid, 0))
		usr_loadaccount (player->userid, uacc);
	else
		uacc = &othruseracc;
	if (!uacc)
		return 0;

	return ((uacc->sex == 'M') ? bjfSEX : 0);

#endif

	return 0;		/* just in case */
}


/* return 0 if player will be charged, 1 if he can bet to death */
int
bj_player_nocharge (struct bj_player *player)
{
#ifdef MEGISTOS_BBS
/*
  In Megistos there are some classes that have no credit charge. These classes
  should be scanned and its users must not be charged for positive credits (subtract).
  Positive charges will be allowed, but can also be deactivated
*/
	classrec_t class, *uclass = &class;

/* check if option disabled */
	if (!P_SYSOPS_NOCHARGE)
		return 0;

	uclass = cls_find (othruseracc.curclss);

	if (uclass->flags & CLF_NOCHRGE)
		return bjfNOCHARGE;
	else
		return 0;

#endif				/* MEGISTOS_BBS */

	return 0;		/* just in case */
}


/* pass the userid and the command text */
int
bj_get_cmd (char *userid, char *text)
{
#ifdef MEGISTOS_BBS
	struct pluginmsg p;
	int     n;

	if (thisuseronl.flags & OLF_MMCONCAT) {
		strcpy (text, thisuseronl.input);
		strcpy (userid, thisuseronl.userid);
		thisuseronl.flags &= ~OLF_MMCONCAT;
		return 1;
	}

	n = msgrcv (qid, (struct msgbuf *) &p, sizeof (p) - sizeof (long), 0,
		    IPC_NOWAIT);

	if (n > 0) {
		strcpy (userid, p.userid);
		strcpy (text, p.text);

		return n;
	} else {
		userid[0] = 0;
		text[0] = 0;
	}

	return n;

#endif				/* MEGISTOS_BBS */

	return 0;
}


/* End of File */
