/*****************************************************************************\
 **                                                                         **
 **  FILE:     visual.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Interface with ncurses and /dev/vcsa in a civilised manner.  **
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
 * Revision 1.1  2001/04/16 14:51:22  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:14:55  alexios
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
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_KD_H 1
#include <linux/types.h>
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#include "visual.h"
#include "bbs.h"


int           autorefresh=1;
unsigned int  numrows=80;
unsigned int  numcolumns=25;
unsigned int  cursorx=0;
unsigned int  cursory=0;
unsigned int  wx1=0;
unsigned int  wy1=0;
unsigned int  wx2=79;
unsigned int  wy2=24;
int           lastcolumn=0;
int           attr=0x07;
unsigned char *screen=NULL;



void
initvisual()
{
  initscreen();
  initkeyboard();
  atexit(donevisual);
}


void
donevisual()
{
  donekeyboard();
  donescreen();
}
