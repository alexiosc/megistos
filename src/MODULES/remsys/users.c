/*****************************************************************************\
 **                                                                         **
 **  FILE:     users.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Sysop commands dealing with users in various nasty ways      **
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
 * Revision 1.1  2001/04/16 14:58:16  alexios
 * Initial revision
 *
 * Revision 0.8  1998/12/27 16:07:28  alexios
 * Added autoconf support. Added support for new getlinestatus().
 * Fixed a POST bug that wouldn't post to users not on-line.
 *
 * Revision 0.7  1998/08/11 10:19:45  alexios
 * Fixed audit calls in delete, exempt and suspend commands.
 *
 * Revision 0.6  1998/07/24 10:23:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.5  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 11:10:55  alexios
 * Changed flaguser() to allow calls to audit() within
 * the function to use the new auditing scheme. Flaguser() now
 * has a good collection of arguments. :-) Generally changed
 * calls to audit so they make use of the new scheme.
 *
 * Revision 0.3  1997/09/12 13:24:18  alexios
 * Added auditing() for the rsys_hangup() command.
 *
 * Revision 0.2  1997/08/30 13:01:01  alexios
 * Changed bladcommand() calls to bbsdcommand(). Removed commented
 * out audit() entries logging user disconnections. These are now
 * recorded by bbsd itself.
 *
 * Revision 0.1  1997/08/28 11:05:52  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "remsys.h"

#include "mbk_remsys.h"


char *
flaguser(pr,flag,ok1,ok0,err,flag1,aus1,aud1,flag2,aus2,aud2)
int pr,flag,ok1,ok0,err,flag1,flag2;
char *aus1,*aud1,*aus2,*aud2;
{
  static char userid[32];
  useracc usracc, *uacc=&usracc;

  memset(userid,0,sizeof(userid));
  if(!getuserid(userid,pr,UNKUID,0,NULL,0))return userid;
  if(!uinsys(userid,0))loaduseraccount(userid,uacc);
  else uacc=&othruseracc;

  if((uacc->flags&UFL_EXEMPT||sameas(userid,SYSOP))
     &&(!(uacc->flags&flag))){
    prompt(err,userid);
    userid[0]=0;
    return userid;
  }
  
  uacc->flags^=flag;
  
  if (!uinsys(userid,0))saveuseraccount(uacc);
  if(uacc->flags&flag){
    prompt(ok1,userid);
    audit(getenv("CHANNEL"),flag1,aus1,aud1,thisuseracc.userid,userid);
  } else {
    prompt(ok0,userid);
    audit(getenv("CHANNEL"),flag2,aus2,aud2,thisuseracc.userid,userid);
    userid[0]=0;
  }
  return userid;
}


void
rsys_delete()
{
  char userid[32];
  strcpy(userid,
	 flaguser(RSDELETEWHO,UFL_DELETED,RSDELETEOK,
		  RSDELETEUNDO,RSDELETEERR,
		  AUDIT(RSMDEL),AUDIT(RSMUDEL)));

  /* Do this anyway. If we're undeleting, we know the user isn't
     online anyway */

  if(userid[0]){
    if(uinsys(userid,0)){
      bbsdcommand("hangup",othruseronl.channel,"");
    }
  }
}


void
rsys_exempt()
{
  flaguser(RSEXEMPTWHO,UFL_EXEMPT,RSEXEMPTOK,RSEXEMPTUNDO,RSEXEMPTERR,
	   AUDIT(RSXMPT),AUDIT(RSUXMPT));
}


