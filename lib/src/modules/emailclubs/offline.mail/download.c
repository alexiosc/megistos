/*****************************************************************************\
 **                                                                         **
 **  FILE:     download.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Downloading mail packets                                     **
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
 * Revision 1.5  2003/12/27 12:33:53  alexios
 * Adjusted #includes. Changed struct message to message_t.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:44:48  alexios
 * Minor fixes wrt to auto-translation of fields in the QWK
 * format files.
 *
 * Revision 0.5  1998/12/27 15:48:12  alexios
 * Added autoconf support. Various bug fixes.
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
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "offline.mail.h"
#include <mailerplugins.h>
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include <mbk/mbk_mailer.h>

#define __EMAILCLUBS_UNAMBIGUOUS__
#include <mbk/mbk_emailclubs.h>


static int nummsgs = 0;
static int num4u = 0;
static int numconf = 0;


static int
doemail ()
{
	int     res;
	int     t;
	int     n = 0, n4 = 0;
	int     shown = 0, first = 1;
	char    c;

	if (!readecuser (thisuseracc.userid, &emlu)) {
		error_fatal ("Unable to read E-mail preference file for %s",
			     thisuseracc.userid);
	}

	prompt (OMDLEM);
	goclub (NULL);

	res =
	    findmsgto (&t, thisuseracc.userid, emlu.lastemailqwk + 1, BSD_GT);

	inp_nonblock ();
	thisuseronl.flags |= (OLF_BUSY | OLF_NOTIMEOUT);

	if (read (0, &c, 1))
		if (c == 27 || c == 15 || c == 3)
			abort ();
	if (fmt_lastresult == PAUSE_QUIT)
		abort ();

	while (res == BSE_FOUND) {
		message_t msg;

		if (read (0, &c, 1))
			if (c == 27 || c == 15 || c == 3)
				abort ();
		if (fmt_lastresult == PAUSE_QUIT)
			abort ();

		if (!first) {
			if ((res =
			     npmsgto (&t, thisuseracc.userid, t + 1,
				      BSD_GT)) != BSE_FOUND)
				break;
		} else
			first = 0;

		getmsgheader (t, &msg);
		if (t > msg.msgno)
			break;
		if (!shown) {
			shown = 1;
			startind ();
		} else
			progressind (1);
		outmsg (0, &msg);
		nummsgs++;
		n++;
		num4u++;
		n4++;
		emlu.lastemailqwk = msg.msgno;
	}
	inp_block ();
	thisuseronl.flags &= ~(OLF_BUSY | OLF_NOTIMEOUT);
	if (shown)
		endind ();

	prompt (OMDLT2, n, n4);
	return 0;
}


static int
doclub (struct lastread *p)
{
	int     res;
	int     t;
	int     n = 0, n4 = 0;
	int     shown = 0;
	int     first = 1;
	char    c;

	if (!
	    ((p->flags & LRF_INQWK) &&
	     (getclubax (&thisuseracc, p->club) > CAX_ZERO)))
		return 0;

	numconf++;

	prompt (OMDLT1, p->club, clubhdr.descr);
	goclub (p->club);

	res = findmsgnum (&t, p->qwklast + 1, BSD_GT);

	thisuseronl.flags |= (OLF_BUSY | OLF_NOTIMEOUT);
	inp_nonblock ();

	if (read (0, &c, 1))
		if (c == 27 || c == 15 || c == 3)
			abort ();
	if (fmt_lastresult == PAUSE_QUIT)
		abort ();

	while (res == BSE_FOUND) {
		message_t msg;

		if (read (0, &c, 1))
			if (c == 27 || c == 15 || c == 3)
				abort ();
		if (fmt_lastresult == PAUSE_QUIT)
			abort ();

		if (!first) {
			if ((res = npmsgnum (&t, t + 1, BSD_GT)) != BSE_FOUND)
				continue;
		} else
			first = 0;

		getmsgheader (t, &msg);
		if (t > msg.msgno)
			break;
		if (!shown) {
			shown = 1;
			startind ();
		} else
			progressind (1);
		outmsg (clubhdr.clubid, &msg);
		nummsgs++;
		n++;
		if (sameas (msg.to, thisuseracc.userid)) {
			n4++;
			num4u++;
		}
		p->qwklast = t;
	}
	inp_block ();

	thisuseronl.flags &= ~(OLF_BUSY | OLF_NOTIMEOUT);
	if (shown)
		endind ();
	prompt (OMDLT2, n, n4);
	return 0;
}



static int
controldat ()
{
	FILE   *fp = fopen ("control.dat", "w");
	struct lastread *p;
	char    tmp[256];

	if (!fp) {
		error_logsys ("Unable to create control.dat");
		return 1;
	}

	strcpy (tmp, sysvar->bbstitle);
	xlate_out (tmp);
	fprintf (fp, "%s\r\n", tmp);

	strcpy (tmp, sysvar->city);
	xlate_out (tmp);
	fprintf (fp, "%s\r\n", tmp);

	strcpy (tmp, sysvar->dataphone);
	xlate_out (tmp);
	fprintf (fp, "%s\r\n", tmp);

	strcpy (tmp, msg_get (ADMNAM));
	xlate_out (tmp);
	fprintf (fp, "%s\r\n", tmp);

	fprintf (fp, "00000,%s\r\n", bbsid);
	fprintf (fp, "%s,%s\r\n", qwkdate (today ()), strtime (now (), 1));
	fprintf (fp, "%s\r\n\r\n0\r\n", thisuseracc.userid);
	fprintf (fp, "%d\r\n", nummsgs);
	fprintf (fp, "%d\r\n", numconf);

	fprintf (fp, "0\r\n%s\r\n", omceml);

	p = resetqsc ();
	while (p != NULL) {
		if (!
		    ((p->flags & LRF_INQWK) &&
		     (getclubax (&thisuseracc, p->club) > CAX_ZERO)))
			goto next;
		fprintf (fp, "%d\r\n%s\r\n", clubhdr.clubid, p->club);
	      next:
		p = nextqsc ();
	}

	fprintf (fp, "%s\r\n%s\r\n%s\r\n",
		 ansihi ? hifile : "", "", ansibye ? byefile : "");
	fclose (fp);

	return 0;
}


static int
addtodoorid ()
{
	FILE   *fp;

	if ((fp = fopen ("door.id", "a")) == NULL) {
		fclose (fp);
		return 1;
	}
#ifdef GREEK
	if (userqwk.flags & USQ_GREEKQWK)
		fprintf (fp, "GREEKQWK\r\n");
#endif
	fprintf (fp, "RECEIPT\r\n");
	outcontroltypes (fp);
	fclose (fp);

	return 0;
}


int
omdownload ()
{
	struct lastread *p;
	int     res;

	readprefs (&prefs);

	if (addtodoorid ())
		return 1;

	nummsgs = num4u = numconf = 0;

	prompt (OMDLHD);

	openreqdb ();

	if ((res = messagesdat ()) != 0)
		return res;

	if ((res = doemail ()) != 0)
		return res;

	p = startqsc ();
	while (p) {
		if ((res = doclub (p)) != 0)
			return res;
		if (fmt_lastresult == PAUSE_QUIT)
			return 1;
		p = nextqsc ();
	}

	prompt (OMCLF);

	/* Deal with requested files and attachments */

	{
		int     i = getnumatt ();

		prompt (MSGSTOT, nummsgs, msg_getunit (MSGSNG, nummsgs));
		if (num4u)
			prompt (MSGS4U, num4u, msg_getunit (MSGSNG, num4u));
		if (i)
			prompt (MSGSAT, i, msg_getunit (MSGSNG, i));
	}

	doatt ();

	if ((res = controldat ()) != 0)
		return res;

	/* Everything's ok, update the structures */

	if (!writeecuser (thisuseracc.userid, &emlu)) {
		error_fatal ("Unable to write E-mail preference file for %s",
			     thisuseracc.userid);
	}

	updateqsc ();
	saveqsc ();
	doneqsc ();

	return 0;
}


/* End of File */
