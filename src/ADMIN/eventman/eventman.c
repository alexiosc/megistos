/*****************************************************************************\
 **                                                                         **
 **  FILE:     eventman.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 95, Version 1.0                                   **
 **  PURPOSE:  Manage BBS timed events                                      **
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
 * Revision 1.4  2001/10/03 18:13:51  alexios
 * Migrated to snprintf() for security reasons.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.7  2000/01/06 11:35:56  alexios
 * Event names may now comprise a wider range of characters, not
 * just alphabetics.
 *
 * Revision 1.6  1999/07/18 21:12:30  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.5  1998/12/27 14:43:56  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 1.4  1998/07/24 10:07:19  alexios
 * Upgraded to version 0.6 of library.
 *
 * Revision 1.3  1997/11/06 20:08:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.2  1997/11/06 16:46:42  alexios
 * Changed calls to audit() to follow the new auditing scheme.
 * Created AUT_ flags for all audit trail entries made by this
 * utility.
 *
 * Revision 1.1  1997/08/30 12:49:48  alexios
 * Changed bladcommand() calls to bbsdcommand().
 *
 * Revision 1.0  1997/08/26 15:45:45  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_CTYPE_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "mbk_eventman.h"
#include "bbs.h"


promptblock_t *msg;

int  entrykey;
char *fullaxid;
int  logshd;
int  logspn;
int  logpre;


static char *channelstatus[]={"NORMAL","BUSY-OUT","NO-ANSWER","OFF-LINE"};


/*                   123456789012345678901234567890 */
#define AUS_EVNEW   "EVENT CREATION"
#define AUS_EVDEL   "EVENT DELETION"
#define AUS_EVADD   "EVENT SCHEDULED"
#define AUS_EVCAN   "EVENT CANCELED"

/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_EVNEW   "User %s created event %s."
#define AUD_EVDEL   "User %s deleted event %s."
#define AUD_EVADD   "%s scheduled %s (to run at %02d:%02d)"
#define AUD_EVADA   "%s scheduled %s (to run ASAP)"
#define AUD_EVCAN   "%s canceled %s"

#define AUT_EVNEW   (AUF_EVENT|AUF_OPERATION|AUF_INFO)
#define AUT_EVDEL   (AUF_EVENT|AUF_OPERATION|AUF_CAUTION)
#define AUT_EVADD   (AUF_EVENT|AUF_OPERATION|AUF_INFO)
#define AUT_EVCAN   (AUF_EVENT|AUF_OPERATION|AUF_CAUTION)


void
init()
{
  mod_init(INI_ALL);
  msg=msg_open("eventman");
  msg_setlanguage(thisuseracc.language);

  entrykey=msg_int(ENTRYKEY,0,129);
  fullaxid=msg_string(FULLAXID);
  logshd=msg_bool(LOGSHD);
  logspn=msg_bool(LOGSPN);
  logpre=msg_bool(LOGPRE);
}


int
fullaccess()
{
  char ids[256],*cp=ids;
  char uid[256];

  snprintf(ids,sizeof(ids)," Sysop %s ",fullaxid);
  snprintf(uid,sizeof(uid)," %s ",thisuseracc.userid);
  for(cp=ids;*cp;cp++)*cp=toupper(*cp);
  for(cp=uid;*cp;cp++)*cp=toupper(*cp);
  return (strstr(ids,uid)!=NULL);
}


