/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbslogout.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 1.0 alpha                              **
 **  PURPOSE:  Perform user logout sequence                                 **
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
 * $Id: bbslogout.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: bbslogout.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/23 08:18:08  alexios
 * Corrected minor #include discrepancies.
 *
 * Revision 1.4  2003/12/22 17:23:36  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1998/12/27 16:20:53  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 0.5  1998/07/24 10:25:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:15:33  alexios
 * This program is now stable.
 *
 * Revision 0.3  1997/11/06 20:04:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/08/30 13:09:35  alexios
 * Cleaned up the code (not too much work there). Set the flag
 * OLF_LOGGEDOUT so that bbsd knows this was a normal discon-
 * nection.
 *
 * Revision 0.1  1997/08/28 11:14:36  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] = "$Id: bbslogout.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TERMIOS_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_TYPES_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <mbk/mbk_login.h>


promptblock_t *msg;



void
resetlinestatus ()
{
	channel_status_t status;

	channel_getstatus (thisuseronl.channel, &status);
	status.result = LSR_LOGOUT;
	status.baud = atoi (getenv ("BAUD"));
	status.user[0] = 0;
	channel_setstatus (thisuseronl.channel, &status);
}


int
main (int argc, char *argv[])
{
	char    fname[256];
	int     hup = !strcmp (argv[0], "bbshangup");

	mod_setprogname (argv[0]);

	mod_init (INI_ALL);
	msg = msg_open ("login");
	msg_setlanguage (thisuseracc.language);

	if (!hup) {
		fmt_setverticalformat (0);
		prompt (SEEYA);
		thisuseronl.flags |= OLF_LOGGEDOUT;
	}

	thisuseracc.datelast = today ();

	mod_done (INI_ALL);
	channel_disconnect (thisuseronl.emupty);

	sprintf (fname, "%s/%s", mkfname (ONLINEDIR), thisuseracc.userid);
	unlink (fname);

	resetlinestatus ();

	return 0;
}


/* End of File */
