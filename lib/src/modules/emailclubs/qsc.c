/*****************************************************************************\
 **                                                                         **
 **  FILE:     qsc.c                                                        **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1995                                               **
 **            B, August 1996                                               **
 **  PURPOSE:  Quickscan functions                                          **
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
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/25 13:33:28  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/18 21:21:38  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.6  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/11 10:03:22  alexios
 * Club listings are now case insensitive. Quickscan configuration
 * bug fixes.
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:04:17  alexios
 * Moved a few bits of code arount to facilitate the new types
 * of handling email (bypassing the quickscan) and to get rid
 * of that annoying SIGSEGV bug while in the login() process.
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
#include "mbk_emailclubs.h"
#include "clubs.h"
#include "email.h"


#define ADD  1
#define DEL -1


struct lastread *uqsc = NULL;
static struct lastread *uqscp = NULL;
static int numclubs = 0, clubp = 0;


static int
qsccmp (const void *A, const void *B)
{
	register char *a = ((struct lastread *) A)->club;
	register char *b = ((struct lastread *) B)->club;
	register char ca;
	register char cb;

      again:
	ca = toupper (*a);
	cb = toupper (*b);
	if (ca != cb)
		return ca - cb;
	if (!*a)
		return 0;
	a++, b++;
	goto again;
}


static void
sortqsc ()
{
	qsort (uqsc, numclubs, sizeof (struct lastread), qsccmp);
}


struct lastread *
ustartqsc (char *uid)
{
	char    fname[256];
	struct stat st;
	FILE   *fp;

	if (uqsc) {
		free (uqsc);
		uqsc = NULL;
	}
	if (uqscp)
		uqscp = NULL;
	numclubs = clubp = 0;

	sprintf (fname, "%s/%s", mkfname (QSCDIR), uid);
	if (stat (fname, &st))
		return NULL;

	if ((fp = fopen (fname, "r")) == NULL) {
		error_fatalsys ("Unable to open quickscan configuration %s",
				fname);
	}

	while (!feof (fp)) {
		struct lastread x, *new;

		if (fread (&(x), sizeof (x), 1, fp) == 1) {
			if (getclubax (&thisuseracc, x.club) > CAX_ZERO) {
				new = alcmem (sizeof (x) * (numclubs + 1));
				if (uqsc)
					memcpy (new, uqsc,
						sizeof (x) * numclubs);
				x.entrymsg = -1;
				memcpy (&new[numclubs], &x, sizeof (x));
				numclubs++;
				free (uqsc);
				uqsc = new;
			}
		}
	}
	fclose (fp);

	sortqsc ();
	uqscp = uqsc;
	clubp = 0;
	return uqsc;
}


struct lastread *
startqsc ()
{
	return ustartqsc (thisuseracc.userid);
}


struct lastread *
getqsc ()
{
	return uqscp;
}


struct lastread *
nextqsc ()
{
	if (clubp + 1 >= numclubs)
		return NULL;
	clubp++;
	uqscp++;
	return uqscp;
}


struct lastread *
prevqsc ()
{
	if (!clubp)
		return NULL;
	clubp--;
	uqscp--;
	return uqscp;
}


struct lastread *
findqsc (char *club)
{
	return bsearch (club, uqsc, numclubs, sizeof (struct lastread),
			qsccmp);
}


struct lastread *
goqsc (char *club)
{
	return uqscp =
	    bsearch (club, uqsc, numclubs, sizeof (struct lastread), qsccmp);
}


struct lastread *
resetqsc ()
{
	uqscp = uqsc;
	clubp = 0;
	return uqscp;
}


int
isfirstqsc ()
{
	struct lastread *i;

	if (uqscp == uqsc)
		return 1;
	for (i = uqscp; i >= uqsc; i--)
		if (i->entrymsg >= 0)
			return 0;
	return 1;
}


int
islastqsc ()
{
	return 0;
}


void
doneqsc ()
{
	if (uqsc)
		free (uqsc);
	uqsc = uqscp = NULL;
	numclubs = clubp = 0;
}


void
usaveqsc (char *uid)
{
	char    fname[256];
	FILE   *fp;
	int     i;

	sortqsc ();

	sprintf (fname, "%s/%s", mkfname (QSCDIR), uid);
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Unable to create quickscan configuration %s",
				fname);
	}

	for (i = 0; i < numclubs; i++) {
		if (uqsc[i].flags & LRF_DELETED)
			continue;
		if (fwrite (&uqsc[i], sizeof (struct lastread), 1, fp) != 1) {
			error_fatalsys
			    ("Unable to write quickscan configuration %s",
			     fname);
		}
	}

	fclose (fp);
}


void
saveqsc ()
{
	usaveqsc (thisuseracc.userid);
}


void
addqsc (char *club, int lastmsg, int flags)
{
	struct lastread x, *p;

	if ((p = findqsc (club)) == NULL) {
		memset (&x, 0, sizeof (x));
		strcpy (x.club, club);
		if (lastmsg >= 0)
			x.lastmsg = x.emllast = lastmsg;
		if (flags & LRF_INITQWK)
			x.qwklast = lastmsg;
		x.flags = flags;

		p = alcmem (sizeof (x) * (numclubs + 1));
		if (uqsc)
			memcpy (p, uqsc, sizeof (x) * numclubs);

		memcpy (&p[numclubs], &x, sizeof (x));
		numclubs++;
		if (uqsc)
			free (uqsc);
		uqsc = p;
		resetqsc ();
	} else {
		if (lastmsg >= 0)
			p->lastmsg = p->emllast = lastmsg;
		if (flags & LRF_INITQWK)
			x.qwklast = lastmsg;
		p->flags &= ~flags;
		p->flags |= flags;
	}
	sortqsc ();
}


int
delqsc (char *club)
{
	struct lastread *p;

	p = findqsc (club);
	if (!p)
		return 0;

	if (!numclubs) {
		doneqsc ();
		return 0;
	}

	p->flags &= ~LRF_QUICKSCAN;
	return 1;
}


int
killqsc (char *club)
{
	struct lastread *p;

	p = findqsc (club);
	if (!p)
		return 0;

	if (!numclubs) {
		doneqsc ();
		return 0;
	}

	p->flags = LRF_DELETED;

	return 1;
}


void
all (int add)
{
	struct dirent **clubs;
	int     n, i;

	n = scandir (mkfname (CLUBHDRDIR), &clubs, hdrselect, ncsalphasort);
	for (i = 0; i < n; free (clubs[i]), i++) {
		char   *cp = &clubs[i]->d_name[1];
		struct lastread *p;

		if (!loadclubhdr (cp))
			continue;

		p = findqsc (clubhdr.club);

		if (add == DEL) {
			delqsc (clubhdr.club);
			/*addqsc(clubhdr.club,-1,p?p->flags&~LRF_QUICKSCAN:0); */
		} else if (p && (p->flags & LRF_QUICKSCAN)) {
			addqsc (clubhdr.club, clubhdr.msgno, p->flags);
		} else {
			addqsc (clubhdr.club, 0,
				p ? p->flags | LRF_QUICKSCAN : LRF_QUICKSCAN);
		}
	}
	free (clubs);
	enterdefaultclub ();
}


