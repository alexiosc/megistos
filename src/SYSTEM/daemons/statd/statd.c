/*****************************************************************************\
 **                                                                         **
 **  FILE:     statd.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 94, Version 0.01                                 **
 **  PURPOSE:  Statistics daemon                                            **
 **  NOTES:    Statistics gathered:                                         **
 **              * Time & Credits used / hour (aka DAYSTATS)                **
 **              * Time, Credits & Calls / channel (aka TTYSTATS)           **
 **              * Time & Credits used / user class (aka CLSSTATS)          **
 **              * Time, Credits & Calls / baud rate (aka BAUDSTATS)        **
 **              * Time & Credits used / module (aka MODSTATS)              **
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
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 22:07:05  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.4  1998/12/27 16:28:44  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 0.3  1998/07/24 10:28:18  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:04:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:19:16  alexios
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
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_SIGNAL_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"


/*#define DEBUG 1*/

#ifdef DEBUG
#define debug(s) fprintf(stderr,s)
#define debug2(s,f) fprintf(stderr,s,f)
#else
#define debug(s)
#define debug2(s,f)
#endif

#define MAXCLSS 128
#define MAXTTYS 256
#define MAXBAUDS 32
#define MAXMODS 128

#define SLEEPTIME    1000000 /* useconds */
#define TICKTIME     12      /* run stuff every 12 secs */


promptblock_t         *msg;
time_t            classtime=0;
time_t            channeltime=0;
time_t            daystattime=0;
time_t            ttystattime=0;
time_t            clsstattime=0;
time_t            baudstattime=0;
time_t            modstattime=0;
struct clsstats   clsstats[MAXCLSS];
int               numclsstats=0;
struct ttystats   ttystats[MAXTTYS];
int               numttystats=0;
struct baudstats  baudstats[MAXBAUDS];
int               numbaudstats=0;
struct usagestats daystats[24];
struct modstats   modstats[MAXMODS];
int               nummodstats=0;


void
storepid()
{
  FILE *fp;
  char fname[256];
  
  sprintf(fname,"%s/statd.pid",mkfname(BBSETCDIR));
  if((fp=fopen(fname,"w"))==NULL)return;
  fprintf(fp,"%d",getpid());
  fclose(fp);
  chmod(fname,0600);
  chown(fname,0,0);
}


void
refreshclasses()
{
  struct stat s;
  stat(mkfname(CLASSFILE),&s);
  if (s.st_ctime!=classtime) {
    debug("REFRESHING CLASSES...\n");
    classtime=s.st_ctime;
    mod_init(INI_CLASSES);
  }
}


void
refreshchannels()
{
  struct stat s;
  if(stat(mkfname(CHANDEFFILE),&s))return;
  if (s.st_ctime!=channeltime) {
    debug("REFRESHING CHANNELS...\n");
    channeltime=s.st_ctime;
    chan_init();
  }
}


void
readdaystats()
{
  FILE *fp;
  int i;
  struct stat s;

  if(stat(mkfname(DAYSTATFILE),&s)){
    memset(daystats,0,sizeof(daystats));
    return;
  }
  if (s.st_ctime==daystattime)return;
  debug("READING DAY STATS...\n");
  memset(daystats,0,sizeof(daystats));
  if((fp=fopen(mkfname(DAYSTATFILE),"r"))==NULL)return;
  for(i=0;i<24;i++){
    fscanf(fp,"%d %d\n",&daystats[i].credits,&daystats[i].minutes);
  }
  fclose(fp);
}


void
writedaystats()
{
  FILE *fp;
  int i;
  struct stat s;

  debug("WRITING DAY STATS...\n");
  if((fp=fopen(mkfname(DAYSTATFILE),"w"))==NULL){
    error_intsys("Unable to write %s",mkfname(DAYSTATFILE));
    return;
  }
  for(i=0;i<24;i++){
    fprintf(fp,"%d %d\n",daystats[i].credits,daystats[i].minutes);
  }
  fclose(fp);
  if(!stat(mkfname(DAYSTATFILE),&s))daystattime=s.st_ctime;
}


void
readttystats()
{
  FILE *fp;
  struct stat s;

  if(stat(mkfname(TTYSTATFILE),&s)){
    numttystats=0;
    return;
  }
  if (s.st_ctime==ttystattime)return;
  debug("READING TTY STATS...\n");
  numttystats=0;
  if((fp=fopen(mkfname(TTYSTATFILE),"r"))==NULL)return;
  while(!feof(fp)){
    struct ttystats *tty=&ttystats[numttystats];
    int i=fscanf(fp,"%s %x %d %d %d\n",tty->name,&tty->channel,
		 &tty->credits,&tty->minutes,&tty->calls);
    if(numttystats>=MAXTTYS)break;
    if(i==5)numttystats++;
  }
  fclose(fp);
}


