/*****************************************************************************\
 **                                                                         **
 **  FILE:     database.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **            B, August 1996, Version 0.9                                  **
 **  PURPOSE:  Functions to handle the mail database.                       **
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
 * Revision 1.4  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
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
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "typhoon.h"
#include "email.h"
#include "ecdbase.h"


static char dbclubname[256]=EMAILCLUBNAME;
static char dbclubdir[256]=EMAILDIR;
static char dbcur[256]="";
static int  dbopen=0;
static int  clubdbid=-1;


int
getmsgheader(int msgno,struct message *msg)
{
  char lock[256], fname[256], tmp[256];
  FILE *fp;

  sprintf(tmp,"%d",msgno);
  sprintf(lock,MESSAGELOCK,dbclubname,tmp);
  if((lock_wait(lock,20))==LKR_TIMEOUT)return BSE_LOCK;
  lock_place(lock,"reading");

  sprintf(fname,"%s/"MESSAGEFILE,mkfname(dbclubdir),msgno);
  if((fp=fopen(fname,"r"))==NULL){
    lock_rm(lock);
    return BSE_OPEN;
  } else if(fread(msg,sizeof(struct message),1,fp)!=1){
    fclose(fp);
    lock_rm(lock);
    return BSE_READ;
  }
  fclose(fp);
  lock_rm(lock);
  return BSE_FOUND;
}


int
writemsgheader(struct message *msg)
{
  char lock[256], fname[256], tmp[256];
  FILE *fp;

  sprintf(tmp,"%d",msg->msgno);
  sprintf(lock,MESSAGELOCK,dbclubname,tmp);
  if((lock_wait(lock,20))==LKR_TIMEOUT)return BSE_LOCK;
  lock_place(lock,"writing");

  sprintf(fname,"%s/"MESSAGEFILE,mkfname(dbclubdir),msg->msgno);
  if((fp=fopen(fname,"r+"))==NULL){
    lock_rm(lock);
    return BSE_OPEN;
  } else if(fwrite(msg,sizeof(struct message),1,fp)!=1){
    fclose(fp);
    lock_rm(lock);
    return BSE_WRITE;
  }
  fclose(fp);
  lock_rm(lock);
  return BSE_FOUND;
}


void
dbrm(struct message *msg)
{
  setclub(msg->club);
  if(d_keyfind(NUM,&(msg->msgno))==S_OKAY)d_delete();
}


int
dbgetindex(struct ecidx *idx)
{
  DB_ADDR x;

  if(d_crget(&x)!=S_OKAY)return BSE_NFOUND;
  return (d_recread(idx)==S_OKAY)?BSE_FOUND:BSE_NFOUND;
}


int
dbchkemail(int msgno)
{
  struct ecidx buf;
  d_recread(&buf);
  if(buf.num!=msgno)return 0;
  return (strcmp(thisuseracc.userid,buf.from)&&
	  strcmp(thisuseracc.userid,buf.to));
}


static void
opendb()
{
  /* Don't open the db if it's already open */

  if(!strcmp(dbcur,dbclubname)){
    d_dbset(clubdbid);
  } else {
    char fname[256];

    /* Close the current database */
    if(dbopen){
      d_dbset(clubdbid);
      d_close();
    }

    /* Open the new one */
    strcpy(dbcur,dbclubname);
    sprintf(fname,"%s/%s",mkfname(dbclubdir),DBDIR);
    mkdir(fname,0777);
    d_dbfpath(fname);
    d_dbdpath(mkfname(DBDDIR));
    if(d_open(".ecdb","s")!=S_OKAY){
      error_fatal("Cannot open database for %s (db_status %d).",
	    dbclubname,db_status);
    }
    d_dbget(&clubdbid);
    dbopen=1;
  }
}


void
setclub(char *club)
{
  if(!club || !club[0]){
    strcpy(dbclubname,EMAILCLUBNAME);
    strcpy(dbclubdir,EMAILDIR);
  } else {
    strcpy(dbclubname,club);
    sprintf(dbclubdir,"%s/%s",MSGSDIR,club);
  }
  opendb();
}
