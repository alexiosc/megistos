/*****************************************************************************\
 **                                                                         **
 **  FILE:     globalcmd.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Handle BBS global commands                                   **
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
 * Revision 1.1  2001/04/16 14:49:35  alexios
 * Initial revision
 *
 * Revision 0.12  2000/01/06 11:34:26  alexios
 * When a user pages the Sysop at the main console (/p sysop when
 * Sysop isn't online), the event is flagged in the user's online
 * record. This allows the console and other programs to monitor
 * pages to the console and notify the operator.
 *
 * Revision 0.11  1999/08/13 16:56:08  alexios
 * Kludged/fixed (pick one) wrong behaviour in gcs_recent() that
 * printed ffffffff (-1) if the channel number couldn't be found.
 * It prints 00 now, which isn't very good if you have a channel
 * by that number. Won't cause problems, though.
 *
 * Revision 0.10  1999/07/28 23:06:34  alexios
 * Remnants of a debugging session caused a new version here.
 *
 * Revision 0.9  1999/07/18 21:01:53  alexios
 * Changed one fatal() call to fatalsys().
 *
 * Revision 0.8  1998/12/27 14:31:16  alexios
 * Added autoconf support. Various minor fixes. Added support
 * for new getlinestatus(). Fixed locking for the remsys command.
 * Fixed pipe calls to tac in /recent command so that pipe errors
 * aren't reported to the user.
 *
 * Revision 0.7  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.6  1997/12/02 20:42:14  alexios
 * Fixed slight bug in /audit command.
 *
 * Revision 0.5  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/06 16:52:10  alexios
 * Changed USY_AUDITPAGE to USY_PAGEAUDIT.
 *
 * Revision 0.3  1997/11/05 10:58:35  alexios
 * Moved the /r (registry lookup) command to this file.
 * Abolished the registry daemon (regd). As a result, the first
 * registry lookup per user per module may be slightly slower than
 * the rest.
 * Changed gcs_audit() to set severity filtering, not just turn
 * audit notification on and off. Added a help prompt and made sure
 * no mere mortals can access this command (huge bug there, before).
 *
 * Revision 0.2  1997/09/12 12:49:41  alexios
 * Added functionality to the page global command so that the
 * pager's and pagee's sexes are made obvious for languages that
 * need them to form correct sentences.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
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
#define WANT_STRINGS_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_SHM_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>

#include "config.h"
#include "bbs.h"
#include "registry.h"
#include "mbk_sysvar.h"

#define __REGISTRY_UNAMBIGUOUS__
#include "mbk_registry.h"

typedef int (*gcs_t)(void);
gcs_t *gcservers=NULL;
int  gcsnum=0;


#define USERPAGED (othruseronl.onlinetime-othruseronl.lastpage \
		   <othruseracc.pagetime)
#define ISYSOP    (hassysaxs(&thisuseracc,USY_MASTERKEY))


int
gcs_time()
{
  long date,time;
  char month[64];

  if(!margc) return 0;
  else if(margc==1 && (sameas(margv[0],"/time")||sameas(margv[0],"/t"))){
    date=today();
    time=now();
    setmbk(sysblk);
    strcpy(month,stgopt(tdmonth(date)+DTCJAN));
    prompt(TIME,tdday(date),month,tdyear(date),strtime(now(),1));
    rstmbk();
    return 1;
  } else return 0;
}


int
gcs_hash()
{
  int               i;
  char              majst[32],minst[32],user[24];
  char              *lonstr, *supstr, *nixstr;
  int               baud;

  if(!margc) return 0;
  else if(margc!=1 || !sameas(margv[0],"/#")) return 0;

  setmbk(sysblk);
  prompt(WHOHDR,NULL);
  lonstr=stgopt(WHOLON);
  supstr=stgopt(WHOSUP);
  nixstr=stgopt(WHONIX);

  for(i=0;i<numchannels;i++){
    char fname[256], line[256];
    FILE *fp;

    sprintf(fname,"%s/.status-%s",CHANDEFDIR,channels[i].ttyname);
    if((fp=fopen(fname,"r"))==NULL) {
      /*int i=errno;*/
      continue;
    }
      
    fgets(line,256,fp);
    fclose(fp);
    if(sscanf(line,"%s %s %d %s",majst,minst,&baud,user)!=4) continue;
    if(!strcmp(minst,"LOGIN")){
      prompt(WHOLINE1,channels[i].channel,lonstr,baudstg(baud));
    } else if(!strcmp(minst,"USER")) {
      if(!strcmp(user,"[SIGNUP]")){
	prompt(WHOLINE1,channels[i].channel,supstr,baudstg(baud));
      } else if(!strcmp(user,"[UNIX]")){
	prompt(WHOLINE1,channels[i].channel,nixstr,baudstg(baud));
      } else {
	struct shmuserrec *ushm=NULL;

	if(uinsystem(user,!ISYSOP,&ushm)){
	  char status, invis;

	  if(!ushm) continue;

	  if(ushm->onl.flags&OLF_BUSY) status='B';
	  else if(ushm->onl.pagestate==PGS_OFF) status='P';
	  else status=' ';

	  if(ushm->onl.flags&OLF_INVISIBLE) invis='I';
	  else invis=' ';
	  prompt(WHOLINE2,channels[i].channel,ushm->onl.userid,baudstg(baud),
		 status,invis,ushm->onl.descr[(int)thisuseracc.language-1]);
	}
	shmdt((char *)ushm);
      }
    }
  }

  rstmbk();
  free(lonstr);
  free(supstr);
  free(nixstr);
  return 1;
}


