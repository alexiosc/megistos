/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbslockd.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  The BBS lock daemon.                                         **
 **  NOTES:    Serialises lock operations in the BBS, thus solving most of  **
 **            those ugly race conditions. It's pretty small, too.          **
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
 * Revision 1.5  2004/05/03 05:41:59  alexios
 * Added a setsid() to make this a better daemon.
 *
 * Revision 1.4  2004/02/29 18:02:54  alexios
 * Ran through megistos-config --oh. Minor permission/file location
 * issues fixed to account for the new infrastructure.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1999/07/18 22:03:05  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Minor fixes.
 *
 * Revision 1.0  1998/12/27 16:25:21  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_SOCKET_H 1
#define WANT_SYS_UN_H 1
#define WANT_UNISTD_H 1
#define WANT_PWD_H 1
#define WANT_SYS_FCNTL_H 1
#define WANT_SYS_IOCTL_H 1
#include <bbsinclude.h>
#include <megistos/bbs.h>
#include "bbslockd.h"


char   *progname;
int     locksocket;
struct sockaddr_un name;
int     bbsuid, bbsgid;



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
mksocket ()
{
	int     len;

	/* Remove the named socket for good measure */
	unlink (BBSLOCKD_SOCKET);

	/* Create the socket */
	if ((locksocket = socket (AF_UNIX, SOCK_STREAM, 0)) < 0) {
		error_fatalsys ("Unable to create bbslockd socket");
	}

	/* Name the socket */
	memset (&name, 0, sizeof (struct sockaddr_un));
	name.sun_family = AF_UNIX;
	strcpy (name.sun_path, BBSLOCKD_SOCKET);
	len = sizeof (name.sun_family) + strlen (name.sun_path);

	/* Bind the socket to the name */
	if (bind (locksocket, (struct sockaddr *) &name, len) < 0) {
		error_fatalsys ("Failed to bind bbslockd socket to %s",
				BBSLOCKD_SOCKET);
	}

	/* Set ownership and permissions of the socket */
	chown (BBSLOCKD_SOCKET, bbsuid, bbsgid);
	chmod (BBSLOCKD_SOCKET, 0660);
}


static void
storepid ()
{
	char    fname[512];
	FILE   *fp;

	strncpy (fname, mkfname (BBSRUNDIR "/bbslockd.pid"), sizeof (fname));

	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Unable to open %s for writing.",
				fname);
		exit (1);
	}
	fprintf (fp, "%d", getpid ());
	fclose (fp);
	chmod (fname, 0600);
	chown (fname, 0, 0);
}


static void
mainloop ()
{
	int     ns = 0, len;

	for (;;) {
		if (listen (locksocket, 5) < 0) {
			error_fatalsys ("Unable to listen to socket %s",
					BBSLOCKD_SOCKET);
		}

		if ((ns =
		     accept (locksocket, (struct sockaddr *) &name,
			     &len)) < 0) {
			error_fatalsys ("accept() failed for socket %s",
					BBSLOCKD_SOCKET);
		}

		handlerequest (ns);

		close (ns);
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
	switch (fork ()) {
	case -1:
		fprintf (stderr, "%s: fork: unable to fork daemon\n",
			 progname);
		exit (1);
	case 0:
		ioctl (0, TIOCNOTTY, NULL);
		setsid ();
		close (0);
#ifndef DEBUG
		close (1);
		close (2);
#endif
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
	setenv ("CHANNEL", "[bbslockd]", 1);
	signal (SIGPIPE, SIG_IGN);

	checkuid ();		/* Make sure the superuser is running us */
	forkdaemon ();		/* Fork() the daemon */
	getpwbbs ();		/* Get the /etc/passwd entry user 'bbs' */
	mksocket ();		/* Make BBSD's FIFO and set its permissions */
	storepid ();		/* Store the daemon's PID */
	mainloop ();		/* Finally, run the daemon's main loop */

	return 0;
}


/* End of File */
