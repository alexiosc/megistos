/*****************************************************************************\
 **                                                                         **
 **  FILE:     signup.c                                                     **
 **  AUTHORS:  Alexios, Loukas                                              **
 **  REVISION: C, March 95, Version 0.6                                     **
 **            D, July  96, Version 0.7                                     **
 **  PURPOSE:  Signup a new user, assign id and password, etc.              **
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
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.7  2004/05/21 20:08:56  alexios
 * Removed deprecated code stanza pertaining to a chown() operation on
 * the user's newly created account.
 *
 * Revision 1.6  2004/05/05 09:21:51  alexios
 * Signup no longer asks encoding, language and ANSI questions if they've
 * already been asked by something else (e.g. bbslogin). Bug fix that
 * tried to open the password generation dictionary without prepending
 * the BBS prefix, then performed no error checking if this
 * failed. Placed additional safeguards against this happening for other
 * reasons. Minor beautification changes.
 *
 * Revision 1.5  2003/12/23 06:38:04  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.4  2003/12/22 17:23:36  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.9  1999/08/13 17:07:21  alexios
 * Starting in this version of signup, the program refrains from
 * allocating new UNIX user accounts to new BBS users. This speeds
 * things up quite a lot.
 *
 * Revision 0.8  1999/07/18 22:07:16  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.7  1998/12/27 16:29:59  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Other useradd fixes.
 *
 * Revision 0.6  1998/07/24 10:29:10  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.5  1997/11/06 20:05:01  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 11:09:36  alexios
 * Changed getconversion() to askxlation(). Made it simillar to
 * the same function in bbslogin, so that it asks for one of the
 * generalised customisable translation tables instead of the
 * hardwired ones.
 *
 * Revision 0.3  1997/09/12 13:33:49  alexios
 * Added code to reflect passowrd policy changes, as seen in the
 * Account module. Password lengths are now configurable and the
 * system may be asked to not be too strict with new passwords
 * (i.e. they MAY consist solely of alpha characters).
 *
 * Revision 0.2  1997/08/30 13:15:02  alexios
 * Signup now cooperates with the new bbsd. Fixed a slight bug
 * that caused a SIGSEGV (and a user hangup) if Enter was
 * pressed during language selection.
 *
 * Revision 0.1  1997/08/28 11:20:03  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] = "$Id$";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_PWD_H 1
#define WANT_SIGNAL_H 1
#define WANT_GRP_H 1
#define WANT_PWD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_SHM_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <mbk/mbk_signup.h>
#include <mbk/mbk_login.h>
#include <mbk/mbk_sysvar.h>

#define __ACCOUNT_UNAMBIGUOUS__
#include <mbk/mbk_account.h>


promptblock_t *msg, *loginmsg;
useracc_t uacc;
int     asklang = 1, askansi = 1, askxlt = 1, xlation = 1;
char    tty[32];

char   *unixuid;
char   *newclss;
int     intpauz;
int     welpauz;
int     sgnaud;
int     safpsw;
int     strpss;
int     minpln;
int     mkpswd;
int     mkpwdf;
int     askscr;
int     askcom;
int     askadr;
int     askpho;
int     asksys;
int     askage;
int     asksex;
int     prfvis;
int     mxuidl;
int     alwnum;
int     alwsym;

void
init ()
{
	void    registerbbsd (), trap ();

	strcpy (tty, getenv ("CHANNEL"));
	mod_regpid (tty);
	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGSTOP, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);
	signal (SIGTERM, trap);
	signal (SIGKILL, trap);
	signal (SIGSEGV, trap);
	signal (SIGFPE, trap);
	signal (SIGHUP, trap);
	signal (SIGILL, trap);

	mod_init (INI_INPUT | INI_SYSVARS | INI_CLASSES | INI_ERRMSGS |
		  INI_ATEXIT | INI_LANGS | INI_OUTPUT | INI_CHAT | INI_TTYNUM);
	memset (&uacc, 0, sizeof (useracc_t));
	out_setflags (OFL_WAITTOCLEAR);
	loginmsg = msg_open ("login");
	unixuid = msg_string (UNIXUID);

	msg = msg_open ("account");
	safpsw = msg_bool (ACCOUNT_SAFPSW);
	strpss = msg_bool (ACCOUNT_STRPSS);
	minpln = msg_int (ACCOUNT_MINPLN, 3, 15);
	mkpswd = msg_bool (ACCOUNT_MKPSWD);
	mkpwdf = msg_bool (ACCOUNT_MKPWDF);
	msg_close (msg);

	msg = msg_open ("signup");
	msg_set (msg);

	registerbbsd ();
	thisuseronl.idlezap = msg_int (SUPZAP, 0, 32767);
}


void
registerbbsd ()
{
	FILE   *fp;
	char    fname[256];
	struct shmuserrec buf;
	struct stat s;
	int     i;

	sprintf (fname, "%s/[SIGNUP-%s]", mkfname (ONLINEDIR),
		 getenv ("CHANNEL"));
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Unable to create file %s", fname);
	}
	memset (&buf, 0, sizeof (buf));
	if (fwrite (&buf, sizeof (buf), 1, fp) != 1) {
		error_fatalsys ("Unable to write file %s", fname);
	}
	fclose (fp);

	/* Notify BBSD of the new online record */

	if ((fp = fopen (mkfname (BBSDPIPEFILE), "w")) == NULL)
		return;
	fprintf (fp, "connect %s [SIGNUP-%s]\n", getenv ("CHANNEL"),
		 getenv ("CHANNEL"));
	fclose (fp);

	sprintf (fname, "%s/.shmid-[SIGNUP-%s]", mkfname (ONLINEDIR),
		 getenv ("CHANNEL"));
	for (i = 0; i < 20; i++) {
		usleep (100000);
		if (!stat (fname, &s)) {
			int     shmid;

			if ((fp = fopen (fname, "r")) == NULL) {
				error_fatalsys ("Unable to open file %s",
						fname);
			}
			if (!fscanf (fp, "%d", &shmid)) {
				error_fatalsys ("Unable to read file %s",
						fname);
			}
			fclose (fp);

			if ((thisshm =
			     (struct shmuserrec *) shmat (shmid, NULL,
							  0)) == NULL) {
				error_fatalsys ("Unable to shmat() to %s.",
						fname);
			}

			return;
		}
	}
	sprintf (fname, "%s/[SIGNUP-%s]", mkfname (ONLINEDIR),
		 getenv ("CHANNEL"));
	unlink (fname);
	error_fatal ("Timed out waiting for bbsd registration");
}


