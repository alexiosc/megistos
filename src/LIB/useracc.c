/*****************************************************************************\
 **                                                                         **
 **  FILE:     useracc.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Handle user and class information                            **
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
 * Revision 0.5  1999/08/13 16:56:08  alexios
 * Fixed error reporting when injoth() fails.
 *
 * Revision 0.4  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added code to recognise user files
 * by magic number. Other minor fixes. Moved various functions
 * from miscfx.c to useracc.c, where they belong.
 *
 * Revision 0.3  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.2  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_MSG_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"


struct shmuserrec *thisshm=NULL, *othrshm=NULL;
classrec                   *userclasses=NULL;
int                        numuserclasses=0;


int
userexists(char *uid)
{
  DIR *dp;
  struct dirent *de;
  char fname[256];
  struct stat s;

  sprintf(fname,"%s/%s",USRDIR,uid);
  if(!stat(fname,&s))return 1;

  if((dp=opendir(USRDIR))==NULL) return 0;
  while((de=readdir(dp))!=NULL){
    if(sameas(de->d_name,uid)){
      closedir(dp);
      strcpy(uid,de->d_name);
      return 1;
    }
  }
  closedir(dp);
  return 0;
}


classrec *
findclass (char *s)
{
  int i;
  for(i=0;i<numuserclasses;i++)if(sameas(userclasses[i].name,s)){
    return (classrec *)&userclasses[i];
  }
  /*fatal("Can't find class %s!",s,NULL); */
  return NULL;
}


int
loaduseraccount (char *whose, useracc *uacc)
{
  char fname[256];
  int result;
  FILE *fp;

  sprintf(fname,"%s/%s",USRDIR,whose);
  if((fp=fopen(fname,"r"))==NULL) return 0;
  result=fread(uacc,sizeof(useracc),1,fp);
  fclose(fp);
  if(result!=1) return 0;

  if(strncmp(uacc->magic,USR_MAGIC,sizeof(uacc->magic))){
    fatal("User account for %s is corrupted (invalid magic number)");
  }
  return 1;
}


int
loaduseronlrec (char *whose, onlinerec *onlrec)
{
  char       fname[256];
  int        result;
  FILE       *fp;

  sprintf(fname,"%s/%s",ONLINEDIR,whose);
  if((fp=fopen(fname,"r"))==NULL) return 0;
  result=fread(onlrec,sizeof(onlinerec),1,fp);
  fclose(fp);
  if(result!=1) return 0;
  return 1;
}


int
saveuseraccount (useracc *uacc)
{
  char       fname[256],fname2[256];
  int        result;
  FILE       *fp;
  
  sprintf(fname,"%s/%s",USRDIR,uacc->userid);
  sprintf(fname2,"%s/.%05d.%s",USRDIR,(int)getpid(),uacc->userid);
  if((fp=fopen(fname2,"w"))==NULL) return 0;
  result=fwrite(uacc,sizeof(useracc),1,fp);
  fclose(fp);
  if(result!=1) return 0;
  rename(fname2,fname);
  return 1;
}


int
saveuseronlrec (onlinerec *usronl)
{
  char        fname[256],fname2[256];
  int         result;
  FILE        *fp;
  struct stat st;

  sprintf(fname,"%s/%s",ONLINEDIR,usronl->userid);
  if(!stat(fname,&st))return 1;
  sprintf(fname2,"%s/.%05d.%s",ONLINEDIR,(int)getpid(),usronl->userid);
  if((fp=fopen(fname2,"w"))==NULL) return 0;
  result=fwrite(usronl,sizeof(onlinerec),1,fp);
  fclose(fp);
  if(result!=1) return 0;
  rename(fname2,fname);
  return 1;
}


void
postcredits (char *userid, int amount, int paid)
{
  useracc user, *uacc=&user;
  
  if(!uinsys(userid,0))loaduseraccount(userid,uacc);
  else uacc=&othruseracc;
  if(!uacc) return;

  uacc->credits+=amount;
  uacc->totcreds+=amount;
  if(paid)uacc->totpaid+=amount;
  if(sysvar){
    sysvar->tcreds+=amount;
    if(paid)sysvar->tcredspaid+=amount;
  }
  
  if(!uinsys(userid,0))saveuseraccount(uacc);
}


void
chargecredits (int amount)
{
  classrec *ourclass=findclass(thisuseracc.curclss);

  if(ourclass)if(ourclass->flags&CF_NOCHRGE)return;
  thisuseracc.credits-=amount;
  thisuseracc.totcreds-=amount;
  thisuseronl.statcreds+=amount;
}


void
changeclass (char *userid, char *newclass, int permanent)
{
  useracc *uacc=NULL;

  if(!uinsys(userid,0))loaduseraccount(userid,uacc);
  else uacc=&othruseracc;
  if(!uacc) return;

  if(!permanent){
    strcpy(uacc->tempclss,uacc->curclss);
    strcpy(uacc->curclss,newclass);
  } else {
    strcpy(uacc->tempclss,newclass);
    strcpy(uacc->curclss,newclass);
    uacc->classdays=0;
  }
  
  if(!uinsys(userid,0))saveuseraccount(uacc);
}


int
canpay(int amount)
{
  classrec *ourclass=findclass(thisuseracc.curclss);

  if(ourclass)if(ourclass->flags&CF_NOCHRGE)return 1;
  return(thisuseracc.credits>=amount);
}