int
gcs_invis()
{
  if(margc==1 && sameas(margv[0],"/invis")){
    if(hassysaxs(&thisuseracc,USY_INVIS)){
      thisuseronl.flags^=OLF_INVISIBLE;
      setmbk(sysblk);
      prompt((thisuseronl.flags&OLF_INVISIBLE)?INVON:INVOFF);
      rstmbk();
      return 1;
    }
  }
  return 0;
}


static int
dopage()
{
  if(!haskey(&thisuseracc,sysvar->pgovkey)){
    if(othruseronl.pagestate==PGS_ON && USERPAGED){
      char tmp[80];
      strcpy(tmp,getpfix(SEXM,othruseracc.sex==USX_MALE));
      prompt(PAGL2M,tmp,othruseracc.userid,
	     othruseracc.pagetime,getpfix(MINSING,othruseracc.pagetime==1));
      return 0;
    } else if(othruseronl.pagestate==PGS_OFF){
      prompt(PAGOFF,
	     getpfix(SEXM,othruseracc.sex==USX_MALE),
	     othruseracc.userid);
      return 0;
    }
  }
  
  if (!(othruseronl.flags&OLF_INVISIBLE)||ISYSOP){
    char *pgfrom=(char *)&thisuseronl.descr[(int)othruseracc.language-1];
    char injbuf[MSGBUFSIZE];
    
    if (!hassysaxs(&othruseracc,USY_MASTERKEY)
	&&(thisuseronl.flags&OLF_INVISIBLE)) {
      prompt(URINVS,NULL);
      return 0;
    } else if (margc==2) {
      sprintf(injbuf,getmsglang(othruseronl.flags&OLF_BUSY?PAGMSG1:PAGMSG2,
				othruseracc.language-1),
	      getpfix(SEXM,thisuseracc.sex==USX_MALE),
	      thisuseracc.userid,pgfrom);
    } else {
      rstrin();
      sprintf(injbuf,getmsglang(othruseronl.flags&OLF_BUSY?PAGNOT1:PAGNOT2,
				othruseracc.language-1),
	      getpfix(SEXM,thisuseracc.sex==USX_MALE),
	      thisuseracc.userid,pgfrom,margv[2]);
    }

    if (!(othruseronl.flags&OLF_BUSY)) {
      prompt(PAGEOK,getpfix(ACKM,othruseracc.sex==USX_MALE),
	     othruseracc.userid);
      injoth(&othruseronl,injbuf,0);
      othruseronl.lastpage=othruseronl.onlinetime;
      return 1;
    } else if (othruseronl.pagestate==PGS_STORE||
	       haskey(&thisuseracc,sysvar->pgovkey)){
      prompt(PAGNPST,
	     getpfix(NOMM,othruseracc.sex==USX_MALE),
	     othruseracc.userid);
      injoth(&othruseronl,injbuf,1);
      othruseronl.lastpage=othruseronl.onlinetime;
      return 1;
    } else prompt(PAGNPS,
		  getpfix(ACKM,othruseracc.sex==USX_MALE),
		  othruseracc.userid);
  }
  return 0;
}


