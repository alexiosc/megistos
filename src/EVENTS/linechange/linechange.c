/*****************************************************************************\
 **                                                                         **
 **  FILE:     linechange.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 99                                                 **
 **  PURPOSE:  Change the state of a line.                                  **
 **  NOTES:    This is a useful little event, especially for BBSs that      **
 **            run non-24h lines or that need to grab a line at some point  ** 
 **            in the day (eg for a connection to an ISP).                  **
 **                                                                         **
 **            Event data: -warn n supported (please use!)                  **
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
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRINGS_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"


/*                   123456789012345678901234567890 */
#define AUS_LINECHANGE "MEGISTOS LINE CHANGE EVENT"
 
/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_LINECHANGE "Line %x changed to %s."

#define AUT_LINECHANGE (AUF_EVENT|AUF_INFO|AUF_OPERATION|AUF_OTHER)


void
warn(int line, int n)
{
  int t,h=0,m=0,warntype=LNCHGW3;
  channel_status_t status;

  msg_sys=msg_open("sysvar");
  out_initsubstvars();
  mod_init(INI_SYSVARS|INI_TTYNUM);
  msg_set(msg_sys);

  t=now();
  if(n>=60){
    h=(tdhour(t)+(tdmin(t)+n)/60)%24;
    m=(tdmin(t)+n)%60;
    warntype=LNCHGW1;
  } else if(n>=5)warntype=LNCHGW2;

  if(chan_getname(line)==NULL)exit(1);
  
  channel_getstatus(chan_last->ttyname,&status);
  if((status.result!=LSR_USER) || (status.user[0]=='[') ||
     (!usr_insys(status.user,0)))exit(0);
  
  if(warntype==LNCHGW1){
    sprompt_other(othrshm,msg_buffer,warntype,h,m);
  } else {
    sprompt_other(othrshm,msg_buffer,warntype,n,
		  msg_getunitl(MINSING,n,othruseracc.language-1));
  }
  if(usr_insys(status.user,0))usr_injoth(&othruseronl,msg_buffer,0);
}


void
linechange(int st, int line)
{
  msg_sys=msg_open("sysvar");
  out_initsubstvars();
  mod_init(INI_SYSVARS|INI_TTYNUM);
  msg_set(msg_sys);

  if(chan_getname(line)==NULL)exit(1);
  
  bbsdcommand("hangup",chan_last->ttyname,"");
  sleep(5);
  bbsdcommand("change",chan_last->ttyname,channel_states[st]);
  audit("[LINECHANGE]",AUDIT(LINECHANGE),
	chan_last->channel,channel_states[st]);
  exit(0);
}


int
main(int argc, char *argv[])
{
  mod_setprogname(argv[0]);
  if(argc==5 && !strcmp(argv[3],"-warn")){
    int line, st=LST_NORMAL;
    if(!sscanf(argv[1],"%x",&line))exit(1);
    if(sameas(argv[2],"NORMAL"))st=LST_NORMAL;
    else if(sameas(argv[2],"NORMAL"))st=LST_NORMAL;
    else if(sameas(argv[2],"NOANSWER"))st=LST_NOANSWER;
    else if(sameas(argv[2],"BUSYOUT"))st=LST_BUSYOUT;
    else if(sameas(argv[2],"OFFLINE"))st=LST_OFFLINE;
    if(st!=LST_NORMAL)warn(line,atoi(argv[4]));
  }
  else if(argc!=3){
    fprintf(stderr,"linechange: this is a Megistos BBS event.\n");
    fprintf(stderr,"            Please do not run unless you ");
    fprintf(stderr,"know what you're doing.\n");
    exit(1);
  } else {
    int line,st=LST_NORMAL;
    if(sameas(argv[2],"NORMAL"))st=LST_NORMAL;
    else if(sameas(argv[2],"NORMAL"))st=LST_NORMAL;
    else if(sameas(argv[2],"NOANSWER"))st=LST_NOANSWER;
    else if(sameas(argv[2],"BUSYOUT"))st=LST_BUSYOUT;
    else if(sameas(argv[2],"OFFLINE"))st=LST_OFFLINE;
    if(!sscanf(argv[1],"%x",&line))exit(1);
    linechange(st,line);
  }
  return 0;
}
