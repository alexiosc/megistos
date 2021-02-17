/*****************************************************************************\
 **                                                                         **
 **  FILE:     lock.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94                                                 **
 **  PURPOSE:  Place, check, and remove locks                               **
 **  NOTES:    Locks are placed in directory /bbs/lock (#define LOCKDIR in  **
 **            config.h. The filename of the lock is given by the caller.   **
 **            The lock file contains the PID of the caller, together with  **
 **            a user defined INFO string.                                  **
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
 * $Id: lock.c,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: lock.c,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2003/12/19 13:24:30  alexios
 * Updated include directives.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 14:31:16  alexios
 * Added autoconf support. Major changes, since lock.c now
 * talks to the BBS lock daemon, which does all actual locking.
 *
 * Revision 0.3  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.2  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: lock.c,v 2.0 2004/09/13 19:44:34 alexios Exp $";


#define __BBSLOCKD__ 1
#define WANT_SYS_SOCKET_H 1
#define WANT_SYS_UN_H 1
#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <megistos/bbsinclude.h>

#include <megistos/useracc.h>
#include <megistos/miscfx.h>
#include <megistos/config.h>
#include <megistos/errors.h>
#include <megistos/lock.h>



static int
lockdcmd (char *cmd, const char *name, char *info)
{
	char    buf[512];
	int     n, s, len, res;
	struct sockaddr_un sock;

	/* Create the socket */

	if ((s = socket (AF_UNIX, SOCK_STREAM, 0)) < 0) {
		error_fatalsys ("Unable to create bbslockd socket.");
	}


	/* Name the socket */

	bzero (&sock, sizeof (sock));
	sock.sun_family = AF_UNIX;
	strcpy (sock.sun_path, BBSLOCKD_SOCKET);
	len = sizeof (sock.sun_family) + strlen (sock.sun_path);

	/* Connect to the socket */
	for (n = 0; n < 10; n++) {
		res = connect (s, (struct sockaddr *) &sock, len);
		if (res == 0)
			break;
		if (errno == ECONNREFUSED) {

			/* Connection refused. This may mean that the server is too
			   backlogged (whoa, I'd hate to imagine such a simple server
			   being backlogged -- this should really never happen). Wait a
			   bit and retry. */

			usleep (100000);	/* Wait for .1 second */
			continue;
		}
	}


	/* Oh well, we failed to connect. */
	if (res < 0)
		error_fatalsys ("Unable to connect to bbslockd socket %s",
				BBSLOCKD_SOCKET);



	/* Prepare the command string */

	if (!strcmp (cmd, LKC_PLACE)) {
		sprintf (buf, "%s %s %d %s", cmd, name, (int) getpid (),
			 (info == NULL || !strlen (info)) ? "" : info);
	} else {
		sprintf (buf, "%s %s %d", cmd, name, (int) getpid ());
	}


	/* Transmit the command string */

	if (send (s, buf, strlen (buf), 0) < 0) {
		error_fatalsys ("Unable to send() to bbslockd.");
	}


	/* Receive the result */

	bzero (buf, sizeof (buf));
	if (recv (s, buf, sizeof (buf), 0) < 0) {
		error_fatalsys ("Unable to recv() from bbslockd.");
	}


	if (sscanf (buf, "%d%n", &res, &n) != 1) {
		error_fatal
		    ("bbslockd issued syntantically incorrect response \"%s\"!",
		     buf);
	}
	if (res > 1 && info != NULL)
		strcpy (info, &buf[n]);

	shutdown (s, 2);
	close (s);
	return res;
}



int
lock_place (const char *name, const char *info)
{
	return lockdcmd (LKC_PLACE, name, (char *) info);
}


int
lock_check (const char *name, char *info)
{
	return lockdcmd (LKC_CHECK, name, info);
}


int
lock_rm (const char *name)
{
	return lockdcmd (LKC_REMOVE, name, NULL);
}


int
lock_wait (const char *name, int delay)
{
	int     naps = delay * 5;
	int     i, result;

	for (i = 0; i < naps; i++) {
		if ((result = lock_check (name, NULL)) < 1)
			return result;
		usleep (200000);
	}
	return LKR_TIMEOUT;
}