int
gcs_page()
{
  if(margc&&sameas(margv[0],"/p")){
    setmbk(sysblk);
    if (!haskey(&thisuseracc,sysvar->pagekey)){
      prompt(CANTPG,NULL);
    } else if (margc==1){
      prompt(PAGFMT,NULL);
    } else if (!uinsys(margv[1],!ISYSOP)){
      if (sameas(margv[1],"on")){
	thisuseronl.pagestate=PGS_ON;
	prompt(PAGTON,
	       thisuseracc.pagetime,
	       getpfix(MINSING,thisuseracc.pagetime==1));
      } else if (sameas(margv[1],"off")) {
	thisuseronl.pagestate=PGS_OFF;
	prompt(PAGTOF,NULL);
      } else if (sameas(margv[1],"ok")) {
	thisuseronl.pagestate=PGS_OK;
	prompt(PAGTOK,NULL);
      } else if (sameas(margv[1],"store")) {
	thisuseronl.pagestate=PGS_STORE;
	prompt(PAGTST,NULL);
      } else if (sameas(margv[1],SYSOP)) {
	prompt(PGSYSOP,NULL);
	thisuseronl.lastconsolepage=time(NULL);
      } else if(sameas(margv[1],"all")&&(haskey(&thisuseracc,sysvar->pallkey))){
	int i, count=0;
	struct linestatus status;

	for(i=0;i<numchannels;i++){
	  if(getlinestatus(channels[i].ttyname,&status)<0)continue;
	  
	  if(status.result==LSR_USER){
	    if(sameas(status.user,thisuseracc.userid))continue;
	    if(uinsys(status.user,!ISYSOP)){
	      if(!othrshm) continue;
	      count+=dopage();
	    }
	  }
	}

	if (!count) prompt(PALLNC,NULL);
      } else {
	int i, count=0;
	char userid[25];
	struct linestatus status;

	for(i=0;i<numchannels;i++){
	  if(getlinestatus(channels[i].ttyname,&status)<0)continue;
	  
	  if(status.result==LSR_USER){
	    if(uinsys(status.user,!ISYSOP)){
	      if(!othrshm) continue;
	      if(othruseronl.flags&OLF_INVISIBLE && (!ISYSOP))continue;
	      if(sameto(margv[1],othruseronl.userid)){
		count++;
		strcpy(userid,othruseronl.userid);
	      }
	    }
	  }
	}

	if (!count) {
	  prompt(PAGNON,margv[1]);
	} else if (count > 1) {
	  prompt(PAGMOM,margv[1]);
	} else {
	  uinsys(userid,!ISYSOP);
	  dopage();
	}
      }
    } else dopage();
    rstmbk();
    return 1;
  }
  return 0;
}


int
gcs_crdavail()
{
  if(margc==1 && sameas(margv[0],"/$")){
    char crdpf[MSGBUFSIZE], minpf[MSGBUFSIZE];

    setmbk(sysblk);
    strcpy(minpf,getpfix(MINSING,thisuseronl.onlinetime==1));
    strcpy(crdpf,getpfix(CRDSING,thisuseracc.credits==1));
    prompt(CRDAVAIL,thisuseronl.onlinetime,minpf,
	   thisuseracc.credits,crdpf);
    rstmbk();
    return 1;
  }
  return 0;
}



static promptblk *regmsg=NULL;
static int template [3][30];