void rsys_post()
{
  int     getclassname();
  char    userid[24];
  int     amount, fop;
  useracc usracc, *uacc=&usracc;
  int     prompted=0;

  if(!getuserid(userid,RSPOSTWHO,UNKUID,0,NULL,0))return;
  if(!uinsys(userid,0))loaduseraccount(userid,uacc);
  else uacc=&othruseracc;

  if(!getnumber(&amount,RSPOSTAMT,-1<<30,0x7fffffff,NUMERR,0,0))return;
  if(!amount) return;

  for(;;){
    int c=0;
    char *s;
    lastresult=0;
    if(morcnc()){
      s=cncword();
      c=toupper(*s);
    } else {
      prompt(RSPOSTFOP,NULL);
      getinput(0);
      if(margc&&isX(margv[0]))return;
      c=toupper(margv[0][0]);
    }
    if(c=='F' || c=='P'){
      fop=toupper(c);
      break;
    } else {
      endcnc();
      prompt(RSPOSTERR,NULL);
    }      
  }

  for(;;){
    int c=0;
    lastresult=0;
    if(morcnc()){
      c=cncyesno();
    } else {
      char creds[MSGBUFSIZE];
      char acc  [MSGBUFSIZE];

      strcpy(creds,getpfix(CRDSING,amount==1));
      strcpy(acc,getpfix(MSCACC,uacc->sex==USX_MALE));

      prompt(RSPOSTCNF,amount,(fop=='F')?"FREE":"PAID",creds,acc,uacc->userid);
      getinput(0);
      if(margc&&isX(margv[0]))return;
      c=toupper(margv[0][0]);
    }
    if(c=='Y')break;
    else if(c=='N')return;
  }

  if(!userexists(userid)){
    prompt(RSPOSTDEL,NULL);
    return;
  }

  postcredits(uacc->userid,amount,fop=='P');
  audit(getenv("CHANNEL"),AUDIT(CRDPOST),amount,
	(fop=='P'?"PAID":"FREE"),uacc->userid);
  if(fop=='P'){
    classrec *ourclass=findclass(uacc->curclss);
    if(strcmp(ourclass->credpost,uacc->curclss)){
      strncpy(uacc->curclss,ourclass->credpost,sizeof(uacc->tempclss));
      strncpy(uacc->tempclss,uacc->curclss,sizeof(uacc->tempclss));
      uacc->classdays=0;
      prompted=1;
      prompt(RSPOSTOK2,uacc->curclss);

      if (uinsys(userid,0)) {
	sprintf(outbuf,getmsglang(RSPOSTNOT3,othruseracc.language-1),
		amount,getpfixlang(CRDSING,amount==1,othruseracc.language-1),
		uacc->curclss);
	if(injoth(&othruseronl,outbuf,0))prompt(NOTIFIED,othruseronl.userid);
      }
    }
  }

  if(!prompted){
    prompt(RSPOSTOK);
    
    if (uinsys(userid,0)) {
      sprintf(outbuf,getmsglang(RSPOSTNOT1+(fop=='P'),othruseracc.language-1),
	      amount,getpfixlang(CRDSING,amount==1,othruseracc.language-1));
      if(injoth(&othruseronl,outbuf,0))prompt(NOTIFIED,othruseronl.userid);
    }
  }
}


void
rsys_hangup()
{
  char tty[64];
  struct linestatus status;

  for(;;){
    if(!getchanname(tty,RSHANGUPWHO,0))return;
    getlinestatus(tty,&status);
    if(status.result!=LSR_USER){
      prompt(RSHANGUPERR);
      endcnc();
    }
    else break;
  }
  bbsdcommand("hangup",tty,"");
  audit(getenv("CHANNEL"),AUDIT(KICKED),thisuseracc.userid,status.user);
  prompt(RSHANGUPOK,NULL);
}


void
rsys_suspend()
{
  char userid[32];
  strcpy(userid,
	 flaguser(RSSUSPWHO,UFL_SUSPENDED,RSSUSPOK,
		  RSSUSPUNDO,RSSUSPERR,
		  AUDIT(RSSUSP),AUDIT(RSUSUSP)));
  if(userid[0]){
    if(uinsys(userid,0))bbsdcommand("hangup",othruseronl.channel,"");
  }
}


