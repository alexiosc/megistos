/*****************************************************************************\
 **                                                                         **
 **  FILE:     operations.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1995, Version 0.5                                    **
 **  PURPOSE:  System operations for the Clubs module                       **
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
 * Revision 1.2  2001/04/16 21:56:31  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.8  1999/07/18 21:21:38  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.7  1998/12/27 15:33:03  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Migrated to the new locking functions.
 *
 * Revision 0.6  1998/08/14 11:29:14  alexios
 * Minor white-space re-ordering changes. :-)
 *
 * Revision 0.5  1998/08/11 10:03:22  alexios
 * Club listings are now case insensitive. Added code to set
 * default accesses for new clubs.
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:04:17  alexios
 * The default operator of new clubs is now the club's creator,
 * not the Sysop.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
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
#include "mbk_emailclubs.h"
#include "email.h"
#include "clubs.h"



int
qscselect(const struct dirent *d)
{
  return d->d_name[0]!='.';
}


void
globalqsc(int add, char *club)
{
  struct dirent **qscs;
  int n,i;
  char clubtmp[32];

  strcpy(clubtmp,club);

  n=scandir(QSCDIR,&qscs,qscselect,ncsalphasort);
  if(n)doneqsc();
  for(i=0;i<n;i++){
    ustartqsc(qscs[i]->d_name);
    if(add){
      struct lastread *p=findqsc(clubtmp);
      if(!p){
	addqsc(clubtmp,0,LRF_QUICKSCAN+LRF_INQWK);
	usaveqsc(qscs[i]->d_name);
      }
    } else if(killqsc(clubtmp))usaveqsc(qscs[i]->d_name);
    doneqsc();
    free(qscs[i]);
  }
  free(qscs);
  if(n)startqsc();
}


void
listclubs()
{
  struct dirent **clubs;
  int n,i;

  n=scandir(CLUBHDRDIR,&clubs,hdrselect,ncsalphasort);
  prompt(LCHDR);
  for(i=0;i<n;free(clubs[i]),i++){
    char *cp=&clubs[i]->d_name[1];
    if(!loadclubhdr(cp))continue;
    if(fmt_lastresult==PAUSE_QUIT)break;
    if(getclubax(&thisuseracc,cp)==CAX_ZERO)continue;
    prompt(LCTAB,clubhdr.club,clubhdr.clubop,clubhdr.descr);
  }
  free(clubs);
  enterdefaultclub();
  if(fmt_lastresult==PAUSE_QUIT)return;
  prompt(LCFTR);
}


void
longlistclubs()
{
  struct dirent **clubs;
  int n,i;
  char date[256];

  prompt(LC2HDR);
  n=scandir(CLUBHDRDIR,&clubs,hdrselect,ncsalphasort);
  for(i=0;i<n;free(clubs[i]),i++){
    char *cp=&clubs[i]->d_name[1];
    if(!loadclubhdr(cp))continue;
    if(fmt_lastresult==PAUSE_QUIT)break;
    if(getclubax(&thisuseracc,cp)==CAX_ZERO)continue;
    strcpy(date,strdate(clubhdr.crdate));
    /*memcpy(&date[7],&date[9],3);*/
    prompt(LC2TAB,clubhdr.club,clubhdr.nmsgs,clubhdr.nfiles,
	   clubhdr.nblts,date,clubhdr.clubop,clubhdr.descr);
  }
  free(clubs);
  enterdefaultclub();
  if(fmt_lastresult==PAUSE_QUIT)return;
  prompt(LC2FTR);
}


int
modifybanner()
{
  char fname[256], temp[256];
  struct stat st;

  sprintf(fname,"%s/b%s",CLUBHDRDIR,clubhdr.club);
  sprintf(temp,TMPDIR"/mb%05d",getpid());
  symlink(fname,temp);

  if(editor(temp,msglen)||stat(temp,&st)){
    unlink(temp);
    return 0;
  }
  unlink(temp);
  return 1;
}


