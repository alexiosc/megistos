/*****************************************************************************\
 **                                                                         **
 **  FILE:     clublist.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1995                                               **
 **            B, August 1996                                               **
 **  PURPOSE:  List Club messages                                           **
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
 * Revision 1.2  2001/04/16 21:56:31  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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
const char *__RCS=RCS_VER;
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "clubs.h"
#include "email.h"


static void
msglist(int msg, int method, int files)
{
  int j,msgno=msg;
  struct message m;
  int f=1, c;

  j=findmsgnum(&msgno,msg,BSD_GT);
  if(msgno<0 || j!=BSE_FOUND){
    j=findmsgnum(&msgno,msg,BSD_LT);
    if(msgno<0 || j!=BSE_FOUND){
      prompt(RLBNMSG);
      cnc_end();
      return;
    }
  }

  if(msgno!=msg && msg!=LASTMSG && msg>=0)prompt(RLMISS,msg);

  inp_nonblock();

  for(;msgno>0;){
    int i=0;
    if(getmsgheader(msgno,&m)==BSE_FOUND){
      char subj[256], date[16];
      int k;

      if(read(fileno(stdin),&c,1)&&
	 ((c==13)||(c==10)||(c==27)||(c==15)||(c==3)))
	fmt_lastresult=PAUSE_QUIT;

      if(files && ((m.flags&MSF_FILEATT)==0))goto nextone;

      if(f){
	if(!method)prompt(RLBHDR);
	else prompt(RLTHDR);
	f=0;
      }

      if(fmt_lastresult==PAUSE_QUIT)break;
      if(!method){
	strcpy(subj,m.subject);
	k=max(0,thisuseracc.scnwidth-35);
	if(k<256)subj[k]=0;

	strcpy(date,strdate(m.crdate));
	/*memcpy(&date[7],&date[9],3);*/
	prompt(RLBTAB,msgno,m.from,date,strtime(m.crtime,1),subj);
      } else showheader(clubhdr.club,&m);
      if(method==2)readmsg(&m);
    }
    i=msgno;

  nextone:
    msg=msgno+1;
    j=npmsgnum(&msgno,msg,BSD_GT);
    if(j==BSE_NFOUND)break;
    if(i==msgno)break;
  }

  inp_block();

  if(fmt_lastresult==PAUSE_QUIT)prompt(RLABORT);
  else if(!f)prompt(method?RLDONE:RLBFTR);
  else {
    prompt(RLBNMSG);
  }
}


static void
qmsglist(int method, int files)
{
  int j,msgno=0,msg=0;
  struct message m;
  int first=1, count=0, newmsg=0, f=1;
  int c;

  startqsc();

  inp_nonblock();

  do{
    struct lastread *lastread=getqsc();

    if(read(fileno(stdin),&c,1)&&
       ((c==13)||(c==10)||(c==27)||(c==15)||(c==3)))
      fmt_lastresult=PAUSE_QUIT;

    if(first && (lastread==NULL)){
      prompt(QSEMPTY);
      inp_block();
      return;
    }
    first=0;

    if((lastread->flags&LRF_QUICKSCAN)==0)continue;
    if(getclubax(&thisuseracc,lastread->club)<CAX_READ)continue;
    
    count++;

    if(fmt_lastresult==PAUSE_QUIT){
      prompt(RLABORT);
      inp_block();
      return;
    }

    prompt(QSSCAN,lastread->club);
    enterclub(lastread->club);
    msgno=msg=lastread->lastmsg+1;

    j=findmsgnum(&msgno,msg,BSD_GT);
    if(msgno<0 || j!=BSE_FOUND)continue;

    newmsg++;
    f=1;

    for(;msgno>0;){
      int i=0;
      if(getmsgheader(msgno,&m)==BSE_FOUND){
	char subj[256], date[16];
	int k;
	
	if(read(fileno(stdin),&c,1)&&
	   ((c==13)||(c==10)||(c==27)||(c==15)||(c==3)))
	  fmt_lastresult=PAUSE_QUIT;

	if(files && ((m.flags&MSF_FILEATT)==0))goto nextone;

	if(f){
	  if(!method)prompt(RLBHDR);
	  else prompt(RLTHDR);
	  f=0;
	}
	
	if(fmt_lastresult==PAUSE_QUIT){
	  prompt(RLABORT);
	  break;
	}
	if(!method){
	  strcpy(subj,m.subject);
	  k=max(0,thisuseracc.scnwidth-35);
	  if(k<256)subj[k]=0;
	  
	  strcpy(date,strdate(m.crdate));
	  /*memcpy(&date[7],&date[9],3);*/
	  prompt(RLBTAB,msgno,m.from,date,strtime(m.crtime,1),subj);
	} else showheader(clubhdr.club,&m);
	if(method==2)readmsg(&m);
      }
      if(fmt_lastresult==PAUSE_QUIT){
	prompt(RLABORT);
	break;
      }
      i=msgno;
      
    nextone:
      msg=msgno+1;
      j=findmsgnum(&msgno,msg,BSD_GT);
      if(i==msgno || j!=BSE_FOUND)break;
    }
    if(fmt_lastresult==PAUSE_QUIT)prompt(RLABORT);
    else if(!f)prompt(method?RLDONE:RLBFTR);

    if(fmt_lastresult==PAUSE_QUIT){
      inp_block();
      return;
    }
  } while (nextqsc());

  inp_block();

  if(!count)prompt(QSEMPTY);
  else if(!newmsg)prompt(QSNONEW);
  else prompt(QSEND);
}


void
listmessages(int file)
{
  char opt;
  int i, msg=0;

  for(;;){
    inp_setflags(INF_HELP);
    i=get_menu(&opt,0,0,RLMNU,RLMNUR,"BTF",0,0);
    inp_clearflags(INF_HELP);
    if(!i)return;
    if(i==-1){
      prompt(RLMNUH);
      cnc_end();
      continue;
    } else break;
  }

  if(!quickscan){
    startqsc();
    if(!getrdmsgno(&msg,RLASK,RLASKH,RLASKR,getlastread(clubhdr.club))){
      doneqsc();
      return;
    }
  }

  switch(opt){
  case 'B':
    if(quickscan)qmsglist(0,file);
    else msglist(msg,0,file);
    break;
  case 'T':
    if(quickscan)qmsglist(1,file);
    else msglist(msg,1,file);
    break;
  case 'F':
    if(quickscan)qmsglist(2,file);
    else msglist(msg,2,file);
  }
}
