/*****************************************************************************\
 **                                                                         **
 **  FILE:     plugins.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 0.5                                    **
 **  PURPOSE:  Teleconferences, plugin support.                             **
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
 * Revision 1.1  2001/04/16 14:58:34  alexios
 * Initial revision
 *
 * Revision 0.8  1999/08/13 17:03:06  alexios
 * Various bug fixes and improvements of the interface between
 * the teleconference module and its plugins.
 *
 * Revision 0.7  1999/08/07 02:19:04  alexios
 * Optimised runmodule().
 *
 * Revision 0.6  1999/07/28 23:13:16  alexios
 * Added some debugging info. Loads of bug fixes and changes
 * to make this more viable in preparation for some actual
 * plugins.
 *
 * Revision 0.5  1999/07/18 21:48:36  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.4  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
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



#define __TELEPLUGIN__


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_TERMIO_H 1
#define WANT_WAIT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "telecon.h"
#include "plugins.h"


#define DEBUG 1

#ifdef DEBUG
#define debug(s...) print("PLUGIN DEBUG: "##s)
#else
#define debug(s...) ;
#endif


static int numplugins;
static struct plugin *plugins=NULL;


static int
plugincmp(const void *A, const void *B)
{
  const struct plugin *a=A, *b=B;
  return strcmp(a->keyword,b->keyword);
}


void
initplugins()
{
  FILE *fp;
  if((fp=fopen(TELEPLUGINFILE,"r"))==NULL){
    fatalsys("Unable to open %s",TELEPLUGINFILE);
  }
  if(!fread(&numplugins,sizeof(int),1,fp)){
    fatalsys("Unable to read %s",TELEPLUGINFILE);
  }

  if(plugins)free(plugins);
  plugins=alcmem(sizeof(struct plugin)*numplugins);

  if(fread(plugins,sizeof(struct plugin),numplugins,fp)!=numplugins){
    fatalsys("Unable to read plugins from %s",TELEPLUGINFILE);
  }
  fclose(fp);
}


void
listplugins()
{
  int shownheader=0, i;
  for(i=0;i<numplugins;i++){
    if(!haskey(&thisuseracc,plugins[i].key))continue;
    if(!shownheader){
      shownheader=1;
      prompt(PINTABL1);
    }
    prompt(PINTABL2,plugins[i].keyword,
	   plugins[i].descr[thisuseracc.language-1]);
  }
  if(!shownheader){
    prompt(PINNONE);
    return;
  } else prompt(PINTABL3);
}


int
qexists()
{
  struct msqid_ds buf;
  debug("thisuseraux.pluginq=%d\n",thisuseraux.pluginq);
  return msgctl(thisuseraux.pluginq,IPC_STAT,&buf)==0;
}


int
getid(char *plugin, char *channel, int *pid)
{
  char qname[256];
  FILE *fp;
  int id;

  *pid=-1;
  strcpy(thisuseraux.plugin,plugin);
  sprintf(qname,PLUGINQ,plugin,curchannel);
  if((fp=fopen(qname,"r"))==NULL)return -1;
  if(!fscanf(fp,"%d %d",&id,pid)){
    fclose(fp);
    return -1;
  } else fclose(fp);
  thisuseraux.pluginq=id;
  if(!qexists())return -1;
  return thisuseraux.pluginq;
}


void
makequeue(char *keyword, char *channel)
{
  int id=msgget(IPC_PRIVATE,IPC_CREAT|IPC_EXCL|0664);
  FILE *fp;
  char qname[256];
  
  if(id<0){
    fatal("Unable to create IPC message queue (errno=%d).",
	  errno);
  }

  thisuseraux.pluginq=id;

  sprintf(qname,PLUGINQ,keyword,channel);
  if((fp=fopen(qname,"w"))==NULL){
    fatalsys("Unable to create %s",qname);
  }
  fprintf(fp,"%d -1\n",id);
  fclose(fp);
  chmod(qname,0666);
}


void
runplugin(struct plugin *p, char *s)
{
  char tmp[256];
  int pid,status;

  debug("running.\n");

  switch(pid=fork()){
  case 0:
    doneinput();
    donesignals();
    if(s!=NULL && strlen(s)){
      strcpy(thisuseronl.input,s);
      thisuseronl.flags|=OLF_MMCONCAT;
    } else thisuseronl.flags&=~OLF_MMCONCAT;

    sprintf(tmp,"%d",thisuseraux.pluginq);
    execlp(p->exec,p->exec,p->keyword,curchannel,thisuseracc.userid,tmp,NULL);
    fatalsys("Unable to execlp() teleplugin!");
  case -1:
    fatalsys("Unable to fork and run teleplugin!");
  default:
    waitpid(pid,&status,0);
    regpid(thisuseronl.channel);
    thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
    resetinactivity();
    if(thisuseronl.flags&OLF_MMGCDGO)exit(0);
  }

#if 0
  sprintf(command,"%s %s %s %s %d",
	  p->exec,
	  p->keyword,
	  curchannel,
	  thisuseracc.userid,
	  thisuseraux.pluginq);
  runmodule(command);
#endif
}


int
pluginrunning(int pid)
{
  if(pid<0)return 0;
  else {
    char fname[256];
    struct stat st;
    sprintf(fname,"%s/%d",PROCDIR,pid);
    return stat(fname,&st)==0;
  }
  return 0;
}


void
plugin(struct plugin *p, char *command)
{
  int pid=-1, res=0;
  char lock[256];
  struct pluginmsg msg;

  msg.mtype=MTYPE_COMMAND;
  strcpy(msg.userid,thisuseracc.userid);
  strcpy(msg.text,command);

  pid=-1;

  if(qexists()){
    debug("sending %d bytes.\n",SIZE(command));
    res=msgsnd(thisuseraux.pluginq,(struct msgbuf *)&msg,SIZE(command),0);
  } else {
    debug("couldn't send\n");

    sprintf(lock,LCKPIN,p->keyword,curchannel);
    waitlock(lock,60);

    if(getid(p->keyword,curchannel,&pid)==-1){
      debug("making\n");
      placelock(lock,"making");
      makequeue(p->keyword,curchannel);
      rmlock(lock);
    }
  }

  debug("is plugin running?\n");
  if(!pluginrunning(pid)){
    debug("running plugin with command (%s)\n",command);
    placelock(lock,"running");
    runplugin(p,command);
    rmlock(lock);
  } else {
    msgsnd(thisuseraux.pluginq,(struct msgbuf *)&msg,SIZE(command),0);
  }
}


int
handleplugins(char *s)
{
  struct plugin *p,key;
  char tmp[2048];
  int n=strlen(s)+1,i;

  if(*s=='/')return 0;

  if(!sscanf(s,"%s %n",tmp,&n))return 0;
  if(strlen(tmp)>15)return 0;

  for(i=0;tmp[i];i++)tmp[i]=toupper(tmp[i]);

  strcpy(key.keyword,tmp);
  
  if((p=bsearch(&key,plugins,numplugins,sizeof(struct plugin),plugincmp))==NULL)
    return 0;

  if(!haskey(&thisuseracc,p->key)){
    prompt(PINNAX,p->keyword);
    return 1;
  }

  if(!qexists()){
    thisuseraux.plugin[0]=0;
    thisuseraux.pluginq=-1;
  }

  if((thisuseraux.plugin[0])&&(!sameas(thisuseraux.plugin,p->keyword))){
    prompt(PINALR,thisuseraux.plugin,thisuseraux.plugin);
    return 1;
  }

  plugin(p,&s[n]);

  return 1;
}


/* Stuff required by plugins */

