/*****************************************************************************\
 **                                                                         **
 **  FILE:     chanusr.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, channel user handling functions             **
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
 * Revision 1.2  2001/04/16 21:56:33  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.7  1999/07/18 21:48:36  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.6  1998/12/27 16:10:27  alexios
 * Added autoconf support. Other slight fixes.
 *
 * Revision 0.5  1998/08/14 11:51:24  alexios
 * Removed the "DONE" markers from updated functions.
 *
 * Revision 0.4  1998/08/14 11:45:25  alexios
 * Rewrote channel engine to use directories for channels and
 * files for the header and user records. This makes sure no
 * strange filing bugs show up like before.
 *
 * Revision 0.3  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "telecon.h"
#include "mbk_telecon.h"


struct chanusr *
makechanusr(char *userid, int access)
{
  static struct chanusr usr;
  memset(&usr,0,sizeof(usr));
  strcpy(usr.userid,userid);

  usr.flags=access;

  usr_insys(userid,0);
  if(strcmp(userid,othruseracc.userid)){
    error_fatal("Unable to read account for user %s",userid);
  }

  usr.sex=othruseracc.sex;
  if(thisuseronl.flags&OLF_TLCUNLIST)usr.flags|=CUF_UNLISTED;
    
  return &usr;
}


struct chanusr *
readchanusr(char *channel, char *userid)
{
  FILE *fp;
  char fname[256];
  struct stat st;
  static struct chanusr retval;
  
  /* Locate channel user file, return NULL if doesn't exist */

  sprintf(fname,"%s/%s/%s-",TELEDIR,mkchfn(channel),userid);
  if(stat(fname,&st)){
    sprintf(fname,"%s/%s/%s+",TELEDIR,mkchfn(channel),userid);
    if(stat(fname,&st))return NULL;
  }

  if((fp=fopen(fname,"r"))==NULL){
    error_fatalsys("Unable to open existing channel user file %s",fname);
  }

  if(fread(&retval,sizeof(struct chanusr),1,fp)!=1){
    error_fatalsys("Unable to write to channel user file %s",fname);
  }

  fclose(fp);
  
  /* Delete leftover channel files for users who aren't on-line now */

  if(!usr_insys(userid,0)){
    unlink(fname);
    return NULL;
  }

  return &retval;
}


int
writechanusr(char *channel, struct chanusr *wusr)
{
  FILE *fp;
  char fname[256];

  /* Unlink old channel user file, if available */

  sprintf(fname,"%s/%s/%s%s",TELEDIR,mkchfn(channel),wusr->userid,
	  wusr->flags&CUF_PRESENT?"-":"+");
  unlink(fname);


  /* Create the new one */

  sprintf(fname,"%s/%s/%s%s",TELEDIR,mkchfn(channel),wusr->userid,
	  wusr->flags&CUF_PRESENT?"+":"-");
  if((fp=fopen(fname,"w"))==NULL){
    error_fatalsys("Unable to open channel user file %s",fname);
  }

  if(fwrite(wusr,sizeof(struct chanusr),1,fp)!=1){
    error_fatalsys("Unable to write to channel user file %s",fname);
  }

  fclose(fp);

  return 2;
}


void
chanusrflags(char *userid, char *channel, int flagson, int flagsoff)
{
  struct chanusr *usr;

  if((usr=readchanusr(channel,userid))==NULL)return;

  usr->flags&=~flagsoff;
  usr->flags|=flagson;

  writechanusr(channel,usr);
}
