/*****************************************************************************\
 **                                                                         **
 **  FILE:     invitations.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 96, Version 0.5                                      **
 **  PURPOSE:  Teleconferences, inviting and uninviting users.              **
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
 * Revision 1.1  2001/04/16 14:58:24  alexios
 * Initial revision
 *
 * Revision 0.3  1998/12/27 16:10:27  alexios
 * Added autoconf support. One slight bug fix.
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


void
invite(char *s)
{
  char userid[2048]={0};
  int i;

  i=sscanf(s,"%*s %s",userid);

  if((i<1)||sameas(userid,"?")){
    prompt(INVHELP);
    return;
  }

  if(sameas(userid,"ALL")){
    setchanax(CHF_OPEN);
    prompt(INOKALL);
    if(!sameas(thisuseronl.telechan,thisuseracc.userid))prompt(INVWRN);
    return;
  }

  if(!uidxref(userid,1)){
    prompt(IUNKUSR,userid);
    return;
  }
  
  if(sameas(thisuseracc.userid,userid)){
    prompt(IWHYU);
    return;
  }

  uinsys(userid,0);

  setusrax(thisuseracc.userid,userid,0,CUF_EXPLICIT|CUF_ACCESS,0);

  {
    char article[2048];

    strcpy(article,getpfix(IRECHE,thisuseracc.sex==USX_MALE));

    sprintf(outbuf,getmsglang(IRECIP,othruseracc.language-1),
	    article,thisuseracc.userid,
	    getpfix(IRECHIS,thisuseracc.sex==USX_MALE));

    if(!injoth(&othruseronl,outbuf,0)){
      prompt(UNNOT,othruseronl.userid);
    }
    
    if(othruseronl.flags&OLF_INTELECON){
      sprintf(outbuf,getmsglang(IJOIN,othruseracc.language-1),
	      thisuseracc.userid);
      injoth(&othruseronl,outbuf,0);
    }
  }
  
  prompt(ISENDR,getpfix(ISNDM,othruseracc.sex==USX_MALE),userid);

  if(!sameas(thisuseronl.telechan,thisuseracc.userid))prompt(INVWRN);
}


static char fx_sex, fx_id[24];


static char *
fx_kickout(struct chanusr *u)
{
  char tmp[8192];
  strcpy(outbuf,getmsglang(TDELIM,othruseracc.language-1));

  sprintf(tmp,getmsglang(UOTHER,othruseracc.language-1),
	  getpfixlang(SEXM1,fx_sex==USX_MALE,othruseracc.language-1),
	  fx_id);
  strcat(outbuf,tmp);
  return outbuf;
}


void
uninvite(char *s)
{
  char userid[2048]={0};
  int i;

  i=sscanf(s,"%*s %s",userid);

  if((i<1)||sameas(userid,"?")){
    prompt(UNVHELP);
    return;
  }

  if(sameas(userid,"ALL")){
    setchanax(CHF_PRIVATE);
    prompt(UNOKALL);
    return;
  }

  if(!uidxref(userid,1)){
    prompt(UUNKUSR,userid);
    return;
  }
  
  if(sameas(thisuseracc.userid,userid)){
    prompt(UWHYU);
    return;
  }

  uinsys(userid,0);

  {
    char article[2048];

    strcpy(article,getpfix(URECHE,thisuseracc.sex==USX_MALE));

    sprintf(outbuf,getmsglang(URECIP,othruseracc.language-1),
	    article,thisuseracc.userid,
	    getpfix(URECHIS,thisuseracc.sex==USX_MALE));

    if(!injoth(&othruseronl,outbuf,0)){
      prompt(UNNOT,othruseronl.userid);
    }
    
    setusrax(thisuseracc.userid,userid,0,CUF_EXPLICIT,CUF_PRESENT|CUF_ACCESS);

    if(othruseronl.flags&OLF_INTELECON){
      char tty[16];

      strcpy(tty,othruseronl.channel);
      strcpy(fx_id,userid);
      fx_sex=othruseracc.sex;
      if(!strcmp(othruseronl.telechan,thisuseracc.userid)){
	broadcastchn(thisuseracc.userid,fx_kickout);
      }
      sendmain(userid);
    }
  }
  
  prompt(USENDR,getpfix(USNDM,othruseracc.sex==USX_MALE),userid);
}


void
invitero(char *s)
{
  char userid[2048]={0};
  int i;

  i=sscanf(s,"%*s %s",userid);

  if((i<1)||sameas(userid,"?")){
    prompt(ROHELP);
    return;
  }

  if(sameas(userid,"ALL")){
    setchanax(CHF_READONLY);
    prompt(ROOKALL);
    if(!sameas(thisuseronl.telechan,thisuseracc.userid))prompt(INVWRN);
    return;
  }

  if(!uidxref(userid,1)){
    prompt(RUNKUSR,userid);
    return;
  }
  
  if(sameas(thisuseracc.userid,userid)){
    prompt(RWHYU);
    return;
  }

  uinsys(userid,0);

  setusrax(thisuseracc.userid,userid,0,CUF_EXPLICIT|CUF_ACCESS|CUF_READONLY,0);

  {
    char article[2048];

    strcpy(article,getpfix(RRECHE,thisuseracc.sex==USX_MALE));

    sprintf(outbuf,getmsglang(RRECIP,othruseracc.language-1),
	    article,thisuseracc.userid,
	    getpfix(RRECHIS,thisuseracc.sex==USX_MALE));

    if(!injoth(&othruseronl,outbuf,0)){
      prompt(UNNOT,othruseronl.userid);
    }
    
    if(othruseronl.flags&OLF_INTELECON){
      sprintf(outbuf,getmsglang(RJOIN,othruseracc.language-1),
	      thisuseracc.userid);
      injoth(&othruseronl,outbuf,0);
    }
  }
  
  prompt(RSENDR,getpfix(RSNDM,othruseracc.sex==USX_MALE),userid);

  if(!sameas(thisuseronl.telechan,thisuseracc.userid))prompt(INVWRN);
}