void
initialise ()
{
	struct dirent **clubs;
	int     n, i;

	n = scandir (mkfname (CLUBHDRDIR), &clubs, hdrselect, ncsalphasort);
	for (i = 0; i < n; free (clubs[i]), i++) {
		char   *cp = &clubs[i]->d_name[1];

		if (!loadclubhdr (cp))
			continue;
		addqsc (clubhdr.club, clubhdr.msgno,
			LRF_QUICKSCAN | LRF_INQWK | LRF_INITQWK);
	}
	free (clubs);
	enterdefaultclub ();
}


int
getlastread (char *club)
{
	struct lastread *p = findqsc (club);
	int     ret;

	if (!p)
		addqsc (club, 0, 0);
	p = findqsc (club);
	ret = (inemail == OPT_ALL) ? p->lastmsg : p->emllast;
	saveqsc ();
	return ret;
}


void
setlastread (char *club, int msg)
{
	struct lastread *p = findqsc (club);

	if (!p)
		addqsc (club, msg, 0);
	else
		p->lastmsg = p->emllast = msg;
	saveqsc ();
}


static void
listqsc ()
{
	struct lastread *p;
	int     linemax, i = 0;
	int     first = 1;

	linemax = thisuseracc.scnwidth / 18;

	p = resetqsc ();
	while (p) {
		if ((p->flags & LRF_QUICKSCAN) &&
		    (getclubax (&thisuseracc, p->club) > CAX_ZERO)) {
			if (first) {
				prompt (RQCLH);
			}
			first = 0;
			print ("%-16s  ", p->club);
			i = (i + 1) % linemax;
			if (i == 0)
				print ("\n");
		}
		if (fmt_lastresult == PAUSE_QUIT)
			break;
		p = nextqsc ();
	}
	if (first) {
		prompt (RQLCE);
		resetqsc ();
	} else if (fmt_lastresult != PAUSE_QUIT)
		prompt (RQCLF);
	resetqsc ();
}


static void
addclub ()
{
	char    club[16];
	struct lastread *p;

	if (!getclub (club, RQCADD, RQCDR, 1))
		return;
	if (sameas (club, "ALL"))
		all (ADD);
	else {
		loadclubhdr (club);
		p = findqsc (club);
		if (!p)
			addqsc (club, 0, LRF_QUICKSCAN);
		else if (p->flags & LRF_QUICKSCAN)
			addqsc (club, clubhdr.msgno, p->flags);
		else
			addqsc (club, 0, p->flags | LRF_QUICKSCAN);
	}
}


static void
delclub ()
{
	char    club[16];
	struct lastread *p;

	for (;;) {
		if (!getclub (club, RQCDEL, RQCDR, 1))
			return;
		if (sameas (club, "ALL")) {
			all (DEL);
			return;
		} else if (((p = findqsc (club)) == NULL) ||
			   ((p->flags & LRF_QUICKSCAN) == 0)) {
			prompt (RQCDR);
			cnc_end ();
			continue;
		} else {
			/*addqsc(club,-1,p->flags&~LRF_QUICKSCAN); */
			delqsc (club);
			break;
		}
	}
}


