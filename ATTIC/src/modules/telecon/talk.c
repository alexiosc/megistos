/*****************************************************************************\
 **                                                                         **
 **  FILE:     talk.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, talking to users                            **
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
 * $Id: talk.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: talk.c,v $
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
 * Revision 0.4  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/08/11 10:21:33  alexios
 * Fixed a couple of potentially serious problems.
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
    "$Id: talk.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



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


static char tmp[16384], tmp2[4096];


int
checkax ()
{
	if (thisuseraux.access & CUF_READONLY) {
		prompt (TLKSQU);
		return 0;
	}
	return 1;
}


static char *
fx_say (struct chanusr *u)
{
	tmp[0] = out_buffer[0] = 0;
	sprintf (out_buffer, msg_getl (TFROM, othruseracc.language - 1),
		 getcolour (), thisuseracc.userid, tmp2);
	strcpy (tmp, msg_getl (TDELIM, othruseracc.language - 1));
	strcat (tmp, out_buffer);
	return tmp;
}


void
say (char *s)
{
	if (!checkax ())
		return;

	strcpy (tmp2, s);
	if (broadcast (fx_say) > 0)
		prompt (TSENT);
	else
		prompt (SIU0);
}


void
whisper (char *s)
{
	char   *cp = s, userid[256];
	int     i;

	if (!checkax ())
		return;

	cp = &s[strlen (s)];
	while ((cp != s) && (*cp == 32))
		*(cp--) = 0;
	cp = s;

	if (sameas (inp_buffer, "/") || sameas (inp_buffer, "WHISPER TO")) {
		prompt (HLPWHIS);
		cnc_end ();
		return;
	}

	if (s[0] == '/') {
		cp = s + 1;
		if (sscanf (cp, "%s %n", userid, &i) != 1 ||
		    strlen (&cp[i]) == 0) {
			prompt (HLPWHIS);
			cnc_end ();
			return;
		} else
			cp += i;
	} else if (sameto ("WHISPER TO ", s)) {
		char    dummy1[16], dummy2[16];

		if (sscanf (s, "%s %s %s %n", dummy1, dummy2, userid, &i) != 3
		    || strlen (&cp[i]) == 0) {
			prompt (HLPWHIS);
			cnc_end ();
			return;
		} else
			cp = &s[i];
	} else
		return;

	if (!tlcuidxref (userid, 1)) {
		cnc_end ();
		prompt (UIDNINC);
		return;
	}
	if (usr_insys (userid, 1) && ((thisuseronl.flags & OLF_BUSY) == 0)) {
		sprompt_other (othrshm, out_buffer, TDELIM);
		usr_injoth (&othruseronl, out_buffer, 0);
		sprompt_other (othrshm, out_buffer, TFROMP,
			       getcolour (), thisuseracc.userid, cp);
		usr_injoth (&othruseronl, out_buffer, 0);
		prompt (TSENTP, othruseronl.userid);
	}
}


static char *fxuser, *fxmsg;


static char *
fx_sayto (struct chanusr *u)
{
	sprompt_other (othrshm, out_buffer, TDELIM);
	usr_injoth (&othruseronl, out_buffer, 0);
	if (sameas (u->userid, fxuser)) {
		sprompt_other (othrshm, out_buffer, TFROM2U,
			       getcolour (), thisuseracc.userid, fxmsg);
	} else {
		sprompt_other (othrshm, out_buffer, TFROMT,
			       getcolour (), thisuseracc.userid, fxuser,
			       fxmsg);
	}
	return out_buffer;
}


void
sayto (char *s)
{
	char   *cp = s, userid[256];
	int     i;

	if (!checkax ())
		return;

	cp = &s[strlen (s)];
	while ((cp != s) && (*cp == 32))
		*(cp--) = 0;
	cp = s;

	if (sameas (inp_buffer, "\\") || sameas (inp_buffer, ">") ||
	    sameas (inp_buffer, "SAY TO")) {
		prompt (HLPSAY);
		cnc_end ();
		return;
	}

	if (s[0] == '\\' || s[0] == '>') {
		cp = s + 1;
		if (sscanf (cp, "%s %n", userid, &i) != 1 ||
		    strlen (&cp[i]) == 0) {
			prompt (HLPSAY);
			cnc_end ();
			return;
		} else
			cp += i;
	} else if (sameto ("SAY TO ", s)) {
		if (sscanf (s, "%*s %*s %s %n", userid, &i) != 3
		    || strlen (&cp[i]) == 0) {
			prompt (HLPSAY);
			cnc_end ();
			return;
		} else
			cp = &s[i];
	} else
		return;

	if (!tlcuidxref (userid, 1)) {
		cnc_end ();
		prompt (UIDNINC);
		return;
	}
	if (usr_insys (userid, 1) && ((thisuseronl.flags & OLF_BUSY) == 0)) {
		int     i;

		if (sameas (userid, thisuseracc.userid)) {
			prompt (TWHYU);
			cnc_end ();
			return;
		}
		fxuser = userid;
		fxmsg = cp;
		i = broadcast (fx_sayto);
		if (i > 0)
			prompt (TSENTT, userid);
		else if (!i)
			prompt (SIU0);
	}
}


/* End of File */
