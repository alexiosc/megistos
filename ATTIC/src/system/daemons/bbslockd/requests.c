/*****************************************************************************\
 **                                                                         **
 **  FILE:     requests.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  Handle BBS lockd requests                                    **
 **  NOTES:                                                                 **
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
 * $Id: requests.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: requests.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2004/02/29 18:02:54  alexios
 * Ran through megistos-config --oh. Minor permission/file location
 * issues fixed to account for the new infrastructure.
 *
 * Revision 1.4  2003/12/29 07:46:08  alexios
 * Adjusted #includes.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1999/07/18 22:03:05  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.0  1998/12/27 16:25:21  alexios
 * Initial revision
 *
 *
 */


const static char rcsinfo[] =
    "$Id: requests.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";


#define __BBSLOCKD__ 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_SOCKET_H 1
#define WANT_SYS_UN_H 1
#define WANT_FCNTL_H 1
#define WANT_PWD_H 1
#include <megistos/bbsinclude.h>
#include <megistos/bbs.h>
#include "bbslockd.h"


static int bbslockd_socket;


static int
sendresult (int res)
{
	char    buf[512];

	sprintf (buf, "%d", res);
	if (send (bbslockd_socket, buf, strlen (buf), 0) < 0) {
		error_intsys ("Unable to write to bbslockd socket.");
	}
	return res;
}


static int
sendfullresult (int res, char *info)
{
	char    buf[512];

	sprintf (buf, "%d %s", res, (info != NULL) ? info : "");
	if (send (bbslockd_socket, buf, strlen (buf), 0) < 0) {
		error_intsys ("Unable to send to bbslockd socket.");
	}
	return res;
}


static int
lockd_checklock (char *name, int caller_pid)
{
	int     fd;
	char    fname[256];
	char    buf[512];
	struct stat st;
	int     pid;
	char   *infostr;

	/* If the lock file isn't there, return immediately */

	strcpy (fname, mkfname ("%s/%s", LOCKDIR, name));
	if (stat (fname, &st))
		return sendresult (LKR_OK);

	if ((fd = open (fname, O_RDONLY)) < 0) {
		error_intsys ("Unable top open lock file %s", fname);
		return sendresult (LKR_ERROR);
	}

	bzero (buf, sizeof (buf));
	read (fd, buf, sizeof (buf) - 1);
	close (fd);


	/* If we fail to parse the lock file's contents, assume it's
	   fake. We declare it stale so it can be deleted. */

	if ((infostr = strchr (buf, ' ')) != NULL)
		*infostr++ = 0;
	else
		return sendresult (LKR_STALE);
	if (!sscanf (buf, "%d", &pid))
		return sendresult (LKR_STALE);


	/* Likewise, declare stale any lock made by PID <= 1 (should never happen) */

	if (pid <= 1)
		return sendresult (LKR_STALE);
	if (pid == caller_pid)
		return sendresult (LKR_OWN);
	if ((kill (pid, 0) < 0) && errno == ESRCH)
		return sendresult (LKR_STALE);

	return sendfullresult (pid, infostr);
}


static int
lockd_checklock_quietly (char *name, int caller_pid)
{
	int     fd;
	char    fname[256];
	char    buf[512];
	struct stat st;
	int     pid;
	char   *infostr;

	/* If the lock file isn't there, return immediately */

	strcpy (fname, mkfname ("%s/%s", LOCKDIR, name));
	if (stat (fname, &st))
		return LKR_OK;

	if ((fd = open (fname, O_RDONLY)) < 0) {
		error_intsys ("Unable top open lock file %s", fname);
		return LKR_ERROR;
	}

	bzero (buf, sizeof (buf));
	read (fd, buf, sizeof (buf) - 1);
	close (fd);


	/* If we fail to parse the lock file's contents, assume it's
	   fake. We declare it stale so it can be deleted. */

	if ((infostr = strchr (buf, ' ')) != NULL)
		*infostr++ = 0;
	else
		return LKR_STALE;
	if (!sscanf (buf, "%d", &pid))
		return LKR_STALE;


	/* Likewise, declare stale any lock made by PID <= 1 (should never happen) */

	if (pid <= 1)
		return LKR_STALE;
	if (pid == caller_pid)
		return LKR_OWN;
	if ((kill (pid, 0) < 0) && errno == ESRCH)
		return LKR_STALE;

	return pid;
}


static int
lockd_placelock (char *name, char *info, int pid)
{
	char    fname[512];
	char    buf[64];
	int     res, fd;


	/* Before making the lock, check if it already exists. We shouldn't
	   rely on the client doing this */

	res = lockd_checklock_quietly (name, pid);
	if (res != LKR_OK && res != LKR_OWN && res != LKR_STALE)
		return sendresult (res);

	/* Create the lock */

	strcpy (fname, mkfname ("%s/%s", LOCKDIR, name));
	unlink (fname);		/* Just in case */
	if ((fd = creat (fname, 0660)) < 0) {
		error_intsys ("Unable to creat() lock file %s", fname);
		return sendresult (LKR_ERROR);
	}
	sprintf (buf, "%d ", pid);
	write (fd, buf, strlen (buf));
	if (info != NULL && strlen (info))
		write (fd, info, strlen (info));
	close (fd);

	chown (fname, bbsuid, bbsgid);
	chmod (fname, 0640);

	return sendresult (LKR_OK);
}


static int
lockd_rmlock (char *name)
{
	char    fname[256];

	sprintf (fname, "%s/%s", mkfname (LOCKDIR), name);
	return sendresult (unlink (fname) ? LKR_ERROR : LKR_OK);
}


void
handlerequest (int fd)
{
	char    buf[512], *cp = buf;
	char    cmd[5], lockname[256];
	int     delta, pid;

	bbslockd_socket = fd;

	/* Read the request string */
	bzero (buf, sizeof (buf));

	if (recv (bbslockd_socket, buf, sizeof (buf), 0) < 0) {
		error_intsys ("Failed to receive from socket.");
	}


	/* Parse the request */
	if (sscanf (buf, "%4s %255s %d %n", cmd, lockname, &pid, &delta) != 3) {
		sendresult (LKR_SYNTAX);
	}


	/* Make sure the PID is ok */
	if (pid < 2) {
		sendresult (LKR_SYNTAX);
		return;
	}


	/* Chop the newline */
	cp = &buf[delta];
	if ((cp = strchr (cp, '\n')) != NULL)
		*cp = 0;
	cp = &buf[delta];


	/* Interpret the command */
	if (!strcmp (cmd, LKC_PLACE))
		lockd_placelock (lockname, cp, pid);
	else if (!strcmp (cmd, LKC_CHECK))
		lockd_checklock (lockname, pid);
	else if (!strcmp (cmd, LKC_REMOVE))
		lockd_rmlock (lockname);
	else
		sendresult (LKR_SYNTAX);
}


/* End of File */
