/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubscan.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1995                                               **
 **            B, August 1996                                               **
 **  PURPOSE:  Scan Club messages                                           **
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
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/08/13 17:00:25  alexios
 * Fixed scan-for-keyword bug that caused fatal errors due to
 * uninitialised quickscan lists. This is really a kludge, I
 * couldn't be bothered looking for the root of the problem, so
 * I just fixed things so that quickscan lists aren't updated
 * while scanning for keywords -- this is acceptable behaviour.
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support. Slight message navigation fixes.
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
    "$Id$";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mbk_emailclubs.h>
#include <megistos/clubs.h>
#include <megistos/email.h>
#include <megistos/typhoon.h>


static int indworking = 0;
static int ind = 0;


static void
startind ()
{
	if (!indworking) {
		prompt (RKIND0);
		indworking++;
		ind = 0;
	}
}


static void
progressind (int i)
{
	if (indworking > 0) {
		prompt (RKIND1 + ind, i);
		ind = (ind + 1) % 8;
	}
}


static
    void
endind ()
{
	indworking--;
	if (!indworking)
		prompt (RKINDE);
}


static int
keycmp (char *s)
{
	stgxlate (s, KEYSCAN);
	for (lastkey = 0; lastkey < numkeys; lastkey++)
		if (strstr (s, phonetic[lastkey])) {
			return 1;
		}
	return 0;
}


void
scanupdatemsg (struct message *msg, int read)
{
	struct message m;
	struct lastread *l;

	getmsgheader (msg->msgno, &m);
	if (read)
		m.timesread++;
	if (m.flags & MSF_RECEIPT)
		sendreceipt (&m);
	if (m.flags & MSF_FILEATT)
		downloadatt (&m);
	writemsgheader (&m);

	if (keyscan)
		return;		/* Don't update quickscans if searching */
	if ((l = findqsc (clubhdr.club)) == NULL) {
		error_fatal ("Unable to find quickscan entry for club %s",
			     clubhdr.club);
	}

	if (inemail == OPT_ALL)
		l->lastmsg = max (m.msgno, l->lastmsg);
	else if (inemail == OPT_TOYOU)
		l->emllast = max (m.msgno, l->emllast);
	/*savecounter=(savecounter+1)%5; */
	/*if(!savecounter) */
	saveqsc ();
}



/* Search for a message */


static int
locatemsg (int *msgno, int *sequencebroken, int targetmsg, int dir, int mode)
{
	int     j = BSE_CAN;

	if (*sequencebroken) {
		/* If the sequence is broken, seek the message. */

		if (mode == OPT_FROMYOU) {
			j = findmsgfrom (msgno, thisuseracc.userid, targetmsg,
					 dir);
		} else if (mode == OPT_TOYOU) {
			j = findmsgto (msgno, thisuseracc.userid, targetmsg,
				       dir);
		} else {
			j = findmsgnum (msgno, targetmsg, dir);
		}


		/* Check if we've exceeded search bounds and search again. */

		if (j != BSE_FOUND) {
			int     tdir = (j == BSE_END) ? 2 : 4;

			if (mode == OPT_FROMYOU)
				j = findmsgfrom (msgno, thisuseracc.userid,
						 targetmsg, tdir);
			else if (mode == OPT_TOYOU)
				j = findmsgto (msgno, thisuseracc.userid,
					       targetmsg, tdir);
			else
				j = findmsgnum (msgno, targetmsg, tdir);


			/* Re-establish the sequence along the right direction */

			if (j == BSE_FOUND) {
				if (mode == OPT_FROMYOU)
					findmsgfrom (msgno, thisuseracc.userid,
						     *msgno, dir);
				else if (mode == OPT_TOYOU)
					findmsgto (msgno, thisuseracc.userid,
						   *msgno, dir);
				else
					findmsgnum (msgno, *msgno, dir);
			}
		}

		*sequencebroken = 0;

	} else {
		/* ...otherwise, get the next or previous message in the sequence. */

		if (mode == OPT_FROMYOU)
			j = npmsgfrom (msgno, thisuseracc.userid, targetmsg,
				       dir);
		else if (mode == OPT_TOYOU)
			j = npmsgto (msgno, thisuseracc.userid, targetmsg,
				     dir);
		else
			j = npmsgnum (msgno, targetmsg, dir);
	}

	return j;
}


/* Scan for files */

