/*****************************************************************************\
 **                                                                         **
 **  FILE:     miscfuncs.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Miscellaneous functions for the remote sysop menu            **
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
 * Revision 1.1  2001/04/16 14:58:07  alexios
 * Initial revision
 *
 * Revision 0.7  1999/07/18 21:48:04  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.6  1998/12/27 16:07:28  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/11 10:19:45  alexios
 * Migrated file transfer calls to the new format.
 *
 * Revision 0.4  1998/07/24 10:23:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 16:59:23  alexios
 * Made the AUDIT command take into account the new format of
 * the audit trail. The command now colour-codes entries acc-
 * ording to their severity. Implemented the PAGEAUDIT command
 * to configure filters for global auditing. Wrote a function
 * filter_audit() to look for specific keywords and/or flags
 * in the audit trail. Added a command FILTAUD to work as an
 * interface to filter_audit(). Commands SECURITY and SIGNUPS
 * work as macros to filter_audit(), looking for certain things.
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "remsys.h"

#include "mbk_sysvar.h"
#undef CRDSING
#undef CRDPLUR
#include "mbk_remsys.h"


void
rsys_event()
{
  char command[256];

  sprintf(command,"%s/%s",BINDIR,"eventman");
  runmodule(command);
}


static void
download()
{
  char c,spec[256];

  for(;;){
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return;
    } else {
      prompt(RSXFERWHD);
      getinput(0);
      nxtcmd=input;
      if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return;
      }
    }
    killxferlist();
    strcpy(spec,cncword());
    if(addwild(FXM_DOWNLOAD,spec,sxfdesc,0,-1)){
      dofiletransfer();
      killxferlist();
      break;
    }else{
      prompt(RSXFERERR,nxtcmd);
      endcnc();
      continue;
    }
  }
}


static void
upload()
{
  char fname[256],command[256],*cp;
  FILE *fp;
  int  count = -1;

  addxfer(FXM_UPLOAD,"NAMELESS",sxfdesc,0,0);
  dofiletransfer();
  
  sprintf(fname,XFERLIST,getpid());

  if((fp=fopen(fname,"r"))==NULL){
    prompt(RSXFERER3);
    goto kill;
  }

  while (!feof(fp)){
    char line[1024];

    if(fgets(line,sizeof(line),fp))if(!++count)strcpy(fname,line);
  }
  if((cp=strchr(fname,'\n'))!=NULL)*cp=0;
  fclose(fp);

  if(!count)goto kill;

  for(;;){
    struct stat st;

    prompt(RSXFERWHU,count);
    getinput(0);
    nxtcmd=input;
    if (!margc) {
      endcnc();
      continue;
    }
    if(isX(margv[0])){
      goto kill;
    }
    if(stat(input,&st))prompt(RSXFERERR,input);
    else if(!(st.st_mode&S_IFDIR))prompt(RSXFERER2,input);
    else break;
  }

  sprintf(command,"mv %s/* %s",fname,input);
  system(command);

 kill:
  if(count>=0){
    sprintf(command,"rm -rf %s",fname);
    system(command);
  }
  killxferlist();
}


void
rsys_transfer()
{
  char opt;

  if(!getmenu(&opt,1,RSXFERDIR,RSXFERSHRT,RSXFERRSEL,"UD",0,0))return;

  if (opt=='D') download(); else upload();
}


void
rsys_invis()
{
  thisuseronl.flags^=OLF_INVISIBLE;
  setmbk(sysblk);
  prompt((thisuseronl.flags&OLF_INVISIBLE)?INVON:INVOFF);
  rstmbk();
}


void
rsys_gdet()
{
  prompt(RSGDET);
}


void
rsys_sysop()
{
  void    showmenu();
  char    userid[24];
  char    *word;
  int     shownmenu=1;
  useracc uacc;
  
  if(!sameas(thisuseracc.userid,SYSOP)){
    prompt(RSSYSOPNSY,NULL);
    return;
  }
  if(!getuserid(userid,RSSYSOPWHO,UNKUID,0,NULL,0))return;
  if(sameas(userid,SYSOP)){
    prompt(RSSYSOPSOP,NULL);
    return;
  }

  if(!uinsys(userid,0))loaduseraccount(userid,&uacc);
  else memcpy(uacc.sysaxs,othruseracc.sysaxs,sizeof(uacc.sysaxs));
  
  endcnc();
  for(;;){
    if(!shownmenu){
      prompt(RSSYSOPHDR,userid);
      showmenu(uacc.sysaxs,1);
      shownmenu=1;
    }
    if(morcnc()){
      word=cncword();
    } else {
      prompt(RSSYSOPMNU,NULL);
      getinput(0);
      word=input;
    }

    if(!margc || reprompt){
      endcnc();
      continue;
    } else if (isX(word)) {
      break;
    } else if (sameas(word,"?")) {
      endcnc();
      shownmenu=0;
    } else if (sameas(word,"on")) {
      int i;
      for(i=0;i<4;i++)uacc.sysaxs[i]=-1L;
      shownmenu=0;
    } else if (sameas(word,"off")) {
      int i;
      for(i=0;i<4;i++)uacc.sysaxs[i]=0L;
      shownmenu=0;
    } else {
      int i, found=0, matches=0;
      for(i=0;i<COMMANDS;i++){
	if(sameto(word,commands[i].command)){
	  found=i;
	  matches++;
	  break;
	}
      }
      if(!matches){
	prompt(ERRCOM);
      } else if(matches>1){
	prompt(MORCHR,word);
	endcnc();
      } else {
	int j=commands[found].accessflag;
	uacc.sysaxs[j/32]^=(1<<(j%32));
	prompt(HASAXS(uacc.sysaxs,j)?RSSYSOPON:RSSYSOPOFF,commands[i].command);
      }
    }
  }

  if(!userexists(userid)){
    prompt(RSSYSOPDEL,NULL);
    return;
  } else if (!uinsys(userid,0)) {
    useracc temp;

    loaduseraccount(userid,&temp);
    memcpy(temp.sysaxs,uacc.sysaxs,sizeof(temp.sysaxs));
    saveuseraccount(&temp);
  } else {
    memcpy(othruseracc.sysaxs,uacc.sysaxs,sizeof(othruseracc.sysaxs));
    if(injoth(&othruseronl,getmsglang(RSSYSOPNOT,othruseracc.language-1),0))
      prompt(NOTIFIED,othruseracc.userid);
  }
  prompt(RSSYSOPUPD,NULL);
}


void
showlog(char *fname,int p1,int p2,int p3,int err)
{
  char opt;
  char command[256];
  FILE *fp;

  if(!getmenu(&opt,1,p1,0,err,"BE",0,0))return;
  if(opt=='B')sprintf(command,"cat %s",fname);
  else sprintf(command,"tac %s",fname);

  if((fp=popen(command,"r"))==NULL)return;

  nonblocking();

  prompt(p2);
  while(!feof(fp)){
    char line[1024],*cp,s1[80],*s2,c;
    int  flags, sev;

    if(read(0,&c,1))if(c==13||c==10||c==27||c==15||c==3){
      prompt(p3);
      break;
    }
    if(lastresult==PAUSE_QUIT){
      prompt(p3);
      break;
    }

    if(!fgets(line,sizeof(line),fp))break;
    if((cp=strchr(line,'\n'))!=NULL)*cp=0;
    if(sscanf(&line[20],"%04x",&flags)!=1)continue;

    if(flags&AUF_EMERGENCY)sev=2;
    else if(flags&AUF_CAUTION)sev=1;
    else sev=0;

    strncpy(s1,line,68);
    s1[68]=0;
    s2=&line[68];
    prompt(RSAUDITI+sev,s1,s2);
  }
  blocking();
  fclose(fp);
  return;
}


void
rsys_audit()
{
  showlog(AUDITFILE,RSAUDIT1,RSAUDIT2,RSAUDIT3,RSAUDITR);
}


void
rsys_cleanup()
{
  showlog(CLNUPAUDITFILE,RSCLEANUP1,RSCLEANUP2,RSCLEANUP3,RSCLEANUPR);
}


void
rsys_logon()
{
  char *i, c, dev[32], fname[256];
  int  channel;
  struct stat st;

  if(!morcnc())prompt(RSLOGONH);
  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return;
      i=cncword();
    } else {
      prompt(RSLOGONP);
      getinput(0);
      bgncnc();
      i=cncword();
      if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return;
      }
    }
    if((sameas(i,"*")||sameas(i,"all"))){
      strcpy(dev,"*");
      break;
    } else if(sameas(i,"?")){
      int i;
      
      prompt(RSLOGONL1);
      if(!stat(LOGINMSGFILE,&st))prompt(RSLOGONL2A,st.st_size);
      for(i=0;i<numchannels;i++){
	sprintf(fname,TTYINFOFILE,channels[i].ttyname);
	if(!stat(fname,&st))prompt(RSLOGONL2B,channels[i].channel,st.st_size);
      }
      prompt(RSLOGONL3);
      endcnc();
      continue;
    } else if(strstr(i,"tty")==i){
      if(getchannelnum(i)!=-1){
	strcpy(dev,i);
	break;
      } else {
	prompt(GCHANBDV,NULL);
	endcnc();
	continue;
      }
    } else if(sscanf(i,"%x",&channel)==1){
      char *name=getchannelname(channel);
      if(!name){
	prompt(GCHANBCH,NULL);
	endcnc();
	continue;
      } else {
	strcpy(dev,name);
	break;
      }
    } else {
      prompt(GCHANHUH,i);
      endcnc();
      continue;
    }
  }

  if(sameas(dev,"*"))strcpy(fname,LOGINMSGFILE);
  else sprintf(fname,TTYINFOFILE,dev);

  if(!stat(fname,&st)){
    char opt;
    if(!getmenu(&opt,1,0,RSLOGOND,RSLOGONDR,"ED",0,'E'))return;
    if(opt=='D'){
      unlink(fname);
      prompt(RSLOGONDD);
    } else if(opt=='E'){
      char temp[256];
      struct stat st;

      sprintf(temp,TMPDIR"/remsys%05d",getpid());
      symlink(fname,temp);
      
      if(editor(temp,2048)||stat(temp,&st)){
	unlink(temp);
	return;
      }
      unlink(temp);
    }
  } else editor(fname,2048);
}


void
rsys_pageaudit()
{
  char fname[256], s[256], *cp;
  FILE *fp;
  int  filtering=thisuseracc.auditfiltering, i;

  sprintf(fname,TMPDIR"/rsys%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  i=GETSEVERITY(thisuseracc.auditfiltering);

  if(filtering&AUF_INFO)i=SEVI;
  else if(filtering&AUF_CAUTION)i=SEVC;
  else if(filtering&AUF_EMERGENCY)i=SEVE;
  else i=SEVO;

  fprintf(fp,"%s\n",getmsg(i));
  fprintf(fp,"%s\n",(filtering&AUF_ACCOUNTING)?"on":"off");
  fprintf(fp,"%s\n",(filtering&AUF_EVENT)?"on":"off");
  fprintf(fp,"%s\n",(filtering&AUF_OPERATION)?"on":"off");
  fprintf(fp,"%s\n",(filtering&AUF_SECURITY)?"on":"off");
  fprintf(fp,"%s\n",(filtering&AUF_TRANSFER)?"on":"off");
  fprintf(fp,"%s\n",(filtering&AUF_USERLOG)?"on":"off");
  fprintf(fp,"%s\n",(filtering&AUF_OTHER)?"on":"off");
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("remsys",RSAPGVT,RSAPGLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  filtering=-1;
  for(i=0;i<11;i++){
    if(!fgets(s,sizeof(s),fp))break;
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0){
      filtering&=~AUF_SEVERITY;
      if(!strcmp(s,getmsg(SEVE)))
	filtering|=AUF_EMERGENCY;
      else if(!strcmp(s,getmsg(SEVC)))
	filtering|=AUF_EMERGENCY|AUF_CAUTION;
      else if(!strcmp(s,getmsg(SEVI)))
	filtering|=AUF_SEVERITY;
    } else if(i==1 && sameas(s,"OFF"))filtering&=~AUF_ACCOUNTING;
    else if(i==2 && sameas(s,"OFF"))filtering&=~AUF_EVENT;
    else if(i==3 && sameas(s,"OFF"))filtering&=~AUF_OPERATION;
    else if(i==4 && sameas(s,"OFF"))filtering&=~AUF_SECURITY;
    else if(i==5 && sameas(s,"OFF"))filtering&=~AUF_TRANSFER;
    else if(i==6 && sameas(s,"OFF"))filtering&=~AUF_USERLOG;
    else if(i==7 && sameas(s,"OFF"))filtering&=~AUF_OTHER;
  }
  fclose(fp);
  unlink(fname);

  if(sameas(s,"CANCEL")){
    prompt(RSAPGCAN);
    return;
  }
  prompt(RSAPGOK);
  thisuseracc.auditfiltering=filtering;
}


void
filter_audit(char *keyword, int filtering, int reverse)
{
  FILE *fp;
  char lookfor[256];
  int  found=0;

  lookfor[0]=0;
  if(keyword)strcpy(lookfor,keyword);
  phonetic(lookfor);

  /* Open the file, in reverse if required */

  if(!reverse){
    if((fp=fopen(AUDITFILE,"r"))==NULL){
      logerrorsys("Unable to open Audit Trail!");
      return;
    }
  } else {
    if((fp=popen("tac 2>/dev/null "AUDITFILE,"r"))==NULL){
      logerrorsys("Unable to popen() Audit Trail with tac!");
      return;
    }
  }


  /* Start searching */

  nonblocking();

  while(!feof(fp)){
    char line[1024],*cp,s1[80],*s2,c;
    int  flags, sev;

    if(read(0,&c,1))if(c==13||c==10||c==27||c==15||c==3){
      prompt(AUDSCAN);
      goto done;
    }
    if(lastresult==PAUSE_QUIT){
      prompt(AUDSCAN);
      goto done;
    }

    if(!fgets(line,sizeof(line),fp))continue;
    if((cp=strchr(line,'\n'))!=NULL)*cp=0;

    if(sscanf(&line[20],"%04x",&flags)!=1)continue;
    if(((flags&filtering)&AUF_SEVERITY)==0 ||
       ((flags&filtering)&~AUF_SEVERITY)==0)continue;

    if(lookfor[0]){
      char tmp[1024];
      strcpy(tmp,line);
      phonetic(tmp);
      if(!strstr(tmp,lookfor))continue;
    }

    if(!found)prompt(AUDSRCH);
    found|=1;
    strncpy(s1,line,68);
    s1[68]=0;
    s2=&line[68];

    if(flags&AUF_EMERGENCY)sev=2;
    else if(flags&AUF_CAUTION)sev=1;
    else sev=0;

    prompt(RSAUDITI+sev,s1,s2);
  }

  prompt(found?AUDSEND:AUDNF);

