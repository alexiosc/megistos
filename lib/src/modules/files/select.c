/*****************************************************************************\
 **                                                                         **
 **  FILE:     select.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  Selecting libraries                                          **
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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:29:45  alexios
 * Various minor changes to accommodate for new function
 * semantics.
 *
 * Revision 0.4  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Minor changes for better handling of concatenated commands.
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


inline void
enterlastlib()
{
  if(libexistsnum(thisuseronl.lastlib))enterlib(thisuseronl.lastlib,0);
  else entermainlib();
}


int
enterlib(int libnum, int quiet)
{
  if(!libreadnum(libnum,&library))return 0;
  thisuseronl.lastlib=library.libnum;
  locklib();
  if((!quiet) && !(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
    libinfo();
  }
  return 1;
}


void
entermainlib()
{
  if(!libread(libmain,0,&library)){
    error_fatal("Main library (\"%s\") not found!",libmain);
  }
  thisuseronl.lastlib=library.libnum;
  locklib();
  libinfo();
}


int
getsellibname(struct libidx *l)
{
  char *i,c;
  int helped=0;
  struct libidx lib;

  for(;;){
    fmt_lastresult=0;
    if((c=cnc_more())!=0){
      if(sameas(cnc_nxtcmd,"X"))return 0;
      if(sameas(cnc_nxtcmd,"?")){
	listsublibs();
	cnc_end();
	continue;
      }
      i=cnc_word();
    } else {
      if(!helped){
	prompt(SELHELP);
	helped=1;
      }
      prompt(SELLIB);
      inp_get(0);
      cnc_begin();
      i=cnc_word();
      if(!margc){
	cnc_end();
	continue;
      }
      if(inp_isX(margv[0])){
	return 0;
      }
      if(sameas(margv[0],"?")){
	listsublibs();
	cnc_end();
	continue;
      }
    }
    if(sameas(i,"..")){
      if(nesting(library.fullname)==0){
	prompt(SELNPR);
	cnc_end();
	continue;
      } else return 2;
    } else if(sameas(i,"/")||sameas(i,"\\")){
      if(!libread(libmain,0,&lib)){
	error_fatal("Unable to find main library!");
      } else goto enter;
    } else {
      if(!nesting(i)){
	if(!libread(i,library.libnum,&lib)||
	   !getlibaccess(&lib,ACC_VISIBLE)){
	  prompt(SELERR,i,leafname(library.fullname));
	  cnc_end();
	  continue;
	} else goto enter;
      } else {
	char s[256];
	char *cp;

	strcpy(s,i);
	if(!libread(libmain,0,&lib)){
	  error_fatal("Unable to find main library!");
	}
	cp=strtok(i,"/\\");
	while(cp){
	  if(!strlen(cp))continue;
	  if(!libread(cp,lib.libnum,&lib)||
	     !getlibaccess(&lib,ACC_VISIBLE)){
	    prompt(SELERR,cp,leafname(lib.fullname));
	    cnc_end();
	    goto outerloop;
	  }
	  cp=strtok(NULL,"/\\");
	}
      }
    }
    break;
  outerloop:
  }

enter:
  if(!getlibaccess(&lib,ACC_ENTER)){
    cnc_end();
    return 0;
  }

  memcpy(l,&lib,sizeof(lib));

  return 1;
}


void
selectlib()
{
  struct libidx l;
  switch(getsellibname(&l)){
  case 1:
    memcpy(&library,&l,sizeof(library));
    thisuseronl.lastlib=library.libnum;
    locklib();
    libinfo();
  case 0:
    return;
  case 2:
    /*    memcpy(&library,&l,sizeof(library)); */
    enterlib(library.parent,0);
  }
}
