/*****************************************************************************\
 **                                                                         **
 **  FILE:     channels.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94, Version 0.05 alpha                               **
 **  PURPOSE:  Commands that toy with channels and enable the sysop to spy  **
 **            on poor, unsuspecting users and then blackmail them.         **
 **  NOTES:    Stalin would have *LOVED* this one!                          **
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
 * Revision 1.1  2001/04/16 14:58:05  alexios
 * Initial revision
 *
 * Revision 0.11  2000/01/06 11:42:07  alexios
 * Various small bug fixes. The channel list now flags users who have
 * recently paged the system console.
 *
 * Revision 0.10  1999/08/13 17:02:31  alexios
 * Added status messages for MetaBBS, fixed listing bug for
 * telnet lines.
 *
 * Revision 0.9  1999/07/18 21:48:04  alexios
 * Changed a few fatal() calls to fatalsys(). Removed some
 * leftover debugging information.
 *
 * Revision 0.8  1998/12/27 16:07:28  alexios
 * Added autoconf support. Added support for new getlinestatus().
 * New code for the new bbsgetty states and handling. Various
 * fixes, among which is code to generate a warning if the sysop
 * leaves emulation while the emulated user is in chat mode
 * (hence cannot leave on their own).
 *
 * Revision 0.7  1998/08/14 11:44:25  alexios
 * Fixed rsys_monitor() to watch the new monitor format, which
 * displays either a channel or username (if there is one).
 *
 * Revision 0.6  1998/07/24 10:23:31  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.5  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 11:10:55  alexios
 * Added a typecast to emuq to get rid of a warning about
 * volatile being in place.
 *
 * Revision 0.3  1997/09/12 13:24:18  alexios
 * The channel display for rsys_change() doesn't display the
 * actual username of the user on a channel unless the issuer
 * of the command has the required key (option KEYCHU). Fixed
 * rsys_emulate() bug that would cause constant SIGSEGVs. Fixed
 * extra emulation bug that would turn on blocking() mode and
 * cause the emulate screen to behave abnormally (synchronously).
 * Fixed rsys_send() so it really DOES send stuff.
 *
 * Revision 0.2  1997/08/30 13:01:01  alexios
 * Changed bladcommand() calls to bbsdcommand(). Since bbsd only
 * accepts tty names (blad also allowed usernames), slight
 * adjustments were made at a few points in the code.
 *
 * Revision 0.1  1997/08/28 11:04:28  alexios
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
#define WANT_TERMIOS_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "remsys.h"
#include "mbk_remsys.h"


void
listchannels()
{
  int  i, showntelnetline=0, res;
  struct linestatus status;

  prompt(CHNLSTHDR,NULL);

  for(i=0;i<numchannels;i++){
    int ch=channels[i].channel;

    res=getlinestatus(channels[i].ttyname,&status);
    
    if(res<0 || status.result==LSR_LOGOUT){
      if(channels[i].flags&TTF_TELNET)status.result=LSR_OK;
      else status.result=-1;	/* Temporarily unknown state */
    }

    if(channels[i].flags&TTF_TELNET && showntelnetline &&
       (status.result==LSR_OK)) continue;

    switch(status.result){
    case LSR_INIT:
      prompt(CHNLSTTBI,ch,line_states[status.state]);
      break;
    case LSR_RING:
      prompt(CHNLSTTBR,ch);
      break;
    case LSR_ANSWER:
      prompt(CHNLSTTBA,ch);
      break;
#ifdef HAVE_METABBS
    case LSR_METABBS:
      prompt(CHNLSTTBM,ch,baudstg(status.baud),status.user);
      break;
#endif
    case LSR_LOGIN:
      prompt(CHNLSTTBL,ch,baudstg(status.baud));
      break;
    case LSR_USER:
      {
	if(uinsys(status.user,0)){
	  time_t t=time(NULL)-othruseronl.lastconsolepage;
	  prompt(CHNLSTTBU,ch,baudstg(status.baud),status.user,
		 t>pgstmo?"":getpfix(CHNLSTPGS,1));
	}
	break;
      }
    case LSR_FAIL:
      prompt(CHNLSTTBF,ch,line_states[status.state]);
      break;
    case LSR_RELOGON:
      prompt(CHNLSTTBL,ch,line_states[status.state]);
      break;
    case LSR_LOGOUT:
      prompt(CHNLSTTBQ,ch,line_states[status.state]);
      break;
    case LSR_OK:
      prompt(CHNLSTTBO,ch,line_states[status.state]);
      showntelnetline=channels[i].flags&TTF_TELNET;
      break;
    default:
      prompt(CHNLSTTBE,ch);
    }
    if(lastresult==PAUSE_QUIT)return;
  }
  prompt(CHNLSTFTR);
}


