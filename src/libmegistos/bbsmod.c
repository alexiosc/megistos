/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsmod.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Implement various module functions.                          **
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
 * $Id: bbsmod.c,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: bbsmod.c,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.13  2004/05/22 19:24:30  alexios
 * One slight code beautification modification.
 *
 * Revision 1.12  2004/02/29 17:08:00  alexios
 * Fixed shmget() error condition checking. Extra error logging for when
 * a user account can't be saved. Refrain from changing the umask, as
 * it's set by the rc scripts now. Fixed bug that got the bbs_gid wrong
 * and clobbered the bbs_uid when reading from the environment. Fixed
 * file ownership issues on the .emu-* files. Moved the register-* files
 * to the run/ directory. More chown(2) fixes. Rewrote the --install
 * module handler to help in the new infrastructure. It no longer prints
 * out the installation script; now it prints out the module's desired
 * priorities for all implemented handlers. The rc script takes care of
 * the rest. --uninstall has now been removed for the same reasons.
 *
 * Revision 1.11  2004/02/22 18:51:05  alexios
 * We now collect bbs_uid and bbs_gid from the environment and fall over
 * if we can't, as it's an indication of a broken setup (or something
 * sinister afoot). Initialised the variables to a reasonable value of
 * -1.
 *
 * Revision 1.10  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.9  2003/12/19 13:23:29  alexios
 * Updated include directives; updated some of the directory #defines.
 *
 * Revision 1.8  2003/09/28 22:30:08  alexios
 * Added NLS initialisation to mod_init() and mod_main().
 *
 * Revision 1.7  2003/09/28 13:11:15  alexios
 * Renamed locally used convenience macro _() which clashed with the I18N
 * convenience macro of the same name.
 *
 * Revision 1.6  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.5  2003/09/27 20:33:53  alexios
 * One minor fix in the declaration of mod_done().
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.9  2000/01/06 10:56:23  alexios
 * Changed calls to write(2) to send_out().
 *
 * Revision 0.8  1999/07/28 23:06:34  alexios
 * Fixed slight bulletins bug (yes, a bulletins but in bbsmod).
 *
 * Revision 0.7  1999/07/18 21:01:53  alexios
 * Slight changes in calls to fatal() and fatalsys(). Beautifications.
 * Minor corrections to syschat() and loaduser().
 *
 * Revision 0.6  1998/12/27 14:31:16  alexios
 * Added autoconf support. Made allowances for new getchannelstatus().
 * Added magic number checking for SYSVAR and backing up of the
 * file. Added code to look in passwd for the uid and gid of the
 * BBS user. Added flag to show that user is in Sysop chat mode so
 * that Sysops can be warned when abandoning their users in the
 * 'dungeon'. Other slight changes.
 *
 * Revision 0.5  1998/08/14 11:27:44  alexios
 * Set monitor ID the moment we know we're riding a user and
 * not a daemon or userless process.
 *
 * Revision 0.4  1998/07/24 10:08:57  alexios
 * Added module information structure and a function to set it.
 * Added function to set only the progname field in the module
 * structure, for quick migration. All programs using the lib
 * are expected to register their names if they need to use the
 * error reporting facility.
 *
 * Revision 0.3  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/03 00:34:41  alexios
 * Removed code for hardwired translation tables. Added code to
 * handle generalised tables. Changed all calls to xlwrite() to
 * write() since emud now handles all translations.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: bbsmod.c,v 2.0 2004/09/13 19:44:34 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_CTYPE_H 1
#define WANT_SIGNAL_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIOS_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_PWD_H 1
#define WANT_SEND_OUT 1
#include <megistos/bbsinclude.h>

#include <megistos/gettext.h>
#include <megistos/bbs.h>
#include <megistos/systemversion.h>

#include <mbk/mbk_sysvar.h>


#define _m(x) mkfname("%s%s",SYSVARFILE,x)


struct sysvar *sysvar = NULL;
static promptblock_t *chatmsg;
static long initialised = 0;
mod_info_t __module = { "", "", "", "", "" };
uid_t   bbs_uid = -1;
gid_t   bbs_gid = -1;
int     mod_bot = 0;


void    mod_end ();
void    catchsig ();
void    syschat ();


void
mod_setinfo (mod_info_t * mod)
{
	memcpy (&__module, mod, sizeof (__module));
}


