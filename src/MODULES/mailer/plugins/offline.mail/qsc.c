/*****************************************************************************\
 **                                                                         **
 **  FILE:     setqsc.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Setup the clubs included in the QWK packet                   **
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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/18 21:44:48  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.6  1998/12/27 15:48:12  alexios
 * Added autoconf support. Minor fixes.
 *
 * Revision 0.5  1998/08/14 11:37:13  alexios
 * Fixed problem with deleting clubs from the mailer quickscan.
 *
 * Revision 0.4  1998/08/11 10:13:15  alexios
 * Used dirent calls instead of pipes to get listing of clubs.
 * Made club listing case-insensitive.
 *
 * Revision 0.3  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
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
#include "offline.mail.h"
#include "../../mailer.h"
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"


#define ADD  1
#define DEL -1


struct lastread         *uqsc=NULL;
static struct lastread  *uqscp=NULL;
static int              numclubs=0, clubp=0;

struct emailuser emlu;



static int
qsccmp(const void *A, const void *B)
{
  register char *a=((struct lastread*)A)->club;
  register char *b=((struct lastread*)B)->club;
  register char ca;
  register char cb;
again:
  ca=toupper(*a);
  cb=toupper(*b);
  if(ca!=cb)return ca-cb;
  if(!*a)return 0;
  a++,b++;
  goto again;
}


static void
sortqsc()
{
  qsort(uqsc,numclubs,sizeof(struct lastread),qsccmp);
}


struct lastread *
ustartqsc(char *uid)
{
  char fname[256];
  struct stat st;
  FILE *fp;

  if(uqsc){
    free(uqsc);
    uqsc=NULL;
  }
  if(uqscp)uqscp=NULL;
  numclubs=clubp=0;

  sprintf(fname,"%s/%s",mkfname(QSCDIR),uid);
  if(stat(fname,&st))return NULL;

  if((fp=fopen(fname,"r"))==NULL){
    error_fatalsys("Unable to open quickscan configuration %s",fname);
  }
  
  while(!feof(fp)){
    struct lastread x, *new;

    if(fread(&(x),sizeof(x),1,fp)==1){
      if(getclubax(&thisuseracc,x.club)>CAX_ZERO){
	new=alcmem(sizeof(x)*(numclubs+1));
	if(uqsc)memcpy(new,uqsc,sizeof(x)*numclubs);
	x.entrymsg=-1;
	memcpy(&new[numclubs],&x,sizeof(x));
	numclubs++;
	free(uqsc);
	uqsc=new;
      }
    }
  }
  fclose(fp);

  sortqsc();
  uqscp=uqsc;
  clubp=0;
  return uqsc;
}


struct lastread *
startqsc()
{
  return ustartqsc(thisuseracc.userid);
}


struct lastread *
getqsc()
{
  return uqscp;
}


struct lastread *
nextqsc()
{
  if(clubp+1>=numclubs)return NULL;
  clubp++;
  uqscp++;
  return uqscp;
}


struct lastread *
prevqsc()
{
  if(!clubp)return NULL;
  clubp--;
  uqscp--;
  return uqscp;
}


struct lastread *
findqsc(char *club)
{
  return bsearch(club,uqsc,numclubs,sizeof(struct lastread),qsccmp);
}


struct lastread *
goqsc(char *club)
{
  return uqscp=bsearch(club,uqsc,numclubs,sizeof(struct lastread),qsccmp);
}


struct lastread *
resetqsc()
{
  uqscp=uqsc;
  clubp=0;
  return uqscp;
}


int isfirstqsc()
{
  struct lastread *i;
  if(uqscp==uqsc)return 1;
  for(i=uqscp;i>=uqsc;i--)if(i->entrymsg>=0)return 0;
  return 1;
}


int islastqsc()
{
  return 0;
}


void
doneqsc()
{
  if(uqsc)free(uqsc);
  uqsc=uqscp=NULL;
  numclubs=clubp=0;
}


void
usaveqsc(char *uid)
{
  char fname[256];
  FILE *fp;

  if(uqsc==NULL)return;

  sortqsc();

  sprintf(fname,"%s/%s",mkfname(QSCDIR),uid);
  if((fp=fopen(fname,"w"))==NULL){
    error_fatalsys("Unable to create quickscan configuration %s",fname);
  }

  if(fwrite(uqsc,sizeof(struct lastread),numclubs,fp)!=numclubs){
    error_fatalsys("Unable to write quickscan configuration %s",fname);
  }

  fclose(fp);
}


void
saveqsc()
{
  usaveqsc(thisuseracc.userid);
}


void
addqsc(char *club, int lastmsg, int flags)
{
  struct lastread x, *p;

  if((p=findqsc(club))==NULL){
    memset(&x,0,sizeof(x));
    strcpy(x.club,club);
    if(lastmsg>=0)x.qwklast=lastmsg;
    x.flags=flags;
    
    p=alcmem(sizeof(x)*(numclubs+1));
    if(uqsc)memcpy(p,uqsc,sizeof(x)*numclubs);

    memcpy(&p[numclubs],&x,sizeof(x));
    numclubs++;
    if(uqsc)free(uqsc);
    uqsc=p;
    resetqsc();
  } else {
    if(lastmsg>=0)p->qwklast=lastmsg;
    p->flags&=~flags;
    p->flags|=flags;
  }
  saveqsc();
}


int
delqsc(char *club)
{
  struct lastread *p;

  p=findqsc(club);
  if(!p)return 0;

  if(!numclubs){
    doneqsc();
    return 0;
  }

  p->flags&=~LRF_INQWK;
  saveqsc();
  return 1;
}


static void
initialise()
{
  struct dirent **clubs;
  int n,i;

  n=scandir(mkfname(CLUBHDRDIR),&clubs,hdrselect,ncsalphasort);
  for(i=0;i<n;free(clubs[i]),i++){
    char *cp=&clubs[i]->d_name[1];
    if(!loadclubhdr(cp))continue;
    addqsc(clubhdr.club,clubhdr.msgno,LRF_QUICKSCAN|LRF_INQWK);
  }
  free(clubs);
}


static void
all(int add)
{
  struct dirent **clubs;
  int n,i;

  n=scandir(mkfname(CLUBHDRDIR),&clubs,hdrselect,ncsalphasort);
  for(i=0;i<n;free(clubs[i]),i++){
    struct lastread *p;
    char *cp=&clubs[i]->d_name[1];
    if(!loadclubhdr(cp))continue;

    p=findqsc(clubhdr.club);

    if(add==DEL){
      delqsc(clubhdr.club);
      /* addqsc(clubhdr.club,-1,p?p->flags&~LRF_INQWK:0); */
    }else if(p && (p->flags&LRF_INQWK)){
      addqsc(clubhdr.club,clubhdr.msgno,p->flags);
    }
    else {
      addqsc(clubhdr.club,0,p?p->flags|LRF_INQWK:LRF_INQWK);
    }
  }
  free(clubs);
}


