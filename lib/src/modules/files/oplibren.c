/*****************************************************************************\
 **                                                                         **
 **  FILE:     oplibren.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Rename a library.                                            **
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
 * Revision 1.1  2001/04/16 14:56:00  alexios
 * Initial revision
 *
 * Revision 1.0  1999/07/18 21:27:24  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
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


int
listpeerlibs()
{
  struct libidx l;
  int p;
  int res;
  char gt[20];

  prompt(LIBLSTH);

  if(!libreadnum(library.parent,&l)){
    fatal("Unable to get parent lib, libnum=%d",
	  library.parent);
  }
  p=l.parent;


  gt[0]=0;

  do{
    res=libgetchild(library.parent, gt, &l);
    if(res){
      if(getlibaccess(&l,ACC_VISIBLE))
	prompt(LIBLSTL,leafname(l.fullname),l.numfiles,l.numbytes>>10,l.descr);
    }
    if(lastresult==PAUSE_QUIT)break;
    strcpy(gt,l.keyname);
  }while(res);

  prompt(LIBLSTF);

  return lastresult!=PAUSE_QUIT;
}


static int
getnewlibname(char *s)
{
  char *i,c;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      if(sameas(nxtcmd,"?")){
	listsublibs();
	endcnc();
	continue;
      }
      i=cncword();
    } else {
      prompt(OLRNASK);
      getinput(0);
      bgncnc();
      i=cncword();
      if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return 0;
      }
      if(sameas(margv[0],"?")){
	listpeerlibs();
	endcnc();
	continue;
      }
    }
    if(strlen(i)>sizeof(library.keyname)-1){
      prompt(OCRE2LN,sizeof(library.keyname)-1);
    } else if(strspn(i,FNAMECHARS)!=strlen(i)){
      prompt(OCRECHR);
    } else break;
  }
  strcpy(s,i);
  return 1;
}


void
op_libren()
{
  char s[256];

  print("not implemented\n");
  return;

  /* Refuse to rename the main library */

  if(!nesting(library.fullname)){
    prompt(OLRNNMN);
    endcnc();
    return;
  }

  for(;;){
    if(!getnewlibname(s))return;
    
    if(libexists(s,library.parent)){
      prompt(OLRNERR);
      endcnc();
      continue;
    } else break;
  }

  /* Rename the library */

}
