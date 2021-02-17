/*****************************************************************************\
 **                                                                         **
 **  FILE:     qwkout.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Output messages to a QWK packet                              **
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
 * $Id: qwkout.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: qwkout.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:33:53  alexios
 * Adjusted #includes. Changed struct message to message_t.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/07/18 21:44:48  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.7  1998/12/27 15:48:12  alexios
 * Added autoconf support. Various fixes.
 *
 * Revision 0.6  1998/08/14 11:39:37  alexios
 * Fixed VERY serious one-character bug whereby the QWK mess-
 * age block count would be right- instead of left-aligned,
 * causing some (but not all) off-line readers to choke. Ahem,
 * the QWK specs say that the block count can be either way.
 * Oh well. Specs are specs and implementations are bollocks.
 *
 * Revision 0.5  1998/08/11 10:13:15  alexios
 * Added user encoding translation to the outgoing messages.
 *
 * Revision 0.4  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/03 00:41:28  alexios
 * QWK messages are now NOT translated to the user's current
 * translation preferences. The QWK reader should do this and
 * it's a bad idea anyway. Translation is for on-line BBSing
 * only.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: qwkout.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mail.h>
#include "offline.mail.h"
#include <mailerplugins.h>
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include <mbk/mbk_mailer.h>

#define __EMAILCLUBS_UNAMBIGUOUS__
#include <mbk/mbk_emailclubs.h>

#ifdef USE_LIBZ
#define WANT_ZLIB_H 1
#endif


static int msgno = 0;
static int lastconf = -1;
static FILE *msgdat;
static FILE *ndx = NULL;
static FILE *ndxpers;
static struct qwkhdr qwkhdr;
static char qwkbuf[128];
static int numatt;


static void
clrbuf ()
{
	memset (qwkbuf, 0x20, 128);
}


static void
strbuf (char *s)
{
	memcpy (qwkbuf, s, strlen (s));
}


static void
wrtbuf ()
{
	if (!fwrite (qwkbuf, 128, 1, msgdat)) {
		error_fatalsys ("Unable to write to messages.dat");
	}
}


static char *
mkfield (char *f, char *s, int len)
{
	memset (f, 0x20, len);
	memcpy (f, s, min (len, strlen (s)));
	return f;
}


static char *
mkfielduc (char *f, char *s, int len)
{
	int     i, j = strlen (s);

	memset (f, 0x20, min (j, len));
	memcpy (f, s, j);
	for (i = 0; i < j; i++)
		f[i] = toupper (f[i]);
	return f;
}


static void
makeheader (int clubid, message_t *msg)
{
	char    tmp[256], topic[128];

	memset (&qwkhdr, 0x20, sizeof (struct qwkhdr));
	qwkhdr.status = clubid ? STATUS_N : STATUS_P;
	sprintf (tmp, "%d", msg->msgno);
	mkfield (qwkhdr.number, tmp, sizeof (qwkhdr.number));
	mkfield (qwkhdr.date, qwkdate (msg->crdate), sizeof (qwkhdr.date));
	mkfield (qwkhdr.time, strtime (msg->crtime, 0), sizeof (qwkhdr.time));
	mkfielduc (qwkhdr.whoto, sameas (msg->to, MSG_ALL) ? QWK_ALL : msg->to,
		   sizeof (qwkhdr.whoto));
	mkfielduc (qwkhdr.from, msg->from, sizeof (qwkhdr.from));
	strcpy (topic, msg->subject);
	xlate_out (topic);
	mkfield (qwkhdr.subject, topic,
		 sizeof (qwkhdr.subject) +
		 (usepass ? sizeof (qwkhdr.password) : 0));
	if (msg->flags & MSF_REPLY) {
		sprintf (tmp, "%d", msg->replyto);
		mkfield (qwkhdr.reference, tmp, sizeof (qwkhdr.reference));
	}
	qwkhdr.active = MSG_ACT;
	qwkhdr.conference[0] = clubid & 0xff;
	qwkhdr.conference[1] = (clubid & 0xff00) >> 8;
	qwkhdr.msgno[0] = msgno & 0xff;
	qwkhdr.msgno[1] = (msgno & 0xff00) >> 8;
}


static char *
mkpre (int clubid, message_t *msg)
{
	if (prefs.flags & OMF_HEADER) {
		char    s1[256] = { 0 }, s2[256] = {
		0}, s3[256] = {
		0}, s4[256] = {
		0};
		char    s5[256] = { 0 }, s6[256] = {
		0}, s7[256] = {
		0}, m4u[256] = {
		0};

		msg_set (emailclubs_msg);
		strcpy (s1, xlatehist (msg->history));
		msg_set (mail_msg);
		sprintf (s2, "%s/%d  ", clubid ? clubhdr.club : EMAILCLUBNAME,
			 msg->msgno);
		if (strlen (s1) + strlen (s2) > thisuseracc.scnwidth - 1) {
			s1[78 - strlen (s2)] = '*';
			s1[79 - strlen (s2)] = 0;
		}

		strcpy (s3, msg_get (MHDAY0 + getdow (msg->crdate)));
		strcpy (s4, msg_get (MHJAN + tdmonth (msg->crdate)));
		sprintf (s2, "%s, %d %s %d, %s",
			 s3, tdday (msg->crdate), s4, tdyear (msg->crdate),
			 strtime (msg->crtime, 1));

		if (clubid)
			strcpy (m4u, msg_get (MHFORU));

		if (msg->period) {
			sprint (s3, msg_get (MHPERIOD), msg->period,
				msg_getunit (DAYSNG, msg->period));
		} else {
			strcpy (s3,
				msg->
				flags & MSF_EXEMPT ? msg_get (MHXMPT) : "");
		}
		strcpy (s4, msg->flags & MSF_RECEIPT ? msg_get (MHRRR) : "");

		if (msg->timesread) {
			strcpy (s6, msg_get (MHTMRD));
			sprint (s5, s6, msg->timesread,
				msg_getunit (TIMSNG, msg->timesread));
		} else
			strcpy (s5, "");

		if (msg->replies) {
			strcpy (s7, msg_get (MHNREP));
			sprint (s6, s7, msg->replies,
				msg_getunit (REPSNG, msg->replies));
		} else
			strcpy (s6, "");

		sprint (out_buffer, msg_get (MSGHDR1),
			clubid ? clubhdr.club : EMAILCLUBNAME, msg->msgno, s1,
			s2, s3,
			msg->from, s4,
			(msg->club[0] &&
			 (sameas (thisuseracc.userid, msg->to))) ? m4u : "",
			sameas (msg->to, MSG_ALL) ? msg_getunit (MHALL,
								 1) : msg->to,
			s5, msg->subject, s6);

		if (msg->flags & MSF_FILEATT) {
			if (msg->timesdnl) {
				strcpy (s1, msg_get (MHNDNL));
				sprint (s2, s1, msg->timesdnl,
					msg_getunit (TIMSNG, msg->timesdnl));
			} else
				strcpy (s2, "");
			sprint (&out_buffer[strlen (out_buffer)],
				msg_get (MSGHDR2), msg->fatt, s2);
		}

		strcat (out_buffer, msg_get (MSGHDR3));
		return strdup (out_buffer);
	}

	return NULL;
}


#ifdef USE_LIBZ


static char *
mkbody (int clubid, message_t *msg)
{
	char    fname[256], *body = NULL;
	gzFile *zfp;

	strcpy (fname, mkfname ("%s/%s/" MESSAGEFILE, MSGSDIR,
				msg->club[0] ? msg->club : EMAILDIRNAME,
				(long) msg->msgno));
	if ((zfp = gzopen (fname, "rb")) == NULL) {
		gzclose (zfp);
		error_fatalsys ("Unable to open message %s/%d for reading",
				mkfname (msg->club[0] ? msg->
					 club : EMAILDIRNAME, msg->msgno));
	} else {
		message_t dummy;

		if (gzread (zfp, &dummy, sizeof (dummy)) <= 0) {
			gzclose (zfp);
			error_fatalsys ("Unable to fseek() message %s/%d",
					mkfname (msg->club[0] ? msg->
						 club : EMAILDIRNAME,
						 msg->msgno));
		}
	}

	for (;;) {
		char    buffer[1025];
		int     bytes = 0;

		bytes = gzread (zfp, buffer, sizeof (buffer) - 1);
		if (!bytes)
			break;
		else
			buffer[bytes] = 0;

		if (msg->cryptkey)
			bbscrypt (buffer, bytes, msg->cryptkey);

		if (body == NULL)
			body = strdup (buffer);
		else {
			char   *tmp = alcmem (strlen (body) + bytes + 1);

			sprintf (tmp, "%s%s", body, buffer);
			free (body);
			body = tmp;
		}
	}
	gzclose (zfp);
	return body;
}


#else				/* DON'T USE_LIBZ */