static void
resetall(int n)
{
  struct dirent **clubs;
  int i,j;

  if(!readecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to read E-mail preference file for %s",
	  thisuseracc.userid);
  }

  if(n<0)emlu.lastemailqwk=max(n+sysvar->emessages,0);
  else emlu.lastemailqwk=min(sysvar->emessages,n);

  j=scandir(mkfname(CLUBHDRDIR),&clubs,hdrselect,ncsalphasort);
  for(i=0;i<j;free(clubs[i]),i++){
    char *cp=&clubs[i]->d_name[1];
    struct lastread *p;

    if(!loadclubhdr(cp))continue;

    p=findqsc(clubhdr.club);

    if(p && (p->flags&LRF_INQWK)){
      if(n>=0)p->qwklast=min(clubhdr.msgno,n);
      else p->qwklast=max(0,clubhdr.msgno+n);
    }
  }
  free(clubs);

  saveqsc();

  if(!writeecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to write E-mail preference file for %s",
	  thisuseracc.userid);
  }
}


int
getlastread(char *club)
{
  struct lastread *p=findqsc(club);
  int ret;

  if(!p)addqsc(club,0,0);
  p=findqsc(club);
  ret=p->qwklast;
  saveqsc();
  return ret;
}


void
setlastread(char *club, int msg)
{
  struct lastread *p=findqsc(club);

  if(!p)return;
  else p->qwklast=msg;
  saveqsc();
}


