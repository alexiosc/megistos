/*****************************************************************************\
 **                                                                         **
 **  FILE:     respawn.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997                                               **
 **  PURPOSE:  Respawn BBS gettys, just like init(8) does                   **
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
 * $Id: respawn.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: respawn.c,v $
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
 * Revision 0.7  1999/07/18 22:00:00  alexios
 * Paranoia additions to prevent premature death of bbsd.
 *
 * Revision 0.6  1998/12/27 16:21:05  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/07/26 21:11:32  alexios
 * No changes.
 *
 * Revision 0.4  1998/07/24 10:25:55  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:04:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/01 10:33:34  alexios
 * Fixed waitforattached() so that it reflects the bug fixes in
 * waitforchildren() (since the former is a copy of the latter,
 * complete with bugs).
 *
 * Revision 0.1  1997/08/30 13:10:43  alexios
 * Initial revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: respawn.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";


#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_SIGNAL_H 1
#define WANT_PWD_H 1
#define WANT_TIME_H 1
#define WANT_WAIT_H 1
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
#include <mbk/mbk_sysvar.h>
#include "bbsd.h"


static int bbslockd_pid = 0;


void
spawn (struct getty *g)
{
	int     pid;

#ifdef DEBUG
	fprintf (stderr, "spawning getty for %s\n", g->ttyname);
#endif

	switch (pid = fork ()) {
	case -1:
		error_logsys ("Unable to fork() while spawning getty");
		return;
	case 0:
		break;
	default:
		g->pid = pid;
		g->user[0] = 0;
		return;
	}

	/* Only the child reaches this point -- spawn a bbsgetty */

	execl (mkfname (BINDIR "/" BBSGETTY), BBSGETTY, g->ttyname, NULL);
}


static void
spawnfresh ()
{
	int     i;

	for (i = 0; i < chan_count; i++) {
		int     t = time (NULL);

		/* We don't spawn telnet channels */

		if (gettys[i].flags & TTF_TELNET)
			continue;

		/* Is the channel disabled? */

		if ((t - gettys[i].disabled) < DISABLETIME)
			continue;
		gettys[i].disabled = 0;

		/* If there's no such child yet, spawn one */

		if (!gettys[i].pid)
			spawn (&gettys[i]);
	}
}



/* Kill all our child processes and any getty processes attached. Just
   to be sure, commit suicide too (this is only used when exiting for
   a refresh by the init/watchdog daemon (bbsinitd). */

void
sepuku ()
{
	int     i;

	for (i = 0; i < chan_count; i++) {
		if (gettys[i].pid > 1) {
			kill (gettys[i].pid, SIGTERM);
			kill (-gettys[i].pid, SIGTERM);	/* Better yet, kill the entire pgrp */
		}
	}

	sleep (2);

	for (i = 0; i < chan_count; i++) {
		if (gettys[i].pid > 1) {
			kill (gettys[i].pid, SIGKILL);
			kill (-gettys[i].pid, SIGKILL);	/* Better yet, kill the entire pgrp */
		}
	}

	sleep (2);

	kill (-getpid (), SIGKILL);
	kill (-getpid (), SIGTERM);
	kill (getpid (), SIGKILL);
	kill (getpid (), SIGTERM);
}


static void
waitforchildren ()
{
	int     i, status, pid;

	do {
		pid = waitpid (-1, &status, WNOHANG);

		if (pid < 0) {
			/*      error_log("waitpid() returns error (errno=%d).",errno); */
		} else if (pid == 0)
			break;

		if (pid == bbslockd_pid) {
			bbslockd_pid = 0;
			return;
		}

		for (i = 0; i < chan_count; i++) {
			if (gettys[i].pid == pid) {
				if (gettys[i].user[0]) {
#ifdef DEBUG
					fprintf (stderr,
						 "killing %d, tty=%s, userid=(%s)\n",
						 pid, gettys[i].ttyname,
						 gettys[i].user);
#endif
					killshm (gettys[i].user,
						 gettys[i].shmid);
					asapevents ();
				}
				gettys[i].pid = 0;
				gettys[i].user[0] = 0;
				gettys[i].spawncount++;
				if (gettys[i].spawncount >= MAXCOUNT) {
					gettys[i].disabled = time (NULL);
					error_log
					    ("bbsgetty on %s respawning too fast; disabled for %d secs",
					     gettys[i].ttyname, DISABLETIME);
				}
			}
		}
	} while (pid > 0);
}


static void
waitforattached ()
{
	int     i;
	char    fname[256];
	struct stat st;

	for (i = 0; i < chan_count; i++) {

		if (!(gettys[i].flags & TTF_TELNET))
			continue;
		if (!gettys[i].pid)
			continue;
		sprintf (fname, PROCDIR "/%d", gettys[i].pid);
#ifdef DEBUG
		fprintf (stderr, "Checking attached process %d (%s)\n",
			 gettys[i].pid, fname);
#endif
		if (!stat (fname, &st))
			continue;

		/* The channel had a controlling process, but it's gone now */

		if (gettys[i].user[0]) {
#ifdef DEBUG
			fprintf (stderr,
				 "killing attached %d, tty=%s, userid=(%s)\n",
				 gettys[i].pid, gettys[i].ttyname,
				 gettys[i].user);
#endif
			killshm (gettys[i].user, gettys[i].shmid);
			asapevents ();
		}
		gettys[i].pid = 0;
		gettys[i].user[0] = 0;
		gettys[i].spawncount++;
		if (gettys[i].spawncount >= MAXCOUNT) {
			gettys[i].disabled = time (NULL);
			error_log
			    ("bbsgetty on %s respawning too fast; disabled for %d secs",
			     gettys[i].ttyname, DISABLETIME);
		}
	}
}


void
respawn ()
{
	/* Spawn any fresh gettys */
	spawnfresh ();

	/* Wait() in case any children have finished */

	waitforchildren ();
	waitforattached ();
}


void
resetcounts ()
{
	int     i;

	for (i = 0; i < chan_count; i++)
		gettys[i].spawncount = 0;
}


/* End of File */
