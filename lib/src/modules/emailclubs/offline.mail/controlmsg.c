/*****************************************************************************\
 **                                                                         **
 **  FILE:     controlmsg.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Handle QWK control messages                                  **
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
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:37:13  alexios
 * DOSsified output to QWK files.
 *
 * Revision 0.3  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
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
#include <megistos/offline.mail.h>
#include <megistos/../../mailer.h>
#include <megistos/mbk_offline.mail.h>


#define __MAILER_UNAMBIGUOUS__
#include <megistos/mbk_mailer.h>

#define __EMAILCLUBS_UNAMBIGUOUS__
#include <megistos/mbk_emailclubs.h>


static int
ctl_request (struct qwkhdr *qwkhdr, struct message *msg)
{
	int     n = 8;
	int     msgno;
	char    clubname[256], fixedreq[80];
	char   *cp;

	/* No need to process the body */

	skip ();

	/* Gobble the keyword */

	sscanf (msg->subject, "%*s %n", &n);

	/* Accept either REQUEST club/msgno or REQUEST msgno commands */

	if ((cp = strchr (&msg->subject[n], '/')) != NULL) {
		*cp = ' ';
		if (sscanf (&msg->subject[n], "%s %d", clubname, &msgno) != 2) {
			prompt (DIRRQST, &msg->subject[n]);
			prompt (DIRERR1);
			return 0;
		}
	} else if (sscanf (&msg->subject[n], "%d", &msgno) != 1) {
		prompt (DIRRQST, &msg->subject[n]);
		prompt (DIRERR1);
		return 0;
	} else
		strcpy (clubname, msg->club);

	/* Check the existence of the club */

	sprintf (fixedreq, "%s/%d", clubname, msgno);
	if (sameas (omceml, clubname))
		strcpy (clubname, omceml);
	else if (!findclub (clubname)) {
		prompt (DIRRQST, fixedreq);
		prompt (DIRRQUS);
		return 0;
	} else
		loadclubhdr (clubname);

	sprintf (fixedreq, "%s/%d", clubname, msgno);
	prompt (DIRRQST, fixedreq);
	goclub (sameas (omceml, clubname) ? NULL : clubname);


	/* Check the existence of the attachment and request it */

	{
		struct message att;
		char    dosfname[13], num[13], fname[256];
		int     i, res;

		bzero (&att, sizeof (att));
		getmsgheader (msgno, &att);
		if (att.msgno != msgno || ((att.flags & MSF_FILEATT) == 0)) {
			prompt (DIRNFND);
			return 0;
		}

		sprintf (dosfname, "%-8.8s.att",
			 att.club[0] ? att.club : EMAILCLUBNAME);
		sprintf (num, "%d", att.msgno);
		strncpy (&dosfname[strlen (dosfname) - 4 - strlen (num)], num,
			 strlen (num));
		for (i = 0; dosfname[i]; i++) {
			dosfname[i] = dosfname[i] == ' ' ? '-' :
			    qwkuc ? toupper (dosfname[i]) :
			    tolower (dosfname[i]);
		}

		strcpy (fname,
			mkfname ("%s/%s/" MSGATTDIR "/" FILEATTACHMENT,
				 MSGSDIR,
				 att.club[0] ? att.club : EMAILDIRNAME,
				 att.msgno));

		res = mkrequest (att.club[0] ? att.club : EMAILCLUBNAME,
				 dosfname, fname, att.msgno, RQP_ATTREQ, 0);

		prompt (res ? DIRDONE : DIRERR2);
		return res;
	}

	return 1;
}


static int
ctl_add (struct qwkhdr *qwkhdr, struct message *msg)
{
	int     n = 4;
	char    clubname[256];

	/* No need to process the body */

	skip ();

	/* Gobble the keyword and check syntax */

	if (sscanf (msg->subject, "%*s %n%s", &n, clubname) != 1) {
		prompt (DIRADD, &msg->subject[n]);
		prompt (DIRERR1);
		return 0;
	}

	/* Check the existence of the club */

	if (sameas (omceml, clubname)) {
		prompt (DIRADD, omceml);
		prompt (DIRCANT);
		return 0;
	} else if (!findclub (clubname)) {
		prompt (DIRADD, clubname);
		prompt (DIRRQUS);
		return 0;
	} else {
		struct lastread *p;

		loadclubhdr (clubname);
		p = findqsc (clubname);
		prompt (DIRADD, clubname);
		if (p->flags & LRF_INQWK) {
			prompt (DIRNNEED);
			return 0;
		}
		addqsc (clubname, clubhdr.msgno, LRF_INQWK);
		prompt (DIRDONE);
	}
	return 1;
}


