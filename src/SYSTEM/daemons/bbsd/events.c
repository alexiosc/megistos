/*****************************************************************************\
 **                                                                         **
 **  FILE:     events.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997                                               **
 **  PURPOSE:  Execute scheduled events.                                    **
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
 * Revision 1.1  2001/04/16 15:00:33  alexios
 * Initial revision
 *
 * Revision 0.10  1999/07/18 22:00:00  alexios
 * Changed a few fatal() calls to fatalsys(). Other minor
 * changes.
 *
 * Revision 0.9  1998/12/27 16:21:05  alexios
 * Added autoconf support. Added support for new getlinestatus().
 * Other minor fixes.
 *
 * Revision 0.8  1998/07/26 21:11:32  alexios
 * No changes.
 *
 * Revision 0.7  1998/07/24 10:25:55  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.6  1997/11/06 20:04:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.5  1997/11/05 11:06:30  alexios
 * Changed calls to audit() so they use the new auditing scheme.
 *
 * Revision 0.4  1997/09/14 13:52:46  alexios
 * Fixed problem with bbs not setuid/setgid()ing properly.
 * Added an audit trail entry to log events' end of execution
 * (and exit code, for debugging).
 *
 * Revision 0.3  1997/09/12 13:30:47  alexios
 * Added a paranoia check to the eventexec() function to make
 * sure that we've changed to the required uid and gid.
 *
 * Revision 0.2  1997/09/01 10:33:34  alexios
 * Fixed bug with closedir() being called inside a loop; added
 * debugging information to the events() function while trying
 * to find above bug.
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
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIO_H 1
#define WANT_DIRENT_H 1
#define WANT_GRP_H 1
#define WANT_WAIT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"
#include "bbsd.h"


/* Event warning times. The line below means 'warn every 60 mins */
/* until less than 60 mins are left, then every 30 mins', etc.   */

static int warntimes [] = {60,30,15,10,5,4,3,2,1,-1};


void
eventexec(char *command, char *name)
{
  int pid, status;

  if((pid=fork())==0){
    
    signed short int res;

    /* Become a mere mortal to run the event */

    setgid(bbsgid);
    initgroups(BBSUSERNAME,bbsgid);
    setuid(bbsuid);
    
    /*    logerror("executing event (%s)",command); */
    if(!chdir(BINDIR))res=system(command);
    else {
      logerrorsys("eventexec(): unable to chdir(\"%s\") to run event",
	       BINDIR);
      exit(0);
    }

    if(name!=NULL)
      audit("BBS DAEMON",AUDIT(EVEND),name,res);
    
    exit(0);
  } else if(pid>1)waitpid(pid,&status,0);
}


void
asapevents()
{
  struct dirent *dirent;
  DIR *dp;
  int numusers=-1;

  switch(fork()){
  case -1:
    logerrorsys("Unable to fork() in asapevents()");
    return;
  case 0:
    break;
  default:
    return;
  }
  
  if((dp=opendir(EVENTDIR))==NULL){
    fatalsys("Unable to opendir %s",EVENTDIR);
  }

  while((dirent=readdir(dp))!=NULL){
    if(dirent->d_name[0]!='.'){
      struct event event;
      FILE *fp;
      char s[256];
      int i;
	
      memset(&event,0,sizeof(event));
      sprintf(s,"%s/%s",EVENTDIR,dirent->d_name);
      if((fp=fopen(s,"r"))==NULL)continue;
      fread(&event,sizeof(event),1,fp);
      fclose(fp);

      if((event.flags&EVF_ASAP)==0)continue;

      if(numusers<0){
	for(i=0,numusers=0;i<numchannels;i++){
	  struct linestatus status;
	  if(!getlinestatus(channels[i].ttyname,&status))continue;
	  if(status.result==LSR_USER)numusers++;
	}
      }
      
      /* There are still some users in the system */

      if(numusers>0)break;
      
      /* Kill the event file (ASAP events are one-shot */

      unlink(s);

      /* Spawn it */

      audit("BBS DAEMON",AUDIT(EVSPAWN),"[bbsd]",s);
      eventexec(event.command,s);
    }
  }
  closedir(dp);
  exit(0);
}


void
events()
{
  struct dirent *dirent;
  DIR *dp;

#ifdef DEBUG
  fprintf(stderr,"Forking to handle events.\n");
#endif

  switch(fork()){
  case -1:
    logerrorsys("Unable to fork() in events()");
    return;
  case 0:
    break;
  default:
    return;
  }
    
#ifdef DEBUG
  fprintf(stderr,"Handling events.\n");
#endif

  if((dp=opendir(EVENTDIR))==NULL){
    fatalsys("Unable to opendir %s",EVENTDIR);
  }

  while((dirent=readdir(dp))!=NULL){
#ifdef DEBUG
  fprintf(stderr,"Found filename %s\n",dirent->d_name);
#endif
    if(dirent->d_name[0]!='.'){
      struct event event;
      FILE *fp;
      int t, hour, min;
      char s[256];
	
      memset(&event,0,sizeof(event));
      sprintf(s,"%s/%s",EVENTDIR,dirent->d_name);
      if((fp=fopen(s,"r"))==NULL)continue;
      fread(&event,sizeof(event),1,fp);
      fclose(fp);
      
      if(event.flags&EVF_NOW || event.flags&EVF_ASAP)continue;
      
      t=now();
      hour=tdhour(t);
      min=tdmin(t);
      
#ifdef DEBUG
  fprintf(stderr,"Found event %s (exec at %02d:%02d, time now: %02d:%02d)\n",
	  dirent->d_name,event.hour,event.min,hour,min);
#endif
      if(hour==event.hour && min==event.min){
	if(event.flags&EVF_ONLYONCE)unlink(s);
	audit("BBS DAEMON",AUDIT(EVSPAWN),"[bbsd]",s);
	eventexec(event.command,s);
      } else if(event.flags&EVF_WARN){
	int t1 = hour*60+min;
	int t2 = event.hour*60+event.min;
	int t,i;
	
	if(t2<t1)t2+=24*60;
	
	t=t2-t1;
	for(i=0;warntimes[i]>0;i++){
	  if(t>=warntimes[i]){
	    if((t%warntimes[i])==0){
	      char command[512];
	      sprintf(command,"%s -warn %d",event.command,t);
	      eventexec(command,NULL);
	    }
	    break;
	  }
	}
      }
    }
  }
  closedir(dp);
    
  exit(0);
}
