/*****************************************************************************\
 **                                                                         **
 **  FILE:     misc.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997                                               **
 **  PURPOSE:  Miscellaneous functions                                      **
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
 * Revision 1.1  2001/04/16 15:00:36  alexios
 * Initial revision
 *
 * Revision 0.11  1999/08/07 02:20:09  alexios
 * Very slight paranoia changes.
 * ,
 *
 * Revision 0.10  1999/07/18 22:00:00  alexios
 * Changed a few fatal() calls to fatalsys(). Added functions
 * to perform better auditing of users.
 *
 * Revision 0.9  1998/12/27 16:21:05  alexios
 * Added autoconf support. Added support for new getlinestatus().
 * Other minor fixes.
 *
 * Revision 0.8  1998/08/14 11:58:52  alexios
 * Added auditing for users who are relogging on.
 *
 * Revision 0.7  1998/07/26 21:11:32  alexios
 * No changes.
 *
 * Revision 0.6  1998/07/24 10:25:55  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.5  1997/11/06 20:04:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 11:06:30  alexios
 * Changed calls to audit() so they use the new auditing scheme.
 *
 * Revision 0.3  1997/09/14 13:52:46  alexios
 * Fixed problem with bbs not setuid/setgid()ing properly.
 *
 * Revision 0.2  1997/09/12 13:30:47  alexios
 * Fixed dorecent() so that the generated recent files are
 * always owned by the bbs group (permission problems otherwise).
 * Added a killinjoth() function to kill the injoth IPC message
 * queue. Added a paranoia check to the logout() function to
 * ensure that the daemon switches to the required uid and gid
 * before writing files. Minor cosmetic changes.
 *
 * Revision 0.1  1997/08/30 13:10:43  alexios
 * Initial revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_SIGNAL_H 1
#define WANT_PWD_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIO_H 1
#define WANT_DIRENT_H 1
#define WANT_GRP_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"
#include "bbsd.h"


static time_t sysvartime=0;
static time_t classtime=0;


inline static void
logoutaudit()
{
  /* We always log abnormal/forced exits */

#ifdef DEBUG
  fprintf(stderr,"Logging user disconnection (user=%s)\n",thisuseronl.userid);
#endif

  /* Log a normal exit */

  if(sysvar->lofaud){
    if(thisuseronl.flags&OLF_LOGGEDOUT){
      audit(thisuseronl.channel,AUDIT(LOGOUT),
	    thisuseronl.userid,
	    baudstg(thisuseronl.baudrate));
      return;
    }
  }

  if(thisuseronl.flags&OLF_RELOGGED)
    audit(thisuseronl.channel,AUDIT(RELOGON),
	  thisuseronl.userid,
	  baudstg(thisuseronl.baudrate));
  else {
    switch(thisuseronl.lastpage){
    case EXIT_CREDS:		/* User ran out of credits */
      audit(thisuseronl.channel,AUDIT(CREDHUP),
	    thisuseronl.userid,
	    baudstg(thisuseronl.baudrate));
      return;
    case EXIT_TIMEOUT:		/* Connection timed out */
      audit(thisuseronl.channel,AUDIT(TIMEOUT),
	    thisuseronl.userid,
	    baudstg(thisuseronl.baudrate));
      return;
    case EXIT_TIME:		/* Time limit reached */
      audit(thisuseronl.channel,AUDIT(TIMEHUP),
	    thisuseronl.userid,
	    baudstg(thisuseronl.baudrate));
      return;
    case EXIT_DISCON:		/* User disconnected or line died */
    default:
      /*audit(thisuseronl.channel,AUDIT(DISCON),
	    thisuseronl.userid,
	    baudstg(thisuseronl.baudrate));
	    return;*/
    }
  }
  
  /* User disconnected or line died */
  audit(thisuseronl.channel,AUDIT(DISCON),
	thisuseronl.userid,
	baudstg(thisuseronl.baudrate));
}


