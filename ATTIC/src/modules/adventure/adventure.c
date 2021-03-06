/*****************************************************************************\
 **                                                                         **
 **  FILE:     adventure.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1999.                                                **
 **  PURPOSE:  User shell for the hacked ZIP (Infocom interpreter)          **
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
 * $Id: adventure.c,v 2.1 2004/09/13 19:55:34 alexios Exp $
 *
 * $Log: adventure.c,v $
 * Revision 2.1  2004/09/13 19:55:34  alexios
 * Changed email addresses.
 *
 * Revision 2.0  2004/09/13 19:44:49  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/24 20:30:30  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:16  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/08/10 00:46:33  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id: adventure.c,v 2.1 2004/09/13 19:55:34 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_STAT_H 1
#define WANT_DIRENT_H 1
#define WANT_WAIT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_adventure.h"

promptblock_t *msg;

int     entrykey;
int     topkey;
int     playkey;
char   *savedgame;


struct game_t {
	char   *libtitle;	/* For sorting purposes */
	char   *fname;
	char   *title;
};


struct game_t *games = NULL;
int     numgames = 0;


#define GAMEDIR       BBSDATADIR"/adventure"
#define GAMEINDEXFILE GAMEDIR"/00INDEX"
#define TOPFILE       GAMEDIR"/00TOP"



int
gamecmp (const void *a, const void *b)
{
	return strcmp (((struct game_t *) a)->libtitle,
		       ((struct game_t *) b)->libtitle);
}



static void
gatherlist ()
{
	FILE   *fp;
	char    fname[256];
	int     linenum, ignore = 0;
	struct stat st;

	numgames = 0;

	if ((fp = fopen (mkfname (GAMEINDEXFILE), "r")) == NULL) {
		error_fatalsys ("Unable to open %s for reading.",
				mkfname (GAMEINDEXFILE));
	}

	linenum = 0;
	while (!feof (fp)) {
		char    line[8192], *cp;

		if (!fgets (line, sizeof (line), fp))
			break;
		linenum++;
		if ((cp = strchr (line, '#')) != NULL)
			*cp = 0;	/* Comments */

		if (line[0] == ':') {
			int     n;
			char    d[8192], f[1024];

			if (sscanf (&line[1], "%s %n", fname, &n) != 1) {
				error_fatal
				    ("line %d in %s starts with : but has bad format!",
				     linenum, mkfname (GAMEINDEXFILE));
			}
			strcpy (d, stripspace (&line[n]));


			/* Check for the existence of the file. */


			sprintf (f, "%s/%s", mkfname (GAMEDIR), fname);
			if (stat (f, &st)) {
				strcat (fname, ".gz");
				sprintf (f, "%s/%s", mkfname (GAMEDIR), fname);
				if (stat (f, &st)) {
					ignore = 1;
					continue;
				} else
					ignore = 0;
			}


			/* See if we need to save the old entry */

			if (numgames == 0) {
				games = alcmem (sizeof (struct game_t));
				numgames++;
			} else {
				struct game_t *tmp =
				    alcmem ((++numgames) *
					    sizeof (struct game_t));
				memcpy (tmp, games,
					(numgames -
					 1) * sizeof (struct game_t));
				games = tmp;
			}

			games[numgames - 1].fname = strdup (fname);
			games[numgames - 1].title = strdup (d);

			games[numgames - 1].libtitle =
			    games[numgames - 1].title;
			if (sameto ("A ", d))
				games[numgames - 1].libtitle =
				    &games[numgames - 1].title[2];
			if (sameto ("An ", d))
				games[numgames - 1].libtitle =
				    &games[numgames - 1].title[3];
			if (sameto ("The ", d))
				games[numgames - 1].libtitle =
				    &games[numgames - 1].title[4];
			games[numgames - 1].libtitle =
			    strdup (games[numgames - 1].libtitle);
		} else if (numgames > 0 && !ignore) {
			char   *tmp, *cp;

			cp = stripspace (line);
			tmp =
			    alcmem (strlen (games[numgames - 1].title) +
				    strlen (cp) + 2);
			sprintf (tmp, "%s %s", games[numgames - 1].title, cp);
			free (games[numgames - 1].title);
			games[numgames - 1].title = tmp;
			lowerc (games[numgames - 1].libtitle);
		}
	}
	fclose (fp);

	qsort (games, numgames, sizeof (struct game_t), gamecmp);
}


void
init ()
{
	mod_init (INI_ALL);
	gatherlist ();

	msg = msg_open ("adventure");
	entrykey = msg_int (ENTRYKEY, 0, 129);
	topkey = msg_int (TOPKEY, 0, 129);
	playkey = msg_int (PLAYKEY, 0, 129);
	msg_setlanguage (thisuseracc.language);
	savedgame = msg_string (SAVEDGAME);
}


