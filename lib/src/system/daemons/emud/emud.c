/*****************************************************************************\
 **                                                                         **
 **  FILE:     emud (orig. ttysnoops)                                       **
 **  AUTHORS:  Alexios (hack only)                                          **
 **  REVISION: B, February 95                                               **
 **  PURPOSE:  The new emulation daemon                                     **
 **  NOTES:    This is based on ttysnoop 0.12 alpha by Carl Declerck.       **
 **            Ttysnoop copyrights etc belong to the author.                **
 **                                                                         **
 **            Emud uses a pseudo-tty to emulate a user session. It must    **
 **            be run by the super-user, for obvious reasons of security.   **
 **            Once it forks, it spawns bbslogin. Hence it's execl()'d by   **
 **            bbsgetty to handle the line once a connection is made.       **
 **                                                                         **
 **            All the output sent to the user is logged in                 **
 **            /bbs/etc/.log-tty*. A FIFO (/bbs/etc/.emu-tty*) is provided  **
 **            for emulating the user's input (writing to the FIFO has the  **
 **            same effect as the user typing at their keyboard). The PID   **
 **            of the daemon is stored in /bbs/etc/.emud-tty*.pid.          **
 **                                                                         **
 **            Environment variables passed on: CHANNEL contains the tty    **
 **            where the user logged from (without the "/dev/" string).     **
 **            EMUINP contains the pseudo-tty used by the daemon. EMUINP    **
 **            is also the controlling tty of all subsequent processes.     **
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
 * $Id$
 *
 * $Log$
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.8  2004/05/21 23:53:42  alexios
 * Fixed permissions problem that led to user emulation failing.
 *
 * Revision 1.7  2004/05/21 20:08:23  alexios
 * Removed system(3) command to call mkfifo(1), replaced it with the
 * mkfifo(3) function. Also, removed hardwired, system(3)-based chown
 * operation to bbs.bbs in favour of using the chown(2) system call and
 * the appropriate BBS instance UID and GIDs. This may fix serious
 * permission-related bugs.
 *
 * Revision 1.6  2004/05/03 05:42:49  alexios
 * Added code to differentiate between SSH and telnet connections and
 * apply the appropriate timeout to each.
 *
 * Revision 1.5  2004/02/29 16:35:16  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.4  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.11  2000/01/06 11:44:46  alexios
 * Slight corrections to one comment. Reduced the buffer size from
 * 16000 bytes to 8181 (+1) bytes. The extra buffer size is not
 * needed and, after all, buffer size was not at all related to
 * the overruns experienced during non-blocking I/O.
 *
 * Revision 1.10  1999/08/13 17:06:35  alexios
 * Emud now checks for line timeouts in telnet lines. In the
 * future, it may be extended to handle all timeouts, too.
 *
 * Revision 1.9  1999/07/28 23:15:19  alexios
 * Fixed POSIX incompatibility problem.
 *
 * Revision 1.8  1999/07/18 22:03:34  alexios
 * Added debugging info (#ifdef'ed out). Minor fixes and
 * cosmetic changes.
 *
 * Revision 1.7  1998/12/27 16:27:54  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Other minor fixes.
 *
 * Revision 1.6  1998/08/14 11:59:29  alexios
 * Reduced the buffer size to one page (4k). Everything seems
 * to work ok now.
 *
 * Revision 1.5  1998/07/26 21:13:52  alexios
 * Moved emud to stable status.
 *
 * Revision 1.4  1998/07/24 10:27:20  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.3  1998/03/10 10:17:42  alexios
 * Added keyboard translation (reverse translation to that used
 * for outputting stuff to the user). Rearranged receiving and
 * transmitting a bit, so that each end gets data in the right
 * encoding. Changed an occurence of "/bbs/bin" to BINDIR.
 *
 * Revision 1.2  1997/11/06 20:16:19  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/11/03 00:48:51  alexios
 * Trimmed includes so that we don't read in useless header files.
 * Beautified code a bit. Added a few comments. Added code to read
 * in translation tables from disk using function readxlation().
 * Added code to translate text on the fly for both user and
 * any emulating operators.
 *
 * Revision 1.0  1997/09/14 18:35:09  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


/*
	ttysnoops.c
	
	ttysnoops sets up a pseudo-tty for the specified program and
	redirects its stdin/stdout/stderr to/from the current ctty 
	and a specified snoop device (usually another tty or a socket)
	
	v0.00	4-1-94 Carl Declerck	- first version
	v0.01	6-1-94	     ""		- added /etc/snooptab file
	v0.02	9-1-94	     ""		- added socket support
	v0.10	8-8-94	     ""		- various bug fixes
	v0.11	9-8-94       ""		- password authentication added
	v0.11a 23-8-94 Ulrich Callmeier - shadow support hacked in
	v0.12	6-9-94 Carl Declerck	- added suspend/resume key
*/

