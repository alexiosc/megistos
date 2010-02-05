/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.bulletins.c                                          **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Off line mailer, bulletin plugin                             **
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
 * $Id: offline.bulletins.c,v 2.1 2004/09/13 19:55:34 alexios Exp $
 *
 * $Log: offline.bulletins.c,v $
 * Revision 2.1  2004/09/13 19:55:34  alexios
 * Changed email addresses.
 *
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:21  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 15:46:41  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:20:15  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:59  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:53:22  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: offline.bulletins.c,v 2.1 2004/09/13 19:55:34 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "offline.bulletins.h"
#include <mailerplugins.h>
#include "mbk_offline.bulletins.h"

#define __MAILER_UNAMBIGUOUS__
#include <mbk/mbk_mailer.h>

#define __BULLETINS_UNAMBIGUOUS__
#include "../mbk_bulletins.h"

#define __EMAILCLUBS_UNAMBIGUOUS__
#include <mbk/mbk_emailclubs.h>


promptblock_t *msg;
promptblock_t *bulletins_msg;
promptblock_t *emailclubs_msg;

int     sopkey;
int     defblt;
int     defansi;
char   *bltidfn;

void
init ()
{
	mod_init (INI_ALL);

	emailclubs_msg = msg_open ("emailclubs");
	sopkey = msg_int (EMAILCLUBS_SOPKEY, 0, 129);
	msg_close (emailclubs_msg);

	bulletins_msg = msg_open ("bulletins");

	msg = msg_open ("offline.bulletins");
	defblt = msg_bool (DEFBLT);
	defansi = msg_bool (DEFANSI);
	bltidfn = msg_string (BLTIDFN);

	msg_setlanguage (thisuseracc.language);
}


void
done ()
{
	msg_close (msg);
}


void
warn ()
{
	fprintf (stderr, "This is a Mailer plugin. ");
	fprintf (stderr, "It should not be run as an ordinary module.\n");
	exit (1);
}


mod_info_t mod_info_offline_bulletins = {
	"offline.bulletins",
	"Mailer Plugin: Bulletins",
	"Alexios Chouchoulas <alexios@bedroomlan.org>",
	"Packages off-line requested bulletins and lists of bulletins.",
	RCS_VER,
	"1.0",
	{0, NULL},		/* Login handler */
	{0, NULL},		/* Interactive handler */
	{0, NULL},		/* Install logout handler */
	{0, NULL},		/* Hangup handler */
	{0, NULL},		/* Cleanup handler */
	{0, NULL}		/* Delete user handler */
};


char   *progname;


int
main (int argc, char *argv[])
{
	progname = mod_info_offline_bulletins.progname;
	mod_setinfo (&mod_info_offline_bulletins);

	if (argc != 2)
		return mod_main (argc, argv);

	if (!strcmp (argv[1], "--setup")) {
		atexit (done);
		init ();
		setup ();
	} else if (!strcmp (argv[1], "--download")) {
		atexit (done);
		init ();
		return obdownload ();
	} else if (!strcmp (argv[1], "--upload")) {
		atexit (done);
		init ();
		return obupload ();
	}

	/* This should only return help, info, etc */
	return mod_main (argc, argv);
}


/* End of File */
