/*****************************************************************************\
 **                                                                         **
 **  FILE:     opentty.c                                                    **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  Open the tty (what else?)                                    **
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
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.3  1999/07/18 21:54:26  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Added support for
 * the pre/postconnect fields.
 *
 * Revision 1.2  1998/12/27 16:15:40  alexios
 * Slight baud rate bug fixes. Migrated to the new
 * {get,set}linestatus() functions.
 *
 * Revision 1.1  1998/12/15 22:11:57  alexios
 * Fixed erroneous line status reporting. Autobaud bugs fixed.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif


#define OPENTTY_C 1
#define WANT_STDIO_H 1
#define WANT_SIGNAL_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "bbsgetty.h"



void opentty()
{
  int	flags, i, cbaud=0, nspeed=0;
  char	ch;
  int   fd;

  debug(D_RUN,"Opening line: %s (localline=%d)",devname,localline);


  /* Is this a local line? */
  if(localline){
    debug(D_RUN,"The line is local, initiating connection immediately.");
  } else writelinestatus(LSR_RING);


  /* Open the device */
  if((fd=open(devname,waitfor?(O_RDWR|O_NDELAY):(O_RDWR)))<0){
    error_fatalsys("Cannot open line %s",devname);
  }


  /* The file descriptor should be 0 (stdin) */
  if(fd!=0){
    error_fatal("Whoops, file descriptor for stdin is not zero.");
  }


  /* Duplicate it to get stdout */
  if(dup(0)!=1) {
    error_fatal("Whoops, file descriptor for stdout is not one.");
  }


  /* And again for stderr */
  if(dup(0)!=2) {
    error_fatal("Whoops, file descriptor for stderr is not two.");
  }
  

  /* Stop looking for lockfiles now, unless we need to wait some more. */
  if(!waitfor)killminder();


  /* Lock the line */
  lockline();


  /* Become the process group leader */
  setpgrp();
  

  /* Unbuffered I/O for the standard files */
  setbuf(stdin,NULL);
  setbuf(stdout,NULL);
  setbuf(stderr,NULL);


  /* Enable non-blocking mode for stdin */
  flags=fcntl(0,F_GETFL,0);
  fcntl(0,F_SETFL,flags&~O_NDELAY);
  flags=fcntl(1,F_GETFL,0);
  fcntl(1,F_SETFL,flags&~O_NDELAY);
  flags=fcntl(2,F_GETFL,0);
  fcntl(2,F_SETFL,flags&~O_NDELAY);


  /* Setup the initial (arg2=0) flags of the terminal */
  settermios(&itermios,0);
  

  /* Cancel any timeout alarms (not really needed, but won't hurt) */
  signal(SIGALRM,SIG_DFL);
  alarm(0);


  /* Are we delaying line initialisation? */
  if(delay){
    debug(D_RUN,"DELAY specified, sleeping for %d seconds...",delay);
    sleep(delay);

    /* Flush any characters sent to stdin while we were waiting */
    fcntl(0,F_SETFL,flags|O_NDELAY);
    while(read(0,&ch,1)==1);
    fcntl(0,F_SETFL,flags&~O_NDELAY);
  }


  /* registerlinespeed(); */
  /*  if(localline)writelinestatus("ANSWER");*/

  
  /* If a PRECONNECT command is set, issue it now, becoming mortal first */
  if(preconnect!=NULL){
    debug(D_RUN,"Executing preconnect command \"%s\"",preconnect);
    execute_as_mortal(preconnect);
    debug(D_RUN,"Done running preconnect command.");
  }
    

  /* Is there a connect string that we need to send? */
  if(connectstr) {
    debug(D_RUN,"Performing connect sequence.");
    
    if(!strcmp(connectstr,"DEFAULT"))connectstr=DEF_CONNECT;
    if((chat(connectstr))<0) {
      debug(D_RUN, "Connect sequence failed, aborting.");

      /* Exit naturally. This has the desirable effect of refreshing the line's
	 hardware with the init strings etc when the CONNECT timeout
	 occurs. Setting the CONNECT timeout to a conveniently high length of
	 time will help here (this can be done by . */
      exit(0);	
    }


    /* Unless the comm rate is locked, we now have enough information
       to set it. */

    writelinestatus(LSR_ANSWER);
    speed[0]=0;
    nspeed=0;
    if(!lockedbaud){
      if(autobaud) {
	int maxspeed=-1;
	debug(D_RUN,"Detected communication rate: (%s)",autorate);

	/* See if we have a matching termios flag for the modem speed. There's
           no guarantee that there *is* one, since modern modems can do funny
           speeds (usually multiples of 2400 bps). If we fail to find the right
           one, we'll stick with the first speed that's greater than the one
           the modem's reported speed. That should do it. */

	if((nspeed=atoi(autorate))>0){
	  for(i=0;speedtab[i].nspeed;i++){
	    if(nspeed==speedtab[i].nspeed) {
	      cbaud=speedtab[i].cbaud;
	      strcpy(speed,speedtab[i].speed);
	      break;
	    } else if((speedtab[i].nspeed>=nspeed) &&
		      (maxspeed<0 || (speedtab[i].nspeed<maxspeed))) {
	      cbaud=speedtab[i].cbaud;
	      maxspeed=speedtab[i].nspeed;
	      strcpy(speed,speedtab[i].speed);
	    }
	  }

	  if(strlen(speed)){
	    debug(D_RUN,"Modem reports %d bps, selected CBAUD is %s bps.",
		  nspeed,speed);
	  } else {
	    debug(D_RUN,"Modem reports %d bps, yet no CBAUD flag was found.");
	  }
	}
      }
    }
    

    /* If we've settled on a speed flag, set it in the line's termios */
    if(cbaud) {
      itermios.c_cflag=(itermios.c_cflag&~CBAUD)|cbaud;
      ftermios.c_cflag=(ftermios.c_cflag&~CBAUD)|cbaud;
      settermios(&itermios,0);
    }


    /* However, even if we've locked the serial comm rate, make the
       actual *CONNECT* speed available to the BBS, at least if we
       have it. */

    if(strlen(autorate)&&atoi(autorate)>0){
      debug(D_RUN,"Will report %d bps (actual comms speed) to the BBS.",
	    atoi(autorate));
      nspeed=atoi(autorate);
    }


    /* Make the modem speed and device available to the rest of the BBS */
    if(nspeed){
      reportedlinespeed=nspeed;
      unsetenv("BAUD");
      setenv("BAUD",autorate,1);
      setenv("CHANNEL",device,1);
    }

/*     registerlinespeed();*/   /* Be paranoid, cause THEY are everywhere! */
/* This line has finally been to the shrink. :-) */

  }
}
