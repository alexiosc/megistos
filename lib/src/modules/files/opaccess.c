/*****************************************************************************\
 **                                                                         **
 **  FILE:     opaccess.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  The ACCESS command                                           **
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
 * Revision 0.5  1999/07/18 21:29:45  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.4  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Fixed bug whereby password wouldn't update for the sublibrs.
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
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk_files.h"




static void
update_access(struct libidx *lib,int libnum,
	      int *changes,char *passwd,int recursive)
{
  struct libidx l;
  int res;

  if(lib->libnum==libnum){
    if(!strcmp(libmain,lib->fullname)){
      if(lib->flags&LBF_LOCKENTR||lib->readkey){
	lib->flags&=~LBF_LOCKENTR;
	lib->readkey=0;
	prompt(OACNMAIN);
      }
    }
    libupdate(lib);
  }

  if(!recursive)return;
  else if(lib->libnum==libnum)goto children;

  if(!libreadnum(libnum,&l))return;

  if(!adminlock(libnum)){
    prompt(OACCREC2,l.fullname);
  } else {
    int i;

    for(i=0;i<7;i++){
      if(!changes[i])continue;
      switch(i){
      case 0:
	l.readkey=lib->readkey;
	break;
      case 1:
	setflag(l.flags,LBF_LOCKENTR,lib->flags&LBF_LOCKENTR);
	break;
      case 2:
	l.uploadkey=lib->uploadkey;
	break;
      case 3:
	setflag(l.flags,LBF_LOCKUPL,lib->flags&LBF_LOCKUPL);
	break;
      case 4:
	l.downloadkey=lib->downloadkey;
	break;
      case 5:
	setflag(l.flags,LBF_LOCKDNL,lib->flags&LBF_LOCKDNL);
	break;
      case 6:
	strcpy(l.passwd,passwd);
	break;
      default:
      }
    }

    libupdate(&l);

    prompt(OACCREC1,l.fullname);
  }

  libnum=l.libnum;

children:
  res=libgetchild(libnum,"",&l);
  while(res){
    char keyname[20];
    update_access(lib,l.libnum,changes,passwd,recursive);
    strcpy(keyname,l.keyname);
    res=libgetchild(libnum,keyname,&l);
  }
}


void
op_access()
{
  struct libidx lib;
  int changes[7];
  int recursive=0;
  int warned=0;

  memcpy(&lib,&library,sizeof(lib));
  if(!adminlock(lib.libnum))return;

  sprintf(inp_buffer,
	  "%d\n%s\n%d\n%s\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\noff\nOK\nCANCEL\n",
	  lib.readkey,
	  lib.flags&LBF_LOCKENTR?"on":"off",
	  lib.uploadkey,
	  lib.flags&LBF_LOCKUPL?"on":"off",
	  lib.downloadkey,
	  lib.flags&LBF_LOCKDNL?"on":"off",
	  lib.passwd,
	  lib.libops[0],
	  lib.libops[1],
	  lib.libops[2],
	  lib.libops[3],
	  lib.libops[4]);

  if(dialog_run("files",OACCVT,OACCLT,inp_buffer,MAXINPLEN)!=0){
    error_log("Unable to run data entry subsystem");
    adminunlock();
    return;
  }

  dialog_parse(inp_buffer);

  if(sameas(margv[15],"OK")||sameas(margv[13],margv[15])){
    int i;
    for(i=0;i<16;i++){
      char *s=margv[i];
      switch(i){
      case 0:
	changes[i]=lib.readkey!=atoi(s);
	lib.readkey=atoi(s);
	break;
      case 1:
	{
	  int old=lib.flags;
	  setflag(lib.flags,LBF_LOCKENTR,sameas(s,"on"));
	  if(lib.flags!=old)changes[i]=1;
	  break;
	}
      case 2:
	changes[i]=lib.uploadkey!=atoi(s);
	lib.uploadkey=atoi(s);
	break;
      case 3:
	{
	  int old=lib.flags;
	  setflag(lib.flags,LBF_LOCKUPL,sameas(s,"on"));
	  if(lib.flags!=old)changes[i]=1;
	  break;
	}
      case 4:
	changes[i]=lib.downloadkey!=atoi(s);
	lib.downloadkey=atoi(s);
	break;
      case 5:
	{
	  int old=lib.flags;
	  setflag(lib.flags,LBF_LOCKDNL,sameas(s,"on"));
	  if(lib.flags!=old)changes[i]=1;
	  break;
	}
      case 6:
	changes[i]=1;
	strcpy(lib.passwd,s);
	break;
      case 7: case 8: case 9: case 10: case 11:
	if(masterlibop)strcpy(lib.libops[i-7],s);
	else {
	  if(strcmp(lib.libops[i-7],s)&&!warned){
	    prompt(OACCNOP);
	    warned=1;
	  }
	}
	break;
      case 12:
	if((recursive=sameas(s,"on"))!=0)prompt(OACCREC);
	break;
      }
    }
  } else {
    prompt(OPCAN);
    adminunlock();
    return;
  }

  memcpy(&library,&lib,sizeof(library));

  update_access(&lib,lib.libnum,changes,lib.passwd,recursive);

  if(!strcmp(libmain,library.fullname)){
    if(library.flags&LBF_LOCKENTR||library.readkey){
      library.flags&=~LBF_LOCKENTR;
      library.readkey=0;
    }
  }

  adminunlock();
  return;
}
