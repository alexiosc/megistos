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
 * Revision 1.5  2003/12/22 18:18:11  alexios
 * Migrated to the new #include scheme.
 *
 * Revision 1.4  2003/12/22 17:23:37  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1999/07/18 21:54:26  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Added config
 * field that executes some command immediately after connection
 * (postconnect). Minor fixes.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";



#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SIGNAL_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#include <megistos/bbsinclude.h>
#include <megistos/bbs.h>
#include <megistos/bbsgetty.h>



static void
startemud ()
{
	char    fname[256];
	int     i;

	settermios (&ftermios, 1);	/* Switch the terminal to its final state */

	/* Execute the post-connect command, if any */
	if (postconnect != NULL) {
		debug (D_RUN, "Executing postconnect command \"%s\"",
		       postconnect);
		execute_as_mortal (postconnect);
		debug (D_RUN, "Done running postconnect command.");
	}

	sprintf (fname, "%s/.emu-%s", mkfname (EMUFIFODIR), device);
	unlink (fname);

	if (mkfifo (fname, 0660)) {
		error_fatalsys ("Unable to create emulation FIFO %s", fname);
	}
	if (chown (fname, bbsuid, bbsgid)) {
		error_fatalsys ("Unable to chown(\"%s\",%d,%d)", fname, bbsuid,
				bbsgid);
	}

	debug (D_RUN, "Turning into emud. Bye!");
	execl (mkfname (EMUDBIN), EMUDBIN, NULL);
	i = errno;

	/* If we get to this point, something's gone wrong */

	debug (D_RUN,
	       "Aieee, something's gone very wrong. Couldn't spawn emud.");
	errno = i;
	error_fatalsys ("Unable to spawn emu daemon for %s.", device);
}


int
main (int argc, char **argv)
{
	mod_setprogname ("bbsgetty");	/* this facilitates Megistos error logging */
	init (argc, argv);	/* initialise bbsgetty */
	waituucplocks ();	/* wait for pending UUCP locks on this tty */
	initline ();		/* initialise the channel */
	watchuucplocks ();	/* monitor the lockfiles */
	opentty ();		/* open & initialize the tty */
	startemud ();		/* start emud (only it spawns bbslogin) */
	return 0;		/* we never reach this point (hopefully) */
}


/* End of File */