/*****************************************************************************/


char *keyword, *channel, *userid;
int  qid;


void
writepid()
{
  char fname[256];
  FILE *fp;

  sprintf(fname,PLUGINQ,keyword,channel);
  if((fp=fopen(fname,"w"))==NULL){
    fatalsys("Plugin %s: Unable to create %s",keyword,fname);
  }

  fprintf(fp,"%d %d\n",qid,getpid());
  fclose(fp);
  chmod(fname,0666);
}


void
initplugin(int argc, char **argv)
{
  struct stat st;
  char fname[256];

  atexit(doneplugin);

  noerrormessages();

  init();

  if(argc!=5){
    fatal("Plugin %s called with bad arguments.",argv[0]);
  }
  keyword=argv[1];
  channel=argv[2];
  userid=argv[3];
  qid=atoi(argv[4]);

  /* Sanity checks */

  sprintf(fname,"%s/%s",TELEDIR,channel);
  if(stat(fname,&st)){
    fatalsys("Plugin %s: channel %s doesn't exist.",
	  keyword,channel);
  }

  if(!uinsys(userid,0)){
    fatal("Plugin %s: user %s not on-line.",keyword,userid);
  }

  writepid();
}


void
becomeserver()
{
  /*donemodule();*/

  if(fork())exit(0);

  atexit(doneserver);

  writepid();

  ioctl(0,TIOCNOTTY,NULL);

  close(0);
  close(1);
  close(2);
}


void
doneplugin()
{
}


void
doneserver()
{
  struct msqid_ds buf;
  int i=msgctl(qid,IPC_RMID,&buf);
  static int circular=0;
  char fname[256];

  fprintf(stderr,"doneserver...\n");

  if(i&&!circular){
    circular=1;
    fatalsys("Plugin %s: couldn't destroy msg queue id=%d.",keyword,qid);
  }
  sprintf(fname,PLUGINQ,keyword,channel);
  unlink(fname);
}