void
trap ()
{
	char    fname[256];

	sprintf (fname, "%s/[SIGNUP-%s]", mkfname (ONLINEDIR),
		 getenv ("CHANNEL"));
	unlink (fname);
	channel_hangup ();
	exit (1);
}


char   *
maxuidlen ()
{
	static char s[10];

	sprintf (s, "%d", mxuidl);
	return s;
}


void
readdefaults ()
{
	newclss = msg_string (NEWCLSS);
	intpauz = msg_int (INTPAUZ, 0, 1000);
	welpauz = msg_int (WELPAUZ, 0, 1000);
	sgnaud = msg_bool (SGNAUD);
	askscr = msg_bool (ASKSCR);
	askcom = msg_bool (ASKCOM);
	askadr = msg_bool (ASKADR);
	askpho = msg_bool (ASKPHO);
	asksys = msg_bool (ASKSYS);
	askage = msg_bool (ASKAGE);
	asksex = msg_bool (ASKSEX);
	prfvis = msg_bool (PRFVIS);
	mxuidl = msg_int (MXUIDL, 3, 16);
	alwnum = msg_bool (ALWNUM);
	alwsym = msg_bool (ALWSYM);

	out_addsubstvar ("@MAXUIDLEN@", maxuidlen);

#if 0
	if ((newgidn = atoi (newgid)) == 0) {
		FILE   *fp = fopen ("/etc/group", "r");
		struct group *g;

		if (fp == NULL)
			error_fatalsys ("Unable to open /etc/group!");
		while ((g = fgetgrent (fp)) != 0) {
			if (!strcmp (g->gr_name, newgid)) {
				newgidn = g->gr_gid;
				break;
			}
		}
		fclose (fp);
		if (g == NULL)
			error_fatal ("Group '%s' not found in /etc/group!",
				     newgid);
	}
	if (!newgidn)
		error_fatal ("Will NOT add BBS users to the root group (0).");
#endif

}