void
writettystats()
{
  FILE *fp;
  int i;
  struct stat s;

  debug("WRITING TTY STATS...\n");
  if((fp=fopen(mkfname(TTYSTATFILE),"w"))==NULL){
    error_intsys("Unable to write %s",mkfname(TTYSTATFILE));
    return;
  }
  for(i=0;i<numttystats;i++){
    fprintf(fp,"%s %x %d %d %d\n",ttystats[i].name,
	    ttystats[i].channel,ttystats[i].credits,
	    ttystats[i].minutes,ttystats[i].calls);
  }
  fclose(fp);
  if(!stat(mkfname(TTYSTATFILE),&s))ttystattime=s.st_ctime;
}


int
findtty(char *tty)
{
  int found=0,i;

  for(i=0;i<numttystats;i++){
    if(!strcmp(ttystats[i].name,tty)){
      found=1;
      break;
    }
  }
  debug2("FOUND TTYSTAT: %s\n",tty);
  if(found)return i;

  if(numttystats>=MAXTTYS)return -1;
  memset(&ttystats[numttystats],0,sizeof(struct ttystats));
  strcpy(ttystats[numttystats].name,tty);
  ttystats[numttystats].channel=chan_getnum(tty);
  numttystats++;
  debug2("CREATED TTYSTAT: %s\n",tty);
  return numttystats-1;
}


void
readclsstats()
{
  FILE *fp;
  struct stat s;

  if(stat(mkfname(CLSSTATFILE),&s)){
    if(clsstats)free(clsstats);
    numclsstats=0;
    return;
  }
  if (s.st_ctime==clsstattime)return;
  debug("READING CLASS STATS...\n");
  numclsstats=0;
  if((fp=fopen(mkfname(CLSSTATFILE),"r"))==NULL)return;
  while(!feof(fp)){
    int i=fscanf(fp,"%s %d %d\n",
		 clsstats[numclsstats].name,
		 &clsstats[numclsstats].credits,
		 &clsstats[numclsstats].minutes);

    if(numclsstats>=MAXCLSS)break;
    if(i==3)numclsstats++;
  }
  fclose(fp);
}


void
writeclsstats()
{
  FILE *fp;
  int i;
  struct stat s;

  debug("WRITING CLASS STATS...\n");
  if((fp=fopen(mkfname(CLSSTATFILE),"w"))==NULL){
    error_intsys("Unable to write %s",mkfname(CLSSTATFILE));
    return;
  }
  for(i=0;i<numclsstats;i++){
    fprintf(fp,"%s %d %d\n",clsstats[i].name,clsstats[i].credits,
	    clsstats[i].minutes);
  }
  fclose(fp);
  if(!stat(mkfname(CLSSTATFILE),&s))clsstattime=s.st_ctime;
}


int
findcls(char *cls)
{
  int found=0,i;

  for(i=0;i<numclsstats;i++){
    if(!strcmp(clsstats[i].name,cls)){
      found=1;
      break;
    }
  }
  debug2("FOUND CLSSTAT: %s\n",cls);
  if(found)return i;

  if(numclsstats>=MAXCLSS)return -1;
  
  memset(&clsstats[numclsstats],0,sizeof(struct clsstats));
  strcpy(clsstats[numclsstats].name,cls);
  numclsstats++;
  debug2("CREATED CLSSTAT: %s\n",cls);
  return numclsstats-1;
}


void
readbaudstats()
{
  FILE *fp;
  struct stat s;

  if(stat(mkfname(BAUDSTATFILE),&s)){
    numbaudstats=0;
    return;
  }
  if (s.st_ctime==baudstattime)return;
  debug("READING BAUD STATS...\n");
  numbaudstats=0;
  if((fp=fopen(mkfname(BAUDSTATFILE),"r"))==NULL)return;
  while(!feof(fp)){
    int i=fscanf(fp,"%d %d %d %d\n",
		 &baudstats[numbaudstats].baud,
		 &baudstats[numbaudstats].credits,
		 &baudstats[numbaudstats].minutes,
		 &baudstats[numbaudstats].calls);
    if(numbaudstats>=MAXBAUDS)break;
    if(i==4)numbaudstats++;
  }
  fclose(fp);
}


