/*****************************************************************************\
 **                                                                         **
 **  FILE:     thingy.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  High level operations and objects                            **
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
#undef va_start
#define WANT_VARARGS_H 1


static thingyID=0;

struct thingy *rootthingy=NULL;
struct thingy *curthingy=NULL;
int           quit=0;


void
initthingies()
{
  rootthingy=newthingy(NULL,&TPR_ROOT,0,0,numcolumns-1,numrows-1,0);
}


struct thingy *
newthingy(under,prototype,x,y,w,h,flags)
struct thingy *under;
struct prototype *prototype;
int x,y,w,h,flags;
{
  struct thingy *thingy=alcmem(sizeof(struct thingy));

  if(!thingy)return NULL;
  if(prototype->datasize){
    if((thingy->data=alcmem(prototype->datasize))==NULL){
      free(thingy);
      return NULL;
    }
  } else thingy->data=NULL;

  thingy->thingyID=thingyID;
  thingyID=(thingyID+1)%0x7fffffff;
  
  thingy->x=x;
  thingy->y=y;
  thingy->w=w;
  thingy->h=h;
  thingy->flags=flags;
  thingy->init=prototype->init;
  thingy->draw=prototype->draw;
  thingy->done=prototype->done;
  thingy->handleinput=prototype->handleinput;
  thingy->focus=prototype->focus;
  thingy->defocus=prototype->defocus;

  thingy->parent=under;
  thingy->children=NULL;
  thingy->numchildren=0;
  thingy->focused=NULL;
  thingy->ontop=NULL;

  if(under){
    if(!under->children){
      under->children=thingy;
      thingy->next=thingy->prev=thingy;
    } else {
      struct thingy *oldprev=under->children->prev;
      oldprev->next=thingy;
      thingy->prev=oldprev;
      thingy->next=under->children;
      under->children->prev=thingy;
    }
    under->numchildren++;
    under->focused=under->ontop=thingy;
  }

  curthingy=thingy;
  if(thingy->init)(*thingy->init)();
  if(thingy->focus)(*thingy->focus)();
/*  if(thingy->draw)(*thingy->draw)(); */

  return thingy;
}


void
delthingy(struct thingy *thingy)
{
  struct thingy *parent=thingy->parent, *child=NULL;
  if(parent){
    int i,found=0;
    for(i=0,child=parent->children;i<parent->numchildren;i++,child=child->next){
      if(child->thingyID==thingy->thingyID){
	found=1;
	break;
      }
    }
    if(found){
      parent->numchildren--;
      child->next->prev=child->prev;
      child->prev->next=child->next;
      if(!parent->numchildren)parent->children=NULL;
      if(child==parent->children)parent->children=child->next;
      if(child==parent->focused)parent->focused=child->next;
      if(child==parent->ontop)parent->ontop=child->next;
    }
  }
  curthingy=child;
  if(child->defocus)(*child->defocus)();
  if(child->done)(*child->done)();
  if(thingy->data)free(thingy->data);
  free(thingy);
}


void
runthingies()
{
  dumpscreen();
  while(!quit){
    int key=getch();
    curthingy=rootthingy;
    if(rootthingy->handleinput)(*rootthingy->handleinput)(key);
    if(!autorefresh)dumpscreen();
  }
}


void
thingy_done()
{
  while(CT->numchildren&&CT->children)delthingy(CT->children);
}


int
thingy_handleinput(int key)
{
  int i,ok=0;
  struct thingy *p,*oldCT=CT;
  for(i=0,p=CT->focused;i<CT->numchildren&&p;i++,p=p->next){
    if(p->handleinput){
      CT=p;
      if((*p->handleinput)(key)){
	ok=1;
	break;
      }
    }
  }
  CT=oldCT;
  return ok;
}


void
thingy_draw()
{
  int i;
  struct thingy *p,*oldCT=CT;
  for(i=0,p=CT->ontop;i<CT->numchildren&&p;i++,p=p->next){
    CT=p;
    if(p->draw)(*p->draw)();
  }
  CT=oldCT;
}


void
thingy_setflag(int flag,int onoff)
{
  if(onoff)CT->flags|=flag;
  else CT->flags&=~flag;
}