void
newevent()
{
  char *s=inp_buffer, fname[256];
  struct event event;
  struct stat st;
  int bool;
  FILE *fp;

  memset(&event,0,sizeof(event));

  /* Get name */
  
  for(;;){
    if(!cnc_more()){
      prompt(EVNNAME);
      inp_get(13);
      cnc_begin();
    }
    if(!margc)continue;
    else if(inp_isX(margv[0])){
      prompt(CANCEL);
      return;
    } else {
      char *cp=s;
      int ok;

      s=cnc_word();
      for(ok=1;(*cp=tolower(*cp))!=0;cp++){
	if(*cp!='_'&&*cp!='-'&&*cp!='.'&&(!isdigit(*cp))&&(!isalpha(*cp))){
	  prompt(EVNCHR);
	  cnc_end();
	  ok=0;
	  break;
	}
      }
      if(!ok)continue;
      snprintf(fname,sizeof(fname),"%s/.%s",mkfname(EVENTDIR),s);
      if(!stat(fname,&st)){
	prompt(EVNALRX);
	cnc_end();
	continue;
      }
      break;
    }
  }

  /* Get description */

  cnc_end();
  for(;;){
    prompt(EVNDESC);
    inp_get(40);
    cnc_begin();
    if(!margc)continue;
    else if(inp_isX(margv[0])){
      prompt(CANCEL);
      return;
    } else {
      strncpy(event.descr,inp_buffer,sizeof(event.descr));
      break;
    }
  }

  /* Get event program */

  cnc_end();
  for(;;){
    prompt(EVNPROG);
    inp_get(255);
    cnc_begin();
    if(!margc)continue;
    else if(inp_isX(margv[0])){
      prompt(CANCEL);
      return;
    } else {
      strncpy(event.command,inp_buffer,sizeof(event.command));
      break;
    }
  }
  cnc_end();
  inp_buffer[0]=0;
  cnc_nxtcmd=inp_buffer;

  if(!get_bool(&bool,EVNONCE,ERRSEL,0,0))return;
  if(!bool)event.flags|=EVF_ONLYONCE;

  if(!get_bool(&bool,EVNUNIQ,ERRSEL,0,0))return;
  if(bool)event.flags|=EVF_UNIQUE;

  if(!get_bool(&bool,EVNWARN,ERRSEL,0,0))return;
  if(bool)event.flags|=EVF_WARN;

  snprintf(fname,sizeof(fname),"%s/.%s",mkfname(EVENTDIR),s);
  if((fp=fopen(fname,"w"))==NULL){
    error_fatalsys("Unable to create file %s",fname);
  }
  fwrite(&event,sizeof(struct event),1,fp);
  fclose(fp);
  prompt(EVNOK,s);
  audit(thisuseronl.channel,AUDIT(EVNEW),thisuseracc.userid,s);
}


void
listevents()
{
  DIR    *dp;
  struct dirent *dirent;
  char *asap=msg_string(EVLASAP);
  
  if((dp=opendir(mkfname(EVENTDIR)))==NULL){
    error_fatalsys("Unable to opendir %s",mkfname(EVENTDIR));
  }
  prompt(EVLHDR); 
  while((dirent=readdir(dp))!=NULL){
    if(dirent->d_name[0]!='.'){
      struct event event;
      FILE *fp;
      char s[256];
      char time[10];

      memset(&event,0,sizeof(event));
      snprintf(s,sizeof(s),"%s/%s",mkfname(EVENTDIR),dirent->d_name);
      if((fp=fopen(s,"r"))==NULL)continue;
      fread(&event,sizeof(event),1,fp);
      fclose(fp);
      snprintf(time,sizeof(time),"%02d:%02d",event.hour,event.min);
      prompt(EVLTAB,(char *)&dirent->d_name,
	     event.flags&EVF_ASAP?asap:time,event.descr,
	     msg_getunit(EVLNO,event.flags&EVF_ONLYONCE));
    }
  }
  free(asap);
  closedir(dp);
  prompt(EVLFTR);
}


void
listprototypes()
{
  DIR    *dp;
  struct dirent *dirent;

  if((dp=opendir(mkfname(EVENTDIR)))==NULL){
    error_fatalsys("Unable to opendir %s",mkfname(EVENTDIR));
  }
  prompt(EVPHDR); 
  while((dirent=readdir(dp))!=NULL){
    if(dirent->d_name[0]=='.'){
      struct event event;
      FILE *fp;
      char s[256];

      if((!strcmp(".",dirent->d_name))||(!strcmp("..",dirent->d_name)))
	continue;
      memset(&event,0,sizeof(event));
      snprintf(s,sizeof(s),"%s/%s",mkfname(EVENTDIR),dirent->d_name);
      if((fp=fopen(s,"r"))==NULL)continue;
      fread(&event,sizeof(event),1,fp);
      fclose(fp);
      prompt(EVPTAB,(char *)&dirent->d_name[1],event.descr);
    }
  }
  closedir(dp);
  prompt(EVPFTR);
}