void
newclub()
{
  char *i, *cp;
  char c;
  struct clubheader new;
  int ok;
  char lock[256], fname[256];

  for(;;){
    fmt_lastresult=0;
    if((c=cnc_more())!=0){
      if(sameas(cnc_nxtcmd,"X"))return;
      if(sameas(cnc_nxtcmd,"?")){
	listclubs();
	cnc_end();
	continue;
      }
      i=cnc_word();
    } else {
      prompt(CRCASK);
      inp_get(15);
      cnc_begin();
      i=cnc_word();
      if(!margc){
	cnc_end();
	continue;
      } else if(inp_isX(margv[0]))return;
      if(sameas(margv[0],"?")){
	listclubs();
	cnc_end();
	continue;
      }
    }

    if(*i=='/')i++;

    if(strlen(i)>15){
      prompt(CRERR);
      cnc_end();
      continue;
    }
    for(ok=1,cp=i;*cp;cp++)if(!strchr(FNAMECHARS,*cp)){
      prompt(CRERR);
      cnc_end();
      ok=0;
      break;
    }
    if(!ok)continue;

    if(findclub(i)){
      prompt(CRCXST);
      cnc_end();
      continue;
    } else break;
  }

  memset(&new,0,sizeof(new));
  strcpy(new.club,i);
  new.clubid=getclubid();
  strcpy(new.clubop,thisuseracc.userid);
  new.crdate=today();
  new.crtime=now();
  new.keyreadax=drdaxkey;
  new.keydnlax=ddlaxkey;
  new.keywriteax=dwraxkey;
  new.keyuplax=dulaxkey;
  new.msglife=clblif;
  new.postchg=clbwchg;
  new.uploadchg=clbuchg;
  new.dnloadchg=clbdchg;
  new.credspermin=-1;

  sprintf(lock,CLUBLOCK,new.club);
  if(lock_wait(lock,10)==LKR_TIMEOUT)return;
  lock_place(lock,"creating");
  saveclubhdr(&new);
  lock_rm(lock);
  prompt(CRCCNF,new.club);

  sprintf(fname,"%s/%s",MSGSDIR,new.club);
  mkdir(fname,0770);

  strcpy(thisuseracc.lastclub,new.club);
  enterdefaultclub();

  sprintf(fname,"%s/%s/%s",MSGSDIR,new.club,MSGATTDIR);
  mkdir(fname,0770);

  sprintf(fname,"%s/%s/%s",MSGSDIR,new.club,MSGBLTDIR);
  mkdir(fname,0770);


  /* Add the club to all quickscan configurations */

  if(addnew)globalqsc(QSC_ADD,new.club);
}



void
delclub()
{
  char *i;
  char c;
  int yes;
  char lock[256], command[256];
  DIR *dp;
  struct dirent *dir;
  

  for(;;){
    fmt_lastresult=0;
    if((c=cnc_more())!=0){
      if(sameas(cnc_nxtcmd,"X"))return;
      if(sameas(cnc_nxtcmd,"?")){
	listclubs();
	cnc_end();
	continue;
      }
      i=cnc_word();
    } else {
      prompt(DCASK);
      inp_get(15);
      cnc_begin();
      i=cnc_word();
      if(!margc){
	cnc_end();
	continue;
      } else if(inp_isX(margv[0]))return;
      if(sameas(margv[0],"?")){
	listclubs();
	cnc_end();
	continue;
      }
    }

    if(*i=='/')i++;

    if(!findclub(i)){
      prompt(DCUNK);
      cnc_end();
      continue;
    } else break;
  }

  loadclubhdr(i);

  if(!strcmp(i,defclub)){
    prompt(DCERR2);
    return;
  }

  if(!checkinclub(i)){
    prompt(DCERR1);
    return;
  }
  
  loadclubhdr(clubhdr.club);

  prompt(DCINFO);

  if(!get_bool(&yes,DCCONF,DCCR,0,0))return;
  if(!yes)return;
  if(!checkinclub(i)){
    prompt(DCSNUK);
    return;
  }

  prompt(DCWAIT);


  /* Remove the club from all quickscan configurations */

  globalqsc(QSC_DEL,clubhdr.club);


  /* Lock club and start deleting directories */

  loadclubhdr(i);
  sprintf(lock,CLUBLOCK,clubhdr.club);
  lock_wait(lock,60);
  lock_place(lock,"deleting");
  sprintf(command,"\\rm -rf %s/?%s %s/%s >&/dev/null &",
	  CLUBHDRDIR,clubhdr.club,
	  MSGSDIR,clubhdr.club);
  system(command);


  /* Delete all special user accesses to the club */
  

  if((dp=opendir(CLUBAXDIR))!=NULL){
    while((dir=readdir(dp))!=NULL){
      useracc_t usracc, *uacc=&usracc;
      
      if(dir->d_name[0]=='.')continue;
      
      if(!usr_insys(dir->d_name,0))usr_loadaccount(dir->d_name,uacc);
      else uacc=&othruseracc;

      setclubax(uacc,clubhdr.club,CAX_DEFAULT);
    }
  }
  closedir(dp);


  /* Unlock and exit */

  lock_rm(lock);
  prompt(DCOK);
}