static int
scan4files (int *msgno, int *sequencebroken, int targetnum, int dir, int mode)
{
	int     first = 1;
	struct ecidx idx;

	inp_nonblock ();
	*msgno = -1;
	for (;;) {
		int     j =
		    locatemsg (msgno, sequencebroken, targetnum, dir, mode);
		int     found = 0;
		int     c;

		if (j == BSE_NFOUND || (*msgno) < 0) {
			if (!first)
				if (!keyscan)
					endind ();
			*msgno = -1;
			inp_block ();
			return j;
		} else if (first) {
			startind ();
			first = 0;
		}

		dbgetindex (&idx);
		progressind (idx.num);

		if (filescan == 2) {
			found = ((idx.flags & MSF_FILEATT) &&
				 ((idx.flags & MSF_APPROVD) == 0));
		} else
			found = idx.flags & MSF_FILEATT;

		if ((read (fileno (stdin), &c, 1) &&
		     ((c == 13) || (c == 10) || (c == 27) || (c == 15) ||
		      (c == 3)))
		    || (fmt_lastresult == PAUSE_QUIT)) {
			if (!first)
				if (!keyscan)
					endind ();
			prompt (FSCCAN);
			inp_block ();
			*msgno = -1;
			return BSE_CAN;
		}

		if (found) {
			if (!first)
				if (!keyscan)
					endind ();
			inp_block ();
			return j;
		}

		if (dir == BSD_GT)
			targetnum = *msgno + 1;
		else
			targetnum = *msgno - 1;
	}
	inp_block ();
	return (dir == BSD_GT) ? BSE_END : BSE_BEGIN;
}


/* Look for messages (scan, key, etc) */


int
scan4msg (int *msgno, int *sequencebroken, int targetnum, int dir, int mode)
{
	char    c;

	enterclub (clubhdr.club);
	if (!keyscan) {
		if (!filescan)
			return locatemsg (msgno, sequencebroken, targetnum,
					  dir, mode);
		else
			return scan4files (msgno, sequencebroken, targetnum,
					   dir, mode);
	} else {
		struct message msg;
		int     first = 1;

		inp_nonblock ();

		for (;;) {
			int     j, found = 0;

			*msgno = -1;
			if (!filescan)
				j = locatemsg (msgno, sequencebroken,
					       targetnum, dir, mode);
			else
				j = scan4files (msgno, sequencebroken,
						targetnum, dir, mode);

			if (j == BSE_NFOUND || (*msgno) < 0) {
				if (!first)
					endind ();
				*msgno = -1;
				inp_block ();
				return j;
			} else if (first) {
				startind ();
				first = 0;
			}

			progressind (*msgno);

			getmsgheader (*msgno, &msg);

			if (keycmp (msg.from))
				found = 1;
			else if (keycmp (msg.to))
				found = 1;
			else if (keycmp (msg.subject))
				found = 1;
			else if (keycmp (msg.history))
				found = 1;
			else if (keycmp (msg.fatt))
				found = 1;
			else if (keycmp (msg.origbbs))
				found = 1;
			else if (keycmp (msg.origclub))
				found = 1;
			else if (keycmp (msg.msgid))
				found = 1;
			else {
				FILE   *fp;
				char    fname[256], line[1024];

				sprintf (fname, "%s/%s/" MESSAGEFILE,
					 mkfname (MSGSDIR), msg.club,
					 msg.msgno);
				if ((fp = fopen (fname, "r")) != NULL) {
					while (fgets (line, sizeof (line), fp)) {
						if (keycmp (line)) {
							found = 1;
							break;
						}
						if ((read
						     (fileno (stdin), &c, 1) &&
						     ((c == 13) || (c == 10) ||
						      (c == 27) || (c == 15) ||
						      (c == 3)))
						    || (fmt_lastresult ==
							PAUSE_QUIT)) {
							if (!first)
								endind ();
							prompt (RKCAN);
							inp_block ();
							*msgno = -1;
							return BSE_CAN;
						}
					}
					fclose (fp);
				}
			}

			if (found) {
				if (!first)
					endind ();
				prompt (RKFOUND, keywords[lastkey]);
				inp_block ();
				return j;
			}

			if (dir == BSD_GT)
				targetnum = *msgno + 1;
			else
				targetnum = *msgno - 1;

			if ((read (fileno (stdin), &c, 1) &&
			     ((c == 13) || (c == 10) || (c == 27) || (c == 15)
			      || (c == 3)))
			    || (fmt_lastresult == PAUSE_QUIT)) {
				if (!first)
					endind ();
				prompt (RKCAN);
				inp_block ();
				*msgno = -1;
				return BSE_CAN;
			}
		}
		if (!first)
			endind ();
		*msgno = -1;
	}
	inp_block ();
	return BSE_NFOUND;
}


