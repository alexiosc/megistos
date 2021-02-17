/*****************************************************************************\
 **                                                                         **
 **  FILE:     thingy_window.c                                              **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Window object                                                **
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
 * $Id: thingy_window.c,v 1.3 2001/04/22 14:49:06 alexios Exp $
 *
 * $Log: thingy_window.c,v $
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id: thingy_window.c,v 1.3 2001/04/22 14:49:06 alexios Exp $"
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


#define WINDOW_DATA ((struct window_data *)CT->data)


char frametypes[8][8]={
  {32, 32, 32, 32, 32, 32, 32, 32},
  {218,196,191,179,179,192,196,217},
  {201,205,187,186,186,200,205,188},
  {214,196,183,186,186,211,196,189},
  {213,205,184,179,179,212,205,190},
  {219,219,219,219,219,219,219,219},
  {219,223,219,219,219,219,220,219},
  {220,220,220,219,219,223,223,223}
};


void
window_init()
{
  if(CT->flags&TFL_WINDOW_SHADOW)CT->w+=2;
  WINDOW_DATA->title=NULL;
  WINDOW_DATA->overlap=alcmem(CT->w*CT->h*2);
  vgetblock(WINDOW_DATA->overlap,CT->x,CT->y,CT->w,CT->h);
  memcpy(WINDOW_DATA->frames,&frametypes[CT->flags&TFL_WINDOW_FRAME],8);
  memset(WINDOW_DATA->frameattr,0x07,8);
  WINDOW_DATA->titleattr=0x07;
  WINDOW_DATA->insideattr=0x07;
  WINDOW_DATA->shadowand=0x07;
  WINDOW_DATA->shadowor=0x00;
}


void
window_done()
{
  vputblock(WINDOW_DATA->overlap,CT->x,CT->y,CT->w,CT->h);
  if(WINDOW_DATA->title)free(WINDOW_DATA->title);
  free(WINDOW_DATA->overlap);
}


void
window_settitle(char *s)
{
  if(WINDOW_DATA->title)free(WINDOW_DATA->title);
  WINDOW_DATA->title=alcmem(strlen(s)+1);
  strcpy(WINDOW_DATA->title,s);
}


void
window_setframes(char *s)
{
  memcpy(WINDOW_DATA->frames,s,8);
}


void
window_setattrs(int frame, int title, int inside)
{
  memset(WINDOW_DATA->frameattr,frame,8);
  WINDOW_DATA->titleattr=title;
  WINDOW_DATA->insideattr=inside;
}


void
window_setshadow(int shadowand, int shadowor)
{
  WINDOW_DATA->shadowand=shadowand;
  WINDOW_DATA->shadowor=shadowor;
}


void
window_draw()
{
  int x1=CT->x;
  int y1=CT->y;
  int x2=x1+CT->w-1;
  int y2=y1+CT->h-1;
  int fsp=(CT->flags&TFL_WINDOW_FRAMESP)!=0;
  int i;
  char title[256];

  if(fsp)vputat(x1,y1,WINDOW_DATA->frameattr[0],32);
  vputat(x1+fsp,y1,WINDOW_DATA->frameattr[0],WINDOW_DATA->frames[0]);
  for(i=0;i<CT->w-2-2*fsp;i++)
    vputat(x1+fsp+1+i,y1,WINDOW_DATA->frameattr[1],WINDOW_DATA->frames[1]);
  if(fsp)vputat(x2,y1,WINDOW_DATA->frameattr[2],32);
  vputat(x2-fsp,y1,WINDOW_DATA->frameattr[2],WINDOW_DATA->frames[2]);

  strncpy(title,WINDOW_DATA->title,sizeof(title));
  title[min(sizeof(title)-1,CT->w-4-2*fsp)]=0;
  if(CT->w>4){
    int pos=fsp+(CT->w-2-strlen(title))/2;
    vputat(x1+pos,y1,WINDOW_DATA->titleattr,32);
    attr=WINDOW_DATA->titleattr;
    vprintat(x1+1+pos,y1,title);
    vputat(x1+pos+1+strlen(title),y1,WINDOW_DATA->titleattr,32);
  }

  for(i=0;i<CT->h-2;i++){
    if(fsp){
      vputat(x1,y1+1+i,WINDOW_DATA->frameattr[3],32);
      vputat(x2,y1+1+i,WINDOW_DATA->frameattr[4],32);
    }
    vputat(x1+fsp,y1+1+i,WINDOW_DATA->frameattr[3],WINDOW_DATA->frames[3]);
    vputat(x2-fsp,y1+1+i,WINDOW_DATA->frameattr[4],WINDOW_DATA->frames[4]);
  }

  if(fsp)vputat(x1,y2,WINDOW_DATA->frameattr[5],32);
  vputat(x1+fsp,y2,WINDOW_DATA->frameattr[5],WINDOW_DATA->frames[5]);
  for(i=0;i<CT->w-2-2*fsp;i++)
    vputat(x1+fsp+1+i,y2,WINDOW_DATA->frameattr[6],WINDOW_DATA->frames[6]);
  if(fsp)vputat(x2,y2,WINDOW_DATA->frameattr[7],32);
  vputat(x2-fsp,y2,WINDOW_DATA->frameattr[7],WINDOW_DATA->frames[7]);

  setblock(x1+1+fsp,y1+1,x2-1-fsp,y2-1,WINDOW_DATA->insideattr,32);
  if(CT->h>1){
    maskblock(x2+1,y1+1,x2+2,y2+1,
	      WINDOW_DATA->shadowand,WINDOW_DATA->shadowor);
  }
  if(CT->w>2){
    maskblock(x1+2,y2+1,x2+2,y2+1,
	      WINDOW_DATA->shadowand,WINDOW_DATA->shadowor);
  }

  thingy_draw();
}


struct prototype TPR_WINDOW={
  sizeof(struct window_data),
  window_init,
  window_draw,
  window_done,
  thingy_handleinput,
  NULL,
  NULL
};


