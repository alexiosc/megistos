/*****************************************************************************\
 **                                                                         **
 **  FILE:     actions.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 0.5                                    **
 **  PURPOSE:  Teleconferences, handle action verbs                         **
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
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:37:29  alexios
 * Adjusted #includes. Minor cosmetic changes. Removed dependency on
 * compiled action list (via mbk_teleactions.h) by hardwiring indices for
 * the number of action verbs and the beginning of the action list, which
 * was really all we needed before, too.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1998/03/10 11:17:28  alexios
 * Fixed insidious little bug that would 'change' sex to
 * targets of actions.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "telecon.h"
#include "actions.h"
#if 0
#  include <mbk/mbk_teleactions.h>
#else
#  define NUMVERBS 2
#  define BEGNVERB (NUMVERBS+1)
#endif


static struct actionidx *actions = NULL;

static int numactions = 0;

static promptblock_t *actionblk = NULL;

static char *inpptr;


void
initactions ()
{
	int     i, pr;
	char    type;

	actionblk = msg_open ("teleactions");
	numactions = msg_int (NUMVERBS, 0, 1 << 20);	/* 1M actions SHOULD suffice */
	if (!numactions) return;
	if (actions) free (actions);
	actions = alcmem (numactions * sizeof (struct actionidx));

	pr = BEGNVERB + 1;

	for (i = 0; i < numactions; i++) {
                /*  print("%d. ",pr);fflush(stdout); */
		actions[i].index = pr;
		actions[i].verb = strdup (msg_get (pr));
		type = msg_char (pr + 1);
                /*  print("%c (%s)\n",type,actions[i].verb); */
		switch (type) {
		case TYPE_SIMPLE:
			pr += 4 + 2 * NUMLANGUAGES;
			break;
		case TYPE_OBJECT:
			pr += 4 + 5 * NUMLANGUAGES;
			break;
		case TYPE_DOUBLE:
			pr += 4 + 6 * NUMLANGUAGES;
			break;
		case TYPE_ADVERB:
			pr += 4 + 3 * NUMLANGUAGES;
			break;
		case TYPE_GENERIC:
			pr += 4 + 2 * NUMLANGUAGES;
			break;
		default:
			error_fatal ("Action verb '%s' has invalid type '%c'.",
				     actions[i].verb, type);
		}
	}
}


static int fx_pr, fx_objopt;
static char *fx_fmtuser = NULL, *fx_fmtsmpl = NULL, *fx_fmtothr = NULL;
static char *fx_fmtall = NULL, *fx_fmttrgt = NULL, *fx_fmtscrt = NULL;
static char *fx_fmtadvb = NULL, *fx_fmtgnrc = NULL, *fx_fmtusec = NULL;
static char fx_tmp[8192];
char    fx_target[24], fx_targetsex;
int     fx_targetcol;



void
sendusermsg (int pr)
{
	int     lang;

	if (fx_objopt & OBJ_SECRETLY) {
		if (!fx_fmtusec) {
			msg_set (msg);
			fx_fmtusec = strdup (msg_get (FMTUSEC));
		}
	} else {
		if (!fx_fmtuser) {
			msg_set (msg);
			fx_fmtuser = strdup (msg_get (FMTUSER));
		}
	}

	msg_set (actionblk);
	for (lang = thisuseracc.language - 1; lang >= 0; lang--) {
		char   *s = msg_get (pr + 4 + lang);

		if (s && *s) {
			print (fx_objopt & OBJ_SECRETLY ? fx_fmtusec :
			       fx_fmtuser, s);
			return;
		}
	}
	msg_set (msg);
	prompt (VERBSENT);
}


char   *
fx_simple (struct chanusr *u)
{
	msg_set (actionblk);
	sprompt (fx_tmp, fx_pr + othruseracc.language - 1);
	sprint (out_buffer, fx_fmtsmpl, fx_tmp);
	return out_buffer;
}


void
simpleaction (int pr)
{
	fx_pr = pr + 4 + ML;
	if (!fx_fmtsmpl) {
		msg_set (msg);
		fx_fmtsmpl = strdup (msg_get (FMTSMPL));
	}
	if (broadcast (fx_simple) > 0)
		sendusermsg (pr);
	else {
		msg_set (msg);
		prompt (SIU0);
		msg_set (actionblk);
	}
}