void
mod_setprogname (char *s)
{
	char   *cp = strrchr (s, '/');

	if (cp != NULL)
		__module.progname = strdup (cp + 1);
	else
		__module.progname = strdup (s);
}


int
mod_isbot ()
{
	return mod_bot;
}


void
mod_setbot (int s)
{
	mod_bot = (s != 0);
	if (s)
		out_flags |= OFL_ISBOT;
	else
		out_flags &= ~OFL_ISBOT;
}



void
initsignals ()
{
	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGSTOP, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);
	signal (SIGTERM, catchsig);
	signal (SIGKILL, catchsig);
	signal (SIGSEGV, catchsig);
	signal (SIGFPE, catchsig);
	signal (SIGHUP, catchsig);
	signal (SIGILL, catchsig);
}


void
donesignals ()
{
	signal (SIGINT, SIG_DFL);
	signal (SIGQUIT, SIG_DFL);
	signal (SIGSTOP, SIG_DFL);
	signal (SIGTSTP, SIG_DFL);
	signal (SIGTERM, SIG_DFL);
	signal (SIGKILL, SIG_DFL);
	signal (SIGSEGV, SIG_DFL);
	signal (SIGFPE, SIG_DFL);
	signal (SIGHUP, SIG_DFL);
	signal (SIGILL, SIG_DFL);
}


void
loadsysvars ()
{
	FILE   *sysvarf;
	int     shmid, load = 0, i;
	char    fname[256];

	/* Wait for any pending locks on the file */

	lock_wait ("LCK..sysvarshm", 60);
	lock_wait ("LCK..sysvar", 60);

	/* Is the sysvar file somewhere in shared memory? */

	if ((sysvarf = fopen (mkfname (SYSVARSHMFILE), "r")) != NULL) {
		char    magic[5];

		fscanf (sysvarf, "%d", &shmid);

		/* Yup, attach it */

		sysvar = (struct sysvar *) shmat (shmid, NULL, 0);
		if ((int) sysvar < 0)
			load = 1;
		else {

			/* Check the magic number, just to be sure */

			memcpy (magic, sysvar->magic, sizeof (sysvar->magic));
			magic[4] = 0;

			if (strcmp (magic, SYSVAR_MAGIC)) {
				/* Don't know what we just attached, but it shore ain't sysvar! */
				error_fatal
				    ("Incorrent magic number in sysvar, will not attach!");
			}
		}
	} else {

		/* The sysvar isn't in shared memory, so we'll have to read it on
		   our own. This is really really bad, but we'll steel ourselves
		   and get on with it anyway. */

		load = 1;
	}
	fclose (sysvarf);

	/* You lucky, lucky bastard! */
	if (!load)
		return;

	/* Allocate memory */
	sysvar = (struct sysvar *) alcmem (sizeof (struct sysvar));

	strcpy (fname, mkfname (SYSVARFILE));
	for (i = 0; i < 6; i++) {
		if ((sysvarf = fopen (fname, "r")) != NULL) {
			char    magic[5];

			/* Attempt to load it */
			if (fread (sysvar, sizeof (struct sysvar), 1, sysvarf)
			    != 1) {
				/* Whoops, failed to read it it. Try the backups next. */
				goto try_backup;
			}
			fclose (sysvarf);

			/* Check magic number */
			memcpy (magic, sysvar->magic, sizeof (sysvar->magic));
			magic[4] = 0;
			if (strcmp (magic, SYSVAR_MAGIC)) {
				/* Not enough magic. Try the backups. */
				goto try_backup;
			}

			/* Wheee, it works! */
			break;

		}
	      try_backup:
		strcat (fname, i ? "O" : ".O");
	}
}