void
about ()
{
	prompt (ABOUT);
}


void
howto ()
{
	prompt (HOWTO);
}


void
download_saved_games ()
{
	char    spec[256];

	sprintf (spec, TMPDIR "/adv-%s/*", thisuseracc.userid);
	if (xfer_addwild (FXM_TRANSIENT, spec, savedgame, 0, -1)) {
		prompt (DLNOW);
		xfer_run ();
		xfer_kill_list ();
	}
}


int
play (char *gamename)
{
	char    fname[256], s[256];
	char    tmpdir[256];
	char   *cp;
	struct dirent *buf;
	DIR    *dp;
	int     i;
	int     t0, t1;

	/* Make the temp directory and clean it up if needs be */

	sprintf (tmpdir, TMPDIR "/adv-%s", thisuseracc.userid);
	mkdir (tmpdir, 0750);

	if ((dp = opendir (tmpdir)) == NULL)
		error_fatalsys ("Unable to open directory %s", tmpdir);

	while ((buf = readdir (dp)) != NULL) {
		sprintf (fname, "%s/%s", tmpdir, buf->d_name);
		if ((strcmp (buf->d_name, ".") == 0) ||
		    (strcmp (buf->d_name, "..") == 0))
			continue;
		if (unlink (fname) < 0)
			error_fatalsys ("Unable to unlink(\"%s\")", fname);
	}
	closedir (dp);


	/* Copy the game file there */

	sprintf (fname, "%s/%s", mkfname (GAMEDIR), gamename);
	sprintf (s, "%s/%s", tmpdir, gamename);
	if (fcopy (fname, s)) {
		error_fatal ("Unable to fcopy() %s -> %s", fname, s);
	}


	/* Uncompress the file, if needed */

	cp = strstr (s, ".gz");
	if (cp == s + strlen (s) - 3) {
		char    command[512];

		sprintf (command, "gunzip %s", s);
		if ((i = system (command)) != 0) {
			error_fatal ("Unable to system(\"%s\") (exit code %d)",
				     command, i);
		}
		*cp = 0;	/* Remove the ".gz" suffix */
	}


	/* Finally, run the game */

	prompt (PLAYWARN);
	out_clearflags (OFL_WAITTOCLEAR);
	print ("\e[2J");
	mod_done (INI_INPUT);
	t0 = time (NULL);

	switch (fork ()) {
	case 0:
		chdir (tmpdir);
		execl (mkfname (BINDIR "/infoint"), "infoint", s);
		error_fatalsys ("Unable to execl()");	/* Whoops, this doesn't look good. */
		break;

	case -1:
		error_fatalsys ("Unable to fork()");	/* This never returns... */
		break;		/* ...but even paranoids have enemies. */

	default:
		wait (&i);	/* Wait for the interpreter to finish */
		break;
	}


	/* Only the parent process gets back here. */

	t1 = time (NULL);
	unlink (s);
	mod_regpid (thisuseronl.channel);
	mod_init (INI_INPUT | INI_SIGNALS);
	inp_resetidle ();
	thisuseronl.flags &= ~(OLF_BUSY | OLF_NOTIMEOUT | OLF_INHIBITGO |
			       OLF_INSYSCHAT | OLF_MMCONCAT);
	cnc_end ();
	inp_buffer[0] = 0;
	out_setflags (OFL_AFTERINPUT);
	print ("\e[2J");
	out_setflags (OFL_WAITTOCLEAR);

	download_saved_games ();

	return t1 - t0;
}


void
listgames ()
{
	int     i;

	prompt (LISTHDR);
	for (i = 0; i < numgames; i++) {
		prompt (LISTGAM, i + 1, games[i].title);
		if (fmt_lastresult == PAUSE_QUIT)
			break;
	}
	if (fmt_lastresult != PAUSE_QUIT)
		prompt (LISTFTR);
}


void
updatetop (int s, int n)
{
	FILE   *fp, *out;
	char    fname[256], lock[256];
	int     written = 0;

	/* Lock this operation first */

	sprintf (lock, "LCK..adventtop");
	if (lock_wait (lock, 2) == LKR_TIMEOUT)
		return;
	lock_place (lock, "writing");


	/* Copy over the rest of the file, change the one entry we're interested in. */

	fp = fopen (mkfname (TOPFILE), "r");

	sprintf (fname, "%s~", mkfname (TOPFILE));
	if ((out = fopen (fname, "w")) == NULL) {
		lock_rm (lock);
		error_fatalsys ("Unable to create %s", fname);
	}

	if (fp != NULL)
		while (!feof (fp)) {
			char    game[256];
			int     secs;
			int     times;

			if (fscanf (fp, "%s %d %d", game, &secs, &times) != 3)
				continue;

			if (!strcmp (game, games[n].fname)) {
				times++;
				secs += s;
				written = 1;
			}
			fprintf (out, "%s %d %d\n", game, secs, times);
		}

	if (!written)
		fprintf (out, "%s %d %d\n", games[n].fname, s, 1);

	if (fp != NULL)
		fclose (fp);
	fclose (out);

	if (rename (fname, mkfname (TOPFILE))) {
		lock_rm (lock);
		error_fatalsys ("Unable to rename %s to %s", fname,
				mkfname (TOPFILE));
	}

	lock_rm (lock);
}