char   *
fx_generic (struct chanusr *u)
{
	msg_set (actionblk);
	sprompt (fx_tmp, fx_pr + othruseracc.language - 1);
	sprint (out_buffer, fx_fmtgnrc, fx_tmp, inpptr);
	return out_buffer;
}


void
genericaction (int pr, char *verb)
{
	if (!inpptr || inpptr[0] == 0) {
		msg_set (msg);
		prompt (VERBNMT, verb);
		return;
	}
	fx_pr = pr + 4 + ML;
	if (!fx_fmtgnrc) {
		msg_set (msg);
		fx_fmtgnrc = strdup (msg_get (FMTGNRC));
	}
	if (broadcast (fx_generic) > 0)
		sendusermsg (pr);
	else {
		msg_set (msg);
		prompt (SIU0);
		msg_set (actionblk);
	}
}


char   *
fx_adverb (struct chanusr *u)
{
	msg_set (actionblk);
	sprompt (fx_tmp, fx_pr + othruseracc.language - 1);
	sprint (out_buffer, fx_fmtadvb, fx_tmp, inpptr);
	return out_buffer;
}


void
adverbaction (int pr)
{
	if (!inpptr || inpptr[0] == 0) {
		simpleaction (pr);
		return;
	}

	fx_pr = pr + 4 + 2 * ML;
	if (!fx_fmtadvb) {
		msg_set (msg);
		fx_fmtadvb = strdup (msg_get (FMTADVB));
	}
	if (broadcast (fx_adverb) > 0) {
		msg_set (msg);
		prompt (VERBSENT);
	} else {
		msg_set (msg);
		prompt (SIU0);
		msg_set (actionblk);
	}
}


char   *
fx_object (struct chanusr *u)
{
	msg_set (actionblk);
	if (fx_objopt & OBJ_ALL) {
		sprompt (fx_tmp,
			 fx_pr + (4 + 2 * ML) + othruseracc.language - 1);
		sprint (out_buffer, fx_fmtall, fx_tmp);
	} else if (fx_objopt & OBJ_SECRETLY) {
		if (!sameas (u->userid, fx_target))
			return NULL;
		sprompt (fx_tmp,
			 fx_pr + (4 + 4 * ML) + othruseracc.language - 1);
		sprint (out_buffer, fx_fmtscrt, fx_tmp);
	} else if (sameas (u->userid, fx_target)) {
		sprompt (fx_tmp,
			 fx_pr + (4 + 3 * ML) + othruseracc.language - 1);
		sprint (out_buffer, fx_fmttrgt, fx_tmp);
	} else {
		sprompt (fx_tmp, fx_pr + (4 + ML) + othruseracc.language - 1);
		sprint (out_buffer, fx_fmtothr, fx_tmp);
	}
	return out_buffer;
}


void
objectaction (int pr, char *verb, int typeD)
{
	char    tmp[8192];

	msg_set (msg);
	if (!inpptr || inpptr[0] == 0) {
		prompt (VERBNOBJ, verb);
		return;
	}

	tmp[0] = fx_objopt = OBJ_NORMAL;
	switch (sscanf (inpptr, "%s %s", fx_tmp, tmp)) {
	case 0:
		prompt (VERBNOBJ, verb);
		return;
	case 1:
		fx_objopt = OBJ_NORMAL;
		break;
	case 2:
		if (sameas (tmp, stgsec1) || sameas (tmp, stgsec2))
			fx_objopt |= OBJ_SECRETLY;
	}

	if (sameas (fx_tmp, stgall1) || sameas (fx_tmp, stgall2)) {
		fx_objopt |= OBJ_ALL;
		if (fx_objopt & OBJ_SECRETLY) {
			prompt (VERBNAS);
			return;
		}
	} else {
		strncpy (fx_target, fx_tmp, sizeof (fx_target));
		if (!tlcuidxref (fx_target, 0)) {
			prompt (VERBUID, fx_target);
			return;
		}
		usr_insys (fx_target, 0);
		fx_targetsex = othruseracc.sex;
		fx_targetcol = othruseraux.colour;
	}

	msg_set (actionblk);
	fx_pr = typeD ? pr + ML : pr;

	if (!fx_fmtothr) {
		msg_set (msg);
		fx_fmtothr = strdup (msg_get (FMTOTHR));
	}
	if (!fx_fmttrgt) {
		msg_set (msg);
		fx_fmttrgt = strdup (msg_get (FMTTRGT));
	}
	if (!fx_fmtall) {
		msg_set (msg);
		fx_fmtall = strdup (msg_get (FMTALL));
	}
	if (!fx_fmtscrt) {
		msg_set (msg);
		fx_fmtscrt = strdup (msg_get (FMTSCRT));
	}

	if (broadcast (fx_object) > 0)
		sendusermsg (pr);
	else {
		msg_set (msg);
		prompt (SIU0);
		msg_set (actionblk);
	}
}