static char *
mkbody (int clubid, message_t *msg)
{
	char    fname[256], *body = NULL;
	FILE   *fp;

	strcpy (fname, mkfname ("%s/%s/" MESSAGEFILE, MSGSDIR,
				msg->club[0] ? msg->club : EMAILDIRNAME,
				msg->msgno));
	if ((fp = fopen (fname, "r")) == NULL) {
		fclose (fp);
		error_fatalsys ("Unable to open message %s/%d for reading",
				mkfname (msg->club[0] ? msg->
					 club : EMAILDIRNAME, msg->msgno));
	} else if (fseek (fp, sizeof (message_t), SEEK_SET)) {
		int     i = errno;

		fclose (fp);
		errno = i;
		error_fatalsys ("Unable to fseek() message %s/%d",
				mkfname (msg->club[0] ? msg->
					 club : EMAILDIRNAME, msg->msgno));
	}
	while (!feof (fp)) {
		char    buffer[1025];
		int     bytes = 0;

		bytes = fread (buffer, 1, sizeof (buffer) - 1, fp);
		if (!bytes)
			break;
		else
			buffer[bytes] = 0;

		if (msg->cryptkey)
			bbscrypt (buffer, bytes, msg->cryptkey);

		if (body == NULL)
			body = strdup (buffer);
		else {
			char   *tmp = alcmem (strlen (body) + bytes + 1);

			sprintf (tmp, "%s%s", body, buffer);
			free (body);
			body = tmp;
		}
	}
	fclose (fp);
	return body;
}