void
editclub()
{
  char fname[256];
  char descr[256];
  int lifetime=0;

  sprintf(inp_buffer,"%s\n%d\nEdit\nOK\nCancel\n",
	  clubhdr.descr,
	  clubhdr.msglife);

  if(dialog_run("emailclubs",ECVT,ECLT,inp_buffer,MAXINPLEN)!=0){
    error_log("Unable to run data entry subsystem");
  }

  dialog_parse(inp_buffer);

  if (sameas(margv[5],"OK") || sameas (margv[2],margv[5])
      || sameas(margv[3],margv[5])) {


    /* Edit the banner? */

    if(sameas(margv[2],margv[5])){
      if(!modifybanner()){
	prompt(ECCAN);
	return;
      }
    }

    bzero(descr,sizeof(descr));
    strncpy(descr,margv[0],sizeof(descr));
    lifetime=atoi(margv[1]);

    sprintf(fname,CLUBLOCK,clubhdr.club);
    if(lock_wait(fname,10)==LKR_TIMEOUT)return;
    lock_place(fname,"writing");
    loadclubhdr(clubhdr.club);
    strncpy(clubhdr.descr,descr,sizeof(clubhdr.descr)-1);
    clubhdr.descr[sizeof(clubhdr.descr)-1]='\0';
    clubhdr.msglife=lifetime;
    saveclubhdr(&clubhdr);
    lock_rm(fname);
    prompt(ECDONE);
  } else {
    prompt(ECCAN);
  }
}


void
accesslevels()
{
  sprintf(inp_buffer,"%d\n%d\n%d\n%d\nOK\nCANCEL\n",
	  clubhdr.keyreadax,
	  clubhdr.keydnlax,
	  clubhdr.keywriteax,
	  clubhdr.keyuplax);

  if(dialog_run("emailclubs",AXLVT,AXLLT,inp_buffer,MAXINPLEN)!=0){
    error_log("Unable to run data entry subsystem");
  }

  dialog_parse(inp_buffer);

  if(sameas(margv[6],"OK")||sameas(margv[6],margv[4])){
    int  r=atoi(margv[0]);
    int  d=atoi(margv[1]);
    int  w=atoi(margv[2]);
    int  u=atoi(margv[3]);
    char fname[256];

    sprintf(fname,CLUBLOCK,clubhdr.club);
    if(lock_wait(fname,10)==LKR_TIMEOUT)return;
    lock_place(fname,"writing");
    loadclubhdr(clubhdr.club);
    clubhdr.keyreadax=sameas(clubhdr.club,defclub)?0:r;
    if(sameas(clubhdr.club,defclub))prompt(WRNDEFC);
    clubhdr.keydnlax=d;
    clubhdr.keywriteax=w;
    clubhdr.keyuplax=u;
    saveclubhdr(&clubhdr);
    lock_rm(fname);
    prompt(ECDONE);
  } else {
    prompt(ECCAN);
  }
}


void
charges()
{
  sprintf(inp_buffer,"%d\n%d\n%d\n%d\nOK\nCANCEL\n",
	  clubhdr.postchg,
	  clubhdr.uploadchg,
	  clubhdr.dnloadchg,
	  clubhdr.credspermin);

  if(dialog_run("emailclubs",CHVT,CHLT,inp_buffer,MAXINPLEN)!=0){
    error_log("Unable to run data entry subsystem");
    return;
  }

  dialog_parse(inp_buffer);

  if(sameas(margv[6],"OK")||sameas(margv[6],margv[4])){
    char fname[256];

    sprintf(fname,CLUBLOCK,clubhdr.club);
    if(lock_wait(fname,10)==LKR_TIMEOUT)return;
    lock_place(fname,"writing");
    loadclubhdr(clubhdr.club);
    clubhdr.postchg=atoi(margv[0]);
    clubhdr.uploadchg=atoi(margv[1]);
    clubhdr.dnloadchg=atoi(margv[2]);
    clubhdr.credspermin=atoi(margv[3]);
    saveclubhdr(&clubhdr);
    lock_rm(fname);
    prompt(ECDONE);
  } else {
    prompt(ECCAN);
  }
}


