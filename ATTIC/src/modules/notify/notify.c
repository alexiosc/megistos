/*****************************************************************************\
 **                                                                         **
 **  FILE:     notify.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 1997, Version 0.1                                **
 **  PURPOSE:  Notify users about other users logging in.                   **
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
 * $Id: notify.c,v 2.1 2004/09/13 19:55:34 alexios Exp $
 *
 * $Log: notify.c,v $
 * Revision 2.1  2004/09/13 19:55:34  alexios
 * Changed email addresses.
 *
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/02/29 16:45:15  alexios
 * Added one minor bug fix; one error reporting fix; and two minor code
 * beautification changes.
 *
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.4  1999/07/18 21:47:34  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.3  1998/12/27 16:06:58  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 1.2  1998/07/24 10:23:07  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:14:02  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/11/03 23:53:22  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id: notify.c,v 2.1 2004/09/13 19:55:34 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_notify.h"


#define NOTIFYDIR BBSDATADIR"/notify"


promptblock_t *msg;

int     entrykey;
int     invkey;
int     sopkey;
int     numusr;

struct listitem {
	char    userid[24];
};

struct listitem *list = NULL;

int     numusers;
int     own;


int
listcmp (const void *a, const void *b)
{
	return strcmp (((struct listitem *) a)->userid,
		       ((struct listitem *) b)->userid);
}


void
init ()
{
	mod_init (INI_ALL);
	msg = msg_open ("notify");
	msg_setlanguage (thisuseracc.language);
	entrykey = msg_int (ENTRYKEY, 0, 129);
	invkey = msg_int (SOPKEY, 0, 129);
	sopkey = msg_int (INVKEY, 0, 129);
	numusr = msg_int (NUMUSR, 1, 1000);
}


inline void
donelist ()
{
	if (list != NULL) {
		free (list);
		list = NULL;
		numusers = 0;
	}
}


inline void
newlist ()
{
	if (list != NULL)
		donelist ();
	list = alcmem (numusr * sizeof (thisuseracc.userid));
	numusers = 0;
}


void
loadlist (char *userid)
{
	char    fname[256];
	FILE   *fp;
	struct stat st;

	newlist ();
	sprintf (fname, "%s/%s", mkfname (NOTIFYDIR), userid);

	if (stat (fname, &st)) return;

	if ((fp = fopen (fname, "r")) == NULL) {
		if (errno != ENOENT) {
			error_fatalsys ("Unable to open %s", fname);
		} else
			return;
	}
	while (!feof (fp)) {
		char    line[256], *cp;

		if (!fgets (line, sizeof (line), fp)) break;
		cp = strtok (line, "\n\r");
		if (!usr_exists (cp)) continue;
		strcpy (list [numusers++].userid, cp);
	}
	fclose (fp);
	qsort (list, numusers, sizeof (struct listitem), listcmp);
	own = strcmp (userid, thisuseracc.userid);
}


void
savelist ()
{
	char    fname[256];
	FILE   *fp;
	int     i;

	sprintf (fname, "%s/%s", mkfname (NOTIFYDIR), thisuseracc.userid);
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Unable to create %s", fname);
	}
	for (i = 0; i < numusers; i++)
		fprintf (fp, "%s\n", list[i].userid);
	fclose (fp);
}


void
notifyothers ()
{
	int     i;
	char    fname[256];
	struct stat st;
	struct listitem key;
	channel_status_t status;

	strcpy (key.userid, thisuseracc.userid);

	for (i = 0; i < chan_count; i++) {
		if (channel_getstatus (channels[i].ttyname, &status)) {
			if (status.result == LSR_USER) {
				sprintf (fname, "%s/%s", mkfname (NOTIFYDIR),
					 status.user);
				if (stat (fname, &st))
					continue;

				/* Check for Notify invisibility */

				usr_insys (status.user, 0);
				if (key_owns (&thisuseracc, invkey) &&
				    (!key_owns (&othruseracc, invkey)))
					continue;

				/* Now load the other user's notify list and check it */

				loadlist (status.user);
				if (bsearch
				    (&key, list, numusers,
				     sizeof (struct listitem),
				     listcmp) != NULL) {
					sprompt_other (othrshm, out_buffer,
						       INJMSG,
						       msg_getunit (SEXM,
								    thisuseracc.
								    sex ==
								    USX_MALE),
						       thisuseracc.userid);
					usr_injoth (&othruseronl, out_buffer,
						    0);
				}
			}
		}
	}
}


void
notifyme ()
{
	int     i, j, k;
	int    *online;
	char    tmp[8192];

	loadlist (thisuseracc.userid);
	online = alcmem (numusers * sizeof (int));
	bzero (online, numusers * sizeof (int));
	for (i = j = 0; i < numusers; i++) {
		if (!usr_insys (list[i].userid, 1))
			continue;
		if (key_owns (&othruseracc, invkey) &&
		    !key_owns (&thisuseracc, invkey))
			continue;
		online[i] = 1 + (othruseracc.sex == USX_FEMALE);
		j++;
	}

	if (!j)
		return;
	for (i = k = 0; i < numusers; i++) {
		if (!online[i])
			continue;
		k++;
		if (k == 1) {
			if (j == 1)
				sprompt (out_buffer, LOGIN1,
					 msg_getunit (CONM, online[i]));
			else
				sprompt (out_buffer, LOGIN1,
					 msg_getunit (CONP, 1));
		}
		if (k > 1 && k < j) {
			sprompt (tmp, LOGIN3);
			strcat (out_buffer, tmp);
		} else if (k > 1 && k == j) {
			sprompt (tmp, LOGIN4);
			strcat (out_buffer, tmp);
		}
		sprompt (tmp, LOGIN2, msg_getunit (SEXM, online[i]),
			 list[i].userid);
		strcat (out_buffer, tmp);
	}
	sprompt (tmp, LOGIN5);
	strcat (out_buffer, tmp);
	print (out_buffer);
}


