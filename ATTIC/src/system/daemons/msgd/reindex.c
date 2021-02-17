/*****************************************************************************\
 **                                                                         **
 **  FILE:     reindex.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.1                                     **
 **            B, August 1996, Version 0.2                                  **
 **            C, August 1996, Version 0.3                                  **
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
 * $Id: reindex.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: reindex.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2004/02/29 16:32:58  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 16:28:24  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:27:56  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:16:29  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:16:40  alexios
 * First registered revision. Adequate.
 *
 *
 */



static const char rcsinfo[] = "$Id: reindex.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



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

#include "bbs.h"
#include "msgd.h"
#include "ecdbase.h"


void
doreindex ()
{
	char   *fname = mkfname (BINDIR "/mailfixup");
	char    command[4096];

	sprintf (command, "su bbs -c \"%s >&/dev/null &\"", fname);
	system (command);
}