void
evilpause (int secs)
{
	int     i;

	if (!secs)
		return;
	prompt (PAUSE1, secs);
	for (i = 0; i < secs; i++) {
		prompt (PAUSE2, (secs - i));
		sleep (1);
	}
	prompt (PAUSE3);
}


void
askxlation ()
{
	struct stat st;
	char    fname[256];
	int     xltmap[10];
	int     i, xlation = 0;
	int     def = -1;

	if (chan_getnum (getenv ("CHANNEL")) < 0) {
		error_fatal ("%s has not been registered in %s",
			     getenv ("CHANNEL"), mkfname (CHANDEFFILE));
	}


	/* Has this been asked before? */

	if (!askxlt) {
		char * env_xlation = getenv("XLATION");
		if (env_xlation != NULL) {
			xlation = atoi (env_xlation);
			goto skipxlationquestion;
		}
	}


	/* Check the available translation tables and make the first one the
	   default */

	for (i = 0; i < NUMXLATIONS; i++) {
		strcpy (fname, mkfname (XLATIONDIR "/" XLATIONSRC, i));
		xltmap[i] = (stat (fname, &st) == 0);
		if (xltmap[i] && def < 0)
			def = i;
	}

	/* Check if this channel has a default translation table. */

	if (chan_last->xlation)
		def = chan_last->xlation;

	msg_set (loginmsg);
	for (;;) {
		prompt (XLATEM, def);
		inp_get (1);
		if (strlen (inp_buffer) == 1 && isdigit (*inp_buffer))
			xlation = atoi (inp_buffer);
		else if (!strlen (inp_buffer))
			xlation = def;
		if (!xltmap[xlation])
			prompt (XLATEE);
		else
			break;
	}

 skipxlationquestion:

	out_setxlation (xlation);
	usr_setpxlation (uacc, xlation);
}


void
getlanguage ()
{
	int     i = 0, choice = 0, ok = 0, showmenu = 1, quiet = 0;

	/* Has this been asked before? */

	if (!asklang) {
		char * env_lang = getenv("LANG");
		if (env_lang != NULL) {
			choice = atoi (env_lang);
			quiet = 1;
			goto skiplangquestion;
		}
	}

	msg_set (msg);
	if (msg_numlangs) {
		while (!ok) {
			if (showmenu) {
				showmenu = 0;
				prompt (LNGSEL1);
				for (i = 0; i < msg_numlangs; i++)
					prompt (LNGSEL2, i + 1,
						msg_langnames[i]);
			}
			prompt (LNGSEL3, 1, msg_numlangs);
			inp_get (1);
			if (margc && sameas (margv[0], "?")) {
				showmenu = 1;
				continue;
			} else if (!margc) {
				ok = 1;
				choice = 1;
			} else if (margc && isdigit (margv[0][0])) {
				choice = atoi (margv[0]);
				if (choice < 1 || choice > msg_numlangs) {
					prompt (LNGSLRR, 1, msg_numlangs);
					continue;
				} else
					ok = 1;
			}
		}
	} else
		choice = 1;

 skiplangquestion:

	uacc.language = choice;
	msg_setlanguage (choice);
	if (!quiet) prompt (LNGSLOK, msg_langnames [choice - 1]);
}


void
getansiop ()
{
	int     ansiflag;

	/* Has this been asked before? */

	if (!askansi) {
		char * env_ansi = getenv("ANSI");
		if (env_ansi != NULL) {
			ansiflag = atoi (env_ansi) != 0;
			goto skipansiquestion;
		}
	}
	
	msg_set (msg);
	prompt (B4QANS);
	while (!get_bool (&ansiflag, NEWANS, ANSBERR, 0, 0)) prompt (ANSBERR);

 skipansiquestion:
	if (ansiflag) {
		uacc.prefs |= UPF_ANSION;
		out_setflags (OFL_ANSIENABLE);
	} else
		out_clearflags (OFL_ANSIENABLE);
}


void
getusername ()
{
	char   *cp;

	for (;;) {
		prompt (GUSRNAM);
		inp_get (sizeof (uacc.username) - 1);
		if (margc < 2)
			continue;
		inp_raw ();
		if (strlen (inp_buffer) < 7)
			continue;
		break;
	}
	for (cp = inp_buffer; *cp && (*cp == 32); cp++);
	strcpy (uacc.username, cp);
}


