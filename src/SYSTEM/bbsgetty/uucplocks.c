/*****************************************************************************\
 **                                                                         **
 **  FILE:     uucplocks.c                                                  **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  Deal with UUCP locks                                         **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 15:00:27  alexios
 * Initial revision
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_SYS_TYPES_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SIGNAL_H 1
#define WANT_UNISTD_H 1
#define WANT_ERRNO_H 1
#define WANT_WAIT_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include <bbsgetty.h>



static int chpid=-1;		/* The lockfile minder child's PID */



/* readuucplock() reads the lock specified by name, returning the PID
   stored in the lock file or -1 on error. */

static int
readuucplock(char *name)
{
  int fd;
  pid_t pid;
  char apid[16];

  debug(D_LOCK,"readuucplock(\"%s\") called.",name);

  if((fd=open(name,O_RDONLY))<0){
    int i=errno;
    debug(D_LOCK,"Unable to open(\"%s\",O_RDONLY), errno=%d",name,i);
    return -1;
  }
  

  /* Try reading the PID as an ascii number first. */

  read(fd,apid,sizeof(apid));
  if(sscanf(apid,"%d",(int*)&pid)!=1){


    /* Hm, maybe it's stored as a binary number */

    close(fd);
    if((fd=open(name,O_RDONLY))<0){
      int i=errno;
      debug(D_LOCK,"Unable to open(\"%s\",O_RDONLY), errno=%d",name,i);
      return -1;
    }
    read(fd,&pid,sizeof(pid));
  }

  close(fd);
  debug(D_LOCK,"Read PID %d from the lockfile.",pid);
  return pid;
}



/* checkuucplock() tests for the presence of a UUCP lock file, returning a
   non-zero value if one is found. */

int
checkuucplock(char *name)
{
  int pid;
  struct stat st;
  
  debug(D_LOCK,"checkuucplock(\"%s\") called.",name);
  
  if (stat(name,&st) && errno==ENOENT){
    debug(D_LOCK,"stat(\"%s\",&st) failed, file not found",name);
    return 0;
  }

  if((pid=readuucplock(name))<=0){
    debug(D_LOCK,"Unable to read lockfile \"%s\"!",name);
    return 0;
  }
  
  if(pid==(int)getpid()){
    debug(D_LOCK,"Lockfile belongs to me... damn race conditions!");
    return 0;
  }
  
  if((kill(pid,0)<0)&&errno==ESRCH) {
    debug(D_LOCK,"Stale lock, will remove.");
    unlink(name);
    return 0;
  }
  
  debug(D_LOCK,"Lock belongs to active process.");
  return 1;
}



/* makeuucplock creates the named lock, storing our PID inside the filename */

int makeuucplock(char *name)
{
  int fd, pid;
  char buf[256];
  char apid[16];
  
  debug(D_LOCK, "makelock(\"%s\") called.",name);

  /* First make a temp file */
  sprintf(buf,UUCPLOCK,"tmp.");
  sprintf(apid,"%d",(int)getpid());
  strcat(buf,apid);
  if((fd=creat(buf,0444))<0){
    debug(D_LOCK,"Unable to create tempfile \"%s\"",buf);
    return -1;
  }

  debug(D_LOCK,"Created temp file \"%s\"",buf);


  /* Put our pid in it */

  sprintf(apid,"%d",(int)getpid());
  write(fd,apid,strlen(apid));
  close(fd);
  
  
  /* Link it to the lock file. */
  while(link(buf,name)<0){
    int i=errno;
    debug(D_LOCK,"link(\"%s\",\"%s\") failed, errno=%d\n",buf,name,i);
    if(i==EEXIST){		/* Lock file already exists. */
      
      /* Maybe someone already created that lock? */
      
      if((pid=readuucplock(name))<=0){
	debug(D_LOCK,"Whoops, link \"%s\" exists now. Sleeping for 30s...",
	      name);
	sleep(30);
	continue;
      }
      
      
      /* They did, but are they still around? */
      
      if((kill(pid,0)<0)&& errno==ESRCH){
	unlink(name);		/* Remove the link... */
	continue;		/* ...and retry. */
      }
      
      debug(D_LOCK,"Lock \"%s\" not created, someone beat us to it.",name);
      unlink(buf);
      return -1;
    }
  }
    
    
  /* And there was much rejoicing */
  
  debug(D_LOCK,"Lock \"%s\" created.",name);
  unlink(buf);
  return 1;
}



/* If any UUCP locks are pending on this tty, wait until they're gone. */

void waituucplocks()
{
  debug(D_LOCK,"Checking for the lockfile."); 
  
  if(checkuucplock(lock)) {
    while(checkuucplock(lock))sleep(30);
    exit(0);
  }
}




/* A simplistic signal handler to remove our lock */

void
rmuucplock()
{
  unlink(lock);
}



/* Lock the line. Sending SIG{HUP,INT,QUIT,TERM} removes the lock */

void lockline()
{
  debug(D_LOCK,"locking the line.");
  
  if(!makeuucplock(lock))exit(0); /* Errors are reported by makelock() */

  signal(SIGHUP,rmuucplock);
  signal(SIGINT,rmuucplock);
  signal(SIGQUIT,rmuucplock);
  signal(SIGTERM,rmuucplock);
}




void
uucplockchildhangup()
{
  debug(D_LOCK,"Child caught SIGHUP.");
  exit(0);
}



/* watchlocks() forks a child process to monitor the UUCP lockfile. If
   a lockfile is detected, the child signals a SIGHUP which should
   kill the parent. The parent kills the child with a SIGHUP. */

void
watchuucplocks()
{
  int ppid;
  
  /* If waitfor is used, there's no need to check for locks. */

  if(waitfor)return;

  ppid=(int)getpid();


  /* Now fork */
  if((chpid=fork())==0){
    
    /* This is the child process */

    signal(SIGHUP,uucplockchildhangup);

    for(;;) {
      if((kill(ppid,0)<0)&&errno==ESRCH){
	debug(D_LOCK,"Parent exited, child exiting too.");
	exit(0);
      }
      if(checkuucplock(lock))break;
      if((altlock)&&checkuucplock(altlock))break;
      sleep(5);
    }
      
    debug(D_LOCK,"Found lockfile(s), signaling parent and exiting...");
    kill(ppid,SIGHUP);
    exit(0);
  }
    

  /* This is the parent process. */
  
  if(chpid<0){
    fatal("Couldn't fork lock-minding child process, exiting.");
  }
}



void
killminder()
{
  int status;
  if(chpid<0)return;
  kill(chpid,SIGHUP);
  wait(&status);
}