int
uinsystem(char *userid, int checkinvis, struct shmuserrec **buf)
{
  char fname [256];
  FILE *fp;
  int shmid;

  sprintf(fname,"%s/.shmid-%s",ONLINEDIR,userid);
  if((fp=fopen(fname,"r"))==NULL)return 0;
/*  if(buf && !strcmp((*buf)->onl.userid,userid)){
    fclose(fp);
    return 1;
  } */
  if(!fscanf(fp,"%d",&shmid)){
    fatal("Unable to read file %s",fname);
  }
  fclose(fp);

  if(*buf){
    shmdt((char *)*buf);
    *buf=NULL;
  }
  if((*buf=(struct shmuserrec *)shmat(shmid,NULL,0))==NULL) return 0;

  if(checkinvis)return(((*buf)->onl.flags&OLF_INVISIBLE)==0);
  else return 1;
}


int
uinsys(char *userid, int checkinvis)
{
  if(!userexists(userid))return 0;
  return uinsystem(userid,checkinvis,&othrshm);
}


int
injoth(onlinerec *user,char *msg,int force)
{
  char dummy[MSGMAX+sizeof(long)];
  struct msgbuf *buf=(struct msgbuf*)(&dummy);

  if(!force)if(user->flags&OLF_BUSY)return 0;
  
  if(user->injothqueue<0)return 0;

  bzero(&dummy,sizeof(dummy));
  buf->mtype=1;
  strncpy(buf->mtext,msg,MSGMAX-1);
  buf->mtext[MSGMAX-1]=0;

  if(strlen(msg)+1>MSGMAX){
    interror("Message len (%d) exceeded size of injoth buf (%d).",
	     strlen(msg), MSGMAX);
  }

  if(msgsnd(user->injothqueue,buf,strlen(msg)+1,IPC_NOWAIT)<0){
    interrorsys("Failed to injoth() to %s",user->userid,i,strerror(i));
    return 0;
  }
  
  return 1;
}


#define CACHESIZE 32

static char xrefcache[CACHESIZE][24];

static int cachesize=0;


static void
cachepush(char *s)
{
  memcpy(&xrefcache[1],&xrefcache[0],(CACHESIZE-1)*24);
  strcpy(xrefcache[0],s);
  if(cachesize<CACHESIZE)cachesize++;
}


static int
cachechk(char *s)
{
  int i;
  for(i=0;i<cachesize;i++){
    if(sameas(s,xrefcache[i])){
      strcpy(s,xrefcache[i]);
      return 1;
    }
  }
  return 0;
}


int
uidxref(char *userid, int online)
{
  char matches[1000][80];
  int  num=0;
  int  retry=0;
  int  cache;

 tryagain:
  if(strlen(userid)<3 && (!online))return 0;
  if(!strlen(userid) && online)return 0;
  cache=cachechk(userid);
  if(online)if(uinsys(userid,!hassysaxs(&thisuseracc,USY_MASTERKEY))){
    if(!cache)cachepush(userid);
    return 1;
  }
  if(!online)if(userexists(userid)){
    if(!cache)cachepush(userid);
    return 1;
  }
  
  num=0;
  memset(matches,0,sizeof(matches));
  if(online){
    int i;
    struct linestatus status;

    for(i=0;i<numchannels;i++){
      if(getlinestatus(channels[i].ttyname,&status)<0)continue;
      
      if(status.result==LSR_USER){
	if(uinsys(status.user,!hassysaxs(&thisuseracc,USY_MASTERKEY))){
	  if(sameto(userid,status.user)&&(num<1000)){
	    strcpy(matches[num],status.user);
	    num++;
	  }
	}
      }
    }
  } else {
    FILE *fp;
    char command[256],uid[256];
    
    sprintf(command,"\\ls %s",USRDIR);
    if((fp=popen(command,"r"))==NULL){
      pclose(fp);
      return 0;
    }
    while(!feof(fp)){
      uid[0]=0;
      if(!fscanf(fp,"%s",uid))continue;
      if(sameto(userid,uid)&&num<1000){
	strcpy(matches[num],uid);
	num++;
      }
    }
    pclose(fp);
  }
    
  if(num==1){
    cachepush(strcpy(userid,matches[0]));
    return 1;
  } else if(!num && !retry)return 0;
  else {
    int i,ans=0;
    
    setmbk(sysblk);
    for(;;){
      endcnc();
      if(num){
	prompt(UXRF1,userid);
	for(i=0;i<num;i++)prompt(UXRF2,i+1,matches[i]);
	prompt(UXRF3,1,num);
      } else prompt(UXRF3A);
      getinput(0);
      if(!margc){
	continue;
      } else if(margc && isX(margv[0])){
	rstmbk();
	return 0;
      } else if(margc && sameas(margv[0],"?")){
	continue;
      } else if(num && margc && (ans=atoi(margv[0]))){
	if(ans>num){
	  prompt(UXRF4);
	  continue;
	} else {
	  cachepush(strcpy(userid,matches[ans-1]));
	  rstmbk();
	  return 1;
	}
      } else if(margc){
	rstmbk();
	strcpy(userid,margv[0]);
	retry=1;
	goto tryagain;
      }
    }
  }
  return 0;
}