void
rsys_detail()
{
  static char userid[32];
  useracc usracc, *uacc=&usracc;
  char wh[80],age[80],sex[80];
  char s1[80],s2[80],s3[80],s4[80];
  char d1[80],d2[80];
  char sys[80],ns[80],lang[80];

  memset(userid,0,sizeof(userid));
  if(!getuserid(userid,RSDETAILWHO,UNKUID,0,NULL,0))return;
  if(!uinsys(userid,0))loaduseraccount(userid,uacc);
  else uacc=&othruseracc;

  strcpy(wh,getmsg(RSDETAILNAX));
  strcpy(sex,uacc->sex==USX_MALE?getmsg(RSDETAILM):getmsg(RSDETAILF));
  memset(s1,0,sizeof(s1));
  if(uacc->flags&UFL_SUSPENDED)strcpy(s1,getmsg(RSDETAILSUSP));
  memset(s2,0,sizeof(s2));
  if(uacc->flags&UFL_EXEMPT)strcpy(s2,getmsg(RSDETAILXMPT));
  memset(s3,0,sizeof(s3));
  if(uacc->flags&UFL_DELETED)strcpy(s3,getmsg(RSDETAILDEL));
  memset(s4,0,sizeof(s3));
  if(uacc->sysaxs[0]||uacc->sysaxs[1]||uacc->sysaxs[2])
    strcpy(s4,getmsg(RSDETAILOP));
  strcpy(sys,getmsg(RSDETAILS1+uacc->system-1));
  ns[0]=0;
  if(uacc->prefs&UPF_NONSTOP)strcpy(ns,getmsg(RSDETAILNST));
  strcpy(lang,getmsg(RSDETAILL1+uacc->language-1));
  sprintf(age,"%d",uacc->age);

  strcpy(d1,strdate(uacc->datecre));
  strcpy(d2,(uacc->datelast>=0)?strdate(uacc->datelast):"");
  prompt(RSDETAIL,userid,
	 d1,s1,s2,
	 d2,s3,s4,
	 (haskey(&thisuseracc,kydnam)?uacc->username:wh),
	 (haskey(&thisuseracc,kydcom)?uacc->company:wh),
	 (haskey(&thisuseracc,kydadr)?uacc->address1:wh),
	 (haskey(&thisuseracc,kydadr)?uacc->address2:wh),
	 (haskey(&thisuseracc,kydpho)?uacc->phone:wh),
	 (haskey(&thisuseracc,kydage)?age:wh),
	 (haskey(&thisuseracc,kydsex)?sex:wh),
	 sys,uacc->scnwidth,uacc->scnheight,ns,
	 lang,uacc->curclss,
	 ((!hidepass)&&haskey(&thisuseracc,kydpss)?uacc->passwd:wh),
	 uacc->credits,uacc->totpaid);
}


int
stgcmp(char *op,char *a,char *b)
{
  int d;
  if(sameas(op," "))return 0;
  if(sameas(op,"IN"))return(strstr(a,b)!=NULL);
  d=strcmp(a,b);
  if(d<0 && (sameas(op,"<")||sameas(op,"<=")))return 1;
  if(d==0 && (sameas(op,"<=")||sameas(op,"=")||sameas(op,">=")))return 1;
  if(d>0 && (sameas(op,">=")||sameas(op,">")))return 1;
  return 0;
}


int
numcmp(char *op,int a,int b)
{
  int d;
  if(sameas(op," "))return 0;
  d=a-b;
  if(d<0 && (sameas(op,"<")||sameas(op,"<=")))return 1;
  if(d==0 && (sameas(op,"<=")||sameas(op,"=")||sameas(op,">=")))return 1;
  if(d>0 && (sameas(op,">=")||sameas(op,">")))return 1;
  return 0;
}


