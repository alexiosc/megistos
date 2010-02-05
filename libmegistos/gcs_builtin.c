/*****************************************************************************\
 **                                                                         **
 **  FILE:     gcs_builtin.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  A few built-in global commands.                              **
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
\*****************************************************************************/


/*
 * $Id: gcs_builtin.c,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: gcs_builtin.c,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.8  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.7  2003/12/19 13:24:30  alexios
 * Updated include directives.
 *
 * Revision 1.6  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.5  2003/09/27 20:33:12  alexios
 * Aesthetic fixes (indentations, spacing, etc).
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: gcs_builtin.c,v 2.0 2004/09/13 19:44:34 alexios Exp $";


#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_SHM_H 1
#define WANT_TIME_H 1
#include <megistos/bbsinclude.h>

#include <megistos/bbs.h>

#include <mbk/mbk_sysvar.h>

#define USERPAGED (othruseronl.onlinetime-othruseronl.lastpage \
		   <othruseracc.pagetime)
#define ISYSOP    (hassysaxs(&thisuseracc,USY_MASTERKEY))


/* Print out the current date and time. */

static int
gcs_time ()
{
	long    date, time;
	char    month[64];

	if (!margc)
		return 0;
	else if ((margc == 1) &&
		 (sameas (margv[0], "/time") || sameas (margv[0], "/t"))) {

		date = today ();
		time = now ();
		msg_set (msg_sys);
		strcpy (month, msg_string (tdmonth (date) + DTCJAN));
		prompt (TIME,
			tdday (date),
			month, tdyear (date), strtime (now (), 1));
		msg_reset ();

		return 1;
	}

	return 0;
}


/* List online users. */

int
gcs_hash ()
{
	int     i;
	char    majst[32], minst[32], user[24];
	char   *lonstr, *supstr, *nixstr;
	int     baud;

	if (!margc)
		return 0;
	else if ((margc != 1) || !sameas (margv[0], "/#"))
		return 0;

	msg_set (msg_sys);
	prompt (WHOHDR);
	lonstr = msg_string (WHOLON);
	supstr = msg_string (WHOSUP);
	nixstr = msg_string (WHONIX);

	for (i = 0; i < chan_count; i++) {
		char    fname[256], line[256];
		FILE   *fp;

		sprintf (fname, "%s/.status-%s",
			 mkfname (CHANDEFDIR), channels[i].ttyname);

		if ((fp = fopen (fname, "r")) == NULL) {
			/*int i=errno; */
			continue;
		}

		fgets (line, sizeof (line), fp);
		fclose (fp);

		if (sscanf (line, "%s %s %d %s", majst, minst, &baud, user) !=
		    4)
			continue;

		if (!strcmp (minst, "LOGIN")) {
			prompt (WHOLINE1,
				channels[i].channel,
				lonstr, channel_baudstg (baud));

		} else if (!strcmp (minst, "USER")) {
			if (!strcmp (user, "[SIGNUP]")) {
				prompt (WHOLINE1,
					channels[i].channel,
					supstr, channel_baudstg (baud));

			} else if (!strcmp (user, "[UNIX]")) {
				prompt (WHOLINE1,
					channels[i].channel,
					nixstr, channel_baudstg (baud));

			} else {
				struct shmuserrec *ushm = NULL;

				if (usr_insystem (user, !ISYSOP, &ushm)) {
					char    status, invis;

					if (!ushm)
						continue;

					if (ushm->onl.flags & OLF_BUSY)
						status = 'B';
					else if (ushm->onl.pagestate ==
						 PGS_OFF)
						status = 'P';
					else
						status = ' ';

					if (ushm->onl.flags & OLF_INVISIBLE)
						invis = 'I';
					else
						invis = ' ';
					prompt (WHOLINE2,
						channels[i].channel,
						ushm->onl.userid,
						channel_baudstg (baud),
						status,
						invis,
						ushm->onl.
						descr[(int) thisuseracc.
						      language - 1]);
				}
				shmdt ((char *) ushm);
			}
		}
	}

	msg_reset ();
	free (lonstr);
	free (supstr);
	free (nixstr);

	return 1;
}


/* Print out how many credits a user has. */

int
gcs_crdavail ()
{
	if (margc == 1 && sameas (margv[0], "/$")) {
		char    crdpf[MSGBUFSIZE], minpf[MSGBUFSIZE];

		msg_set (msg_sys);
		strcpy (minpf,
			msg_getunit (MINSING, thisuseronl.onlinetime == 1));
		strcpy (crdpf,
			msg_getunit (CRDSING, thisuseracc.credits == 1));
		prompt (CRDAVAIL, thisuseronl.onlinetime, minpf,
			thisuseracc.credits, crdpf);
		msg_reset ();
		return 1;
	}
	return 0;
}



