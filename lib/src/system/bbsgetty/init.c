/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsgetty.c                                                   **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  Talk to comms hardware and establish connections.            **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.4  2003/12/22 17:23:37  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  1999/07/18 21:54:26  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Added support
 * for the pre/postconnect fields.
 *
 * Revision 1.1  1998/12/27 16:15:40  alexios
 * Migrated to the new {get,set}linestatus() functions.
 * Changed connect to connectstr to disambiguate the variable
 * from the connect() system call.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";



#define WANT_SIGNAL_H 1
#define WANT_UNISTD_H 1
#define WANT_PWD_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include <megistos/bbsgetty.h>



char    autorate[256];		/* Baud rate as autodetected */
char    device[256];		/* TTY device name minus "/dev/" */
char    devname[256];		/* Full device name (/dev/...) */
char    lock[256];		/* Name of the UUCP lock file */
char    altlock[256];		/* Alternative UUCP lock file */
char    speed[256];		/* Speed string */

char   *progname = NULL;	/* The program name */
char   *waitfor = NULL;		/* The WAITFOR string */
char   *connectstr = NULL;	/* The CONNECT string */
char   *defname = NULL;		/* The class defaults file for this line */
char   *initstr = NULL;		/* The modem init string */
char   *busyout = NULL;		/* The modem BUSYOUT string */
char   *noanswer = NULL;	/* The modem NOANSWER string */
char   *offline = NULL;		/* The modem OFFLINE string */
char   *initial = NULL;		/* gettydefs like initial line flags */
char   *final = NULL;		/* gettydefs like final line flags */
char   *preconnect = NULL;	/* program to run at getty startup */
char   *postconnect = NULL;	/* program to run right after connection */

int     autobaud;		/* Autodetect(ed) baud rate? */
int     debug;			/* Debug level */
int     bbsgid;			/* GID of the bbs user */
int     bbsuid;			/* UID of the bbs user */
int     nohangup;		/* Do not hangup tty line on startup */
int     delay;			/* Delay before starting */
int     waitchar;		/* Wait for a character before starting */
int     lockedbaud;		/* Lock the bps rate of the modem? */
int     reportedlinespeed;	/* Modem's reported line speed */
int     linestate;		/* State of the line */
int     localline;		/* Is this line local (eg serial terminal?) */
int     chanidx;		/* The ttynum index of this line */


/* we shall cleanse Ye Holy Online Directory of sinful leftover files.
   Fetch the Holy Hand Grenade! */

static void
cleanonline ()
{
	FILE   *fp = NULL;
	char    fname[256];

	strcpy (fname, mkfname ("%s/.%s", mkfname (ONLINEDIR), device));
	if ((fp = fopen (fname, "r")) != NULL) {
		char    onlrec[256];

		if (fscanf (fp, "%s", onlrec) == 1)
			unlink (onlrec);
		fclose (fp);
	}
	unlink (fname);
}



/* Get the bbs user's uid and gid */

static void
getbbsuid ()
{
	struct passwd *bbspass = getpwnam (BBSUSERNAME);

	if (bbspass == NULL) {
		error_fatal ("Unable to get /etc/passwd entry for user %s",
			     BBSUSERNAME);
	}
	bbsuid = bbspass->pw_uid;
	bbsgid = bbspass->pw_gid;
}



/* Store our PID */

static void
storepid ()
{
	FILE   *fp;
	char    fname[256];
	pid_t   pid;

	strcpy (fname, mkfname (CHANDEFDIR "/.pid-%s", device));

	debug (D_RUN, "Writing PID file (%s).", fname);

	if ((fp = fopen (fname, "w")) == NULL) {
		int     i = errno;

		debug (D_RUN, "Unable to write PID file (%s), aborting.",
		       fname);
		errno = i;
		error_fatalsys ("Cannot open PID file %s for writing", fname);
	}

	pid = getpid ();
	fprintf (fp, "%d\n", (int) pid);
	fclose (fp);

	debug (D_RUN, "Written PID %d to file %s", pid, fname);
}



/* Ask the BBS about our device's channel information */

