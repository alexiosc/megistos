/*****************************************************************************\
 **                                                                         **
 **  FILE:     charge.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997                                               **
 **  PURPOSE:  Charge credits to the users                                  **
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
 * Revision 1.2  2001/04/16 21:56:33  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.7  1999/08/13 17:06:02  alexios
 * Removed the FORCEIDLE condition. Telnet line timeouts are now
 * handled internally by emud.
 *
 * Revision 0.6  1999/07/18 22:00:00  alexios
 * Numerous changes wrt auditing and MetaBBS.
 *
 * Revision 0.5  1998/12/27 16:21:05  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 *
 * Revision 0.4  1998/07/26 21:11:32  alexios
 * No changes.
 *
 * Revision 0.3  1998/07/24 10:25:55  alexios
 * Added idle timeout zapping of telnetted users in caase the
 * connection has silently died without notification.
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:04:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/30 13:10:43  alexios
 * Initial revision. Adequate.
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
#define WANT_PWD_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIO_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"
#include "bbsd.h"


int numusers=0;

#ifdef HAVE_METABBS
int oldnumusers=0;
int lines_free=0;
int oldlines_free=0;
#endif


static void
suptimeouts(char *tty)
{
  struct shmuserrec *ushm=NULL;
  int shmid;
  char supid[256];
  FILE *fp;

  sprintf(supid,"%s/.shmid-[SIGNUP-%s]",ONLINEDIR,tty);

  if((fp=fopen(supid,"r"))==NULL) return;
  if(!fscanf(fp,"%d",&shmid)) {
    error_logsys("Unable to read file %s",supid);
    return;
  }
  fclose(fp);

  if((ushm=(struct shmuserrec *)shmat(shmid,NULL,0))==NULL)return;

  if(ushm->onl.idlezap){
    ushm->onl.timeoutticks++;

#ifdef DEBUG
    fprintf(stderr,"%s: ticks=%d, limit=%d\n",
	    tty,
	    ushm->onl.timeoutticks,
	    ushm->onl.idlezap*JIFFIESPERMIN);
#endif

    if((ushm->onl.timeoutticks)>=(ushm->onl.idlezap*JIFFIESPERMIN)){
      char fname[256];
      sprintf(fname,DEVDIR"/%s",tty);
      if((fp=fopen(fname,"w"))!=NULL){
	write(fileno(fp),msg_getl(IDLEBYE,ushm->acc.language-1),
	      strlen(msg_buffer));
	fclose(fp);
      }
#ifdef DEBUG
      fprintf(stderr,"disconnecting %s\n",tty);
#endif

      channel_disconnect(tty);

      sprintf(supid,"%s/.shmid-[SIGNUP-%s]",ONLINEDIR,tty);
      unlink(supid);
    }
  }

  shmdt((char *)ushm);
}


void
charge()
{
  int i;

  refreshclasses();
  refreshsysvars();

#ifdef HAVE_METABBS
  oldnumusers=numusers; /* Calculate difference in numusers for registration */
