/*****************************************************************************\
 **                                                                         **
 **  FILE:     prefs.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 1995, Version 0.5                                    **
 **  PURPOSE:  Email preferences                                            **
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
 * Revision 1.1  2001/04/16 14:55:30  alexios
 * Initial revision
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


static void
setsignature()
{
  char fname[256], fname2[256];
  FILE *fp, *fp2;
  int bytes, lines, truncpos=-1;
  char buffer[1024];
  struct stat st;

  
  if(!haskey(&thisuseracc,sigckey)){
    prompt(NOAXSIG);
    return;
  }
  if(!canpay(sigchg)){
    prompt(NOCRSIG,sigchg,getpfix(CRDSNG,sigchg));
    return;
  }

  sprintf(fname,"%s/%s",MSGSIGDIR,thisuseracc.userid);
  sprintf(fname2,TMPDIR"/email-%d",getpid());

  if((fp=fopen(fname,"r"))!=NULL){
    if((fp2=fopen(fname2,"w"))==NULL){
      fclose(fp);
      unlink(fname2);
      return;
    }

    do{
      if((bytes=fread(buffer,1,sizeof(buffer),fp))!=0)
	fwrite(buffer,bytes,1,fp2);
    }while(bytes);

    fclose(fp);
    fclose(fp2);
  }

  if(editor(fname2,sigbmax)||stat(fname2,&st)){
    prompt(SIGCCAN);
    unlink(fname2);
    return;
  }
  
  if((fp2=fopen(fname2,"r"))==NULL){
    prompt(SIGCCAN);
    unlink(fname2);
    return;
  }
  if((fp=fopen(fname,"w"))==NULL){
    prompt(SIGCCAN);
    fclose(fp2);
    unlink(fname2);
    return;
  }

  lines=0;
  while(!feof(fp2)){
    if(fgets(buffer,sizeof(buffer),fp2)){
      if(strlen(buffer)>1)truncpos=-1;
      else if(truncpos==-1)truncpos=ftell(fp);

      lines++;
      if(lines>siglmax){
	prompt(SIGLIN,siglmax,getpfix(LINSNG,siglmax));
	break;
      } else fputs(buffer,fp);
    } else break;
  }
  fclose(fp);
  fclose(fp2);
  unlink(fname2);
  if(truncpos!=-1)truncate(fname,truncpos);

  prompt(SIGOK,sigchg,getpfix(CRDSNG,sigchg));
  chargecredits(sigchg);
}


void
preferences()
{
  struct emailuser ecuser;
  char uid[256], c, otheruid[256];
  int first=1;

  for(;;){
    if(!getmenu(&c,first,PMENU,PMENUS,ERRSEL,"1234",0,0))return;
    first=0;

    switch(c-'0'){
    case 1:
      if(!haskey(&thisuseracc,afwkey)){
	prompt(PQUEST1N);
	break;
      }

      if(haskey(&thisuseracc,sopkey)){
	if(!getuserid(otheruid,PQUEST1A,PQUEST1U,PQUEST1D,thisuseracc.userid,0))
	  return;
      } else strcpy(otheruid,thisuseracc.userid);

      if(!readecuser(otheruid,&ecuser))return;
      
      if((!strcmp(ecuser.forwardto,otheruid))||(!ecuser.forwardto[0])){
	prompt(PQUEST1IB);
      }else{
	prompt(PQUEST1IA,ecuser.forwardto);
      }

      if(!getuserid(uid,PQUEST1B,PQUEST1U,PQUEST1D,otheruid,0))return;
      else {
	strcpy(ecuser.forwardto,uid);
	if(sameas(otheruid,ecuser.forwardto))prompt(PQUEST1Y);
	else prompt(PQUEST1O,uid);
      }
      writeecuser(otheruid,&ecuser);
      break;

    case 2:
      if(!readecuser(thisuseracc.userid,&ecuser))return;
      if(!getmenu(&c,1,PQUEST2,PQUEST2S,PQUEST2R,"123",0,0)){
	writeecuser(thisuseracc.userid,&ecuser);
	return;
      }
      ecuser.prefs&=~(ECP_QUOTEYES|ECP_QUOTEASK);
      if(c=='2')ecuser.prefs|=ECP_QUOTEYES;
      else if(c=='3')ecuser.prefs|=ECP_QUOTEASK;
      writeecuser(thisuseracc.userid,&ecuser);
      break;

    case 3:
      if(!readecuser(thisuseracc.userid,&ecuser))return;
      if(!getmenu(&c,1,PQUEST3,PQUEST3S,PQUEST3R,"123",0,0)){
	writeecuser(thisuseracc.userid,&ecuser);
	return;
      }
      ecuser.prefs&=~(ECP_LOGINYES|ECP_LOGINASK);
      if(c=='2')ecuser.prefs|=ECP_LOGINYES;
      else if(c=='3')ecuser.prefs|=ECP_LOGINASK;
      writeecuser(thisuseracc.userid,&ecuser);
      break;

    case 4:
      setsignature();
      break;
    }
  }
}