void
choose_and_run ()
{
	int     n, i, t;

	for (;;) {
		inp_setflags (INF_HELP);
		i = get_number (&n, CHOOSE, 0, numgames, CHOOSERR, 0, 0);
		inp_clearflags (INF_HELP);
		if (i == 0)
			return;
		else if (i < 0)
			listgames ();
		if (i > 0)
			break;
	}

	if (n == 0) {
		int     r;

		srand (time (NULL));
		r = rand () % numgames;
		prompt (RANDOM, r + 1, games[r].title);
		t = play (games[r].fname);
		updatetop (t, r);
	} else {
		t = play (games[n - 1].fname);
		updatetop (t, n - 1);
	}
}



void
top10 ()
{
	FILE   *fp;
	char    lock[256];
	int     i;
	struct {
		char    fname[256];
		int     games;
		int     secs;
	} top[10], g;
	int     numtop = 0;


	/* Lock this operation first */

	sprintf (lock, "LCK..adventtop");
	if (lock_wait (lock, 5) == LKR_TIMEOUT)
		error_fatal ("Whoa, timeout expired while waiting for lock %s",
			     lock);
	lock_place (lock, "reading");


	/* Read the accounting file, gather what information we need. */

	if ((fp = fopen (mkfname (TOPFILE), "r")) == NULL) {
		prompt (NOTOP);
		lock_rm (lock);
		return;
	}

	if (fp != NULL)
		while (!feof (fp)) {
			bzero (&g, sizeof (g));
			if (fscanf (fp, "%s %d %d", g.fname, &g.secs, &g.games)
			    != 3)
				continue;

			if (numtop > 0 && top[numtop].secs >= g.secs)
				continue;

			if (numtop == 0) {
				memcpy (&top[0], &g, sizeof (g));
				numtop++;
			} else {
				for (i = numtop - 1; i >= 0; i--) {
					if (top[i].secs >= g.secs)
						break;
				}
				i++;
				if (i < 9)
					memmove (&top[i + 1], &top[i],
						 sizeof (g) * (9 - i));
				memcpy (&top[i], &g, sizeof (g));
				numtop++;
			}
		}
	fclose (fp);
	lock_rm (lock);


	/* Print the top N */

	prompt (TOPHDR, numtop);
	for (i = 0; i < numtop; i++) {

		/* Inefficient as hell... :-( */

		int     j;

		for (j = 0; j < numgames; j++) {
			if (!strcmp (games[j].fname, top[i].fname)) {
				prompt (TOPLIN,
					i + 1,
					top[i].secs / 3600,
					(top[i].secs % 3600) / 60,
					top[i].games, games[j].title);
			}
			if (fmt_lastresult == PAUSE_QUIT)
				return;
		}
	}

	prompt (TOPFTR);
}



void
run ()
{
	int     shownmenu = 0;
	char    c;

	if (!key_owns (&thisuseracc, entrykey)) {
		prompt (NOENTRY);
		return;
	}

	for (;;) {
		thisuseronl.flags &= ~OLF_BUSY;
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownmenu) {
				prompt (MENU, numgames);
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
					prompt (SHMENU, numgames);
				} else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			switch (c) {
			case 'A':
				about ();
				break;
			case 'H':
				howto ();
				break;
			case 'P':
				choose_and_run ();
				shownmenu = 0;
				break;
			case 'T':
				top10 ();
				break;
			case 'X':
				prompt (LEAVE);
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
	msg_close (msg);
}



int
handler_run (int argc, char **argv)
{
	atexit (done);
	init ();
	run ();
	done ();
	return 0;
}


mod_info_t mod_info_adventure = {
	"adventure",
	"Adventure game",
	"Alexios Chouchoulas <alexios@bedroomlan.org>",
	"BBS-oriented interpreter for Infocom adventure games.",
	RCS_VER,
	"1.0",
	{0, NULL}
	,			/* Login handler */
	{0, handler_run}
	,			/* Interactive handler */
	{0, NULL}
	,			/* Install logout handler */
	{0, NULL}
	,			/* Hangup handler */
	{0, NULL}
	,			/* Cleanup handler */
	{0, NULL}		/* Delete user handler */
};


int
main (int argc, char *argv[])
{
	mod_setinfo (&mod_info_adventure);
	return mod_main (argc, argv);
}


/* End of File */
