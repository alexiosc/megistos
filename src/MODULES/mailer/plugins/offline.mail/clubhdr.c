/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubhdr.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **  PURPOSE:  Miscellaneous club functions                                 **
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
 * Revision 0.6  1999/07/18 21:44:48  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/11 10:13:15  alexios
 * Made club sequence non case-sensitive.
 *
 * Revision 0.3  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
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
#define WANT_TIME_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "offline.mail.h"
#include "../../mailer.h"
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __EMAILCLUBS_UNAMBIGUOUS__
#include "mbk_emailclubs.h"



char defaultclub[32]={0};


struct clubheader clubhdr;
time_t            clubhdrtime=0;


int
hdrselect(const struct dirent *d)
{
  return d->d_name[0]=='h';
}


int
ncsalphasort(const struct dirent * const *A, const struct dirent * const *B)
{
  register char *a=(*A)->d_name;
  register char *b=(*B)->d_name;
  register char ca;
  register char cb;
again:
  ca=toupper(*a);
  cb=toupper(*b);
  if(ca!=cb)return ca-cb;
  if(!*a)return 0;
  a++,b++;
  goto again;
}


int
findclub(char *club)
{
  DIR *dp;
  struct dirent *dir;
  
  if(*club=='/')club++;
  if(!isalpha(*club))return 0;

  if((dp=opendir(mkfname(CLUBHDRDIR)))==NULL){
    error_fatalsys("Unable to open directory %s",mkfname(CLUBHDRDIR));
  }
  while((dir=readdir(dp))!=NULL){
    if(dir->d_name[0]!='h')continue;
    if(sameas(&(dir->d_name[1]),club)){
      strcpy(club,&(dir->d_name[1]));
      closedir(dp);
      return getclubax(&thisuseracc,&(dir->d_name[1]))>CAX_ZERO;
    }
  }
  closedir(dp);
  return 0;
}


int
loadclubhdr(char *club)
{
  FILE *fp;
  char fname[256];
  struct stat st;

  if(*club=='/')club++;
  sprintf(fname,"%s/h%s",mkfname(CLUBHDRDIR),club);
  if(stat(fname,&st)){
    clubhdrtime=0;
    return 0;
  }
  
  if((strcmp(club,clubhdr.club)==0)&&(st.st_ctime==clubhdrtime))return 1;

  clubhdrtime=st.st_ctime;
  if((fp=fopen(fname,"r"))==NULL){
    clubhdrtime=0;
    return 0;
  }

  if(fread(&clubhdr,sizeof(clubhdr),1,fp)!=1){
    fclose(fp);
    clubhdrtime=0;
    return 0;
  }
  fclose(fp);

  return 1;
}


int
getdefaultax(useracc_t *uacc, char *club)
{
  if(!loadclubhdr(club)){/* soup */
    return CAX_ZERO;
  }

  if(key_owns(uacc,clubhdr.keyuplax))return CAX_UPLOAD;
  if(key_owns(uacc,clubhdr.keywriteax))return CAX_WRITE;
  if(key_owns(uacc,clubhdr.keydnlax))return CAX_DNLOAD;
  if(key_owns(uacc,clubhdr.keyreadax))return CAX_READ;

  /* Everyone always has access to the Default club. */
  return sameas(club,defaultclub)?CAX_READ:CAX_ZERO;
}


int
getclubax(useracc_t *uacc, char *club)
{
  char fname[256], clubname[256], access;
  int ax=CAX_ZERO, found=0;
  char tmp[32];
  FILE *fp;

  strcpy(tmp,club);
  if(!loadclubhdr(club)){
    return CAX_ZERO;
  }

  strcpy(club,tmp);

  if(key_owns(uacc,sopkey))return CAX_SYSOP;
  else if(!strcmp(uacc->userid,clubhdr.clubop))return CAX_CLUBOP;

  sprintf(fname,"%s/%s",mkfname(CLUBAXDIR),uacc->userid);
  strcpy(tmp,club);
  if((fp=fopen(fname,"r"))==NULL){
    strcpy(club,tmp);
    return getdefaultax(uacc,club);
  }

  while(!feof(fp)){
    if(fscanf(fp,"%s %c",clubname,&access)!=2)continue;
    if(!strcmp(clubname,club)){
      found=1;
      switch(access){
      case 'Z':
	ax=sameas(club,defaultclub)?CAX_READ:CAX_ZERO;
	break;
      case 'R':
	ax=CAX_READ;
	break;
      case 'D':
	ax=CAX_DNLOAD;
	break;
      case 'W':
	ax=CAX_WRITE;
	break;
      case 'U':
	ax=CAX_UPLOAD;
	break;
      case 'C':
	ax=CAX_COOP;
	break;
      default:
	ax=getdefaultax(uacc,club);
	break;
      }
      break;
    }
  }
  fclose(fp);

  if(!found){
    return getdefaultax(uacc,tmp);
  }
  return ax;
}
