/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubfx.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1995, Version 0.5                                    **
 **  PURPOSE:  Miscellaneous Club functions                                 **
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
 * Revision 1.5  2003/12/25 13:33:29  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:21:38  alexios
 * Just a slight addition (made "-" and "*" work same as "ALL"
 * in getclubname().
 *
 * Revision 0.5  1998/12/27 15:33:03  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:04:17  alexios
 * Fixed bug that caused a SIGSEGV when entering clubs from the
 * login() function (mail notification) of the Email module.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
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
#include "mbk_emailclubs.h"
#include "clubs.h"
#include "email.h"


char    inclublock[256];

int     clntrkey;
int     clsopkey;
int     tlckey;
int     bltkey;
int     clbwchg;
int     clbuchg;
int     clbdchg;
int     clblif;
int     cdnlaud;
int     cuplaud;
char   *defclub;
int     modaxkey;
int     modchkey;
int     modhdkey;

int     threadmessage = 0;
char    threadclub[16] = { 0 };


void
enterdefaultclub ()
{
	if (thisuseracc.lastclub[0] == 0)
		strcpy (thisuseracc.lastclub, defclub);
	else if (!findclub (thisuseracc.lastclub))
		strcpy (thisuseracc.lastclub, defclub);
	loadclubhdr (thisuseracc.lastclub);

	if (clubhdr.credspermin == -1)
		thisuseronl.credspermin = defaultrate;
	else
		thisuseronl.credspermin = clubhdr.credspermin;

	lock_rm (inclublock);
	sprintf (inclublock, INCLUBLOCK, thisuseronl.channel, clubhdr.club);
	lock_place (inclublock, "reading");

	setclub (clubhdr.club);
}


void
enterclub (char *club)
{
	if (!findclub (club))
		strcpy (club, defclub);
	loadclubhdr (club);

	if (clubhdr.credspermin == -1)
		thisuseronl.credspermin = defaultrate;
	else
		thisuseronl.credspermin = clubhdr.credspermin;

	lock_rm (inclublock);
	sprintf (inclublock, INCLUBLOCK, thisuseronl.channel, clubhdr.club);
	lock_place (inclublock, "reading");

	setclub (clubhdr.club);
}


void
showbanner ()
{
	char    fname[256];
	struct stat st;

	if (cnc_more ())
		return;
	sprintf (fname, "%s/b%s", mkfname (CLUBHDRDIR), clubhdr.club);
	if (stat (fname, &st))
		return;
	prompt (BANNERH);
	out_printfile (fname);
	prompt (BANNERF);
}


int
checkinclub (char *club)
{
	int     i;
	char    lock[256];
	channel_status_t status;
	struct stat st;

	for (i = 0; i < chan_count; i++) {
		if (channel_getstatus (channels[i].ttyname, &status)) {
			if (status.result == LSR_USER) {
				strcpy (lock,
					mkfname (LOCKDIR "/" INCLUBLOCK,
						 channels[i].ttyname, club));
				if (!stat (lock, &st))
					return 0;
			}
		}
	}
	return 1;
}


int
getclub (char *club, int pr, int err, int all)
{
	char   *i;
	char    c;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				listclubs ();
				cnc_end ();
				continue;
			}
			i = cnc_word ();
		} else {
			prompt (pr);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc) {
				cnc_end ();
				continue;
			} else if (inp_isX (margv[0]))
				return 0;
			if (sameas (margv[0], "?")) {
				listclubs ();
				cnc_end ();
				continue;
			}
		}

		if (*i == '/')
			i++;

		if ((sameas (i, "-") || sameas (i, "*") || sameas (i, "ALL"))
		    && all) {
			strcpy (club, "ALL");
			return 1;
		}
		if (!findclub (i)) {
			prompt (err);
			cnc_end ();
			continue;
		} else
			break;
		return 1;
	}

	strcpy (club, i);
	return 1;
}


