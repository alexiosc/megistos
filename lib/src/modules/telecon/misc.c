/*****************************************************************************\
 **                                                                         **
 **  FILE:     misc.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, miscellaneous commands                      **
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
 * Revision 0.7  1998/12/27 16:10:27  alexios
 * Added autoconf support. Minor bug fixes.
 *
 * Revision 0.6  1998/08/14 11:45:25  alexios
 * Migrated to the new channel engine.
 *
 * Revision 0.5  1998/08/11 10:21:33  alexios
 * Function chanscan() moved out.
 *
 * Revision 0.4  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/08/30 13:04:43  alexios
 * Changed bladcommand() calls to bbsdcommand().
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "telecon.h"
#include "mbk_telecon.h"


int
chanselect(const struct dirent *d)
{
  return(int)(d->d_name[0]!='.');
}


int
getchanax(char *user, char *chan)
{
  int ax=getusrax(chan,user);

  if(ax<0){
    prompt(-ax);
    return -1;
  }
  return ax;
}


void
joinchan(char *s)
{
  char chan[256];
  int i,ax;

  if(!checktick())return;

  i=sscanf(s,"%*s %s",chan);
  if((i==1)&&sameas(chan,"?"))prompt(JOINHLP);
  if(i!=1){
    if(sameas(thisuseracc.userid,thisuseronl.telechan))strcpy(chan,MAINCHAN);
    else strcpy(chan,thisuseracc.userid);
  }

  if(!sameas(chan,MAINCHAN)&&(chan[0]!='/'))tlcuidxref(chan,0);

  if(sameas(chan,curchannel)){
    prompt(SAMECHAN);
    return;
  }
  
  ax=getchanax(thisuseracc.userid,chan);
/*  print("CHAN=(%s), AX=%x\n",chan,ax); */
  if(ax<0)return;
  else if(!ax){
    prompt(CHNAX);
    return;
  }

  userexit(LFTCHN);
  leavechannel();
  enterchannel(chan);
  userent(ENTCHN);
  showinfo();
}


void
flagunlist(int on)
{
  if(on){
    chanusrflags(thisuseracc.userid,curchannel,CUF_UNLISTED,0);
    thisuseronl.flags|=OLF_TLCUNLIST;
    prompt(UNLSTON);
  } else {
    chanusrflags(thisuseracc.userid,curchannel,0,CUF_UNLISTED);
    thisuseronl.flags&=~OLF_TLCUNLIST;
    prompt(UNLSTOFF);
  }
}


void
sendmain(char *userid)
{
  sendaction(userid,ACT_DROPMAIN);
}


void
sendaction(char *userid,int action)
{
  if(usr_insys(userid,0)){
    othruseraux.action=action;
    bbsdcommand("user2",othruseronl.channel,"");
  }
}


void
actionhandler()
{
  signal(SIGMAIN,actionhandler);
  inp_cancel();
}


void
droptomain()
{
  if(strcmp(curchannel,MAINCHAN)){
    char tmp[24];
    leavechannel();
    prompt(DROPMAIN);
    strcpy(tmp,MAINCHAN);
    enterchannel(tmp);
    userent(ENTCHN);
    showinfo();
  }
}


static char sqtmp[24];
static int squelchopt;

char *
fx_squelch(struct chanusr *u)
{
  int lang=othruseracc.language-1;
  char moderator[1024], squelchee[1024];

  strcpy(moderator,msg_getunitl(SQUMODM,thisuseracc.sex==USX_MALE,lang));
  strcpy(squelchee,msg_getunitl(SQUMALE,othruseracc.sex==USX_MALE,lang));
  
  if(strcmp(sqtmp,u->userid)){
    sprintf(out_buffer,msg_getl(squelchopt?SQUOTHR:USQOTHR,lang),
	    moderator,squelchee,sqtmp);
  } else {
    sprintf(out_buffer,msg_getl(squelchopt?SQUYOU:USQYOU,lang),moderator);
  }
  return out_buffer;
}