static void
listqsc()
{
  struct lastread *p;

  prompt(OMCLH);

  prompt(OMCL,omceml,"",emlu.lastemailqwk);

  p=resetqsc();
  while(p){
    if((p->flags&LRF_INQWK)&&(getclubax(&thisuseracc,p->club)>CAX_ZERO)){
      prompt(OMCL,p->club,
	     msg_getunit(OMCLYES,(p->flags&LRF_QUICKSCAN)!=0),
	     p->qwklast);
    }
    if(fmt_lastresult==PAUSE_QUIT)break;
    p=nextqsc();
  }
  if(fmt_lastresult!=PAUSE_QUIT)prompt(OMCLF);
  resetqsc();
}


static void
addclub()
{
  char club[16];
  struct lastread *p;

  if(!getclub(club,OMCADD,OMCCR,1,0))return;
  if(sameas(club,"ALL"))all(ADD);
  else {
    loadclubhdr(club);
    p=findqsc(club);
    if(!p)addqsc(club,0,LRF_INQWK);
    else if(p->flags&LRF_INQWK)addqsc(club,clubhdr.msgno,p->flags);
    else addqsc(club,0,p->flags|LRF_INQWK);
  }
}


static void
delclub()
{
  char club[16];
  struct lastread *p;

  for(;;){
    if(!getclub(club,OMCDEL,OMCDR,1,0))return;
    if(sameas(club,"ALL")){
      all(DEL);
      return;
    } else if(((p=findqsc(club))==NULL) || ((p->flags&LRF_INQWK)==0)){
      prompt(OMCDR);
      cnc_end();
      continue;
    } else {
      delqsc(club);
      /* addqsc(club,-1,p->flags&~LRF_INQWK); */
      break;
    }
  }
}


static void
resetclub()
{
  char club[16];
  struct lastread *p;
  int all=0, n, email=0;

  for(;;){
    if(!getclub(club,OMCRES,OMCRR,1,1))return;
    if(sameas(club,"ALL")){
      all=1;
      break;
    } else if(sameas(club,omceml)){
      email=1;
      break;
    } else if(((p=findqsc(club))==NULL) || ((p->flags&LRF_INQWK)==0)){
      prompt(OMCRR);
      cnc_end();
      continue;
    } else break;
  }

  if(!all&&!email&&!loadclubhdr(club)){
    error_fatal("Unable to load club %s.",club);
  }

  if(!get_number(&n,OMCRN,
		email?-sysvar->emessages:(all?-99999:-clubhdr.msgno),
		email?sysvar->emessages:(all?99999:clubhdr.msgno),
		OMCRNR,0,0)){
    return;
  }

  if(all)resetall(n);
  else if(email){
    if(!readecuser(thisuseracc.userid,&emlu)){
      error_fatal("Unable to read E-mail preference file for %s",
	    thisuseracc.userid);
    }

    if(n<0)n=max(n+sysvar->emessages,0);
    emlu.lastemailqwk=n;

    if(!writeecuser(thisuseracc.userid,&emlu)){
      error_fatal("Unable to write E-mail preference file for %s",
	    thisuseracc.userid);
    }
  } else {
    if(n<0)n=max(n+clubhdr.msgno,0);
    setlastread(club,n);
  }
}


