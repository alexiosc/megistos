/*****************************************************************************\
 **                                                                         **
 **  BLACKJACK game for AcroGate Network                                    **
 **                                                                         **
 **  FILE:     bjack.c                                                      **
 **  AUTHORS:  Valis, Alexios                                               **
 **  REVISION: Under development                                            **
 **  PURPOSE:  Black Jack Teleconference plugin                             **
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
 * $Id: bjack.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: bjack.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:38  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/09/04 13:57:57  valis
 * first stable release, tidy up source code
 *
 * Revision 0.6  1999/09/01 22:18:56  valis
 * createidstr() replaced by MODULE_ID
 *
 * Revision 0.5  1999/08/28 18:18:37  valis
 * support for bbs prompt subsystem
 * logging functions implemented
 *
 * Revision 0.4  1999/08/24 11:56:34  valis
 * source in run() moved to bjutil.c as bj_loop()
 *
 * Revision 0.3  1999/08/24 08:51:23  valis
 * player sex support
 * various improvements
 *
 * Revision 0.2  1999/08/22 17:39:31  valis
 * author name changed
 *
 * Revision 0.1  1999/08/22 17:31:27  bbs
 * initial revision. almost working perfectly.
 *
 */


static const char rcsinfo[] =
    "$Id: bjack.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <signal.h>

#ifdef MEGISTOS_BBS

#include <megistos/bbs.h>
#include <telecon.h>
#include <teleconplugins.h>

#endif				/* MEGISTOS_BBS */

#include "bjver.h"
#include "bjconf.h"
#include "bjack.h"
#include "bjintrfc.h"



#ifdef BBSPROMPTS

#ifdef MEGISTOS_BBS
#include "mbk_bjack.h"
#endif

#else
#include <megistos/bjmsg.h>

#endif				/* BBSPROMPTS */


const char MODULE_ID[] =
    "BlackJack " BJ_MAJORVERSION "." BJ_MINORVERSION " [" BJ_COMPILED_BY "] #"
    BJ_MAKE_NUMBER " " BJ_DATE;


void
controllingpart ()
{
	srand (time (0));

#ifdef BBSPROMPTS

#ifdef MEGISTOS_BBS
	msg = msg_open ("bjack");
#endif				/* MEGISTOS_BBS */

#endif				/* BBSPROMPTS */

	bj_init ();

	STATUS = STAT_NOGAME;
	bj_channel = channel;

	pause_timer = time (0) + P_PAUSE_EXP;	/* wait for next game */
}


/* Honor the original teleconference test module */
void
run (void)
{
	bj_loop ();
}


/* Honor the turbo vision subsystem from turbo pascal */
void
end (void)
{

#ifdef BBSPROMPTS

#ifdef MEGISTOS_BBS
	msg_close (msg);
#endif				/* MEGISTOS_BBS */

#endif				/* BBSPROMPS */

}

#if 0
void
init_wdog_module (void)
{
	init_wdog ();
	set_params (30, getpid (), 15);

	wdog_pid = fork ();

	switch (wdog_pid) {
	case 0:{
			bj_logmsg
			    ("Starting watchdog module (parent pid = %i)",
			     getppid ());
			loop ();
			exit (0);
		};
		break;
	default:{
			bj_logmsg ("Parent pid=%i Child pid=%i", getpid (),
				   wdog_pid);
			return;
		};
		break;
	}
}
#endif


char   *
sv_bell ()
{
	if (player_list != NULL)
		return (player_list->flags & bjfPFIX) ? "" : "\007";
	return "\007";
}


int
main (int argc, char *argv[])
{

	bj_logmsg ("--- BJACK session begins [ %s.%s #%s ] ---",
		   BJ_MAJORVERSION, BJ_MINORVERSION, BJ_MAKE_NUMBER);

	atexit (end);

	mod_setprogname (argv[0]);

	initplugin (argc, argv);

	controllingpart ();

	becomeserver ();
	mod_init (INI_OUTPUT | INI_SYSVARS);
	out_addsubstvar ("@BELL@", sv_bell);

	run ();

	bj_logmsg ("--- BJACK session ends ---");

	return 0;
}


/* End of File */