void
squelch(char *s)
{
  char userid[2048]={0};
  int i;

  i=sscanf(s,"%*s %s",userid);

  if((i<1)||sameas(userid,"?")){
    prompt(SQHELP);
    return;
  }

  if(!key_owns(&thisuseracc,sopkey)&&strcmp(thisuseracc.userid,curchannel)
     &&(!(thisuseraux.access&CUF_MODERATOR))){
    prompt(SQNOAX);
    return;
  }
  
  if(!tlcuidxref(userid,1)){
    prompt(QUNKUSR,userid);
    return;
  }
  
  usr_insys(userid,0);
  
  if(strcmp(othruseronl.telechan,curchannel)||
     ((othruseronl.flags&OLF_INTELECON)==0)){
    prompt(QUNKUSR,userid);
    return;
  }

  setusrax(curchannel,userid,0,CUF_READONLY,0);

  strcpy(sqtmp,userid);
  squelchopt=1;
  broadcast(fx_squelch);

  prompt(SQUMOD,msg_getunit(SQUMALE,othruseracc.sex==USX_MALE),userid);
}


void
unsquelch(char *s)
{
  char userid[2048]={0};
  int i;

  i=sscanf(s,"%*s %s",userid);

  if((i<1)||sameas(userid,"?")){
    prompt(SQHELP);
    return;
  }

  if(!key_owns(&thisuseracc,sopkey)&&strcmp(thisuseracc.userid,curchannel)
     &&(!(thisuseraux.access&CUF_MODERATOR))){
    prompt(SQNOAX);
    return;
  }
  
  if(!tlcuidxref(userid,1)){
    prompt(QUNKUSR,userid);
    return;
  }
  
  usr_insys(userid,0);
  
  if(strcmp(othruseronl.telechan,curchannel)||
     ((othruseronl.flags&OLF_INTELECON)==0)){
    prompt(QUNKUSR,userid);
    return;
  }

  setusrax(curchannel,userid,0,0,CUF_READONLY);

  strcpy(sqtmp,userid);
  squelchopt=0;
  broadcast(fx_squelch);

  prompt(USQMOD,msg_getunit(SQUMALE,othruseracc.sex==USX_MALE),userid);
}


static char topictmp[64];

char *
fx_topic(struct chanusr *u)
{
  int lang=othruseracc.language-1;
  sprintf(out_buffer,msg_getl(TOPNEW,lang),
	  msg_getunitl(TOPM,thisuseracc.sex==USX_MALE,lang),
	  thisuseracc.userid,topictmp);
  return out_buffer;
}


void
topic(char *s)
{
  char *topic, *cp;
  int i=-1,n;

  if(!key_owns(&thisuseracc,sopkey)&&strcmp(thisuseracc.userid,curchannel)
     &&(!(thisuseraux.access&CUF_MODERATOR))){
    prompt(TOPNAX);
    return;
  }

  i=sscanf(s,"%*s %n",&n);

  if(i>=0){
    topic=&s[n];
    for(cp=topic+strlen(topic)-1;*cp==32;cp--){printf("(%s)\n",topic);*cp=0;}
  }

  if(i<0||!topic[0]){
    struct chanhdr *c;
    if((c=readchanhdr(curchannel))==NULL){
      error_fatal("Unable to read channel %s",curchannel);
    }
    
    c->topic[0]=0;
    
    writechanhdr(curchannel,c);
    
    prompt(TOPCLR);
    
    return;
  } else {
    struct chanhdr *c;
    if((c=readchanhdr(curchannel))==NULL){
      error_fatal("Unable to read channel %s",curchannel);
    }

    strncpy(c->topic,topic,sizeof(c->topic));
    
    writechanhdr(curchannel,c);

    prompt(TOPMOD,c->topic);

    strcpy(topictmp,c->topic);
    broadcast(fx_topic);
    
    return;
  }
}
