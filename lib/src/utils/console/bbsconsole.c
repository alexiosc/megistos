/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsconsole.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Implement a minimal bbs console.                             **
 **  NOTES:    Minimalist version.                                          **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.2  2001/04/16 21:56:28  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif

#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include <bbs.h>
#include <mbk/mbk_remsys.h>


int pgstmo; 
promptblock_t *msg;
int       t=0;


void
waitchannels()
{
  int  i,j;
  char fname[256];
  struct stat st;

  for(j=0;j<30;j++){
    usleep(100000);		/* .1 sec */
    for(i=0;i<chan_count;i++){
      sprintf(fname,"%s/.status-%s",CHANDEFDIR,channels[i].ttyname);
      bzero(&st,sizeof(st));
      stat(fname,&st);
      if(st.st_mtime>t){
	t=st.st_mtime;
	return;
      }
    }
  }
}


void
listchannels()
{
  int  i, showntelnetline=0, res;
  channel_status_t status;

  prompt(CHNLSTHDR,NULL);

  for(i=0;i<chan_count;i++){
    int ch=channels[i].channel;

    res=channel_getstatus(channels[i].ttyname,&status);
    
    if(res<0 || status.result==LSR_LOGOUT){
      if(channels[i].flags&TTF_TELNET)status.result=LSR_OK;
      else status.result=-1;	/* Temporarily unknown state */
    }

    if(channels[i].flags&TTF_TELNET && showntelnetline && (status.result==LSR_OK))
      continue;

    switch(status.result){
    case LSR_INIT:
      prompt(CHNLSTTBI,ch,channel_states[status.state]);
      break;
    case LSR_RING:
      prompt(CHNLSTTBR,ch);
      break;
    case LSR_ANSWER:
      prompt(CHNLSTTBA,ch);
      break;
#ifdef HAVE_METABBS
    case LSR_METABBS:
      prompt(CHNLSTTBM,ch,channel_baudstg(status.baud),status.user);
      break;
#endif
    case LSR_LOGIN:
      prompt(CHNLSTTBL,ch,channel_baudstg(status.baud));
      break;
    case LSR_USER:
      {
	if(usr_insys(status.user,0)){
	  time_t t=time(NULL)-othruseronl.lastconsolepage;
	  if(t<=60)print("\007");
	  prompt(CHNLSTTBU,ch,channel_baudstg(status.baud),status.user,
		 t>pgstmo?"":msg_getunit(CHNLSTPGS,1));
	}
	break;
      }
    case LSR_FAIL:
      prompt(CHNLSTTBF,ch,channel_states[status.state]);
      break;
    case LSR_RELOGON:
      prompt(CHNLSTTBL,ch,channel_states[status.state]);
      break;
    case LSR_LOGOUT:
      prompt(CHNLSTTBQ,ch,channel_states[status.state]);
      break;
    case LSR_OK:
      prompt(CHNLSTTBO,ch,channel_states[status.state]);
      showntelnetline=channels[i].flags&TTF_TELNET;
      break;
    default:
      prompt(CHNLSTTBE,ch);
    }
    if(fmt_lastresult==PAUSE_QUIT)return;
  }
  prompt(CHNLSTFTR);
}


int
main()
{
  mod_init(INI_TTYNUM|INI_OUTPUT|INI_SYSVARS|INI_ERRMSGS|INI_CLASSES);
  msg=msg_open("remsys");
  pgstmo=msg_int(PGSTMO,1,9999)*60;
  for(;;){
    waitchannels();
    puts("\033[H\033[2J");fflush(stdout);
    listchannels();
  }
}
