/*****************************************************************************\
 **                                                                         **
 **  FILE:     modify.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 1995, Version 0.5                                    **
 **  PURPOSE:  Modify email/club messages                                   **
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
 * Revision 1.1  2001/04/16 14:55:26  alexios
 * Initial revision
 *
 * Revision 0.5  1999/07/18 21:21:38  alexios
 * Changed a few fatal() calls to fatalsys().
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


static int
modifybody(struct message *msg)
{
  struct message dummy;
  FILE *fp, *fp2;
  char fname[1024],modfn[256];
  struct stat st;
  int truncpos;
  
#ifdef USE_LIBZ
  decompress(msg);
#endif

  sprintf(fname,"%s/%s/"MESSAGEFILE,MSGSDIR,
	  msg->club[0]?msg->club:EMAILDIRNAME,
	  (long)msg->msgno);

  if((fp=fopen(fname,"r"))==NULL){
    fclose(fp);
#ifdef USE_LIBC
    unlink(fname);
#endif
    return 0;
  }
  sprintf(modfn,TMPDIR"/mod%05d",getpid());

  if((fp2=fopen(modfn,"w"))==NULL){
    fclose(fp);
    fclose(fp2);
#ifdef USE_LIBC
    unlink(fname);
#endif
    return 0;
  }

  if(fread(&dummy,sizeof(struct message),1,fp)!=1){
    fclose(fp);
    fclose(fp2);
#ifdef USE_LIBC
    unlink(fname);
#endif
    return 0;
  }
  
  while(!feof(fp)){
    char buffer[1025]={0}, *cp, *ep;
    int bytes=0;

    bytes=fread(buffer,1,sizeof(buffer)-1,fp);
    if(!bytes)break;
    else buffer[bytes]=0;

    if(msg->cryptkey)bbscrypt(buffer,bytes,dummy.cryptkey);

    cp=buffer;
    while(*cp){
      if((ep=strchr(cp,'\n'))==NULL){
	fprintf(fp2,"%s",cp);
	break;
      } else {
	*ep=0;
	fprintf(fp2,"%s\n",cp);
	cp=ep+1;
      }
    }
  }
  
  fclose(fp);
  fclose(fp2);


  if(editor(modfn,msglen)||stat(modfn,&st)){
    unlink(modfn);
#ifdef USE_LIBC
    unlink(fname);
#endif
    return 0;
  }


  if((fp=fopen(fname,"r+"))==NULL){
    fclose(fp);
#ifdef USE_LIBC
    unlink(fname);
#endif
    unlink(modfn);
    return 0;
  }
  fseek(fp,sizeof(struct message),SEEK_SET);
  if((fp2=fopen(modfn,"r"))==NULL){
    fclose(fp);
    fclose(fp2);
    unlink(modfn);
#ifdef USE_LIBC
    unlink(fname);
#endif
    return 0;
  }

  while(!feof(fp2)){
    char buffer[1025]={0};
    int bytes=0;

    bytes=fread(buffer,1,sizeof(buffer)-1,fp2);
    if(!bytes)break;

    if(msg->cryptkey)bbscrypt(buffer,bytes,dummy.cryptkey);
    
    fwrite(buffer,1,bytes,fp);
  }
  truncpos=ftell(fp);
  fclose(fp);
  fclose(fp2);
  truncate(fname,truncpos);
  unlink(modfn);

  return 1;
}


void
modifymail()
{
  int msgno;
  int i,j,ok=0;
  char fname[256],bedit[256],bok[256],bcan[256],res[256],s[256],*cp;
  struct stat st;
  FILE *fp;
  struct message msg;

  if(!morcnc())prompt(MMINFO);
  
  setclub(NULL);
  do{
    if(!getnumber(&msgno,MMASK,1,sysvar->emessages,MMERR3,0,0))return;

    j=findmsgfrom(&i,thisuseracc.userid,msgno,BSD_GT);
    if((j!=BSE_FOUND)||(msgno!=i))ok=0;
    else ok=1;

    /* Be paranoid about it, check if the mail itself exists, too. */

    if(ok){
      sprintf(fname,EMAILDIR"/"MESSAGEFILE,(long)msgno);
      ok=(stat(fname,&st)==0);
    }

    if(!ok)prompt(MMERR1,msgno);
  }while(!ok);

  getmsgheader(msgno,&msg);

  if(msg.flags&MSF_CANTMOD && (!hassysaxs(&thisuseracc,USY_MASTERKEY))){
    prompt(MMERR2);
    return;
  }

  if(!checklocks(&msg)){
    prompt(USING);
    return;
  }

  sprintf(fname,TMPDIR"/mm%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  fprintf(fp,"%s\n",msg.subject);
  fprintf(fp,"%s\n",msg.flags&MSF_FILEATT?msg.fatt:"");
  fprintf(fp,"%s\n",msg.flags&MSF_RECEIPT?"on":"off");
  fprintf(fp,"Edit button\nOK button\nCancel button\n");
  fclose(fp);

  dataentry("emailclubs",MMVT,MMLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<7;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==3)strcpy(bedit,s);
    else if(i==4)strcpy(bok,s);
    else if(i==5)strcpy(bcan,s);
    else if(i==6)strcpy(res,s);
  }
  if(sameas(bedit,bok))bok[0]=0;
  if(sameas(bedit,bcan))bcan[0]=0;
  if(sameas(bok,bcan))bok[0]=bcan[0]=0;

  if(sameas(res,"CANCEL")||sameas(res,bcan)){
    prompt(MMCAN);
    fclose(fp);
    unlink(fname);
    return;
  }
  if(sameas(res,bedit)){
    if(!modifybody(&msg)){
      prompt(MMCAN);
      fclose(fp);
      unlink(fname);
      return;
    }
  }
  
  rewind(fp);

  getmsgheader(msgno,&msg);

  for(i=0;i<3;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0)strcpy(msg.subject,s);
    else if(i==1){
      if(s[0]){
	if(!(msg.flags&MSF_FILEATT)){
	  if(strcmp(msg.subject,s))prompt(MMWARN1);
	} else {
	  int warn=0;
	  for(i=0;s[i];i++)if(!strchr(FNAMECHARS,s[i])){
	    warn=1;
	    s[i]='_';
	  }
	  if(warn)prompt(MMWARN2,s);
	}
      } else sprintf(msg.fatt,"%ld.att",msg.msgno);
    }else if(i==2){
      int current=(msg.flags&MSF_RECEIPT)!=0;
      int rrr=sameas(s,"ON");

      if(rrr!=current){
	if(rrr){
	  if(!haskey(&thisuseracc,rrrkey))prompt(MMWARN3);
	  else if(!canpay(rrrchg))prompt(MMWARN4);
	  else {
	    msg.flags|=MSF_RECEIPT;
	    chargecredits(rrrchg);
	    prompt(MMINFO1,rrrchg,getpfix(CRDSING,rrrchg));
	  }
	}
      }
    }
  }

  fclose(fp);
  unlink(fname);
  writemsgheader(&msg);
}