char
clubreadmenu (struct message *msg, char defopt)
{
	char    opt, options[32], tmp[2];
	int     menu, msgno, res;

	menu = quickscan ? RQSRMNU1 : RSRMNU1;
	strcpy (options, "NPERT#");
	if (quickscan)
		strcat (options, "Q");

	if (getclubax (&thisuseracc, msg->club) >= CAX_COOP) {
		menu = quickscan ? RQSRMNU3 : RSRMNU3;
		strcat (options, "S");
	} else if (sameas (thisuseracc.userid, msg->from)) {
		menu = quickscan ? RQSRMNU2 : RSRMNU2;
		strcat (options, "CM");
	}

      again:
	for (;;) {
		inp_setflags (INF_HELP);
		res =
		    get_menu (&opt, 1, 0, menu, RDMNUR, options, RSDEF,
			      defopt);
		inp_clearflags (INF_HELP);
		if (!res)
			return 'X';
		else if (res < 0) {
			prompt (menu + 1);
			cnc_end ();
			continue;
		}
		break;
	}

	msgno = msg->msgno;
	getmsgheader (msgno, msg);
	switch (opt) {
	case 'N':
	case 'P':
	case '#':
	case 'X':
		return opt;

	case 'R':
		reply (msg, 0);
		enterdefaultclub ();
		return 1;

	case 'E':
		reply (msg, 1);
		enterdefaultclub ();
		return 1;

	case 'T':
		return thread (msg, defopt == 'N' ? 'F' : 'B');

	case 'C':
		erasemsg (0, msg);
		return 1;

	case 'M':
		modifyclubmsg (msg);
		return 'N';

	case 'Q':
		tmp[0] = quickscanmenu (msg);
		tmp[1] = 0;
		if (inp_isX (tmp))
			goto again;
		else
			return tmp[0];

	case 'S':
		{
			char    club[16];
			int     i;

			strcpy (club, msg->club);
			i = clubopmenu (msg);
			enterclub (club);
			return i;
		}

	default:
		return 'N';
	}
}


char
clubheadermenu (struct message *msg, char defopt)
{
	int     res;
	char    opt;

	for (;;) {
		inp_setflags (INF_HELP);
		if ((msg->flags & (MSF_FILEATT | MSF_APPROVD)) ==
		    (MSF_FILEATT | MSF_APPROVD)) {
			res =
			    get_menu (&opt, 1, 0, RSSCNMD, RSSCNR, "NP#RXTDQ",
				      RSDEF, defopt);
		} else {
			res =
			    get_menu (&opt, 1, 0, RSSCNM, RSSCNR, "NP#RTXQ",
				      RSDEF, defopt);
		}

		inp_clearflags (INF_HELP);

		if (!res)
			return 'X';
		else if (res == -1) {
			if ((msg->flags & (MSF_FILEATT | MSF_APPROVD)) ==
			    (MSF_FILEATT | MSF_APPROVD)) {
				prompt (RSSCNMH);
			} else
				prompt (RSSCNMHD);
			cnc_end ();
			continue;
		} else if (opt == 'Q' && !quickscan) {
			prompt (QSNOJMP);
			cnc_end ();
			continue;
		}
		break;
	}

	return opt;
}