#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STDARG_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_FCNTL_H 1
#define WANT_GRP_H 1
#define WANT_PWD_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_SOCKET_H 1
#define WANT_NETINET_IN_H 1
#define WANT_TIME_H 1
#define WANT_WAIT_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include <sys/socket.h>
#include <mbk/mbk_sysvar.h>
#include <megistos/config.h>
#include <megistos/bbs.h>


/* #define DEBUG 1 */


#define BUFF_SIZE	8191

char    buff[BUFF_SIZE + 1];

int     authpid = -1;
int     emuin = -1;
int     fdmax = 0;
int     pid;
int     idlzapt = 0;
int     via_telnet = 0;
char    ptynam[32];
char    fname[128], tty[32];
char    relogfn[256];
char    kbdxlation[NUMXLATIONS][256];
char    xlation[NUMXLATIONS][256];
struct sockaddr_in peer;
struct emuqueue *emuq;
struct stat st;


#define TTY_STORE	16

static struct termios orig_tty_state[TTY_STORE];
static int sttyfds[TTY_STORE];
int     bbsuid, bbsgid;



void
storepid ()
{
	FILE   *fp;
	char    fname[256];

	sprintf (fname, "%s/emud-%s.pid", mkfname (BBSRUNDIR), tty);
	if ((fp = fopen (fname, "w")) == NULL)
		return;
	fprintf (fp, "%d", getpid ());
	fclose (fp);
	chmod (fname, 0600);
	chown (fname, 0, 0);
}


void
notifybbsd ()
{
	FILE   *fp;

	if ((fp = fopen (mkfname (BBSDPIPEFILE), "w")) == NULL)
		return;
	fprintf (fp, "getty %s %d\n", tty, getpid ());
	fclose (fp);
}


void
errorf (char *fmt, ...)
{
	va_list args;

	va_start (args, fmt);
	fprintf (stderr, "emud: ");
	vfprintf (stderr, fmt, args);
	exit (1);
}



char   *
leafname (char *path)
{
#undef HAVE_GETPT
#ifndef HAVE_GETPT

	int     i = 0, j;

	for (j = 0; path[j]; j++)
		if (path[j] == '/')
			i = j + 1;
	return (path + i);

#else

#  error "This won't work, please fix lots of things first!"

	char   *devdir = DEVDIR "/";

	if (!strncmp (path, devdir, strlen (devdir)))
		return path + strlen (devdir);

#endif				/* HAVE_GETPT */
}



/* init the stty store array */

void
stty_initstore (void)
{
	int     i;

	for (i = 0; i < TTY_STORE; i++)
		sttyfds[i] = -1;
}

/* set tty on fd into raw mode */

int
stty_raw (int fd)
{
	struct termios tty_state;
	int     i;

	if (tcgetattr (fd, &tty_state) < 0)
		return (-1);

	for (i = 0; i < TTY_STORE; i++)
		if (sttyfds[i] == -1) {
			orig_tty_state[i] = tty_state;
			sttyfds[i] = fd;
			break;
		}

	tty_state.c_lflag &= ~(ICANON | IEXTEN | ISIG | ECHO);
	tty_state.c_iflag &= ~(ICRNL | INPCK | ISTRIP | IXON | BRKINT);
	tty_state.c_oflag &= ~OPOST;
	tty_state.c_cflag |= CS8;

	tty_state.c_cc[VMIN] = 1;
	tty_state.c_cc[VTIME] = 0;

	if (tcsetattr (fd, TCSAFLUSH, &tty_state) < 0)
		return (-1);

	return (0);
}


