/*****************************************************************************\
 **                                                                         **
 **  FILE:     telecon.test.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 1.0                                    **
 **  PURPOSE:  Test teleconference plugin.                                  **
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
 * $Id: telecon.test.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: telecon.test.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:41:37  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:19  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: telecon.test.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";




#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <telecon.h>
#include <teleconplugins.h>


int     lucky_number;


void
controllingpart ()
{
	print ("\033!JThis is the controlling part of the plugin.\n");
	print ("It behaves just like an ordinary Megistos BBS module ");
	print ("-- the plugin can interact with the user to establish ");
	print ("configuration options etc. \n");
	print ("Only the user who initially activates the plugin will ");
	print ("see this bit, IF a plug-in has it, of course.");
	print ("\033!)\n\n");

	for (lucky_number = -1; lucky_number <= 0;) {
		print ("Enter your lucky number (1-999): ");
		inp_get (3);
		lucky_number = atoi (inp_buffer);
	}
}


static char fx_prompt[8192];
struct pluginmsg p;

char   *
fx_test (struct chanusr *u)
{
	sprintf (fx_prompt,
		 "\033!WHello %s, %s's lucky number is %d.\n%s Says '%s'\033!)\n",
		 u->userid, thisuseracc.userid, lucky_number, p.userid,
		 p.text);
	return fx_prompt;
}


char   *
fx_end (struct chanusr *u)
{
	strcpy (fx_prompt, "Finished with plugin, removing...\n");
	return fx_prompt;
}


void
run ()
{
	int     n;
	int     a = 0;

	for (a = 0; a < 10;) {
		n = msgrcv (qid, (struct msg_buffer *) &p,
			    sizeof (p) - sizeof (long), 0, IPC_NOWAIT);
		if (n > 0) {
			a++;
			broadcastchnall (channel, fx_test, 1);
		}
		usleep (50000);
	}
	broadcastchnall (channel, fx_end, 1);
}


int
main (int argc, char *argv[])
{
	mod_setprogname (argv[0]);
	initplugin (argc, argv);

	controllingpart ();

	becomeserver ();

	run ();

	exit (0);
}


/* End of File */