#endif

  numusers=0;
  for(i=0;i<chan_count;i++){
    struct shmuserrec *ushm=NULL;
    channel_status_t status;

    if(!channel_getstatus(channels[i].ttyname,&status))continue;

    if(status.result!=LSR_USER)continue;

    numusers++;			/* This is a line with a user on it */

    if(!strcmp(status.user,"[SIGNUP]")){
      suptimeouts(channels[i].ttyname);
      continue;
    }

    if(!strcmp(status.user,"[UNIX]"))continue;
      
    if(!usr_insystem(status.user,0,&ushm))continue;
    if(!ushm->onl.userid[0])continue;

    /* User related charges and time counts */
    
    ushm->onl.tick=(ushm->onl.tick+1)%JIFFIESPERMIN;
    ushm->onl.fraccharge+=(ushm->onl.credspermin)/JIFFIESPERMIN;

    if(!ushm->onl.tick){
      long charge=((long)ushm->onl.fraccharge)/100L;
      classrec_t *class=cls_find(ushm->acc.curclss);

      sysvar->timever++;
      ushm->onl.onlinetime++;
      ushm->acc.timetdy++;
      ushm->acc.timever++;

      /* Credit charges */

      if(charge){
	if(class && class->flags&CLF_NOCHRGE){
	  ushm->onl.fraccharge=0;
	} else {
	  ushm->acc.credits-=charge;
	  ushm->acc.credsever+=charge;
	  ushm->onl.statcreds+=charge;
	  ushm->onl.fraccharge%=100;
	  if(ushm->acc.credits<=0){
	    ushm->acc.credits=0;
	    ushm->onl.lastpage=EXIT_CREDS;
	    byebye(ushm,NOCRDBYE);
	    if(class)usr_setclass(ushm->acc.userid,class->nocreds,0);
	  } else if((float)((float)ushm->acc.credits -
			    (float)((float)ushm->onl.credspermin/100.0))<=0.0){
	    usr_injoth(&(ushm->onl),msg_getl(NOCREDS,ushm->acc.language-1),0);
	  }
	}
      }

      /* Time limit per call */

      if(class && class->limpercall>=0){
	if(ushm->onl.onlinetime>=class->limpercall){
	  ushm->onl.lastpage=EXIT_TIME;
	  byebye(ushm,NOCTIMBYE);
	  if(class)usr_setclass(ushm->acc.userid,class->nocreds,0);
	} else if(ushm->onl.onlinetime+1>=class->limpercall){
	  usr_injoth(&(ushm->onl),msg_getl(NOCTIM,ushm->acc.language-1),0);
	}
      }
      
      /* Daily time limit */

      if(class && class->limperday>=0){
	if(ushm->acc.timetdy>=class->limperday){
	  ushm->onl.lastpage=EXIT_TIME;
	  byebye(ushm,NODTIMBYE);
	  if(class)usr_setclass(ushm->acc.userid,class->nocreds,0);
	} else if(ushm->acc.timetdy+1>=class->limperday){
	  usr_injoth(&(ushm->onl),msg_getl(NODTIM,ushm->acc.language-1),0);
	}
      }
    }

    /* Inactivity Timeout */

    if(ushm->onl.idlezap){
      if(!(ushm->onl.flags&(OLF_NOTIMEOUT|OLF_BUSY|OLF_ZAPBYPASS))
	 /*|| (ushm->onl.flags&OLF_FORCEIDLE)*/){
	if((++ushm->onl.timeoutticks)>=(ushm->onl.idlezap*JIFFIESPERMIN)){
	  /*audit(ushm->onl.channel,AUDIT(DISCON),
		ushm->onl.userid,
		baudstg(ushm->onl.baudrate));*/
	  ushm->onl.lastpage=EXIT_TIMEOUT;
	  byebye(ushm,IDLEBYE);
	} else if(ushm->onl.timeoutticks==((ushm->onl.idlezap-1)*JIFFIESPERMIN)){
	  sprintf(msg_buffer,msg_getl(IDLEWRN,ushm->acc.language-1),
		  ushm->onl.timeoutticks/JIFFIESPERMIN);
	  usr_injoth(&(ushm->onl),msg_buffer,0);
	}
      }
    }

    shmdt((char *)ushm);
  }

#ifdef HAVE_METABBS
  
  oldlines_free=lines_free;
  lines_free=max(0,sysvar->tnlmax-chan_telnetlinecount());
  
  
  /* Re-register with the MetaBBS service so that line/user counters
     are up to date. */
  
  if((numusers!=oldnumusers) || (lines_free!=oldlines_free))
    last_registration_time=0;

#ifdef DEBUG
  fprintf(stderr,"numusers=%d oldnumusers=%d lines_free=%d\n",
	  numusers,oldnumusers,lines_free);
#endif

#endif
}
