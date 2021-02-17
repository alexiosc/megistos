/*****************************************************************************\
 **                                                                         **
 **  FILE:     misc.c                                                       **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  Miscellaneous functions                                      **
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
 * $Id: misc.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: misc.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/02/29 17:58:32  alexios
 * Minor permission/file location issues fixed to account for the new
 * infrastructure.
 *
 * Revision 1.5  2003/12/23 08:18:08  alexios
 * Corrected minor #include discrepancies.
 *
 * Revision 1.4  2003/12/22 17:23:37  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  1999/07/18 21:54:26  alexios
 * Added execute_as_mortal() to drop super user privileges,
 * execute a shell command, and then return back to normal.
 *
 * Revision 1.1  1998/12/27 16:15:40  alexios
 * Simplified entire module by use of {get,set}linestatus().
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id: misc.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



#define WANT_SYS_TIME_H 1
#define WANT_SYS_RESOURCE_H 1
#define WANT_SIGNAL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_WAIT_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "bbsgetty.h"



/* Read the line state and status */

void
readlinestatus ()
{
	channel_status_t status;

	debug (D_RUN, "Reading status file for device %s", device);
	channel_getstatus (device, &status);
	linestate = status.state;
	debug (D_RUN, "Line status: state=%s, result=%s, bps=%d, user=%s",
	       channel_states[status.state], channel_results[status.result],
	       status.baud, status.user);
}



/* Write the line status */

void
writelinestatus (int result)
{
	channel_status_t status;

	debug (D_RUN, "Writing status for device \"%s\"", device);
	channel_getstatus (device, &status);
	status.result = result;
	status.baud = reportedlinespeed;
	status.user[0] = 0;
	channel_setstatus (device, &status);
}



/* Drop our priority, become mortal and sleep for ever */
void
idler ()
{
	setpriority (PRIO_PROCESS, 0, 20);
	setuid (bbsuid);
	setgid (bbsgid);
	for (;;) {
#ifdef REPENT_SINNERS_THE_END_IS_NIGH
		sleep (999999);
#else
		sleep (666666);
#endif
	}
}



/* Execute a command as a mere mortal */

void
execute_as_mortal (char *command)
{
	int     pid = fork ();

	if (command == NULL)
		return;

	switch (pid) {
	case 0:
		setuid (bbsuid);
		setgid (bbsgid);
		if (getuid ()) {
			execl ("/bin/sh", "sh", "-c", command, NULL);
			system (command);
		}
		error_fatal ("Unable to become uid:pid %d:%d to run \"%s\".",
			     bbsuid, bbsgid, command);
		exit (1);
	case -1:
		error_fatal ("Unable to fork() child process to run \"%s\"!",
			     command);
		exit (1);
	default:
		wait (&pid);	/* No magic, I'm just reusing the pid variable here */
	}
}


/* End of File */