void
savesysvars ()
{
	FILE   *sysvarf;
	char    fname[256], magic[5];
	struct stat st;

	/* Don't save if sysvar is corrupted or non-existent */
	if (!sysvar)
		return;
	magic[4] = 0;
	memcpy (magic, sysvar->magic, sizeof (sysvar->magic));
	if (strcmp (magic, SYSVAR_MAGIC))
		return;

	/* Make a backup copy of the sysvar file and age it -- it tends to
	   die at bad crashes and we need the backups */

	if (!stat (_m(".OOOO"), &st))
		rename (_m(".OOOO"), _m(".OOOOO"));
	if (!stat (_m(".OOO"), &st))
		rename (_m(".OOO"), _m(".OOOO"));
	if (!stat (_m(".OO"), &st))
		rename (_m(".OO"), _m(".OOO"));
	if (!stat (_m(".O"), &st))
		rename (_m(".O"), _m(".OO"));
	if (!stat (_m(""), &st))
		fcopy (_m(""), _m(".O"));

	/* Make sure the files have the right owners/permissions if we're root */
	if (!getuid ()) {
		chown (_m(""), bbs_uid, bbs_gid);
		chown (_m(".O"), bbs_uid, bbs_gid);
		chown (_m(".OO"), bbs_uid, bbs_gid);
		chown (_m(".OOO"), bbs_uid, bbs_gid);
		chown (_m(".OOOO"), bbs_uid, bbs_gid);
		chown (_m(".OOOOO"), bbs_uid, bbs_gid);
		chmod (_m(""), 0660);
		chmod (_m(".O"), 0660);
		chmod (_m(".OO"), 0660);
		chmod (_m(".OOO"), 0660);
		chmod (_m(".OOOO"), 0660);
		chmod (_m(".OOOOO"), 0660);
	}

	sprintf (fname, mkfname ("%s.%d", SYSVARFILE, (int) getpid ()));
	if ((sysvarf = fopen (fname, "w")) != NULL) {
		fwrite (sysvar, sizeof (struct sysvar), 1, sysvarf);
	} else {
		/* Too late to gripe. Fail quietly and exit, hoping it's all right. */
		unlink (fname);
		return;
	}

	/* Phew, it worked. Close the file. */
	fclose (sysvarf);

	/* Make sure the file was written properly -- paranoia check */
	if ((sysvarf = fopen (fname, "r")) != NULL) {
		char    dummy[256];

		magic[4] = 0;

		if (fread (sysvar, sizeof (struct sysvar), 1, sysvarf) == 1) {
			memcpy (magic, sysvar->magic, sizeof (sysvar->magic));

			/* Magic or More Magic? */
			if (!strcmp (magic, SYSVAR_MAGIC)) {
				/* More Magic */

				/* Lock the file and put it in its rightful place. */
				lock_wait ("LCK..sysvar", 10);
				if (lock_check ("LCK..sysvar", dummy) <= 0) {
					lock_place ("LCK..sysvar", "writing");
					fcopy (fname, _m(""));
					unlink (fname);
					lock_rm ("LCK..sysvar");
				}
			}
		}
	}
	unlink (fname);

	/* Hey, I may be paranoid, but They *are* out to get me! */
	shmdt ((char *) sysvar);
}


void
loadclasses ()
{
	FILE   *fp;
	struct stat s;

	if ((fp = fopen (mkfname (CLASSFILE), "r")) == NULL) {
		error_fatalsys ("Failed to open user class file %s.",
				mkfname (CLASSFILE));
	}

	stat (mkfname (CLASSFILE), &s);
	if (!s.st_size) {
		error_fatal ("User class file %s is emtpy.",
			     mkfname (CLASSFILE));
	}
	if (s.st_size % sizeof (classrec_t)) {
		error_fatal ("User class file %s has bad format.",
			     mkfname (CLASSFILE));
	}

	cls_classes = realloc (cls_classes, s.st_size);
	cls_count = s.st_size / sizeof (classrec_t);
	if (cls_count !=
	    fread (cls_classes, sizeof (classrec_t), MAXCLASS, fp)) {
		error_fatalsys ("Can't read user classes from %s.",
				mkfname (CLASSFILE));
	}

	fclose (fp);
}


