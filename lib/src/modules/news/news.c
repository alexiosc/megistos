/*****************************************************************************\
 **                                                                         **
 **  FILE:     news.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 95, Version 1.0                                      **
 **            B, August 96, Version 1.0                                    **
 **  PURPOSE:  Display latest news at login and/or inside BBS               **
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
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.8  2000/01/06 11:41:35  alexios
 * Made main() return a value.
 *
 * Revision 1.7  1999/07/18 21:47:26  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.6  1998/12/27 16:06:39  alexios
 * Added autoconf support.
 *
 * Revision 1.5  1998/08/11 10:18:49  alexios
 * Fixed [E]dit command bugs. Migrated file transfers to the
 * new format.
 *
 * Revision 1.4  1998/07/24 10:22:52  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.3  1997/11/06 20:13:48  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.2  1997/11/06 16:58:09  alexios
 * Changed calls to setaudit() so they use the new auditing
 * scheme.
 *
 * Revision 1.1  1997/09/12 13:19:14  alexios
 * Fixed news bulletin listing (it used to be out of alignment
 * and looked ugly). Added default answer of 'N' to the ASKUPL
 * question. Also implemented the ability to EDIT the bulletin
 * rather than re-uploading it.
 *
 * Revision 1.0  1997/08/28 11:02:32  alexios
 * Initial revision
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
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/news.h>
#include <megistos/mbk_news.h>


promptblock_t *msg;

int     linkey;
int     entrykey;
int     sopkey;
int     defdur;
int     defshw;
int     defhdr;
char   *defcls;
int     defkey;
int     maxlen;
char   *upldesc;


void
init ()
{
	classrec_t *cls;

	mod_init (INI_ALL);
	msg = msg_open ("news");
	msg_setlanguage (thisuseracc.language);

	linkey = msg_int (LINKEY, 0, 129);
	entrykey = msg_int (ENTRYKEY, 0, 129);
	sopkey = msg_int (SOPKEY, 0, 129);
	defdur = msg_int (DEFDUR, 0, 3650);
	maxlen = msg_int (MAXLEN, 256, 262144);

	if ((defshw = msg_token (DEFSHW, "ALWAYS", "ONCE")) == 0) {
		error_fatal ("Option DEFSHW in news.msg has bad value");
	} else
		defshw--;

	if ((defhdr = msg_token (DEFHDR, "NONE", "DATE", "TIME", "BOTH")) == 0) {
		error_fatal ("Option DEFHDR in news.msg has bad value");
	} else
		defhdr--;

	defcls = msg_string (DEFCLS);

	if ((*defcls != '\0') &&
	    (cls = cls_find (defcls = msg_string (DEFCLS))) == NULL) {
		error_fatal ("User class \"%s\" does not exist!", defcls);
	}

	upldesc = msg_string (UPLDESC);
}


int
bltcmp (const void *a, const void *b)
{
	const struct newsbulletin *ba = a;
	const struct newsbulletin *bb = b;
	int     i;

	if ((i = bb->priority - ba->priority) != 0)
		return i;
	if ((i = bb->date - ba->date) != 0)
		return i;
	if ((i = bb->time - ba->time) != 0)
		return i;
	if ((i = bb->num - ba->num) != 0)
		return i;
	return 0;
}


void
shownews (int lin, int sop)
{
	DIR    *dp;
	FILE   *fp;
	char    fname[256];
	struct dirent *dirent;
	struct newsbulletin blt, *showlist = NULL, *tmp;
	int     numblt = 0, i, shownheader = 0;

	if ((dp = opendir (mkfname (NEWSDIR))) == NULL) {
		error_fatalsys ("Unable to opendir %s", mkfname (NEWSDIR));
	}

	while ((dirent = readdir (dp)) != NULL) {
		if (!sameto ("hdr-", dirent->d_name))
			continue;
		sprintf (fname, "%s/%s", mkfname (NEWSDIR), dirent->d_name);

		if ((fp = fopen (fname, "r")) == NULL)
			continue;
		if (fread (&blt, sizeof (blt), 1, fp) != 1) {
			fclose (fp);
			continue;
		}
		fclose (fp);

		if (!blt.enabled)
			continue;
		if (!key_owns (&thisuseracc, sopkey)) {
			if (!key_owns (&thisuseracc, blt.key))
				continue;
			if (blt.class[0] &&
			    !sameas (thisuseracc.curclss, blt.class))
				continue;
		}

		numblt++;
		tmp = alcmem (numblt * sizeof (blt));
		if (numblt)
			memcpy (tmp, showlist, (numblt - 1) * sizeof (blt));
		memcpy (&tmp[numblt - 1], &blt, sizeof (blt));
		if (showlist)
			free (showlist);
		showlist = tmp;
	}
	closedir (dp);

	qsort (showlist, numblt, sizeof (blt), bltcmp);

	if (!numblt) {
		if (!lin)
			prompt (NONEWS);
		free (showlist);
		return;
	}

	for (i = 0; i < numblt; i++) {
		if (sop) {
			if (!shownheader) {
				shownheader = 1;
				prompt (RDNEWS);
			}
			prompt (SHEADER, showlist[i].num,
				strdate (showlist[i].date),
				strtime (showlist[i].time, 1),
				showlist[i].priority, showlist[i].numdays,
				msg_getunit (VEDIT1A + showlist[i].info, 1),
				showlist[i].class, showlist[i].key);
		} else if (showlist[i].info) {
			char    hdr[256] = { 0 };

			switch (showlist[i].info) {
			case 1:
				sprintf (hdr, "%s",
					 strdate (showlist[i].date));
				break;
			case 2:
				sprintf (hdr, "%s",
					 strtime (showlist[i].time, 1));
				break;
			case 3:
				sprintf (hdr, "%s %s",
					 strdate (showlist[i].date),
					 strtime (showlist[i].time, 1));
				break;
			}
			if (thisuseracc.datelast <= showlist[i].date) {
				if (!shownheader) {
					shownheader = 1;
					prompt (RDNEWS);
				}
				prompt (HEADER, hdr, msg_getunit (NEWBLT, 1));
			} else {
				if (!shownheader) {
					shownheader = 1;
					prompt (RDNEWS);
				}
				prompt (HEADER, hdr, "");
			}
		} else if (thisuseracc.datelast <= showlist[i].date)
			prompt (NEWBLT);

		strcpy (fname, mkfname (NEWSFNAME, showlist[i].num));
		print ("\n");
		if (fmt_lastresult == PAUSE_QUIT)
			break;
		out_printfile (fname);
		prompt (BLTDIV);
		if (fmt_lastresult == PAUSE_QUIT)
			break;
	}
	free (showlist);
}


void
listblts ()
{
	DIR    *dp;
	FILE   *fp;
	char    fname[256];
	struct dirent *dirent;
	struct newsbulletin blt;


	if ((dp = opendir (mkfname (NEWSDIR))) == NULL) {
		error_fatalsys ("Unable to opendir %s", mkfname (NEWSDIR));
	}

	prompt (LSTHDR);

	while ((dirent = readdir (dp)) != NULL) {
		if (!sameto ("hdr-", dirent->d_name))
			continue;
		sprintf (fname, "%s/%s", mkfname (NEWSDIR), dirent->d_name);

		if ((fp = fopen (fname, "r")) == NULL)
			continue;
		if (fread (&blt, sizeof (blt), 1, fp) != 1) {
			fclose (fp);
			continue;
		}
		fclose (fp);
		if (fmt_lastresult == PAUSE_QUIT)
			break;
		prompt (LSTTAB, blt.num, strdate (blt.date),
			strtime (blt.time, 1), blt.priority, blt.numdays,
			blt.enabled ? ' ' : '*', blt.class, blt.key);
	}
	prompt (LSTFTR);
	closedir (dp);
}


int
askbltnum (int pr)
{
	int     i, r;
	struct stat st;
	char    fname[256];

	for (;;) {
		i = 0;
		inp_setflags (INF_HELP);
		r = get_number (&i, pr, 1, 32767, NUMERR, 0, 0);
		inp_clearflags (INF_HELP);
		if (!r)
			return 0;
		if (r == -1) {
			listblts ();
			continue;
		} else {
			strcpy (fname, mkfname (NEWSHDR, i));
			if (stat (fname, &st)) {
				prompt (NUMERR, i);
				continue;
			}
			strcpy (fname, mkfname (NEWSFNAME, i));
			if (stat (fname, &st)) {
				prompt (NUMERR, i);
				continue;
			}
			return i;
		}
	}
}


int
getbltnum ()
{
	int     i;
	struct stat st;

	char    fname[256];

	for (i = 1;; i++) {
		strcpy (fname, mkfname (NEWSFNAME, i));
		if (!stat (fname, &st))
			continue;
		strcpy (fname, mkfname (NEWSHDR, i));
		if (!stat (fname, &st))
			continue;
		return i;
	}
}


void
upload (char *uploadname)
{
	char    fname[256], command[256], *cp, name[256], dir[256];
	FILE   *fp;
	int     count = -1;

	name[0] = dir[0] = 0;
	xfer_setaudit (0, NULL, NULL, 0, NULL, NULL);
	xfer_add (FXM_UPLOAD, uploadname, upldesc, 0, 0);
	xfer_run ();

	sprintf (fname, XFERLIST, getpid ());

	if ((fp = fopen (fname, "r")) == NULL)
		goto kill;

	while (!feof (fp)) {
		char    line[1024];

		if (fgets (line, sizeof (line), fp)) {
			count++;
			if (!count)
				strcpy (dir, line);
			else if (count == 1)
				strcpy (name, line);
		}
	}

	if ((cp = strchr (dir, '\n')) != NULL)
		*cp = 0;
	if ((cp = strchr (name, '\n')) != NULL)
		*cp = 0;
	fclose (fp);

	if (count < 1)
		goto kill;
	else if (count > 1)
		prompt (FTOOMANY);

	{
		char    command[256];

		sprintf (command, "cp %s %s", name, uploadname);
		system (command);
	}

      kill:
	sprintf (command, "rm -rf %s %s", fname, dir);
	system (command);
	if (name[0]) {
		sprintf (command, "rm -f %s >&/dev/null", name);
		system (command);
	}
	xfer_kill_list ();
}


void
insert (int num)
{
	char    fname[256], fname2[256];
	FILE   *fp;
	int     duration = defdur, enabled = 1, info = defhdr, key =
	    defkey, priority = 0;
	int     i, j, check;
	char    class[16], res[256], action;
	struct stat st;
	struct newsbulletin blt;

	if (num) {
		strcpy (fname, mkfname (NEWSHDR, num));
		if ((fp = fopen (fname, "r")) == NULL) {
			prompt (NUMERR, num);
			return;
		}
		fread (&blt, sizeof (blt), 1, fp);
		fclose (fp);

		duration = blt.numdays;
		enabled = blt.enabled;
		info = blt.info;
		key = blt.key;
		priority = blt.priority;
		strcpy (class, blt.class);
	} else {
		memset (&blt, 0, sizeof (blt));
	}

	sprintf (inp_buffer, "%d\n%s\n%s\n%s\n%d\n%d\nOK\nCANCEL\n",
		 duration,
		 enabled ? "on" : "",
		 msg_get (VEDIT1A + info), class, key, priority);

	if (dialog_run ("news", VEDIT, LEDIT, inp_buffer, MAXINPLEN) != 0) {
		error_log ("Unable to run data entry subsystem");
		return;
	}

	dialog_parse (inp_buffer);

	for (i = 0; i < 12; i++) {
		char   *s = margv[i];

		if (i == 0)
			sscanf (s, "%d", &duration);
		else if (i == 1)
			enabled = sameas (s, "ON");
		else if (i == 2) {
			for (j = 0; j < 3; j++)
				if (!strcmp (msg_get (VEDIT1A + j), s)) {
					info = j;
					break;
				}
		} else if (i == 3)
			strcpy (class, stripspace (s));
		else if (i == 4)
			sscanf (s, "%d", &key);
		else if (i == 5)
			sscanf (s, "%d", &priority);
		else if (i == 8)
			strcpy (res, s);
	}

	if (sameas (res, "CANCEL") || sameas (res, margv[7])) {
		prompt (CANCEL);
		return;
	}

	if (class[0] && cls_find (class) == 0)
		prompt (WARNCLS, class);

	if (!num) {
		blt.date = today ();
		blt.time = now ();
	}
	blt.numdays = duration;
	blt.priority = priority;
	blt.enabled = enabled;
	strcpy (blt.class, class);
	blt.key = key;
	blt.info = info;

	if (num) {
		if (!get_menu
		    (&action, 0, 0, ASKUPL, ASKERR, "YNE", ASKUPLD, 'N'))
			action = 'N';
		check = action != 'N';
	} else {
		check = 0;
		action = 'Y';
	}

	if (!num)
		blt.num = num = getbltnum ();

	strcpy (fname2, mkfname (NEWSFNAME, num));

	strcpy (fname, mkfname (NEWSHDR, num));
	if ((fp = fopen (fname, "w")) == NULL) {
		prompt (IOERR);
		unlink (fname2);
		unlink (fname);
		return;
	}
	fwrite (&blt, sizeof (blt), 1, fp);
	fclose (fp);

	switch (action) {
	case 'N':
		break;
	case 'Y':
		strcpy (fname, mkfname (NEWSFNAME, num));
		upload (fname);

		strcpy (fname, mkfname (NEWSFNAME, num));
		if (!stat (fname, &st)) {
			prompt (BLTOK, num);
			return;
		} else {
			strcpy (fname, mkfname (NEWSHDR, num));
			if (check)
				prompt (IOERR);
			unlink (fname);
		}
		break;
	case 'E':
		strcpy (fname, mkfname (NEWSFNAME, num));
		sprintf (fname2, TMPDIR "/filedes%08lx", time (0));
		unlink (fname2);
		fcopy (fname, fname2);
		editor (fname2, maxlen);
		if (stat (fname2, &st)) {
			prompt (TXTCAN);
			cnc_end ();
		} else {
			fcopy (fname2, fname);
			unlink (fname2);
			prompt (BLTOK, num);
		}
	}
}


void
edit ()
{
	int     num = askbltnum (ASKEDT);

	if (num)
		insert (num);
}



void
delete ()
{
	int     num = askbltnum (DELBLT);

	if (num) {
		char    fname[256];

		strcpy (fname, mkfname (NEWSFNAME, num));
		unlink (fname);
		strcpy (fname, mkfname (NEWSHDR, num));
		unlink (fname);
		prompt (DELOK);
	}
}



void
cleanup ()
{
	DIR    *dp;
	FILE   *fp;
	char    fname[256];
	struct dirent *dirent;
	struct newsbulletin blt;
	int     dayssince = 1, cof = cofdate (today ());

	printf ("News cleanup\n\n");

	sprintf (fname, "%s/.LAST.CLEANUP", mkfname (NEWSDIR));
	if ((fp = fopen (fname, "r")) != NULL) {
		int     i;

		if (fscanf (fp, "%d\n", &i) == 1) {
			dayssince = cof - i;
			if (dayssince < 0)
				dayssince = 1;
		}
		fclose (fp);
	}
	if ((fp = fopen (fname, "w")) != NULL) {
		fprintf (fp, "%d\n", cof);
		fclose (fp);
	}
	chmod (fname, 0660);
	printf ("Days since last cleanup: %d\n\n", dayssince);


	if ((dp = opendir (mkfname (NEWSDIR))) == NULL) {
		error_fatalsys ("Unable to opendir %s", mkfname (NEWSDIR));
	}

	while ((dirent = readdir (dp)) != NULL) {
		if (!sameto ("hdr-", dirent->d_name))
			continue;
		sprintf (fname, "%s/%s", mkfname (NEWSDIR), dirent->d_name);

		if ((fp = fopen (fname, "r")) == NULL)
			continue;
		if (fread (&blt, sizeof (blt), 1, fp) != 1) {
			fclose (fp);
			continue;
		}
		fclose (fp);

		if (!blt.numdays)
			continue;
		blt.numdays -= dayssince;
		if (blt.numdays <= 0) {
			blt.numdays = 0;
			blt.enabled = 0;
		}

		if ((fp = fopen (fname, "w")) == NULL)
			continue;
		if (fwrite (&blt, sizeof (blt), 1, fp) != 1) {
			fclose (fp);
			continue;
		}
		fclose (fp);
	}
	closedir (dp);
	printf ("News cleanup done.\n\n");
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

	if (!key_owns (&thisuseracc, sopkey)) {
		shownews (0, 0);
		return;
	}

	for (;;) {
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
				if (shownmenu == 1)
					prompt (SHMENU);
				else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			switch (c) {
			case 'R':
				shownews (0, key_owns (&thisuseracc, sopkey));
				break;
			case 'I':
				insert (0);
				break;
			case 'L':
				listblts ();
				break;
			case 'E':
				edit ();
				break;
			case 'D':
				delete ();
				break;
			case 'X':
				prompt (LEAVE, NULL);
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
login ()
{
	print ("\n");
	shownews (1, 0);
}


void
done ()
{
	msg_close (msg);
	exit (0);
}


int
handler_cleanup (int argc, char **argv)
{
	cleanup ();
	return 0;
}


int
handler_login (int argc, char **argv)
{
	init ();
	login ();
	done ();
	return 0;
}


int
handler_run (int argc, char *argv[])
{
	init ();
	run ();
	done ();
	return 9;
}


mod_info_t mod_info_news = {
	"news",
	"BBS news bulletins",
	"Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
	"Shows bulletins to users immediately after login.",
	RCS_VER,
	"1.0",
	{10, handler_login}
	,			/* Login handler */
	{0, handler_run}
	,			/* Interactive handler */
	{0, NULL}
	,			/* Install logout handler */
	{0, NULL}
	,			/* Hangup handler */
	{50, handler_cleanup}
	,			/* Cleanup handler */
	{0, NULL}		/* Delete user handler */
};


int
main (int argc, char *argv[])
{
	mod_setinfo (&mod_info_news);
	return mod_main (argc, argv);
}


/* End of File */
