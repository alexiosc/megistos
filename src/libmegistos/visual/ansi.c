/*****************************************************************************\
 **                                                                         **
 **  FILE:     ansi.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Convert ANSI directives into characters and attributes       **
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
 * $Id: ansi.c,v 1.3 2001/04/22 14:49:05 alexios Exp $
 *
 * $Log: ansi.c,v $
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id: ansi.c,v 1.3 2001/04/22 14:49:05 alexios Exp $"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_NCURSES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_KD_H 1
#include <linux/types.h>
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#include "visual.h"
#include "bbs.h"


static int colorxl[8]={0,4,2,6,1,5,3,7};


void
printansi(char *s)
{
  unsigned char c;
  char parms[1024], *cp, *ep;
  int state=0, len=0, n,y,x, sx=0,sy=0;
  int fg=7, bg=0, bold=0, tmp=autorefresh;
  char *msgbuf=s;

  setrefresh(0);
  while ((c=*msgbuf++)!=0){
    if(c==13)continue;
    if (c==27 && !state) state=1;
    else if (c=='[' && state==1){
      state=2;
      len=0;
      parms[0]=0;
    } else if(state==2){
      if(isdigit(c) || c==';') {
	parms[len++]=c;
	parms[len]=0;
	parms[len+1]=0;
	len=len%77;
      } else {
	state=0;
	switch(c) {
	case 'A':
	  n=atoi(parms);
	  if(!n)n++;
	  cursorxy(cursorx,cursory-n);
	  break;
	case 'B':
	  n=atoi(parms);
	  if(!n)n++;
	  cursorxy(cursorx,min(wy2-wy1,cursory+n));
	  break;
	case 'C':
	  n=atoi(parms);
	  if(!n)n++;
	  cursorxy(min(wx2-wx1,cursorx+n),cursory);
	  break;
	case 'D':
	  n=atoi(parms);
	  if(!n)n++;
	  cursorxy(cursorx-n,cursory);
	  break;
	case 'H':
	  x=y=0;
	  sscanf(parms,"%d;%d",&x,&y);
	  if(x)x--;
	  if(y)y--;
	  cursorxy(x,y);
	  break;
	case 'J':
	  clearscreen(attr,32);
	  cursorxy(0,0);
	  break;
	case 'K':
	  cleartoeol(attr,32);
	  break;
	case 'm':
	  cp=ep=parms;
	  while(*cp){
	    while(*ep && *ep!=';')ep++;
	    *(ep++)=0;
	    n=atoi(cp);
	    switch (n) {
	    case 0:
	      attr=0x07;
	      fg=7;
	      bg=0;
	      bold=0;
	      break;
	    case 1:
	      attr|=0x08;
	      bold=1;
	      break;
	    case 2:
	      attr&=~0x08;
	      break;
	    case 4:
	      attr&=~0x07;
	      attr|=0x01;
	      fg=4;
	      break;
	    case 5:
	      attr|=0x80;
	      attron(A_BLINK);
	      break;
	    case 7:
	      {
		int f=(attr&0x07)<<4;
		int b=(attr&0x70)>>4;
		attr&=~0x77;
		attr|=f+b;
		n=fg;
		fg=bg;
		bg=n;
	      }
	      break;
	    case 21:
	    case 22:
	      attr&=~0x08;
	      bold=0;
	      break;
	    case 25:
	      attr&=~0x80;
	      break;
	    default:
	      if (n>= 30 && n<=37) {
		fg=colorxl[n-30];
		attr&=~0x07;
		attr|=fg;
	      } else if (n>=40 && n<=47) {
		bg=(colorxl[n-40])<<4;
		attr&=~0x70;
		attr|=bg;
	      }
	    }
	    cp=ep;
	  }
	  break;
	case 's':
	  sx=cursorx;
	  sy=cursory;
	  break;
	case 'u':
	  cursorxy(sx,sy);
	  break;
	}
      }
    } else if(!state)vputch(c);
  }
  setrefresh(tmp);
  if(autorefresh)dumpscreen();
}
