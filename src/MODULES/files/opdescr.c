/*****************************************************************************\
 **                                                                         **
 **  FILE:     opdescr.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Edit file descriptions.                                      **
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


static char *
getfilenames(int pr)
{
  static char fn[256];

  for(;;){
    if(morcnc()){
      strcpy(fn,cncword());
    } else {
      prompt(pr);
      getinput(sizeof(fn)-1);
      strcpy(fn,input);
    }

    if(isX(fn))return NULL;
    else if(!strlen(fn)){
      endcnc();
      continue;
    } else if(!strcmp(fn,"?")){
      listapproved();
      endcnc();
      continue;
    } else break;
  }

  return fn;
}


void
op_descr()
{
  char *spec;
  int numfiles;
  struct filerec *fr;
  struct fileidx f;
  int i;

  if(library.flags&LBF_OSDIR){
    prompt(ODESOS);
    endcnc();
    return;
  }

  if((spec=getfilenames(ODESASK))==NULL)return;
  numfiles=expandspec(spec,1);
  if(numfiles==0){
    prompt(ODESERR);
    endcnc();
    return;
  }

  fr=firstfile();
  i=1;
  while(fr){
    if(!fileread(library.libnum,fr->fname,1,&f))
      if(!fileread(library.libnum,fr->fname,0,&f)) continue;
    
    prompt(ODESFIL,f.fname,i,numfiles,f.summary);
    endcnc();
    getinput(sizeof(f.summary)-1);
    rstrin();
    if(strlen(input)){
      if(isX(input))break;

      bzero(f.summary,sizeof(f.summary));
      strncpy(f.summary,input,sizeof(f.summary));
      fileupdate(&f);
    }
      
    i++;
    fr=nextfile();
  }

  reset_filearray();
}


static void
editdescr(struct fileidx *f)
{
  int fd;
  char fname[256];
  struct stat st;
  
  sprintf(fname,TMPDIR"/des-%05d",getpid());

  if((fd=open(fname,O_WRONLY|O_CREAT,0600))<0){
    fatalsys("Unable to open() %s for writing.",fname);
  }
  write(fd,f->description,strlen(f->description));
  close(fd);
  
  if(editor(fname,deslen)||stat(fname,&st))return;
  
  stat(fname,&st);
  bzero(f->description,sizeof(f->description));
  if((fd=open(fname,O_RDONLY))<0){
    fatalsys("Unable to open() %s for reading.",fname);
  }
  read(fd,f->description,min(st.st_size,sizeof(f->description)));
  f->descrlen=strlen(f->description)+1;
  close(fd);
  unlink(fname);
  fileupdate(f);
  return;
}


void
op_long()
{
  char *spec;
  int numfiles;
  struct filerec *fr;
  struct fileidx f;
  int i;

  if(library.flags&LBF_OSDIR){
    prompt(OLONOS);
    endcnc();
    return;
  }

  if((spec=getfilenames(OLONASK))==NULL)return;
  numfiles=expandspec(spec,1);
  if(numfiles==0){
    prompt(OLONERR);
    endcnc();
    return;
  }

  fr=firstfile();
  i=1;
  while(fr){
    if(!fileread(library.libnum,fr->fname,1,&f))
      if(!fileread(library.libnum,fr->fname,0,&f)) continue;

    for(;;){
      int yes,res;
      prompt(OLONINF,i,numfiles);
      fileinfo(&library,&f);
      setinputflags(INF_HELP);
      res=getbool(&yes,OLONCONT,0,OLONCND,0);
      setinputflags(INF_NORMAL);
      if(res<0)continue;
      if(res==0)goto done;
      if(yes)editdescr(&f);
      break;
    }
      
    i++;
    fr=nextfile();
  }
  
 done:
  reset_filearray();
}