static int
ctl_drop (struct qwkhdr *qwkhdr, struct message *msg)
{
	int     n = 5;
	char    clubname[256];

	/* No need to process the body */

	skip ();

	/* Gobble the keyword and check syntax */

	if (sscanf (msg->subject, "%*s %n%s", &n, clubname) != 1) {
		prompt (DIRDROP, &msg->subject[n]);
		prompt (DIRERR1);
		return 0;
	}

	/* Check the existence of the club */

	if (sameas (omceml, clubname)) {
		prompt (DIRDROP, omceml);
		prompt (DIRCANT);
		return 0;
	} else if (!findclub (clubname)) {
		prompt (DIRDROP, clubname);
		prompt (DIRRQUS);
		return 0;
	} else {
		struct lastread *p;

		loadclubhdr (clubname);
		p = findqsc (clubname);
		prompt (DIRDROP, clubname);
		if ((p->flags & LRF_INQWK) == 0) {
			prompt (DIRNNEED);
			return 0;
		}
		delqsc (clubname);
		prompt (DIRDONE);
	}
	return 1;
}


static int
ctl_reset (struct qwkhdr *qwkhdr, struct message *msg)
{
	int     n = 6;
	char    clubname[256], tmp[256];
	int     msgno;

	/* No need to process the body */

	skip ();

	/* Gobble the keyword */

	if (sscanf (msg->subject, "%*s %n%s %d", &n, clubname, &msgno) != 2) {
		prompt (DIRRESET, &msg->subject[n]);
		prompt (DIRERR1);
		return 0;
	}


	/* Check the existence of the club */

	sprintf (tmp, "%s %d", clubname, msgno);
	if (sameas (omceml, clubname))
		strcpy (clubname, omceml);
	else if (!findclub (clubname)) {
		prompt (DIRRESET, tmp);
		prompt (DIRRQUS);
		return 0;
	} else {
		struct lastread *p;

		loadclubhdr (clubname);
		p = findqsc (clubname);
		if (!(p->flags & LRF_INQWK)) {
			sprintf (tmp, "%s %d", clubname, msgno);
			prompt (DIRRESET, tmp);
			prompt (DIRCNTR);
			return 0;
		}
		if (msgno < 0)
			msgno = max (msgno + clubhdr.msgno, 0);
		else
			msgno = min (msgno, clubhdr.msgno);
		sprintf (tmp, "%s %d", clubname, msgno);
		prompt (DIRRESET, tmp);
		setlastread (clubname, msgno);
		prompt (DIRDONE);
	}
	return 1;
}


struct ctltype {
	char   *keyword;
	int     (*handler) (struct qwkhdr *, struct message *);
};


static struct ctltype ctltypes[] = {
	{"REQUEST", ctl_request},
	{"ADD", ctl_add},
	{"DROP", ctl_drop},
	{"RESET", ctl_reset},
	{"-", NULL}
};


void
outcontroltypes (FILE * fp)
{
	int     i;

	for (i = 0; strcmp (ctltypes[i].keyword, "-"); i++) {
		fprintf (fp, "CONTROLTYPE = %s\n\r", ctltypes[i].keyword);
	}
}


static int serial = 0;

static int
addforeign (struct qwkhdr *qwkhdr, struct message *msg)
{
	char    fname[15];

	sprintf (fname, "foreign.%03d", ++serial);
	dobody (fname);
	prompt (DIRFOR, msg->subject);
	return mkrequest (msg->club[0] ? msg->club : omceml,
			  fname, msg->subject, -1, RQP_CTLMSG, RQF_CTLMSG);
}


int
handlecontrolmsg (struct qwkhdr *qwkhdr, struct message *msg)
{
	char    tmp[256];
	int     i;

	for (i = 0; strcmp (ctltypes[i].keyword, "-"); i++) {
		sprintf (tmp, "%s ", ctltypes[i].keyword);
		if (sameto (tmp, msg->subject) ||
		    sameas (ctltypes[i].keyword, msg->subject))
			return (int) (*ctltypes[i].handler) (qwkhdr, msg);
	}

	return addforeign (qwkhdr, msg);
}


/* End of File */
