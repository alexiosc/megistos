/*****************************************************************************\
 **                                                                         **
 **  FILE:     editprefs.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, preferences etc                             **
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
 * Revision 1.1  2001/04/16 14:58:24  alexios
 * Initial revision
 *
 * Revision 0.6  1999/07/18 21:48:36  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.5  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 11:14:03  alexios
 * Changed calls to audit so that they take advantage of the
 * new auditing scheme.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "telecon.h"
#include "mbk_telecon.h"


void
editprefs()
{
  FILE *fp;
  char fname[256], s[80], *cp;
  int i, nax=0, che=0, chx=0;
  struct tlcuser temptlcu;

  memcpy(&temptlcu,&tlcu,sizeof(struct tlcuser));

  leavechannel();
  usermsg(ENTEDIT);

  sprintf(fname,TMPDIR"/tlc%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  fprintf(fp,"%s\n",temptlcu.entrystg);
  fprintf(fp,"%s\n",temptlcu.exitstg);
  fprintf(fp,"%s\n",temptlcu.topic);
  if(temptlcu.flags&TLF_BEGUNINV)fprintf(fp,"%s\n",getmsg(CHANST1));
  else if(temptlcu.flags&TLF_BEGINV)fprintf(fp,"%s\n",getmsg(CHANST2));
  else fprintf(fp,"%s\n",getmsg(CHANST3));
  fprintf(fp,"%s\n",getmsg(temptlcu.flags&TLF_STARTMAIN?DEFCHAN1:DEFCHAN2));
  fprintf(fp,"%d\n",temptlcu.chatinterval);
  fprintf(fp,"%s\n",temptlcu.actions?"on":"off");
  fprintf(fp,"%s\n",getmsg(temptlcu.colour+COLOUR1-1));
  
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("telecon",UEDITVT,UEDITLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  } 

  for(i=0;i<11;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;

    if((i==0)&&strcmp(s,temptlcu.entrystg)){
      strcpy(temptlcu.entrystg,s);
      che=1;
    } else if((i==1)&&strcmp(s,temptlcu.exitstg)){
      strcpy(temptlcu.exitstg,s);
      chx=1;
    } else if(i==2)strcpy(temptlcu.topic,s);
    else if(i==3){
      int j;
      temptlcu.flags&=~(TLF_BEGUNINV|TLF_BEGINV|TLF_BEGPANEL);
      for(j=0;j<3;j++)if(!strcmp(getmsg(CHANST1+j),s)){
	if(!j)temptlcu.flags|=TLF_BEGUNINV;
	else if(j==1)temptlcu.flags|=TLF_BEGINV;
	else temptlcu.flags|=TLF_BEGPANEL;
	break;
      }
    } else if(i==4){
      if(!strcmp(getmsg(DEFCHAN1),s))temptlcu.flags|=TLF_STARTMAIN;
      else temptlcu.flags&=~TLF_STARTMAIN;
    } else if(i==5){
      temptlcu.chatinterval=thisuseraux.interval;
      thisuseraux.interval=(temptlcu.chatinterval=atoi(s))*60;
    } else if(i==6){
      if(!haskey(&thisuseracc,actkey)){
	temptlcu.actions=thisuseraux.actions=0;
	prompt(ACTNAX);
      } else temptlcu.actions=thisuseraux.actions=sameas(s,"on");
    } else if(i==7){
      int j;
      for(j=0;j<15;j++){
	if(!strcmp(s,getmsg(COLOUR1+j))){
	  temptlcu.colour=j+1;
	  break;
	}
      }
    }
  }

  fclose(fp);
  unlink(fname);
  if(!sameas(s,"CANCEL")){
    prompt(EDITOK);

    if(che){
      if(!haskey(&thisuseracc,msgkey)){
	nax=1;
	prompt(MSGNAX);
      } else if(!canpay(msgchg)){
	prompt(MSGNCRE);
      } else {
	chargecredits(msgchg);
	prompt(MSGCHE);
      }

      if(amsgch)audit(getenv("CHANNEL"),AUDIT(CHMSGE),
		      thisuseracc.userid,msgchg);
    }

    if(chx){
      if(!haskey(&thisuseracc,msgkey)){
	if(!nax)prompt(MSGNAX);
      } else if(!canpay(msgchg)){
	prompt(MSGNCRX);
      } else {
	chargecredits(msgchg);
	prompt(MSGCHX);
      }
      
      if(amsgch)audit(getenv("CHANNEL"),AUDIT(CHMSGX),
		      thisuseracc.userid,msgchg);
    }
    
    savetlcuser(thisuseracc.userid,&temptlcu);
    if((i=loadtlcuser(thisuseracc.userid,&tlcu))==0){
      fatal("Unable to re-read tlcuser %s",thisuseracc.userid);
    }

    thisuseraux.interval=temptlcu.chatinterval*60;
    thisuseraux.colour=tlcu.colour;
  } else prompt(EDITCAN);

  curchannel[0]=0;
  enterchannel(thisuseronl.telechan);
  userent(ENTTLC);
  prompt(INTRO);
  showinfo();
}


