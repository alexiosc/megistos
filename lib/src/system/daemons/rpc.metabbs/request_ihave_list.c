/*****************************************************************************\
 **                                                                         **
 **  FILE:     request_ihave_list.c                                         **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Distributed club stuff, talking to IHAVE databases.          **
 **  NOTES:    Purposes:                                                    **
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
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  2000/01/08 12:17:03  alexios
 * Added an alarm() call to set a timeout, just in case.
 *
 * Revision 1.0  1999/07/28 23:15:45  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif


#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <rpc/rpc.h>
#include <netdb.h>
#include <sys/socket.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <typhoon.h>

#include "config.h"
#include "metaservices.h"
#include "metabbs.h"
#include "mail.h"
#include "ihavedb.h"


/* Given a starting date (and the usual bbscodes), produce and yield a list of
   IHAVE entries after and including that time. */

struct ihave_list *
distclub_request_ihave_1_svc(ihave_request_t *ihavereq, struct svc_req *req)
{
  static struct ihave_list    retstuff;
  ihave_list_p                cur=NULL;
  int                         i;
  struct sockaddr_in        * caller=svc_getcaller(server);
  int                         fifo[2];
  int                         pid;


  /* Set a reasonable timeout */

  alarm(60);



  bzero(&retstuff,sizeof(retstuff));


#ifdef DEBUG
  fprintf(stderr,"Club \"%s\" IHAVE request from BBS \"%s\" for BBS \"%s\"\n",
	  ihavereq->club,ihavereq->codename,ihavereq->targetname);
#endif


  /* Right. Is the targetted BBS registered with us? */
  
  if((i=find_system(ihavereq->targetname))<0){
    retstuff.result_code=CLR_UNKNOWNCLUB;
    return &retstuff;
  }


  /* It is indeed. But is it really a Megistos BBS? */
  
  if(registered_systems[i].users_online<0){
    retstuff.result_code=CLR_NOTMEGISTOS;
    return &retstuff;
  }


  /* Ok, check club access. */

  this_system=&registered_systems[i];
  if(!loadclubhdr(ihavereq->club)){
    retstuff.result_code=CLR_UNKNOWNCLUB; /* This should never happen */
    return &retstuff;
  }

  
  /* Is this guy allowed to see the club? */

  if(!getclubaccess(caller,ihavereq->codename)){
    retstuff.result_code=CLR_UNKNOWNCLUB; /* This should never happen */
    return &retstuff;
  }


  /* Strategy: chroot to the IHAVE directory; become mortal; create a pair of
     pipes; fork; replace stdin/stdout with the pipes to allow reading from a
     child process (inp_buffer piping); execl() the dump-ihave program. */


  /* Chroot to the IHAVE directory */

#if 0
  if(chroot(apply_prefix(IHAVEDIR))<0){
#ifdef DEBUG
    i=errno;
    fprintf(stderr,"Unable to chroot(\"%s\"): %s\n",
	    apply_prefix(IHAVEDIR),strerror(i));
#endif
    exit(1);
  }
  chdir("/");			/* Change to the new root directory */
#endif
  chdir(apply_prefix(IHAVEDIR));

  /* Become mortal. No going back, this sub-process will exit after
     finishing, anyway. We don't assume the local BBS' uid for security
     reasons: even if chroot() is compromised, it'll be difficult to do much as
     user "nobody". */

  setuid(-1);			/* Nobody */
  setgid(this_system->bbs_gid);

  
  /* Create the pipes. */

  if(pipe(fifo)<0){
#ifdef DEBUG
    i=errno;
    fprintf(stderr,"Unable to create pipes: %s\n",strerror(i));
#endif
    exit(1);
  }



  /* Fork */

  if((pid=fork())<0){
#ifdef DEBUG
    i=errno;
    fprintf(stderr,"Unable to fork(): %s\n",strerror(i));
#endif
    exit(1);
  }


  if(pid==0){			/* Child process first */
    char s[32];
    
    /* Replace stdout with fifo[1] in the child */
    
    close(1);
    if(dup2(fifo[1],1)<0){
#ifdef DEBUG
      i=errno;
      fprintf(stderr,"Unable to dup2(%d,1): %s\n",
	      fifo[1],strerror(i));
#endif
      exit(1);
    }


    /* Execute the ihave-dump binary in the IHAVE directory. */
    
    sprintf(s,"%d",ihavereq->since_time);
    execl("./dump-ihave","dump-ihave",ihavereq->club,s,NULL);


#ifdef DEBUG
    i=errno;
    fprintf(stderr,"Unable to execl() /dump-ihave: %s\n",strerror(i));
#endif
    exit(1);




  } else {			/* Parent process */
    
    /* Replace stdin with fifo[0] in the parent */
    
    close(0);
    if(dup2(fifo[0],0)<0){
#ifdef DEBUG
      i=errno;
      fprintf(stderr,"Unable to dup2(%d,0): %s\n",
	      fifo[0],strerror(i));
#endif
      exit(1);
    }

    
    alarm(30);
    setbuf(stdin,NULL);
    while(!feof(stdin)){
      char a[256],b[256],c[256];
      int d,t;
      if(scanf("%d",&i)==1)if(i==0)break;
      if(scanf("%d %*s %s %s %s %*s %*s %d",&t,a,b,c,&d)!=5)break;
#ifdef DEBUG
      fprintf(stderr,"IHAVE: %s/%s/%s\n",a,b,c);
#endif
      
      if(cur==NULL){
	retstuff.ihave_list_u.ihave_list=
	  (ihave_list_p)malloc(sizeof(struct ihave_entry_t));
	cur=retstuff.ihave_list_u.ihave_list;
      } else {
	cur->next=(ihave_list_p)malloc(sizeof(struct ihave_entry_t));
	cur=cur->next;
      }

      bzero(cur,sizeof(struct ihave_entry_t));
      cur->time=t;
      cur->codename=strdup(a);
      cur->orgclub=strdup(b);
      cur->msgid=strdup(c);
      cur->msgno=d;
    }
  }

  retstuff.result_code=0;
  return &retstuff;
}
