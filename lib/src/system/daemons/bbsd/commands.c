/*****************************************************************************\
 **                                                                         **
 **  FILE:     commands.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997                                               **
 **  PURPOSE:  Processing commands from the bbsd FIFO                       **
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
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2004/02/29 18:25:30  alexios
 * Ran through megistos-config --oh. Various minor changes to account for
 * new directory structure.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/07/18 22:00:00  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Added MetaBBS
 * daemon support.
 *
 * Revision 0.7  1998/12/27 16:21:05  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 0.6  1998/07/26 21:11:32  alexios
 * No changes.
 *
 * Revision 0.5  1998/07/24 10:25:55  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:04:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/05 11:06:30  alexios
 * Added relogon command and fixed a slight forking problem.
 *
 * Revision 0.2  1997/09/14 13:52:46  alexios
 * Commented out and removed various calls to fork() and exit()
 * that were causing infinite forking with highly undesirable
 * results on the system (argh argh).
 *
 * Revision 0.1  1997/08/30 13:10:43  alexios
 * Initial revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_SIGNAL_H 1
#define WANT_PWD_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIO_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mbk_sysvar.h>
#include "bbsd.h"


struct cmd {
	char   *name;
	void    (*handler) (int chan, char *tty, char *arg);
};


static void
cmd_getty (int chan, char *tty, char *arg)
{
	/* Connect a process ID with a channel (only telnet channels) */

	if (gettys[chan].flags & TTF_TELNET) {
		gettys[chan].pid = atoi (arg);
		gettys[chan].user[0] = 0;
	}
#ifdef HAVE_METABBS
	/* Hm, our line count has possibly changed */
	last_registration_time = 0;
#endif
}


static void
cmd_connect (int chan, char *tty, char *arg)
{
	int     shmid;

	/* Make sure there's a process running for the channel */

	if (gettys[chan].pid <= 0) {
		error_log
		    ("processcmd(): can't connect user before spawning getty");
		return;
	}

	/* Kill any previously connected user (e.g. relogon) */

	if (gettys[chan].user[0]) {
		killshm (gettys[chan].user, gettys[chan].shmid);
		asapevents ();
	}

	/* Make shared memory segment for new user */

	if ((shmid = makeshm (arg)) >= 0) {
		strcpy (gettys[chan].user, arg);
		gettys[chan].shmid = shmid;

#ifdef DEBUG
		fprintf (stderr, "userid for %s is now (%s)\n",
			 gettys[chan].ttyname, gettys[chan].user);
#endif

	}
#ifdef HAVE_METABBS
	/* Hm, our line count has possibly changed */
	last_registration_time = 0;
#endif
}


static void
cmd_hangup (int chan, char *tty, char *arg)
{
	/* Hangup a user */

	/*  if(fork())return; */

	arg = arg;		/* Gets rid of warning */
	if (!gettys[chan].pid)
		return;
	kill (-gettys[chan].pid, SIGHUP);
	sleep (1);
	kill (-gettys[chan].pid, SIGTERM);
	sleep (1);
	kill (-gettys[chan].pid, SIGKILL);
	/*  exit(0); */
}


static void
cmd_delete (int chan, char *tty, char *arg)
{
	/* Hangup and then delete a user */

	int     kicked = 0;
	char    fname[256];
	struct stat st;

	if (fork ())
		return;

	sprintf (fname, "%s/.shmid-%s", mkfname (ONLINEDIR), arg);

	while (!stat (fname, &st)) {
		if (!kicked) {
			for (chan = 0; chan < chan_count; chan++) {
				if (!strcmp (gettys[chan].user, arg)) {
					cmd_hangup (chan, gettys[chan].ttyname,
						    "");
				}
			}
		}
		sleep (1);
		kicked++;
		if (kicked > 5) {
			error_log
			    ("cmd_delete(): timed out waiting to hangup user %s.",
			     arg);
			exit (0);
		}
	}

	chdir (mkfname (BINDIR));
	{
		char    command[256];

		sprintf (command, "%s %s", mkfname (USERDELBIN), arg);
		setenv ("PREFIX", mkfname (""), 1);
		setenv ("BBSPREFIX", mkfname (""), 1);
		execl ("/bin/sh", "sh", "-c", command, NULL);
		error_logsys ("failed to execl() %s", command);
	}
	exit (1);
}


void
cmd_chat (int chan, char *tty, char *arg)
{
	FILE   *fp;
	char    s[256];
	int     pid;

	/*  if(fork())return; */

	sprintf (s, "%s/register-%s", mkfname (BBSRUNDIR), tty);
	if ((fp = fopen (s, "r")) == NULL) {
		error_logsys ("cmd_chat(): Unable to open %s", s);
		/*    exit(0); */
		return;
	}
	if (!fgets (s, sizeof (s), fp)) {
		error_logsys ("cmd_chat(): Unable to read %s", s);
		fclose (fp);
		/*    exit(0); */
		return;
	}
	fclose (fp);
	if (sscanf (s, "%d", &pid) != 1) {
		error_logsys ("cmd_chat(): Unable to scan %s", s);
		/*    exit(0); */
		return;
	}

	kill (pid, SIGCHAT);
	/*  exit(0); */
}


