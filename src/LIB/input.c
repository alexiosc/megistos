/*****************************************************************************\
 **                                                                         **
 **  FILE:     input.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Handle user input using ncurses                              **
 **  NOTES:    Initialise using initinput()                                 **
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
 * Revision 1.1  2001/04/16 14:49:38  alexios
 * Initial revision
 *
 * Revision 0.11  2000/01/06 10:56:23  alexios
 * Changed calls to write(2) to send_out().
 *
 * Revision 0.10  1999/07/28 23:06:34  alexios
 * Added a timeout facility to getinp(), accessible using
 * setinputtimeout().
 *
 * Revision 0.9  1999/07/18 21:01:53  alexios
 * Changed a couple of fatal() calls to fatalsys(). Minor
 * fixes in dealing with global commands while in password
 * entry mode. One minor change to getint() to make it behave
 * better in concatenated mode. One minor fix to getbool().
 *
 * Revision 0.8  1998/12/27 14:31:16  alexios
 * Added autoconf support. Enhanced terminal setting support to
 * deal with changes forced by new bbsgetty. Moved isX from
 * miscfx.c to input.c. Same for settimeout and resetinactivity().
 *
 * Revision 0.7  1998/08/14 11:27:44  alexios
 * Augmented monitorinput() to record either the user's
 * channel number or their user ID (if it is known).
 *
 * Revision 0.6  1998/07/26 21:05:25  alexios
 * Removed obsolete injothfile variable. Fixed very serious bug
 * that would not accept messages from an injoth() queue with
 * SYSV IPC queue id equal to 0.
 *
 * Revision 0.5  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.4  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/03 00:34:41  alexios
 * Changed all calls to xlwrite() to write() since emud now
 * handles all translations itself.
 *
 * Revision 0.2  1997/09/12 12:49:41  alexios
 * Acceptinjoth() now uses an IPC message queue instead of the
 * previous method (using disk files). Added resetblocking() so
 * that the previous state of the terminal blocking may be restored.
 * Functions blocking() and nonblocking() now change this previous
 * sate and resetblocking() changes it back.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_TERMIOS_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_MSG_H 1
#define WANT_ERRNO_H 1
#define WANT_SEND_OUT 1
#include <bbsinclude.h>

#include "config.h"
#include "errors.h"
#include "input.h"
#include "useracc.h"
#include "miscfx.h"
#include "prompts.h"
#include "output.h"
#include "format.h"
#include "globalcmd.h"
#include "sysstruct.h"
#include "bbsmod.h"
#include "security.h"
#define __SYSVAR_UNAMBIGUOUS__
#include "mbk_sysvar.h"

struct termios  oldkbdtermios;
struct termios  newkbdtermios;
char            del[4]="\010 \010\0";
char            input[MAXINPLEN+1];
char            *margv[MAXINPLEN/2];
char            *margn[MAXINPLEN/2];
char            *nxtcmd,wordbuf[MAXINPLEN];
int             margc;
int             inplen;
int             reprompt;
int             passwordentry;
int             dontinjoth;
int             inputflags=0;
int             oldblocking=1;
int             newblocking=1;
int             inptimeout_msecs=0;
int             inptimeout_intr=0;

static long oldflags=0;
static volatile int cancel=0;
volatile struct monitor *monitor;
static char montty[24];


void setmonitorid(char *s)
{
  sprintf(montty," %s",s);
}


static void
initmonitor()
{
  FILE *fp;
  int shmid;

  strcpy(montty,getenv("CHANNEL"));

  if((fp=fopen(MONITORFILE,"r"))==NULL){
    fatalsys("Unable to open %s",MONITORFILE);
  }

  fscanf(fp,"%d",&shmid);
  fclose(fp);

  if((monitor=(struct monitor *)shmat(shmid,NULL,0))==NULL){
    fatalsys("Unable to attach to shm block (errno=%d).",errno);
  }
}


void
initinput()
{
  int i;
  tcgetattr(0, &oldkbdtermios);
  memcpy(&newkbdtermios,&oldkbdtermios,sizeof(newkbdtermios));
  newkbdtermios.c_lflag = newkbdtermios.c_lflag & ~ (ICANON | ECHO | ISIG);
  for(i=0;i<sizeof(newkbdtermios.c_cc);i++) newkbdtermios.c_cc[i]=0;
  newkbdtermios.c_cc[VTIME]=0;	/* Cook the tty (medium rare) */
  newkbdtermios.c_cc[VMIN]=1;
  tcsetattr(0, TCSANOW, &newkbdtermios);
  reprompt=0;
  dontinjoth=0;
  passwordentry=0;

  initmonitor();
}


