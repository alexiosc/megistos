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
 * Revision 1.1  2001/04/16 14:55:33  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:46  alexios
 * Initial checkin.
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


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif




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
#include "mailcleanup.h"


void
doreindex()
{
  fflush(stdout);
  fflush(stderr);
  if(!getuid()){
    system("su bbs -c "BINDIR"/mailfixup");
  } else {
    system(BINDIR"/mailfixup");
  }
}
