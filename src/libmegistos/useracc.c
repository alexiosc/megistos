/*****************************************************************************\
 **                                                                         **
 **  FILE:     useracc.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Handle user and class information                            **
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
 * $Id: useracc.c,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: useracc.c,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.7  2003/12/24 18:35:07  alexios
 * Fixed #includes.
 *
 * Revision 1.6  2003/12/19 13:25:18  alexios
 * Updated include directives.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/08/13 16:56:08  alexios
 * Fixed error reporting when injoth() fails.
 *
 * Revision 0.4  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added code to recognise user files
 * by magic number. Other minor fixes. Moved various functions
 * from miscfx.c to useracc.c, where they belong.
 *
 * Revision 0.3  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.2  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: useracc.c,v 2.0 2004/09/13 19:44:34 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_MSG_H 1
#include <megistos/bbsinclude.h>

#include <megistos/bbs.h>

#include <mbk/mbk_sysvar.h>


struct shmuserrec *thisshm = NULL, *othrshm = NULL;
classrec_t *cls_classes = NULL;
int     cls_count = 0;


int
usr_exists (char *uid)
{
	DIR    *dp;
	struct dirent *de;
	char    fname[256];
	struct stat s;

	sprintf (fname, "%s/%s", mkfname (USRDIR), uid);
	if (!stat (fname, &s))
		return 1;
	
	if ((dp = opendir (mkfname (USRDIR))) == NULL)
		return 0;
	
	while ((de = readdir (dp)) != NULL) {
		if (sameas (de->d_name, uid)) {
			closedir (dp);
			strcpy (uid, de->d_name);
			return 1;
		}
	}

	closedir (dp);
	return 0;
}


classrec_t *
cls_find (char *s)
{
	int     i;
	
	for (i = 0; i < cls_count; i++) {
		if (sameas (cls_classes[i].name, s)) {
			return (classrec_t *) & cls_classes[i];
		}
	}

	return NULL;
}


int
usr_loadaccount (char *whose, useracc_t * uacc)
{
	char    fname[256];
	int     result;
	FILE   *fp;

	sprintf (fname, "%s/%s", mkfname (USRDIR), whose);
	if ((fp = fopen (fname, "r")) == NULL)
		return 0;
	result = fread (uacc, sizeof (useracc_t), 1, fp);
	fclose (fp);
	if (result != 1)
		return 0;

	if (strncmp (uacc->magic, USR_MAGIC, sizeof (uacc->magic))) {
		error_fatal
		    ("User account for %s is corrupted (invalid magic number)");
	}
	return 1;
}


int
usr_loadonlrec (char *whose, onlinerec_t * onlrec)
{
	char    fname[256];
	int     result;
	FILE   *fp;

	sprintf (fname, "%s/%s", mkfname (ONLINEDIR), whose);
	if ((fp = fopen (fname, "r")) == NULL)
		return 0;
	result = fread (onlrec, sizeof (onlinerec_t), 1, fp);
	fclose (fp);
	if (result != 1)
		return 0;
	return 1;
}


int
usr_saveaccount (useracc_t * uacc)
{
	char    fname[256], fname2[256];
	int     result;
	FILE   *fp;

	sprintf (fname, "%s/%s", mkfname (USRDIR), uacc->userid);
	sprintf (fname2, "%s/.%05d.%s", mkfname (USRDIR), (int) getpid (),
		 uacc->userid);
	if ((fp = fopen (fname2, "w")) == NULL)
		return 0;
	result = fwrite (uacc, sizeof (useracc_t), 1, fp);
	fclose (fp);
	if (result != 1)
		return 0;
	rename (fname2, fname);
	return 1;
}


int
usr_saveonlrec (onlinerec_t * usronl)
{
	char    fname[256], fname2[256];
	int     result;
	FILE   *fp;
	struct stat st;

	sprintf (fname, "%s/%s", mkfname (ONLINEDIR), usronl->userid);
	if (!stat (fname, &st))
		return 1;
	sprintf (fname2, "%s/.%05d.%s",
		 mkfname (ONLINEDIR), (int) getpid (), usronl->userid);
	if ((fp = fopen (fname2, "w")) == NULL)
		return 0;
	result = fwrite (usronl, sizeof (onlinerec_t), 1, fp);
	fclose (fp);
	if (result != 1)
		return 0;
	rename (fname2, fname);
	return 1;
}


void
usr_postcredits (char *userid, int amount, int paid)
{
	useracc_t user, *uacc = &user;

	if (!usr_insys (userid, 0))
		usr_loadaccount (userid, uacc);
	else
		uacc = &othruseracc;
	if (!uacc)
		return;

	uacc->credits += amount;
	uacc->totcreds += amount;
	if (paid)
		uacc->totpaid += amount;
	if (sysvar) {
		sysvar->tcreds += amount;
		if (paid)
			sysvar->tcredspaid += amount;
	}

	if (!usr_insys (userid, 0))
		usr_saveaccount (uacc);
}


void
usr_chargecredits (int amount)
{
	classrec_t *ourclass = cls_find (thisuseracc.curclss);

	if (ourclass)
		if (ourclass->flags & CLF_NOCHRGE)
			return;
	thisuseracc.credits -= amount;
	thisuseracc.totcreds -= amount;
	thisuseronl.statcreds += amount;
}


void
usr_setclass (char *userid, char *newclass, int permanent)
{
	useracc_t *uacc = NULL;

	if (!usr_insys (userid, 0))
		usr_loadaccount (userid, uacc);
	else
		uacc = &othruseracc;
	if (!uacc)
		return;

	if (!permanent) {
		strcpy (uacc->tempclss, uacc->curclss);
		strcpy (uacc->curclss, newclass);
	} else {
		strcpy (uacc->tempclss, newclass);
		strcpy (uacc->curclss, newclass);
		uacc->classdays = 0;
	}

	if (!usr_insys (userid, 0))
		usr_saveaccount (uacc);
}


int
usr_canpay (int amount)
{
	classrec_t *ourclass = cls_find (thisuseracc.curclss);

	if (ourclass)
		if (ourclass->flags & CLF_NOCHRGE)
			return 1;
	return (thisuseracc.credits >= amount);
}


int
usr_insystem (char *userid, int checkinvis, struct shmuserrec **buf)
{
	char    fname[256];
	FILE   *fp;
	int     shmid;

	sprintf (fname, "%s/.shmid-%s", mkfname (ONLINEDIR), userid);
	if ((fp = fopen (fname, "r")) == NULL)
		return 0;
/*  if(buf && !strcmp((*buf)->onl.userid,userid)){
    fclose(fp);
    return 1;
    } */
	if (!fscanf (fp, "%d", &shmid)) {
		error_fatal ("Unable to read file %s", fname);
	}
	fclose (fp);

	if (*buf) {
		shmdt ((char *) *buf);
		*buf = NULL;
	}
	if ((*buf = (struct shmuserrec *) shmat (shmid, NULL, 0)) == NULL)
		return 0;

	if (checkinvis)
		return (((*buf)->onl.flags & OLF_INVISIBLE) == 0);
	else
		return 1;
}


