/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsgetty.c                                                   **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  Talk to comms hardware and establish connections.            **
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
 * Revision 1.1  2001/04/16 15:00:16  alexios
 * Initial revision
 *
 * Revision 1.1  1999/07/18 21:54:26  alexios
 * Changed a few fatal() calls to fatalsys(). Added config
 * field that executes some command immediately after connection
 * (postconnect). Minor fixes.
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
#define WANT_SYS_STAT_H 1
#define WANT_SIGNAL_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "bbsgetty.h"



static void
startemud()
{
  char fname[256];
  int i;

  settermios(&ftermios,1);	/* Switch the terminal to its final state */

  /* Execute the post-connect command, if any */
  if(postconnect!=NULL){
    debug(D_RUN,"Executing postconnect command \"%s\"",postconnect);
    execute_as_mortal(postconnect);
    debug(D_RUN,"Done running postconnect command.");
  }
  
  sprintf(fname,"%s/.emu-%s",EMUFIFODIR,device);
  unlink(fname);

  if(mkfifo(fname,0660)){
    fatalsys("Unable to create emulation FIFO %s",fname);
  }
  if(chown(fname,bbsuid,bbsgid)){
    fatalsys("Unable to chown(\"%s\",%d,%d)",fname,bbsuid,bbsgid);
  }

  debug(D_RUN,"Turning into emud. Bye!");
  execl(EMUDBIN,EMUDBIN,NULL);
  i=errno;

  /* If we get to this point, something's gone wrong */
  debug(D_RUN,"Aieee, something's gone very wrong. Couldn't spawn emud.");
  errno=i;
  fatalsys("Unable to spawn emu daemon for %s.",device);
}


int main(int argc, char **argv)
{
  setprogname("bbsgetty");	/* this facilitates Megistos error logging */
  init(argc,argv);		/* initialise bbsgetty */
  waituucplocks();		/* wait for pending UUCP locks on this tty */
  initline();			/* initialise the channel */
  watchuucplocks();		/* monitor the lockfiles */
  opentty();			/* open & initialize the tty */
  startemud();			/* start emud (only it spawns bbslogin) */
  return 0;			/* we never reach this point (hopefully) */
}