/* restore all altered ttys to their original state */

void
stty_orig (void)
{
	int     i;

	for (i = 0; i < TTY_STORE; i++)
		if (sttyfds[i] != -1) {
			tcsetattr (sttyfds[i], TCSAFLUSH, &orig_tty_state[i]);
			sttyfds[i] = -1;
		}
}



void
makeshm (char *tty)
{
	char    fname[256];
	FILE   *fp;
	int     shmid = 0;
	struct shmid_ds buf;
	char *s;

	if ((s = getenv ("BBSUID")) == NULL) {
		error_fatal ("Environment improperly set. The rc.bbs script is broken.");
	} else bbsuid = atoi (s);

	if ((s = getenv ("BBSGID")) == NULL) {
		error_fatal ("Environment improperly set. The rc.bbs script is broken.");
	} else bbsgid = atoi (s);


	/* Create shared memory */

	sprintf (fname, "%s/emud-%s.pid", mkfname (BBSRUNDIR), tty);
	if ((shmid =
	     shmget (ftok (fname, 'E'), 16384,
		     IPC_CREAT | IPC_EXCL | 0660)) == -1)
		return;
	sprintf (fname, "%s/.shmid-%s", mkfname (BBSETCDIR), tty);

	/* Write shared memory ID to disk */

	if ((fp = fopen (fname, "w")) == NULL)
		return;
	fprintf (fp, "%012d", shmid);
	fclose (fp);

	/* Attach to shared memory */

	if ((emuq = (struct emuqueue *) shmat (shmid, NULL, 0)) == NULL) {
		errorf ("unable to attach shared memory.\n");
	}

	/* Create the emuqueue data structure */

	bzero (emuq, sizeof (struct emuqueue));
	emuq->xlation = -1;

	/* Make the BBS instance UID and GID the owner of the shared memory
	 * block */

	if (shmctl (shmid, IPC_STAT, &buf) < 0) {
		errorf ("unable to IPC_STAT shared memory (errno=%d)", errno);
	} else {
		buf.shm_perm.uid = bbsuid;
		buf.shm_perm.gid = bbsgid;

		if (shmctl (shmid, IPC_SET, &buf) < 0) {
			errorf ("unable to IPC_SET shared memory (errno=%d)",
				errno);
		}
	}

	/* Mark the block for destruction when we're done with it. */

	shmctl (shmid, IPC_RMID, &buf);


	/* Fix file permissions */

	chown (fname, bbsuid, bbsgid);
	sprintf (fname, "%s/emud-%s.pid", mkfname (BBSRUNDIR), tty);
	chown (fname, bbsuid, bbsgid);
	chmod (fname, 0444);
}


void
gracefulexit ()
{
	char    fname[256];
	channel_status_t status;

	putchar (0);
	channel_getstatus (tty, &status);
	mod_init (INI_OUTPUT | INI_SYSVARS | INI_TTYNUM);

	sprintf (fname, "%s/%s", mkfname (ONLINEDIR), status.user);
	unlink (fname);
	sprintf (fname, "%s/[SIGNUP-%s]", mkfname (ONLINEDIR), tty);
	unlink (fname);

	sprintf (fname, "%s/_%s", mkfname (ONLINEDIR), status.user);
	close (creat (fname, 0660));

	status.baud = 0;
	status.result = LSR_LOGOUT;
	status.user[0] = 0;
	channel_setstatus (tty, &status);

	kill (-getpid (), SIGKILL);
	exit (0);
}



/* find & open a pty to be used by the pty-master */

