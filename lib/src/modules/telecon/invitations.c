/*****************************************************************************\
 **                                                                         **
 **  FILE:     invitations.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 96, Version 0.5                                      **
 **  PURPOSE:  Teleconferences, inviting and uninviting users.              **
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
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/12/27 16:10:27  alexios
 * Added autoconf support. One slight bug fix.
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
#include <megistos/telecon.h>
#include <megistos/mbk_telecon.h>


void
invite (char *s)
{
	char    userid[2048] = { 0 };
	int     i;

	i = sscanf (s, "%*s %s", userid);

	if ((i < 1) || sameas (userid, "?")) {
		prompt (INVHELP);
		return;
	}

	if (sameas (userid, "ALL")) {
		setchanax (CHF_OPEN);
		prompt (INOKALL);
		if (!sameas (thisuseronl.telechan, thisuseracc.userid))
			prompt (INVWRN);
		return;
	}

	if (!usr_uidxref (userid, 1)) {
		prompt (IUNKUSR, userid);
		return;
	}

	if (sameas (thisuseracc.userid, userid)) {
		prompt (IWHYU);
		return;
	}

	usr_insys (userid, 0);

	setusrax (thisuseracc.userid, userid, 0, CUF_EXPLICIT | CUF_ACCESS, 0);

	{
		char    article[2048];

		strcpy (article,
			msg_getunit (IRECHE, thisuseracc.sex == USX_MALE));

		sprompt_other (othrshm, out_buffer, IRECIP,
			       article, thisuseracc.userid,
			       msg_getunit (IRECHIS,
					    thisuseracc.sex == USX_MALE));

		if (!usr_injoth (&othruseronl, out_buffer, 0)) {
			prompt (UNNOT, othruseronl.userid);
		}

		if (othruseronl.flags & OLF_INTELECON) {
			sprompt_other (othrshm, out_buffer, IJOIN,
				       thisuseracc.userid);
			usr_injoth (&othruseronl, out_buffer, 0);
		}
	}

	prompt (ISENDR, msg_getunit (ISNDM, othruseracc.sex == USX_MALE),
		userid);

	if (!sameas (thisuseronl.telechan, thisuseracc.userid))
		prompt (INVWRN);
}


static char fx_sex, fx_id[24];


static char *
fx_kickout (struct chanusr *u)
{
	char    tmp[8192];

	strcpy (out_buffer, msg_getl (TDELIM, othruseracc.language - 1));

	sprintf (tmp, msg_getl (UOTHER, othruseracc.language - 1),
		 msg_getunitl (SEXM1, fx_sex == USX_MALE,
			       othruseracc.language - 1), fx_id);
	strcat (out_buffer, tmp);
	return out_buffer;
}


void
uninvite (char *s)
{
	char    userid[2048] = { 0 };
	int     i;

	i = sscanf (s, "%*s %s", userid);

	if ((i < 1) || sameas (userid, "?")) {
		prompt (UNVHELP);
		return;
	}

	if (sameas (userid, "ALL")) {
		setchanax (CHF_PRIVATE);
		prompt (UNOKALL);
		return;
	}

	if (!usr_uidxref (userid, 1)) {
		prompt (UUNKUSR, userid);
		return;
	}

	if (sameas (thisuseracc.userid, userid)) {
		prompt (UWHYU);
		return;
	}

	usr_insys (userid, 0);

	{
		char    article[2048];

		strcpy (article,
			msg_getunit (URECHE, thisuseracc.sex == USX_MALE));

		sprompt_other (othrshm, out_buffer, URECIP,
			       article, thisuseracc.userid,
			       msg_getunit (URECHIS,
					    thisuseracc.sex == USX_MALE));

		if (!usr_injoth (&othruseronl, out_buffer, 0)) {
			prompt (UNNOT, othruseronl.userid);
		}

		setusrax (thisuseracc.userid, userid, 0, CUF_EXPLICIT,
			  CUF_PRESENT | CUF_ACCESS);

		if (othruseronl.flags & OLF_INTELECON) {
			char    tty[16];

			strcpy (tty, othruseronl.channel);
			strcpy (fx_id, userid);
			fx_sex = othruseracc.sex;
			if (!strcmp (othruseronl.telechan, thisuseracc.userid)) {
				broadcastchn (thisuseracc.userid, fx_kickout);
			}
			sendmain (userid);
		}
	}

	prompt (USENDR, msg_getunit (USNDM, othruseracc.sex == USX_MALE),
		userid);
}


void
invitero (char *s)
{
	char    userid[2048] = { 0 };
	int     i;

	i = sscanf (s, "%*s %s", userid);

	if ((i < 1) || sameas (userid, "?")) {
		prompt (ROHELP);
		return;
	}

	if (sameas (userid, "ALL")) {
		setchanax (CHF_READONLY);
		prompt (ROOKALL);
		if (!sameas (thisuseronl.telechan, thisuseracc.userid))
			prompt (INVWRN);
		return;
	}

	if (!usr_uidxref (userid, 1)) {
		prompt (RUNKUSR, userid);
		return;
	}

	if (sameas (thisuseracc.userid, userid)) {
		prompt (RWHYU);
		return;
	}

	usr_insys (userid, 0);

	setusrax (thisuseracc.userid, userid, 0,
		  CUF_EXPLICIT | CUF_ACCESS | CUF_READONLY, 0);

	{
		char    article[2048];

		strcpy (article,
			msg_getunit (RRECHE, thisuseracc.sex == USX_MALE));

		sprompt_other (othrshm, out_buffer, RRECIP,
			       article, thisuseracc.userid,
			       msg_getunit (RRECHIS,
					    thisuseracc.sex == USX_MALE));

		if (!usr_injoth (&othruseronl, out_buffer, 0)) {
			prompt (UNNOT, othruseronl.userid);
		}

		if (othruseronl.flags & OLF_INTELECON) {
			sprompt_other (othrshm, out_buffer, RJOIN,
				       thisuseracc.userid);
			usr_injoth (&othruseronl, out_buffer, 0);
		}
	}

	prompt (RSENDR, msg_getunit (RSNDM, othruseracc.sex == USX_MALE),
		userid);

	if (!sameas (thisuseronl.telechan, thisuseracc.userid))
		prompt (INVWRN);
}





/* End of File */
