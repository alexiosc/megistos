/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbslogin.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: C, March 95, Version 0.3                                     **
 **            D, July 95, Version 0.4                                      **
 **            E, July 95, Version 0.5                                      **
 **  PURPOSE:  Begin a BBS session                                          **
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
 * Revision 1.7  2003/12/23 08:19:56  alexios
 * Fixed MetaBBS conditional compilation issues. Removed references to
 * sys_errlist[], which is deprecated, replacing them with calls to
 * strerror(). Fixed #include directives.
 *
 * Revision 1.6  2003/12/22 17:23:36  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.5  2001/05/20 13:59:28  alexios
 * Wisely changed audit entries AU*_HACKTRY to AU*_CRACKTRY. :-)
 *
 * Revision 1.4  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.11  1999/08/13 17:04:25  alexios
 * Numerous MetaBBS-related fixes. Starting in this version,
 * bbslogin does not expect the users to have their own BBS
 * accounts and setuid()s to a preset user ID shared among all
 * BBS users. This speeds things up massively, especially at
 * signup.
 *
 * Revision 1.10  1999/08/07 02:19:40  alexios
 * Added code to clear any remaining remsys locks. This is a
 * temporary kludge.
 *
 * Revision 1.9  1999/07/28 23:14:56  alexios
 * Bug fixes related to the environment (home directories etc).
 *
 * Revision 1.8  1999/07/18 21:58:44  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Numerous changes,
 * including support for the MetaBBS client, security fixes, etc.
 *
 * Revision 1.7  1998/12/27 16:19:44  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Numerous other long-awaited fixes.
 *
 * Revision 1.6  1998/08/11 10:24:16  alexios
 * Fixed injoth bug. Removed umask().
 *
 * Revision 1.5  1998/07/24 10:25:30  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.4  1998/03/10 10:11:26  alexios
 * Reinstating the STABLE status. What a silly mistake.
 *
 * Revision 1.3  1998/03/10 10:09:34  alexios
 * Corrected a couple of small problems. Paranoia programming,
 * mostly.
 *
 * Revision 1.2  1997/11/06 20:15:17  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/11/06 17:03:13  alexios
 * Fixed a few minor leftover bugs and switched to the new
 * auditing scheme.
 *
 * Revision 1.0  1997/11/03 00:55:23  alexios
 * Bbslogin is now Stable and has advanced to version 1.0.
 * Removed code to handle hardwired translation tables. Re-
 * placed it with code to ask for and use generalised
 * customisable translation tables. Bbslogin 1.0 handles the
 * ANSIASK and TRASK flags to ask the user for their ANSI
 * and translation preferences (unless already asked by the
 * system). Minor beautification and bugfixes. Replaced all
 * instances of xlwrite() with write(), since translation is
 * now handled by emud.
 *
 * Revision 0.5  1997/09/14 13:52:03  alexios
 * Removed calls to system() that slowed bbslogin down.
 * Replaced them with standard system calls like chown().
 *
 * Revision 0.4  1997/09/12 13:29:31  alexios
 * Added code to create the user's IPC usr_injoth() queue. Fixed the
 * broken invisible-login feature. Added auditing for duplicate
 * user login attempts.
 *
 * Revision 0.3  1997/08/30 13:08:49  alexios
 * Removed a soup (sic).
 *
 * Revision 0.1  1997/08/28 11:13:27  alexios
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
#define WANT_FCNTL_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#define WANT_SYS_WAIT_H 1
#define WANT_PWD_H 1
#define WANT_GRP_H 1
#define WANT_UTMP_H 1
#define WANT_SIGNAL_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <mbk/mbk_signup.h>
#include <mbk/mbk_login.h>
#include "bbslogin.h"


#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define LOCALLINE    ((chan_last->flags&(TTF_SERIAL|TTF_CONSOLE))!=0)
#define ALLOWSIGNUPS ((chan_last->flags&TTF_SIGNUPS)!=0)
#define KEY          (chan_last->key)


char    tty[32], userid[64];
char   *unixuid;
int     linestate, baud, ansiopt = 0;
useracc_t uacc;
onlinerec_t user;
promptblock_t *msg = NULL;
int     lonalrm;
char   *terminal;
extern char **environ;
int     xlation = 0, lang = 1;
int     setlang = 0, setansi = 0, setxlt = 0;
int     uid = -1, gid = -1;
int     bbsuid = -1, bbsgid = -1;
int     metab4, metalg;

#ifdef HAVE_METABBS
int     through_metabbs = 0;
#endif



void
setchannelstate (int result, char *user)
{
	channel_status_t status;

	channel_getstatus (tty, &status);
	status.result = result;
	status.baud = baud;
	strcpy (status.user, user);
	channel_setstatus (tty, &status);
}