void
getcompany ()
{
	char   *cp;

	if (!askcom)
		return;
	prompt (GUSRCOM);
	inp_get (sizeof (uacc.company) - 1);
	inp_raw ();
	for (cp = inp_buffer; *cp && (*cp == 32); cp++);
	strcpy (uacc.company, cp);
}


void
getaddress ()
{
	char   *cp;

	if (!askadr)
		return;
	for (;;) {
		prompt (GUSRAD1);
		inp_get (sizeof (uacc.address1) - 1);
		if (margc < 2)
			continue;
		inp_raw ();
		for (cp = inp_buffer; *cp && (*cp == 32); cp++);
		if (strlen (cp) < 5)
			continue;
		break;
	}
	strcpy (uacc.address1, cp);

	for (;;) {
		prompt (GUSRAD2);
		inp_get (sizeof (uacc.address2) - 1);
		if (margc < 1)
			continue;
		inp_raw ();
		for (cp = inp_buffer; *cp && (*cp == 32); cp++);
		if (strlen (cp) < 5)
			continue;
		break;
	}
	strcpy (uacc.address2, cp);
}


void
getphone ()
{
	char   *cp;

	if (!askpho)
		return;
	for (;;) {
		prompt (GUSRPHO);
		inp_get (sizeof (uacc.address1) - 1);
		if (margc < 1)
			continue;
		inp_raw ();
		for (cp = inp_buffer; *cp && (*cp == 32); cp++);
		if (strlen (cp) < 7)
			continue;
		break;
	}
	strcpy (uacc.phone, cp);
}


void
getage ()
{
	int     i;
	char   *cp;

	if (!askage)
		return;
	for (;;) {
		prompt (GUSRAGE);
		inp_get (2);
		if (margc < 1)
			continue;
		inp_raw ();
		for (cp = inp_buffer; *cp && (*cp == 32); cp++);
		i = atoi (cp);
		if (i <= 5 || i >= 99)
			continue;
		break;
	}
	uacc.age = i;
}


void
getsex ()
{
	char    i;

	if (!asksex)
		return;
	for (;;) {
		prompt (GUSRSEX);
		inp_get (1);
		if (margc < 1)
			continue;
		inp_raw ();
		switch (toupper (inp_buffer[0])) {
		case 'M':
#ifdef GREEK
		case 'A':
		case -128:
		case -104:
		case -117:
		case -93:
#endif
			i = USX_MALE;
			break;
		case 'F':
#ifdef GREEK
		case 'G':
		case -126:
		case -102:
		case -108:
		case -83:
#endif
			i = USX_FEMALE;
			break;
		default:
			continue;
		}
		break;
	}
	uacc.sex = i;
}


void
getscnsize ()
{
	int     i;
	char   *cp;

	if (!askscr)
		return;
	for (;;) {
		prompt (GSCNWID);
		inp_get (3);
		if (!margc) {
			i = 80;
			break;
		} else if (margc != 1)
			continue;
		inp_raw ();
		for (cp = inp_buffer; *cp && (*cp == 32); cp++);
		i = atoi (cp);
		if (!i)
			continue;
		else if (i < 40) {
			prompt (SCN2NAR);
			continue;
		}
		if (i > 255)
			continue;
		break;
	}
	prompt (SCNWDOK);
	uacc.scnwidth = i;
	fmt_setlinelen (i);

	for (;;) {
		prompt (GSCNHGT);
		inp_get (3);
		if (!margc) {
			i = 23;
			break;
		} else if (margc != 1)
			continue;
		inp_raw ();
		for (cp = inp_buffer; *cp && (*cp == 32); cp++);
		i = atoi (cp);
		if (i < 10)
			continue;
		if (i > 255)
			continue;
		break;
	}
	uacc.scnheight = i;
}


void
getsystype ()
{
	int     i;

	if (!asksys)
		return;
	for (;;) {
		prompt (GSYSTYP);
		inp_get (1);
		if (!margc)
			continue;
		inp_raw ();
		i = atoi (inp_buffer);
		if (i < 0 || i > 7)
			continue;
		break;
	}
	uacc.system = i;
}


