/*****************************************************************************\
 **                                                                         **
 **  FILE:     broadcast.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, broadcasting messages to other users        **
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
 * Revision 1.1  2001/04/16 14:58:22  alexios
 * Initial revision
 *
 * Revision 0.5  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:45:25  alexios
 * Rewrote channel engine to use directories for channels and
 * files for the header and user records. This makes sure no
 * strange filing bugs show up like before.
 *
 * Revision 0.3  1998/08/11 10:21:33  alexios
 * Cosmetic changes.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "telecon.h"
#include "mbk_telecon.h"


int
broadcastchnall(char *curchannel, char *(*fx)(struct chanusr *u), int all)
{
  struct chanusr *u;
  int count=0;

  if(!begscan(curchannel,TSM_PRESENT))return -1;

  for(;;){
    if((u=getscan())==NULL)break;
    if((u->flags&CUF_PRESENT) &&
       uinsys(u->userid,0)&&
       (all||strcmp(thisuseracc.userid,u->userid))){
      
      char *buf;
      
      if(othruseronl.flags&OLF_BUSY)continue;
      if(!(othruseronl.flags&OLF_INTELECON))continue;
      
      if((othruseronl.flags&OLF_INVISIBLE)==0)count++;
      
      if((buf=fx(u))!=NULL)injoth(&othruseronl,buf,0);
    }
  }
  
  endscan();

  return count;
}


int
broadcastchn(char *curchannel, char *(*fx)(struct chanusr *u))
{
  return broadcastchnall(curchannel, fx, 0);
}


int broadcast(char *(*fx)(struct chanusr *u))
{
  return broadcastchnall(curchannel,fx,0);
}


static int fxprompt;
static char tmp[16384];


static char *
fx_msg(struct chanusr *u)
{
  tmp[0]=outbuf[0]=0;
  strcpy(tmp,getmsglang(TDELIM,othruseracc.language-1));

  sprintf(outbuf,getmsglang(fxprompt,othruseracc.language-1),
	  getpfixlang(SEXM1,thisuseracc.sex==USX_MALE,othruseracc.language-1),
	  thisuseracc.userid);
  strcat(tmp,outbuf);
  return tmp;
}


static char *
fx_enter(struct chanusr *u)
{
  tmp[0]=outbuf[0]=0;
  strcpy(tmp,getmsglang(TDELIM,othruseracc.language-1));

  if(tlcu.entrystg[0]){
    sprintf(outbuf,getmsglang(ENTEXTS,othruseracc.language-1),
	    getcolour(),tlcu.entrystg);
    strcat(tmp,outbuf);
  } else {
    sprintf(outbuf,getmsglang(fxprompt,othruseracc.language-1),
	    getpfixlang(SEXM1,thisuseracc.sex==USX_MALE,othruseracc.language-1),
	    thisuseracc.userid);
    strcat(tmp,outbuf);
  }
  return tmp;
}


static char *
fx_leave(struct chanusr *u)
{
  strcpy(tmp,getmsglang(TDELIM,othruseracc.language-1));

  if(tlcu.exitstg[0]){
    sprintf(outbuf,getmsglang(ENTEXTS,othruseracc.language-1),
	    getcolour(),tlcu.exitstg);
    strcat(tmp,outbuf);
  } else {
    sprintf(outbuf,getmsglang(fxprompt,othruseracc.language-1),
	    getpfixlang(SEXM1,thisuseracc.sex==USX_MALE,othruseracc.language-1),
	    thisuseracc.userid);
    strcat(tmp,outbuf);
  }
  return tmp;
}


void
usermsg(int pr)
{
  fxprompt=pr;
  broadcast(fx_msg);
}


void
userent(int pr)
{
  if(thisuseronl.flags&OLF_INVISIBLE)return;
  fxprompt=pr;
  broadcast(fx_enter);
}


void
userexit(int pr)
{
  if(thisuseronl.flags&OLF_INVISIBLE)return;
  fxprompt=pr;
  broadcast(fx_leave);
}