void
configurequickscan (int create)
{
	char    opt;
	int     i;

	startqsc ();
	if (create)
		initialise ();

	for (;;) {
		inp_setflags (INF_HELP);
		i = get_menu (&opt, 0, 0, RQCMNU, RCMNUR, "+-V", 0, 0);
		inp_clearflags (INF_HELP);
		if (!i) {
			saveqsc ();
			if (create) {
				struct emailuser ecuser;

				if (!readecuser (thisuseracc.userid, &ecuser))
					return;
				ecuser.flags |= ECF_QSCCFG;
				writeecuser (thisuseracc.userid, &ecuser);
			}
			return;
		}
		if (i == -1) {
			prompt (RQCHELP);
			cnc_end ();
			continue;
		}

		switch (opt) {
		case '+':
			addclub ();
			break;
		case '-':
			delclub ();
			break;
		case 'V':
			listqsc ();
			break;
		}
	}
}


int
quickscanmenu (message_t *msg)
{
	char    opt;
	int     res;

	for (;;) {
		inp_setflags (INF_HELP);
		res = get_menu (&opt, 1, 0, QSMMNU, QWMNUR, "NPRBCS", 0, 0);
		inp_clearflags (INF_HELP);
		if (!res)
			return 'X';
		else if (res < 0) {
			prompt (QSMNUH);
			cnc_end ();
			continue;
		}
		break;
	}

	return tolower (opt);
}


void
doquickscan ()
{
	int     dir = BSD_GT;	/* Direction of scanning */
	int     count;		/* Number of clubs scanned so far */
	int     j;		/* Result of database functions */
	int     opt;		/* Value returned by startscanning() */
	int     startmsg;	/* Message at which scanning begins */
	int     msgno;		/* Actual message number */

	startqsc ();

	/* Loop here for each club */

	do {
		struct lastread *lastread;

	      selclub:
		lastread = (struct lastread *) getqsc ();

		/* End of quickscan? */

		if (!lastread) {
			prompt (QSEMPTY);
			return;
		}


		/* Non-blocking mode */

		inp_nonblock ();


		/* Read this club? */

		if (inemail == OPT_ALL)
			if ((lastread->flags & LRF_QUICKSCAN) == 0)
				continue;
		if (getclubax (&thisuseracc, lastread->club) < CAX_READ)
			continue;
		count++;


		/* Handle quit commands */

		if (fmt_lastresult == PAUSE_QUIT) {
			prompt (QSABORT);
			inp_block ();
			return;
		}


		/* Show 'scanning club xxx...' message */

		if (!keyscan)
			prompt (QSSCAN, lastread->club);
		else
			showkeywords ();


		/* Enter the club, calculate next message */

		enterclub (lastread->club);


		/* Find the first message, if it exists */

		setclub (lastread->club);
		if (lastread->entrymsg < 0) {
			lastread->entrymsg = startmsg =
			    inemail ==
			    OPT_ALL ? lastread->lastmsg +
			    1 : lastread->emllast + 1;
		}
		j = findmsgnum (&msgno,
				dir == BSD_LT ? LASTMSG : lastread->entrymsg,
				dir);
		if (j != BSE_FOUND || msgno < 0) {
			lastread->entrymsg = -1;
			continue;
		} else
			lastread->entrymsg = msgno;


		/* Now scan the club */

		opt = 0;
		opt = startscanning (msgno, dir);

		/* And handle the exit codes */

		switch (opt) {
		case 'X':
			saveqsc ();
			prompt (QSABORT);
			return;

		case 'p':
			prompt (QSLEAVE, clubhdr.club);
		case BSE_BEGIN:
		case 'P':
			dir = BSD_LT;
			break;

		case 'n':
			prompt (QSLEAVE, clubhdr.club);
		case BSE_END:
		case 'N':
		case 'b':
		case 'c':
		case 'r':
			dir = BSD_GT;
			break;

		case 's':
			goto selclub;
		}

	} while ((dir == BSD_GT) ? nextqsc () : prevqsc ());

	saveqsc ();

/*  if(bsi==BSI_MSGNO){
    if(!count)prompt(QSEMPTY);
    else if(!newmsg)prompt(QSNONEW);
    else prompt(QSEND);
  }
  if(bsi!=BSI_MSGNO && dir==BSD_LT){
    prompt(QWRT2EM);
    return -1;
  } */

	prompt (QSDONE);
}




int
qgoclub ()
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
			prompt (SCASK);
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

		if (!findclub (i)) {
			prompt (SCERR);
			cnc_end ();
			continue;
		} else
			break;
	}

	if (!goqsc (i)) {
		saveqsc ();
		addqsc (i, 0, 0);
		saveqsc ();
		goqsc (i);
		prompt (SCADD, i);
	}
	return 1;
}


/* End of File */