int
gcs_registry()
{
  struct stat st;
  char fname[256], userid[32];

  if(margc==2 && sameas(margv[0],"/r")){
    setmbk(sysblk);
    strcpy(userid,margv[1]);
    uidxref(userid,0);
    if(!userexists(userid)){ 
      prompt(REGERR);
      rstmbk();
      return 1;
    }
    sprintf(fname,"%s/%s",REGISTRYDIR,userid);
    if(stat(fname,&st)){
      prompt(REGERR);
      rstmbk();
      return 1;
    }

    if(!regmsg){
      int i,j;
      regmsg=opnmsg("registry");
      for(i=0;i<3;i++)for(j=0;j<30;j++)
	template[i][j]=numopt(REGISTRY_T1F1+i*30+j,0,255);
    }

    {
      FILE *fp;
      char *format[33];
      struct registry registry;
      int i,j,pos;

      setmbk(regmsg);
      memset(&registry,0,sizeof(registry));

      sprintf(fname,"%s/%s",REGISTRYDIR,userid);
      if((fp=fopen(fname,"r"))==NULL){
	sprompt(outbuf,REGISTRY_UIDERR);
	injoth(&othruseronl,outbuf,0);
	return 1;
      }

      if(fread(&registry,sizeof(struct registry),1,fp)!=1){
	fatalsys("Unable to read registry %s",fname);
      }
      registry.template=registry.template%3;
      fclose(fp);

      format[0]=userid;
      for(i=pos=0,j=1;i<30;pos+=template[registry.template][i++]+1){
	if(template[registry.template][i])format[j++]=&registry.registry[pos];
      }
      format[j++]=registry.summary;
      format[j]=NULL;
      vsprintf(outbuf,getmsg(REGISTRY_T1LOOKUP+registry.template),format);
      print(outbuf);
    }
    
    return 1;
  } else if(margc==1 && sameas(margv[0],"/r")){
    setmbk(sysblk);
    prompt(REGHELP);
    rstmbk();
    return 1;
  }
  rstmbk();
  return 0;
}


int
gcs_cookie()
{
  if(margc==1 && sameas(margv[0],"/cookie") && sysvar->glockie){
    char command[256];

    sprintf(command,"%s/cookie",BINDIR);
    system(command);
    return 1;
  } else return 0;
}


int
gcs_gdet()
{
  int  kgdnam, kgdcom, kgdadr, kgdpho, kgdage, kgdsex;
  int  kgdpss, kgdpass;
  static char userid[32];
  useracc usracc, *uacc=&usracc;
  char wh[80],age[80],sex[80];
  char s1[80],s2[80],s3[80],s4[80];
  char d1[80],d2[80];
  char sys[80],ns[80],lang[80];

  if(margc!=2||(!sameas(margv[0],"/l"))||(!hassysaxs(&thisuseracc,USY_GDET))){
    return 0;
  }

  memset(userid,0,sizeof(userid));
  strcpy(userid,margv[1]);
  uidxref(userid,0);
  if(!userexists(userid)){
    setmbk(sysblk);
    prompt(GDETUR,userid);
    rstmbk();
    return 1;
  }
  if(!uinsys(userid,0))loaduseraccount(userid,uacc);
  else uacc=&othruseracc;

  setmbk(sysblk);

  kgdnam=numopt(KGDNAM,0,129);
  kgdcom=numopt(KGDCOM,0,129);
  kgdadr=numopt(KGDADR,0,129);
  kgdpho=numopt(KGDPHO,0,129);
  kgdage=numopt(KGDAGE,0,129);
  kgdsex=numopt(KGDSEX,0,129);
  kgdpss=numopt(KGDPSS,0,129);
  kgdpass=ynopt(KGDPASS);

  strcpy(wh,getmsg(GDETNAX));
  strcpy(sex,uacc->sex==USX_MALE?getmsg(GDETM):getmsg(GDETF));
  memset(s1,0,sizeof(s1));
  if(uacc->flags&UFL_SUSPENDED)strcpy(s1,getmsg(GDETSUSP));
  memset(s2,0,sizeof(s2));
  if(uacc->flags&UFL_EXEMPT)strcpy(s2,getmsg(GDETXMPT));
  memset(s3,0,sizeof(s3));
  if(uacc->flags&UFL_DELETED)strcpy(s3,getmsg(GDETDEL));
  memset(s4,0,sizeof(s3));
  if(uacc->sysaxs[0]||uacc->sysaxs[1]||uacc->sysaxs[2])
    strcpy(s4,getmsg(GDETOP));
  strcpy(sys,getmsg(GDETS1+uacc->system-1));
  ns[0]=0;
  if(uacc->prefs&UPF_NONSTOP)strcpy(ns,getmsg(GDETNST));
  strcpy(lang,getmsg(GDETL1+uacc->language-1));
  sprintf(age,"%d",uacc->age);

  strcpy(d1,strdate(uacc->datecre));
  strcpy(d2,(uacc->datelast>=0)?strdate(uacc->datelast):"");
  prompt(GDET,userid,
	 d1,s1,s2,
	 d2,s3,s4,
	 (haskey(&thisuseracc,kgdnam)?uacc->username:wh),
	 (haskey(&thisuseracc,kgdcom)?uacc->company:wh),
	 (haskey(&thisuseracc,kgdadr)?uacc->address1:wh),
	 (haskey(&thisuseracc,kgdadr)?uacc->address2:wh),
	 (haskey(&thisuseracc,kgdpho)?uacc->phone:wh),
	 (haskey(&thisuseracc,kgdage)?age:wh),
	 (haskey(&thisuseracc,kgdsex)?sex:wh),
	 sys,uacc->scnwidth,uacc->scnheight,ns,
	 lang,uacc->curclss,
	 ((!kgdpass)&&haskey(&thisuseracc,kgdpss)?uacc->passwd:wh),
	 uacc->credits,uacc->totpaid);

  rstmbk();
  return 1;
}


