/*****************************************************************************\
 **                                                                         **
 **  FILE:     funcs.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **  PURPOSE:  Miscellaneous email/club functions                           **
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
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/28 23:11:36  alexios
 * Added a history entry for networked messages.
 *
 * Revision 0.5  1999/07/18 21:21:38  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Migrated to the new locking functions.
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
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mbk_emailclubs.h>
#include <megistos/email.h>
#ifdef USE_LIBZ
#define WANT_ZLIB_H 1
#endif


struct histentry {
	char    keyword[32];
	int     index;
};


static struct histentry histentries[] = {
	{HST_CC, HISTCC},
	{HST_CP, HISTCP},
	{HST_FW, HISTFW},
	{HST_NETMAIL, HISTNM},
	{HST_RECEIPT, HISTRRR},
	{HST_REPLY, HISTREP},
	{HST_AUTOFW, HISTAFW},
	{HST_DIST, HISTDST},
	{HST_OFFLINE, HISTOLR},
	{HST_NET, HISTNET},
	{"", 0}
};


int
getrdmsgno (int *num, int msg, int help, int err, int def)
{
	char    w[256];
	char    c;
	int     i;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (help && sameas (cnc_nxtcmd, "?")) {
				cnc_end ();
				if (help)
					prompt (help);
				continue;
			}
			if (sameas (cnc_nxtcmd, ".")) {
				*num = def;
				return 1;
			}
			strcpy (w, cnc_word ());
		} else {
			prompt (msg, def);
			inp_get (0);
			strcpy (w, margv[0]);
			if ((!margc || (margc == 1 && sameas (margv[0], ".")))
			    && !inp_reprompt ()) {
				*num = def;
				return 1;
			} else if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 0;
			}
			if (sameas (margv[0], "?")) {
				cnc_end ();
				if (help)
					prompt (help);
				continue;
			}
		}
		latinize (w);
		if (sameas (w, "F")) {
			*num = -1;
			return 1;
		} else if (sameas (w, "L")) {
			*num = LASTMSG;
			return 1;
		}
		if (sscanf (w, "%d", &i) == 1) {
			*num = max (1, i);
			return 1;
		} else {
			prompt (err);
			cnc_end ();
			continue;
		}
	}
	return 0;
}


int
askyesno (boolean, msg, err, charge)
int    *boolean, msg, err, charge;
{
	int     c = 0;

	for (;;) {
		fmt_lastresult = 0;
		if (cnc_more ())
			c = cnc_yesno ();
		else {
			prompt (msg, charge, msg_getunit (CRDSING, charge));
			inp_get (0);
			if (margc) {
				if (inp_isX (margv[0])) {
					return 0;
				}
			} else
			    if ((!margc ||
				 (margc == 1 && sameas (margv[0], "."))) &&
				!inp_reprompt ()) {
				*boolean = 0;
				return 1;
			}
			cnc_begin ();
			c = cnc_yesno ();
		}
		switch (c = toupper (c)) {
#ifdef GREEK
		case -109:
		case -84:
#endif
		case 'Y':
			*boolean = 1;
			return 1;
#ifdef GREEK
		case -92:
		case -116:
#endif
		case 'N':
			*boolean = 0;
			return 1;
		case '?':
			break;
		default:
			cnc_end ();
			if (err)
				prompt (err, c);
		}
	}
	return 0;
}


int
confirmcancel ()
{
	int     i;

	if (!get_bool (&i, WECCAN, WERRSEL, WECCND, 0))
		return 0;
	else
		return i;
}


char   *
xlatehist (char *s)
{
	static char buffer[256];
	char    temp[256], *cp = s, keyword[256], value[256];
	int     i, n, found;

	if (!s)
		return NULL;
	buffer[0] = 0;
	while (*cp) {
		if ((sscanf (cp, "%s%n", keyword, &n)) != 1)
			break;
		for (i = 0, found = 0; histentries[i].index; i++) {
			if (!strcmp (histentries[i].keyword, keyword)) {
				if (keyword[strlen (keyword) - 1] == ':') {
					cp += n;
					if (sscanf (cp, "%s%n", value, &n) ==
					    1) {
						sprintf (temp,
							 msg_get (histentries
								  [i].index),
							 value);
						if (buffer[0]) {
							strcat (buffer, ", ");
						}
						strcat (buffer, temp);
					}
				} else {
					if (buffer[0]) {
						strcat (buffer, ", ");
					}
					strcat (buffer,
						msg_get (histentries[i].
							 index));
				}
				found = 1;
				break;
			}
		}
		if (!found) {
			strcat (buffer, keyword);
			strcat (buffer, " ");
		}
		cp += n;
	}
	return buffer;
}


void
showheader (char *sig, struct message *msg)
{
	char    s1[256] = { 0 }, s2[256] = {
	0}, s3[256] = {
	0}, s4[256] = {
	0};
	char    s5[256] = { 0 }, s6[256] = {
	0}, s7[256] = {
	0}, m4u[256] = {
	0};

	strcpy (s1, xlatehist (msg->history));
	sprintf (s2, "%s/%d  ", sig, msg->msgno);
	if (strlen (s1) + strlen (s2) > thisuseracc.scnwidth - 1) {
		s1[78 - strlen (s2)] = '*';
		s1[79 - strlen (s2)] = 0;
	}

	strcpy (s3, msg_get (MHDAY0 + getdow (msg->crdate)));
	strcpy (s4, msg_get (MHJAN + tdmonth (msg->crdate)));
	sprintf (s2, "%s, %d %s %d, %s",
		 s3, tdday (msg->crdate), s4, tdyear (msg->crdate),
		 strtime (msg->crtime, 1));

#ifdef CLUBS
	strcpy (m4u, msg_get (MHFORU));
#endif

	if (msg->period) {
		sprintf (s3, msg_get (MHPERIOD), msg->period,
			 msg_getunit (DAYSNG, msg->period));
	} else {
		strcpy (s3, msg->flags & MSF_EXEMPT ? msg_get (MHXMPT) : "");
	}
	strcpy (s4, msg->flags & MSF_RECEIPT ? msg_get (MHRRR) : "");

	if (msg->timesread) {
		strcpy (s6, msg_get (MHTMRD));
		sprintf (s5, s6, msg->timesread,
			 msg_getunit (TIMSNG, msg->timesread));
	} else
		strcpy (s5, "");

	if (msg->replies) {
		strcpy (s7, msg_get (MHNREP));
		sprintf (s6, s7, msg->replies,
			 msg_getunit (REPSNG, msg->replies));
	} else
		strcpy (s6, "");

	prompt (MSGHDR1,
		sig, msg->msgno, s1,
		s2, s3,
		msg->from, s4,
		(msg->club[0] &&
		 (sameas (thisuseracc.userid, msg->to))) ? m4u : "",
		sameas (msg->to, MSG_ALL) ? msg_getunit (MHALL, 1) : msg->to,
		s5, msg->subject, s6);

	if (msg->flags & MSF_FILEATT) {
		if (msg->timesdnl) {
			strcpy (s1, msg_get (MHNDNL));
			sprintf (s2, s1, msg->timesdnl,
				 msg_getunit (TIMSNG, msg->timesdnl));
		} else
			strcpy (s2, "");
		prompt (MSGHDR2, msg->fatt, s2);
	}

	prompt (MSGHDR3);
}



int
writeecuser (char *uid, struct emailuser *user)
{
	char    fname[256], lock[256];
	FILE   *fp;

	sprintf (fname, "%s/%s", mkfname (MSGUSRDIR), uid);
	sprintf (lock, ECUSERLOCK, uid);

	if ((lock_wait (lock, 20)) == LKR_TIMEOUT)
		return 0;
	lock_place (lock, "writing");

	if ((fp = fopen (fname, "w")) == NULL) {
		lock_rm (lock);
		return 0;
	}
	if (fwrite (user, sizeof (struct emailuser), 1, fp) != 1) {
		fclose (fp);
		lock_rm (lock);
		return 0;
	}
	fclose (fp);
	lock_rm (lock);

	return 1;
}


int
readecuser (char *uid, struct emailuser *user)
{
	char    fname[256], lock[256];
	FILE   *fp;

	sprintf (fname, "%s/%s", mkfname (MSGUSRDIR), uid);
	sprintf (lock, ECUSERLOCK, uid);

	if ((lock_wait (lock, 20)) == LKR_TIMEOUT)
		return 0;
	lock_place (lock, "reading");

	if ((fp = fopen (fname, "r")) == NULL) {
		lock_rm (lock);
		memset (user, 0, sizeof (struct emailuser));
		strcpy (user->forwardto, thisuseracc.userid);
		user->prefs = ECP_QUOTEYES | ECP_LOGINASK;
		return 2;
	}
	if (fread (user, sizeof (struct emailuser), 1, fp) != 1) {
		fclose (fp);
		lock_rm (lock);
		return 0;
	}
	fclose (fp);
	lock_rm (lock);

	return 1;
}


void
appendsignature (char *into)
{
	FILE   *fp, *fp2;
	char    fname[256], buffer[1024];
	int     bytes;

	sprintf (fname, "%s/%s", mkfname (MSGSIGDIR), thisuseracc.userid);

	if ((fp = fopen (fname, "r")) != NULL) {
		if ((fp2 = fopen (into, "a")) == NULL) {
			fclose (fp);
			return;
		}

		do {
			if ((bytes =
			     fread (buffer, 1, sizeof (buffer), fp)) != 0)
				fwrite (buffer, bytes, 1, fp2);
		} while (bytes);

		fclose (fp);
		fclose (fp2);
	}
}


char   *
addhistory (char *h, char *s, int len)
{
	char    temp[1024];

	sprintf (temp, "%s %s", s, h);
	strncpy (h, temp, len);
	return h;
}



void
bbscrypt (char *buf, int size, int key)
{
	char    longkey[4] = { 0, 0, 0, 0 };
	register char smallkey;
	register int i;

	if (!key)
		return;
	memcpy (longkey, &key, sizeof (int));
	smallkey = (longkey[0] ^ longkey[1] ^ longkey[2] ^ longkey[3]);
	for (i = 0; i < size; i++)
		buf[i] ^= smallkey;
}


int
checklocks (struct message *msg)
{
	int     i;
	char    lock[256], dummy[64];
	channel_status_t status;

	for (i = 0; i < chan_count; i++) {
		if (channel_getstatus (channels[i].ttyname, &status)) {
			if ((status.result == LSR_USER) &&
			    (!sameas (status.user, thisuseracc.userid))) {
				sprintf (dummy, "%d", msg->msgno);
				sprintf (lock, MSGREADLOCK,
					 channels[i].ttyname,
					 msg->club[0] ? msg->
					 club : EMAILCLUBNAME, dummy);
				if (lock_check (lock, dummy) > 0)
					return 0;
			}
		}
	}
	return 1;
}


int
askmsgno ()
{
	int     newmsgno;

	if (!get_number (&newmsgno, RDGONUM, 0, LASTMSG, 0, 0, 0))
		return -1;
	if (!newmsgno)
		newmsgno = 1;
	return newmsgno;
}


void
decompressmsg (struct message *msg)
{
#ifdef USE_LIBZ

	gzFile *zfp;
	FILE   *fp;
	char    fname1[256];
	char    fname2[256];

	sprintf (fname1, "%s/%s/" MESSAGEFILE, mkfname (MSGSDIR),
		 msg->club[0] ? msg->club : EMAILDIRNAME, (long) msg->msgno);
	sprintf (fname2, "%s/%s/.tmp-%ld", mkfname (MSGSDIR),
		 msg->club[0] ? msg->club : EMAILDIRNAME, (long) msg->msgno);

	if ((zfp = gzopen (fname1, "rb")) == NULL) {
		error_fatalsys ("Unable to gzopen() %s", fname1);
	}
	if ((fp = fopen (fname2, "w")) == NULL) {
		error_fatalsys ("Unable to fopen() %s", fname2);
	}

	for (;;) {
		char    buf[1024];
		int     bytes = gzread (zfp, buf, sizeof (buf));

		if (bytes <= 0)
			break;
		if (fwrite (buf, sizeof (buf), 1, fp) != 1) {
			error_fatalsys ("I/O error while writing.", fname2);
		}
	}

	gzclose (zfp);
	fclose (fp);
	if (rename (fname2, fname1)) {
		error_fatalsys ("Unable to move decompressmsged message.");
	}
#endif
}



void
compressmsg (struct message *msg)
{
#ifdef USE_LIBZ

	gzFile *zfp;
	FILE   *fp;
	char    fname1[256];
	char    fname2[256];

	sprintf (fname1, "%s/%s/" MESSAGEFILE, mkfname (MSGSDIR),
		 msg->club[0] ? msg->club : EMAILDIRNAME, (long) msg->msgno);
	sprintf (fname2, "%s/%s/.tmp-%ld", mkfname (MSGSDIR),
		 msg->club[0] ? msg->club : EMAILDIRNAME, (long) msg->msgno);

	if ((fp = fopen (fname1, "r")) == NULL) {
		error_fatalsys ("Unable to fopen() %s", fname2);
	}
	if ((zfp = gzopen (fname2, "wb")) == NULL) {
		error_fatalsys ("Unable to gzopen() %s", fname1);
	}

	for (;;) {
		char    buf[1024];
		int     bytes = fread (buf, 1, sizeof (buf), fp);

		if (bytes <= 0)
			break;
		if (gzwrite (zfp, buf, sizeof (buf)) <= 0) {
			error_fatalsys ("I/O error while writing.", fname1);
		}
	}

	gzclose (zfp);
	fclose (fp);
	if (rename (fname2, fname1)) {
		error_fatalsys ("Unable to move compressed message.");
	}
#endif
}


/* End of File */