void
doneinput()
{
  tcsetattr(0, TCSANOW, &oldkbdtermios);
}


int
acceptinjoth()
{
  char dummy[MSGMAX+sizeof(long)];
  struct msgbuf *buf=(struct msgbuf*)(&dummy);
  int i=0;

  if(thisshm==NULL)return 0;
  if(!thisuseronl.userid[0])return 0;
  if(thisuseronl.injothqueue<0)return 0;

  for(;;){
    bzero(dummy,sizeof(dummy));
    errno=0;
    if(msgrcv(thisuseronl.injothqueue,buf,MSGMAX,0,IPC_NOWAIT)<0)return i>0;
    i++;
    print("%s",buf->mtext);
  }

  return 1;
}



void
inputstring(int maxlen)
{
  int  cp=0, count=0, tmout;
  unsigned char c;
  struct timeval tv,tvtimeout;
  struct timezone tz;

  cancel=0;
  if(inptimeout_msecs){
    gettimeofday (&tv, &tz);
    memcpy(&tvtimeout,&tv,sizeof(tv));
    tvtimeout.tv_usec+=inptimeout_msecs*1000;
    tvtimeout.tv_sec+=tvtimeout.tv_usec/1000000;
    tvtimeout.tv_usec=tvtimeout.tv_usec%1000000;
  }

  tmout=inptimeout_msecs>0;

  nonblocking();
  reprompt=0;

  if(!maxlen)maxlen=MAXINPLEN-1;
  for(;;){
    while (read(0,&c,1)!=1){
      if(cancel){
	acceptinjoth();
	reprompt=1;
	clrinp();
	blocking();
	return;
      }
      usleep(10000);
      if(tmout && (cp==0 || inptimeout_intr)){ /* Handle timeouts */
	gettimeofday (&tv, &tz);
	if((tv.tv_sec>tvtimeout.tv_sec) ||
	   ((tv.tv_sec==tvtimeout.tv_sec)&&(tv.tv_usec>=tvtimeout.tv_usec))){
	  inptimeout_msecs=0;
	  inptimeout_intr=0;
	  clrinp();
	  blocking();
	  return;
	}
      }
      count=(count+1)%5;
      if(dontinjoth || cp) continue;
      if(acceptinjoth()){
	reprompt=1;
	clrinp();
	blocking();
	return;
      }
      if(count) continue;
    }
    resetinactivity();
    switch(c){
    case 13:
    case 10:
      c='\n';
      send_out(fileno(stdout),&c,1);
      fflush(stdout);
      input[cp]=0;
      monitorinput(montty);
      blocking();
      if(!passwordentry && handlegcs()){
	clrinp();
	reprompt=1;
      }
      return;
    case 127:
    case 8:
      if(cp){
	send_out(fileno(stdout),del,3);
	cp--;
      }
      break;
    default:
      if(cp<maxlen && (c>=0x20)){
	input[cp++]=c;
	if(passwordentry)c='*';
	send_out(fileno(stdout),&c,1);
      }
    }
  }
}


void
parsin()
{
  char *cp=input;

  margc=0;
  inplen=strlen(input);

  cp=strtok(input," ");
  while(cp){
    margv[margc++]=cp;
    cp=strtok(NULL," ");
  }

/*  for(;;){
    while(*cp==32)cp++;
    if(!*cp)break;
    margv[margc++]=cp;
    
    while(*cp && (*cp!=32))cp++;
    if(!*cp)break;
    *(cp++)=0;
  }*/
}


void
monitorinput(char *tty)
{
  monitor->timestamp++;
  strcpy((char *)monitor->channel,tty);
  strcpy((char *)monitor->input,passwordentry?"<password>":input);
}


char *
getinput(int maxlen)
{
  afterinput=1;
  memset(input,0,sizeof(input));
  if(lastresult==PAUSE_QUIT) {
    reprompt=1;
  } else {
    resetvpos(0);
    inputstring(maxlen);
  }
  resetvpos(0);
  nxtcmd=NULL;
  return margv[0];
}


void
clrinp()
{
  input[0]=0;
  inplen=0;
  margc=0;
}


void
rstrin()
{
  int i;

  for(i=0;i<margc-1;i++)(margv[i][strlen(margv[i])])=32;
}


void
bgncnc()
{
  nxtcmd=margv[0];
  rstrin();
}