int
gcs_remsys()
{
  if(margc==1 &&
     (sameas(margv[0],"/olympos")||sameas(margv[0],"/hypermenu")||
      sameas(margv[0],"/@"))){
    int i,j;
    
    for(i=j=0;i<sizeof(thisuseracc.sysaxs)/sizeof(long);i++)
      j|=thisuseracc.sysaxs[i];

    if(j){
      char dummy[16];
      char lock[256];
      int i;

      sprintf(lock,"LCK-remsys-%s",thisuseronl.channel);
      i=checklock(lock,dummy);
      if(i>0 || i==LKR_OWN){
	setmbk(sysblk);
	prompt(REMSERR);
	rstmbk();
	return 1;
      }
      runmodule(REMSYSBIN);
      rmlock(lock);
      return 1;
    }
  }
  return 0;
}


int
gcs_go()
{
  if(margc==2 && sameas(margv[0],"/go")){
    gopage(margv[1]);
    return 1;
  }
  return 0;
}


int
gcs_recent()
{
  FILE *fp;
  char command[256];
  int  line,day=-1,limit=0,changes=0,c;

  if(margc>=1 && (sameas(margv[0],"/recent")||sameas(margv[0],"/rc"))){
    if(margc==2 && (sameas(margv[1],"help")||sameas(margv[1],"?"))){
      setmbk(sysblk);
      prompt(RCNTHLP);
      rstmbk();
      endcnc();
      return 1;
    } else if(margc==1||(margc==2 && (limit=atoi(margv[1]))!=0)){
      setmbk(sysblk);
      prompt(LSTHDR);
      sprintf(command,"tac %s 2>/dev/null",RECENTFILE);
      if((fp=popen(command,"r"))==NULL)return 0;
      line=0;
      while(!feof(fp)){
	char user[32],tty[32],date[32],tim1[32],tim2[32];
	int delta;
	time_t t1,t2;
	struct tm *dt;
	
	if(lastresult==PAUSE_QUIT)break;
	if(fscanf(fp,"%s %s %lx %lx\n",user,tty,&t1,&t2)!=4)break;
	dt=localtime(&t1);
	strcpy(date,strdate(makedate(dt->tm_mday,dt->tm_mon+1,1900+dt->tm_year)));
	strcpy(tim1,strtime(maketime(dt->tm_hour,dt->tm_min,dt->tm_sec),1));
	dt=localtime(&t2);
	strcpy(tim2,strtime(maketime(dt->tm_hour,dt->tm_min,dt->tm_sec),1));
	delta=t2-t1;
	line++;
	if(limit&&(line>limit))break;
	else if(!limit){
	  if((day!=-1)&&(dt->tm_mday!=day))changes++;
	  if(changes>=2)break;
	}
	if((c=getchannelnum(tty))<0)c=0;
	prompt(LSTLIN,user,c,date,tim1,tim2,
	       delta/3600,(delta%3600)/60,delta%60);
	day=dt->tm_mday;
      }
      prompt(RCFTR,line);
      rstmbk();
      pclose(fp);
      endcnc();
      return 1;
    } else if(margc==2&&uidxref(margv[1],0)){
      struct stat st;
      useracc user;

      sprintf(command,"%s/%s",RECENTDIR,margv[1]);
      if(stat(command,&st)){
	setmbk(sysblk);
	prompt(UNKUSR,margv[1]);
	rstmbk();
	endcnc();
	return 1;
      }
      loaduseraccount (margv[1], &user);
      setmbk(sysblk);
      endcnc();
      prompt(USRHDR,margv[1],user.connections);
      sprintf(command,"tac %s/%s 2>/dev/null",RECENTDIR,margv[1]);
      if((fp=popen(command,"r"))==NULL)return 0;
      line=0;
      while(!feof(fp)){
	char tty[32],date[32],tim1[32],tim2[32];
	int delta;
	time_t t1,t2;
	struct tm *dt;
	
	if(lastresult==PAUSE_QUIT)break;
	if(fscanf(fp,"%s %lx %lx\n",tty,&t1,&t2)!=3)break;
	dt=localtime(&t1);
	strcpy(date,strdate(makedate(dt->tm_mday,dt->tm_mon+1,1900+dt->tm_year)));
	strcpy(tim1,strtime(maketime(dt->tm_hour,dt->tm_min,dt->tm_sec),1));
	dt=localtime(&t2);
	strcpy(tim2,strtime(maketime(dt->tm_hour,dt->tm_min,dt->tm_sec),1));
	delta=t2-t1;
	if((c=getchannelnum(tty))<0)c=0;
	prompt(USRLIN,c,date,tim1,tim2,
	       delta/3600,(delta%3600)/60,delta%60);
	if(++line>=RECENT_ENTRIES)break;
      }
      prompt(URCFTR);
      rstmbk();
      pclose(fp);
      endcnc();
      return 1;
    } else if(margc==2){
      setmbk(sysblk);
      prompt(UNKUSR,margv[1]);
      rstmbk();
      endcnc();
      return 1;
    }
  }
  return 0;
}


