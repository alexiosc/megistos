/*****************************************************************************\
 **                                                                         **
 **  FILE:     opdisapp.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Remove approval from files                                   **
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


static void
disapprovekeywords(struct libidx *l, struct fileidx *f)
{
  struct filekey k;
  int    morekeys, keys=0;
  char   keystg[8192];
      
  keystg[0]=0;
  morekeys=keyfilefirst(l->libnum,f->fname,1,&k);
  while(morekeys){
    char tmp[32];
    keys++;
    sprintf(tmp,"%s ",k.keyword);
    strcat(keystg,tmp);
    morekeys=keyfilenext(l->libnum,f->fname,1,&k);
  }
  if(keys){
    char k[8192],*cp;
    strcpy(k,keystg);
    for(cp=strtok(k," ");cp;cp=strtok(NULL," ")){
      deletekeyword(l->libnum,f->fname,1,cp);
    }
    addkeywords(keystg,0,f);
  }
}


static int
disapprovefile(struct libidx *l, char *fname)
{
  struct fileidx f;
  char c;

  /* Read the file and ask whether the user wants it approved or not */

  if(!fileread(l->libnum,fname,1,&f)) return 1;

  for(;;){
    int res;
    fileinfo(l,&f);
  nohelp:
    inp_setflags(INF_HELP);
    res=get_menu(&c,0,0,ODISASK,ODISERR,"YND",0,0);
    inp_clearflags(INF_HELP);
    if(res<0)continue;
    else if(!res)return 0;

    if(c=='N')return 1;
    else if(c=='D'){
      struct libidx tmp;
      memcpy(&tmp,&library,sizeof(library));
      download(fname);
      memcpy(&library,&tmp,sizeof(library));
      goto nohelp;
    } else if(c=='Y')break;
  }


  /* Ok, let's remove the file approval. First re-read the file. */

  if(!fileread(l->libnum,fname,1,&f))return 1;
  filedelete(&f); /* This is needed to properly update the approved field */
  f.approved=0;
  strcpy(f.approved_by,thisuseracc.userid);
  filecreate(&f);
  prompt(ODISOK);


  /* Now we have to approve its keywords, one by one. */

  disapprovekeywords(l,&f);


  /* Finally, update the library */

  {
    struct libidx lib;
    char fn[1024];
    struct stat st;
    if(libreadnum(l->libnum,&lib)){
      sprintf(fn,"%s/%s",lib.dir,fname);
      if(!stat(fn,&st)){
	lib.numbytes-=st.st_size;
	lib.bytesunapp+=st.st_size;
      }
      lib.numfiles--;
      lib.numunapp++;

      libupdate(&lib);
    }
  }

  return 1;
}


static char *
getfilename()
{
  static char fn[256];

  for(;;){
    if(cnc_more()){
      strcpy(fn,cnc_word());
    } else {
      prompt(ODISQ);
      inp_get(sizeof(fn)-1);
      strcpy(fn,inp_buffer);
    }

    if(inp_isX(fn))return NULL;
    else if(!strlen(fn)) continue;

    if(!fileexists(library.libnum,fn,1)){
      cnc_end();
      prompt(ODISR);
      continue;
    } else break;
  }
  return fn;
}


void
op_disapprove()
{
  char *fn=getfilename();
  if(fn==NULL)return;
  disapprovefile(&library,fn);
}