void
add ()
{
	if (numusers == numusr)
		prompt (ADDLIM, numusr);
	else if (numusers > numusr)
		prompt (ADDLM2, numusers, numusr);
	else {
		struct listitem key;
		useracc_t acc;

		for (;;) {
			if (!get_userid (key.userid, ADDASK, ADDERR, 0, 0, 0))
				return;
			if (sameas (key.userid, thisuseracc.userid)) {
				prompt (ADDHUH);
				cnc_end ();
				continue;
			}
			if (bsearch
			    (&key, list, numusers, sizeof (struct listitem),
			     listcmp) != NULL) {
				prompt (ADDEXS, key.userid);
				cnc_end ();
				continue;
			} else
				break;
		}
		strcpy (list[numusers].userid, key.userid);
		numusers++;
		usr_loadaccount (key.userid, &acc);
		prompt (ADDOK, msg_getunit (SEXM, acc.sex == USX_MALE),
			acc.userid);
		qsort (list, numusers, sizeof (struct listitem), listcmp);
	}
}


void
delete ()
{
	struct listitem key, *p;

	if (!numusers) {
		prompt (NOUSERS);
		return;
	}

	for (;;) {
		if (!get_userid (key.userid, DELASK, DELERR, 0, 0, 0))
			return;
		if ((p =
		     bsearch (&key, list, numusers, sizeof (struct listitem),
			      listcmp)) == NULL) {
			prompt (DELERR, key.userid);
			cnc_end ();
			continue;
		} else
			break;
	}

	if (numusers > 1) {
		strcpy (p->userid, "\377\377\377");
		qsort (list, numusers, sizeof (struct listitem), listcmp);
	}
	numusers--;
	prompt (DELOK, key.userid);
}


void
listusers ()
{
	int     i;

	if (!numusers) {
		prompt (NOUSERS);
		return;
	}
	prompt (LISTHD);
	for (i = 0; i < numusers; i++)
		prompt (LISTU, list[i].userid);
	prompt (LISTFT, numusers);
}


void
run ()
{
	int     shownmenu = 0;
	char    c = 0;

	if (!key_owns (&thisuseracc, entrykey)) {
		prompt (NOENTRY);
		return;
	}

	loadlist (thisuseracc.userid);

	for (;;) {
		thisuseronl.flags &= ~OLF_BUSY;
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownmenu) {
				prompt (MENU);
				shownmenu = 2;
			}
		} else
			shownmenu = 1;
		if (thisuseronl.flags & OLF_MMCALLING && thisuseronl.input[0]) {
			thisuseronl.input[0] = 0;
		} else {
			if (!cnc_nxtcmd) {
				if (thisuseronl.flags & OLF_MMCONCAT) {
					thisuseronl.flags &= ~OLF_MMCONCAT;
					return;
				}
				if (shownmenu == 1) {
					prompt (SHMENU);
				} else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			switch (c) {
			case 'H':
				prompt (HELP, numusr);
				break;
			case 'L':
				listusers ();
				break;
			case 'A':
				add ();
				break;
			case 'D':
				delete ();
				break;
			case 'X':
				prompt (LEAVE);
				savelist ();
				return;
			case '?':
				shownmenu = 0;
				break;
			default:
				prompt (ERRSEL, c);
				cnc_end ();
				continue;
			}
		}
		if (fmt_lastresult == PAUSE_QUIT)
			fmt_resetvpos (0);
		cnc_end ();
	}
}


void
done ()
{
	if (own)
		savelist ();
	msg_close (msg);
}


int
handler_run (int argc, char *argv[])
{
	atexit (done);
	init ();
	run ();
	done ();
	return 0;
}


int
handler_userdel (int argc, char **argv)
{
	char   *victim = argv[2], fname[1024];

	if (strcmp (argv[1], "--userdel") || argc != 3) {
		fprintf (stderr, "User deletion handler: syntax error\n");
		return 1;
	}

	if (!usr_exists (victim)) {
		fprintf (stderr,
			 "User deletion handler: user %s does not exist\n",
			 victim);
		return 1;
	}

	sprintf (fname, "%s/%s", mkfname (NOTIFYDIR), victim);
	unlink (fname);

	return 0;
}


int
handler_login (int argc, char **argv)
{
	init ();
	notifyothers ();
	notifyme ();
	done ();
	return 0;
}


mod_info_t mod_info_notify = {
	"notify",
	"User login notification",
	"Alexios Chouchoulas <alexios@bedroomlan.org>",
	"Notifies users when their friends log in (or are already logged in).",
	RCS_VER,
	"1.0",
	{95, handler_login}
	,			/* Login handler */
	{0, handler_run}
	,			/* Interactive handler */
	{0, NULL}
	,			/* Install logout handler */
	{0, NULL}
	,			/* Hangup handler */
	{0, NULL}
	,			/* Cleanup handler */
	{50, handler_userdel}	/* Delete user handler */
};


int
main (int argc, char *argv[])
{
	mod_setinfo (&mod_info_notify);
	return mod_main (argc, argv);
}


/* End of File */
