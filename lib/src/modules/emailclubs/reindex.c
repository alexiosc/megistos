/*****************************************************************************\
 **                                                                         **
 **  FILE:     reindex.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.1                                     **
 **  PURPOSE:  Reindex/rethread message areas                               **
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
 * $Id$
 *
 * $Log$
 * Revision 1.5  2003/12/25 13:33:28  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.3  1998/12/27 15:17:13  alexios
 * Added autoconf support.
 *
 * Revision 1.2  1998/07/24 10:08:19  alexios
 * Upgraded to version 0.6 of library.
 *
 * Revision 1.1  1997/11/06 20:09:08  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/30 12:52:57  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_ERRNO_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mailcleanup.h"


void
doreindex ()
{
	fflush (stdout);
	fflush (stderr);
	if (!getuid ()) {
		char    cmd[1024];

		strcat (cmd, "su bbs -c ");
		strcat (cmd, mkfname (BINDIR "/mailfixup"));
		system (cmd);
	} else {
		char    cmd[1024];

		strcat (cmd, mkfname (BINDIR "/mailfixup"));
		system (cmd);
	}
}


/* End of File */
