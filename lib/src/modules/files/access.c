/*****************************************************************************\
 **                                                                         **
 **  FILE:     access.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  Users' accesses to the libraries                             **
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
 * Revision 1.1  2001/04/16 14:55:37  alexios
 * Initial revision
 *
 * Revision 0.3  1999/07/18 21:29:45  alexios
 * Changed islibop() to recursively look at the parent libraries
 * since a libop is always privileged in any child libraries owned
 * by his/her library.
 *
 * Revision 0.2  1998/12/27 15:40:03  alexios
 * Added autoconf support. Added support for new getlinestatus().
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk_files.h"


#define LIBLOCK   "LCK..lib.%s.%d"
#define ADMINLOCK "LCK..libadm.%d"


/* This an extern, defined in clubhdr.o */

int getclubax(useracc *uacc, char *club);


static int lastlibnum=-1;
static int lastadmin=-1;


int islibop(struct libidx *l)
{
  int i;
  if(haskey(&thisuseracc,libopkey))return 1;
  for(i=0;i<5;i++){
    if(sameas(thisuseracc.userid,l->libops[i]))return 1;
  }
  
  /* Recurse looking at the parent libraries, too */

  {
    struct libidx lib;
    if(libreadnum(l->parent,&lib)){
      return islibop(&lib);
    }
  }

  return 0;
}


static int forcefail=0;


void
forcepasswordfail()
{
  forcefail=1;
}


static int
getlibpasswd(struct libidx *l)
{
  int i;
  if(forcefail)return 0;
  for(i=0;i<numtries;i++){
    prompt(ENTPASS);
    setpasswordentry(1);
    getinput(15);
    setpasswordentry(0);
    if(sameas(input,l->passwd))return 1;
    endcnc();
    if(i+1<numtries)prompt(WRNGPSS);
  }
  prompt(FAILPASS);
  return 0;
}


int
getlibaccess(struct libidx *l, int access_type)
{
  /* Check for the Operator, but still ask for a password if applicable We'll
     allow the operator access to the library, as long as they provide a
     correct password (if required). We skip the other tests (club and mere
     mortal test). */

  if(islibop(l)){
    if(access_type==ACC_ENTER&&l->flags&LBF_LOCKENTR)return getlibpasswd(l);
    if(access_type==ACC_DOWNLOAD&&l->flags&LBF_LOCKDNL)return getlibpasswd(l);
    if(access_type==ACC_UPLOAD&&l->flags&LBF_LOCKUPL)return getlibpasswd(l);
    return 1;
  }

  /* If library is attached to a club, check club permissions */

  if(l->club[0]){
    int clubax=getclubax(&thisuseracc,l->club);
    if(access_type==ACC_VISIBLE && clubax<CAX_READ)return 0;
    if(access_type==ACC_ENTER && clubax<CAX_READ)return 0;
    if(access_type==ACC_DOWNLOAD && clubax<CAX_DNLOAD)return 0;
    if(access_type==ACC_UPLOAD && clubax<CAX_UPLOAD)return 0;
  }

  /* Check for mere mortals */

  if(access_type==ACC_VISIBLE) return haskey(&thisuseracc,l->readkey);
  else if(access_type==ACC_ENTER){
    if(!haskey(&thisuseracc,l->readkey))return 0;
    if(l->flags&LBF_LOCKENTR)return getlibpasswd(l);
  } else if(access_type==ACC_DOWNLOAD){
    if(!haskey(&thisuseracc,l->downloadkey))return 0;
    if(l->flags&LBF_LOCKDNL)return getlibpasswd(l);
  } else if(access_type==ACC_UPLOAD){
    if(!haskey(&thisuseracc,l->uploadkey))return 0;
    if(l->flags&LBF_LOCKUPL)return getlibpasswd(l);
  }

  return 1;
}


void
locklib()
{
  char lock[256];
  unlocklib();
  sprintf(lock,LIBLOCK,thisuseronl.channel,lastlibnum=library.libnum);
  placelock(lock,"inlib");
}


void
unlocklib()
{
  char lock[256];
  if(lastlibnum!=-1){
    sprintf(lock,LIBLOCK,thisuseronl.channel,lastlibnum);
    rmlock(lock);
    lastlibnum=-1;
  }
}


int
checklocks(int libnum)
{
  int  i;
  char lock[256],dummy[64];
  struct linestatus status;

  for(i=0;i<numchannels;i++){
    if(getlinestatus(channels[i].ttyname,&status)){
      if((status.result==LSR_USER)
	 &&(!sameas(status.user,thisuseracc.userid))){
	sprintf(lock,LIBLOCK,channels[i].ttyname,libnum);
	if(checklock(lock,dummy)>0)return 0;
      }
    }
  }
  return 1;
}


int
adminlock(int libnum)
{
  char lock[256];
  adminunlock();
  sprintf(lock,ADMINLOCK,libnum);
  if(checklock(lock,NULL)){
    prompt(LIBCOL);
    if(waitlock(lock,5)){
      prompt(LIBFAIL);
      return 0;
    }
  }
  placelock(lock,"admin");
  lastadmin=libnum;
  return 1;
}


void
adminunlock()
{
  char lock[256];
  if(lastadmin!=-1){
    sprintf(lock,ADMINLOCK,lastadmin);
    rmlock(lock);
    lastadmin=-1;
  }
}


int
autoapp(struct libidx *l)
{
  return islibop(l)||l->flags&LBF_AUTOAPP;
}