#ifdef HAVE_METABBS
static int
call_metabbs_client (int mode)
{
	char    parm[4];
	int     result, pid;

	switch (pid = fork ()) {

	case -1:
		error_fatalsys ("Unable to fork() MetaBBS client");
		break;

	case 0:		/* The child process */

		/* Become mortal, the MetaBBS client doesn't need to be run by root. */

		setgid (bbsgid);
		setuid (bbsuid);

		/* Set line status and environment variables */

		setchannelstate (LSR_METABBS, "[MetaBBS]");
		strcpy (userid, "[SIGNUP]");
		setenv ("CHANNEL", tty, 1);
		sprintf (parm, "%d", baud);
		setenv ("SPEED", parm, 1);
		setenv ("TERM", terminal, 1);
		sprintf (parm, "%d", lang % 999);
		setenv ("LANG", parm, 1);
		sprintf (parm, "%d", xlation);
		setenv ("XLATION", parm, 1);
		sprintf (parm, "%d", (out_flags & OFL_ANSIENABLE) != 0);
		setenv ("ANSI", parm, 1);

		/* Now invoke the client */

		strcpy (parm, "-");
		if (setlang)
			strcat (parm, "l");
		if (setansi)
			strcat (parm, "a");
		if (setxlt)
			strcat (parm, "x");

		execl (mkfname (METABBSBIN),
		       METABBSBIN, parm, (mode == METAB4 ? "--addlocal" : " "),
		       NULL);

		/* Oops, ececl() failed. Try system() as our last resort. */

		{
			char    cmd[2048];

			strcpy (cmd, "exec ");
			strcat (cmd, mkfname (METABBSBIN));
			exit (system (cmd));
		}
	}


	/* Only the parent process gets to this point */

	waitpid (pid, &result, 0);	/* Wait for the child to finish */
	pid = WIFEXITED (result);	/* Bogus call: just need to call WIFEXITED() */

	setchannelstate ((LOCALLINE) ? LSR_OK : LSR_LOGIN, "[NO-USER]");

	return WEXITSTATUS (result);	/* Stupid sequence, but necessary... */
}


static int
call_metabbs_server ()
{
	mod_setbot (1);
	return 0;

#if 0
	char    parm[4];

	/* Become mortal, the metabbsd server doesn't need to run as root. */
	setgid (bbsgid);
	setuid (bbsuid);

	/* Set line status and environment variables */

	setchannelstate (LSR_INTERBBS, "[MetaBBSd]");
	strcpy (userid, "[SIGNUP]");
	setenv ("CHANNEL", tty, 1);
	sprintf (parm, "%d", baud);
	setenv ("SPEED", parm, 1);
	setenv ("TERM", terminal, 1);
	sprintf (parm, "%d", lang % 999);
	setenv ("LANG", parm, 1);
	sprintf (parm, "%d", xlation);
	setenv ("XLATION", parm, 1);
	sprintf (parm, "%d", (out_flags & OFL_ANSIENABLE) != 0);
	setenv ("ANSI", parm, 1);

	/* Now invoke the client */

	execl (mkfname (METABBSDBIN), METABBSDBIN, NULL);

	/* Oops, execl() failed. Try system() as our last resort. */

	{
		char    cmd[2048];

		strcpy (cmd, "exec ");
		strcat (cmd, mkfname (METABBSDBIN));
		exit (system (cmd));
	}

	exit (0);
#endif
}


#endif



void
mkinjoth ()
{
	struct msqid_ds buf;

	user.injothqueue = msgget (IPC_PRIVATE, 0620);
	if (user.injothqueue < 0) {
		int     i = errno;

		error_fatal
		    ("Unable to allocate IPC message queue (errno=%d, %s)", i,
		     strerror (i));
	}

	if (msgctl (user.injothqueue, IPC_STAT, &buf)) {
		int     i = errno;

		error_fatal ("Unable to IPC_STAT injoth queue (errno=%d, %s)",
			     i, strerror (i));
	}

	buf.msg_perm.uid = uid;
	buf.msg_perm.gid = gid;

	if (msgctl (user.injothqueue, IPC_SET, &buf)) {
		error_fatalsys ("Unable to IPC_SET injoth queue");
	}
}


void
writeonline (char status)
{
	FILE   *fp;
	char    fname[256], ttyname[256];

	sprintf (fname, "%s/%s", mkfname (ONLINEDIR), userid);
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Unable to create on-line info for %s.",
				userid);
	}
	memset (&user, 0, sizeof (user));
	memcpy (user.magic, ONL_MAGIC, sizeof (user.magic));
	user.injothqueue = -1;
	strcpy (user.userid, userid);
	user.baudrate = atoi (getenv ("BAUD"));
	user.statcreds = 0;
	user.statptrs = STF_FIRST;
	strcpy (user.channel, tty);
	strcpy (user.emupty, getenv ("EMUPTY"));
	strcpy (user.curpage, "");
	user.flags = 0;
	user.tick = 0;
	user.loggedin = time (0);
	strcpy (user.input, "");
	if (mod_isbot ()) {
		user.flags |= OLF_ISBOT;
	}
	if (hassysaxs (&uacc, USY_INVIS) && status == '!') {
		unsetenv ("INVIS");
		user.flags |= OLF_INVISIBLE;
	}

	/* Describe user logon process for /# command */

	{
		int     i;

		for (i = 0; i < NUMLANGUAGES; i++) {
			strcpy (user.descr[i], msg_getl (DESCR, i));
		}
	}


	/* This is no longer used, emud takes care of it. */

