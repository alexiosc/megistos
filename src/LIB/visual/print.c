/*****************************************************************************\
 **                                                                         **
 **  FILE:     print.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  String printing, scrolling, etc.                             **
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
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
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
#include "bbs.h"
#undef va_start
#define WANT_VARARGS_H 1


void
setrefresh(int onoff)
{
  autorefresh=onoff;
}


void
setwindow(int x1,int y1,int x2,int y2)
{
  wx1=x1;
  wy1=y1;
  wx2=x2;
  wy2=y2;
}


void
vscroll(int delta)
{
  if(!delta)return;
  else if(delta>0){
    register unsigned char *ofs1, *ofs2;
    register int i;
    int tmp;
    if(delta>NUMROWS)delta=NUMROWS;
    ofs1=&screen[wy1*2*numcolumns+wx1*2];
    ofs2=ofs1+delta*numcolumns*2;

    for(i=delta;i<NUMROWS;i++){
      memcpy(ofs1,ofs2,NUMCOLUMNS*2);
      ofs1+=numcolumns*2;
      ofs2+=numcolumns*2;
    }
    tmp=autorefresh;
    setrefresh(0);

    setblock(wx1,wy1+NUMROWS-delta,wx2,wy2,attr,32);
    setrefresh(tmp);
    dumpscreen();
  } else if(delta<0){
    register int y;
    register unsigned char *ofs1, *ofs2;
    delta=-delta;

    if(delta>numrows)delta=numrows;
    ofs1=&screen[wy2*numcolumns*2];
    ofs2=&screen[(wy2-delta)*numcolumns*2];
    for(y=NUMROWS-delta;y>=0;y--){
      memcpy(ofs1,ofs2,NUMCOLUMNS*2);
      ofs1-=numcolumns*2;
      ofs2-=numcolumns*2;
    }
    setblock(wx1,wy1,wx2,wy2+delta,attr,32);
  }
}


void
vnewline()
{
  lastcolumn=0;
  cursorx=0;
  cursory++;
  if(cursory>=NUMROWS){
    cursory=NUMROWS-1;
    vscroll(1);
  } else if(autorefresh)cursorxy(cursorx,cursory);
}


void
vputat(int x, int y, unsigned char attr, unsigned char chr)
{
  register int ofs=(wx1+x)*2+(wy1+y)*numcolumns*2;
  register unsigned char *c=&chr;

  screen[ofs]=xlation_table[*c];
  screen[ofs+1]=attr;
  if(autorefresh)dumpchar(ofs,wx1+x,wy1+y);
}


void
vputch(unsigned char chr)
{
  switch(chr){
  case '\n':
    cursorx=0;
    vnewline();
    break;
  default:
    if(!lastcolumn&&(cursorx<NUMCOLUMNS-1)){
      vputat(cursorx,cursory,attr,chr);
      cursorx++;
    } else if(!lastcolumn&&(cursorx==NUMCOLUMNS-1)){
      vputat(cursorx,cursory,attr,chr);
      lastcolumn=1;
    } else if(lastcolumn){
      vnewline();
      vputat(cursorx,cursory,attr,chr);
      cursorx++;
      lastcolumn=0;
    }
  }
}


void
vprint(format,va_alist)
char *format;
va_dcl
{
  va_list       args;
  unsigned char buf[65536],*cp;

  va_start(args);
  vsprintf(buf,format,args);
  va_end(args);

  for(cp=buf;*cp;cp++)vputch(*cp);
  if(autorefresh)cursorxy(cursorx,cursory);
}


void
vprintat(x,y,format,va_alist)
int x,y;
char *format;
va_dcl
{
  va_list       args;
  unsigned char buf[65536],*cp;
  int tmp;

  va_start(args);
  vsprintf(buf,format,args);
  va_end(args);

  tmp=autorefresh;
  setrefresh(0);
  for(cp=buf;*cp;cp++){
    vputat(x,y,attr,*cp);
    x=(x+1)%NUMCOLUMNS;
    if(!x)y=(y+1)%NUMROWS;
  }
  setrefresh(tmp);
  if(autorefresh){
    dumpscreen();
    cursorxy(cursorx,cursory);
  }
}