int
endcnc()
{
  nxtcmd=NULL;
  thisuseronl.input[0]=0;
  parsin();
/*  if (!margc)return 1;
  strncpy(input,nxtcmd,strlen(nxtcmd)+1);
  parsin(); */
  return (margc==0);
}


char
cncchr()
{
  char c;

  if(nxtcmd==NULL)return 0;
  if((c=tolatin(toupper(*nxtcmd)))!=0)nxtcmd++;
  return c;
}


int
cncint()
{
  int ofs, d=0;

  sscanf(nxtcmd,"%d%n",&d,&ofs);
  nxtcmd+=ofs;
  return d;
}


long
cnclong()
{
  int ofs;
  long l=0L;

  sscanf(nxtcmd,"%ld%n",&l,&ofs);
  nxtcmd+=ofs;
  return l;
}


char
cncyesno()
{
  char c;
  
  switch (c=cncchr()) {
  case 'Y':
#ifdef GREEK
  case -109:
  case -84:
#endif
    c='Y';
    break;
  case 'N':
#ifdef GREEK
  case -92:
  case -116:
#endif
    c='N';
    break;
  }
  return(c);
}


char *
cncword()
{
  int i=0;
  char c;

  wordbuf[0]=0;

  while((c=*nxtcmd)!=' ' && c){
    nxtcmd++;
    wordbuf[i++]=c;
  }
  wordbuf[i]=0;
  return wordbuf;
}


char *
cncall()
{
  char *s;
  
  s=nxtcmd;
  nxtcmd="";
  return s;
}


char
morcnc()
{
  if(!nxtcmd) return 0;
  while(*nxtcmd==' ')nxtcmd++;
  return(toupper(*nxtcmd));
}


int
cnchex()
{
  int i,retval=0,flag=0;
  static char hex[6]={'A','B','C','D','E','F'};
  
  while (1) {
    if(isdigit(*nxtcmd))retval=(retval<<4)+(*nxtcmd-'0');
    else {
      for(i=0;i<6;i++){
	if (toupper(*nxtcmd)==hex[i]){
	  retval=(retval<<4)+10+i;
	  break;
	}
      }
      if (i==6)return(flag?retval:-1);
    }
    nxtcmd++;
    flag=1;
  }
}


char *
cncnum()
{
  int i=0;
  static char retval[12];
  
  if (*nxtcmd=='-')retval[i++]=*(nxtcmd++);
  while(isdigit(*nxtcmd)&& i<11)retval[i++]=*(nxtcmd++);
  retval[i]='\0';
  return(retval);
}


void
setpasswordentry(int n)
{
  passwordentry=(n!=0);
}


void
setinjoth(int n)
{
  dontinjoth=(n==0);
}


void
setinputflags(int n)
{
  inputflags=n;
}


int isX(char *s)
{
  int c=toupper(s[0]);
  int result;

  if(strlen(s)!=1) return 0;
  result=(c=='X');
#ifdef GREEK
  result|=(c==-82 || c==-107);
#endif
  return result;
}


int
getnumber(num,msg,min,max,err,def,defval)
int *num,msg,min,max,err,def,defval;
{
  int i;
  char c;

  lastresult=PAUSE_CONTINUE;
  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      if(sameas(nxtcmd,"?")&&(inputflags&INF_HELP))return -1;
      if(sameas(nxtcmd,".")&&def){
	*num=defval;
	return 1;
      }
      i=cncint();
    } else {
      if(msg)prompt(msg,min,max,NULL);
      if(def){
	sprintf(outbuf,getmsg(def),defval);
	print(outbuf,NULL);
      }
      getinput(0);
      if((!margc||(margc==1&&sameas(margv[0],"."))) && def && !reprompt) {
	*num=defval;
	return 1;
      } else if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return 0;
      }
      if(sameas(margv[0],"?")&&(inputflags&INF_HELP))return -1;
      bgncnc();
      i=cncint();
    }
    if(i<min || i>max){
      endcnc();
      if(err)prompt(err,min,max,NULL);
    }else{
      *num=i;
      return 1;
    }
  }
  return 0;
}