void
modifyclubmsg(struct message *orig)
{
  int i;
  char fname[256],bedit[256],bok[256],bcan[256],res[256],s[256],*cp;
  FILE *fp;
  struct message msg;

  getmsgheader(orig->msgno,&msg);

  if(!checklocks(&msg)){
    prompt(USING);
    return;
  }

  sprintf(fname,TMPDIR"/mm%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  fprintf(fp,"%s\n",msg.subject);
  fprintf(fp,"%s\n",msg.flags&MSF_FILEATT?msg.fatt:"");
  fprintf(fp,"Edit button\nOK button\nCancel button\n");
  fclose(fp);

  dataentry("emailclubs",MCMVT,MCMLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<6;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==2)strcpy(bedit,s);
    else if(i==3)strcpy(bok,s);
    else if(i==4)strcpy(bcan,s);
    else if(i==5)strcpy(res,s);
  }
  if(sameas(bedit,bok))bok[0]=0;
  if(sameas(bedit,bcan))bcan[0]=0;
  if(sameas(bok,bcan))bok[0]=bcan[0]=0;

  if(sameas(res,"CANCEL")||sameas(res,bcan)){
    prompt(MMCAN);
    fclose(fp);
    unlink(fname);
    return;
  }
  if(sameas(res,bedit)){
    if(!modifybody(&msg)){
      prompt(MMCAN);
      fclose(fp);
      unlink(fname);
      return;
    }
  }
  
  rewind(fp);

  getmsgheader(orig->msgno,&msg);

  for(i=0;i<2;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0)strcpy(msg.subject,s);
    else if(i==1){
      if(s[0]){
	if(!(msg.flags&MSF_FILEATT)){
	  if(strcmp(msg.subject,s))prompt(MMWARN1);
	} else {
	  int warn=0;
	  for(i=0;s[i];i++)if(!strchr(FNAMECHARS,s[i])){
	    warn=1;
	    s[i]='_';
	  }
	  if(warn)prompt(MMWARN2,s);
	}
      } else sprintf(msg.fatt,"%ld.att",msg.msgno);
    }
  }

  fclose(fp);
  unlink(fname);
  writemsgheader(&msg);
}