int
find_ptyxx (char *ptyname)
{

#ifndef HAVE_GETPT

	int     fd, i, j;
	static char *s1 = "srpq", *s2 = "fedcba9876543210";

	strcpy (ptyname, DEVDIR "/ptyxx");

	for (i = 0; s1[i]; i++) {
		ptyname[8] = s1[i];

		for (j = 0; s2[j]; j++) {
			ptyname[9] = s2[j];

			if ((fd = open (ptyname, O_RDWR)) >= 0) {
				ptyname[5] = 't';
				return (fd);
			}

			if (errno == ENOENT)
				return (-1);
		}
	}

	return (-1);

#else

	int     fd = getpt ();

	if (fd >= 0)
		return fd;

#endif				/* HAVE_GETPT */

}

/* find & open a pty (tty) to be used by pty-client */

int
find_ttyxx (char *ttyname, int ptyfd)
{
	struct group *grp;
	int     gid, fd;

	if ((grp = getgrnam ("tty")) != NULL)
		gid = grp->gr_gid;
	else
		gid = -1;

	chown (ttyname, getuid (), gid);
	chmod (ttyname, S_IRUSR | S_IWUSR | S_IWGRP);

	if ((fd = open (ttyname, O_RDWR)) >= 0)
		return (fd);

	close (ptyfd);
	return (-1);
}

/* fork off the pty-client and redirect its stdin/out/err to the pty */

int
fork_pty (int *ptyfd, char *ttynam)
{
	struct termios term;
	struct winsize twin;
	int     ttyfd;
	char    name[32];

	tcgetattr (STDIN_FILENO, &term);
	ioctl (STDIN_FILENO, TIOCGWINSZ, (char *) &twin);

	if ((*ptyfd = find_ptyxx (name)) < 0)
		errorf ("No free pty.\n");

	strcpy (ttynam, leafname (name));
	setenv ("EMUPTY", ttynam, 1);

	if ((pid = fork ()) < 0)
		errorf ("Can't fork.\n");

	if (pid == 0) {		/* child */
		if (setsid () < 0)
			errorf ("setsid failed.\n");

		if ((ttyfd = find_ttyxx (name, *ptyfd)) < 0)
			errorf ("can't open tty.\n");

		close (*ptyfd);

		if (tcsetattr (ttyfd, TCSANOW, &term) < 0)
			errorf ("can't set termios.\n");

		if (ioctl (ttyfd, TIOCSWINSZ, &twin) < 0)
			errorf ("can't set winsize.\n");

		if (dup2 (ttyfd, STDIN_FILENO) != STDIN_FILENO)
			errorf ("can't dup2 into stdin.\n");

		if (dup2 (ttyfd, STDOUT_FILENO) != STDOUT_FILENO)
			errorf ("can't dup2 into stdout.\n");

		if (dup2 (ttyfd, STDERR_FILENO) != STDERR_FILENO)
			errorf ("can't dup2 into stderr.\n");

		if (ttyfd > STDERR_FILENO)
			close (ttyfd);
	}

	return (pid);
}


void
makepipe ()
{
	struct stat s;
	char    fname[256];
	char    command[256];

	sprintf (fname, "%s/.injoth-%s", mkfname (ONLINEDIR), tty);
	unlink (fname);

	sprintf (fname, "%s/.emu-%s", mkfname (EMUFIFODIR), tty);
	if (!stat (fname, &s)) return;

	if (mkfifo (fname, 0666) != 0) {
		errorf ("unable to create pipe %s: %s", fname, strerror (errno));
	}

	if (chmod (fname, 0666) != 0) {
		errorf ("unable to chmod(2) %s: %s", fname, strerror (errno));
	}

	if (chown (fname, bbs_uid, bbs_gid) != 0) {
		errorf ("unable to chown(2) %s: %s", fname, strerror (errno));
	}
}


void
readxlation ()
{
	FILE   *fp;

	if ((fp = fopen (mkfname (XLATIONFILE), "r")) == NULL) {
		int     i = errno;

		errorf ("unable to open %s (errno=%d)\n",
			mkfname (XLATIONFILE), i);
	}
	if (fread (xlation, sizeof (xlation), 1, fp) != 1) {
		int     i = errno;

		errorf ("unable to read %s (errno=%d)\n",
			mkfname (XLATIONFILE), i);
	}
	if (fread (kbdxlation, sizeof (kbdxlation), 1, fp) != 1) {
		int     i = errno;

		errorf ("unable to read %s (errno=%d)\n",
			mkfname (XLATIONFILE), i);
	}
	fclose (fp);
}


