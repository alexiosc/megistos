/*****************************************************************************\
 **                                                                         **
 **  FILE:     utils.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, miscellaneous utilities                     **
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
 * Revision 1.5  2003/12/27 12:29:38  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1998/12/27 16:10:27  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 0.5  1998/08/14 11:45:25  alexios
 * Migrated to the new channel engine.
 *
 * Revision 0.4  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1998/03/10 11:17:28  alexios
 * Very slight changes while trying to find the sex changing
 * bug.
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
#include "mbk_telecon.h"
#include <mbk/mbk_sysvar.h>


#define CACHESIZE 32

static char xrefcache[CACHESIZE][24];

static int cachesize = 0;


static void
cachepush (char *s)
{
	memcpy (&xrefcache[1], &xrefcache[0], (CACHESIZE - 1) * 24);
	strcpy (xrefcache[0], s);
	if (cachesize < CACHESIZE)
		cachesize++;
}


static int
cachechk (char *s)
{
	int     i;

	for (i = 0; i < cachesize; i++) {
		if (sameto (s, xrefcache[i])) {
			strcpy (s, xrefcache[i]);
			return 1;
		}
	}
	return 0;
}


int
tlcuidxref (char *userid, int inchannel)
{
	char    matches[10][80];
	int     num = 0;
	int     retry = 0;
	int     i, cache;
	channel_status_t status;

      tryagain:
	if (!strlen (userid))
		return 0;
	cache = cachechk (userid);
	if (usr_insys (userid, 1)) {
		if (!cache)
			cachepush (userid);
		if (inchannel) {
			if ((!strcmp (curchannel, othruseronl.telechan)) &&
			    (othruseronl.flags & OLF_INTELECON)) {
				if (!cache)
					cachepush (userid);
				return 1;
			} else
				return 0;
		} else {
			if (!cache)
				cachepush (userid);
			return 1;
		}
	}

	num = 0;
	memset (matches, 0, sizeof (matches));

	for (i = 0; i < chan_count; i++) {
		if (!channel_getstatus (channels[i].ttyname, &status))
			continue;

		if (status.result == LSR_USER) {
			if (usr_insys (status.user, 1)) {
				if (sameto (userid, status.user) && (num < 10)
				    && (othruseronl.flags | OLF_INTELECON)
				    && ((!inchannel) ||
					(sameas
					 (curchannel,
					  othruseronl.telechan)))) {
					strcpy (matches[num], status.user);
					num++;
				}
			}
		}
	}

	if (num == 1) {
		if (inchannel) {
			if ((!strcmp (curchannel, othruseronl.telechan)) &&
			    (othruseronl.flags & OLF_INTELECON)) {
				cachepush (strcpy (userid, matches[0]));
				return 1;
			} else
				return 0;
		} else {
			strcpy (userid, matches[0]);
			cachepush (userid);
			return 1;
		}
	} else if (!num && !retry)
		return 0;
	else {
		int     i, ans = 0;

		msg_set (msg_sys);
		for (;;) {
			cnc_end ();
			if (num) {
				prompt (UXRF1, userid);
				for (i = 0; i < num; i++)
					prompt (UXRF2, i + 1, matches[i]);
				prompt (UXRF3, 1, num);
			} else
				prompt (UXRF3A);
			inp_get (0);
			if (!margc) {
				continue;
			} else if (margc && inp_isX (margv[0])) {
				msg_reset ();
				return 0;
			} else if (margc && sameas (margv[0], "?")) {
				continue;
			} else if (num && margc && (ans = atoi (margv[0]))) {
				if (ans > num) {
					prompt (UXRF4);
					continue;
				} else {
					cachepush (strcpy
						   (userid, matches[ans - 1]));
					msg_reset ();
					return 1;
				}
			} else if (margc) {
				msg_reset ();
				strcpy (userid, margv[0]);
				retry = 1;
				goto tryagain;
			}
		}
	}
	return 0;
}


void
showinfo ()
{
	struct chanhdr *c;
	struct chanusr *u;
	int     count = 0, i;

	if (sameas (curchannel, thisuseracc.userid))
		prompt (SICHYPR);
	else if (sameas (curchannel, MAINCHAN))
		prompt (SICHMAIN);
	else if (curchannel[0] == '/')
		prompt (SICHCLUB, curchannel);
	else if (usr_exists (curchannel)) {
		useracc_t uacc;

		if (usr_loadaccount (curchannel, &uacc)) {
			prompt (SICHPRO,
				msg_getunit (OFMALE, (uacc.sex == USX_MALE)),
				curchannel);
		}
	} else
		prompt (SICHTMP, curchannel);


	/* print topic, prepare for scanning users */

	if ((c = begscan (curchannel, TSM_PRESENT)) == NULL)
		return;

	if (c->topic[0])
		prompt (SITOPIC, c->topic);

	/* scan users and print ones present in the channel */

	for (count = 0;;) {
		if ((u = getscan ()) == NULL)
			break;
		if ((u->flags & CUF_PRESENT) &&
		    usr_insys (u->userid, 1) &&
		    strcmp (thisuseracc.userid, u->userid))
			count++;
	}

	if (!count)
		prompt (SIU0);
	else {
		endscan ();
		begscan (curchannel, TSM_PRESENT);

		for (i = 0; i < count;) {
			if ((u = getscan ()) == NULL)
				break;
			if ((u->flags & CUF_PRESENT) &&
			    usr_insys (u->userid, 1) &&
			    strcmp (thisuseracc.userid, u->userid)) {
				if (!i) {
					prompt (count == 1 ? SIU1 : SIUN1,
						msg_getunit (SEXM1,
							     u->sex ==
							     USX_MALE),
						u->userid);
				} else if ((i + 1) == count)
					prompt (SIUN3,
						msg_getunit (SEXM2,
							     u->sex ==
							     USX_MALE),
						u->userid);
				else
					prompt (SIUN2,
						msg_getunit (SEXM2,
							     u->sex ==
							     USX_MALE),
						u->userid);
				i++;
			}
		}
	}

	endscan ();
	prompt (ASKHLP);
}