#endif				/* USE_LIBZ */


static char *
mkfooter (int clubid, message_t *msg)
{
	if (msg->flags & MSF_FILEATT) {
		char    fname[256];
		int     res;
		struct stat st;

		strcpy (fname,
			mkfname ("%s/%s/" MSGATTDIR "/" FILEATTACHMENT,
				 MSGSDIR,
				 msg->club[0] ? msg->club : EMAILDIRNAME,
				 msg->msgno));

		/* Check if the file is there */

		if (stat (fname, &st)) {
			sprint (out_buffer, msg_get (ATTNOT6));
			return strdup (out_buffer);
		}


		/* Attempt to make the request for the file */

		if (prefs.flags & OMF_ATT) {
			char    dosfname[13], num[13];
			int     i;

			sprintf (dosfname, "%-8.8s.att",
				 clubid ? msg->club : EMAILCLUBNAME);
			sprintf (num, "%d", msg->msgno);
			strncpy (&dosfname
				 [strlen (dosfname) - 4 - strlen (num)], num,
				 strlen (num));
			for (i = 0; dosfname[i]; i++) {
				dosfname[i] = dosfname[i] == ' ' ? '-' :
				    qwkuc ? toupper (dosfname[i]) :
				    tolower (dosfname[i]);
			}

			numatt++;
			res = mkrequest (clubid ? msg->club : EMAILCLUBNAME,
					 dosfname,
					 fname, msg->msgno, RQP_ATT, RQF_ATT);
		} else
			res = 1;

		if (msg->club[0] && (msg->flags & MSF_APPROVD) == 0 &&
		    getclubax (&thisuseracc, msg->club) < CAX_COOP) {
			sprint (out_buffer, msg_get (ATTNOT5), msg->fatt,
				st.st_size);
		} else if (msg->club[0] &&
			   getclubax (&thisuseracc, msg->club) < CAX_DNLOAD) {
			sprint (out_buffer, msg_get (ATTNOT4), msg->fatt,
				st.st_size);
		} else if (res && prefs.flags & OMF_ATTYES) {
			sprint (out_buffer, msg_get (ATTNOT2), msg->fatt,
				st.st_size, ctlname[0],
				msg->club[0] ? msg->club : EMAILCLUBNAME,
				msg->msgno);
		} else if (res && prefs.flags & OMF_ATTASK) {
			sprint (out_buffer, msg_get (ATTNOT3), msg->fatt,
				st.st_size, ctlname[0],
				msg->club[0] ? msg->club : EMAILCLUBNAME,
				msg->msgno);
		} else
			sprint (out_buffer, msg_get (ATTNOT1), msg->fatt,
				st.st_size, ctlname[0],
				msg->club[0] ? msg->club : EMAILCLUBNAME,
				msg->msgno);

		return strdup (out_buffer);
	}

	return NULL;
}


