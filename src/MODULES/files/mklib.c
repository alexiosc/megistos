/*****************************************************************************\
 **                                                                         **
 **  FILE:     mklib.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  mklib: create a library                                      **
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
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.5  2000/01/06 10:37:25  alexios
 * Modified mklib() to accept a third argument, allowing the
 * caller to set the initial flags of a library when readytowrite
 * is not set. Sanity checks and security fixes.
 *
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_FCNTL_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk/mbk_files.h"


void
discoverdevice(struct libidx *lib)
{
  struct stat st;

  if(stat(lib->dir,&st)){
    error_fatalsys("Unable to stat directory \"%s\"",lib->dir);
  }
  
  lib->device=st.st_dev;
}


void
mklib(struct libidx *lib, int readytowrite, int flags)
{
  int i;
  char *cp;
  struct stat st;


  /* Make the library's directory */

  mkdir(lib->dir,0770);
  if(stat(lib->dir,&st) || !S_ISDIR(st.st_mode)){
    int i=errno;
    error_intsys("Unable to mkdir(\"%s\")",lib->dir);
    prompt(OCREMKD,lib->dir,i,strerror(i));
    return;
  }

#if 0
  /* Make the library's long description file and initialise it to
     contain the short description. */

  sprintf(fname,"%s/%s",lib->dir,rdmefil);
  if(stat(fname,&st)){
    char s[41];
    i=creat(fname,0660);
    sprintf(s,"%s\n",lib->descr);
    write(i,s,strlen(s));
    close(i);
  }
#endif
  
  if((cp=strrchr(lib->fullname,'/'))==NULL)cp=lib->fullname;
  else cp++;
  for(i=0;*cp;i++)lib->keyname[i]=tolower(*cp++);

  discoverdevice(lib);

  lib->libnum=libmaxnum()+1;
  
  if(!readytowrite){
    lib->crdate=today();
    lib->crtime=now();

    lib->readkey=defrkey;
    lib->downloadkey=defdkey;
    lib->uploadkey=defukey;

    lib->filelimit=defflim;
    lib->filesizelimit=defslim;
    lib->libsizelimit=defllim;

    lib->dnlcharge=defdchg;
    lib->uplcharge=defuchg;
    lib->rebate=defreb;

    lib->numfiles=lib->numbytes=lib->numunapp=lib->bytesunapp=0;

    bzero(&(lib->uploadsperday),sizeof(lib->uploadsperday));
    bzero(&(lib->bytesperday),sizeof(lib->bytesperday));

    lib->flags=flags;
    if(defdaud)lib->flags|=LBF_DNLAUD;
    if(defuaud)lib->flags|=LBF_UPLAUD;
  }

  libcreate(lib);
}


void
makemainlib()
{
  struct libidx mainlib;

  if(libexists(libmain,0))return;

  bzero(&mainlib,sizeof(mainlib));
  strcpy(mainlib.fullname,libmain);
  strcpy(mainlib.descr,msg_get(MAINDESCR));
  sprintf(mainlib.dir,"%s/%s",FILELIBDIR,libmain);
  mklib(&mainlib,0,0);
}