int
startscanning (int startmsg, int bdir)
{
	int     i;		/* Message number being read (hopefully) */
	int     dir = bdir;	/* Starting movement direction */
	int     sequencebroken = 1;	/* Re-establish the message sequence */
	int     oldmsgno = startmsg;	/* Previously read message */
	int     dontshow = 0;	/* Don't display msg header this time round */
	int     nummsgs = 0;	/* Number of messages shown so far */
	int     optdecided;	/* Don't reprocess navigation commands */
	int     bound = 0;	/* Reached beginning/end of list */
	int     targetmsg = startmsg;	/* Target message when jumping around */

	char    lock[256];	/* Message lock */
	char    tmp[256];	/* Dogsbody */

	char    opt;		/* Menu selection */
	char    defopt;		/* Default menu option */

	struct lastread *lastread;	/* Quickscan configuration */


	lastread = getqsc ();

	if (startmsg < 0)
		startmsg = oldmsgno = 1;

	cnc_end ();
	for (i = startmsg;;) {
		int     msgno;
		int     j;
		struct message msg;


		/* Find the message */

		oldmsgno = msgno;
		msgno = -1;
		if (!threadmessage)
			setclub (clubhdr.club);
		else
			setclub (threadclub);
		j = scan4msg (&msgno, &sequencebroken, i, dir, inemail);


		/* Remove the indicator, just in case */

		endind ();


		/* If no more messages, prompt the user and/or leave */

		if (j != BSE_FOUND) {
			if (!quickscan) {
				if (dir == BSD_LT)
					prompt (RSBEG);
				else if (dir == BSD_GT) {
					prompt (RSEND);
				}
			} else {
				int     ret = 1;

				if (isfirstqsc () && dir == BSD_LT) {
					prompt (RSBEG);
					ret = 0;
				} else if (islastqsc () && dir == BSD_GT) {
					prompt (RSEND);
					ret = 0;
				} else if (nummsgs)
					prompt (QSLEAVE);
				if (ret)
					return dir ==
					    BSD_LT ? BSE_BEGIN : BSE_END;
			}
			bound = dir;
			defopt = 'X';
			dontshow = 1;
			sequencebroken = 1;
			msgno = oldmsgno;
		} else {
			defopt = 'R';
			bound = 0;
		}


		/* Produce a MISS message */

		if (msgno != targetmsg && targetmsg >= 0 &&
		    targetmsg != LASTMSG) {
			if (quickscan) {
				if (msgno <= targetmsg) {
					saveqsc ();
					return dir ==
					    BSD_LT ? BSE_BEGIN : BSE_END;
				}
			} else {
				prompt (RSMISS, targetmsg);
			}
			bound = 0;
		}
		targetmsg = -1;


		/* Lock the current message */

		if (msgno != oldmsgno) {
			dontshow = 0;

			if (lock[0])
				lock_rm (lock);
			sprintf (tmp, "%d", msgno);
			sprintf (lock, MSGREADLOCK, thisuseronl.channel,
				 EMAILCLUBNAME, tmp);
			lock_place (lock, "reading");
		}


		/* Read and display the message header, if we need to. */

		if (!dontshow) {

			/* Read the message header. Be paranoid about it. */

			if (getmsgheader (msgno, &msg) != BSE_FOUND) {
				if (dir == BSD_GT)
					i = msgno + 1;
				else
					i = msgno - 1;
				continue;
			}

			/* Show the message's header. */

			showheader (clubhdr.club, &msg);
		}
		nummsgs++;


		/* Notify the user that we're threading */

		if (threadmessage)
			prompt (THREAD);


		/* Header menu */

	      bound_hit:
		opt = clubheadermenu (&msg, defopt);

		for (optdecided = 0; !optdecided;) {
			switch (opt) {
			case 'D':
				scanupdatemsg (&msg, 0);

			case 'N':
				if (bound == BSD_GT) {
					if (!quickscan) {
						prompt (RSEND);
						goto bound_hit;
					} else {
						if (islastqsc ()) {
							prompt (RSEND);
							goto bound_hit;
						}
						if (nummsgs)
							prompt (QSLEAVE);
						return BSE_END;
					}
				}
				optdecided = 1;
				i = msgno + 1;
				dir = BSD_GT;
				break;

			case 'P':
				if (bound == BSD_LT) {
					if (!quickscan) {
						prompt (RSBEG);
						goto bound_hit;
					} else {
						if (isfirstqsc ()) {
							prompt (RSBEG);
							goto bound_hit;
						}
						if (nummsgs)
							prompt (QSLEAVE);
						return BSE_BEGIN;
					}
				}
				optdecided = 1;
				i = msgno - 1;
				dir = BSD_LT;
				break;

			case '#':
				{
					int     newmsgno = msgno;

					if (getrdmsgno
					    (&newmsgno, RDGONUM, RDGOHLP, 0,
					     0)) {
						i = msgno = newmsgno;
						dontshow = 0;
					} else {
						i = msgno;
						dontshow = 1;
					}
					targetmsg = msgno;
					sequencebroken = 1;
					optdecided = 1;
					dir = BSD_GT;
					break;
				}

			case 'T':
				{
					int     newmsgno =
					    -thread (&msg,
						     dir ==
						     BSD_GT ? 'F' : 'B');
					if (newmsgno > 0) {
						i = msgno = newmsgno;
						dontshow = 0;
					} else {
						i = msgno;
						dontshow = 1;
					}
					sequencebroken = 1;
					targetmsg = msgno;
					optdecided = 1;
					dir = BSD_GT;
					break;
				}

			case 'R':
				readmsg (&msg);
				scanupdatemsg (&msg, 1);
				do {
					opt =
					    clubreadmenu (&msg,
							  dir ==
							  BSD_GT ? 'N' : 'P');
					optdecided = 1;

					if (opt < 0) {
						targetmsg = i = -opt;
						dir = BSD_GT;
						opt = 1;
					} else if (!opt) {
						oldmsgno = msgno;
						opt = 0;
					} else if (opt == 1) {
						sequencebroken = 1;
						opt = 'N';
						optdecided = 0;
						break;
					} else {
						optdecided = 0;
						break;
					}
				} while (opt <= 0);
				break;

			case 'Q':
				optdecided = 0;
				opt = quickscanmenu (&msg);
				tmp[0] = opt;
				tmp[1] = '\0';
				if (toupper (opt) == 'S') {
					if (!qgoclub ()) {
						optdecided = 0;
						opt = 'Q';
					} else
						return opt;
				} else if (!inp_isX (tmp)) {
					optdecided = 0;
				} else if (toupper (opt) == 'C') {

				} else {
					i = msgno;
					dontshow = 0;
					optdecided = 1;
					goto bound_hit;
				}
				break;

			case 'n':
				saveqsc ();
				return 'n';

			case 'p':
				saveqsc ();
				return 'p';

			case 'b':
				if (inemail == OPT_ALL)
					lastread->lastmsg = msg.msgno - 1;
				else if (inemail == OPT_TOYOU)
					lastread->emllast = msg.msgno - 1;
				saveqsc ();
				prompt (QSMBM, msg.msgno, clubhdr.club);
				return 'b';

			case 'c':
				if (inemail == OPT_ALL)
					lastread->lastmsg = clubhdr.msgno;
				else if (inemail == OPT_TOYOU)
					lastread->emllast = clubhdr.msgno;
				saveqsc ();
				prompt (QSMCU, clubhdr.club);
				return 'c';

			case 'r':
				lastread->flags &= ~LRF_QUICKSCAN;
				saveqsc ();
				prompt (QSMRM, clubhdr.club);
				return 'r';

			case 's':
				if (!qgoclub ()) {
					optdecided = 0;
					opt = 'Q';
					break;
				} else
					return 's';

			case 0:
				break;

			case 1:
				sequencebroken = 1;
				dontshow = 0;
				optdecided = 1;
				break;

			case 'X':
			default:
				cnc_end ();
				return 'X';
			}
		}
	}

	return 'X';
}