void
writebaudstats()
{
  FILE *fp;
  int i;
  struct stat s;

  debug("WRITING BAUD STATS...\n");
  if((fp=fopen(mkfname(BAUDSTATFILE),"w"))==NULL){
    error_intsys("Unable to write %s",mkfname(BAUDSTATFILE));
    return;
  }
  for(i=0;i<numbaudstats;i++){
    fprintf(fp,"%d %d %d %d\n",baudstats[i].baud,baudstats[i].credits,
	    baudstats[i].minutes,baudstats[i].calls);
  }
  fclose(fp);
  if(!stat(mkfname(BAUDSTATFILE),&s))baudstattime=s.st_ctime;
}


int
findbaud(long baud)
{
  int found=0,i;

  for(i=0;i<numbaudstats;i++){
    if(baudstats[i].baud==baud){
      found=1;
      break;
    }
  }
  debug2("FOUND BAUDSTAT: %ld\n",baud);
  if(found)return i;

  if(numbaudstats>=MAXBAUDS)return -1;
  memset(&baudstats[numbaudstats],0,sizeof(struct baudstats));
  baudstats[numbaudstats].baud=baud;
  numbaudstats++;
  debug2("CREATED BAUDSTAT: %ld\n",baud);
  return numbaudstats-1;
}


void
readmodstats()
{
  FILE *fp;
  struct stat s;
  struct modstats mod;

  if(stat(mkfname(MODSTATFILE),&s)){
    nummodstats=0;
    return;
  }
  if (s.st_ctime==modstattime)return;
  debug("READING MOD STATS...\n");
  nummodstats=0;
  if((fp=fopen(mkfname(MODSTATFILE),"r"))==NULL)return;
  while(!feof(fp)){
    char line[1024],*cp;
    int len,ptr;
    
    if(nummodstats>=MAXMODS)break;
    
    if(!fgets(line,sizeof(line),fp))continue;
    if(!sscanf(line,"%d %n",&len,&ptr))continue;

    cp=&line[ptr];
    cp[len]=0;
    strncpy(mod.name,cp,sizeof(mod.name));
    cp+=len+1;

    if(sscanf(cp,"%d %d\n",&mod.credits,&mod.minutes)==2){
      memcpy(&modstats[nummodstats++],&mod,sizeof(struct modstats));
    }
  }
  fclose(fp);
}


void
writemodstats()
{
  FILE *fp;
  int i;
  struct stat s;

  debug("WRITING MOD STATS...\n");
  if((fp=fopen(mkfname(MODSTATFILE),"w"))==NULL){
    error_intsys("Unable to write %s",mkfname(MODSTATFILE));
    return;
  }
  for(i=0;i<nummodstats;i++){
    fprintf(fp,"%d %s %d %d\n",strlen(modstats[i].name),modstats[i].name,
	    modstats[i].credits,modstats[i].minutes);
  }
  fclose(fp);
  if(!stat(mkfname(MODSTATFILE),&s))modstattime=s.st_ctime;
}


int
findmod(char *mod)
{
  int found=0,i;

  for(i=0;i<nummodstats;i++){
    if(!strcmp(modstats[i].name,mod)){
      found=1;
      break;
    }
  }
  debug2("FOUND MODSTAT: %s\n",mod);
  if(found)return i;

  if(nummodstats>=MAXMODS)return -1;

  memset(&modstats[nummodstats],0,sizeof(struct modstats));
  strncpy(modstats[nummodstats].name,mod,sizeof(modstats[0].name));
  nummodstats++;
  debug2("CREATED MODSTAT: %s\n",mod);
  return nummodstats-1;
}


