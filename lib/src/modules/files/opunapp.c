/*****************************************************************************\
 **                                                                         **
 **  FILE:     opunapp.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Recursively list unapproved files.                           **
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
 * Revision 1.0  1999/07/18 21:27:24  alexios
 * Initial revision
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


static int
traverseunapp(struct libidx *l)
{
  char c;

  if(read(fileno(stdin),&c,1)&&
     ((c==13)||(c==10)||(c==27)||(c==15)||(c==3)))return 0;
  if(fmt_lastresult==PAUSE_QUIT)return 0;

  if(!islibop(&library))return 1;
  else {
    struct libidx child, otherchild;
    struct fileidx f;
    int res;

    /* Check if there are any unapproved files in the library. We
       don't even mention libraries without unapproved files here. */

    if(filegetfirst(l->libnum,&f,0)){
      struct libidx tmp;
      memcpy(&tmp,&library,sizeof(tmp));
      memcpy(&library,l,sizeof(library));
      res=filelisting(0);	/* Show the library's unapproved files */
      memcpy(&library,&tmp,sizeof(library));
      if(!res)return 0;
      inp_nonblock();		/* filelisting() restores blocking mode */
    }

    res=libgetchild(l->libnum,"",&otherchild);
    while(res){
      memcpy(&child,&otherchild,sizeof(child));
      res=libgetchild(l->libnum,child.keyname,&otherchild);
      if(!traverseunapp(&child))return 0;
    }
  }

  return 1;
}


void
op_listunapp()
{
  inp_nonblock();
  traverseunapp(&library);
  inp_block();
}
