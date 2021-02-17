/*****************************************************************************\
 **                                                                         **
 **  FILE:     thingy_root.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Root object and default event handlers                       **
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
 * $Id: thingy_root.c,v 1.3 2001/04/22 14:49:05 alexios Exp $
 *
 * $Log: thingy_root.c,v $
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id: thingy_root.c,v 1.3 2001/04/22 14:49:05 alexios Exp $"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_NCURSES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_KD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#undef va_start
#define WANT_VARARGS_H 1
#include <bbsinclude.h>



void
root_init()
{
  CT->data[0]=32;
  CT->data[1]=0x07;
}


void
root_draw()
{
  setblock(CT->x,CT->y,CT->x+CT->w,CT->y+CT->h,CT->data[1],CT->data[0]);

  thingy_draw();
}


int
root_handleinput(int key)
{
  vprint("%d\n",key);
  quit=key=='q';
  return(1);
}


struct prototype TPR_ROOT={
  2,
  root_init,
  root_draw,
  thingy_done,
  root_handleinput,
  NULL,
  NULL
};