const char *colours[] = {
	"", "0;34", "0;32", "0;36", "0;31", "0;35", "0;33", "0;37",
	"1;30", "1;34", "1;32", "1;36", "1;31", "1;35", "1;33", "1;37"
};


char   *
getcolour ()
{
	return (char *) colours[tlcu.colour];
}


char   *
mkchfn (char *chan)
{
	static char tmpchan[64];

	strcpy (tmpchan, chan);
	if (tmpchan[0] == '/')
		tmpchan[0] = '_';
	return tmpchan;
}


char   *
gettopic (char *chan)
{
	if (!strcmp (chan, MAINCHAN))
		return msg_get (MAINTOPIC);
	else if (chan[0] == '/') {
		if (!loadclubhdr (chan)) {
			error_fatal ("Can't load club header for %s", chan);
		}
		return clubhdr.descr;
	} else if (usr_exists (chan)) {
		static struct tlcuser usr;

		if (!loadtlcuser (chan, &usr)) {
			error_fatal ("Can't load user record for %s", chan);
		}
		return usr.topic;
	}
	return msg_get (MAINTOPIC);
}


void
countdown ()
{
	if (thisuseronl.telecountdown > 0)
		thisuseronl.telecountdown--;
	if (!thisuseronl.telecountdown)
		thisuseronl.telecountdown = -2;
}


int
checktick ()
{
	thisuseraux.numentries++;
	if ((time (0) - thisuseraux.entrytick) >= TELETICK) {
		thisuseraux.numentries = 0;
		thisuseraux.entrytick = time (0);
	}
	if (thisuseraux.numentries > maxcht) {
		prompt (CH2OFT);
		return 0;
	}
	return 1;
}


/* End of File */