void
checkbbschannel ()
{

	debug (D_INIT, "Making sure tty %s is managed by the BBS", device);
	mod_init (INI_TTYNUM);
	chanidx = chan_getindex (device);
	if (chanidx < 0) {
		debug (D_OPT, "Device %s is not defined in %s",
		       device, mkfname (CHANDEFSRCFILE));
		error_fatal ("Device %s is not defined in %s",
			     device, mkfname (CHANDEFSRCFILE));
	}
	debug (D_INIT, "Ok, device %s is known as channel %x in the BBS.",
	       device, channels[chanidx].channel);


	/* While we're at it, find out what file we have to read to get our
	   defaults. */

	defname = strdup (channels[chanidx].config);
	localline = (chan_last->flags & (TTF_CONSOLE | TTF_SERIAL)) != 0;
	debug (D_INIT, "Class defaults file suffix is \"%s\".", defname);
	debug (D_INIT, "This is%s a local line (eg serial terminal).",
	       localline ? "" : "n't");
}



void
shangup ()
{
	debug (D_RUN, "Caught SIG_HUP signal, exiting.");
	exit (0);
}



/* Initialise */

void
init (int argc, char **argv)
{
	/* Initialise values */
	device[0] = 0;		/* tty device */
	autobaud = 0;		/* no autobauding */
	autorate[0] = 0;	/* autodetected comm rate */
	nohangup = 0;		/* hangup the line first */
	delay = 0;		/* delay before prompt */
	speed[0] = 0;		/* comm speed */
	waitchar = 0;		/* don't wait for a char */
	waitfor = NULL;		/* no waitfor string */
	connectstr = NULL;	/* no connect string */
	debug = 0;		/* no debugging */
	lockedbaud = 0;		/* no baud rate lock */
	reportedlinespeed = 0;	/* Unknown connection speed */
	linestate = LST_NORMAL;	/* normal line status */

	/* parse command line and defaults file */
	setdefaults (argc, argv);

	/* Get the uid and gid for the bbs user */
	getbbsuid ();
	debug (D_INIT, "The " BBSUSERNAME " user has UID %d, GID %d.", bbsuid,
	       bbsgid);

	/* Initialise some of the BBS facilities */
	mod_init (INI_TTYNUM | INI_SYSVARS);

	/* Make sure the tty is one of those managed by the BBS */
	checkbbschannel ();

	/* Parse the class defaults file and the tty-specific defaults file */
	parsefile (defname);
	parsefile (device);	/* The tty-specific file has the same
				   name as the device itself. */
	validate ();		/* Validate the setup */
	parselinetype ();	/* Convert INI_AL/FINAL to termios */

	/* Find out what state we need to put the line in */
	readlinestatus ();
	writelinestatus (LSR_INIT);
	if (linestate == LST_BUSYOUT)
		initstr = busyout;
	else if (linestate == LST_NOANSWER)
		initstr = noanswer;
	else if (linestate == LST_OFFLINE)
		initstr = offline;

	/* Just in case... */
	thisshm = malloc (sizeof (struct shmuserrec));

	/* Store our PID */
	storepid ();

	/* Wipe the environment */
#if 0
	environ = (char **) malloc (sizeof (char *));
	memset (environ, 0, sizeof (char *));
#endif

	/* Clean up any remaining files in the BBS online directory */
	cleanonline ();

	/* Close the standard files */
	close (0);
	close (1);
	close (2);

	/* Hangup our line */
	signal (SIGHUP, SIG_IGN);
#if HAVE_VHANGUP
	vhangup ();		/* This seems to be Linux-specific */
#else
	signal (0, SIGHUP);
#endif

	/* And register our own Hangup signal handler */
	signal (SIGHUP, shangup);

	/* Start a new session */
	setsid ();

	/* Set signal handling */
	signal (SIGINT, SIG_IGN);	/* ignore ^C */
	signal (SIGQUIT, SIG_DFL);
	signal (SIGTERM, SIG_DFL);

	/* Derived values */
	sprintf (devname, DEVDIR "/%s", device);
	sprintf (lock, UUCPLOCK, device);
	debug (D_LOCK, "UUCP lock: \"%s\"", lock);
	altlock[0] = 0;

	/* Get the program name */
	progname = argv[0];
	if ((progname = strrchr (argv[0], '/')) == NULL)
		progname = argv[0];
	else
		progname++;
	debug (D_INIT, "Program name is \"%s\"", progname);
}


/* End of File */