void
cmd_user2 (int chan, char *tty, char *arg)
{
	FILE   *fp;
	char    s[256];
	int     pid;

	/*  if(fork())return; */

	sprintf (s, "%s/register-%s", mkfname (BBSRUNDIR), tty);
	if ((fp = fopen (s, "r")) == NULL) {
		error_logsys ("cmd_chat(): Unable to open %s", s);
		/*    exit(0); */
		return;
	}
	if (!fgets (s, sizeof (s), fp)) {
		error_logsys ("cmd_chat(): Unable to read %s", s);
		fclose (fp);
		/*    exit(0); */
		return;
	}
	fclose (fp);
	if (sscanf (s, "%d", &pid) != 1) {
		error_logsys ("cmd_chat(): Unable to scan %s", s);
		/*    exit(0); */
		return;
	}

	kill (pid, SIGMAIN);
	/*  exit(0); */
}


static void
changeline (int chan, char *tty, int state,
	    int result, int baud, char *user, int hangup)
{
	channel_status_t status;

	bzero (&status, sizeof (status));
	status.state = state;
	status.result = result;
	status.baud = baud;
	strcpy (status.user, user);
	channel_setstatus (tty, &status);
	if (hangup)
		cmd_hangup (chan, tty, "");
}


void
cmd_change (int chan, char *tty, char *arg)
{
	int     i, res, state;
	channel_status_t status;

	state = LST_NORMAL;
	for (i = 0; i < LST_NUMSTATES; i++) {
		if (sameas (arg, channel_states[i])) {
			state = i;
			break;
		}
	}
	if (gettys[chan].flags & TTF_TELNET) {
		for (i = 0; i < chan_count; i++) {
			res = channel_getstatus (gettys[i].ttyname, &status);
			if ((status.result == LSR_OK || res < 0) &&
			    (channels[i].flags & TTF_TELNET)) {
				changeline (i, gettys[i].ttyname, state,
					    status.result, status.baud,
					    status.user, 1);
			}
		}
	} else {
		res = channel_getstatus (gettys[chan].ttyname, &status);
		changeline (chan, gettys[chan].ttyname, state, status.result,
			    status.baud, status.user, 1);
	}

#ifdef HAVE_METABBS
	/* Hm, our line count has possibly changed */
	last_registration_time = 0;
#endif
}


void
cmd_nchang (int chan, char *tty, char *arg)
{
	int     i, res, state;
	channel_status_t status;

	state = LST_NORMAL;
	for (i = 0; i < LST_NUMSTATES; i++) {
		if (sameas (arg, channel_states[i])) {
			state = i;
			break;
		}
	}
	if (gettys[chan].flags & TTF_TELNET) {
		for (i = 0; i < chan_count; i++) {
			res = channel_getstatus (gettys[i].ttyname, &status);
			if ((status.result == LSR_OK || res < 0) &&
			    (channels[i].flags & TTF_TELNET)) {
				changeline (i, gettys[i].ttyname, state,
					    status.result, status.baud,
					    status.user, 0);
			}
		}
	} else {
		res = channel_getstatus (gettys[chan].ttyname, &status);
		changeline (chan, gettys[chan].ttyname, state, status.result,
			    status.baud, status.user, 0);
	}

#ifdef HAVE_METABBS
	/* Hm, our line count has possibly changed */
	last_registration_time = 0;
#endif
}


void
cmd_event (int chan, char *tty, char *arg)
{
	struct event event;
	FILE   *fp;
	char    s[256];

	/*  if(fork())return; */

	bzero (&event, sizeof (event));
	sprintf (s, "%s/%s", mkfname (EVENTDIR), arg);
	if ((fp = fopen (s, "r")) == NULL)
		return;
	fread (&event, sizeof (event), 1, fp);
	fclose (fp);
	unlink (s);
	eventexec (event.command, arg);
}


void
cmd_relogon (int chan, char *tty, char *arg)
{
	if (gettys[chan].user[0]) {
		killshm (gettys[chan].user, gettys[chan].shmid);
		gettys[chan].user[0] = 0;
	}
#ifdef HAVE_METABBS
	/* Hm, our line count has possibly changed */
	last_registration_time = 0;
#endif
}


static struct cmd cmds[] = {
	{"getty", cmd_getty},
	{"connect", cmd_connect},
	{"relogon", cmd_relogon},
	{"hangup", cmd_hangup},
	{"delete", cmd_delete},
	{"chat", cmd_chat},
	{"user2", cmd_user2},
	{"change", cmd_change},
	{"nchang", cmd_nchang},
	{"event", cmd_event},
	{"-", NULL}
};


static void
processcmd (char *buf)
{
	char    keyword[32], tty[32], arg[32], *cp;
	int     chan, i, found = 0;

	for (cp = strtok (buf, "\n"); cp; cp = strtok (NULL, "\n")) {
		if (sscanf (cp, "%s %s %s", keyword, tty, arg) != 3)
			return;

		chan = chan_getindex (tty);
		if (chan < 0 && strcmp (tty, "-")) {
			error_log ("processcmd(): %s is not a BBS channel",
				   tty);
			return;
		}
#ifdef DEBUG
		fprintf (stderr, "received command: %s %s %s\n", keyword, tty,
			 arg);
#endif

		for (found = i = 0; strcmp (cmds[i].name, "-"); i++) {
			if (!strcmp (cmds[i].name, keyword)) {
				(*cmds[i].handler) (chan, tty, arg);
				found = 1;
				break;
			}
		}

		if (!found) {
			error_log ("processcmd(): unknown command: %s", buf);
			continue;
		}
	}
}


void
processcommands (int fd)
{
	int     n;
	char    buf[1024];

	do {
		bzero (buf, sizeof (buf));
		n = read (fd, buf, sizeof (buf));

		if (n < 0) {
			error_log ("Error reading from pipe, errno=%d", errno);
		} else if (n == sizeof (buf)) {
			error_log ("Possible command buffer overrun.");
		} else if (n > 0) {
			processcmd (buf);
		}
	} while (n > 0);
}


/* End of File */
