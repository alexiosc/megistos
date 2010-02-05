/*****************************************************************************\
 **                                                                         **
 **  FILE:     keyboard.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Keyboard part of the advanced visual library.                **
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
 * $Id: keyboard.c,v 1.3 2001/04/22 14:49:05 alexios Exp $
 *
 * $Log: keyboard.c,v $
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id: keyboard.c,v 1.3 2001/04/22 14:49:05 alexios Exp $"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_NCURSES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_KD_H 1
#include <linux/types.h>
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#include "visual.h"


static unsigned long oldmetaflag;


void
initkeyboard()
{
  ioctl(0,KDGKBMETA,&oldmetaflag);
  ioctl(0,KDSKBMETA,K_ESCPREFIX);
  cbreak();
  noecho();
  keypad(stdscr,TRUE);
  meta(stdscr,1);
}


void
donekeyboard()
{
  ioctl(0,KDSKBMETA,oldmetaflag);
}
