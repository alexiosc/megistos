/*****************************************************************************\
 **                                                                         **
 **  FILE:     screen.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Low level screen routines for the advanced visual library    **
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
#include "bbs.h"


static FILE *dfp;


static void
initcolours()
{
  int i,j;
  int cols[8]={COLOR_BLACK,COLOR_BLUE,COLOR_GREEN,COLOR_CYAN,
	   COLOR_RED,COLOR_MAGENTA,COLOR_YELLOW,COLOR_WHITE};
  
  if(!has_colors())return;
  start_color();
  for(i=0;i<8;i++)for(j=0;j<8;j++)init_pair(i+j*8,cols[i],cols[j]);
  attr=0x07;
}


void
initscreen()
{
  initscr();
  scrollok(stdscr,FALSE);
  leaveok(stdscr,FALSE);

  numrows=LINES;
  numcolumns=COLS;
  initcolours();

  screen=(char *)alcmem(numcolumns*numrows*2);
  setwindow(0,0,numcolumns-1,numrows-1);
}


void
donescreen()
{
  endwin();
  if(screen){
    free(screen);
    screen=NULL;
  }
  fclose(dfp);
}


void
dumpscreen()
{
  unsigned x,y,a=-1,ofs=0;
  if(wx1!=0||wy1!=0||wx2!=0||wy2!=0){
    dumpblock(wx1,wy1,wx2,wy2);
    return;
  }
  for(y=0;y<numrows;y++){
    move(y,0);
    ofs=y*numcolumns*2;
    for(x=0;x<numcolumns;x++){
      unsigned char *t=&screen[ofs+x*2+1], c;
      if((*t)!=a){
	setcolor(*t);
	a=*t;
      }
      if(*t==0x00 || *t==0x80){
	c=32;
      }
      else c=screen[ofs+x*2]&0xff;
      addch(c);
    }
  }
  cursorxy(cursorx,cursory);
  refresh();
}


void
dumpblock(int x1, int y1, int x2, int y2)
{
  unsigned x,y,a=-1,ofs=0;
  cursorxy(cursorx,cursory);
  for(y=y1;y<=y2;y++){
    move(y,x1);
    ofs=y*numcolumns*2;
    for(x=x1;x<=x2;x++){
      unsigned char *t=&screen[ofs+x*2+1],c;
      if((*t)!=a){
	setcolor(*t);
	a=*t;
      }
      if(*t==0x00 || *t==0x80)c=32;
      else c=screen[ofs+x*2]&0xff;
      addch(c);
    }
  }
  cursorxy(cursorx,cursory);
  refresh();
}


void
dumpchar(int ofs,int x, int y)
{
  unsigned char c=screen[ofs];
  unsigned char *a=&screen[ofs+1];

  setcolor(*a);
  if(*a==0x00 || *a==0x80)c=32;
  else c=screen[ofs+x*2]&0xff;
  mvaddch(y,x,c);
  cursorxy(cursorx,cursory);
  refresh();
}


void
cursorxy(int x, int y)
{
  cursorx=x;
  cursory=y;
  if(CT){
    CT->cursorx=x;
    CT->cursory=y;
  }
  move(wy1+cursory,wx1+cursorx);
  /*    mvcur(-1,-1,wy1+cursory,wx1+cursorx); */
}


void
setcolor(int a)
{
  int fg=a&0x07;
  int bg=(a&0x70)>>4;
  attrset(0);
  if(fg==0&&bg==0&&(a&8)){
    if(a&0x80)attron(A_BLINK);
    attron(COLOR_PAIR(7)+A_DIM);
  } else {
    if(a&0x08)attron(A_BOLD);
    if(a&0x80)attron(A_BLINK);
    attron(COLOR_PAIR((bg*8+fg)));
  }
}


void
clearscreen(unsigned char attr,unsigned char chr)
{
  register int i;
  register unsigned char a=attr&0xff;
  register unsigned char *c=&chr;
  (*c)&=0xff;
  for(i=0;i<numcolumns*numrows*2;i+=2){
    screen[i]=*c;
    screen[i+1]=a;
  }
  if(autorefresh)dumpscreen();
}


void
cleartoeol(unsigned char a,unsigned char chr)
{
  register int i;
  int x=cursorx,y=cursory,tmp=autorefresh,oldattr=attr;
  setrefresh(0);
  attr=a;
  for(i=cursorx;i<=wx2;i++)vputat(i,y,a,chr);
  attr=oldattr;
  setrefresh(tmp);
  cursorxy(x,y);
}


void
setblock(int x1,int y1,int x2,int y2,unsigned char attr,unsigned char chr)
{
  register int x,y,ofs=0;
  register unsigned char a=attr&0xff;
  register unsigned char *c=&chr;
  (*c)&=0xff;

  if(x1<0&&x2<0)return;
  if(x1>=numcolumns&&x2>=numcolumns)return;
  if(y1<0&&y2<0)return;
  if(y1>=numrows&&y2>=numrows)return;
  x1=min(numcolumns-1,max(0,x1));
  y1=min(numrows-1,max(0,y1));
  x2=min(numcolumns-1,max(0,x2));
  y2=min(numrows-1,max(0,y2));

  for(y=y1;y<=y2;y++){
    ofs=y*numcolumns*2+x1*2;
    for(x=x1;x<=x2;x++){
      screen[ofs++]=*c;
      screen[ofs++]=a;
    }
  }

  if(autorefresh)dumpblock(x1,y1,x2,y2);
}


void
maskblock(int x1,int y1,int x2,int y2,unsigned char attrand,unsigned char attror)
{
  register int x,y,ofs=0;

  if(x1<0&&x2<0)return;
  if(x1>=numcolumns&&x2>=numcolumns)return;
  if(y1<0&&y2<0)return;
  if(y1>=numrows&&y2>=numrows)return;
  x1=min(numcolumns-1,max(0,x1));
  y1=min(numrows-1,max(0,y1));
  x2=min(numcolumns-1,max(0,x2));
  y2=min(numrows-1,max(0,y2));

  for(y=y1;y<=y2;y++){
    ofs=y*numcolumns*2+x1*2+1;
    for(x=x1;x<=x2;x++){
      screen[ofs]=(screen[ofs]&attrand)|attror;
      ofs+=2;
    }
  }

  if(autorefresh)dumpblock(x1,y1,x2,y2);
}

