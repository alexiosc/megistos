/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsshutdown.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, February 95                                               **
 **  PURPOSE:  Shutdown the BBS (i.e. Kill System)                          **
 **  NOTES:    Under Linux, the kill system command is implemented easily.  **
 **            We *DON'T* wan't to shutdown the whole system, just the BBS. **
 **            This is done by forbidding access to the system to users.    **
 **            Bbsshutdown does exactly this: forces all BBS lines except   **
 **            (C)onsole lines (defined in /bbs/channel.defs/CHANNELS) to   **
 **            BUSY-OUT mode.                                               **
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
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.6  2000/01/06 11:36:53  alexios
 * Added AUF_EVENT to the audit trail entry for a BBS shutdown.
 * Made main() return a value.
 *
 * Revision 1.5  1998/12/27 14:44:14  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 1.4  1998/07/24 10:07:34  alexios
 * Upgraded to version 0.6 of library.
 *
 * Revision 1.3  1997/11/06 20:08:47  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.2  1997/11/06 16:48:00  alexios
 * Changed calls to audit() so they use the new auditing scheme.
 * Added an AUT_ flag for the same reason.
 *
 * Revision 1.1  1997/08/30 12:50:29  alexios
 * Changed bladcommand() calls to bbsdcommand().
 *
 * Revision 1.0  1997/08/26 15:47:09  alexios
 * Initial revision
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
#define AUS_SHUTDOWN "MEGISTOS SYSTEM SHUTDOWN"
 
/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_SHUTDOWN "All non-console channels have been shut down."

#define AUT_SHUTDOWN (AUF_INFO|AUF_EVENT|AUF_OPERATION|AUF_OTHER)


void
warn(int n)
{
  int i,t,h=0,m=0,warntype=SHTDW3;
  channel_status_t status;

  msg_sys=msg_open("sysvar");
  out_initsubstvars();
  mod_init(INI_SYSVARS|INI_TTYNUM);
  msg_set(msg_sys);

  t=now();
  if(n>=60){
    h=(tdhour(t)+(tdmin(t)+n)/60)%24;
    m=(tdmin(t)+n)%60;
    warntype=SHTDW1;
  } else if(n>=5)warntype=SHTDW2;

  for(i=0;i<chan_count;i++){
    channel_getstatus(channels[i].ttyname,&status);
    if((status.result!=LSR_USER) || (status.user[0]=='[') ||
       (!usr_insys(status.user,0)))continue;

    if(warntype==SHTDW1){
      sprompt_other(othrshm,msg_buffer,warntype,h,m);
    } else {
      sprompt_other(othrshm,msg_buffer,warntype,n,
		    msg_getunitl(MINSING,n,othruseracc.language-1));
    }
    if(usr_insys(status.user,0))usr_injoth(&othruseronl,msg_buffer,0);
  }
}


void
bbsshutdown()
{
  channel_status_t status;
  int  i;
  
  msg_sys=msg_open("sysvar");
  out_initsubstvars();
  mod_init(INI_SYSVARS|INI_TTYNUM);
  msg_set(msg_sys);

  for(i=0;i<chan_count;i++){
    if(channels[i].flags&TTF_CONSOLE)continue;
    if(!channel_getstatus(channels[i].ttyname,&status))continue;
    if(status.result==LSR_USER){
      bbsdcommand("hangup",channels[i].ttyname,"");
      usleep(250000);
    }
    
    bbsdcommand("change",channels[i].ttyname,"BUSY-OUT");
  }
  audit("[SHUTDOWN]",AUDIT(SHUTDOWN));
  exit(0);
}


int
main(int argc, char *argv[])
{
  mod_setprogname(argv[0]);
  if(argc==3 && !strcmp(argv[1],"-warn"))warn(atoi(argv[2]));
  else if(argc!=1){
    fprintf(stderr,"bbsshutdown: this is a Megistos BBS event.\n");
    fprintf(stderr,"             Please do not run unless you ");
    fprintf(stderr,"know what you're doing.\n");
    exit(1);
  } else bbsshutdown();
  return 0;
}
