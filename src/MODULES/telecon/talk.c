/*****************************************************************************\
 **                                                                         **
 **  FILE:     talk.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, talking to users                            **
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
 * Revision 1.2  2001/04/16 21:56:33  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.4  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/08/11 10:21:33  alexios
 * Fixed a couple of potentially serious problems.
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
const char *__RCS=RCS_VER;
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


static char tmp[16384], tmp2[4096];


int
checkax()
{
  if(thisuseraux.access&CUF_READONLY){
    prompt(TLKSQU);
    return 0;
  }
  return 1;
}


static char *
fx_say(struct chanusr *u)
{
  tmp[0]=out_buffer[0]=0;
  sprintf(out_buffer,msg_getl(TFROM,othruseracc.language-1),
	  getcolour(),thisuseracc.userid,tmp2);
  strcpy(tmp,msg_getl(TDELIM,othruseracc.language-1));
  strcat(tmp,out_buffer);
  return tmp;
}


void
say(char *s)
{
  if(!checkax())return;

  strcpy(tmp2,s);
  if(broadcast(fx_say)>0)prompt(TSENT);
  else prompt(SIU0);
}


void
whisper(char *s)
{
  char *cp=s, userid[256];
  int i;

  if(!checkax())return;

  cp=&s[strlen(s)];
  while((cp!=s)&&(*cp==32))*(cp--)=0;
  cp=s;

  if(sameas(inp_buffer,"/")||sameas(inp_buffer,"WHISPER TO")){
    prompt(HLPWHIS);
    cnc_end();
    return;
  }

  if(s[0]=='/'){
    cp=s+1;
    if(sscanf(cp,"%s %n",userid,&i)!=1 || strlen(&cp[i])==0){
      prompt(HLPWHIS);
      cnc_end();
      return;
    } else cp+=i;
  } else if(sameto("WHISPER TO ",s)){
    char dummy1[16],dummy2[16];

    if(sscanf(s,"%s %s %s %n",dummy1,dummy2,userid,&i)!=3 ||
       strlen(&cp[i])==0){
      prompt(HLPWHIS);
      cnc_end();
      return;
    } else cp=&s[i];
  } else return;

  if(!tlcuidxref(userid,1)){
    cnc_end();
    prompt(UIDNINC);
    return;
  }
  if(usr_insys(userid,1)&&((thisuseronl.flags&OLF_BUSY)==0)){
    usr_injoth(&othruseronl,msg_get(TDELIM),0);
    sprintf(out_buffer,msg_get(TFROMP),getcolour(),thisuseracc.userid,cp);
    usr_injoth(&othruseronl,out_buffer,0);
    prompt(TSENTP,othruseronl.userid);
  }
}


static char *fxuser, *fxmsg;


static char *
fx_sayto(struct chanusr *u)
{
  usr_injoth(&othruseronl,msg_get(TDELIM),0);
  if(sameas(u->userid,fxuser)){
    sprintf(out_buffer,msg_getl(TFROM2U,othruseracc.language-1),
	    getcolour(),thisuseracc.userid,fxmsg);
  } else {
    sprintf(out_buffer,msg_getl(TFROMT,othruseracc.language-1),
	    getcolour(),thisuseracc.userid,fxuser,fxmsg);
  }
  return out_buffer;
}


void
sayto(char *s)
{
  char *cp=s, userid[256];
  int i;
  
  if(!checkax())return;

  cp=&s[strlen(s)];
  while((cp!=s)&&(*cp==32))*(cp--)=0;
  cp=s;

  if(sameas(inp_buffer,"\\")||sameas(inp_buffer,">")||sameas(inp_buffer,"SAY TO")){
    prompt(HLPSAY);
    cnc_end();
    return;
  }

  if(s[0]=='\\'||s[0]=='>'){
    cp=s+1;
    if(sscanf(cp,"%s %n",userid,&i)!=1 || strlen(&cp[i])==0){
      prompt(HLPSAY);
      cnc_end();
      return;
    } else cp+=i;
  } else if(sameto("SAY TO ",s)){
    if(sscanf(s,"%*s %*s %s %n",userid,&i)!=3
       || strlen(&cp[i])==0){
      prompt(HLPSAY);
      cnc_end();
      return;
    } else cp=&s[i];
  } else return;

  if(!tlcuidxref(userid,1)){
    cnc_end();
    prompt(UIDNINC);
    return;
  }
  if(usr_insys(userid,1)&&((thisuseronl.flags&OLF_BUSY)==0)){
    int i;
    if(sameas(userid,thisuseracc.userid)){
      prompt(TWHYU);
      cnc_end();
      return;
    }
    fxuser=userid;
    fxmsg=cp;
    i=broadcast(fx_sayto);
    if(i>0)prompt(TSENTT,userid);
    else if(!i)prompt(SIU0);
  }
}