int
checkbaduid (char *uid)
{
	FILE   *fp;
	char    line[256];

	if ((fp = fopen (mkfname (BADUIDFILE), "r")) == NULL)
		return 1;
	while (!feof (fp)) {
		if (fgets (line, 256, fp)) {
			int     i;

			for (i = 0; i < sizeof (line); i++) {
				if (line[i] == 10 || line[i] == 13) {
					line[i] = 0;
					break;
				}
			}
			if (sameas (line, uid)) {
				fclose (fp);
				return 0;
			}
		}
	}
	fclose (fp);
	return 1;
}


#if 0
int
uidexists (char *s)
{
	FILE   *fp;

	if ((fp = fopen ("/etc/passwd", "r")) == NULL) {
		error_fatalsys ("Unable to open /etc/passwd!");
	}

	while (!feof (fp)) {
		char    line[1024];
		char   *cp;

		if (!fgets (line, 1024, fp))
			continue;
		if ((cp = strchr (line, ':')) == NULL)
			continue;
		*cp = 0;
		if (sameas (line, s)) {
			fclose (fp);
			return 1;
		}
	}
	fclose (fp);
	return 0;
}
#endif


void
getid ()
{
	int     i, c, l, ok, accepted;

	prompt (PREUID);
	for (;;) {
		prompt (GUSERID);
		inp_get (mxuidl);
		if (!margc)
			continue;
		inp_raw ();
		if (strlen (inp_buffer) < 3) {
			prompt (SMLUID);
			continue;
		}
		for (ok = 1, c = l = i = 0; inp_buffer[i]; i++) {
			char    ch = inp_buffer[i];

			if (isalpha (ch)) {
				l++;
				if (islower (ch))
					c--;
				else
					c++;
			} else {
				if (isdigit (ch) && !alwnum)
					ok = 0;
				else if (!alwsym &&
					 (ch == '-' || ch == '_' || ch == '.'))
					ok = 0;
				else if (!isalpha (ch))
					ok = 0;
			}
		}
		if (!ok) {
			prompt (BADUID1, inp_buffer);
			continue;
		}
		if (abs (c) == l) {
			inp_buffer[0] = toupper (inp_buffer[0]);
			for (i = 1; i < strlen (inp_buffer); i++)
				inp_buffer[i] = tolower (inp_buffer[i]);
		}
		if (!checkbaduid (inp_buffer)) {
			prompt (BADUID2, inp_buffer);
			continue;
		}
		if ( /*uidexists(inp_buffer)|| */ usr_exists (inp_buffer)) {
			prompt (BADUID3, inp_buffer);
			continue;
		}

		accepted = 0;
		while (!accepted) {
			prompt (UIDOK, inp_buffer);
			strcpy (uacc.userid, inp_buffer);
			inp_get (1);
			if (!margc)
				continue;
			cnc_begin ();
			switch (cnc_yesno ()) {
			case 'Y':
				accepted = 1;
				break;
			case 'N':
				accepted = -1;
				break;
			}
		}
		if (accepted == -1)
			continue;

		break;
	}
}


char   *
makeapass ()
{
	FILE   *words;
	static char pass[16] = { 0 };
	char    word[16] = { 0 };
	int     l, i, j;

	pass [0]=0;
	if ((words = fopen (mkfname(FLETTRWORDS), "r")) != NULL) {
		randomize ();
		fseek (words, 0L, SEEK_END);
		l = (int) ftell (words);
		rewind (words);
		fseek (words, (long) rnd (l - 15), SEEK_SET);
		fscanf (words, "%s", pass);
		fscanf (words, "%s", pass);
		fseek (words, (long) rnd (l - 15), SEEK_SET);
		fscanf (words, "%s", word);
		fscanf (words, "%s", word);
		pass[4] = DELIM[rnd (strlen (DELIM))];
		memcpy (pass + 5, word, 5);
		fclose (words);

		j = rnd (4);
		if (j < 2) {
			int     k = (j == 0) ? 4 : 1;

			for (i = 0; i < k; i++)
				pass[i] = toupper (pass[i]);
		} else {
			int     k = (j == 2) ? 9 : 6;

			for (i = 5; i < k; i++)
				pass[i] = toupper (pass[i]);
		}
	}

	return pass;
}


