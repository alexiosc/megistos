/*****************************************************************************\
 **                                                                         **
 **  FILE:     cache.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1998, Version 0.1                                 **
 **  PURPOSE:  Cache copies of big files residing on slow devices           **
 **  NOTES:    Extremely basic implementation. Will exclusively copy files  **
 **            to the cache directory. Deletes them right after use. This   **
 **            is not a good caching strategy at all, but we can always     **
 **            improve it later if needs be.                                **
 **                                                                         **
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
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 0.2  1998/07/24 10:18:32  alexios
 * File cache for slow devices.
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
#define WANT_FCNTL_H 1
#define WANT_DIRENT_H 1
#define WANT_UTIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk_files.h"


#define mkcachename(s,l,u,f) \
sprintf(s,"%s/%s:%d:%s",mkfname(LIBCACHEDIR),u,l->libnum,f)


static char *convertfname(struct libidx *lib, char *fname)
{
  static char ret[512];
  /*  char buf[256];
  int i;

  for(i=0;fname[i];i++)buf[i]=fname[i]=='/'?':':fname[i];
  buf[i]=0;*/

  mkcachename(ret,lib,thisuseracc.userid,fname);
  return ret;
}


/* Assumes the slow device (if any) has been locked */

static int copyfile(struct libidx *lib, char *source)
{
  char *target=convertfname(lib, source);
  if(fcopy(source,target)){
    unlink(target);
    return 0;
  }
  utime(target,NULL);
  return 1;
}


static char *incache(struct libidx *lib, char *fname)
{
  char *converted=convertfname(lib,fname);
  struct stat st;
  if(!stat(converted,&st)){
    utime(converted,NULL);
    return converted;
  }
  return NULL;
}



static char  *converted_fname;
static int    libnum;

static int cachesel(const struct dirent *d)
{
  char tmp[256], *cp;

  strcpy(tmp,d->d_name);

  /* Skip the username */

  if((cp=strtok(tmp,":"))==NULL)return 0;

  /* Now get and compare the libnum */

  if((cp=strtok(NULL,":"))==NULL)return 0;
  if(atoi(cp)!=libnum)return 0;

  /* Finally get and compare the filename */

  if((cp=strtok(NULL,":"))==NULL)return 0;
  return !strcmp(converted_fname,cp);
}


/* A lateral way of caching: if someone's already copied the file to the cache
   directory, make a hard link to it. That way no space is wasted and no
   locking/copying is required. The last user who unlinks the file frees its
   space too. Whoa, this could actually be what we needed. :-) -- Almost
   (caching isn't persistent as planned, but it saves disk space).  Assumption:
   the file hasn't already been put in the cache by THIS user. */

static char *linkfile(struct libidx *lib, char *fname)
{
  struct dirent  **d=NULL;
  char           source[512];
  static char    target[512];
  int            i,j;

  converted_fname=fname;
  libnum=lib->libnum;
  if((j=scandir(mkfname(LIBCACHEDIR),&d,cachesel,alphasort))==0){
    if(d)free(d);
    return NULL;
  }

  /* Any of these will do, they're all hard links to the same inode anyway. So
     we pick the first one (obviously). */

  sprintf(source,"%s/%s",mkfname(LIBCACHEDIR),d[0]->d_name);
  for(i=0;i<j;i++)free(d[i]);	/* Clean up */
  mkcachename(target,lib,thisuseracc.userid,fname);
  if(link(source, target))return NULL;

  /* Success! */
  return target;
}


char *cachefile(struct libidx *lib, struct fileidx *file)
{
  int  group=getlibgroup(lib);
  char *pathname;

  /* If it's not on a slow device, no need to cache it. */
  if(group<0)return NULL;

  /* Check if it's already in the cache by us */

  if((pathname=incache(lib,file->fname))!=NULL)
    return pathname;		/* It's there, return its filename. */

  /* Now check to see if someone else has requested this file and it's in the
     cache under another user's ID. If it is, make a fresh hard link to it so
     it doesn't get inadvertently unlinked. */

  if((pathname=linkfile(lib,file->fname))!=NULL)
    return pathname;		/* Linked to it, return the new filename. */

  /* Fair enough, it's not in the cache at all. Copy it. */

  /* Step one. Lock the slow device so we have exclusive use. */

  prompt(FILECACH);
  if(!obtainliblock(lib,sldevto,"caching")){
    error_fatal("Timeout waiting for slow library %s.",lib->fullname);
  }
  if(!copyfile(lib,file->fname)){
    error_fatal("Error while copying file to cache.",lib->fullname);
  }
  rmliblock(lib);

  return convertfname(lib,file->fname);
}






















#if 0

static int allsel(const struct dirent *d)
{
  return 1;
}


static int cachesize()		/* Also unlinks expired files */
{
  struct dirent **d=NULL;
  struct stat st;
  char fname[512];
  int i, j, s=0, t=time(NULL)-sldctim*60;

  if((j=scandir(mkfname(LIBCACHEDIR),&d,allsel,alphasort))==0){
    if(d)free(d);
    return 0;
  }

  for(i=0;i<j;i++){
    sprintf(fname,"%s/%s",mkfname(LIBCACHEDIR),d[i]->d_name);
    st.st_size=0;
    stat(fname,&st);
    if((stat(fname,&st)==0) && st.st_mtime<t){
      unlink(fname);
      st.st_size=0;
      stat(fname,&st);
    }
    s+=st.st_size;
    free(d[i]);
  }
  free(d);

  return s;
}
#endif