#if 0
	/* Force idle timeouts if the user is connecting through telnet */

	if ((channels[chan_getindex (user.channel)].flags) & TTF_TELNET)
		user.flags |= OLF_FORCEIDLE;
#endif

	/* Check if user is elligible to bypass idle zapping (eg is a sysop) */

	if (key_owns (&uacc, sysvar->idlovr))
		user.flags |= OLF_ZAPBYPASS;

	user.lastpage = -100;

	if ((uacc.prefs & UPF_TRDEF) == 0) {
		usr_setoxlation (user, usr_getpxlation (uacc));
		out_setxlation (usr_getpxlation (uacc));
	}

	user.flags &= ~OLF_ANSION;
	if (uacc.prefs & (UPF_ANSIDEF | UPF_ANSIASK) &&
	    (out_flags & OFL_ANSIENABLE))
		user.flags |= OLF_ANSION;
	else if ((uacc.prefs & UPF_ANSIDEF) == 0 && uacc.prefs & UPF_ANSION)
		user.flags |= OLF_ANSION;

	mkinjoth ();

	if (!fwrite (&user, sizeof (user), 1, fp)) {
		error_fatalsys ("Unable to write on-line info for %s.",
				userid);
	}
	fclose (fp);

	sprintf (ttyname, "%s/.%s", mkfname (ONLINEDIR), tty);
	if ((fp = fopen (ttyname, "w")) != NULL) {
		fprintf (fp, "%s\n", fname);
	}
	fclose (fp);
	sprintf (fname, "%s/.shmid-%s", mkfname (ONLINEDIR), userid);
	chown (fname, uid, gid);
	sprintf (fname, "%s/.%s", mkfname (ONLINEDIR), tty);
	chown (fname, uid, gid);
	sprintf (fname, "%s/%s", mkfname (ONLINEDIR), userid);
	chown (fname, uid, gid);
}


void
updateutmp (char *username)
{
	struct utmp ut;
	int     wtmp;

	memset ((char *) &ut, 0, sizeof (ut));
	ut.ut_type = USER_PROCESS;
	ut.ut_pid = getpid ();
	strncpy (ut.ut_line, tty, sizeof (ut.ut_line));
	memcpy (ut.ut_id, &tty[3], 2);
	(void) time (&ut.ut_time);
	strncpy (ut.ut_user, username, sizeof (ut.ut_user));

	utmpname (_PATH_UTMP);
	setutent ();
	pututline (&ut);
	endutent ();

	if ((wtmp = open (_PATH_WTMP, O_APPEND | O_WRONLY)) >= 0) {
		write (wtmp, (char *) &ut, sizeof (ut));
		close (wtmp);
	}
}


void
notifybbsd ()
{
	FILE   *fp;

	if ((fp = fopen (mkfname (BBSDPIPEFILE), "w")) == NULL)
		return;
	fprintf (fp, "connect %s %s\n", tty, user.userid);
	fclose (fp);
}


void
waitshmid (char *user)
{
	int     i;
	char    fname[256], userf[256];
	struct stat buf;

	sprintf (fname, "%s/.shmid-%s", mkfname (ONLINEDIR), user);
	for (i = 0; i < 20; i++) {
		usleep (100000);
		if (!stat (fname, &buf))
			return;
	}
	sprintf (userf, "%s/%s", mkfname (ONLINEDIR), user);
	unlink (userf);
	error_fatal ("Timed out waiting for bbsd file %s", fname);
}


void
storepid ()
{
	FILE   *fp;
	char    fname[256];

	sprintf (fname, "%s/.pid-%s", mkfname (CHANDEFDIR), tty);

	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Cannot open PID file %s for writing", fname);
	}

	fprintf (fp, "%d\n", getpid ());
	fclose (fp);
}


void
resetchannel ()
{
	channel_status_t status;

	channel_getstatus (tty, &status);
	status.result = LSR_OK;
	status.baud = baud;
	status.user[0] = 0;
	channel_setstatus (tty, &status);
}