void
delevent()
{
  char *s=inp_buffer, fname[256];
  struct stat st;
  int bool;

  prompt(EVDWARN);

  /* Get name */
  
  for(;;){
    if(!cnc_more()){
      prompt(EVDASK);
      inp_get(13);
      cnc_begin();
    }
    if(!margc)continue;
    else if(inp_isX(margv[0])){
      prompt(CANCEL);
      return;
    } else if(margc==1 && sameas(margv[0],"?")){
      listprototypes();
      cnc_end();
      continue;
    } else {
      char *cp=s;

      s=cnc_word();
      for(;(*cp=tolower(*cp))!=0;cp++);
      snprintf(fname,sizeof(fname),"%s/.%s",mkfname(EVENTDIR),s);
      if(s[0]=='.' || stat(fname,&st)){
	prompt(EVDNEXS);
	cnc_end();
	continue;
      }
      break;
    }
  }

  if(!get_bool(&bool,EVDCONF,ERRSEL,0,0)){
    prompt(CANCEL);
    return;
  } else if (bool){
    snprintf(fname,sizeof(fname),"%s/.%s",mkfname(EVENTDIR),s);
    unlink(fname);
    prompt(EVDOK,s);
    audit(thisuseronl.channel,AUDIT(EVDEL),thisuseracc.userid,s);
  } else {
    prompt(CANCEL);
  }
}


void
beginasap()
{
  int i;
  channel_status_t status;

  for(i=0;i<chan_count;i++){
    channel_getstatus(channels[i].ttyname,&status);
    if(status.result!=LSR_USER)
      bbsdcommand("change",channels[i].ttyname,channelstatus[1]);
    else
      bbsdcommand("nchang",channels[i].ttyname,channelstatus[1]);
  }
}


void
makevent(char *name)
{
  char *s,fname[256];
  int helped=0,i,bool=0;
  struct event event;
  FILE *fp;
  struct stat st;
  
  for(i=0;i<99;i++){
    sprintf(fname,sizeof(fname),"%s/%s-%02d",mkfname(EVENTDIR),name,i);
    if(!stat(fname,&st)){
      prompt(EVAUNI,name);
      return;
    }
  }

  for(;;){
    if(!cnc_more()){
      if(!helped){
	prompt(EVAWHH);
	helped=1;
      }
      prompt(EVAWHN);
      inp_get(0);
      cnc_begin();
    }
    if(!margc)continue;
    else if(inp_isX(margv[0])){
      prompt(CANCEL);
      return;
    } else if(margc==1 && sameas(margv[0],"?")){
      helped=0;
      cnc_end();
      continue;
    } else {
      int h,m,format,t,en;
      
      s=cnc_word();
      if(sscanf(s,"%d:%d",&h,&m)==2){
	if(h<0 || h>23 || m<0 || m>59){
	  prompt(EVAWHE);
	  cnc_end();
	  continue;
	} else format=0;
      } else if(sscanf(s,"%d",&m)==1){
	if(m<=0){
	  prompt(EVAWHE);
	  cnc_end();
	  continue;
	} else format=1;
      } else if(sameas(s,"ASAP")){
	format=2;
      } else if(sameas(s,"NOW")){
	format=3;
      } else {
	prompt(EVAWHE);
	cnc_end();
	continue;
      }

      /* scheduling done here */

      memset(&event,0,sizeof(event));
      snprintf(fname,sizeof(fname),"%s/.%s",mkfname(EVENTDIR),name);
      if((fp=fopen(fname,"r"))==NULL)continue;
      fread(&event,sizeof(event),1,fp);
      fclose(fp);

      switch(format){
      case 0:
	event.hour=h;
	event.min=m;
	break;
      case 1:
	t=now();
	event.hour=(tdhour(t)+(tdmin(t)+m)/60)%24;
	event.min=(tdmin(t)+m)%60;
	break;
      case 2:
	event.hour=event.min=-1;
	event.flags|=EVF_ASAP;
	beginasap();
	break;
      case 3:
	if(!get_bool(&bool,EVAWARN,ERRSEL,0,0)){
	  prompt(CANCEL);
	  return;
	}
	if(!bool){
	  prompt(CANCEL);
	  return;
	}
	event.hour=event.min=-1;
	event.flags|=EVF_NOW;
	break;
      }

      for(i=0,en=-1;i<99;i++){
	snprintf(fname,sizeof(fname),"%s/%s-%02d",mkfname(EVENTDIR),name,i);
	if(stat(fname,&st)){
	  en=i;
	  break;
	}
      }
      if(en<0){
	prompt(EVA2MN,name);
	return;
      }
      if((fp=fopen(fname,"w"))==NULL)continue;
      fwrite(&event,sizeof(event),1,fp);
      fclose(fp);
      if(event.flags&EVF_ASAP)prompt(EVADD3,name);
      else if(event.flags&EVF_NOW)prompt(EVADD4,name);
      else prompt(event.flags&EVF_ONLYONCE?EVADD1:EVADD2,
		  name,event.hour,event.min);
      
      snprintf(fname,sizeof(fname),"%s-%02d",name,i);
      if(event.flags&EVF_ASAP){
	audit(thisuseronl.channel,AUDIT(EVADD),thisuseracc.userid,fname);
      } else if(event.flags&EVF_NOW){
	audit(thisuseronl.channel,AUDIT(EVSPAWN),thisuseracc.userid,fname);

	bbsdcommand("event",thisuseronl.channel,fname);
      } else {
	audit(thisuseronl.channel,AUDIT(EVADD),
	      thisuseracc.userid,fname,event.hour,event.min);
      }
      return;
    }
  }
}