static void
dorecent()
{
  FILE *fp;
  char fname[256],command[256];
  int i;

  i=time(0);
  fp=fopen(RECENTFILE,"a");
  fprintf(fp,"%s %s %08lx %08x\n",thisuseronl.userid,
	  thisuseronl.channel,thisuseronl.loggedin,i);
  fclose(fp);
  
  sprintf(fname,"%s/%s",RECENTDIR,thisuseronl.userid);
  fp=fopen(fname,"a");
  fprintf(fp,"%s %08lx %08x\n",thisuseronl.channel,thisuseronl.loggedin,i);
  fclose(fp);
  
  sprintf(command,"tail -%d %s >%s/tmp%08x;\\mv %s/tmp%08x %s;chown bbs.bbs %s",
	  RECENT_ENTRIES,fname,RECENTDIR,i,RECENTDIR,i,fname,fname);
  system(command);

  chown(fname,bbsuid,bbsgid);
  chmod(fname,0660);
  sprintf(fname,"%s/.%s",ONLINEDIR,thisuseronl.channel);
  unlink(fname);
}


static void
killinjoth()
{
  struct msqid_ds buf;
      
  if(msgctl(thisuseronl.injothqueue,IPC_RMID,&buf)<0)return;
}


static void
cleanup()
{
  struct linestatus status;
  getlinestatus(thisuseronl.channel,&status);
  status.user[0]=0;
  setlinestatus(thisuseronl.channel,&status);
}


void
logoutuser()
{
  int pid;

  if(!(thisuseronl.userid[0]&&thisuseronl.loggedin))return;

  switch(pid=fork()){
  case -1:
    logerrorsys("Unable to fork() while spawning getty");
    return;
  case 0:
    break;
  default:
    return;
  }


  /* Kill the injoth() message queue */

  killinjoth();

  
  /* Become a plain user -- we're going to do file handling */

  setgid(bbsgid);
  initgroups(BBSUSERNAME,bbsgid);
  setuid(bbsuid);


  /* Record the user's exit in the audit trail */

  logoutaudit();


  /* Record the user's exit in the RECENT file */

  dorecent();


  /* Cleanup misc files */

  cleanup();
  
  exit(0);
}


void
refreshsysvars()
{
  struct stat s;
  if(stat(SYSVARFILE,&s)){
    fatalsys("Unable to stat() sysvar file (%s)!",SYSVARFILE);
  }

  if (s.st_ctime!=sysvartime && sysvar) {
    FILE *sysvarf;

    sysvartime=s.st_ctime;
    
    if((sysvarf=fopen(SYSVARFILE,"r"))!=NULL){
      fread(sysvar,sizeof(struct sysvar),1,sysvarf);
    }

    fclose(sysvarf);
  }
}


void
refreshclasses()
{
  struct stat s;
  if(stat(CLASSFILE,&s)){
    fatalsys("Unable to stat() class file (%s)!",CLASSFILE);
  }
  if (s.st_ctime!=classtime) {
    classtime=s.st_ctime;
    initmodule(INITCLASSES);
  }
}


void
byebye(struct shmuserrec *ushm,int prompt)
{
  FILE *fp;
  char fname[64], *outbuf;
  int  chan=getchannelindex(ushm->onl.channel);
  
  setmbk(sysblk);
  outbuf=getmsglang(prompt,ushm->acc.language-1);
	    
  if(outbuf){
    sprintf(fname,DEVDIR"/%s",ushm->onl.emupty);
    if((fp=fopen(fname,"w"))!=NULL){
      fprintf(fp,"%s",outbuf);
    }
    fflush(fp);
    fclose(fp);
  }

#ifdef DEBUG
  fprintf(stderr,"byebye(): killing process group %d for tty %s\n",
	  gettys[chan].pid,ushm->onl.channel);
#endif

  if(!gettys[chan].pid)return;
  kill(-gettys[chan].pid,SIGHUP);
  if(kill(-gettys[chan].pid,0)){
    sleep(1);
    kill(-gettys[chan].pid,SIGTERM);
    if(kill(-gettys[chan].pid,0)){
      sleep(1);
      kill(-gettys[chan].pid,SIGKILL);
    }
  }
}
