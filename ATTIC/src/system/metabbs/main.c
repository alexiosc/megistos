/*****************************************************************************\
 **                                                                         **
 **  FILE:     main.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Meta-daemon for networking/distributing BBSs over networks.  **
 **  NOTES:    Purposes:                                                    **
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
 * $Id: main.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: main.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2004/02/29 17:45:56  alexios
 * storepid() now stores the PID file under run/.
 *
 * Revision 1.4  2003/12/23 08:22:30  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  1999/08/07 02:20:41  alexios
 * Added code to store daemon PID to a file.
 *
 * Revision 1.1  1999/07/28 23:16:48  alexios
 * *** empty log message ***
 *
 * Revision 1.0  1999/07/18 22:05:10  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id: main.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";


#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#include <sys/socket.h>
#include <syslog.h>
#include <sys/utsname.h>
#include <signal.h>
#include <bbs.h>

#include "metaservices.h"
#include "metabbs.h"



char   *progname;
SVCXPRT *server;



void    metabbs_prog_1 (struct svc_req *rqstp, register SVCXPRT * transp);



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
		fprintf (stderr, "%s: fork(): unable to fork daemon\n",
			 progname);
		exit (1);
	case 0:
		ioctl (0, TIOCNOTTY, NULL);
		setsid ();
#if 0
		close (0);
		close (1);
		close (2);
#endif
		break;
	default:
		exit (0);
	}
}


static void
dispatch (struct svc_req *rqstp, register SVCXPRT * transp)
{
	server = transp;	/* Keep this so that services have access to it. */
	metabbs_prog_1 (rqstp, transp);
}


void
handle_child_exit (int sig)
{
	int     status;
	int     pid;

#ifdef DEBUG
	fprintf (stderr, "A child changed status. Waiting for it...\n");
#endif

	while ((pid = waitpid (-1, &status, WNOHANG)) > 0) {

#ifdef DEBUG
		fprintf (stderr,
			 "Child wifexited=%d pid=%d status=%d.\n",
			 WIFEXITED (status), pid, WEXITSTATUS (status));
#endif
	}

	signal (SIGCHLD, handle_child_exit);
}


/* This nice little thing was actually generated by rpcgen(1) */


static void
rpc_svc_run ()
{
	register SVCXPRT *transp;

	pmap_unset (METABBS_PROG, METABBS_VERS);

	transp = server = svctcp_create (RPC_ANYSOCK, 0, 0);

	if (transp == NULL) {
		fprintf (stderr, "cannot create tcp service.");
		exit (1);
	}
	if (!svc_register
	    (transp, METABBS_PROG, METABBS_VERS, dispatch, IPPROTO_TCP)) {
		fprintf (stderr,
			 "unable to register (METABBS_PROG, METABBS_VERS, tcp).");
		exit (1);
	}

	signal (SIGCHLD, handle_child_exit);
	svc_run ();
	fprintf (stderr, "svc_run returned");
	exit (1);
}


static void
storepid ()
{
	char fname [512];
	FILE   *fp;

	strncpy (fname, mkfname (BBSRUNDIR "/rpc.metabbs.pid"), sizeof (fname));
	
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Unable to open %s for writing.", fname);
		exit (1);
	}
	fprintf (fp, "%d", getpid ());
	fclose (fp);
	chmod (fname, 0600);
	chown (fname, 0, 0);
}





int
main (int argc, char **argv)
{
	my_hostname ();		/* Get our hostname and cache it for later */
	checkuid ();		/* Make sure the superuser is running us */
	forkdaemon ();		/* Fork() the daemon */
	storepid ();		/* Store the PID of this daemon */
	rpc_svc_run ();		/* Execute the RPC service routine */
	return 0;		/* We never reach this point */
}


/* End of File */
