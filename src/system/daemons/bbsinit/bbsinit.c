/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsinit.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  BBS watchdog daemon.                                         **
 **  NOTES:    Purposes:                                                    **
 **              * Makes sure all daemons are running properly. If any      **
 **                exit (because of error or [in bbsd's case] a need for    **
 **                refresh (to clear any memory leaks), bbsinit restarts    **
 **                the daemon. If bbsd dies, we kill *all* daemons and      **
 **                restart them.                                            **
 **                                                                         **
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
 * $Id: bbsinit.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: bbsinit.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.7  2004/05/03 05:41:34  alexios
 * Additions to the debug code (e.g. no forking()).
 *
 * Revision 1.6  2004/02/29 18:27:57  alexios
 * Various changes to account for new directory structure.
 *
 * Revision 1.5  2003/12/22 16:18:54  alexios
 * Beautified code with megistos-config --oh. Fixed #includes and rcsinfo.
 *
 * Revision 1.4  2003/09/30 14:58:59  alexios
 * Brought over to new build structure.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  2000/01/06 11:44:10  alexios
 * Corrected name of rpc.metabbs PID lock file.
 *
 * Revision 1.0  1999/08/07 02:22:10  alexios
 * Initial revision
 *
 *
 */


static const char rcsinit[] = "$Id: bbsinit.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";


/*#define DEBUG_*/


#define WANT_PWD_H 1
#define WANT_SYS_WAIT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_WAIT_H 1
#define WANT_IOCTL_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#include <megistos/bbsinclude.h>
#include <megistos/bbs.h>


int     bbsuid, bbsgid;
char   *progname;



static void
getpwbbs ()
{
	char *s;

	if ((s = getenv ("BBSUID")) == NULL) {
		error_fatal ("Environment improperly set. The rc.bbs script is broken.");
	} else bbsuid = atoi (s);

	if ((s = getenv ("BBSGID")) == NULL) {
		error_fatal ("Environment improperly set. The rc.bbs script is broken.");
	} else bbsgid = atoi (s);
}


static void
storepid ()
{
	char fname [512];
	FILE   *fp;

	strncpy (fname, mkfname (BBSRUNDIR "/bbsinit.pid"), sizeof (fname));
	
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Unable to open %s for writing.", fname);
		exit (1);
	}
	fprintf (fp, "%d", getpid ());
	fclose (fp);
	chmod (fname, 0600);
	chown (fname, 0, 0);
}


struct daemon {
	char   *name;
	char   *binary;
	char   *pidfile;
	int     ismaster;
	int     pid;
};


#define d(x,y,z) {x,BINDIR"/"x,BBSRUNDIR"/"x".pid",y,z}

struct daemon daemons[] = {
#ifdef HAVE_METABBS
	{"rpc.metabbs", DAEMONDIR "/rpc.metabbs", BBSRUNDIR "/rpc.metabbs.pid", 0, 0},
#endif /* HAVE_METABBS */
	{"bbslockd", DAEMONDIR "/bbslockd", BBSRUNDIR "/bbslockd.pid", 0, 0},
	{"bbsd", DAEMONDIR "/bbsd", BBSRUNDIR "/bbsd.pid", 1, 0},
	{"statd", DAEMONDIR "/statd", BBSRUNDIR "/statd.pid", 0, 0},
	{"msgd", DAEMONDIR "/msgd", BBSRUNDIR "/msgd.pid", 0, 0},
	{"", "", "", 0, 0}
};


void
murder_spree ()
{
	int     i;

	for (i = 0; daemons[i].name[0]; i++) {
		if (daemons[i].pid > 1) {
			register int pid = daemons[i].pid;

			kill (pid, SIGTERM);
			kill (-pid, SIGTERM);
		}
	}
	sleep (3);
	for (i = 0; daemons[i].name[0]; i++) {
		if (daemons[i].pid > 1) {
			register int pid = daemons[i].pid;

			kill (pid, SIGKILL);
			kill (-pid, SIGKILL);
		}
	}
}


static void
mainloop ()
{
	int     i, pid, status;

	for (;;) {
#ifdef DEBUG_
		fprintf (stderr, "bbsinit: in main loop...\n");
#endif


		/* Check if any daemons have died */

		for (i = 0; daemons[i].name[0]; i++) {
			int     fd;
			char    spid[80];

			if ((fd =
			     open (mkfname (daemons[i].pidfile),
				   O_RDONLY)) < 0)
				continue;
			bzero (spid, sizeof (spid));
			read (fd, spid, sizeof (spid) - 1);
			close (fd);

			if ((pid = atoi (spid)) > 1) {
				if (!kill (pid, 0))
					continue;

#ifdef DEBUG_
				fprintf (stderr,
					 "bbsinit: daemon %s (pid %d) died.\n",
					 daemons[i].name, pid);
#endif
				daemons[i].pid = 0;
				if (daemons[i].ismaster)
					murder_spree ();

			}
		}


		/* (Re)spawn any dead daemons */

		for (i = 0; daemons[i].name[0]; i++) {

			/* Is the daemon dead? */

			if (daemons[i].pid == 0) {
				int     pid;
				char    fname [1024];

				strncpy (fname, mkfname (daemons [i].binary), sizeof (fname));

#ifdef DEBUG_
				fprintf (stderr, "bbsinit: spawning %s (%s).\n",
					 daemons[i].name, fname);
#endif

				switch (pid = fork ()) {
				case -1:
					error_logsys
					    ("Unable to fork() while spawning daemon %s",
					     daemons[i].name);
					break;
				case 0:
					/* argument 2 is a full pathname on purpose. It helps
					   in killing off the daemons later on. */

					execl (fname, fname, NULL);
					error_fatalsys
					    ("Unable to spawn daemon %s (%s)",
					     daemons[i].name, fname);
					break;
				default:
					daemons[i].pid = pid;
				}

				sleep (1);
				waitpid (pid, &status, 0);
			}
		}


		/* Sleep for a bit. */

		sleep (5);
	}
}


static void
checkuid ()
{
	if (getuid ()) {
		fprintf (stderr, "%s: getuid: not super-user\n", progname);
		exit (1);
	}
}


static void
forkdaemon ()
{

#ifndef DEBUG_
	pid_t pid = fork ();
#else
	pid_t pid = 0;
#endif /* DEBUG_ */

	switch (pid) {
	case -1:
		fprintf (stderr, "%s: fork: unable to fork daemon\n",
			 progname);
		exit (1);

	case 0:
		ioctl (0, TIOCNOTTY, NULL);
		setsid ();

		/* Some of these are merely wishful thinking, of course. */
		
#if 1
		signal (SIGHUP, SIG_IGN);
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGILL, SIG_IGN);
		signal (SIGTRAP, SIG_IGN);
		signal (SIGIOT, SIG_IGN);
		signal (SIGBUS, SIG_IGN);
		signal (SIGFPE, SIG_IGN);
		signal (SIGUSR1, SIG_IGN);
		signal (SIGSEGV, SIG_IGN);
		signal (SIGUSR2, SIG_IGN);
		signal (SIGUSR2, SIG_IGN);
		signal (SIGPIPE, SIG_IGN);
		signal (SIGALRM, SIG_IGN);
		signal (SIGTERM, SIG_IGN);
		/*  signal(SIGCHLD,SIG_IGN); */
		signal (SIGCONT, SIG_IGN);
		signal (SIGSTOP, SIG_IGN);
#endif

#ifndef DEBUG_

		/* These are ifdeffed out because of an insiduous daemonic bug
		   involving file descriptors. */

		close (0);
		close (1);
		close (2);
#endif /* DEBUG_ */
		break;

	default:
		exit (0);
	}
}


int
main (int argc, char *argv[])
{
	progname = argv[0];
	mod_setprogname (argv[0]);
	setenv ("CHANNEL", "[bbsinit]", 1);

	checkuid ();		/* Make sure the superuser is running us */
	forkdaemon ();		/* Fork() the daemon */
	getpwbbs ();		/* Get the /etc/passwd entry user 'bbs' */
	storepid ();		/* Store the daemon's PID */
	mainloop ();		/* Finally, run the daemon's main loop */

	return 0;
}