int
getchanname(char *dev, int msg, int all)
{
  char *i, c;
  int  channel;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      i=cncword();
    } else {
      prompt(msg,NULL);
      getinput(0);
      bgncnc();
      i=cncword();
      if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return 0;
      }
    }
    if(all&&(sameas(i,"*")||sameas(i,"all"))){
      strcpy(dev,"*");
      return 1;
    } else if(sameas(i,"?")){
      listchannels();
      endcnc();
      continue;
    } else if(strstr(i,"tty")==i){
      if(getchannelnum(i)!=-1){
	strcpy(dev,i);
	return 1;
      } else {
	prompt(GCHANBDV,NULL);
	endcnc();
	continue;
      }
    } else if(userexists(i)){
      if(!uinsys(i,0)){
	prompt(GCHANBID,NULL);
	endcnc();
	continue;
      } else {
	strcpy(dev,othruseronl.channel);
	return 1;
      }
    } else if(sscanf(i,"%x",&channel)==1){
      char *name=getchannelname(channel);
      if(!name){
	prompt(GCHANBCH,NULL);
	endcnc();
	continue;
      } else {
	strcpy(dev,name);
	return 1;
      }
    } else {
      prompt(GCHANHUH,i);
      endcnc();
      continue;
    }
  }
  return 0;
}


void
rsys_change()
{
  int  st;
  char tty[32];
  char opt, bc[64];
  struct linestatus status;

  for(;;){
    if(!morcnc())listchannels();
    for(;;){
      if(!getchanname(tty,RSCHANGEWHT,1))return;
      if(!strcmp(tty,"*"))break;
      getlinestatus(tty,&status);
      if(status.result==LSR_USER){
	prompt(RSCHANGEERR);
	endcnc();
      }
      else break;
    }
    if(!getmenu(&opt,1,RSCHANGELMN,RSCHANGESMN,RSCHANGEBAD,
		"RBNO",0,0))return;

    strcpy(bc,"RNBO");
    st=strchr(bc,opt)-bc;

    if(strcmp(tty,"*"))bbsdcommand("change",tty,line_states[st]);
    else {
      int i;
      
      for(i=0;i<numchannels;i++){
	getlinestatus(channels[i].ttyname,&status);
	if(status.result!=LSR_USER){
	  bbsdcommand("change",channels[i].ttyname,line_states[st]);
	}
      }
    }
    prompt(RSCHANGEOK,NULL);
  }
}


int
getchkname(char *checkname,char *tty)
{
  char s[256];
  FILE *fp;
  int pid;

  pid=0;
  sprintf(s,"%s/register-%s",BBSETCDIR,tty);
  if((fp=fopen(s,"r"))!=NULL){
    fgets(s,sizeof(s),fp);
    fclose(fp);
    sscanf(s,"%d",&pid);
    sprintf(checkname,"%s/%d",PROCDIR,pid);
  }
  return pid;
}