int
usr_insys (char *userid, int checkinvis)
{
	if (!usr_exists (userid))
		return 0;
	return usr_insystem (userid, checkinvis, &othrshm);
}


int
usr_injoth (onlinerec_t * user, char *msg, int force)
{
	char    dummy[MSGMAX + sizeof (long)];
	struct injoth_buf *buf = (struct injoth_buf *) (&dummy);

	if (!force)
		if (user->flags & OLF_BUSY)
			return 0;

	if (user->injothqueue < 0)
		return 0;

	bzero (&dummy, sizeof (dummy));
	buf->mtype = INJ_MESSAGE;
	strncpy (buf->m.simple, msg, MSGMAX - 1);
	buf->m.simple[MSGMAX - 1] = 0;

	if (strlen (msg) + 1 > MSGMAX) {
		error_int
		    ("Message len (%d) exceeded size of injoth buf (%d).",
		     strlen (msg), MSGMAX - 1);
	}

	if (msgsnd (user->injothqueue, buf, strlen (msg) + 1, IPC_NOWAIT) < 0) {
		error_intsys ("Failed to injoth() to %s", user->userid, i,
			      strerror (i));
		return 0;
	}

	return 1;
}



int
usr_injoth_ack (onlinerec_t * user, char *msg, char *ack, int force)
{
	char    dummy[MSGMAX + sizeof (long)];
	struct injoth_buf *buf = (struct injoth_buf *) (&dummy);
	int     len;

	len = sizeof (buf->m.withack.sender) +
	    sizeof (buf->m.withack.ackofs) +
	    strlen (msg) + 1 + strlen (ack) + 1;

	/* If no ACK given, fall back to a simple msg_injoth() */

	if (ack == NULL)
		return usr_injoth (user, msg, force);


	if (!force)
		if (user->flags & OLF_BUSY)
			return 0;

	if (user->injothqueue < 0)
		return 0;

	if (len > MSGMAX - 1) {
		error_int
		    ("Message+Ack len (%d) exceeded size of injoth buf (%d).",
		     len, MSGMAX - 1);
	}

	bzero (&dummy, sizeof (dummy));
	buf->mtype = INJ_MESSAGE_ACK;
	strcpy (buf->m.withack.sender, thisuseracc.userid);
	buf->m.withack.ackofs = strlen (msg) + 1;
	strcpy (buf->m.withack.msg, msg);
	strcpy (&(buf->m.withack.msg[strlen (msg) + 1]), ack);

	if (msgsnd (user->injothqueue, buf, len, IPC_NOWAIT) < 0) {
		error_intsys ("Failed to injoth() to %s", user->userid, i,
			      strerror (i));
		return 0;
	}

	return 1;
}


