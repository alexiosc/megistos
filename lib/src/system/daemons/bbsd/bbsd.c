/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsd.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: D, January 95, Version 0.8                                   **
 **  PURPOSE:  Generic multi-purpose BBS daemon.                            **
 **  NOTES:    Purposes:                                                    **
 **              * Allocate user shared memory upon login, destroy upon     **
 **                logout.                                                  **
 **              * Manage credit consumption and other timing activities.   **
 **              * Manage (spawn, warn) BBS events.                         **
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
 * Changed a few fatal() calls to fatalsys(). Added support
 * for the MetaBBS daemon.
 *
 * Revision 0.9  1998/12/27 16:21:05  alexios
 * Added autoconf support. Added support for new getlinestatus().
 * Daemon restarts entire system after a few hours of inactivity
 * to make sure no inadvertent zombies are left running. Not
 * strictly needed, though. This may be removed in later versions.
 *
 * Revision 0.8  1998/07/26 21:11:32  alexios
 * Set CHANNEL environment variable so any errors are shown to
 * come from bbsd.
 *
 * Revision 0.7  1998/07/24 10:25:55  alexios
 * Added idle timeout zapping of telnetted users in caase the
 * connection has silently died without notification.
 * Migrated to bbslib 0.6.
 *
 * Revision 0.6  1997/11/06 20:04:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.5  1997/11/05 11:06:30  alexios
 * Added a function to enablegettys() after they've been disabled
 * for some reason. Made it so the function gets called when
 * bbsd receives a SIGUSR signal.
 *
 * Revision 0.4  1997/09/14 13:52:46  alexios
 * Kept stdout open when DEBUG is defined for obvious reasons
 * of debugging processes.
 *
 * Revision 0.3  1997/09/01 10:32:11  alexios
 * Fixed call to events() so that events are spawned on the
 * minute (at 00 seconds).
 *
 * Revision 0.2  1997/08/30 13:12:30  alexios
 * Rewritten the daemon practically from scratch in an effort to
 * speed it up, debug it, remove redundancy and reduce the
 * system's dependence on files under /etc. BBSD now spawns the
 * gettys, so init(8) isn't necessary and also includes all the
 * functionality of blad, which is now obsolete.
 *
 * Revision 0.1  1997/08/28 11:14:58  alexios
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
#define WANT_TIME_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"
#include "mbk_signup.h"
#include "mbk_metabbs.h"
#include "bbsd.h"


int bbsuid, bbsgid;
char *progname;



static void
getpwbbs()
{
  struct passwd *pass=pass=getpwnam(BBSUSERNAME);
  if(pass==NULL)fatal("User %s not found.",BBSUSERNAME);
  bbsuid=pass->pw_uid;
  bbsgid=pass->pw_gid;
}


static void
mkpipe()
{
  unlink(BBSDPIPEFILE);
  if(mkfifo(BBSDPIPEFILE,0220)){
    fatalsys("Unable to mkfifo(\"%s\",0220)",BBSDPIPEFILE);
  }
  if(chown(BBSDPIPEFILE,bbsuid,bbsgid)){
    fatalsys("Unable to chown() %s",BBSDPIPEFILE);
  }
  if(chmod(BBSDPIPEFILE,0220)){
    fatalsys("Unable to chmod(\"%s\",0220)",BBSDPIPEFILE);
  }
}


static void
storepid()
{
  FILE *fp=fopen(BBSETCDIR"/bbsd.pid","w");
  if(fp==NULL){
    fatalsys("Unable to open "BBSETCDIR"/bbsd.pid for writing.");
    exit(1);
  }
  fprintf(fp,"%d",getpid());
  fclose(fp);
  chmod(BBSETCDIR"/bbsd.pid",0600);
  chown(BBSETCDIR"/bbsd.pid",0,0);
}


static void
mainloop()
{
  int killed=0;
  int fd=open(BBSDPIPEFILE,O_RDONLY|O_NONBLOCK);
  int ticks=0, jiffies=0;
  int t, sec, min, oldmin=-1;
  int timestarted=time(NULL);

  if(fd<0){
    fatalsys("Unable to open() %s",BBSDPIPEFILE);
    exit(1);
  }

  for(;!killed;){
    respawn();			/* Respawn gettys and bbslockd*/
    processcommands(fd);	/* Process commands from the FIFO */

    usleep(SLEEPTIME);		/* Sleep a bit */


    /* Execute events no more than once a minute, on the minute */
    
    t=now();
    sec=tdsec(t);
    min=tdmin(t);
    if(sec==0&&oldmin!=min){
      events();
      oldmin=min;
    }


    /* The following is executed once every jiffy */

    ticks=(ticks+1)%TICKSPERJIFFY;
    if(ticks)continue;

    charge();			/* Charge credits and count on-line time */


    /* We register with the Meta-BBS daemon (or send a 'heartbeat'
       re-registration) every 5 mins, or every time our number of
       online users changes (whichever occurs first). */
    
#ifdef HAVE_METABBS
    if((last_registration_time+(5*60))<=time(NULL))register_with_metabbs();
#endif


    /* The following is executed once every minute */

    jiffies=(jiffies+1)%JIFFIESPERMIN;
    if(jiffies)continue;
    
    resetcounts();		/* Reset spawn counts on gettys */




    /* Restart system if it is idle */

    if(numusers==0 && (time(0)-timestarted>sysvar->bbsrst*3600)){
      sepuku();
      exit(0);			/* This should never really happen */
    }
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
    close(0);
#ifndef DEBUG
    close(1);
    close(2);
#endif
    break;
  default:
    exit(0);
  }
}


static promptblk *msg;

int   supzap;

#ifdef HAVE_METABBS
int   telnet_port;
char *bbscod;
char *url;
char *email;
char *allow;
char *deny;
char *bbsad;
#endif


void
enablegettys()
{
  int i;
  for(i=0;i<numchannels;i++)if(gettys[i].disabled){
    gettys[i].disabled=0;
    gettys[i].spawncount=0;
  }
}


static void init(int argc, char *argv[])
{
  progname=argv[0];
  setprogname(argv[0]);

  msg=opnmsg("signup");
  supzap=numopt(SUPZAP,0,32767);
  clsmsg(msg);

#ifdef HAVE_METABBS
  msg=opnmsg("metabbs");
  telnet_port=numopt(TELPRT,0,65535);
  url=stgopt(URL);
  email=stgopt(EMAIL);
  allow=stgopt(ALLOW);
  deny=stgopt(DENY);
  bbsad=stgopt(BBSAD);
  init_non_megistos();		/* Initialise the non-Megistos system table */
  clsmsg(msg);
#endif

  msg=sysblk=opnmsg("sysvar");
  bbscod=stgopt(BBSCOD);
  signal(SIGUSR1,enablegettys);
  setenv("CHANNEL","[bbsd]",1);
}


int
main(int argc, char *argv[])
{
  init(argc,argv);		/* Initialise stuff */

  checkuid();			/* Make sure the superuser is running us */

  forkdaemon();			/* Fork() the daemon */
  
  getpwbbs();			/* Get the /etc/passwd entry user 'bbs' */

  cleanuponline();		/* Clean up the ONLINE directory */

  mkpipe();			/* Make BBSD's FIFO and set its permissions */

  readchannels();		/* Read in the channels */

  storepid();			/* Store the daemon's PID */

  monitorshm();			/* Allocate monitor memory */

  sysvarshm();			/* Allocate sysvar memory */

  mainloop();			/* Finally, run the daemon's main loop */
  
  return 0;			/* We never get here. */
}