void
clubopmodify(struct message *orig)
{
  int i;
  char fname[256],bedit[256],bok[256],bcan[256],res[256],s[256],*cp;
  FILE *fp;
  struct message msg;

  memcpy(&msg,orig,sizeof(msg));
  getmsgheader(orig->msgno,&msg);

  if(!checklocks(&msg)){
    prompt(USING);
    return;
  }

  sprintf(fname,TMPDIR"/mm%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  fprintf(fp,"%s\n",msg.subject);
  fprintf(fp,"%s\n",msg.flags&MSF_FILEATT?msg.fatt:"");
  fprintf(fp,"%s\n",msg.flags&MSF_APPROVD?"on":"off");
  fprintf(fp,"%s\n",msg.flags&MSF_EXEMPT?"on":"off");
  fprintf(fp,"%d\n",msg.period);
  fprintf(fp,"Edit button\nOK button\nCancel button\n");
  fclose(fp);

  dataentry("emailclubs",COPMVT,COPMLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<9;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==5)strcpy(bedit,s);
    else if(i==6)strcpy(bok,s);
    else if(i==7)strcpy(bcan,s);
    else if(i==8)strcpy(res,s);
  }
  if(sameas(bedit,bok))bok[0]=0;
  if(sameas(bedit,bcan))bcan[0]=0;
  if(sameas(bok,bcan))bok[0]=bcan[0]=0;

  if(sameas(res,"CANCEL")||sameas(res,bcan)){
    prompt(MMCAN);
    fclose(fp);
    unlink(fname);
    return;
  }
  if(sameas(res,bedit)){
    if(!modifybody(&msg)){
      prompt(MMCAN);
      fclose(fp);
      unlink(fname);
      return;
    }
  }
  
  rewind(fp);

  getmsgheader(orig->msgno,&msg);

  for(i=0;i<5;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0)strcpy(msg.subject,s);
    else if(i==1){
      if(s[0]){
	if(!(msg.flags&MSF_FILEATT)){
	  if(strcmp(msg.subject,s))prompt(MMWARN1);
	} else {
	  int warn=0;
	  for(i=0;s[i];i++)if(!strchr(FNAMECHARS,s[i])){
	    warn=1;
	    s[i]='_';
	  }
	  if(warn)prompt(MMWARN2,s);
	}
      } else sprintf(msg.fatt,"%ld.att",msg.msgno);
    } else if(i==2){
      int i=(msg.flags&MSF_APPROVD)!=0;
      int j=sameas(s,"on");
      if((msg.flags&MSF_FILEATT)&&(i!=j)){
	msg.flags^=MSF_APPROVD;
	prompt(msg.flags&MSF_APPROVD?COPOK1:COPOK2);
      } else if(i!=j)prompt(COPMW1);
    } else if(i==3){
      int j=(msg.flags&MSF_EXEMPT)!=0;
      int k=sameas(s,"on");
      if(j!=k){
	msg.flags^=MSF_EXEMPT;
	prompt(msg.flags&MSF_EXEMPT?COPOK3:COPOK4);
      }
    } else if(i==4){
      int j;
      int k=msg.period;
      if(sscanf(s,"%d",&j)){
	if(j!=k){
	  msg.period=j;
	  if(msg.period)prompt(COPOK5,msg.period,getpfix(DAYSNG,msg.period));
	  else prompt(COPOK6);
	}
      }
    }
  }

  fclose(fp);
  unlink(fname);
  writemsgheader(&msg);
}
