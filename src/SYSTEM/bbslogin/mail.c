/*****************************************************************************\
 **                                                                         **
 **  FILE:     mail.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: D, July 95, Version 0.4                                      **
 **  PURPOSE:  Send email to/from sysop after a signup                      **
 **  NOTES:    This had to be implemented here, and not in signup, since    **
 **            (a) there were security risks                                **
 **            (b) we can only send mail after the online record of the     **
 **                user has been created, and this is done in bbslogin      **
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
 * Revision 0.7  1998/12/27 16:19:44  alexios
 * Added autoconf support.
 *
 * Revision 0.6  1998/03/10 10:11:26  alexios
 * Reinstating the STABLE status. What a silly mistake.
 *
 * Revision 0.5  1998/03/10 10:09:34  alexios
 * No changes.
 *
 * Revision 0.4  1997/11/06 20:15:17  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/06 17:03:13  alexios
 * Fixed a few minor leftover bugs and switched to the new
 * auditing scheme.
 *
 * Revision 0.2  1997/08/30 13:08:49  alexios
 * Added call to system() so that mail can be sent to the Sysop.
 * Stupid bug.
 *
 * Revision 0.1  1997/08/28 11:13:27  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_PWD_H 1
#define WANT_GRP_H 1
#define WANT_UTMP_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"
#include "mbk_signup.h"
#include "mbk_login.h"


promptblock_t *signup;

int  supu2s;
char *supauth;
int  sups2u;
char *e2uatt;
int  e2urrr;


void
sendu2s()
{
  FILE *fp;
  char header[256], body[256];
  int  kgdnam, kgdcom, kgdadr, kgdpho, kgdage, kgdsex;
  int  kgdpss, kgdpass;
  char wh[80],age[80],sex[80];
  char s1[80],s2[80],s3[80],s4[80];
  char d1[80],d2[80];
  char sys[80],ns[80],lang[80];
  char buffer[MSGBUFSIZE], *supauth;
  char command[256];
  struct message msg;

  msg_set(msg_sys);

  kgdnam=msg_int(KGDNAM,0,129);
  kgdcom=msg_int(KGDCOM,0,129);
  kgdadr=msg_int(KGDADR,0,129);
  kgdpho=msg_int(KGDPHO,0,129);
  kgdage=msg_int(KGDAGE,0,129);
  kgdsex=msg_int(KGDSEX,0,129);
  kgdpss=msg_int(KGDPSS,0,129);
  kgdpass=msg_bool(KGDPASS);

  strcpy(wh,msg_get(GDETNAX));
  strcpy(sex,thisuseracc.sex==USX_MALE?msg_get(GDETM):msg_get(GDETF));
  memset(s1,0,sizeof(s1));
  if(thisuseracc.flags&UFL_SUSPENDED)strcpy(s1,msg_get(GDETSUSP));
  memset(s2,0,sizeof(s2));
  if(thisuseracc.flags&UFL_EXEMPT)strcpy(s2,msg_get(GDETXMPT));
  memset(s3,0,sizeof(s3));
  if(thisuseracc.flags&UFL_DELETED)strcpy(s3,msg_get(GDETDEL));
  memset(s4,0,sizeof(s3));
  if(thisuseracc.sysaxs[0]||thisuseracc.sysaxs[1]||thisuseracc.sysaxs[2])
    strcpy(s4,msg_get(GDETOP));
  strcpy(sys,msg_get(GDETS1+thisuseracc.system-1));
  ns[0]=0;
  if(thisuseracc.prefs&UPF_NONSTOP)strcpy(ns,msg_get(GDETNST));
  strcpy(lang,msg_get(GDETL1+thisuseracc.language-1));
  sprintf(age,"%d",thisuseracc.age);

  strcpy(d1,strdate(thisuseracc.datecre));
  strcpy(d2,(thisuseracc.datelast>=0)?strdate(thisuseracc.datelast):"");
  sprompt(buffer,GDET,thisuseracc.userid,
	 d1,s1,s2,
	 d2,s3,s4,
	 thisuseracc.username,
	 thisuseracc.company,
	 thisuseracc.address1,
	 thisuseracc.address2,
	 thisuseracc.phone,
	 age,
	 sex,
	 sys,thisuseracc.scnwidth,thisuseracc.scnheight,ns,
	 lang,thisuseracc.curclss,
	 ((!kgdpass)?thisuseracc.passwd:wh),
	 thisuseracc.credits,thisuseracc.totpaid);

  msg_set(signup);

  sprintf(body,"/tmp/u2s%dB",getpid());
  if((fp=fopen(body,"w"))==NULL)return;
  fputs(buffer,fp);
  fclose(fp);

  supauth=msg_get(SUPAUTH);
  if(supauth && *supauth){
    sprintf(command,"%s %s %s",supauth,thisuseracc.userid,body);
    system(command);
  }

  memset(&msg,0,sizeof(msg));
  strcpy(msg.from,thisuseracc.userid);
  strcpy(msg.to,SYSOP);
  sprintf(msg.subject,msg_get(U2STPC),thisuseracc.userid);
  msg.flags=MSF_CANTMOD|MSF_SIGNUP;

  sprintf(header,"/tmp/u2s%dH",getpid());
  if((fp=fopen(header,"w"))==NULL)return;
  fwrite(&msg,sizeof(msg),1,fp);
  fclose(fp);

  sprintf(command,"%s %s %s",BBSMAILBIN,header,body);
  system(command);
  unlink(body);
  unlink(header);
}


void
sends2u()
{
  FILE *fp;
  char header[256], body[256];
  char command[256];
  struct message msg;
  char *e2uatt;

  sprintf(body,"/tmp/s2u%dB",getpid());
  if((fp=fopen(body,"w"))==NULL)return;
  fputs(msg_get(S2UTXT),fp);
  fclose(fp);

  memset(&msg,0,sizeof(msg));
  strcpy(msg.to,thisuseracc.userid);
  strcpy(msg.from,SYSOP);
  sprintf(msg.subject,msg_get(S2UTPC),thisuseracc.userid);
  if(msg_bool(E2URRR))msg.flags=MSF_RECEIPT;

  e2uatt=msg_string(E2UATT);
  if(e2uatt && *e2uatt){
    msg.flags|=(MSF_FILEATT|MSF_APPROVD);
    strcpy(msg.fatt,msg_get(E2UNAM));
  }

  sprintf(header,"/tmp/s2u%dH",getpid());
  if((fp=fopen(header,"w"))==NULL)return;
  fwrite(&msg,sizeof(msg),1,fp);
  fclose(fp);

  if(e2uatt && *e2uatt){
    sprintf(command,"%s %s %s -s %s",BBSMAILBIN,header,body,e2uatt);
  } else {
    sprintf(command,"%s %s %s",BBSMAILBIN,header,body);
  }
  system(command);
  unlink(body);
  unlink(header);
}


void
sendmail()
{
  signup=msg_open("signup");
  msg_set(signup);
  supu2s=msg_bool(SUPU2S);
  supauth=msg_string(SUPAUTH);
  sups2u=msg_bool(SUPS2U);
  e2uatt=msg_string(E2UATT);
  e2urrr=msg_bool(E2URRR);

  if(supu2s)sendu2s();
  if(sups2u)sends2u();

  audit(thisuseronl.channel,AUDIT(SIGNUP),thisuseracc.userid);
}