void
fromqsc()
{
  struct lastread *p;
  int yes;

  if(!get_bool(&yes,OMCFC,OMCFCR,0,0)){
    prompt(OMCFCAN);
    return;
  }
  if(!yes){
    prompt(OMCFCAN);
    return;
  }

  if(!readecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to read E-mail preference file for %s",
	  thisuseracc.userid);
  }
  emlu.lastemailqwk=emlu.lastemailread;
  if(!writeecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to write E-mail preference file for %s",
	  thisuseracc.userid);
  }

  p=resetqsc();
  while(p){
    p->qwklast=p->lastmsg;
    if(p->flags&LRF_QUICKSCAN)p->flags|=LRF_INQWK;
    else p->flags&=~LRF_INQWK;
    p=nextqsc();
  }
  saveqsc();
  prompt(OMCFOK);
}


void
updateqsc()
{
  struct lastread *p;
  if(!updqsc)return;
  if(!readecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to read E-mail preference file for %s",
	  thisuseracc.userid);
  }
  emlu.lastemailread=emlu.lastemailqwk;
  if(!writeecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to write E-mail preference file for %s",
	  thisuseracc.userid);
  }
  
  p=resetqsc();
  while(p){
    /* if(p->flags&LRF_INQWK)p->lastmsg=p->qwklast; */
    p=nextqsc();
  }
}


void
toqsc()
{
  struct lastread *p;
  int yes;

  if(!get_bool(&yes,OMCTC,OMCTCR,0,0)){
    prompt(OMCTCAN);
    return;
  }
  if(!yes){
    prompt(OMCTCAN);
    return;
  }

  if(!readecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to read E-mail preference file for %s",
	  thisuseracc.userid);
  }
  emlu.lastemailread=emlu.lastemailqwk;
  if(!writeecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to write E-mail preference file for %s",
	  thisuseracc.userid);
  }
  
  p=resetqsc();
  while(p){
    p->lastmsg=p->qwklast;
    if(p->flags&LRF_INQWK)p->flags|=LRF_QUICKSCAN;
    else p->flags&=~LRF_QUICKSCAN;
    p=nextqsc();
  }
  saveqsc();
  prompt(OMCTOK);
}


void
configurequickscan(int create)
{
  char opt;
  int i, shown=0;

  startqsc();
  if(create==2){
    prompt(OMCHLP);
    cnc_end();
    initialise();
  } else if(create){
    prompt(OMCHLP2);
    cnc_end();
    all(ADD);
    all(ADD);
    emlu.lastemailqwk=sysvar->emessages;
  }

  for(;;){
    inp_setflags(INF_HELP);
    i=get_menu(&opt,!shown,OMCMNU,OMCMNUS,OMERR,"+-VRFT",0,0);
    shown=1;
    inp_clearflags(INF_HELP);
    if(!i){
      saveqsc();
      return;
    }
    if(i==-1){
      prompt(OMCHLP);
      shown=0;
      cnc_end();
      continue;
    }
  
    switch(opt){
    case '+':
      addclub();
      break;
    case '-':
      delclub();
      break;
    case 'R':
      resetclub();
      break;
    case 'V':
      listqsc();
      break;
    case 'F':
      fromqsc();
      break;
    case 'T':
      toqsc();
      break;
    }
  }
}


void
setqsc()
{
  char fname[256];
  struct stat st;
  int create=0;
  struct prefs prefs;

  if(!readecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to read E-mail preference file for %s",
	  thisuseracc.userid);
  }

  sprintf(fname,"%s/%s",mkfname(QSCDIR),thisuseracc.userid);
  readprefs(&prefs);
  if((prefs.flags&OMF_QSCOK)==0){
    create=1;
  }
  if(stat(fname,&st)!=0)create=2;
  configurequickscan(create);
  prefs.flags|=OMF_QSCOK;
  writeprefs(&prefs);
  if(!writeecuser(thisuseracc.userid,&emlu)){
    error_fatal("Unable to write E-mail preference file for %s",
	  thisuseracc.userid);
  }
}
