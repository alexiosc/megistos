/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsinit.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  BBS watchdog daemon.                                         **
 **  NOTES:    Purposes:                                                    **
 **              * Makes sure all daemons are running properly. If any      **
 **                exit (because of error or [in bbsd's case] a need for    **
 **                refresh (to clear any memory leaks), bbsinit restarts    **
 **                the daemon. If bbsd dies, we kill *all* daemons and      **
 **                restart them.                                            **
 **                                                                         **
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
 * Revision 1.1  2000/01/06 11:44:10  alexios
 * Corrected name of rpc.metabbs PID lock file.
 *
 * Revision 1.0  1999/08/07 02:22:10  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define DEBUG


#define WANT_PWD_H 1
#define WANT_SYS_WAIT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_IOCTL_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"


int bbsuid, bbsgid;
char *progname;



static void
getpwbbs()
{
  struct passwd *pass=pass=getpwnam(BBSUSERNAME);
  if(pass==NULL)error_fatal("User %s not found.",BBSUSERNAME);
  bbsuid=pass->pw_uid;
  bbsgid=pass->pw_gid;
}


static void
storepid()
{
  FILE *fp=fopen(BBSETCDIR"/bbsinit.pid","w");
  if(fp==NULL){
    error_fatalsys("Unable to open "BBSETCDIR"/bbsinit.pid for writing.");
  }
  fprintf(fp,"%d",(int)getpid());
  fclose(fp);
  chmod(BBSETCDIR"/bbsinit.pid",0600);
  chown(BBSETCDIR"/bbsinit.pid",0,0);
}


struct daemon {
  char *name;
  char *binary;
  char *pidfile;
  int   ismaster;
  int   pid;
};


struct daemon daemons[] = {
  {"rpc.metabbs", BINDIR"/rpc.metabbs", BBSETCDIR"/rpc.metabbs.pid",  0, 0},
  {"bbslockd",    BINDIR"/bbslockd",    BBSETCDIR"/bbslockd.pid",     0, 0},
  {"bbsd",        BINDIR"/bbsd",        BBSETCDIR"/bbsd.pid",         1, 0},
  {"statd",       BINDIR"/statd",       BBSETCDIR"/statd.pid",        0, 0},
  {"msgd",        BINDIR"/msgd",        BBSETCDIR"/msgd.pid",         0, 0},
  {"",            "",                   "", 0, 0}
};


void
murder_spree()
{
  int i;
  for(i=0;daemons[i].name[0];i++){
    if(daemons[i].pid>1){
      register int pid=daemons[i].pid;
      kill(pid,SIGTERM);
      kill(-pid,SIGTERM);
    }
  }
  sleep(3);
  for(i=0;daemons[i].name[0];i++){
    if(daemons[i].pid>1){
      register int pid=daemons[i].pid;
      kill(pid,SIGKILL);
      kill(-pid,SIGKILL);
    }
  }
}


static void
mainloop()
{
  int i, pid, status;

  for(;;){
#ifdef DEBUG_
    fprintf(stderr,"bbsinit: in main loop...\n");
#endif


    /* Check if any daemons have died */

    for(i=0;daemons[i].name[0];i++){
      int fd;
      char spid[80];
      
      if((fd=open(daemons[i].pidfile,O_RDONLY))<0)continue;
      bzero(spid,sizeof(spid));
      read(fd,spid,sizeof(spid)-1);
      close(fd);
      
      if((pid=atoi(spid))>1){
	if(!kill(pid,0))continue;
	
#ifdef DEBUG_
	fprintf(stderr,"bbsinit: daemon %s (pid %d) died.\n",
		daemons[i].name,pid);
#endif
	daemons[i].pid=0;
	if(daemons[i].ismaster)murder_spree();
	
      }
    }


    /* (Re)spawn any dead daemons */

    for(i=0;daemons[i].name[0];i++){

      /* Is the daemon dead? */

      if(daemons[i].pid==0){
	int pid;

#ifdef DEBUG_
	fprintf(stderr,"bbsinit: spawning %s.\n",daemons[i].name);
#endif

	switch(pid=fork()){
	case -1:
	  error_logsys("Unable to fork() while spawning daemon %s",daemons[i].name);
	  break;
	case 0:
	  execl(daemons[i].binary,daemons[i].binary,NULL);
	  error_fatalsys("Unable to spawn daemon %s (%s)",
		   daemons[i].name,daemons[i].binary);
	  break;
	default:
	  daemons[i].pid=pid;
	}
	
	sleep(1);
	waitpid(pid,&status,0);
      }
    }


    /* Sleep for a bit. */

    sleep(5);
  }
}


static void
checkuid()
{
  if (getuid()){
    fprintf(stderr, "%s: getuid: not super-user\n", progname);
    exit(1);
  }
}


static void
forkdaemon()
{
  switch(fork()){
  case -1:
    fprintf(stderr,"%s: fork: unable to fork daemon\n",progname);
    exit(1);
  case 0:
    ioctl(0,TIOCNOTTY,NULL);
    setsid();
#if 0

    /* These are ifdeffed out because of an insiduous daemonic bug
       involving file descriptors. */

    close(0);
    close(1);
    close(2);
#endif
    break;
  default:
    exit(0);
  }
}


int
main(int argc, char *argv[])
{
  progname=argv[0];
  mod_setprogname(argv[0]);
  setenv("CHANNEL","[bbsinit]",1);

  /* Some of these are merely wishful thinking, of course. */


  signal(SIGHUP,SIG_IGN);
  signal(SIGINT,SIG_IGN);
  signal(SIGQUIT,SIG_IGN);
  signal(SIGILL,SIG_IGN);
  signal(SIGTRAP,SIG_IGN);
  signal(SIGIOT,SIG_IGN);
  signal(SIGBUS,SIG_IGN);
  signal(SIGFPE,SIG_IGN);
  signal(SIGKILL,SIG_IGN);	/* Yeah, right */
  signal(SIGUSR1,SIG_IGN);
  signal(SIGSEGV,SIG_IGN);
  signal(SIGUSR2,SIG_IGN);
  signal(SIGUSR2,SIG_IGN);
  signal(SIGPIPE,SIG_IGN);
  signal(SIGALRM,SIG_IGN);
  signal(SIGTERM,SIG_IGN);
  /*  signal(SIGCHLD,SIG_IGN); */
  signal(SIGCONT,SIG_IGN);
  signal(SIGSTOP,SIG_IGN);

  checkuid();			/* Make sure the superuser is running us */
  forkdaemon();			/* Fork() the daemon */
  getpwbbs();			/* Get the /etc/passwd entry user 'bbs' */
  storepid();			/* Store the daemon's PID */
  mainloop();			/* Finally, run the daemon's main loop */

  return 0;
}