void
loaduser ()
{
	char    userid[64] = { 0 }, fname[256];
	FILE   *fp;
	int     shmid;

	strncpy (userid, getenv ("USERID"), 63);
	if (strlen (userid) < 3) {
		error_fatal ("Variable $USERID incorrectly set.");
	}

	sprintf (fname, "%s/.shmid-%s", mkfname (ONLINEDIR), userid);
	if ((fp = fopen (fname, "r")) == NULL) {
		error_fatalsys ("Unable to open file %s", fname);
	}
	if (!fscanf (fp, "%d", &shmid)) {
		error_fatalsys ("Unable to read file %s", fname);
	}
	fclose (fp);

	if ((thisshm = (struct shmuserrec *) shmat (shmid, NULL, 0)) == -1) {
		error_fatalsys ("Unable to shmat(%x) to %s.", shmid, fname);
	}

	thisuseronl.flags &=
	    ~(OLF_BUSY | OLF_NOTIMEOUT | OLF_INHIBITGO | OLF_INSYSCHAT);
	msg_setlanguage (thisuseracc.language);
	fmt_setlinelen (thisuseracc.scnwidth);
	fmt_setscreenheight (thisuseracc.scnheight);
	fmt_setverticalformat ((thisuseracc.prefs & UPF_NONSTOP) ? 0 : 1);
	out_setansiflag (thisuseronl.flags & OLF_ANSION);
	out_setwaittoclear ((thisuseracc.prefs & UPF_NONSTOP) == 0);
	/*  setxlationtable(getpxlation(thisuseracc)); */
}


void
saveuser ()
{
	char    userid[64] = { 0 };

	strncpy (userid, getenv ("USERID"), 63);

	initialised &= ~INI_USER;
	if (!strcmp (userid, thisuseracc.userid)) {
		if (!usr_saveaccount (&thisuseracc)) {
			error_logsys ("Unable to save account for %s", userid);
		}
	} else {
		error_log ("User ID name mismatch \"%s\"!=\"%s\", "
			   "won't save account.", userid, thisuseracc.userid);
	}

	if (!strcmp (userid, thisuseronl.userid)) {
		if (!usr_saveonlrec (&thisuseronl)) {
			error_logsys ("Unable to save online info for %s",
				      userid);
		}
	} else {
		error_log ("UserID mismatch \"%s\"!=\"%s\", "
			   "won't save online info.", userid,
			   thisuseronl.userid);
	}
}


static void
getprevinput ()
{
	if (thisuseronl.flags & OLF_MMCALLING && thisuseronl.input[0]) {
		strcpy (inp_buffer, thisuseronl.input);
		inp_parsin ();
		cnc_nxtcmd = NULL;
		cnc_begin ();
	}
}


void
mod_init (uint32 f)
{
	char *s;

#ifdef HAVE_SETLOCALE
	/* Set locale via LC_ALL.  */
	setlocale (LC_ALL, "");
#endif
	
#if ENABLE_NLS
	/* Set the text message domain.  */
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
#endif

	/* umask (0007); Obsoleted: now set by RC scripts */
	mod_regpid (getenv ("CHANNEL"));
	initialised |= f;

	if (f & INI_SYSVARS)
		loadsysvars ();
	if (f & INI_OUTPUT) {
		out_init ();
		if (mod_isbot ())
			out_setflags (OFL_ISBOT);
	}
	if (f & INI_USER) {
		loaduser ();
		if ((thisshm != NULL) && (f & INI_OUTPUT) != 0) {
			if (thisuseronl.flags & OLF_AFTERINP)
				out_setflags (OFL_AFTERINPUT);
			if (thisuseronl.flags & OLF_ISBOT)
				out_setflags (OFL_ISBOT);
		}
	}

	error_setnotify (f & INI_ERRMSGS);
	if (f & INI_INPUT) {
		inp_init ();
		if (initialised & INI_USER && initialised & INI_SYSVARS) {
			inp_setmonitorid (thisuseracc.userid);
			inp_setidle (sysvar->idlezap);
		}
	}

	if (f & INI_SIGNALS) initsignals ();
	if (f & INI_CLASSES) loadclasses ();
	if (f & INI_LANGS) msg_init ();
	if (f & INI_GLOBCMD) gcs_init ();
	if (f & INI_TTYNUM) chan_init ();
	if (f & INI_ATEXIT) atexit (mod_end);
	if ((f & INI_USER) && (f & INI_INPUT)) getprevinput ();
	if (f & INI_CHAT) signal (SIGCHAT, syschat);
	else signal (SIGCHAT, SIG_IGN);

#if 0
	pass = getpwnam (BBSUSERNAME);
	if (pass == NULL) {
		error_fatal ("User " BBSUSERNAME " is not in /etc/passwd!");
	}

	bbs_uid = pass->pw_uid;
	bbs_gid = pass->pw_gid;
#endif

	if ((s = getenv ("BBSUID")) == NULL) {
		error_fatal ("Environment improperly set. The rc.bbs script is broken.");
	} else bbs_uid = atoi (s);

	if ((s = getenv ("BBSGID")) == NULL) {
		error_fatal ("Environment improperly set. The rc.bbs script is broken.");
	} else bbs_gid = atoi (s);
}


