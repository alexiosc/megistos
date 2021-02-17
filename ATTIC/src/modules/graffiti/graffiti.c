/*****************************************************************************\
 **                                                                         **
 **  FILE:     graffiti.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 1.0                                    **
 **  PURPOSE:  Graffiti Wall                                                **
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
 * $Id: graffiti.c,v 2.1 2004/09/13 19:55:34 alexios Exp $
 *
 * $Log: graffiti.c,v $
 * Revision 2.1  2004/09/13 19:55:34  alexios
 * Changed email addresses.
 *
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.6  1999/07/18 21:42:37  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.5  1998/12/27 15:44:51  alexios
 * Added autoconf support. Migrated to new locking functions.
 *
 * Revision 1.4  1998/08/14 11:30:53  alexios
 * Minor bug fixes.
 *
 * Revision 1.3  1998/08/11 10:10:18  alexios
 * Removed umask() call.
 *
 * Revision 1.2  1998/07/24 10:19:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:11:34  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 10:42:25  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id: graffiti.c,v 2.1 2004/09/13 19:55:34 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_STRING_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_graffiti.h"
#include "graffiti.h"

promptblock_t *msg;


int     entrykey;
int     maxlen;
int     maxsize;
int     maxmsgs;
int     ovrkey;
int     syskey;
int     wrtkey;


static char *
zonk (char *s)
{
	int     i;

	for (i = strlen (s) - 1; i > 0; i--)
		if (s[i] == 32)
			s[i] = 0;
		else
			break;
	return s;
}


void
init ()
{
	mod_init (INI_ALL);
	msg = msg_open ("graffiti");
	msg_setlanguage (thisuseracc.language);

	entrykey = msg_int (ENTRYKEY, 0, 129);
	maxlen = msg_int (MAXLEN, 1, 255);
	maxsize = msg_int (MAXSIZE, 1, 32767);
	maxmsgs = msg_int (MAXMSGS, 1, 100);
	ovrkey = msg_int (OVRKEY, 0, 129);
	syskey = msg_int (SYSKEY, 0, 129);
	wrtkey = msg_int (WRTKEY, 0, 129);

	randomize ();
}


int
checkfile ()
{
	struct stat buf;
	FILE   *fp;
	struct wallmsg header;

	if (stat (mkfname (WALLFILE), &buf)) {
		if ((lock_wait (WALLLOCK, 5)) == LKR_TIMEOUT) {
			error_log ("Timed out waiting for lock %s", WALLLOCK);
			return 0;
		}
		lock_place (WALLLOCK, "creating");

		if ((fp = fopen (mkfname (WALLFILE), "w")) == NULL) {
			error_fatalsys ("Unable to create file %s",
					mkfname (WALLFILE));
		}
		memset (&header, 0, sizeof (header));
		strcpy (header.userid, SYSOP);
		sprintf (header.message, "%d", 0);
		fwrite (&header, sizeof (header), 1, fp);

		fclose (fp);
		chmod (mkfname (WALLFILE), 0666);
		lock_rm (WALLLOCK);
	}
	return 1;
}


void
drawmessage ()
{
	FILE   *fp, *out;
	char    fname[256];
	char    message[256] = { 0 };
	char    userid[24];
	int     numlines = 0, i;
	struct wallmsg wallmsg;

	if (!key_owns (&thisuseracc, wrtkey)) {
		prompt (WRTNAX);
		cnc_end ();
		return;
	} else if (!checkfile ()) {
		prompt (OOPS);
		return;
	} else {
		if ((lock_wait (WALLLOCK, 5)) == LKR_TIMEOUT) {
			error_log ("Timed out waiting for lock %s", WALLLOCK);
			return;
		}
		lock_place (WALLLOCK, "checking");

		if ((fp = fopen (mkfname (WALLFILE), "r")) == NULL) {
			lock_rm (WALLLOCK);
			error_fatalsys ("Unable to open file %s",
					mkfname (WALLFILE));
		}

		if (!fread (&wallmsg, sizeof (wallmsg), 1, fp)) {
			lock_rm (WALLLOCK);
			error_fatalsys ("Unable to read file %s",
					mkfname (WALLFILE));
		}

		numlines = atoi (wallmsg.message);
		strcpy (userid, wallmsg.userid);
		if (!key_owns (&thisuseracc, ovrkey)
		    && sameas (wallmsg.userid, thisuseracc.userid) &&
		    numlines >= maxmsgs) {
			prompt (MSGDENY);
			lock_rm (WALLLOCK);
			return;
		}
	}
	fclose (fp);
	lock_rm (WALLLOCK);

	for (;;) {
		if (!cnc_more ()) {
			prompt (NEWMSG);
			bzero (inp_buffer, MAXINPLEN + 1);
			inp_get (maxlen);
			cnc_begin ();
		}
		inp_raw ();
		strcpy (message, cnc_all ());

		if (inp_reprompt ()) {
			cnc_end ();
			continue;
		} else if (!message[0] || inp_isX (message))
			return;
		else
			break;
	}

	prompt (WALLSAV);

	lock_place (WALLLOCK, "writing");
	if ((fp = fopen (mkfname (WALLFILE), "r")) == NULL) {
		int     i = errno;

		lock_rm (WALLLOCK);
		errno = i;
		error_fatalsys ("Unable to open file %s", mkfname (WALLFILE));
	}

	fread (&wallmsg, sizeof (wallmsg), 1, fp);

	sprintf (fname, TMPDIR "/graffiti%05d", getpid ());
	if ((out = fopen (fname, "w")) == NULL) {
		int     i = errno;

		lock_rm (WALLLOCK);
		errno = i;
		error_fatalsys ("Unable to create temporary file %s", fname);
	}
	if (sameas (thisuseracc.userid, userid))
		numlines++;
	else
		numlines = 1;

	memset (&wallmsg, 0, sizeof (wallmsg));
	strcpy (wallmsg.userid, thisuseracc.userid);
	sprintf (wallmsg.message, "%d", numlines);
	fwrite (&wallmsg, sizeof (wallmsg), 1, out);

	strcpy (wallmsg.message, message);
	fwrite (&wallmsg, sizeof (wallmsg), 1, out);

	for (i = 0; (i < (maxsize - 1)) && (!feof (fp));) {
		if (fread (&wallmsg, sizeof (wallmsg), 1, fp) &&
		    wallmsg.userid[0]) {
			i++;
			fwrite (&wallmsg, sizeof (wallmsg), 1, out);
		}
	}
	fclose (out);
	fclose (fp);

	if (fcopy (fname, mkfname (WALLFILE))) {
		prompt (OOPS);
		lock_rm (WALLLOCK);
		return;
	}
	unlink (fname);
	lock_rm (WALLLOCK);
	prompt (WALLDON);
}


void
readwall ()
{
	FILE   *fp;
	struct wallmsg wallmsg;
	struct stat buf;

	if (stat (mkfname (WALLFILE), &buf)) {
		prompt (EMPTY);
		return;
	}

	prompt (WALLHEAD);

	if ((fp = fopen (mkfname (WALLFILE), "r")) == NULL) {
		error_fatalsys ("Unable to open %s for reading.",
				mkfname (WALLFILE));
	}

	fread (&wallmsg, sizeof (wallmsg), 1, fp);
	while (!feof (fp)) {
		if (!fread (&wallmsg, sizeof (wallmsg), 1, fp))
			continue;
		if (wallmsg.userid[0]) {
			print ("%s%s\n", colors[rnd (MAXCOLOR)],
			       zonk (wallmsg.message));
			if (fmt_lastresult == PAUSE_QUIT) {
				fclose (fp);
				prompt (ABORT);
				return;
			}
		}
	}
	fclose (fp);
	prompt (WALLEND);
}


void
listwall ()
{
	FILE   *fp;
	int     i = 0;
	struct wallmsg wallmsg;
	struct stat buf;

	if (stat (mkfname (WALLFILE), &buf)) {
		prompt (EMPTY);
		return;
	}

	prompt (WALLHEAD);

	if ((fp = fopen (mkfname (WALLFILE), "r")) == NULL) {
		error_fatalsys ("Unable to open %s for reading.",
				mkfname (WALLFILE));
	}

	fread (&wallmsg, sizeof (wallmsg), 1, fp);
	while (!feof (fp)) {
		if (!fread (&wallmsg, sizeof (wallmsg), 1, fp))
			continue;
		i++;
		if (wallmsg.userid[0]) {
			print ("%3d %-10s %s\n", i, wallmsg.userid,
			       zonk (wallmsg.message));
			if (fmt_lastresult == PAUSE_QUIT) {
				fclose (fp);
				prompt (ABORT);
				return;
			}
		}
	}
	fclose (fp);
	prompt (WALLEND);
}


void
cleanwall ()
{
	FILE   *fp;
	struct wallmsg wallmsg;
	struct stat buf;
	int     linenum;

	if (stat (mkfname (WALLFILE), &buf) ||
	    (buf.st_size / sizeof (wallmsg)) < 2) {
		prompt (WALLEMPTY);
		return;
	}

	if ((fp = fopen (mkfname (WALLFILE), "r+")) == NULL) {
		error_fatalsys ("Unable to open %s for reading.",
				mkfname (WALLFILE));
	}

	for (;;) {
		if (!get_number
		    (&linenum, DELMSG, 1, buf.st_size / sizeof (wallmsg),
		     BADNUM, 0, 0)) {
			lock_rm (WALLLOCK);
			fclose (fp);
			return;
		}
		if (lock_wait (WALLLOCK, 5) == LKR_TIMEOUT) {
			prompt (TIMEOUT);
			fclose (fp);
			return;
		}
		lock_place (WALLLOCK, "cleaning");
		fstat (fileno (fp), &buf);
		if (linenum >= buf.st_size / sizeof (wallmsg)) {
			prompt (BADNUM);
			lock_rm (WALLLOCK);
		} else {
			if (fseek (fp, sizeof (wallmsg) * linenum, SEEK_SET)) {
				int     i = errno;

				lock_rm (WALLLOCK);
				errno = i;
				error_fatalsys ("Unable to seek %s",
						mkfname (WALLFILE));
			}
			if (!fread (&wallmsg, sizeof (wallmsg), 1, fp)) {
				int     i = errno;

				lock_rm (WALLLOCK);
				errno = i;
				error_fatalsys ("Unable to read %s",
						mkfname (WALLFILE));
			}
			if (!wallmsg.userid[0]) {
				lock_rm (WALLLOCK);
				prompt (BADNUM);
			} else {
				wallmsg.userid[0] = 0;
				if (fseek
				    (fp, sizeof (wallmsg) * linenum,
				     SEEK_SET)) {
					int     i = errno;

					lock_rm (WALLLOCK);
					errno = i;
					error_fatalsys ("Unable to seek %s",
							mkfname (WALLFILE));
				}
				if (!fwrite
				    (&wallmsg, sizeof (wallmsg), 1, fp)) {
					int     i = errno;

					lock_rm (WALLLOCK);
					errno = i;
					error_fatalsys ("Unable to write %s",
							mkfname (WALLFILE));
				}
				fclose (fp);
				lock_rm (WALLLOCK);
				prompt (WALLDEL);
				return;
			}
		}
	}
}


void
run ()
{
	int     shownintro = 0;
	int     shownmenu = 0;
	char    c = 0;

	if (!key_owns (&thisuseracc, entrykey)) {
		prompt (NOENTRY);
		return;
	}

	for (;;) {
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownintro) {
				prompt (HITHERE);
				shownintro = 1;
			}
			if (!shownmenu) {
				prompt (key_owns (&thisuseracc, syskey) ?
					SYSMENU : MENU);
				prompt (VSHMENU);
				shownmenu = 2;
			}
		} else
			shownintro = shownmenu = 1;
		if (thisuseronl.flags & OLF_MMCALLING && thisuseronl.input[0]) {
			thisuseronl.input[0] = 0;
		} else {
			if (!cnc_nxtcmd) {
				if (thisuseronl.flags & OLF_MMCONCAT) {
					thisuseronl.flags &= ~OLF_MMCONCAT;
					return;
				}
				if (shownmenu == 1) {
					prompt (key_owns (&thisuseracc, syskey)
						? SYSSHMENU : SHMENU);
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
				prompt (ABOUT);
				break;
			case 'D':
				drawmessage ();
				break;
			case 'R':
				readwall ();
				break;
			case 'L':
				if (key_owns (&thisuseracc, syskey))
					listwall ();
				else
					prompt (ERRSEL, c);
				break;
			case 'C':
				if (key_owns (&thisuseracc, syskey))
					cleanwall ();
				else
					prompt (ERRSEL, c);
				break;
			case 'X':
				prompt (LEAVE);
				return;
			case '?':
				shownmenu = 0;
				break;
			default:
				prompt (ERRSEL, c);
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
	exit (0);
}


int
handler_run (int argc, char **argv)
{
	init ();
	run ();
	done ();
	return 0;
}


mod_info_t mod_info_graffiti = {
	"graffiti",
	"The Graffiti Wall",
	"Alexios Chouchoulas <alexios@bedroomlan.org>",
	"Hosts (semi-)anonymous, multi-coloured one-liners written by users.",
	RCS_VER,
	"1.0",
	{0, NULL},		/* Login handler */
	{0, handler_run},	/* Interactive handler */
	{0, NULL},		/* Install logout handler */
	{0, NULL},		/* Hangup handler */
	{0, NULL},		/* Cleanup handler */
	{0, NULL}		/* Delete user handler */
};


int
main (int argc, char *argv[])
{
	mod_setinfo (&mod_info_graffiti);
	return mod_main (argc, argv);
}


/* End of File */