void
configureuser()
{
  char uid[256], opt, fname[256];
  int res, cur, i;
  useracc_t usracc, *uacc=&usracc;
  
  int axp[]={
    CAX_ZERO,CAX_READ,CAX_DNLOAD,CAX_WRITE,
    CAX_UPLOAD,CAX_COOP,CAX_CLUBOP,CAX_SYSOP,-1};

  int axo[]={
    'D', CAX_DEFAULT,
    '0', CAX_ZERO,
    '1', CAX_READ,
    '2', CAX_DNLOAD,
    '3', CAX_WRITE,
    '4', CAX_UPLOAD,
    '5', CAX_COOP,
    '6', CAX_CLUBOP,
    0};

  for(;;){
    if(!get_userid(uid,CUASK,CUERR1,0,0,0))return;
    break; /* Don't check for Sysop here */
    if(sameas(SYSOP,uid)){
      prompt(CUERR2);
      cnc_end();
      continue;
    } else break;
  }

  if(!usr_insys(uid,0))usr_loadaccount(uid,uacc);
  else uacc=&othruseracc;

  cur=getclubax(uacc,clubhdr.club);

  for(i=0;axp[i]>=0;i++)if(axp[i]==cur){
    prompt(CUCUR,uid,msg_getunit(CULVL0+i,1));
    break;
  }

  if(cur==CAX_SYSOP)prompt(CUSYSW);

  for(;;){
    inp_setflags(INF_HELP);
    res=get_menu(&opt,1,CUMNU,CUSMNU,CUMNUR,"D0123456",0,0);
    inp_clearflags(INF_HELP);
    if(!res)return;
    else if(res==-1){
      prompt(CUHLP);
      cnc_end();
      continue;
    } else if(opt=='6' && getclubax(&thisuseracc,clubhdr.club)<CAX_SYSOP){
      prompt(CUMNUR1);
      cnc_end();
      continue;
    } else if(opt=='5' && getclubax(&thisuseracc,clubhdr.club)<CAX_CLUBOP){
      prompt(CUMNUR2);
      cnc_end();
      continue;
    } else if(opt=='0' && sameas(clubhdr.club,defclub)){
      prompt(CUMNUR3);
      cnc_end();
      continue;
    } else if(opt!='6' && sameas(SYSOP,uid)){
      prompt(CUERR2);
      cnc_end();
      continue;
    } else break;
  }

  cur=CAX_DEFAULT;
  for(i=0;axo[i];i+=2){
    if(opt==axo[i]){
      cur=axo[i+1];
      break;
    }
  }

  if(cur==CAX_CLUBOP && (!sameas(clubhdr.clubop,uid))){
    uacc=&usracc;
    if(!usr_insys(clubhdr.clubop,0))usr_loadaccount(clubhdr.clubop,uacc);
    else uacc=&othruseracc;
    setclubax(uacc,clubhdr.club,CAX_DEFAULT);
    prompt(CUDIS,uacc->userid);
  }

  uacc=&usracc;
  if(!usr_insys(uid,0))usr_loadaccount(uid,uacc);
  else uacc=&othruseracc;

  setclubax(uacc,clubhdr.club,cur);

  if(cur==CAX_CLUBOP || (cur!=CAX_CLUBOP&&sameas(clubhdr.clubop,uid))){
    sprintf(fname,CLUBLOCK,clubhdr.club);
    if(lock_wait(fname,10)==LKR_TIMEOUT)return;
    lock_place(fname,"writing");
    loadclubhdr(clubhdr.club);
    if(cur==CAX_CLUBOP)strcpy(clubhdr.clubop,uid);
    else if(cur!=CAX_CLUBOP&&sameas(clubhdr.clubop,uid))strcpy(clubhdr.clubop,SYSOP);
    saveclubhdr(&clubhdr);
    lock_rm(fname);
  }

  if(cur>=CAX_COOP){
    if(usr_insys(uid,1)){
      sprintf(out_buffer,msg_getl(CUCNOT,othruseracc.language-1),clubhdr.club);
      usr_injoth(&othruseronl,out_buffer,0);
    }
  }

  prompt(CUCHG,uid);
}


void
operations()
{
  char opt;
  int show=1;
  int access;

  for(;;){
    enterdefaultclub();
    access=getclubax(&thisuseracc,clubhdr.club);
    if(!get_menu(&opt,show,OPMNU,SHOPMNU,ERRSEL,"HNDEAMC",0,0))return;

    show=0;
    switch(opt){
    case 'H':
      prompt(OPHELP);
      continue;
    case 'N':
      if(access==CAX_SYSOP)newclub();
      else prompt(NOAXES,opt);
      continue;
    case 'D':
      if(access>=CAX_SYSOP)delclub();
      else prompt(NOAXES,opt);
      continue;
    case 'A':
      if(access==CAX_SYSOP || key_owns(&thisuseracc,modaxkey))accesslevels();
      else prompt(NOAXES,opt);
      continue;
    case 'M':
      if(access==CAX_SYSOP || key_owns(&thisuseracc,modchkey))charges();
      else prompt(NOAXES,opt);
      continue;
    case 'E':
      if(access==CAX_SYSOP || key_owns(&thisuseracc,modhdkey))editclub();
      else prompt(NOAXES,opt);
      continue;
    case 'C':
      if(access>=CAX_COOP)configureuser();
      else prompt(NOAXES,opt);
      continue;
    }
  }
}