/* Print out recent logins. */

int
gcs_recent ()
{
	FILE   *fp;
	char    command[256];
	int     line, day = -1, limit = 0, changes = 0, c;

	if ((margc >= 1) &&
	    (sameas (margv[0], "/recent") || sameas (margv[0], "/rc"))) {

		/* Has the optional argument been specified? */

		if ((margc == 2) &&
		    (sameas (margv[1], "help") || sameas (margv[1], "?"))) {

			/* Provide help */

			msg_set (msg_sys);
			prompt (RCNTHLP);
			msg_reset ();
			cnc_end ();
			return 1;

		} else if ((margc == 1) ||
			   ((margc == 2) && (limit = atoi (margv[1])) != 0)) {

			/* List the maximal number of recent users, or an
			 * optionally specified number (e.g /rc 10 to show the
			 * last 10 users logged in. */

			msg_set (msg_sys);
			prompt (LSTHDR);
			sprintf (command, "tac %s 2>/dev/null",
				 mkfname (RECENTFILE));
			if ((fp = popen (command, "r")) == NULL)
				return 0;
			line = 0;

			while (!feof (fp)) {
				char    user[32], tty[32], date[32],
				    tim1[32], tim2[32];
				int     delta;
				time_t  t1, t2;
				struct tm *dt;

				if (fmt_lastresult == PAUSE_QUIT)
					break;

				if (fscanf
				    (fp, "%s %s %lx %lx\n", user, tty, &t1,
				     &t2) != 4)
					break;

				dt = localtime (&t1);
				strcpy (date, strdate (makedate (dt->tm_mday,
								 dt->tm_mon +
								 1,
								 1900 +
								 dt->
								 tm_year)));

				strcpy (tim1, strtime (maketime (dt->tm_hour,
								 dt->tm_min,
								 dt->tm_sec),
						       1));
				dt = localtime (&t2);
				strcpy (tim2, strtime (maketime (dt->tm_hour,
								 dt->tm_min,
								 dt->tm_sec),
						       1));
				delta = t2 - t1;
				line++;
				if (limit && (line > limit))
					break;
				else if (!limit) {
					if ((day != -1) &&
					    (dt->tm_mday != day))
						changes++;
					if (changes >= 2)
						break;
				}
				if ((c = chan_getnum (tty)) < 0)
					c = 0;
				prompt (LSTLIN,
					user,
					c,
					date,
					tim1,
					tim2,
					delta / 3600,
					(delta % 3600) / 60, delta % 60);
				day = dt->tm_mday;
			}
			prompt (RCFTR, line);
			msg_reset ();
			pclose (fp);
			cnc_end ();
			return 1;

		} else if ((margc == 2) && usr_uidxref (margv[1], 0)) {

			/* A specific user was requested. List that user's
			 * recent logons. */

			struct stat st;
			useracc_t user;

			sprintf (command, "%s/%s", mkfname (RECENTDIR),
				 margv[1]);
			if (stat (command, &st)) {
				msg_set (msg_sys);
				prompt (UNKUSR, margv[1]);
				msg_reset ();
				cnc_end ();
				return 1;
			}
			usr_loadaccount (margv[1], &user);
			msg_set (msg_sys);
			cnc_end ();
			prompt (USRHDR, margv[1], user.connections);
			sprintf (command, "tac %s/%s 2>/dev/null",
				 mkfname (RECENTDIR), margv[1]);

			if ((fp = popen (command, "r")) == NULL)
				return 0;
			line = 0;

			while (!feof (fp)) {
				char    tty[32], date[32], tim1[32], tim2[32];
				int     delta;
				time_t  t1, t2;
				struct tm *dt;

				if (fmt_lastresult == PAUSE_QUIT)
					break;

				if (fscanf (fp, "%s %lx %lx\n", tty, &t1, &t2)
				    != 3)
					break;

				dt = localtime (&t1);
				strcpy (date,
					strdate (makedate (dt->tm_mday,
							   dt->tm_mon + 1,
							   1900 +
							   dt->tm_year)));

				strcpy (tim1,
					strtime (maketime (dt->tm_hour,
							   dt->tm_min,
							   dt->tm_sec), 1));

				dt = localtime (&t2);
				strcpy (tim2,
					strtime (maketime (dt->tm_hour,
							   dt->tm_min,
							   dt->tm_sec), 1));
				delta = t2 - t1;
				if ((c = chan_getnum (tty)) < 0)
					c = 0;

				prompt (USRLIN,
					c,
					date,
					tim1,
					tim2,
					delta / 3600,
					(delta % 3600) / 60, delta % 60);

				if (++line >= RECENT_ENTRIES)
					break;
			}

			prompt (URCFTR);
			msg_reset ();
			pclose (fp);
			cnc_end ();
			return 1;

		} else if (margc == 2) {

			/* We assume the argument is a wrong username */

			msg_set (msg_sys);
			prompt (UNKUSR, margv[1]);
			msg_reset ();
			cnc_end ();
			return 1;
		}
	}

	return 0;
}


