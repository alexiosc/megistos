/*****************************************************************************\
 **                                                                         **
 **  FILE:     metabbs-server.c                                             **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:                                                               **
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
 * $Id$
 *
 * $Log$
 * Revision 1.4  2003/12/22 17:23:36  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  2000/01/23 20:46:33  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";


#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_WAIT_H 1
#define WANT_SYS_SOCKET_H 1
#define WANT_NETINET_IN_H 1
#define WANT_UNISTD_H 1
#define WANT_PWD_H 1
#define WANT_SYS_FCNTL_H 1
#define WANT_SYS_IOCTL_H 1
#include <bbsinclude.h>
#include <megistos/bbs.h>
#include <megistos/metabbs-server.h>


char   *rcs_ver = RCS_VER;
char   *secrets_file = NULL;
int     port = METABBS_PORT;
char    host_name[256];
char   *progname;
int     under_inetd = 1;
int     sock;
struct sockaddr_in name;
struct sockaddr_in peer;
int     bbsuid, bbsgid;
char    tty[32];


void
syntax ()
{
	printf ("syntax: metabbs-server -s file [options]\n\n");
	printf ("   -s secrets      Secrets file to read.\n\nOptions:\n\n");
	printf
	    ("   -p port         Port to listen to (not applicable if running under inetd).\n");
	exit (1);
}


void
get_args (int argc, char **argv)
{
	char    c;

	while ((c = getopt (argc, argv, "p:s:h?")) != EOF) {
		switch (c) {
		case 'p':
			if (atoi (optarg) <= 0 || atoi (optarg) > 65535)
				syntax ();
			port = atoi (optarg);
			break;
		case 's':
			secrets_file = strdup (optarg);
			break;
		case 'h':
		case '?':
		default:
			syntax ();
		}
	}

	if (secrets_file == NULL)
		syntax ();
}


static void
getpwbbs ()
{
	struct passwd *pass = getpwnam (BBSUSERNAME);

	if (pass == NULL)
		error_fatal ("User %s not found.", BBSUSERNAME);
	bbsuid = pass->pw_uid;
	bbsgid = pass->pw_gid;
}


static void
handle_child_exit (int sig)
{
	int     status;
	int     pid;

	while ((pid = waitpid (-1, &status, WNOHANG)) > 0) {
#ifdef DEBUG
		fprintf (stderr,
			 "*** Caught child exit, child pid=%d, signaled=%d, signal=%d\n",
			 pid, WIFSIGNALED (status), WTERMSIG (status));
#endif
	}
	signal (SIGCHLD, handle_child_exit);
}


static void
init ()
{
	mod_init (INI_TTYNUM | INI_OUTPUT | INI_SYSVARS | INI_ERRMSGS |
		  INI_INPUT | INI_SIGNALS | INI_CLASSES | INI_LANGS |
		  INI_ATEXIT);
	out_clearflags (OFL_WAITTOCLEAR);


	getpwbbs ();		/* Get the /etc/passwd entry user 'bbs' */

	if (gethostname (host_name, sizeof (host_name)) < 0) {
		error_fatalsys ("Unable to get hostname.");
	}

	strcpy (tty, getenv ("CHANNEL"));
}


int
main (int argc, char *argv[])
{
	progname = argv[0];
	mod_setprogname (argv[0]);

	alarm (0);

	setenv ("CHANNEL", "[metabbs-server]", 1);

	init ();		/* Miscellaneous initialisations */
	mainloop ();		/* Finally, run the daemon's main loop */

	return 0;
}


/* End of File */