int
getbool(boolean,msg,err,def,defval)
int *boolean,msg,err,def,defval;
{
  int c=0;
  lastresult=PAUSE_CONTINUE;
  for(;;){
    lastresult=0;
    if(morcnc())c=cncyesno();
    else {
      if(msg)prompt(msg,NULL);
      if(def){
	sprintf(outbuf,getmsg(def),(defval?'Y':'N'));
	print(outbuf,NULL);
      }
      getinput(0);
      if(margc){
	if(isX(margv[0])){
	  return 0;
	}
	if(sameas(margv[0],"?")&&(inputflags&INF_HELP))return -1;
      }else if((!margc||(margc==1&&sameas(margv[0],".")))&&def && !reprompt) {
	*boolean=defval;
	return 1;
      }
      bgncnc();
      c=cncchr();
    }
    switch(c=toupper(c)){
#ifdef GREEK
    case -109:
    case -84:
#endif
    case 'Y':
      *boolean=1;
      return 1;
#ifdef GREEK
    case -92:
    case -116:
#endif
    case 'N':
      *boolean=0;
      return 1;
    case 0:
      endcnc();
      continue;
    case '?':
      if(inputflags&INF_HELP)return -1;
      break;
    default:
      endcnc();
      if(err)prompt(err,c);
    }      
  }
  return 0;
}


int
getuserid(uid,msg,err,def,defval,online)
char *uid, *defval;
int  msg,err,def,online;
{
  char *i;
  char c;

  lastresult=PAUSE_CONTINUE;
  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      if(sameas(nxtcmd,"?")&&(inputflags&INF_HELP))return -1;
      if(sameas(nxtcmd,".")&&def){
	strcpy(uid,defval);
	return 1;
      }
      i=cncword();
    } else {
      if(msg)prompt(msg,NULL);
      if(def){
	sprintf(outbuf,getmsg(def),defval);
	print(outbuf,NULL);
      }
      getinput(0);
      bgncnc();
      i=cncword();
      if((!margc||(margc==1&&sameas(margv[0],".")))&&def && !reprompt) {
	strcpy(uid,defval);
	return 1;
      } else if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return 0;
      }
      if(sameas(margv[0],"?")&&(inputflags&INF_HELP))return -1;
    }
    if(!uidxref(i,online)){
      endcnc();
      if(err)prompt(err,i,NULL);
    }else{
      strcpy(uid,i);
      return 1;
    }
  }
  return 0;
}


int
getmenu(option,show,lmenu,smenu,err,opts,def,defval)
char *option, defval, *opts;
int  show,lmenu,smenu,err,def;
{
  int shownmenu=!show;
  char c;

  lastresult=PAUSE_CONTINUE;
  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      c=cncchr();
      shownmenu=1;
    } else {
      if(!shownmenu && lmenu)prompt(lmenu);
      shownmenu=1;
      if(smenu)prompt(smenu,NULL);
      if(def){
	sprintf(outbuf,getmsg(def),defval);
	print(outbuf,NULL);
      }
      getinput(0);
      bgncnc();
      c=cncchr();
    }
    if((!margc||(margc==1&&sameas(margv[0],".")))&&def && !reprompt) {
      *option=defval;
      return 1;
    } else if (!margc) {
      endcnc();
      continue;
    }
    if(isX(margv[0])){
      return 0;
    } else if(margc && (c=='?'||sameas(margv[0],"?"))){
      if(inputflags&INF_HELP)return -1;
      shownmenu=0;
      continue;
    } else if(strchr(opts,c)){
      *option=c;
      return 1;
    } else {
      if(err)prompt(err,c);
      endcnc();
      continue;
    }
  }
  return 0;
}


void cancelinput()
{
  cancel=1;
}


void
nonblocking()
{
  oldblocking=newblocking;
  newblocking=0;
  oldflags=fcntl(fileno(stdin),F_GETFL)&~O_NONBLOCK;
  fcntl(0,F_SETFL,oldflags|O_NONBLOCK);
}


void
blocking()
{
  oldblocking=newblocking;
  newblocking=1;
  oldflags=fcntl(fileno(stdin),F_GETFL)&~O_NONBLOCK;
  fcntl(0,F_SETFL,oldflags);
}


void
resetblocking()
{
  if(oldblocking)blocking();
  else nonblocking();
}


void
settimeout(int i)
{
  int ovr=0, usy=0, force=0;

  /*  if(thisuseracc.userid[0]&&sysvar!=NULL)
    ovr=haskey(&thisuseracc,sysvar->idlovr); */
  usy=hassysaxs(&thisuseracc,USY_MASTERKEY);
  force=(thisuseronl.flags&OLF_FORCEIDLE)!=0;

  if((!usy&&!ovr)||force)thisuseronl.idlezap=i;
  else thisuseronl.idlezap=0;
}


void
resetinactivity()
{
  if(thisshm)thisuseronl.timeoutticks=0;
}


void
setinputtimeout(int msecs, int intrusive)
{
  inptimeout_msecs=msecs;
  inptimeout_intr=intrusive;
}