int
thread (message_t *msg, char defopt)
{
	char    opt;
	int     i, j, msgno;

      retry:
	for (;;) {
		inp_setflags (INF_HELP);
		i = get_menu (&opt, 0, 0, THRMNU, RCMNUR, "FBPR", RCMNUD,
			      defopt);
		inp_clearflags (INF_HELP);
		if (!i)
			return 0;
		if (i == -1) {
			prompt (THRMNUH);
			cnc_end ();
			continue;
		} else
			break;
	}

	switch (opt) {
	case 'R':
		if (!threadmessage) {
			prompt (THRNRET);
			cnc_end ();
			goto retry;
		}
		prompt (THRRET, threadclub, threadmessage);	/* jump back to club */
		if (strcmp (clubhdr.club, threadclub))
			enterclub (threadclub);
		j = threadmessage;
		threadmessage = 0;
		return -j;
	case 'F':
		j = findmsgsubj (&msgno, msg->subject, msg->msgno, BSD_GT);
		if (j != BSE_FOUND) {
			error_fatal ("Unable to find current message!");
		}
		msgno = -1;
		j = npmsgsubj (&msgno, msg->subject, msg->msgno + 1, BSD_GT);
		if (j != BSE_FOUND || msgno < 0) {
			prompt (THREND);
			return 0;
		} else {
			if (!threadmessage) {
				threadmessage = msg->msgno;
				strcpy (threadclub, msg->club);
			}
			return -msgno;
		}
	case 'B':
		j = findmsgsubj (&msgno, msg->subject, msg->msgno, BSD_LT);
		if (j != BSE_FOUND) {
			error_fatal ("Unable to find current message!");
		}
		msgno = -1;
		j = npmsgsubj (&msgno, msg->subject, msg->msgno - 1, BSD_LT);
		if (j != BSE_FOUND || msgno < 0) {
			prompt (THRBEG);
			return 0;
		} else {
			if (!threadmessage) {
				threadmessage = msg->msgno;
				strcpy (threadclub, msg->club);
			}
			return -msgno;
		}
	case 'P':
		{
			char    replyto[256], *cp;
			int     msgno = 0, ok = 0, i, j, msgn = 0;
			char    fname[256];
			struct stat st;

			if ((msg->flags & MSF_REPLY) == 0) {
				prompt (THRPR);
				return 0;
			}

			if ((cp = strstr (msg->history, HST_REPLY)) != NULL) {
				ok = (sscanf (cp, "%*s %s", replyto) == 1);
			} else {
				prompt (THRPR);
				return 0;
			}

			if (ok) {
				if ((cp = strchr (replyto, '/')) != NULL) {
					*cp = 0;
					cp++;
					ok = (sscanf (cp, "%d", &msgno) == 1);
					msgn = msgno;
				}
			}

			if (ok) {
				if (msg->club[0])
					strcpy (fname,
						mkfname (MSGSDIR "/%s/"
							 MESSAGEFILE,
							 msg->club, msgno));
				else
					strcpy (fname,
						mkfname (MSGSDIR "/"
							 EMAILDIRNAME "/"
							 MESSAGEFILE, msgno));
				ok = (stat (fname, &st) == 0);
			}

			if (!ok) {
				prompt (THRPR);
				return 0;
			} else {
				if (strcmp (clubhdr.club, replyto)) {
					prompt (THRCLC, replyto);
					enterclub (replyto);
				}

				j = findmsgnum (&i, msgno, BSD_GT);
				if ((j != BSE_FOUND) || (msgno != i)) {
					enterclub (msg->club);
					ok = 0;
				}
			}

			if (!ok) {
				prompt (THRPNF, replyto, msgn);
				return 0;
			}

			if (!threadmessage) {
				threadmessage = msg->msgno;
				strcpy (threadclub, msg->club);
			}

			return -msgno;
		}
	}
	return 0;
}



/* End of File */
