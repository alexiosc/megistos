/*****************************************************************************\
 **                                                                         **
 **  FILE:     msgd.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.1                                     **
 **            B, August 1996, Version 0.2                                  **
 **  PURPOSE:  Reindex/rethread message areas, and move network mail (in    **
 **            /usr/spool/mail/ to BBS users' accounts                      **
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
 * $Id: msgd.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: msgd.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2004/05/03 05:43:07  alexios
 * Added setsid() and close() calls to make this a better daemon.
 *
 * Revision 1.4  2004/02/29 16:32:58  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 22:04:23  alexios
 * Removed periodic reindexing of message base -- not needed.
 *
 * Revision 0.5  1998/12/27 16:28:24  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:27:56  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:16:29  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 17:05:09  alexios
 * *** empty log message ***
 *
 * Revision 0.1  1997/08/28 11:16:40  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] = "$Id: msgd.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_TERMIOS_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include <mbk/mbk_emailclubs.h>
#include "msgd.h"


int     tmreidx = 60 * 24;
int     tmnetml = 15;

int     h, m, s;


void
storepid ()
{
	FILE   *fp;
	char    fname[256];

	sprintf (fname, "%s/msgd.pid", mkfname (BBSRUNDIR));
	if ((fp = fopen (fname, "w")) == NULL)
		return;
	fprintf (fp, "%d", getpid ());
	fclose (fp);
	chmod (fname, 0600);
	chown (fname, 0, 0);
}


int
gcd (int a, int b)
{
	while (a && b) {
		if (a > b)
			a = a % b;
		else
			b = b % a;
	}
	return a ? a : b;
}


void
mainloop ()
{
	int     sleeptime = gcd (tmreidx, tmnetml);
	int     reindex = tmreidx / sleeptime;
	int     netmail = tmnetml / sleeptime;
	int     tick = 0;

#ifdef DEBUG
	printf ("msgd mainloop...\n");
	printf ("sleeptime=GCD(%d,%d)=%d\n", tmreidx, tmnetml, sleeptime);
#endif

	for (;;) {
		if ((tick % netmail) == 0)
			getnetmail ();
		if ((tick % reindex) == 0)	/*doreindex() */
			;
		sleep (sleeptime);
		tick++;
	}
}


int
main (int argc, char *argv[])
{
	mod_setprogname (argv[0]);
	if (getuid ()) {
		fprintf (stderr, "%s: getuid: not super-user\n", argv[0]);
		exit (1);
	}

	{
		promptblock_t *msg;

		error_setnotify (0);
		msg = msg_open ("emailclubs");
		tmreidx = msg_int (TMREIDX, 5, 32767) * 60;
		tmnetml = msg_int (TMNETML, 5, 32767) * 60;
		msg_close (msg);
	}

	switch (fork ()) {
	case -1:
		fprintf (stderr, "%s: fork: unable to fork daemon\n", argv[0]);
		exit (1);
	case 0:
		ioctl (0, TIOCNOTTY, NULL);
		setsid ();
		close (0);
		close (1);
		close (2);
		break;
	default:
		exit (0);
	}

	mod_init (INI_SYSVARS);

	storepid ();
	ioctl (0, TIOCNOTTY, NULL);

	mainloop ();

	return 0;
}