#define CACHESIZE 32

static char xrefcache[CACHESIZE][24];

static int cachesize = 0;


static void
cachepush (char *s)
{
	memcpy (&xrefcache[1], &xrefcache[0], (CACHESIZE - 1) * 24);
	strcpy (xrefcache[0], s);
	if (cachesize < CACHESIZE)
		cachesize++;
}


static int
cachechk (char *s)
{
	int     i;

	for (i = 0; i < cachesize; i++) {
		if (sameas (s, xrefcache[i])) {
			strcpy (s, xrefcache[i]);
			return 1;
		}
	}
	return 0;
}


int
usr_uidxref (char *userid, int online)
{
	char    matches[1000][80];
	int     num = 0;
	int     retry = 0;
	int     cache;
	
 tryagain:
	if (strlen (userid) < 3 && (!online))
		return 0;
	if (!strlen (userid) && online)
		return 0;
	cache = cachechk (userid);
	if (online)
		if (usr_insys
		    (userid, !hassysaxs (&thisuseracc, USY_MASTERKEY))) {
			if (!cache)
				cachepush (userid);
			return 1;
		}
	if (!online)
		if (usr_exists (userid)) {
			if (!cache)
				cachepush (userid);
			return 1;
		}

	num = 0;
	memset (matches, 0, sizeof (matches));
	if (online) {
		int     i;
		channel_status_t status;

		for (i = 0; i < chan_count; i++) {
			if (channel_getstatus (channels[i].ttyname, &status) <
			    0)
				continue;

			if (status.result == LSR_USER) {
				if (usr_insys
				    (status.user,
				     !hassysaxs (&thisuseracc,
						 USY_MASTERKEY))) {
					if (sameto (userid, status.user) &&
					    (num < 1000)) {
						strcpy (matches[num],
							status.user);
						num++;
					}
				}
			}
		}
	} else {
		FILE   *fp;
		char    command[256], uid[256];

		sprintf (command, "\\ls %s", mkfname (USRDIR));
		if ((fp = popen (command, "r")) == NULL) {
			pclose (fp);
			return 0;
		}
		while (!feof (fp)) {
			uid[0] = 0;
			if (!fscanf (fp, "%s", uid))
				continue;
			if (sameto (userid, uid) && num < 1000) {
				strcpy (matches[num], uid);
				num++;
			}
		}
		pclose (fp);
	}
	
	if (num == 1) {
		cachepush (strcpy (userid, matches[0]));
		return 1;
	} else if (!num && !retry)
		return 0;
	else {
		int     i, ans = 0;

		msg_set (msg_sys);
		for (;;) {
			cnc_end ();
			if (num) {
				prompt (UXRF1, userid);
				for (i = 0; i < num; i++)
					prompt (UXRF2, i + 1, matches[i]);
				prompt (UXRF3, 1, num);
			} else
				prompt (UXRF3A);
			inp_get (0);
			if (!margc) {
				continue;
			} else if (margc && inp_isX (margv[0])) {
				msg_reset ();
				return 0;
			} else if (margc && sameas (margv[0], "?")) {
				continue;
			} else if (num && margc && (ans = atoi (margv[0]))) {
				if (ans > num) {
					prompt (UXRF4);
					continue;
				} else {
					cachepush (strcpy
						   (userid, matches[ans - 1]));
					msg_reset ();
					return 1;
				}
			} else if (margc) {
				msg_reset ();
				strcpy (userid, margv[0]);
				retry = 1;
				goto tryagain;
			}
		}
	}
	return 0;
}