/* Print out the GPL. */

int
gcs_license ()
{
	if (!margc)
		return 0;
	else if ((margc == 1) &&
		 (sameas (margv[0], "/license") ||
		  sameas (margv[0], "/gpl"))) {
		char    fname[256];

		strcpy (fname, mkfname (DOCDIR "/COPYING"));
		out_printfile (fname);
		return 1;

	} else if ((margc == 1) &&
		   (sameas (margv[0], "/rules") ||
		    sameas (margv[0], "/conditions"))) {
		char    fname[256];

		strcpy (fname, mkfname (DOCDIR "/RULES"));
		out_printfile (fname);
		return 1;

	}

	return 0;
}


static int
dopage ()
{
	/* If the user doesn't have the page override key, a few conditions must
	 * be checked first to ensure the other user's privacy isn't intruded
	 * upon. */

	if (!key_owns (&thisuseracc, sysvar->pgovkey)) {

		/* The other users allows pages but disallows page
		 * flooding. Check last page time via the USERPAGED macro. */

		if (othruseronl.pagestate == PGS_ON && USERPAGED) {
			char    tmp[80];

			strcpy (tmp, msg_getunit (SEXM,
						  othruseracc.sex ==
						  USX_MALE));
			prompt (PAGL2M, tmp, othruseracc.userid,
				othruseracc.pagetime, msg_getunit (MINSING,
								   othruseracc.
								   pagetime ==
								   1));
			return 0;

		} else if (othruseronl.pagestate == PGS_OFF) {

			/* The user disalows pages altogether. */

			prompt (PAGOFF,
				msg_getunit (SEXM,
					     othruseracc.sex == USX_MALE),
				othruseracc.userid);
			return 0;
		}
	}

	/* Only Sysops can page invisible people. */

	if (!(othruseronl.flags & OLF_INVISIBLE) || ISYSOP) {
		char   *pgfrom =
		    (char *) &thisuseronl.descr[(int) othruseracc.language -
						1];
		char    injbuf[MSGBUFSIZE];

		if (!hassysaxs (&othruseracc, USY_MASTERKEY)
		    && (thisuseronl.flags & OLF_INVISIBLE)) {

			/* Only sysops can *page* while invisible. */

			prompt (URINVS);
			return 0;

		} else if (margc == 2) {
			sprompt_other (othrshm, injbuf,
				       othruseronl.
				       flags & OLF_BUSY ? PAGMSG1 : PAGMSG2,
				       msg_getunit (SEXM,
						    thisuseracc.sex ==
						    USX_MALE),
				       thisuseracc.userid, pgfrom);
		} else {
			inp_raw ();
			sprompt_other (othrshm, injbuf,
				       othruseronl.
				       flags & OLF_BUSY ? PAGNOT1 : PAGNOT2,
				       msg_getunit (SEXM,
						    thisuseracc.sex ==
						    USX_MALE),
				       thisuseracc.userid, pgfrom, margv[2]);
		}

		/* Is the other user non-busy and in a module that supports
		 * paging at this point? */

		if (!(othruseronl.flags & OLF_BUSY)) {
			prompt (PAGEOK,
				msg_getunit (ACKM,
					     othruseracc.sex == USX_MALE),
				othruseracc.userid);
			usr_injoth (&othruseronl, injbuf, 0);
			othruseronl.lastpage = othruseronl.onlinetime;
			return 1;

		} else if (othruseronl.pagestate == PGS_STORE ||
			   key_owns (&thisuseracc, sysvar->pgovkey)) {

			/* Store the page for later delivery. */

			char    ack[MSGBUFSIZE];

			prompt (PAGNPST,
				msg_getunit (NOMM,
					     othruseracc.sex == USX_MALE),
				othruseracc.userid);

			sprompt (ack, PAGSTOK,
				 msg_getunit (SEXM,
					      othruseracc.sex == USX_MALE),
				 othruseracc.userid);

			usr_injoth_ack (&othruseronl, injbuf, ack, 1);
			othruseronl.lastpage = othruseronl.onlinetime;
			return 1;

		} else
			prompt (PAGNPS,
				msg_getunit (ACKM,
					     othruseracc.sex == USX_MALE),
				othruseracc.userid);
	}
	return 0;
}


