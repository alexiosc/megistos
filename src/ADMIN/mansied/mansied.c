/*****************************************************************************\
 **                                                                         **
 **  FILE:     mansied.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 95, Version 0.1                                      **
 **  PURPOSE:  Edit files with formatting commands                          **
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
 * Revision 1.2  2001/04/16 21:56:28  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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
#dfeine WANT_SYS_TYPES_H 1
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mansied.h"


int         numlines=0;
int         topx=0, topy=0;
struct line *line=NULL;


void
title()
{
  char fname[256];

  clearscreen(0x00,32);
  attr=BG_GREEN|FG_WHITE;

  sprintf(fname,"%s/mansied/mansied.bin",BBSLIBDIR);
  vfputblock(fname,(numcolumns-80)/2,(numrows-25)/2,80,25);
  cursorxy(0,0);
  setrefresh(0);
  dumpscreen();
  getch();
  clearscreen(0x07,0x20);
  dumpscreen();
}


void
run()
{
  int c=0;

  for(;c!='q';){
    showstatus();
    c=getch();
  }
}


void
main()
{
  initvisual();
  initmodule(INITOUTPUT|INITSIGNALS);
  /*setxlationtable(TRT_7BIT); */

  title();
  run();
  donevisual();
}