void
init ()
{
	struct passwd *passwd = getpwnam (BBSUSERNAME), bbspass;
	char    baudrate[64], fname[256];
	FILE   *fp;

#ifdef HAVE_METABBS
	if (getenv ("DISPLAY") != NULL) {
		char   *disp = getenv ("DISPLAY");

		if (sameto ("MetaBBS:", disp)) {
			char   *s = strdup (&disp[strlen ("MetaBBS:")]), *cp;
			int     i;

			through_metabbs = 1;

			for (i = 0, cp = strtok (s, ":"); cp;
			     cp = strtok (NULL, ":"), i++) {
				switch (i) {
				case 0:	/* Comm rate */
					baud = atoi (cp);
					setenv ("BAUD", cp, 1);
					break;
				case 1:	/* Terminal at other end (ignored) */
					break;
				case 2:
					break;	/* BBS at other end (ignored) */
				default:
					error_fatal
					    ("Sanity check failed while parsing MetaBBS variable!");
				}
			}

			free (s);
		}
	}
#endif


	if (passwd == NULL) {
		error_fatal
		    ("Unable to find the BBS user %s in /etc/passwd. Aborting.",
		     BBSUSERNAME);
	} else
		memcpy (&bbspass, passwd, sizeof (bbspass));


	if (getuid ()) {
		error_fatal ("bbslogin must be run by the super user.");
	}

	bbsuid = bbspass.pw_uid;
	bbsgid = bbspass.pw_gid;

	strcpy (tty, getenv ("CHANNEL"));
	strcpy (baudrate, getenv ("BAUD"));
	setenv ("PREFIX", mkfname (""), 1);
	setenv ("BINDIR", mkfname (BINDIR), 1);
	setenv ("CHANNEL", tty, 1);
	setenv ("BAUD", baudrate, 1);


	mod_init (INI_TTYNUM | INI_OUTPUT | INI_SYSVARS | INI_ERRMSGS |
		  INI_INPUT | INI_SIGNALS | INI_CLASSES | INI_LANGS |
		  INI_ATEXIT);
	out_clearflags (OFL_WAITTOCLEAR);

	atexit (resetchannel);

	if (chan_getnum (tty) < 0) {
		error_fatal ("%s has not been registered in %s",
			     tty, mkfname (CHANDEFFILE));
	}

	msg = msg_open ("login");
	msg_setlanguage (chan_last->lang >
			 0 ? chan_last->lang : -chan_last->lang);
	unixuid = msg_string (UNIXUID);
	lonalrm = msg_int (LONALRM, 0, 32767) * 60;
	terminal = msg_string (TERMINAL);
	metab4 = msg_bool (METAB4);
	metalg = msg_bool (METALG);

	sprintf (fname, "%s/.%s", mkfname (ONLINEDIR), tty);
	if ((fp = fopen (fname, "r")) != NULL) {
		char    onlrec[256];

		if (fscanf (fp, "%s", onlrec) == 1)
			unlink (onlrec);
		fclose (fp);
	}
	unlink (fname);

}


void
idler ()
{
	char    fname[256];

	fclose (stdout);
	fclose (stdin);
	sprintf (fname, "%s/.pid-%s", mkfname (CHANDEFDIR), tty);
	execl (mkfname (IDLERBIN), "idler", ">", fname, "2>", fname, NULL);
}


void
showttyinfo ()
{
	char    fname[256];

	sprintf (fname, mkfname (TTYINFOFILE), tty);
	out_printfile (fname);
}


void
timeout ()
{
	prompt (TIMEOUT);
	sleep (1);
	channel_hangup ();
	exit (0);
}


void
getinp (char *i, int passwordentry)
{
	int     cp = 0;
	unsigned char c;
	static char del[4] = "\010 \010\0";

	for (;;) {
		read (0, &c, 1);

		switch (c) {
		case 13:
		case 10:
			c = '\n';
			write (0, &c, 1);
			fflush (stdout);
			inp_buffer[cp] = 0;
			inp_setmonitorid (tty);
			inp_monitor (tty);
			strcpy (i, inp_buffer);
			return;
		case 127:
		case 8:
			if (cp) {
				write (0, del, 3);
				cp--;
			}
			break;
		case 4:
			sleep (5);
			exit (0);
			break;
		default:
			if (strlen (inp_buffer) < 63 && c >= 0x20) {
				inp_buffer[cp++] = c;
				if (passwordentry)
					c = '*';
				write (0, &c, 1);
			}
		}
	}
}


void
kickout ()
{
	prompt (STRUKO);
	channel_hangup ();
	sleep (5);
	exit (0);
}


void
setterm ()
{
	FILE   *fp;

	setenv ("TERM", terminal, 1);

	if ((fp = fopen (ETCTTYFILE, "r")) == NULL)
		return;
	while (!feof (fp)) {
		char    line[1024], *cp = line, TTY[64], TERM[64];

		if (!fgets (line, sizeof (line), fp))
			continue;
		while (*cp && isspace (*(cp++)));
		if (*cp == '#')
			continue;
		if (sscanf (line, " %s %s ", TERM, TTY) == 2) {
			if (!strcmp (tty, TTY)) {
				setenv ("TERM", TERM, 1);
				break;
			}
		}
	}
	fclose (fp);
}


void
unixlogin ()
{
	char    command[256];

	setterm ();
	sprintf (command, "%s sane", STTYBIN);
	system (command);
	setchannelstate (LSR_USER, "[UNIX]");

	/* Try different ways to start login, using /bin/sh if we have to. */
	execl (LOGINBIN, "login", userid, NULL);
	execl ("/bin/sh", "sh", "-c", "exec", "login", userid, NULL);
	execl ("/bin/sh", "sh", "-c", "login", userid, NULL);
	error_fatalsys ("Unable to execute %s", LOGINBIN);
	exit (1);
}


void
askxlation ()
{
	struct stat st;
	char    fname[256];
	int     xltmap[10];
	int     i;
	char    inp_buffer[80];
	int     def = -1;

	if (setxlt)
		return;		/* Don't ask twice. */

	/* Check the available translation tables and make the first one the
	   default */

	for (i = 0; i < NUMXLATIONS; i++) {
		strcpy (fname, mkfname (XLATIONDIR "/" XLATIONSRC, i));
		xltmap[i] = (stat (fname, &st) == 0);
		if (xltmap[i] && def < 0)
			def = i;
	}

	/* Check if this channel has a default translation table. */

	setxlt = 1;
	if (chan_last->xlation)
		def = chan_last->xlation;

	for (;;) {
		prompt (XLATEM, def);
		getinp (inp_buffer, 0);
		if (strlen (inp_buffer) == 1 && isdigit (*inp_buffer))
			xlation = atoi (inp_buffer);
		else if (!strlen (inp_buffer))
			xlation = def;
		if (!xltmap[xlation])
			prompt (XLATEE);
		else
			break;
	}
}