void
dumpndx (int clubid, message_t *msg)
{
	struct qwkndx ndxrec;

	if (clubid != lastconf) {
		char    fname[256];

		if (ndx) {
			fclose (ndx);
			ndx = NULL;
		}

		sprint (fname, "%03d.ndx", lastconf = clubid);
		if ((ndx = fopen (fname, "w")) == NULL) {
			error_fatalsys ("Unable to create index file %s",
					fname);
		}
	}

	/* Form the index record */

	ndxrec.blkofs = ltomks (1L + (long) ftell (msgdat) / 128L);
	ndxrec.sig = clubid & 0xff;

	/* Always write exactly five bytes. Ignore 32bit word alignment. */

	if (!fwrite (&ndxrec, 5, 1, ndx)) {
		error_fatalsys ("Unable to write to index file.");
	}

	/* Write to PERSONAL.NDX if we need to */

	if (!sameas (msg->to, thisuseracc.userid))
		return;

	if (!fwrite (&ndxrec, 5, 1, ndxpers)) {
		error_fatalsys ("Unable to write to personal.ndx.");
	}
}


void
dumpmsg (char *pre, char *body, char *post)
{
	int     n = 0;
	char    tmp[7];

	n += pre ? strlen (pre) : 0;
	n += body ? strlen (body) : 0;
	n += post ? strlen (post) : 0;

	sprintf (tmp, "%-6d", 1 + (n + 127) / 128);
	strncpy (qwkhdr.blocks, tmp, 6);

	memcpy (qwkbuf, &qwkhdr, sizeof (qwkbuf));
	wrtbuf ();

	if (pre) {
		xlate_out (pre);
		if (!fwrite (pre, strlen (pre), 1, msgdat)) {
			error_fatalsys ("Unable to write to messages.dat");
		}
		free (pre);
	}
	if (body) {
		xlate_out (body);
		if (fwrite (body, strlen (body), 1, msgdat) != 1) {
			error_fatalsys ("Unable to write to messages.dat");
		}
		free (body);
	}
	if (post) {
		xlate_out (post);
		if (!fwrite (post, strlen (post), 1, msgdat)) {
			error_fatalsys ("Unable to write to messages.dat");
		}
		free (post);
	}

	clrbuf ();
	if (n % 128) {
		if (!fwrite (qwkbuf, 128 - (n % 128), 1, msgdat)) {
			error_fatalsys ("Unable to write to messages.dat");
		}
	}
}


static void
updatemsg (int clubid, message_t *msg)
{
	message_t m;

	getmsgheader (msg->msgno, &m);
	m.timesread++;
	writemsgheader (&m);
}