static void
inittimeout ()
{
	char * baud = getenv("BAUD");
	idlzapt = 0;
	mod_init (INI_TTYNUM);

	if ((chan_getnum (tty) >= 0) &&
	    (chan_last->flags & TTF_TELNET)) {
		promptblock_t *msg = msg_open ("sysvar");
		
		/* Is this an SSH connection? */
		
		if ((baud != NULL) && (strcmp (baud, "-1") == 0))
			idlzapt = msg_int (IDLZAPS, 0, 32767) * 60;
		
		/* No. It's a telnet connection. */
		
		else
			idlzapt = msg_int (IDLZAPT, 0, 32767) * 60;
		
		msg_close (msg);
	}

	mod_done (INI_TTYNUM);
}


/* Check if we're running on a socket (i.e. serving a telnet connection) */

static void
checktelnet ()
{
	int     len = sizeof (peer), res;

	/* Try to get information on the other end. If we fail, then we'll
	   just assume this isn't a telnet connection. */

	res = getpeername (0, &peer, &len);

	via_telnet = (res == 0);

	if (via_telnet) {
		printf ("CONNECTING THROUGH TELNET.\n\n\n\n");
		sleep (5);
	}

}



/* main program */

int
main (int argc, char *argv[])
{
	time_t  tmout = time (NULL);
	fd_set  readset;
	int     ptyfd, n, sel = 0;

	if (getuid ())
		errorf ("Only root can execute this daemon.\n");
	if (!isatty (STDIN_FILENO))
		errorf ("stdin is not a tty.\n");


	/* do init stuff */

	readxlation ();
	strcpy (tty, leafname (ttyname (STDIN_FILENO)));
	storepid ();
	makeshm (tty);
	inittimeout ();
	makepipe ();
	checktelnet ();

	setenv ("CHANNEL", tty, 1);
	setenv ("BAUD", "0", 0); /* Why is this here? */


	signal (SIGPIPE, SIG_IGN);
#if 0
	/* This is a no-no under POSIX and Linux. Look at signal(2). */
	/* signal (SIGCHLD, SIG_IGN); */
#endif
	signal (SIGHUP, gracefulexit);
	signal (SIGINT, gracefulexit);
	signal (SIGQUIT, gracefulexit);
	signal (SIGUSR1, readxlation);

	stty_initstore ();
	atexit (stty_orig);
	atexit (gracefulexit);


	/* fork off the client and load the new image */

      relogon:

	if (fork_pty (&ptyfd, ptynam) == 0) {

		/* exec the real pty-client program */

		setenv ("BBSPREFIX", mkfname (""), 1);
		setenv ("PREFIX", mkfname (""), 1);
		execl (mkfname (BINDIR "/bbslogin"), "bbslogin", "-", NULL);

		errorf ("can't exec bbslogin\n");
	}

	notifybbsd ();

	/* put stdin into raw mode */

	stty_raw (STDIN_FILENO);

	/* calc (initial) max file descriptor to use in select() */

	fdmax = max (STDIN_FILENO, ptyfd);

	/* open snoop-device and put it into raw mode */

	sprintf (fname, "%s/.emu-%s", mkfname (BBSETCDIR), tty);
	if ((emuin = open (fname, O_RDONLY | O_NDELAY)) < 0)
		errorf ("can't open inp_buffer emulation FIFO %s\n", fname);

	fdmax = max (fdmax, emuin);

	sprintf (relogfn, "%s/.relogon-%s", mkfname (ONLINEDIR), tty);

	while (1) {
		if (!stat (relogfn, &st)) {
			bbsdcommand ("relogon", tty, "");
			unlink (relogfn);
			if (!kill (pid, SIGKILL))
				wait (NULL);
			stty_orig ();
			channel_setresult (tty, LSR_RELOGON);
			goto relogon;
		}

		do {
			struct timeval tv;

			tv.tv_sec = 5;
			tv.tv_usec = 0;
			FD_ZERO (&readset);
			FD_SET (STDIN_FILENO, &readset);
			FD_SET (ptyfd, &readset);
			FD_SET (emuin, &readset);

			errno = 0;
			sel = select (fdmax + 1, &readset, NULL, NULL, &tv);
			tv.tv_sec = errno;

#ifdef DEBUG
			fprintf (stderr, "\n\r---(res=%d err=%d,%s) ", sel,
				 tv.tv_sec, strerror (tv.tv_sec));
			if (FD_ISSET (STDIN_FILENO, &readset))
				fprintf (stderr, "[userinp] ");
			if (FD_ISSET (ptyfd, &readset))
				fprintf (stderr, "[output] ");
			if (FD_ISSET (emuin, &readset))
				fprintf (stderr, "[emuinp] ");
#endif
		} while (sel == -1);

		if (sel == 0) {

			/* For efficiency, we only check for timeouts whenever select times out
			   itself. It has a 5s timeout which is good enough granularity for
			   checking timeouts measured in minutes. This reduces the number of
			   time() system calls. */

			if (idlzapt)
				if (tmout + idlzapt < time (NULL))
					gracefulexit ();
			continue;
		}
#ifdef DEBUG
		fprintf (stderr, "1");
#endif
		if (sel == -1 /* && errno != EINTR */ ) {
			printf ("select failed; errno = %d\n", errno);
			fflush (stdout);
		}
#ifdef DEBUG
		fprintf (stderr, "2");
#endif
		if (FD_ISSET (STDIN_FILENO, &readset)) {
			n = read (STDIN_FILENO, buff, BUFF_SIZE);
			if (emuq->xlation > 0) {
				buff[n] = 0;
				if (emuq->xlation > 0)
					faststgxlate (buff,
						      kbdxlation[emuq->
								 xlation]);
			}
			write (ptyfd, buff, n);
			tmout = time (NULL);
		}
#ifdef DEBUG
		fprintf (stderr, "3");
#endif
		if ((emuin >= 0) && FD_ISSET (emuin, &readset)) {
			int     i;

			errno = 0;
			n = read (emuin, buff, BUFF_SIZE);
			i = errno;
#ifdef DEBUG
			fprintf (stderr, "3A(%d,%d,%s)", n, i, strerror (i));
#endif
			if (n == 0) {
#ifdef DEBUG
				fprintf (stderr, "[closing]");
#endif
				close (emuin);
				sprintf (fname, "%s/.emu-%s",
					 mkfname (BBSETCDIR), tty);
				if ((emuin =
				     open (fname, O_RDONLY | O_NDELAY)) < 0)
					errorf
					    ("can't open inp_buffer emulation FIFO %s\n",
					     fname);
				fdmax = max (fdmax, emuin);
			} else {
				if (emuq->xlation > 0) {
					buff[n] = 0;
					if (emuq->xlation > 0)
						faststgxlate (buff,
							      xlation[emuq->
								      xlation]);
				}
				write (ptyfd, buff, n);
			}
		}
#ifdef DEBUG
		fprintf (stderr, "4");
#endif
		if (FD_ISSET (ptyfd, &readset)) {
			register int i;

			if ((n = read (ptyfd, buff, BUFF_SIZE)) < 1)
				exit (0);

#ifdef DEBUG
			fprintf (stderr, "5");
#endif
			for (i = 0; i < n; i++) {
				emuq->queue[emuq->index] = buff[i];
				emuq->index =
				    (emuq->index + 1) % sizeof (emuq->queue);
			}

#ifdef DEBUG
			fprintf (stderr, "6");
#endif
			if (emuq->xlation > 0) {
				buff[n] = 0;
				if (emuq->xlation > 0)
					faststgxlate (buff,
						      xlation[emuq->xlation]);
			}
#ifdef DEBUG
			fprintf (stderr, "7");
#endif
			write (STDOUT_FILENO, buff, n);
		}
	}
}


/* End of File */
