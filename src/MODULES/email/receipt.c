/*****************************************************************************\
 **                                                                         **
 **  FILE:     receipt.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **  PURPOSE:  Send a return receipt for a message                          **
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
 * Revision 1.2  2001/04/16 21:56:31  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Used new timedate function getdow() to fix stupid day-of-week
 * errors once and for all.
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
#include "email.h"


void
sendreceipt(struct message *msg)
{
  struct message rrr;
  char hdrname[256], fname[256], s1[256], s2[256];
  char command[256];
  FILE *fp;

  if(strcmp(msg->to,thisuseracc.userid))return;
  sprintf(fname,TMPDIR"/rrrB%d%lx",getpid(),time(0));
  if((fp=fopen(fname,"w"))==NULL)return;

  strcpy(s1,msg_get(MHDAY0+getdow(msg->crdate)));
  strcpy(s2,msg_get(MHJAN+tdmonth(msg->crdate)));
  
  fprintf(fp,msg_get(RRRBODY),
	  msg_getunit(SEXMALE,thisuseracc.sex==USX_MALE),thisuseracc.userid,
	  EMAILCLUBNAME,msg->msgno,
	  s1, tdday(msg->crdate), s2, tdyear(msg->crdate),
	  strtime(msg->crtime,1));
  
  fclose(fp);

  memset(&rrr,0,sizeof(rrr));
  strcpy(rrr.from,thisuseracc.userid);
  strcpy(rrr.to,msg->from);
  sprintf(rrr.subject,msg_get(RRRSUBJ),EMAILCLUBNAME,msg->msgno);
  sprintf(rrr.history,HST_RECEIPT" %s/%d",EMAILCLUBNAME,msg->msgno);
  rrr.flags=MSF_CANTMOD;

  sprintf(hdrname,TMPDIR"/rrrH%d%lx",getpid(),time(0));
  if((fp=fopen(hdrname,"w"))==NULL){
    unlink(fname);
    return;
  }
  fwrite(&rrr,sizeof(rrr),1,fp);
  fclose(fp);

  sprintf(command,"%s %s %s",BBSMAILBIN,hdrname,fname);
  system(command);
  unlink(hdrname);
  unlink(fname);

  prompt(RRRGEN);
  
  if(usr_insys(msg->from,1)){
    sprintf(out_buffer,msg_getl(RRRINJ,othruseracc.language-1),
	    thisuseracc.userid);
    if(usr_injoth(&othruseronl,out_buffer,0))prompt(RRRNOT,othruseronl.userid);
  }
  
  msg->flags&=~MSF_RECEIPT;
}