void
addevent()
{
  struct stat st;
  char fname[256], s[256];
  
  for(;;){
    if(!cnc_more()){
      prompt(EVANAM);
      inp_get(13);
      cnc_begin();
    }
    if(!margc)continue;
    else if(inp_isX(margv[0])){
      prompt(CANCEL);
      return;
    } else if(margc==1 && sameas(margv[0],"?")){
      listprototypes();
      cnc_end();
      continue;
    } else {
      strcpy(s,cnc_word());
      {
	int i;
	for(i=0;s[i];i++)s[i]=tolower(s[i]);
      }
      snprintf(fname,sizeof(fname),"%s/.%s",mkfname(EVENTDIR),s);
      if(stat(fname,&st)){
	prompt(EVANEX);
	cnc_end();
	continue;
      }
      makevent(s);
      break;
    }
  }
}


void
undoevent (char *name)
{
  int yes=0;
  char fname[256];

  if(!cnc_more())prompt(EVCWARN,name);
  if(!get_bool(&yes,EVCASK,ERRSEL,0,0))return;
  if(!yes){
    prompt(CANCEL);
    return;
  }
  snprintf(fname,sizeof(fname),"%s/%s",mkfname(EVENTDIR),name);
  unlink(fname);
  prompt(EVCAN,name);
  audit(thisuseronl.channel,AUDIT(EVCAN),thisuseracc.userid,name);
}


void
cancelevent()
{
  struct stat st;
  char fname[256], s[256];
  
  for(;;){
    if(!cnc_more()){
      prompt(EVCNAM);
      inp_get(16);
      cnc_begin();
    }
    if(!margc)continue;
    else if(inp_isX(margv[0])){
      prompt(CANCEL);
      return;
    } else if(margc==1 && sameas(margv[0],"?")){
      listevents();
      cnc_end();
      continue;
    } else {
      strcpy(s,cnc_word());
      {
	int i;
	for(i=0;s[i];i++)s[i]=tolower(s[i]);
      }
      snprintf(fname,sizeof(fname),"%s/%s",mkfname(EVENTDIR),s);
      if(s[0]=='.' || stat(fname,&st)){
	prompt(EVCNEX);
	cnc_end();
	continue;
      }
      undoevent(s);
      break;
    }
  }
}


void
run()
{
  int shownmenu=0;
  char c=0;
  int hasaccess=fullaccess();

  if(!key_owns(&thisuseracc,entrykey)){
    prompt(NOENTRY,NULL);
    return;
  }

  for(;;){
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(hasaccess?PMENU:MENU,NULL);
	shownmenu=2;
      }
    } else shownmenu=1;
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!cnc_nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return;
	}
	if(shownmenu==1){
	  prompt(hasaccess?SHPMENU:SHMENU,NULL);
	} else shownmenu=1;
	inp_get(0);
	cnc_begin();
      }
    }

    if((c=cnc_more())!=0){
      cnc_chr();
      switch (c) {
      case 'S':
	makevent("shutdown");
	break;
      case 'U':
	undoevent("shutdown-00");
	break;
      case 'X':
	prompt(LEAVE,NULL);
	return;
      case '?':
	shownmenu=0;
	break;
      case 'A':
	addevent();
	break;
      case 'L':
	listevents();
	listprototypes();
	break;
      case 'C':
	cancelevent();
	break;
      case 'N':
	if(hasaccess){
	  newevent();
	  break;
	}
      case 'D':
	if(hasaccess){
	  delevent();
	  break;
	}
      default:
	prompt(ERRSEL,c);
	cnc_end();
	continue;
      }
    }
    if(fmt_lastresult==PAUSE_QUIT)fmt_resetvpos(0);
    cnc_end();
  }
}


void
done()
{
  msg_close(msg);
  exit(0);
}


int
main(int argc, char **argv)
{
  mod_setprogname(argv[0]);
  init();
  run();
  done();
  return 0;
}