void
doubleaction (int pr, char *verb)
{
	if (!inpptr || inpptr[0] == 0)
		simpleaction (pr);
	else
		objectaction (pr, verb, 1);
}


int
actionax (int pr)
{
	if (!key_owns (&thisuseracc, msg_int (pr + 2, 0, 129)))
		return 0;
	else {
		char   *access = strdup (msg_get (pr + 3));
		char    userid[26];

		if (!access[0]) {
			free (access);
			return 1;
		} else {
			sprintf (userid, "(%s)", thisuseracc.userid);
			if (!strstr (msg_get (pr + 3), userid)) {
				free (access);
				return 0;
			}
		}
	}
	return 0;
}


struct actionidx *
bsrch (char *key, int left, int right)
{
	if (left > right)
		return NULL;
	else {
		int     m = (left + right) / 2;
		int     c = strcasecmp (key, actions[m].verb);

		if (!c)
			return &actions[m];
		else if (c < 0)
			return bsrch (key, left, m - 1);
		return bsrch (key, m + 1, right);
	}
	return NULL;		/* just to avoid warnings */
}


struct actionidx *
bs (char *key)
{
	return bsrch (key, 0, numactions - 1);
}


int
handleaction (char *s)
{
	struct actionidx *a = NULL;
	char   *key;
	int     n;

	if (*s == '/')
		return 0;

	if (!key_owns (&thisuseracc, actkey))
		return 0;
	if (!thisuseraux.actions)
		return 0;

	fx_objopt = OBJ_NORMAL;

	key = alcmem (strlen (s) + 1);

	n = 0;
	if (!sscanf (s, "%s %n", key, &n)) {
		free (key);
		msg_set (msg);
		return 0;
	}

	if (!n)
		inpptr = NULL;
	else
		inpptr = s + n;

	a = bs (key);

	free (key);

	if (!a) {
		msg_set (msg);
		return 0;
	}

	/*  print("Action=(%s), Index=%d\n",a->verb,a->index); */

	msg_set (actionblk);
	if (!actionax (a->index)) {
		msg_set (msg);
		return 0;
	}

	switch (msg_char (a->index + 1)) {
	case TYPE_SIMPLE:
		simpleaction (a->index);
		break;
	case TYPE_OBJECT:
		objectaction (a->index, a->verb, 0);
		break;
	case TYPE_DOUBLE:
		doubleaction (a->index, a->verb);
		break;
	case TYPE_ADVERB:
		adverbaction (a->index);
		break;
	case TYPE_GENERIC:
		genericaction (a->index, a->verb);
		break;
	}

	msg_set (msg);
	return 1;
}


void
actionctl (char *s)
{
	char    cmd[2048] = { 0 };
	int     i;

	i = sscanf (s, "%*s %s", cmd);

	if ((i < 1) || sameas (cmd, "?") || sameas (cmd, "HELP")) {
		prompt (ACTHLP);
		return;
	} else if (!key_owns (&thisuseracc, actkey)) {
		prompt (ACTNAX);
		return;
	} else if (sameas (cmd, "ON")) {
		thisuseraux.actions = 1;
		prompt (ACTON);
		return;
	} else if (sameas (cmd, "OFF")) {
		thisuseraux.actions = 0;
		prompt (ACTOFF);
		return;
	} else if (sameas (cmd, "LIST")) {
		prompt (ACTLST);
		return;
	} else {
		prompt (ACTHLP);
		return;
	}
}


/* End of File */