int
stupidpass (char *pass)
{
	FILE   *fp;
	char    line[256];

	if (sameas (pass, uacc.userid))
		return 1;
	if ((fp = fopen (mkfname (BADPASSFILE), "r")) == NULL)
		return 0;
	while (!feof (fp)) {
		if (fgets (line, 256, fp)) {
			int     i;

			for (i = 0; i < sizeof (line); i++) {
				if (line[i] == 10 || line[i] == 13) {
					line[i] = 0;
					break;
				}
			}
			if (sameas (line, pass)) {
				fclose (fp);
				return 1;
			}
		}
	}
	fclose (fp);
	return 0;
}


void
getpassword ()
{
	char * recommended;

	prompt (PREPSW);
	if ((recommended = makeapass ()) != NULL)
		strcpy (uacc.passwd, recommended);

	for (;;) {
		if (mkpswd && mkpwdf && recommended[0]) {
			prompt (FRCPSW, recommended);
		} else {
			if (mkpswd) prompt (RECPSW, recommended);
			prompt (GPSWORD);
			inp_setflags (INF_PASSWD);
			inp_get (15);
			inp_clearflags (INF_PASSWD);
			if (!margc)
				continue;
			inp_raw ();
			
			if (safpsw) {
				int     i, d = 0;
				
				if (strlen (inp_buffer) < minpln) {
					prompt (BADPSW1);
					continue;
				}
				if (!strpss)
					d++;
				else {
					for (i = 0, d = 0; inp_buffer[i]; i++)
						if (isupper (inp_buffer[i]) ||
						    !isalpha (inp_buffer[i]))
							d++;
				}
				if (!d) {
					prompt (BADPSW1);
					continue;
				}
				if (stupidpass (inp_buffer)) {
					prompt (BADPSW2);
					continue;
				}
				strcpy (uacc.passwd, inp_buffer);
			}
		}
		prompt (GPSWAGN);
		inp_setflags (INF_PASSWD);
		inp_get (15);
		inp_clearflags (INF_PASSWD);
		inp_raw ();
		if (!sameas (inp_buffer, uacc.passwd)) {
			prompt (BADPSW3);
			continue;
		}
		break;
	}
	uacc.passexp = sysvar->pswexpiry;
	prompt (PSWEPI, uacc.userid, uacc.passwd);
	inp_get (1);
}


void
flagstuff ()
{
	if (prfvis)
		uacc.prefs |= UPF_VISUAL;
	if (sameas (uacc.userid, SYSOP)) {
		int     i;

		for (i = 0; i < sizeof (uacc.sysaxs) / sizeof (long); i++)
			uacc.sysaxs[i] = -1L;
		uacc.flags |= 0;
		for (i = 0; i < sizeof (uacc.keys) / sizeof (long); i++)
			uacc.keys[i] = -1L;
	}
}


char   *
lowerc (char *s)
{
	static char tmp[1024];
	int     i;

	for (i = 0; i < 1024; i++) {
		tmp[i] = tolower (s[i]);
		if (!s[i])
			return tmp;
	}
	return tmp;
}


#if 0
static int
finduid ()
{
	struct passwd *fott;
	int     unused = beguid;

	while ((fott = getpwuid (++unused)) != NULL);
	return unused;
}
#endif