void
rsys_emulate()
{
  char            tty[256];
  FILE            *fp;
  struct stat     st;
  int             ok, pid;
  char            c;
  char            chkname[256];
  char            devname[256], fname[256];
  struct termios  oldkbdtermios;
  struct termios  newkbdtermios;
  int             count=0, stc=0, err=0;
  struct          emuqueue *emuq;
  int             i,j,shmid;
  char            lock[256];

  lock[0]=0;
  for(;;){
    if(!getchanname(tty,RSEMUWHO,0))return;
    if(!strcmp(thisuseronl.channel,tty))prompt(RSEMUSLF,NULL);
    else {
      FILE *fp=NULL;
      int  pid, ok=0;
      char s[256];

      sprintf(fname,"%s/emud-%s.pid",BBSETCDIR,tty);
      if((fp=fopen(fname,"r"))!=NULL){
	if(fscanf(fp,"%d",&pid)==1){
	  fclose(fp);
	  sprintf(fname,"%s/%d/stat",PROCDIR,pid);
	  if((fp=fopen(fname,"r"))!=NULL){
	    if((fscanf(fp,"%d %s",&pid,s)==2) && (!strcmp(s,"(emud)"))) ok=1;
	  }
	}
	fclose(fp);
	fp=NULL;
      }
      if(fp)fclose(fp);
      if(!ok){
	prompt(RSEMUNUS);
	continue;
      } else {
	char dummy[32];
	
	sprintf(lock,"LCK-emu-%s-%s",tty,thisuseronl.channel);
	if(checklock(lock,dummy)>0){
	  prompt(RSEMUHAHA);
	  continue;
	}
	rmlock(lock);
	sprintf(lock,"LCK-emu-%s-%s",thisuseronl.channel,tty);
	placelock(lock,"");
	break;
      }
    }
  }

  ok=0;
  pid=getchkname(chkname,tty);

  if(stat(chkname,&st)){
    prompt(RSEMUNOE);
    return;
  }

  thisuseronl.flags|=OLF_BUSY;
  prompt(RSEMUGO);

  sprintf(devname,DEVDIR"/%s",tty);

  /* Switch stdin to non blocking mode */

  nonblocking();
  tcgetattr(fileno(stdin), &oldkbdtermios);
  newkbdtermios = oldkbdtermios;
  newkbdtermios.c_lflag = newkbdtermios.c_lflag & ~ (ICANON | ECHO);
  tcsetattr(fileno(stdin), TCSAFLUSH, &newkbdtermios);

  /* Begin emulation */

  sprintf(fname,"%s/.shmid-%s",EMULOGDIR,tty);

  if((fp=fopen(fname,"r"))==NULL){
    fatalsys("Error opening %s\n",fname);
    err=1;
  }
  if(!fscanf(fp,"%d",&shmid)){
    fatalsys("Error reading %s\n",fname);
    err=1;
  }
  fclose(fp);

  if((emuq=(struct emuqueue *)shmat(shmid,NULL,0))==NULL){
    fatalsys("Error attaching to emulation shared memory\n");
    err=1;
  }

  sprintf(fname,"%s/.emu-%s",EMULOGDIR,tty);
  if((fp=fopen(fname,"w"))==NULL){
    fatalsys("Error opening %s\n",fname);
    err=1;
    }
  nonblocking();

  j=i=emuq->index;
  if(!err){
    for(;;){
      usleep(10000);
      count=(count+1)%5;
      if(!count){
	stc=(stc+1)%20;

	if(!stc) {
	  if(stat(chkname,&st)){
	    pid=getchkname(chkname,tty);
	    usleep(5000);
	    if(stat(chkname,&st)){
	      prompt(RSEMUNOE);
	      break;
	    }
	  }
	}

	if(emuq->index!=i){
	  j=emuq->index;
	  do{
	    write(0,(char*)&emuq->queue[i],1);
	    i=(i+1)%sizeof(emuq->queue);
	  }while(i!=j);
	}
      }

      if((read(fileno(stdin),&c,1))==1){
	if(c==17)break;
	else if(c==26){
	  struct linestatus status;

	  bbsdcommand("hangup",tty,"");
	  getlinestatus(tty,&status);
	  prompt(RSEMUHUP);
	  break;
	} else if(c==3){
	  bbsdcommand("chat",tty,"");
	} else {
	  fputc(c,fp);
	  fflush(fp);
	  count=-1;
	}
      }
    }
  }

  /* Switch back to blocking mode, close files, etc */
  
  blocking();
  tcsetattr(fileno(stdin), TCSAFLUSH, &oldkbdtermios);
  fclose(fp);

  shmdt((char *)emuq);

  prompt(RSEMUEND);
  if(othruseronl.flags&OLF_INSYSCHAT)prompt(RSEMUCHT);
  thisuseronl.flags&=~OLF_BUSY;
  rmlock(lock);
}


