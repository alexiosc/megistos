/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubread.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1995                                               **
 **  PURPOSE:  Read Club messages                                           **
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
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support. Slight fixes.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:04:17  alexios
 * Added functionality to look for messages in ALL clubs, not
 * just the ones configured for Quickscan (of course, 'all'
 * being defined as 'all clubs the user has access to'). This is
 * useful while looking for new messages to the user, where we
 * don't care whether a club is in the user's Quickscan or not.
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


char   *keywords[128];
char   *phonetic[128];
int     numkeys = 0;

int     quickscan;		/* Quickscanning */
int     filescan;		/* Filescanning */
int     keyscan;		/* Keyscanning */
int     inemail = OPT_ALL;	/* Scanning from within email (readopt) */
int     allclubs = 0;		/* Scan ALL clubs, not just in quickscan */
int     savecounter = 0;	/* Countdown to saving last read msgnos */
int     lastkey = 0;		/* Last key compared or # of key found */


void
showkeywords ()
{
	int     i;

	if (numkeys == 1)
		prompt (RKSCAN1, keywords[0]);
	else {
		prompt (RKSCAN2, keywords[0]);
		for (i = 1; i < numkeys - 1; i++)
			prompt (RKSCAN3, keywords[i]);
		prompt (RKSCAN4, keywords[numkeys - 1]);
	}
}


int
methodmenu (int d)
{
	char    opt;
	int     i;

	for (;;) {
		inp_setflags (INF_HELP);
		if (!d)
			i = get_menu (&opt, 0, 0, RCMNU, RCMNUR, "SFTLKQ",
				      RCMNUD, 'S');
		else
			i = get_menu (&opt, 0, 0, DMNU, DMNUR, "SFTLKQ", DMNUD,
				      'S');
		inp_clearflags (INF_HELP);
		if (!i)
			return 0;
		if (i == -1) {
			prompt (d ? DMNUH : RCMNUH);
			cnc_end ();
			continue;
		} else
			return opt;
	}
	return 0;
}


void
quickmenu (int file)
{
	char    opt, fname[256];
	int     i;
	struct stat st;
	struct emailuser ecuser;

	if (!readecuser (thisuseracc.userid, &ecuser))
		return;
	sprintf (fname, "%s/%s", mkfname (QSCDIR), thisuseracc.userid);
	if (stat (fname, &st) || st.st_size == 0 ||
	    (ecuser.flags & ECF_QSCCFG) == 0) {
		prompt (RQCFH);
		cnc_end ();
		configurequickscan (1);
		return;
	}

	for (;;) {
		inp_setflags (INF_HELP);
		i = get_menu (&opt, 0, 0, RQMNU, RCMNUR, "SFTLKC", RCMNUD,
			      'S');
		inp_clearflags (INF_HELP);
		if (!i)
			return;
		if (i == -1) {
			prompt (RQMNUH);
			cnc_end ();
			continue;
		} else
			break;
	}

	quickscan = 1;
	switch (opt) {
	case 'S':
		scanmessages ();
		return;
	case 'T':
		inemail = OPT_TOYOU;
		scanmessages ();
		inemail = OPT_ALL;
		return;
	case 'F':
		inemail = OPT_FROMYOU;
		scanmessages ();
		inemail = OPT_ALL;
		return;
	case 'L':
		listmessages (file);
		return;
	case 'K':
		keywordscan ();
		return;
	case 'C':
		configurequickscan (0);
		return;
	}
}


void
clubread (int file)
{
	int     method;

	if (file && (getclubax (&thisuseracc, clubhdr.club) < CAX_DNLOAD)) {
		prompt (DNLNAX);
		cnc_end ();
		return;
	}


	/* Configure scanning */

	filescan = file;
	quickscan = 0;

	method = methodmenu (file);
	switch (method) {
	case 0:
		return;
	case 'S':
		scanmessages ();
		break;
	case 'T':
		inemail = OPT_TOYOU;
		scanmessages ();
		inemail = OPT_ALL;
		break;
	case 'F':
		inemail = OPT_FROMYOU;
		scanmessages ();
		inemail = OPT_ALL;
		break;
	case 'L':
		listmessages (file);
		break;
	case 'K':
		keywordscan ();
		break;
	case 'Q':
		quickscan = 1;
		quickmenu (file);
		break;
	}
}


void
keywordscan ()
{
	char   *i;
	char    tmp[MAXINPLEN];
	int     n;

	if (quickscan)
		startqsc ();
	for (;;) {
		if (cnc_more ()) {
			i = cnc_nxtcmd;
			strcpy (tmp, cnc_nxtcmd);
			strcpy (inp_buffer, cnc_nxtcmd);
			inp_parsin ();
		} else {
			prompt (RKASK);
			inp_get (0);
			if (!margc)
				continue;
		}
		i = margv[0];

		if (!i[0])
			continue;
		else if (inp_isX (i))
			return;
		else if (sameas ("?", i)) {
			prompt (RKHELP);
			cnc_end ();
			continue;
		} else {
			char    s[256], *cp;

			memset (keywords, 0, sizeof (keywords));
			for (numkeys = 0, n = 0; n < margc && n < 128;
			     n++, numkeys++) {
				strncpy (s, margv[n], sizeof (s));
				while (s[strlen (s) - 1] == 32)
					s[strlen (s) - 1] = 0;
				for (cp = s; *cp && (*cp == 32); cp++);
				keywords[n] = alcmem (strlen (cp) + 1);
				strcpy (keywords[n], cp);
				phonetic[n] = alcmem (strlen (cp) + 1);
				strcpy (phonetic[n], stgxlate (cp, KEYSCAN));
			}
			break;
		}
	}

	if (!quickscan)
		showkeywords ();

	keyscan = 1;
	if (quickscan)
		doquickscan ();
	else
		startscanning (-1, BSD_GT);
	keyscan = 0;

	for (n = 0; n < numkeys; n++)
		if (keywords[n]) {
			free (keywords[n]);
			free (phonetic[n]);
			keywords[n] = NULL;
		}
	numkeys = 0;
}


void
fileapp ()
{
	prompt (FAPPSCN);

	keyscan = 0;
	filescan = 2;

	startqsc ();

	startscanning (0, BSD_GT);
	keyscan = filescan = 0;

	rmlocks ();
}


/* End of File */
