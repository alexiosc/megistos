/*****************************************************************************\
 **                                                                         **
 **  FILE:     opmove.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Move files from one library to another.                      **
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


static char *
getfilenames(int pr)
{
  static char fn[256];

  for(;;){
    if(cnc_more()){
      strcpy(fn,cnc_word());
    } else {
      prompt(pr);
      inp_get(sizeof(fn)-1);
      strcpy(fn,inp_buffer);
    }

    if(inp_isX(fn))return NULL;
    else if(!strlen(fn)){
      cnc_end();
      continue;
    } else if(!strcmp(fn,"?")){
      listapproved();
      cnc_end();
      continue;
    } else break;
  }

  return fn;
}


static int
gettargetlibname(struct libidx *l)
{
  char *i,c;
  struct libidx lib;

  for(;;){
    fmt_lastresult=0;
    if((c=cnc_more())!=0){
      if(sameas(cnc_nxtcmd,"X"))return 0;
      if(sameas(cnc_nxtcmd,"?")){
	libtree();
	cnc_end();
	continue;
      }
      i=cnc_word();
    } else {
      prompt(OCPYTRG);
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
	libtree();
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
	  prompt(OCPYTR2);
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
	    prompt(OCPYTR2);
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
  memcpy(l,&lib,sizeof(lib));

  return 1;
}


static void
copyfilekeywords(struct libidx *l, struct fileidx *f, struct fileidx *ft)
{
  struct filekey k;
  int    morekeys, keys=0;
  char   keystg[8192];

  keystg[0]=0;
  morekeys=keyfilefirst(l->libnum,f->fname,f->approved,&k);
  while(morekeys){
    char tmp[32];
    keys++;
    sprintf(tmp,"%s ",k.keyword);
    strcat(keystg,tmp);
    morekeys=keyfilenext(l->libnum,f->fname,f->approved,&k);
  }
  if(keys){
    addkeywords(keystg,ft->approved,ft);
  }
}


static
int docopy(struct fileidx *f, struct libidx *target)
{
  char fname[512], fname2[512];
  struct stat st;
  struct fileidx tf;

  sprintf(fname,"%s/%s",library.dir,f->fname);
  stat(fname,&st);

  /* Check if the target library has enough space */

  if(library.numfiles>library.filelimit){
    prompt(OCPYFAIL);
    cnc_end();
    return 0;
  }
  if(library.numbytes+st.st_size>=(library.libsizelimit<<20)){
    prompt(OCPYFAIL);
    cnc_end();
    return 0;
  }


  /* Check if the file already exists in the target lib */

  if(fileexists(target->libnum,f->fname,0)||
     fileexists(target->libnum,f->fname,1)){
    prompt(OCPYEXT,f->fname);
    return 1;
  }


  /* Physically Copy the file (try a hard link first) */

  sprintf(fname2,"%s/%s",target->dir,f->fname);
  if(link(fname,fname2))fcopy(fname,fname2);


  /* Add the database entry for the target file */
  
  memcpy(&tf,f,sizeof(tf));
  tf.flibnum=target->libnum;
  filecreate(&tf);
  libinstfile(target,&tf,st.st_size,LIF_ADD);

  /* Add keywords */

  copyfilekeywords(&library,f,&tf);

  prompt(OCPYOK,f->fname);

  return 1;
}


void
op_copy()
{
  char *spec;
  int numfiles;
  struct filerec *fr;
  struct fileidx f;
  int i, all=0;
  char c;
  struct libidx target;

  if((spec=getfilenames(OCPYASK))==NULL)return;
  numfiles=expandspec(spec,1);
  if(numfiles==0){
    prompt(OCPYERR);
    cnc_end();
    return;
  } else if(numfiles>1){
    prompt(OCPYNUM,numfiles);
  }

  for(;;){
    switch(gettargetlibname(&target)){
    case 0:
      return;
    case 2:
      if(!libreadnum(library.parent,&target))return;
    }

    if(target.libnum==library.libnum){
      cnc_end();
      prompt(OCPYTR1);
      continue;
    }

    if(target.flags&LBF_READONLY){
      prompt(OCPYTR4);
      cnc_end();
      continue;
    }

    break;
  }

  fr=firstfile();
  i=1;
  while(fr){
    if(!fileread(library.libnum,fr->fname,1,&f))
      if(!fileread(library.libnum,fr->fname,0,&f)) continue;

    for(;;){
      int res;

      if(!all){
	prompt(OCPYINF,i,numfiles);
	fileinfo(&library,&f);

	inp_setflags(INF_HELP);
	res=get_menu(&c,0,0,OCPYMNU,0,"YNA",0,0);
	inp_clearflags(INF_HELP);
	if(res<0)continue;
	if(res==0)goto done;
	if(c=='A'){
	  all=1;
	  c='Y';
	}
      } else c='Y';

      if(c=='Y'){
	res=docopy(&f,&target);
	if(!res)goto done;
      }
      break;
    }

    i++;
    fr=nextfile();
  }

done:
  reset_filearray();
}