void
adduser ()
{
	FILE   *user;

	/*int uidn=finduid(); */
	int     um;
	char    fname[256];
	char    uid[64];

	strcpy (uid, lowerc (uacc.userid));


	/* Stamp with the magic number */
	memcpy (&(uacc.magic), USR_MAGIC, sizeof (uacc.magic));


#if 0
	/* Add the user to /etc/passwd */

	{
		FILE   *passfile;

		if ((passfile = fopen ("/etc/passwd", "a")) == NULL) {
			error_fatalsys
			    ("Failed to open /etc/password for appending.");
		}
		fprintf (passfile, "%s:*:%d:%d:%s:%s/%s:%s\n",
			 uid, uidn, newgidn, newnam, newhome, uid, newshl);
		fclose (passfile);
	}


	/* Add the user to /etc/shadow, if it exists */

	{
		FILE   *shadow;
		struct stat st;

		if (!stat ("/etc/shadow", &st)) {
			if ((shadow = fopen ("/etc/shadow", "a")) != NULL) {
				error_fatalsys
				    ("Failed to open /etc/shadow for appending.");
			}
			fprintf (shadow, "%s:*:9804:0:::::\n", uid);
			fclose (shadow);
		}
	}

	/* Run a script with additional user adding commands */

	um = umask (0022);
	sprintf (fname, "%s %s %d %d \"%s\" %s/%s %s >&/dev/null",
		 mkfname (USERADDBIN), uid, uidn, newgidn, newnam, newhome,
		 uid, newshl);
	if (system (fname))
		error_fatal ("%s failed to add user.", mkfname (USERADDBIN));
	umask (um);
#endif

	/* Run a script with additional user adding commands */

	um = umask (0022);
	sprintf (fname, "%s %s >&/dev/null", mkfname (USERADDBIN), uid);
	if (system (fname))
		error_fatal ("%s failed to execute additional signup script.",
			     mkfname (USERADDBIN));
	umask (um);

	/* Add the user's record */

	sprintf (fname, "%s/%s", mkfname (USRDIR), uacc.userid);
	if ((user = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Failed to create user account %s", fname);
	}

	if (fwrite (&uacc, sizeof (uacc), 1, user) != 1) {
		error_fatalsys ("Failed to write user account %s", fname);
	}

	fclose (user);
}


void
signemup ()
{
	classrec_t *cls;

	memset (&uacc, 0, sizeof (uacc));
	strcpy (uacc.tempclss, newclss);
	zeropad (uacc.tempclss, 10);
	strcpy (uacc.curclss, newclss);
	zeropad (uacc.curclss, 10);
	uacc.scnwidth = 80;
	uacc.scnheight = 23;
	uacc.datecre = today ();
	uacc.sex = USX_MALE;
	uacc.datelast = -1;
	uacc.auditfiltering = -1;

	msg_set (msg_sys);
	if ((uacc.pagestate =
	     msg_token (DFTPOP, "STORE", "OK", "ON", "OFF")) == 0) {
		error_fatal ("Option DFTPOP in sysvar.msg has bad value");
	} else
		uacc.pagestate--;
	uacc.pagetime = msg_int (DFTPTM, 0, 9);
	msg_set (msg);

	if ((cls = cls_find (newclss)) == NULL) {
		error_fatal ("New user class \"%s\" does not exist!", newclss);
	}

	uacc.credits = cls->crdperday;
	uacc.totcreds = cls->crdperday;

	askxlation ();
	getlanguage ();
	getansiop ();

	prompt (INTRO);
	evilpause (intpauz);

	getusername ();
	getcompany ();
	getaddress ();
	getphone ();
	getage ();
	getsex ();
	getscnsize ();
	getsystype ();
	getid ();
	getpassword ();
	
	sleep (1);

	setenv ("USERID", uacc.userid, 1);

	prompt (WELCOME);
	evilpause (welpauz);

	adduser ();
}


void
logemin ()
{
	mod_done (INI_ALL);

	{
		FILE   *fp;
		char    fname[256];

		sprintf (fname, TMPDIR "/signup-%s", tty);
		if ((fp = fopen (fname, "w")) == NULL)
			exit (0);
		fprintf (fp, "%s", uacc.userid);
		fclose (fp);
	}

	exit (0);
/*  (void) execl(BBSLOGIN,"",NULL);
  (void) execl("/bin/sh","-c",BBSLOGIN,NULL);
  error_fatalsys("Cannot execute %s",BBSLOGIN); */
}


void
setquestions (char *s)
{
	if (strchr (s, 'l')) asklang = 0;
	else asklang = 1;

	if (strchr (s, 'a')) askansi = 0;
	else askansi = 1;

	if (strchr (s, 'x')) askxlt = 0;
	else askxlt = 1;
}


int
main (int argc, char *argv[])
{
	mod_setprogname (argv[0]);
	if (argc > 1)
		setquestions (argv[1]);
	init ();
	readdefaults ();
/*  if(argc==2 && sameas(argv[1],"-mail")){
    sendmail();
    sleep(10);
    return;
  } */
	signemup ();
	logemin ();

	return 0;
}


/* End of File */
