/*****************************************************************************\
 **                                                                         **
 **  FILE:     put.c                                                        **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Dumping screen images on the screen                          **
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
 * Revision 1.1  2001/04/16 14:51:09  alexios
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
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_NCURSES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_KD_H 1
#include <linux/types.h>
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#include "visual.h"


#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

void
vputscreen(unsigned char *source)
{
  memcpy(screen,source,numrows*numcolumns*2);
  if(autorefresh)dumpscreen();
}


void
vputblock(unsigned char *source, int x, int y, int w, int h)
{
  register char *ofss=source;
  register char *ofst;
  register i;

  if(w==0||h==0)return;
  x=min(numcolumns-1,max(0,x));
  y=min(numrows-1,max(0,y));
  if(x+w-1>=numcolumns)w=numcolumns-x;
  if(y+h-1>=numrows)h=numrows-y;

  ofst=&screen[x*2+y*2*numcolumns];

  for(i=0;i<h;i++){
    memcpy(ofst,ofss,w*2);
    ofss+=w*2;
    ofst+=numcolumns*2;
  }

  if(autorefresh)dumpscreen();
}


void
vgetblock(unsigned char *target, int x, int y, int w, int h)
{
  register char *ofst=target;
  register char *ofss;
  register i;

  if(w==0||h==0)return;
  x=min(numcolumns-1,max(0,x));
  y=min(numrows-1,max(0,y));
  if(x+w-1>=numcolumns)w=numcolumns-x;
  if(y+h-1>=numrows)h=numrows-y;

  ofss=&screen[x*2+y*2*numcolumns];
  for(i=0;i<h;i++){
    memcpy(ofst,ofss,w*2);
    ofst+=w*2;
    ofss+=numcolumns*2;
  }
}


int
vfputblock(const char *fname, int x, int y, int w, int h)
{
  FILE *fp;
  unsigned char buf[64<<10];

  if((fp=fopen(fname,"r"))==NULL)return 0;
  fread(buf,64<<10,1,fp);
  fclose(fp);
  vputblock(buf,x,y,w,h);
  return 1;
}
