/*****************************************************************************\
 **                                                                         **
 **  FILE:     opdeltree.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  The DELETE operation                                         **
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
 * Revision 1.0  2000/01/06 10:36:59  alexios
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
getdellibname(char *s)
{
  char *i,c;

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
      prompt(ODLTASK);
      inp_get(0);
      cnc_begin();
      i=cnc_word();
      if (!margc) {
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
    if(strlen(i)>sizeof(library.keyname)-1){
      prompt(OCRE2LN,sizeof(library.keyname)-1);
    } else if(strspn(i,FNAMECHARS)!=strlen(i)){
      prompt(OCRECHR);
    } else break;
  }
  strcpy(s,i);
  return 1;
}


static void
delkeywords(struct libidx *l)
{
  struct fileidx f;
  int approved;
  
  for(approved=0;approved<=1;approved++){
    if(filegetfirst(l->libnum,&f,approved)){
      do{
	delfilekeywords(l,&f);
	
      } while(filegetnext(l->libnum,&f));
    }
  }
}



static void
delfiles(struct libidx *l)
{
  struct fileidx f;
  int approved;
  
  for(approved=0;approved<=1;approved++){
    if(filegetfirst(l->libnum,&f,approved)){
      do{
	char fname[512];
	struct stat st;
	bzero(&st,sizeof(st));
	sprintf(fname,"%s/%s",l->dir,f.fname);
	stat(fname,&st);
	libinstfile(l,&f,st.st_size,LIF_DEL);
      } while(filegetnext(l->libnum,&f));
    }
  }
}


static void
deltree(struct libidx *lib)
{
  struct libidx tmp;


  /* First delete keywords */

  prompt(ODLTINF,lib->fullname);
  delkeywords(lib);


  /* Then delete all the files */

  prompt(ODLTINF2);
  delfiles(lib);
  
  prompt(ODLTINF3);


  /* Now recurse, deleting child libraries. We always check for the
     existence of the first child. Every time we recurse, the first
     child will be deleted, pusing the second one up. */

  while(libgetchild(lib->libnum,"",&tmp))deltree(&tmp);


  /* And, finally, delete the library */

  libdelete(lib->libnum);
}



void
op_deltree()
{
  char s[20];
  struct libidx lib;

  for(;;){
    cnc_end();
    if(!getdellibname(s))return;

    if(!libread(s,library.libnum,&lib)){
      prompt(OLDLNEX,s);
      cnc_end();
      continue;
    } else break;
  }

  /* Refuse to delete the main library */
  
  if(sameas(lib.fullname,libmain)){
    prompt(OLDLMAI,libmain);
  }


  deltree(&lib);
}