void
mainloop()
{
  int i, savecount=0, index;
  int sec=-1,min=0,oldsec=-1,oldmin=0;
  channel_status_t status;
  struct shmuserrec *ushm=NULL;

  for(;;){
    debug("\nTICK!\n");

    readdaystats();
    readttystats();
    readclsstats();
    readbaudstats();
    readmodstats();
    refreshclasses();
    refreshchannels();

    debug("Going on...\n");

    for(i=0;i<chan_count;i++){
      if(!channel_getstatus(channels[i].ttyname,&status))continue;
      if(status.result!=LSR_USER)continue;
      if(status.user[0]=='[')continue;
      if(!usr_insystem(status.user,0,&ushm))continue;
      if(!ushm->onl.userid[0])continue;
      debug2("USER: %s\n",status.user);

      /* Day stats */

      index=tdhour(now());
      if(ushm->onl.statcreds>0){
	daystats[index].credits+=ushm->onl.statcreds;
	debug2("DAYSTATS: CREDITS++ = %ld\n",daystats[index].credits);
      } else {
	debug("DAYSTATS: CREDITS<=0\n");
      }
      if(!sec){
	daystats[index].minutes++;
	debug2("DAYSTATS: MINUTE++ = %ld\n",daystats[index].minutes);
      }

      /* TTY stats */

      index=findtty(channels[i].ttyname);
      if(index>=0 && index<numttystats){
	if(ushm->onl.statptrs&STF_FIRST)ttystats[index].calls++;
	if(ushm->onl.statcreds>0){
	  ttystats[index].credits+=ushm->onl.statcreds;
	  debug2("TTYSTATS: CREDITS++ = %ld\n",ttystats[index].credits);
	} else {
	  debug("TTYSTATS: CREDITS<=0\n");
	}
	if(!sec){
	  ttystats[index].minutes++;
	  debug2("TTYSTATS: MINUTE++ = %ld\n",ttystats[index].minutes);
	}
      }

      /* Class stats */

      index=findcls(ushm->acc.curclss);
      if(index>=0 && index<numclsstats){
	if(ushm->onl.statcreds>0){
	  clsstats[index].credits+=ushm->onl.statcreds;
	  debug2("CLSSTATS: CREDITS++ = %ld\n",clsstats[index].credits);
	} else {
	  debug("CLSSTATS: CREDITS<=0\n");
	}
	if(!sec){
	  clsstats[index].minutes++;
	  debug2("CLSSTATS: MINUTE++ = %ld\n",clsstats[index].minutes);
	}
      }

      /* BAUD stats */

      index=findbaud(ushm->onl.baudrate);
      if(index>=0 && index<numbaudstats){
	if(ushm->onl.statptrs&STF_FIRST)baudstats[index].calls++;
	if(ushm->onl.statcreds>0){
	  baudstats[index].credits+=ushm->onl.statcreds;
	  debug2("BAUDSTATS: CREDITS++ = %ld\n",baudstats[index].credits);
	} else {
	  debug("BAUDSTATS: CREDITS<=0\n");
	}
	if(!sec){
	  baudstats[index].minutes++;
	  debug2("BAUDSTATS: MINUTE++ = %ld\n",baudstats[index].minutes);
	}
      }

      /* Module stats */

      index=findmod(ushm->onl.descr[0]);
      if(index>=0 && index<nummodstats){
	if(ushm->onl.statcreds>0){
	  modstats[index].credits+=ushm->onl.statcreds;
	  debug2("MODSTATS: CREDITS++ = %ld\n",modstats[index].credits);
	} else {
	  debug("MODSTATS: CREDITS<=0\n");
	}
	if(!sec){
	  modstats[index].minutes++;
	  debug2("MODSTATS: MINUTE++ = %ld\n",modstats[index].minutes);
	}
      }

      /* Reset stuff */

      ushm->onl.statptrs&=~STF_FIRST;
      ushm->onl.statcreds=0;
      shmdt((char *)ushm);
    }

    for(;;){
      usleep(SLEEPTIME);
      sec=tdsec(now());
      min=tdmin(now());
      debug2(":%02d\n",sec);
      if((sec%TICKTIME)==0){
	if(oldsec!=sec || oldmin!=min){
	  oldsec=sec;
	  oldmin=min;
	  break;
	}
      }
    }

    /* Periodic stat flushing */

    if(!sec){
      if(!savecount){
	writedaystats();
	writettystats();
	writeclsstats();
	writebaudstats();
	writemodstats();
      }
      savecount=(savecount+1)%sysvar->saverate;
    }
  }
}


int
main(int argc, char *argv[])
{
  mod_setprogname(argv[0]);
  if (getuid()){
    fprintf(stderr, "%s: getuid: not super-user\n", argv[0]);
    exit(1);
  }

  switch(fork()){
  case -1:
    fprintf(stderr,"%s: fork: unable to fork daemon\n",argv[0]);
    exit(1);
  case 0:
    break;
  default:
    exit(0);
  }
  
  mod_init(INI_TTYNUM|INI_SYSVARS|INI_CLASSES);
  msg=msg_open("sysvar");
  error_setnotify(0);
  storepid();
  ioctl(0,TIOCNOTTY,NULL);

  mainloop();

  return 0;
}