void
receipt (int clubdid, message_t *msg)
{
	message_t rrr;
	char    hdrname[256], fname[256], s1[256], s2[256];
	char    command[256];
	FILE   *fp;

	if (strcmp (msg->to, thisuseracc.userid))
		return;
	sprintf (fname, TMPDIR "/rrrB%d%lx", getpid (), time (0));
	if ((fp = fopen (fname, "w")) == NULL)
		return;

	strcpy (s1,
		msg_get (EMAILCLUBS_MHDAY0 + (cofdate (msg->crdate) - 4) % 7));
	strcpy (s2, msg_get (EMAILCLUBS_MHJAN + tdmonth (msg->crdate)));

	fprintf (fp, msg_get (EMAILCLUBS_RRRBODY),
		 msg_getunit (EMAILCLUBS_SEXMALE, thisuseracc.sex == USX_MALE),
		 thisuseracc.userid, EMAILCLUBNAME, msg->msgno, s1,
		 tdday (msg->crdate), s2, tdyear (msg->crdate),
		 strtime (msg->crtime, 1));

	fclose (fp);

	memset (&rrr, 0, sizeof (rrr));
	strcpy (rrr.from, thisuseracc.userid);
	strcpy (rrr.to, msg->from);
	sprintf (rrr.subject, msg_get (EMAILCLUBS_RRRSUBJ), EMAILCLUBNAME,
		 msg->msgno);
	sprintf (rrr.history, HST_RECEIPT " %s/%d", EMAILCLUBNAME, msg->msgno);
	rrr.flags = MSF_CANTMOD;

	sprintf (hdrname, TMPDIR "/rrrH%d%lx", getpid (), time (0));
	if ((fp = fopen (hdrname, "w")) == NULL) {
		unlink (fname);
		return;
	}
	fwrite (&rrr, sizeof (rrr), 1, fp);
	fclose (fp);

	sprintf (command, "%s %s %s", mkfname (BBSMAILBIN), hdrname, fname);
	system (command);
	unlink (hdrname);
	unlink (fname);

	if (usr_insys (msg->from, 1)) {
		msg_set (mail_msg);
		sprompt_other (othrshm, out_buffer, RRRINJ,
			       thisuseracc.userid);
		usr_injoth (&othruseronl, out_buffer, 0);
	}

	msg->flags &= ~MSF_RECEIPT;
}


void
outmsg (int clubid, message_t *msg)
{
	char   *preamble, *body, *footer;

	makeheader (clubid, msg);

	preamble = mkpre (clubid, msg);
	body = mkbody (clubid, msg);
	footer = mkfooter (clubid, msg);

	dumpndx (clubid, msg);
	dumpmsg (preamble, body, footer);

	if (msg->flags & MSF_RECEIPT) {
		msg_set (emailclubs_msg);
		receipt (clubid, msg);
		msg_set (mail_msg);
	}
	updatemsg (clubid, msg);
}


void static
mkxlation ()
{
	if (!loadprefs (USERQWK, &userqwk)) {
		error_fatal ("Unable to read user mailer preferences for %s",
			     thisuseracc.userid);
	}

	readxlation ();
	xlationtable = (userqwk.flags & OMF_TR) >> OMF_SHIFT;

	if (userqwk.flags & USQ_GREEKQWK) {

		/* Greek QWK, translate NL/CR to ASCII 0x0c */

		xlation[xlationtable]['\n'] = EOL_GREEKQWK;
		xlation[xlationtable]['\r'] = EOL_GREEKQWK;

	} else {

		/* Normal QWK, translate NL/CR to ASCII 224 */

		xlation[xlationtable]['\n'] = EOL_QWK;
		xlation[xlationtable]['\r'] = EOL_QWK;

#ifdef GREEK

		/* Translate accented lower case eta (ASCII 224) to "n" */
		/* It isn't an eta, but it looks extremely close and we */
		/* can't know the exact charset used, so only ASCII is  */
		/* a certainty. */

		if (fixeta)
			xlation[xlationtable][224] = etaxlt;

#endif				/* GREEK */

	}
}


int
messagesdat ()
{
	if ((msgdat = fopen ("messages.dat", "w")) == NULL) {
		error_logsys ("Unable to create messages.dat");
		return 1;
	}

	if ((ndxpers = fopen ("personal.ndx", "w")) == NULL) {
		error_logsys ("Unable to create personal.ndx");
		return 1;
	}

	mkxlation ();

	msgno = numatt = 0;
	lastconf = -1;

	/* Write the QWK copyright signature */

	clrbuf ();
	strbuf (QWKSIG);
	wrtbuf ();

	return 0;
}


int
getnumatt ()
{
	return numatt;
}


/* End of File */
