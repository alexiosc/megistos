/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.graffiti.c                                           **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Graffiti wall plugin, download                               **
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
 * Revision 0.6  1999/07/18 21:44:25  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 15:47:33  alexios
 * Added autoconf support. Migrated to the new locking functions.
 *
 * Revision 0.4  1998/08/14 11:36:01  alexios
 * Auto-translated from user's character set to the internal
 * BBS one.
 *
 * Revision 0.3  1998/07/24 10:20:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:55  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:54:33  alexios
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
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "offline.graffiti.h"
#include "../../mailer.h"
#define NOCOLORS
#include "../../../graffiti/graffiti.h"
#include "mbk_offline.graffiti.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __GRAFFITI_UNAMBIGUOUS__
#include "mbk_graffiti.h"


static char *
zonk(char *s, int len)
{
  int i;
  for(i=len-1;i&&((s[i]==' ')||(s[i]==0));i--)s[i]=0;
  for(i=0;s[i]==' ';i++);
  return &s[i];
}


int
checkfile()
{
  struct stat    buf;
  FILE           *fp;
  struct wallmsg header;

  if(stat(WALLFILE,&buf)){
    if((lock_wait(WALLLOCK,5))==LKR_TIMEOUT){
      error_log("Timed out waiting for lock %s",WALLLOCK);
      return 0;
    }
    lock_place(WALLLOCK,"creating");
    
    if((fp=fopen(WALLFILE,"w"))==NULL){
      error_fatalsys("Unable to create file %s",WALLFILE);
    }
    memset(&header,0,sizeof(header));
    strcpy(header.userid,SYSOP);
    sprintf(header.message,"%d",0);
    fwrite(&header,sizeof(header),1,fp);

    fclose(fp);
    chmod(WALLFILE,0666);
    lock_rm(WALLLOCK);
  }
  return 1;
}


int
drawmessage(char *text)
{
  FILE           *fp, *out;
  char           fname[256];
  char           userid[24];
  int            numlines=0, i;
  struct wallmsg wallmsg;

  if(!checkfile()){
    error_fatal("Unable to ensure existence of graffiti wall file.");
  }

  if((lock_wait(WALLLOCK,5))==LKR_TIMEOUT){
    error_fatal("Timed out waiting for lock %s",WALLLOCK);
  }

  lock_place(WALLLOCK,"checking");
  
  if((fp=fopen(WALLFILE,"r"))==NULL){
    lock_rm(WALLLOCK);
    error_fatalsys("Unable to open file %s",WALLFILE);
  }
  
  if(!fread(&wallmsg,sizeof(wallmsg),1,fp)){
    lock_rm(WALLLOCK);
    error_fatalsys("Unable to read file %s",WALLFILE);
  }
  
  numlines=atoi(wallmsg.message);
  strcpy(userid,wallmsg.userid);
  if(!key_owns(&thisuseracc,ovrkey)
     && sameas(wallmsg.userid,thisuseracc.userid) && numlines>=maxmsgs){
    lock_rm(WALLLOCK);
    return 0;
  }
  
  fclose(fp);
  lock_rm(WALLLOCK);
  
  lock_place(WALLLOCK,"writing");

  if((fp=fopen(WALLFILE,"r"))==NULL){
    lock_rm(WALLLOCK);
    error_fatalsys("Unable to open file %s",WALLFILE);
  }
  
  fread(&wallmsg,sizeof(wallmsg),1,fp);

  sprintf(fname,TMPDIR"/graffiti%05d",getpid());
  if((out=fopen(fname,"w"))==NULL){
    lock_rm(WALLLOCK);
    error_fatalsys("Unable to create temporary file %s",fname);
  }
  if(sameas(thisuseracc.userid,userid))numlines++;
  else numlines=1;
  
  memset(&wallmsg,0,sizeof(wallmsg));
  strcpy(wallmsg.userid,thisuseracc.userid);
  sprintf(wallmsg.message,"%d",numlines);
  fwrite(&wallmsg,sizeof(wallmsg),1,out);

  strcpy(wallmsg.message,text);
  fwrite(&wallmsg,sizeof(wallmsg),1,out);

  for(i=0;(i<(maxsize-1))&&(!feof(fp));){
    if(fread(&wallmsg,sizeof(wallmsg),1,fp) && wallmsg.userid[0]){
      i++;
      fwrite(&wallmsg,sizeof(wallmsg),1,out);
    }
  }
  fclose(out);
  fclose(fp);

  if(fcopy(fname,WALLFILE)){
    lock_rm(WALLLOCK);
    error_fatal("Unable to fcopy() %s to %s",fname,WALLFILE);
    return 0;
  }
  unlink(fname);
  lock_rm(WALLLOCK);
  return 1;
}



static int
process(char *fname)
{
  int numlines=0, numsuccessful=0;

  FILE *fp=fopen(fname,"r");
  if(fp==NULL){
    error_fatalsys("Unable to open file %s",fname);
  }

  prompt(ULWRH);

  while(!feof(fp)){
    char line[1024], *cp;
    if(!fgets(line,sizeof(line),fp))break;
    if((cp=strchr(line,'\n'))!=NULL)*cp=0;
    if((cp=strchr(line,'\r'))!=NULL)*cp=0;
    cp=zonk(line,sizeof(line));
    xlate_in(cp);
    if(*cp==':'){
      numlines++;
      numsuccessful+=drawmessage(cp+1);
    }
  }

  fclose(fp);

  if(!numlines){
    prompt(ULWMT);
    return 0;
  } else if(numsuccessful==numlines){
    char tmp[1024];
    strcpy(tmp,msg_getunit(WRTSNG,numsuccessful));
    prompt(ULNWR,tmp,numsuccessful,numlines,msg_getunit(LINSNG,numlines));
    return 0;
  } else {
    char tmp[1024];
    strcpy(tmp,msg_getunit(WRTSNG,numlines));
    prompt(ULWRT,tmp,numlines,msg_getunit(LINSNG,numlines));
  }
  return 1;
}


int
ogupload()
{
  struct reqidx idx;
  int res, stop=0;

  openreqdb();
  res=getfirstreq(&idx);

  for(res=getfirstreq(&idx);res;res=getnextreq(&idx)){
    if(idx.priority!=RQP_CTLMSG)continue;

    if(!sameas(zonk(idx.reqfname,sizeof(idx.reqfname)),"WALL"))continue;
  
    stop=!process(idx.dosfname);

    /* Remove the current request from the database */

    unlink(idx.dosfname);
    if(!rmrequest(&idx)){
      error_fatal("Unable to remove request %d from the database.",
	    idx.reqnum);
    }

    if(stop)break;
  }

  return 0;
}