void
rsys_search()
{
  char fname[256];
  FILE *fp;
  char data[30][80], command[256];
  char line[1024], *cp;
  int  i=0,check=0;
  
  sprintf(fname,TMPDIR"/rssrch-%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    fclose(fp);
    return;
  }
  fprintf(fp,"\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  fprintf(fp,"\n%s\n",getmsg(RSSRCHS1));
  fprintf(fp,"\n0\n");
  fprintf(fp,"\n%s\n",getmsg(RSSRCHM));
  fprintf(fp,"\n0\n");
  fprintf(fp,"\n0\n\n\n");
  i=today();
  fprintf(fp,"\n%d/%d/%d\n",tdday(i),1+tdmonth(i),tdyear(i));
  fprintf(fp,"\n%d/%d/%d\n",tdday(i),1+tdmonth(i),tdyear(i));
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("remsys",RSSRCHVT,RSSRCHLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    fclose(fp);
    return;
  }
  for(i=0;i<30;i++){
    fgets(line,sizeof(line),fp);
    if((cp=strchr(line,'\n'))!=NULL)*cp=0;
    strncpy(data[i],line,79);
    if(strcmp(" ",line) && (i%2)==0)check++;
  }
  fgets(line,sizeof(line),fp);
  fgets(line,sizeof(line),fp);
  fgets(line,sizeof(line),fp);
  fclose(fp);
  unlink(fname);
  if((cp=strchr(line,'\n'))!=NULL)*cp=0;
  if(sameas(line,"CANCEL")){
    prompt(RSSRCHC);
    return;
  }
  if(!check)prompt(RSSRCHR);

  if(sameas(getmsg(RSSRCHM),data[19]))data[19][0]=USX_MALE;
  else data[19][0]=USX_FEMALE;
  data[19][1]=0;

  for(i=0;i<8;i++){
    if(sameas(getmsg(RSSRCHS1+i),data[15])){
      sprintf(data[15],"%d",i+1);
      break;
    }
  }

  sprintf(data[27],"%ld",cofdate(scandate(data[27])));
  sprintf(data[29],"%ld",cofdate(scandate(data[29])));

  for(i=0;i<15;i++)strcpy(data[i*2+1],phonetic(data[i*2+1]));

  sprintf(command,"\\ls %s",USRDIR);
  if((fp=popen(command,"r"))==NULL)return;

  nonblocking();

  prompt(RSSRCHB);
  while(!feof(fp)){
    char c=0,name[80];

    if(read(0,&c,1))if(c==13||c==10||c==27||c==15||c==3){
      prompt(RSSRCHC);
      break;
    }
    if(lastresult==PAUSE_QUIT){
      prompt(RSSRCHC);
      break;
    }
    if(fscanf(fp,"%s",name)==1){
      useracc usracc, *uacc=&usracc;
      int match=0;

      if(!uinsys(name,0))loaduseraccount(name,uacc);
      else memcpy(uacc,&othruseracc,sizeof(useracc));

      match=0;      
      for(i=0;i<15;i++){
	char s[80];
	int  n;

	s[0]=0;
	n=0;
	switch(i){
	case 0:
	  strcpy(s,phonetic(uacc->userid));
	  break;
	case 1:
	  strcpy(s,phonetic(uacc->passwd));
	  break;
	case 2:
	  strcpy(s,uacc->username);
	  phonetic(s);
	  break;
	case 3:
	  strcpy(s,phonetic(uacc->company));
	  break;
	case 4:
	  strcpy(s,phonetic(uacc->address1));
	  break;
	case 5:
	  strcpy(s,phonetic(uacc->address2));
	  break;
	case 6:
	  strcpy(s,phonetic(uacc->phone));
	  break;
	case 7:
	  n=uacc->system;
	  break;
	case 8:
	  n=uacc->age;
	  break;
	case 9:
	  s[0]=uacc->sex;
	  s[1]=0;
	  break;
	case 10:
	  n=uacc->credits;
	  break;
	case 11:
	  n=uacc->totpaid;
	  break;
	case 12:
	  strcpy(s,phonetic(uacc->curclss));
	  break;
	case 13:
	  n=cofdate(uacc->datecre);
	  break;
	case 14:
	  n=(uacc->datelast==-1?-1:cofdate(uacc->datelast));
	  break;
	}
	switch(i){
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 9:
	case 12:
	  match+=stgcmp(data[i*2],s,data[i*2+1]);
	  break;
	case 7:
	case 8:
	case 10:
	case 11:
	case 13:
	case 14:
	  match+=numcmp(data[i*2],n,atoi(data[i*2+1]));
	  break;
	}
      }
      if(match==check)prompt(RSSRCHL,name,uacc->username);
    }
  }
  fclose(fp);
  print("\n");
  blocking();
}

