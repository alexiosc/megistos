/*****************************************************************************\
 **                                                                         **
 **  FILE:     dbfrom.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **            B, August 1996, Version 0.9                                  **
 **  PURPOSE:  Database, findmsgfrom() feature.                             **
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
 * $Id: dbfrom.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: dbfrom.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/02/29 18:08:31  alexios
 * Include file changes.
 *
 * Revision 1.5  2003/12/25 13:33:28  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: dbfrom.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <libtyphoon/typhoon.h>
#include "mbk_emailclubs.h"
#include "email.h"
#include "ecdbase.h"


static struct fromc fromc;


static int
getfl (int *first, int *last)
{
	struct ecidx f, l;
	struct fromc fromc1;

	/* Get the first key of the database. */

	strcpy (fromc1.from, fromc.from);
	fromc1.num = 0;
	if (d_keyfind (FROMC, &fromc1) != S_OKAY)
		if (d_keynext (FROMC) != S_OKAY)
			return BSE_NFOUND;


	/* Read the first record. If we can't something's VERY wrong. Panic. */

	if (d_recread (&f) != S_OKAY) {
		error_fatal ("Unable to read first FROM key.");
	}


	/* Now get the last key. */

	l.num = fromc1.num = f.num;
	strcpy (fromc1.from, f.from);
	for (;;) {
		if (d_keynext (FROMC) != S_OKAY)
			break;
		if (d_keyread (&fromc1) != S_OKAY)
			break;
		if (strcmp (fromc1.from, fromc.from))
			break;
		else
			l.num = fromc1.num;
	}

	*first = f.num;
	*last = l.num;

	return BSE_FOUND;
}


static int
getmsgno (int *msgno, int dir)
{
	int     first, last;
	struct fromc f;


	/* Look for the desired message. */

	if (d_keyfind (FROMC, &fromc) == S_OKAY)
		return BSE_FOUND;


	/* Couldn't find that specific message. Let's look for another one. */
	/* Start by getting first and last messages. */

	if (getfl (&first, &last) == BSE_NFOUND)
		return BSE_NFOUND;

	if (dir == BSD_LT) {

		/* Moving backwards. Three subcases here as well. */


		/* msgno < first number? No record found. */

		if (*msgno < first)
			return BSE_BEGIN;


		/* msgno > last number? Since we're going down, the last # applies. */

		if (*msgno > last)
			return (*msgno = last, BSE_FOUND);


		/* Otherwise, we've hit a gap between messages. Choose the next one. */

		d_keyfind (FROMC, &fromc);

		if (d_keynext (FROMC) != S_OKAY) {
			error_fatal
			    ("No next FROMC key. This should never happen.");
		}

		if (d_keyread (&f) != S_OKAY) {
			error_fatal
			    ("Unable to read FROMC key. Should never happen.");
		}

		*msgno = f.num;

	} else {

		/* Moving up (GT) */

		/* Distinguish the same three cases, but treat things a bit different. */


		/* msgno < first message. We're going up, so we choose #first. */

		if (*msgno < first)
			return (*msgno = first, BSE_FOUND);


		/* msgno > last. Since we're going up, we're out of messages. */

		if (*msgno > last)
			return BSE_END;


		/* This is the same as before. Got two copies of it for clarity. */

		d_keyfind (FROMC, &fromc);
		if (d_keynext (FROMC) != S_OKAY) {
			error_fatal
			    ("No next FROMC key. This should never happen.");
		}

		if (d_keyread (&f)) {
			error_fatal
			    ("Unable to read FROMC key. Should never happen.");
		}

		*msgno = f.num;
	}

	/* We've chosen a value for msgno, now say so. */

	return BSE_FOUND;
}


int
findmsgfrom (int *msgno, char *whom, int targetnum, int direction)
{
	int     res;

	/* Prepare the key */

	strcpy (fromc.from, whom);
	fromc.num = targetnum;


	/* Check for existence */

	d_keyfind (FROMC, &fromc);


	/* If we're only checking for existence, return now */

	if (direction == BSD_EQ)
		return (db_status == S_OKAY) ? BSE_FOUND : BSE_NFOUND;


	/* Now look for other applicable message numbers. */

	*msgno = targetnum;

	if ((res = getmsgno (msgno, direction)) == BSE_FOUND) {
		DB_ADDR rec;

		fromc.num = *msgno;
		d_keyfind (FROMC, &fromc);
		if (d_crget (&rec) == S_OKAY)
			d_keyread (&fromc);
		else
			return BSE_NFOUND;
		return strcmp (fromc.from, whom) ? BSE_NFOUND : BSE_FOUND;
	}
	return res;
}


int
npmsgfrom (int *msgno, char *whom, int targetnum, int dir)
{
	int     j;

	if (dir == BSD_GT)
		j = d_keynext (FROMC);
	else
		j = d_keyprev (FROMC);

	if (j != S_OKAY)
		return BSE_NFOUND;

	if (d_keyread (&fromc) != S_OKAY) {
		error_fatal ("Unable to read key though it exists.\n");
	}

	if (strcmp (whom, fromc.from))
		return BSE_NFOUND;
	if (dir == BSD_GT && fromc.num < targetnum)
		return BSE_NFOUND;
	if (dir == BSD_LT && fromc.num > targetnum)
		return BSE_NFOUND;

	*msgno = fromc.num;
	return BSE_FOUND;
}


/* End of File */