done:
  nonblocking();
  if(!reverse)fclose(fp);
  else pclose(fp);
}


void
rsys_filtaud()
{
  char fname[256], s[256], *cp;
  FILE *fp;
  int  filtering=-1, reverse=1, i;
  char keyword[256];

  sprintf(fname,TMPDIR"/rsys%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  for(i=0;i<11;i++)fprintf(fp,"\non");
  fprintf(fp,"\nOK button\nCancel button\n");
  fclose(fp);

  dataentry("remsys",RSFLTVT,RSFLTLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<15;i++){
    if(!fgets(s,sizeof(s),fp))break;
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0)strcpy(keyword,s);
    else if(i==1 && sameas(s,"OFF"))filtering&=~AUF_INFO;
    else if(i==2 && sameas(s,"OFF"))filtering&=~AUF_CAUTION;
    else if(i==3 && sameas(s,"OFF"))filtering&=~AUF_EMERGENCY;
    else if(i==4 && sameas(s,"OFF"))filtering&=~AUF_ACCOUNTING;
    else if(i==5 && sameas(s,"OFF"))filtering&=~AUF_EVENT;
    else if(i==6 && sameas(s,"OFF"))filtering&=~AUF_OPERATION;
    else if(i==7 && sameas(s,"OFF"))filtering&=~AUF_SECURITY;
    else if(i==8 && sameas(s,"OFF"))filtering&=~AUF_TRANSFER;
    else if(i==9 && sameas(s,"OFF"))filtering&=~AUF_USERLOG;
    else if(i==10 && sameas(s,"OFF"))filtering&=~AUF_OTHER;
    else if(i==11 && sameas(s,"OFF"))reverse=0;
  }
  fclose(fp);
  unlink(fname);

  if(sameas(s,"CANCEL"))return;
  filter_audit(keyword,filtering,reverse);
}


void
rsys_security()
{
  filter_audit("",AUF_SEVERITY|AUF_SECURITY,1);
}


void
rsys_signups()
{
  filter_audit(AUS_SIGNUP,-1,1);
}