void
rsys_monitor()
{
  int  c;
  FILE *fp;
  int oldmark=0;

  prompt(RSMONITORHDR,NULL);
  if((fp=fopen(MONITORFILE,"r"))==NULL){
    prompt(RSMONITORERR,NULL);
    return;
  }
  fclose(fp);

  nonblocking();

  for(c=0;!(read(fileno(stdin),&c,1)&&
	    ((c==13)||(c==10)||(c==27)||(c==15)||(c==3)));){
    fseek(fp,0,SEEK_SET);
    
    if(oldmark!=monitor->timestamp){
      char tmp[64];
      if(monitor->channel[0]!=' '){
	sprintf(tmp,"%x",getchannelnum((char*)monitor->channel));
      } else strcpy(tmp,&((char*)monitor->channel)[1]);

      prompt(RSMONITORTAB,tmp,monitor->input);
      resetvpos(0);
      oldmark=monitor->timestamp;
    }

    acceptinjoth();
    usleep(50000);
  }

  prompt(RSMONITOREND,NULL);
  blocking();
}


void
rsys_send()
{
  char tty[32];
  char fname[256],msg[2050],tmp[2048],buf[MSGBUFSIZE];
  FILE *fp;
  struct linestatus status;

  for(;;){
    if(!getchanname(tty,RSSENDWHO,1))return;
    if(!strcmp(tty,"*"))break;
    getlinestatus(tty,&status);
    if(status.result!=LSR_USER){
      prompt(RSSENDR);
      endcnc();
    }
    else break;
  }
  sprintf(fname,TMPDIR"/send-%05d",getpid());
  
  editor(fname,2048);
  memset(msg,0,sizeof(msg));
  if((fp=fopen(fname,"r"))!=NULL)fread(msg,1,sizeof(msg)-1,fp);
  fclose(fp);
  unlink(fname);
  if(!msg[0]){
    prompt(RSSENDCAN);
    return;
  }
  if(strcmp(tty,"*")){
    if(!uinsys(status.user,0)){
      prompt(RSSENDD);
      return;
    }
    strcpy(tmp,getmsglang(RSSENDINH,othruseracc.language-1));
    sprintf(msgbuf,"%s%s\n\n",tmp,msg);
    if(!injoth(&othruseronl,msgbuf,0)){
      prompt(RSSENDX,othruseronl.userid);
    } else prompt(RSSEND1,getchannelnum(tty));
  } else {
    int i,j,n;
    for(i=j=n=0;i<numchannels;i++){
      getlinestatus(channels[i].ttyname,&status);
      if(status.result!=LSR_USER){
	if(uinsys(status.user,0)){
	  strcpy(tmp,getmsglang(RSSENDINH,othruseracc.language-1));
	  sprintf(buf,"%s%s\n\n",tmp,msg);
	  if(uinsys(status.user,0)){
	    n++;
	    if(!injoth(&othruseronl,buf,0)){
	      prompt(RSSENDX,othruseronl.userid);
	    } else j++;
	  }
	}
      }
    }
    if(!j)prompt(RSSEND2B);
    else if(n!=j)prompt(RSSEND2A);
    else prompt(RSSEND2);
  }
}