void
mod_done (uint32 services)
{
	long    i = initialised & services;

	if (i & INI_INPUT)
		inp_done ();
	if (i & INI_OUTPUT)
		out_done ();
	if (i & INI_USER)
		saveuser ();
	if (i & INI_SYSVARS)
		savesysvars ();
	initialised &= ~i;
}


void
mod_end ()
{
	mod_done (INI_ALL);
}


void
catchsig ()
{
	channel_hangup ();
	exit (1);
}


void
endchat ()
{
	void    sigchat ();

	thisuseronl.flags &= ~(OLF_BUSY | OLF_NOTIMEOUT | OLF_INSYSCHAT);
	msg_set (msg_sys);
	prompt (CHATEND);
	msg_set (chatmsg);
	inp_setflags (INF_REPROMPT);
	signal (SIGCHAT, syschat);
}


void
syschat ()
{
	thisuseronl.flags |= OLF_BUSY | OLF_NOTIMEOUT | OLF_INSYSCHAT;
	chatmsg = msg_cur;
	msg_set (msg_sys);
	inp_clearflags (INF_REPROMPT);
	prompt (CHATBEG);
	signal (SIGCHAT, endchat);

	while (!inp_reprompt ()) {
		char    c;

		usleep (20000);
		if (read (fileno (stdin), &c, 1) == 1) {
			if (c == 8 || c == 127) {
				char    del[3] = "\010 \010";

				out_send (fileno (stdout), del, 3);
			} else
				out_send (fileno (stdout), &c, 1);
		}
	}

	{
		char    fname[256], command[256];
		FILE   *fp;

		sprintf (fname, "%s/.emu-%s", mkfname (EMULOGDIR),
			 getenv ("CHANNEL"));
		if ((fp = fopen (fname, "w")) == NULL)
			return;
		fcntl (fileno (fp), F_SETFL,
		       fcntl (fileno (fp), F_GETFL) | O_NONBLOCK);
		fprintf (fp, "\n");
		fclose (fp);
		if (!getuid () || !getgid ()) {
			chown (fname, bbs_uid, bbs_gid);
		}
	}
}


void
mod_regpid (char *tty)
{
	FILE   *fp;
	char    fname[256];
	char    command[256];

	if (tty == NULL || !tty[0] || !strcmp (tty, "(null)"))
		return;
	sprintf (fname, "%s/register-%s", mkfname (BBSRUNDIR), tty);
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Can't open %s for writing.", fname);
	}
	fprintf (fp, "%d", (int) getpid ());
	fclose (fp);
	if (!getuid () || !getgid ()) chown (fname, bbs_uid, bbs_gid);
	chmod (fname, 0660);
}


#define MODULE_ID \
_("Megistos BBS\n\n"\
  "Module:  %s (%s)\n"\
  "Author:  %s\n"\
  "Version: %s\n"\
  "RCS ID:  %s\n"\
  "Library: %s\n\n%s\n\n")

#define MODULE_HANDLER _("\t--%-20s %s\n")


static int
mod_info ()
{
	fprintf (stderr, MODULE_ID,
		 __module.name, __module.progname,
		 __module.author,
		 __module.shortversion,
		 __module.version, bbs_shortversion, __module.descr);
	return 0;
}


static int
mod_syntax ()
{
	fprintf (stderr, _("Syntax: %s command module_options\n\n"
			   "Where command is one of:\n"), __module.progname);

	if (__module.login.handler)
		fprintf (stderr, MODULE_HANDLER,
			 "login", _("User login handler"));
	if (__module.run.handler)
		fprintf (stderr, MODULE_HANDLER,
			 "run", _("User-interactive handler"));
	if (__module.logout.handler)
		fprintf (stderr, MODULE_HANDLER,
			 "logout", _("User logout handler"));
	if (__module.hangup.handler)
		fprintf (stderr, MODULE_HANDLER,
			 "hangup", _("User hangup handler"));
	if (__module.cleanup.handler)
		fprintf (stderr, MODULE_HANDLER,
			 "cleanup", _("Cleanup handler"));
	if (__module.userdel.handler)
		fprintf (stderr, MODULE_HANDLER,
			 "userdel", _("User deletion handler"));

	fprintf (stderr, MODULE_HANDLER, "help", _("You're reading it"));
	fprintf (stderr, MODULE_HANDLER, "install",
		 _("Issues installation symlink information"));
#if 0
	fprintf (stderr, MODULE_HANDLER, "uninstall",
		 _("Issues uninstall script"));
#endif
	fprintf (stderr, MODULE_HANDLER, "info",
		 _("Module version and information"));
	fprintf (stderr, "\n");
	return 1;
}