/* Page another user and set our own paging preferences. */

int
gcs_page ()
{
	if (margc && sameas (margv[0], "/p")) {
		msg_set (msg_sys);

		if (!key_owns (&thisuseracc, sysvar->pagekey)) {

			/* The user doesn't have permissions to page. */

			prompt (CANTPG);

		} else if (margc == 1) {

			/* Produce a help string. */

			prompt (PAGFMT);

		} else if (!usr_insys (margv[1], !ISYSOP)) {

			/* Set preferences. */

			if (sameas (margv[1], "on")) {
				thisuseronl.pagestate = PGS_ON;
				prompt (PAGTON,
					thisuseracc.pagetime,
					msg_getunit (MINSING,
						     thisuseracc.pagetime ==
						     1));

			} else if (sameas (margv[1], "off")) {
				thisuseronl.pagestate = PGS_OFF;
				prompt (PAGTOF);

			} else if (sameas (margv[1], "ok")) {
				thisuseronl.pagestate = PGS_OK;
				prompt (PAGTOK);

			} else if (sameas (margv[1], "store")) {
				thisuseronl.pagestate = PGS_STORE;
				prompt (PAGTST);

			} else if (sameas (margv[1], SYSOP)) {
				prompt (PGSYSOP);
				thisuseronl.lastconsolepage = time (NULL);

			} else if (sameas (margv[1], "all") &&
				   (key_owns (&thisuseracc, sysvar->pallkey)))
			{

				/* Paging all users (if this user has permission). */

				int     i, count = 0;
				channel_status_t status;

				for (i = 0; i < chan_count; i++) {
					if (channel_getstatus
					    (channels[i].ttyname, &status) < 0)
						continue;

					if (status.result == LSR_USER) {
						if (sameas (status.user,
							    thisuseracc.
							    userid))
							continue;

						if (usr_insys
						    (status.user, !ISYSOP)) {
							if (!othrshm)
								continue;
							count += dopage ();
						}
					}
				}

				if (!count)
					prompt (PALLNC);

			} else {

				/* Page a single user. */

				int     i, count = 0;
				char    userid[25];
				channel_status_t status;

				for (i = 0; i < chan_count; i++) {
					if (channel_getstatus
					    (channels[i].ttyname, &status) < 0)
						continue;

					if (status.result == LSR_USER) {
						if (usr_insys
						    (status.user, !ISYSOP)) {
							if (!othrshm)
								continue;

							if (othruseronl.
							    flags &
							    OLF_INVISIBLE &&
							    (!ISYSOP))
								continue;

							if (sameto (margv[1],
								    othruseronl.
								    userid)) {
								count++;
								strcpy (userid,
									othruseronl.
									userid);
							}
						}
					}
				}

				if (!count) {
					prompt (PAGNON, margv[1]);
				} else if (count > 1) {
					prompt (PAGMOM, margv[1]);
				} else {
					usr_insys (userid, !ISYSOP);
					dopage ();
				}
			}
		} else
			dopage ();

		msg_reset ();
		return 1;
	}

	return 0;
}


/* Toggle bot mode manually. */

static int
gcs_bot ()
{
	if (!margc)
		return 0;
	else if (margc == 1 && (sameas (margv[0], "/_bot"))) {
		thisuseronl.flags ^= OLF_ISBOT;
		if (thisuseronl.flags & OLF_ISBOT) {
			mod_setbot (1);
			print
			    ("290 Bot mode active.\n290 Enter /_bot to turn off.\n");
			print
			    ("290 If you're not a bot, things will get VERY confusing now.\n");
		} else {
			mod_setbot (0);
			print ("290 Bot mode off.\n");
		}
		return 1;
	} else
		return 0;
}



/* Main GCS entry point. This is mandatory. */

int
__INIT_GCS__ ()
{
	if (gcs_hash ())
		return 1;
	if (gcs_page ())
		return 1;
	if (gcs_recent ())
		return 1;
	if (gcs_time ())
		return 1;
	if (gcs_crdavail ())
		return 1;
	if (gcs_license ())
		return 1;
	if (gcs_bot ())
		return 1;

	return 0;
}
