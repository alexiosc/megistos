/*****************************************************************************\
 **                                                                         **
 **  FILE:     list.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  Listings of libraries                                        **
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
 * Numerous changes and additions.
 *
 * Revision 0.4  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Slight changes to account for the new database interface.
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
#define WANT_DIRENT_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk_files.h"
#include "typhoon.h"


static int
traverselibtree(struct libidx *l, char *br)
{
  char c;

  if(read(fileno(stdin),&c,1)&&
     ((c==13)||(c==10)||(c==27)||(c==15)||(c==3)))return 0;
  if(fmt_lastresult==PAUSE_QUIT)return 0;

  if(!getlibaccess(l,ACC_VISIBLE))return 1;
  else {
    char branches[256];
    int i, res;
    struct libidx child, otherchild;

    branches[0]=0;
    for(i=0;br[i];i++){
      if(br[i+1]==0&&br[i]=='1')strcat(branches,msg_get(LITRBR));
      else strcat(branches,msg_get(LITRVR+br[i]-'1'));
      if(br[i]=='2')br[i]='3';
    }

    prompt(LITRTB,branches,leafname(l->fullname),l->descr);

    res=libgetchild(l->libnum,"",&otherchild);
    while(res){
      char s[256];
      memcpy(&child,&otherchild,sizeof(child));
      res=libgetchild(l->libnum,child.keyname,&otherchild);
      strcpy(s,br);
      strcat(s,res?"1":"2");
      if(!traverselibtree(&child,s))return 0;
    }
  }
  return 1;
}


void
libtree()
{
  struct libidx l;

  prompt(LITRHD);

  if(!libread(libmain,0,&l)){
    error_fatal("Main library (\"%s\") not found!",libmain);
  }

  inp_nonblock();
  if(traverselibtree(&l,""))prompt(LITRFT);
  inp_block();
}


int
listsublibs()
{
  struct libidx l;
  int res;
  char gt[20];

  prompt(LIBLSTH);

  /* Print the main library */
  if(!libread(libmain,0,&l)){
    error_fatal("Unable to find main lib!");
  } else prompt(LIBLSTL,"/",l.numfiles,l.numbytes>>10,l.descr);
  
  /* Print the parent library, if any */
  if(nesting(library.fullname)){
    if(!libreadnum(library.parent,&l)){
      error_fatal("Unable to get parent lib, libnum=%d",
	    library.parent);
    }
    prompt(LIBLSTP,l.numfiles,l.numbytes>>10,leafname(l.fullname));
  }

  gt[0]=0;

  do{
    res=libgetchild(library.libnum, gt, &l);
    if(res){
      if(getlibaccess(&l,ACC_VISIBLE))
	prompt(LIBLSTL,leafname(l.fullname),l.numfiles,l.numbytes>>10,l.descr);
    }
    if(fmt_lastresult==PAUSE_QUIT)break;
    strcpy(gt,l.keyname);
  }while(res);

  prompt(LIBLSTF);

  return fmt_lastresult!=PAUSE_QUIT;
}


static int listsel(const struct dirent *d)
{
  return (showhid||d->d_name[0]!='.') &&
    strcmp(d->d_name,".") && strcmp(d->d_name,"..");
}


static int
osfiledir()
{
  struct stat st;
  int res=0;
  char fname[256], *cp, *s=strdup(othrfls);

  sprintf(fname,"%s/%s",library.dir,filelst);
  if(!stat(fname,&st)){
    res=1;
    prompt(FLRHDR);
    fmt_lastresult=PAUSE_CONTINUE;
    out_printlongfile(fname);
    if(fmt_lastresult==PAUSE_QUIT)prompt(FLCAN);
    else prompt(FLRFTR);
  } else {
    cp=strtok(s," \n\r\t,");
    while(cp){
      if(!strlen(cp))continue;
      sprintf(fname,"%s/%s",library.dir,cp);
      if(!stat(fname,&st)){
	prompt(FLRHDR);
	fmt_lastresult=PAUSE_CONTINUE;
	out_printlongfile(fname);
	if(fmt_lastresult==PAUSE_QUIT)prompt(FLCAN);
	else prompt(FLRFTR);
	res=1;
	break;
      }
      cp=strtok(NULL," \n\r\t");
    }
  }
  free(s);
  return res;
}


int
osdirlisting()
{
  struct dirent  **d=NULL;
  int              i,j,files=0,bytes=0;
  struct stat      st;
  char             fname[512],c;
  struct tm        *tm;

  if(library.flags&LBF_FILELIST)if(osfiledir())
    return fmt_lastresult!=PAUSE_QUIT;

  if((j=scandir(library.dir,&d,listsel,alphasort))==0){
    if(d)free(d);
    prompt(FLEMPT);		/* No files in library */
    return 1;
  }

  prompt(FLOHDR);
  inp_nonblock();
  for(i=0;i<j;free(d[i]),i++){
    bzero(&st,sizeof(st));
    sprintf(fname,"%s/%s",library.dir,d[i]->d_name);
    if(stat(fname,&st))continue;
    tm=localtime(&st.st_mtime);
    files++;
    bytes+=st.st_size;
    prompt(FLOLST,
	   st.st_size,
	   strdate(makedate(tm->tm_mday,tm->tm_mon+1,1900+tm->tm_year)),
	   strtime(maketime(tm->tm_hour,tm->tm_min,tm->tm_sec),1),
	   d[i]->d_name);

    if(read(fileno(stdin),&c,1)&&
       ((c==13)||(c==10)||(c==27)||(c==15)||(c==3))){
      fmt_lastresult=PAUSE_QUIT;
      break;
    }
    if(fmt_lastresult==PAUSE_QUIT)break;
  }
  if(fmt_lastresult==PAUSE_QUIT)prompt(FLCAN);
  else prompt(FLOFTR,files,bytes);

  free(d);
  inp_block();

  return fmt_lastresult!=PAUSE_QUIT;
}


static int
normallisting(int approved)
{
  int i, numfiles=0, numbytes=0;
  struct fileidx f;
  char c;

  i=filegetfirst(library.libnum,&f,approved);
  if(!i || f.flibnum!=library.libnum){
    prompt(approved?FLEMPT:FLNUNA);
    return 1;
  }
  prompt(approved?FLHDR:FLHDRU);
  inp_nonblock();

  while(i){
    char fname[256];
    struct stat st;

    if(read(fileno(stdin),&c,1)&&
       ((c==13)||(c==10)||(c==27)||(c==15)||(c==3)))break;
    if(fmt_lastresult==PAUSE_QUIT)break;

    if(f.approved!=approved)continue;
    if(f.flibnum!=library.libnum)break;
    sprintf(fname,"%s/%s",library.dir,f.fname);
    st.st_size=0;
    stat(fname,&st);
    prompt(FLLST,f.fname,st.st_size,f.uploader,f.summary);
    numfiles++;
    numbytes+=st.st_size;

    i=filegetnext(library.libnum,&f);
  }
  if(i)prompt(FLCAN);
  else prompt(FLFTR,numfiles,numbytes);
  inp_block();

  return fmt_lastresult!=PAUSE_QUIT;
}


int
filelisting(int approved)
{
  if(library.flags&LBF_OSDIR){
    if(!approved){
      prompt(OLUNOS,library.fullname);
      cnc_end();
      return 1;
    } else return osdirlisting();
  } else return normallisting(approved);
}


void
listapproved()
{
  filelisting(1);
}
