/*****************************************************************************\
 **                                                                         **
 **  FILE:     display.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 95, Version 0.1                                      **
 **  PURPOSE:  Display functions                                            **
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
 * Revision 1.1  2001/04/16 14:48:40  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:21  alexios
 * Initial checkin.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_NCURSES_H 1
#define WANT_SIGNAL_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_KD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mansied.h"


void
showstatus()
{
  cursorxy(0,0);
  setcolor(0x2f);
  printansi(" \033[33mF1\033[37m: Help  \033[33mF2\033[37m: ANSI  ");
  printansi("\033[33mF3\033[37m: Format  \033[33mF4\033[37m: Vars  ");
  printansi("\033[33mF5\033[37m: Misc  \033[33mF6\033[37m: Show");
  cleartoeol(0x2f,32);
  dumpblock(0,0,numcolumns-1,0);
}
