/*****************************************************************************\
 **                                                                         **
 **  FILE:     initline.c                                                   **
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
 * Revision 1.5  2003/12/23 08:18:08  alexios
 * Corrected minor #include discrepancies.
 *
 * Revision 1.4  2003/12/22 17:23:37  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.3  1999/07/18 21:54:26  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Added support
 * for the pre/postconnect fields.
 *
 * Revision 1.2  1998/12/27 16:15:40  alexios
 * Slight bugs fixed.
 *
 * Revision 1.1  1998/12/15 22:11:57  alexios
 * Added a few paranoiac lines of code.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";



#define WANT_SYS_STAT_H 1
#define WANT_STRING_H 1
#define WANT_UTMP_H 1
#define WANT_FCNTL_H 1
#define WANT_IOCTL_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "bbsgetty.h"


/* Update the utmp and wtmp files. */

static void
doutmp ()
{
	pid_t   pid;
	struct utmp *utmp;
	FILE   *fp;

	debug (D_RUN, "doutmp() called, updating UTMP/WTMP files.");

	pid = getpid ();

	utmp = alcmem (sizeof (struct utmp));
	strncpy (utmp->ut_line, device, sizeof (utmp->ut_line));
	strncpy (utmp->ut_id, device + 3, sizeof (utmp->ut_id));	/* ttyS4 -> S4 */
	utmp->ut_host[0] = '\0';
	utmp->ut_addr = 0;
	strncpy (utmp->ut_user, "LOGIN", sizeof (utmp->ut_user));
	utmp->ut_pid = pid;
	utmp->ut_type = LOGIN_PROCESS;
	utmp->ut_time = time (0);
	pututline (utmp);

	/* Now do the WTMP file */
	if ((fp = fopen (WTMP_FILE, "a"))) {
		fseek (fp, 0L, SEEK_END);
		fwrite (utmp, sizeof (*utmp), 1, fp);
		fclose (fp);
	}

	endutent ();
}



void
initline ()
{
	struct stat st;
	struct termios t;
	char    ch;
	int     flags, fd;
	char   *wait = waitfor;

	/* Set the device's ownership back to root */

	chmod (devname, 0666);
	if (!stat (devname, &st))
		chown (devname, 0, st.st_gid);


	/* Update UTMP/WTMP */

	doutmp ();


	/* Open the device for initialisation only if INIT or WAITCHAR are set */

	if (initstr || waitchar) {
		debug (D_RUN, "Opening line for initialisation: %s", devname);
		while (((fd = open (devname, O_RDWR | O_NDELAY)) < 0) &&
		       (errno == EBUSY))
			sleep (30);
		if (fd < 0) {
			debug (D_RUN, "Unable to open %s", devname);
			error_fatalsys ("Unable to open %s", devname);
		}
		if (fd != 0) {
			debug (D_RUN, "Whoops, stdin is not filehandle 0.");
			error_fatal ("Whoops, stdin is not filehandle 0.");
		}
		if (dup (0) != 1) {
			debug (D_RUN, "Whoops, stdout is not filehandle 1.");
			error_fatal ("Whoops, stdout is not filehandle 1.");
		}
		if (dup (0) != 2) {
			debug (D_RUN, "Whoops, stdout is not filehandle 2.");
			error_fatal ("Whoops, stdout is not filehandle 2.");
		}

		/* Arrange for the three file handles to be unbuffered */
		setbuf (stdin, NULL);
		setbuf (stdout, NULL);
		setbuf (stderr, NULL);


		/* Set the baud rate to B0 so the line hangs up */
		if (!nohangup) {
			tcgetattr (0, &t);
			t.c_cflag &= ~CBAUD;
			t.c_cflag |= B0;
			tcsetattr (0, TCSANOW, &t);
		}


		/* Prepare the terminal */
		settermios (&itermios, 0);


		/* Set blocking inp_buffer */
		flags = fcntl (0, F_GETFL, 0);
		fcntl (0, F_SETFL, flags & ~O_NDELAY);


		/* If a PRECONNECT command is set, issue it now, becoming mortal first */
		if (preconnect != NULL) {
			debug (D_RUN, "Executing preconnect command \"%s\"",
			       preconnect);
			execute_as_mortal (preconnect);
			debug (D_RUN, "Done running preconnect command.");
		}


		/* Ok, time to send the init string to the line. */
		if (initstr) {
			debug (D_RUN, "Initialising line %s...", devname);

			/* Set CLOCAL for init, so ATZ works right */
			tcgetattr (0, &t);
			t.c_cflag |= CLOCAL;
			tcsetattr (0, TCSANOW, &t);


			/* Process the init sequence */
			if (chat (initstr) < 0) {
				debug (D_RUN,
				       "Init sequence failed... aborting.");
				/*error_fatal("Init sequence failed, aborting."); */
				exit (1);
			}


			/* Reset the line */
			settermios (&itermios, 0);
		}
	}


	/* Notify the BBS that we initialised ok */
	writelinestatus (LSR_OK);


	/*debug(D_RUN,"OOGAH!!! Linestate=%d, LST_BUSYOYT=%d",linestate,LST_BUSYOUT); */
	/* If the line is in the BUSY-OUT or NO-ANSWER state, we stop here */
	if (linestate == LST_BUSYOUT || linestate == LST_NOANSWER) {
		writelinestatus (LSR_OK);

		/* Cancel alarms and wait for ever */
		alarm (0);
		idler ();
		exit (0);	/* We never get to this point, anyway */
	}



	/* Do we have to wait for a character? */

	if (waitchar) {
		debug (D_RUN, "Waiting for a character...");
		ioctl (0, TCFLSH, 0);
		read (0, &ch, 1);	/* blocking inp_buffer */
		debug (D_RUN, "Got it!");


		/* Check the lockfiles again */
		if (checkuucplock (lock))
			exit (0);
		if ((altlock) && checkuucplock (altlock))
			exit (0);


		/* Should we wait for something specific (except Godot)? */
		if (wait) {
			debug (D_RUN, "Executing WAITFOR script...");


			/* Take into account the character we just read */
			if (ch == *wait)
				wait++;


			/* Wait for the 'wait' sequence */
			if ((*wait) && (expect (wait) < 0)) {
				debug (D_RUN, "WAITFOR match failed.");
				/* error_fatal("WAITFOR match failed."); */
				exit (1);
			}
		}
	}


	/* Now be nice and close any files we've opened */

	if (initstr || waitchar) {
		close (0);
		close (1);
		close (2);
	}
}



/* End of File */