int
gcs_license()
{
  if(!margc) return 0;
  else if(margc==1 && (sameas(margv[0],"/license")||sameas(margv[0],"/gpl"))){
    char fname[256];
    strcpy(fname,DOCDIR"/COPYING");
    printfile(fname);
    return 1;
  } else if(margc==1 && (sameas(margv[0],"/rules")||sameas(margv[0],"/conditions"))){
    char fname[256];
    strcpy(fname,DOCDIR"/RULES");
    printfile(fname);
    return 1;
  } else return 0;
}


void
addgcs(gcs_t gcs){
  gcsnum++;
  if((gcservers=realloc(gcservers,sizeof(void *)*gcsnum))==NULL){
    fatal("Can't allocate global command table space!",NULL);
  }
  gcservers[gcsnum-1]=gcs;
}


int
gcs_audit()
{
  if(!hassysaxs(&thisuseracc,USY_PAGEAUDIT))return 0;
  if(margc&&sameas(margv[0],"/audit")){
    if(margc==1){
      setmbk(sysblk);
      prompt(AUDITHLP);
      rstmbk();
      return 1;
    } else if(margc==2){
      setmbk(sysblk);
      if(sameas("o",margv[1])){
	thisuseracc.auditfiltering&=~AUF_SEVERITY;
	prompt(AUDITOFF);
      } else if(sameto("e",margv[1])){
	thisuseracc.auditfiltering&=~AUF_SEVERITY;
	thisuseracc.auditfiltering|=AUF_EMERGENCY;
	prompt(AUDITE);
      } else if(sameto("c",margv[1])){
	thisuseracc.auditfiltering&=~AUF_SEVERITY;
	thisuseracc.auditfiltering|=AUF_EMERGENCY|AUF_CAUTION;
	prompt(AUDITC);
      } else if(sameto("i",margv[1])){
	thisuseracc.auditfiltering|=AUF_SEVERITY;
	prompt(AUDITI);
      } else prompt(AUDITHLP);
    } else prompt(AUDITHLP);
    rstmbk();
    return 1;
  }
  return 0;
}


void
initgcs(){
  gcs_t gcs[]={
    gcs_time,
    gcs_hash,
    gcs_invis,
    gcs_page,
    gcs_crdavail,
    gcs_registry,
    gcs_cookie,
    gcs_gdet,
    gcs_remsys,
    gcs_go,
    gcs_recent,
    gcs_license,
    gcs_audit,
    NULL
  };
  int i=0;

  while(gcs[i]){
    addgcs(gcs[i]);
    i++;
  }
}


int
handlegcs()
{
  int i;
  int (*gcserver)(void);
  promptblk *temp;

  temp=curblk;
  parsin();
  for(i=0;i<gcsnum;i++){
    gcserver=gcservers[i];
    if(gcserver()){
      setmbk(temp);
      return 1;
    }
  }
  setmbk(temp);
  return 0;
}