void
scanmessages ()
{
	int     startmsg, msgno = -1, j, sequencebroken = 1;
	char    club[16];

	strcpy (club, clubhdr.club);

	/* Configure scan */

	keyscan = 0;


	/* Not quickscanning */

	indworking = 0;
	startqsc ();
	if (!quickscan) {
		enterclub (club);

		/* RS command, ask for starting message number */

		if (!getrdmsgno
		    (&startmsg, RSASK, RSASKH, RSASKR,
		     getlastread (clubhdr.club))) {
			doneqsc ();
			return;
		}

		/* Locate the first applicable message */

		enterclub (clubhdr.club);

		msgno = -1;
		j = scan4msg (&msgno, &sequencebroken, startmsg, BSD_GT,
			      inemail);
		if (j == BSE_CAN)
			return;
		if (msgno < 0 || j != BSE_FOUND) {
			sequencebroken = 1;
			j = scan4msg (&msgno, &sequencebroken, startmsg,
				      BSD_LT, inemail);
			if (j == BSE_CAN)
				return;
			if (msgno < 0 || j != BSE_FOUND) {
				prompt (RSBNMSG);
				cnc_end ();
				return;
			}
		}
	}

	/* Quickscanning or Scan the messages */

	if (quickscan)
		doquickscan ();
	else
		startscanning (msgno, BSD_GT);
	keyscan = 0;
	saveqsc ();


	/* Remove all locks */

	rmlocks ();
}




/* End of File */