#define MOD_INSTALL_HANDLER(x) \
if(__module.x.handler){ \
/*  printf("mkdir -p -m 0750 %s/%s;\n",mkfname(BBSMODULEDIR),#x); \ */ \
/*  printf("ln -sf %s/%s ",mkfname(MODULEDIR),__module.progname);\ */ \
  printf("create: %s/%02d_%s\n",\
         /*mkfname(BBSMODULEDIR),*/ #x,__module.x.priority,__module.progname); \
}


#if 0
static void
mod_uninstall ()
{
	printf ("execute: rm -f %s/*/*_%s;\n", mkfname (BBSMODULEDIR),
		__module.progname);
}
#endif


static void
mod_install ()
{
	/*mod_uninstall ();*/
	MOD_INSTALL_HANDLER (login);
	MOD_INSTALL_HANDLER (run);
	MOD_INSTALL_HANDLER (logout);
	MOD_INSTALL_HANDLER (hangup);
	MOD_INSTALL_HANDLER (cleanup);
	MOD_INSTALL_HANDLER (userdel);
}


int
mod_main (int argc, char **argv)
{

#ifdef HAVE_SETLOCALE
	/* Set locale via LC_ALL.  */
	setlocale (LC_ALL, "");
#endif
	
#if ENABLE_NLS
	/* Set the text message domain.  */
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
#endif

	error_setnotify (0);

	/* Check the validity of the module information block */

	if (__module.progname == NULL || (strlen (__module.progname) == 0)) {
		error_fatal ("Module lacks program name field in mod_info_t");
	}
	if (__module.name == NULL || (strlen (__module.name) == 0)) {
		error_fatal ("Module lacks full name field in mod_info_t");
	}
	if (__module.author == NULL || (strlen (__module.author) == 0)) {
		error_fatal ("Module lacks author field in mod_info_t");
	}
	if (__module.descr == NULL || (strlen (__module.descr) == 0)) {
		error_fatal ("Module lacks description field in mod_info_t");
	}
	if (__module.version == NULL || (strlen (__module.version) == 0)) {
		error_fatal ("Module lacks version field in mod_info_t");
	}
	if (__module.shortversion == NULL ||
	    (strlen (__module.shortversion) == 0)) {
		error_fatal ("Module lacks short version field in mod_info_t");
	}


	/* Good, now do some work. */

	if (argc >= 3) {
		if ((strcmp (argv[1], "--userdel") == 0) &&
		    (__module.userdel.handler != NULL))
			return (*(__module.userdel.handler)) (argc, argv);
	}
	if (argc >= 2) {
		if (strcmp (argv[1], "--help") == 0)
			return mod_syntax (), 0;
		if (strcmp (argv[1], "--info") == 0)
			return mod_info (), 0;
		if (strcmp (argv[1], "--install") == 0)
			return mod_install (), 0;
#if 0
		if (strcmp (argv[1], "--uninstall") == 0)
			return mod_uninstall (), 0;
#endif

		if ((strcmp (argv[1], "--login") == 0) &&
		    (__module.login.handler != NULL))
			return (*(__module.login.handler)) (argc, argv);

		if ((strcmp (argv[1], "--run") == 0) &&
		    (__module.run.handler != NULL))
			return (*(__module.run.handler)) (argc, argv);

		if ((strcmp (argv[1], "--logout") == 0) &&
		    (__module.logout.handler != NULL))
			return (*(__module.logout.handler)) (argc, argv);

		if ((strcmp (argv[1], "--hangup") == 0) &&
		    (__module.hangup.handler != NULL))
			return (*(__module.hangup.handler)) (argc, argv);

		if ((strcmp (argv[1], "--cleanup") == 0) &&
		    (__module.cleanup.handler != NULL))
			return (*(__module.cleanup.handler)) (argc, argv);
	}

	return mod_syntax ();
}