void
askansi ()
{
	int     answer;

	if (setansi)
		return;		/* Don't ask twice */
	setansi = 1;
	while (!get_bool
	       (&answer, 0, QANSIERR, QANSI, chan_last->flags & TTF_ANSI));
	answer ? out_setflags (OFL_ANSIENABLE) :
	    out_clearflags (OFL_ANSIENABLE);
}


void
asklanguage ()
{
	int     i = 0, choice = 0, ok = 0, showmenu = 1;
	char    inp_buffer[80];

	setlang = 1;
	if (msg_numlangs) {
		while (!ok) {
			if (showmenu) {
				showmenu = 0;
				prompt (ASKLNG1);
				for (i = 0; i < msg_numlangs; i++)
					prompt (ASKLNG2, i + 1,
						msg_langnames[i]);
			}
			prompt (ASKLNG3, msg_numlangs, chan_last->lang);
			getinp (inp_buffer, 0);
			if (sameas (inp_buffer, "?")) {
				showmenu = 1;
				continue;
			} else if (!inp_buffer[0]) {
				ok = 1;
				choice = chan_last->lang;
			} else {
				choice = atoi (inp_buffer);
				if (choice < 1 || choice > msg_numlangs) {
					prompt (ASKLNGR, msg_numlangs);
					continue;
				} else
					ok = 1;
			}
		}
	} else
		choice = 1;
	lang = choice;
	msg_setlanguage (choice);
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


#ifdef HAVE_METABBS

static char *magic_spaces = " \t  \t    \t        \t                \t\n";

static int
check_interbbs ()
{
	int     i, j = 0;
	char    c;

	inp_nonblock ();
	for (i = 0; i < 5; i++) {
		print (magic_spaces);
		usleep (150000);

		for (;;) {
			c = 0;
			if (read (0, &c, 1) < 1)
				break;
			else if (c == 2)
				j++;
			if (j == 4) {
				inp_block ();
				return 1;
			}
		}
	}
	inp_block ();
	return 0;
}

#endif /* HAVE_METABBS */


void
authenticate ()
{
	struct passwd *passwd, pass;
	char    status = 0, filename[256];
	FILE   *fp;
	int     givenprompt = 0, strikes = 0, signup = 0;
	int     defaultansi = (chan_last->flags & TTF_ANSI) != 0;
	channel_status_t linestatus;
       
#ifdef HAVE_METABBS
	int metabbs_strikes = 0;
#endif /* HAVE_METABBS */


	/* Delay so that b.a.d comms packages have enough time to start reading the
	   port after the connection. This isn't guaranteed to catch everything, but we
	   DO try, at least. */

	sleep (1);

	baud = atoi (getenv ("BAUD"));

	if (!channel_getstatus (tty, &linestatus)) {
		error_fatal ("Unable to get line status for %s\n", tty);
	}


	/* Clear any remaining remsys locks -- this is obviously a kludge */

	sprintf (filename, "LCK-remsys-%s", tty);
	lock_rm (filename);

	if ((linestatus.state == LST_BUSYOUT) ||
	    (linestatus.state == LST_NOANSWER)) {
		prompt (LDOWN);
		sleep (5);
		channel_hangup ();
		return;
	}

	if (chan_last->flags & TTF_ANSI)
		out_setflags (OFL_ANSIENABLE);
	else
		out_clearflags (OFL_ANSIENABLE);

#ifdef HAVE_METABBS
	if (through_metabbs)
		ansiopt = (chan_last->flags & TTF_ANSI) ? 2 : 1;
	else
#endif	/* HAVE_METABBS */

	if (chan_last->flags & TTF_ASKANSI)
		ansiopt = 3;
	else if (chan_last->flags & TTF_ANSI)
		ansiopt = 2;
	else
		ansiopt = 1;

	setenv ("CHANNEL", tty, 1);
	out_setxlation (xlation = chan_last->xlation);

	if (linestatus.state != LST_OFFLINE) {
		if (!LOCALLINE)
			setchannelstate (LSR_LOGIN, "[NO-USER]");

		if (chan_last->flags & TTF_TELNET &&
		    (chan_telnetlinecount () > sysvar->tnlmax)) {
			prompt (TFULL);
			sleep (1);
			channel_hangup ();
			return;
		}

		out_clearflags (OFL_ANSIENABLE);

		xlation = chan_last->xlation;

#ifdef HAVE_METABBS
		if (check_interbbs ())
			call_metabbs_server ();

		if (!through_metabbs)
#endif
			if (chan_last->flags & TTF_ASKXLT)
				askxlation ();
		out_setxlation (xlation);
		out_setflags (OFL_ANSIENABLE);

		if (!ansiopt)
			ansiopt = 2;
		if (--ansiopt < 2) {
			if (ansiopt)
				out_setflags (OFL_ANSIENABLE);
			else
				out_clearflags (OFL_ANSIENABLE);
		} else {
			char    c, answer = defaultansi ? 'Y' : 'N';
			int     len = 0, ok = 0;

			setansi = 1;
			prompt (QANSI);
			while (!ok) {
				read (STDIN, &c, 1);
				c = toupper (c);
				switch (c) {
				case 'Y':
				case 'N':
					if (!len) {
						len++;
						answer = c;
						write (STDOUT, &c, 1);
					}
					break;
				case 8:
				case 127:
					if (len) {
						fprintf (stdout, "\b \b");
						fflush (stdout);
						len--;
					}
					break;
				case 10:
				case 13:
					ok = 1;
					break;
				}
				ioctl (0, TCFLSH, 0);
			}
			setchannelstate (LSR_LOGIN, "[NO-USER]");
			ansiopt = (answer == 'Y');
			if (ansiopt)
				out_setflags (OFL_ANSIENABLE);
			else
				out_clearflags (OFL_ANSIENABLE);

			if (chan_last->lang < 0) {
				chan_last->lang = -chan_last->lang;

#ifdef HAVE_METABBS
				if (!through_metabbs)
#endif
					asklanguage ();
			}
		}

		error_setnotify (0);
		mod_init (INI_SYSVARS);
	} else {
		out_printfile (LOGINMSGFILE);
		showttyinfo ();
		prompt (BBSOFF, NULL);
		sleep (10);
		channel_hangup ();
		if (!LOCALLINE) {
			sleep (10);
			exit (0);
		} else {
			alarm (0);
			idler ();
		}
	}

	for (;;) {
		if ((!strikes && LOCALLINE) || !givenprompt) {
			givenprompt = 1;
			prompt (chan_last->
				flags & TTF_TELNET ? THELLO : HELLO);
			out_printfile (mkfname (LOGINMSGFILE));
			showttyinfo ();
		}
#ifndef HAVE_METABBS
		prompt (ALLOWSIGNUPS ? ENTUSID : LOGUID);
#else

		/* If METAB4 is set, we run the MetaBBS client BEFORE the user has a chance
		   to login to this BBS. The client is instructed to show the local BBS in
		   its list, too. Access to the local BBS is offered by returning here,
		   rather than calling telnet. */

		if (metab4 && (chan_last->flags & TTF_METABBS)) {

			/* Only run the client once in this way. If remote systems are prone to
			   falling over, it's best to also enable the METALG option so that users
			   will be able to use the OUT command at the login screen and try, try
			   again. */

			metab4 = 0;

			if (++metabbs_strikes > LOGINSTRIKES) {
				channel_hangup ();
				sleep (5);
				exit (0);
			}

			/* A non-zero return value requires disconnection from the system. A zero
			   either allows the user another chance, or (here) dumps them into the
			   local BBS login screen. */

			if (call_metabbs_client (METAB4)) {
				channel_hangup ();
				sleep (1);
				exit (0);
			} else {
				metabbs_strikes++;
				givenprompt = 0;
				continue;
			}
		}


		/* Otherwise, offer the OUT command if this is a MetaBBS-enabled line and
		   option METALG is set. */

		if (chan_last->flags & TTF_METABBS && metalg) {
			prompt (ALLOWSIGNUPS ? ENTUSIDM : LOGUIDM);
		} else {
			prompt (ALLOWSIGNUPS ? ENTUSID : LOGUID);
		}

#endif				/* HAVE_METABBS */

		(void) ioctl (STDIN, TCFLSH, 0);

		if (lonalrm > 0 && !LOCALLINE) {
			signal (SIGALRM, timeout);
			alarm (lonalrm);
		}

		userid[0] = 0;
		getinp (userid, 0);
		alarm (0);

		if (!userid[0]) {
			if (!LOCALLINE || strikes)
				if (++strikes >= LOGINSTRIKES)
					kickout ();
			continue;
		}

		baud = atoi (getenv ("BAUD"));

		if (sameas (userid, SIGNUPID)) {
			if (!ALLOWSIGNUPS) {
				strikes++;
				if (strikes < LOGINSTRIKES) {
					prompt (LOGNOG, NULL);
					continue;
				} else {
					audit (tty, AUDIT (UNKUSER), userid,
					       channel_baudstg (atoi
								(getenv
								 ("BAUD"))));
					kickout ();
				}
			} else {
				char    parm[32], command[256];

				setchannelstate (LSR_USER, "[SIGNUP]");
				strcpy (userid, "[SIGNUP]");
				setenv ("USERID", userid, 1);
				setenv ("CHANNEL", tty, 1);
				setenv ("TERM", terminal, 1);
				updateutmp (userid);

				strcpy (parm, "-");
				if (setlang)
					strcat (parm, "l");
				if (setansi)
					strcat (parm, "a");
				if (setxlt)
					strcat (parm, "x");
				sprintf (command, "%s %s", mkfname (SIGNUPBIN),
					 parm);
				system (command);
				{
					FILE   *fp;
					char    fname[256];

					sprintf (fname, "/tmp/signup-%s", tty);
					if ((fp = fopen (fname, "r")) == NULL)
						exit (0);
					fscanf (fp, "%s", userid);
					signup = 1;
					fclose (fp);
					unlink (fname);
				}
			}
		}
#ifdef HAVE_METABBS
		if (metalg && sameas (userid, METABBSID) &&
		    (chan_last->flags & TTF_METABBS)) {
			if (++metabbs_strikes > LOGINSTRIKES) {
				prompt (METAKO);
				channel_hangup ();
				sleep (5);
				exit (0);
			}

			if (call_metabbs_client (METALG)) {	/* !=0 means 'disconnect afterwards' */
				channel_hangup ();
				sleep (1);
				exit (0);
			}

			givenprompt = 0;
			continue;
		}
#endif

		if (userid[0] == '!' || userid[0] == '@') {
			status = userid[0];
			strcpy (userid, &userid[1]);
		}

		if (!usr_exists (userid) || status == '@') {
			if ((fp = fopen ("/etc/passwd", "r")) == NULL) {
				error_fatal ("Unable to open /etc/passwd!",
					     NULL);
			}
			while (!feof (fp)) {
				char    line[1024], *cp;

				if (!fgets (line, 1024, fp))
					continue;
				if ((cp = strchr (line, ':')) == NULL)
					continue;
				*cp = 0;
				if (!strcmp (lowerc (line), userid)) {
					fclose (fp);
					unixlogin ();
				}
			}
			fclose (fp);
			strikes++;
			if (strikes < LOGINSTRIKES) {
				prompt (ALLOWSIGNUPS ? UIDNOG : LOGNOG, NULL);
				continue;
			} else {
				audit (tty, AUDIT (UNKUSER), userid,
				       channel_baudstg (baud));
				kickout ();
			}
		}

		sprintf (filename, "%s/%s", mkfname (USRDIR), userid);
		if ((fp = fopen (filename, "r")) == NULL) {
			error_fatal ("Failed to open user account %s.",
				     filename, NULL);
		}
		if (fread (&uacc, sizeof (useracc_t), 1, fp) != 1) {
			error_fatal ("Failed to read user account %s.",
				     filename, NULL);
		}
		if (strncmp (uacc.magic, USR_MAGIC, sizeof (uacc.magic))) {
			error_fatal
			    ("User account for %s is corrupted (invalid magic number)",
			     userid);
		}
		fclose (fp);

		if (uacc.flags & (UFL_SUSPENDED | UFL_DELETED)) {
			prompt (uacc.flags & UFL_DELETED ? ACCDEL : ACCSUS,
				NULL);
			channel_hangup ();
			exit (0);
		} else {
			classrec_t *ourclass = cls_find (uacc.curclss);

			if (ourclass == NULL) {
				error_fatal
				    ("Can't find class %s for user %s!",
				     uacc.curclss, uacc.userid);
			}

			msg_setlanguage (uacc.language);
			if (usr_insys (userid, 0)
			    && ((ourclass->flags & CLF_LINUX) == 0 ||
				status != '@')) {
				prompt (ALRDON, NULL);
				audit (tty, AUDIT (DUPUSER), userid,
				       channel_baudstg (baud));
				channel_hangup ();
				exit (0);
			} else if (ourclass->flags & CLF_LINUX &&
				   status == '@') {
				char   *cp = userid - 1;

				strcpy (cp, userid);
				unixlogin ();
			}
			if (ourclass->flags & CLF_LOCKOUT) {
				prompt (LOKOUT, NULL);
				channel_hangup ();
				exit (0);
			} else if (KEY) {
				if (!key_owns (&uacc, KEY)) {
					prompt (NOKEY, NULL);
					kickout ();
				}
			}
		}

		setchannelstate (LSR_LOGIN, "[NO-USER]");
		if (atoi (unixuid) > 0)
			passwd = getpwuid (atoi (unixuid));
		else
			passwd = getpwnam (unixuid);

		if (passwd == NULL) {
			error_fatal
			    ("SECURITY HOLE: %s not found in /etc/passwd.",
			     bbsuid);
		}

		memcpy (&pass, passwd, sizeof (pass));


		for (;;) {
			char    password[64];

			if (!signup) {
				prompt (ENTPSW);
				inp_setflags (INF_PASSWD);

				if (lonalrm > 0 && !LOCALLINE) {
					signal (SIGALRM, timeout);
					alarm (lonalrm);
				}

				getinp (password, 1);
				inp_clearflags (INF_PASSWD);
			} else
				strcpy (password, uacc.passwd);
			alarm (0);

			if (sameas (password, uacc.passwd)) {
				char    tmp[256];

				setenv ("USERID", userid, 1);
				setenv ("CHANNEL", tty, 1);

				uid = pass.pw_uid;
				gid = pass.pw_gid;
				writeonline (status);

				if (sysvar->lonaud)
					audit (tty, AUDIT (LOGIN), user.userid,
					       channel_baudstg (user.
								baudrate));

				notifybbsd ();

				waitshmid (userid);
				mod_done (INI_ALL);
				mod_init (INI_ALL);
				memcpy (&thisuseracc, &uacc,
					sizeof (useracc_t));
				memcpy (&thisuseronl, &user,
					sizeof (onlinerec_t));
				setchannelstate (LSR_USER, userid);
				msg_setlanguage (uacc.language);
				fmt_setscreenheight (thisuseracc.scnheight);
				fmt_setlinelen (thisuseracc.scnwidth);
				out_clearflags (OFL_WAITTOCLEAR);
				out_setflags (OFL_AFTERINPUT);
				fmt_resetvpos (0);

				if (atoi (unixuid) > 0)
					passwd = getpwuid (atoi (unixuid));
				else
					passwd = getpwnam (unixuid);
				memcpy (&pass, passwd, sizeof (pass));

				if (ansiopt)
					out_setflags (OFL_ANSIENABLE);
				else
					out_clearflags (OFL_ANSIENABLE);
				msg_set (msg);
				if (uacc.prefs & UPF_TRASK)
					askxlation ();
				else if (uacc.prefs & UPF_TRDEF)
					out_setxlation (xlation);

				if (uacc.prefs & UPF_ANSIASK)
					askansi ();
				if (ansiopt) {
					user.flags |= OLF_ANSION;
					out_setflags (OFL_ANSIENABLE);
				} else {
					user.flags &= ~OLF_ANSION;
					out_clearflags (OFL_ANSIENABLE);
				}

				if (sysvar)
					sysvar->connections++;

				if ((!getuid ()) || (!getgid ())) {
					char    fname[256];

					sprintf (fname, "%s/.shmid-%s",
						 mkfname (ONLINEDIR), userid);
					chown (fname, bbsuid, bbsgid);
				}

				/*      if(hassysaxs(&uacc,USY_INVIS) && status=='!'){
				   user.flags|=OLF_INVISIBLE;
				   setenv("INVIS","on",1);
				   } */

				sprintf (tmp,
					 "%s sane rows %d columns %d ixon ixoff",
					 STTYBIN, uacc.scnheight,
					 uacc.scnwidth);
				system (tmp);
				sprintf (tmp, "%d", uacc.scnwidth);
/*	setenv("BBSCOLUMNS",tmp,1); */
				sprintf (tmp, "%d", uacc.scnheight);
/*	setenv("BBSROWS",tmp,1); */

				/* Attempt to set the homedir. If it's not there, don't just
				   set /root: set /tmp */
				{
					struct stat st;

					if (!stat (pass.pw_dir, &st))
						setenv ("HOME", pass.pw_dir,
							1);
					else
						setenv ("HOME", "/tmp", 1);
				}
/*
  
  NB: mkfname() must be added to Megistos DIRs here.

	if(pass.pw_uid) setenv("PATH", _PATH_DEFPATH":"BINDIR, 1);
	else setenv("PATH", _PATH_DEFPATH_ROOT":"BINDIR, 1); */


				setenv ("SHELL", pass.pw_shell, 1);
				sprintf (tmp, "%s/%s", _PATH_MAILDIR, userid);
				setenv ("MAIL", tmp, 0);
				setenv ("USERNAME", userid, 1);
				sprintf (tmp, "%s/.bashrc", pass.pw_dir);
				setenv ("ENV", tmp, 1);

				sprintf (tmp, "/dev/%s", tty);
				chmod (tmp, 0660);
				chown (tmp, pass.pw_uid, pass.pw_gid);
				setgid (pass.pw_gid);
				if (initgroups (pass.pw_name, pass.pw_gid) < 0) {
					error_fatal
					    ("Unable to init groups for user %s",
					     pass.pw_name);
				}
				umask (0007);

				updateutmp (pass.pw_name);

				/* Kludge: chmod() /etc/passwd to fix permissions problem */
				/*chmod("/etc/passwd",0644); */

				setgid (pass.pw_gid);
				setuid (pass.pw_uid);

				/* Even paranoids have enemies */

				if (getuid () == 0 || getgid () == 0) {
					error_fatal
					    ("User %s appears to have root uid/gid!",
					     pass.pw_name);
				}

				msg_setlanguage (uacc.language);

				msg_set (msg);
				if (signup)
					sendmail ();
				msg_set (msg);

				fmt_resetvpos (0);
				if (uacc.connections)
					prompt (GREETINGS, userid);
				else
					prompt (NEWGREET, userid);
				prompt (GPL);
				mod_done (INI_ALL);

				msg_close (msg);

				thisuseracc.connections++;

				setterm ();

				fflush (stdout);

				execl ("/bin/sh", "sh", "-c",
				       mkfname (LOGINSCRIPT), NULL);
				error_fatal ("Cannot execute %s",
					     mkfname (LOGINSCRIPT));
			} else {
				prompt (PSWNOG, NULL);
				strikes++;
				if (strikes >= LOGINSTRIKES) {
					audit (tty, AUDIT (CRACKTRY), userid,
					       channel_baudstg (baud));
					kickout ();
				}
			}
		}
	}
}



int
main (int argc, char *argv[])
{
	mod_setprogname (argv[0]);
	if (getuid ()) {
		fprintf (stderr, "%s: not superuser.\n", argv[0]);
		exit (1);
	}
	init ();

	authenticate ();
	return 0;		/* Control never reaches here */
}


/* End of File */
