/*****************************************************************************\
 **                                                                         **
 **  FILE:     read.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **            B, August 1996, Version 0.6                                  **
 **  PURPOSE:  Reading email messages                                       **
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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/03 00:40:41  alexios
 * Chanded all instances of xlwrite() to write(), since
 * translations are now handled by emud.
 *
 * Revision 0.2  1997/09/12 13:04:17  alexios
 * Emailscan() now scans ALL clubs, not just the ones in the user's
 * Quickscan record. Fixed slight locking problems.
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
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "email.h"
#include "clubs.h"
#ifdef USE_LIBZ
#define WANT_ZLIB_H 1
#endif


#ifdef USE_LIBZ


int
readmsg(struct message *msg)
{
  struct message dummy;
  char fname[256];
  gzFile *zfp;

  sprintf(fname,"%s/%s/"MESSAGEFILE,mkfname(MSGSDIR),
	  msg->club[0]?msg->club:EMAILDIRNAME,
	  (long)msg->msgno);
  if((zfp=gzopen(fname,"rb"))==NULL){
    gzclose(zfp);
    prompt(RDIOERR);
    return -1;
  } else if(gzread(zfp,&dummy,sizeof(struct message))<=0){
    gzclose(zfp);
    prompt(RDIOERR);
    return -1;
  }
  
  prompt(RDMSGHDR);
  for(;;){
    char buffer[1025]={0}, *cp, *ep;
    int bytes=0;

    bytes=gzread(zfp,buffer,sizeof(buffer)-1);
    if(bytes<=0)break;
    else buffer[bytes]=0;

    if(msg->cryptkey)bbscrypt(buffer,bytes,msg->cryptkey);

    cp=buffer;
    while(*cp){
      if((ep=strchr(cp,'\n'))==NULL){
	write(0,cp,strlen(cp));
	break;
      } else {
	*ep=0;
	write(0,cp,strlen(cp));
	*ep='\n';
	write(0,ep,1);
 	if(screenpause()==PAUSE_QUIT) return 1;
	cp=ep+1;
      }
    }
  }

  prompt(RDMSGFTR);
  
  gzclose(zfp);
  return 0;
}


#else /* DON'T USE_LIBZ */


int
readmsg(struct message *msg)
{
  struct message dummy;
  char fname[256];
  FILE *fp;

  sprintf(fname,"%s/%s/"MESSAGEFILE,mkfname(MSGSDIR),
	  msg->club[0]?msg->club:EMAILDIRNAME,
	  msg->msgno);
  if((fp=fopen(fname,"r"))==NULL){
    fclose(fp);
    prompt(RDIOERR);
    return -1;
  } else if(fread(&dummy,sizeof(struct message),1,fp)!=1){
    fclose(fp);
    prompt(RDIOERR);
    return -1;
  }
  
  prompt(RDMSGHDR);
  while(!feof(fp)){
    char buffer[1025]={0}, *cp, *ep;
    int bytes=0;

    bytes=fread(buffer,1,sizeof(buffer)-1,fp);
    if(!bytes)break;
    else buffer[bytes]=0;

    if(msg->cryptkey)bbscrypt(buffer,bytes,msg->cryptkey);

    cp=buffer;
    while(*cp){
      if((ep=strchr(cp,'\n'))==NULL){
	write(0,cp,strlen(cp));
	break;
      } else {
	*ep=0;
	write(0,cp,strlen(cp));
	*ep='\n';
	write(0,ep,1);
 	if(fmt_screenpause()==PAUSE_QUIT) return 1;
	cp=ep+1;
      }
    }
  }

  prompt(RDMSGFTR);
  
  fclose(fp);
  return 0;
}


#endif /* USE_LIBZ */


static void
readupdatemsg(int readopt, struct message *msg)
{
  struct emailuser ecuser;
  struct message m;
  
  getmsgheader(msg->msgno,&m);
  m.timesread++;
  if(m.flags&MSF_RECEIPT)sendreceipt(&m);
  if(m.flags&MSF_FILEATT)downloadatt(&m);
  writemsgheader(&m);

  if(readopt==0 || readopt==1){
    readecuser(thisuseracc.userid,&ecuser);
    ecuser.lastemailread=max(m.msgno,ecuser.lastemailread);
    writeecuser(thisuseracc.userid,&ecuser);
  }
}


static char
readmenu(struct message *msg, char defopt)
{
  char opt, options[32];
  int menu=RDRMNU1, msgno, res;
  
  strcpy(options,"NPRECF#");


  /* If it's a reply, we can backtrack */

  if(msg->flags&MSF_REPLY){
    menu=RDRMNU2;
    strcat(options,"B");
  }


  /* If it's a signup message, we can delete the user */

  if(msg->flags&MSF_SIGNUP && strcmp(msg->from,thisuseracc.userid) &&
     (sameas(thisuseracc.userid,SYSOP)||hassysaxs(&thisuseracc,USY_DELETE))){
    menu=RDRMNU3;
    strcat(options,"D");
  }


  /* If it's a auto-forwarded message, we can cancel forwarding. */

  if(msg->flags&MSF_AUTOFW){
    menu=RDRMNU4;
    strcat(options,"S");
  }

  for(;;){
    inp_setflags(INF_HELP);
    res=get_menu(&opt,1,0,menu,RDMNUR,options,RDDEF,defopt);
    inp_clearflags(INF_HELP);
    if(!res)return 'X';
    else if(res<0){
      prompt(menu+1);
      cnc_end();
      continue;
    }
    break;
  }

  msgno=msg->msgno;
  getmsgheader(msgno,msg);
  switch(opt){
  case 'N':
  case 'P':
  case '#':
  case 'X':
    return opt;
  case 'E':
    erasemsg(0,msg);
    return 1;
  case 'C':
    copymsg(msg);
    return 1;
  case 'F':
    forwardmsg(msg);
    return 1;
  case 'R':
    reply(msg,0);
    return 'N';
  case 'B':
    return -backtrack(msg);
  case 'S':
    stopautofw(msg);
    return 'N';
  case 'D':
    deleteuser(msg);
    return 0;
  default:
    return 'N';
  }
}


/* Present and handle the header menu */

char
headermenu(char defopt)
{
  int res;
  char opt;

  for(;;){
    inp_setflags(INF_HELP);
    res=get_menu(&opt,1,0,RDSCNM,RDSCNR,"NP#RCX",RDDEF,defopt);
    inp_clearflags(INF_HELP);
    
    if(!res)return 'X';
    else if(res==-1){
      prompt(RDSCNMH);
      cnc_end();
      continue;
    }
    break;
  }

  return opt;
}


int
locatemsg(int *msgno, int *sequencebroken, int targetmsg, int dir, int mode)
{
  int j;

  if(*sequencebroken){

    /* If the sequence is broken, seek the message. */
    
    if(mode==OPT_FROMYOU){
      j=findmsgfrom(msgno,thisuseracc.userid,targetmsg,dir);
    } else {
      j=findmsgto(msgno,thisuseracc.userid,targetmsg,dir);
    }
    
    /* Check if we've exceeded search bounds and search again. */
    
    if(j!=BSE_FOUND){
      int tdir=(j==BSE_END)?2:4;

      if(mode==OPT_FROMYOU)
	j=findmsgfrom(msgno,thisuseracc.userid,targetmsg,tdir);
      else j=findmsgto(msgno,thisuseracc.userid,targetmsg,tdir);

      /* Re-establish the sequence along the right direction */

      if(j==BSE_FOUND){
	if(mode==OPT_FROMYOU){
	  findmsgfrom(msgno,thisuseracc.userid,*msgno,dir);
	} else {
	  findmsgto(msgno,thisuseracc.userid,*msgno,dir);
	}
      }
    }
    
    *sequencebroken=0;
    
  } else {
    
    /* ...otherwise, get the next or previous message in the sequence. */
    
    if(mode==OPT_FROMYOU){
      j=npmsgfrom(msgno,thisuseracc.userid,targetmsg,dir);
    } else {
      j=npmsgto(msgno,thisuseracc.userid,targetmsg,dir);
    }
  }

  return j;
}


/* Read email. */

int
startreading(int mode, int startmsg)
{
  int i;                   /* Message number being read (hopefully) */
  int dir=BSD_GT;          /* Starting movement direction */
  int sequencebroken=1;    /* Re-establish the message sequence */
  int oldmsgno=startmsg;   /* Previously read message */
  int dontshow=0;          /* Don't display msg header this time round */
  int nummsgs=0;           /* Number of messages shown so far */
  int optdecided;          /* Don't reprocess navigation commands */
  int bound=0;             /* Reached beginning/end of list */
  int targetmsg=startmsg;  /* Target message when jumping around */

  char lock[256];          /* Message lock */
  char tmp[256];           /* Dogsbody */

  char opt;                /* Menu selection */
  char defopt;             /* Default menu option */


  if(startmsg<0) startmsg=oldmsgno=1;

  cnc_end();
  for(i=startmsg;;){
    int msgno;
    int j;
    struct message msg;


    /* Find the message */

    oldmsgno=msgno;
    msgno=-1;
    setclub(NULL);
    j=locatemsg(&msgno,&sequencebroken,i,dir,mode);


    /* If no more messages, prompt the user */

    if(j!=BSE_FOUND){
      if(dir==BSD_LT)prompt(RDBEG);
      else if(dir==BSD_GT){
	prompt(RDEND);
      }
      bound=dir;
      defopt=mode==OPT_PTOYOU?'X':'C';
      dontshow=1;
      sequencebroken=1;
      msgno=oldmsgno;
    } else {
      defopt='R';
      bound=0;
    }


    /* Produce a MISS message */

    if(msgno!=targetmsg && targetmsg>=0 && targetmsg!=LASTMSG){
      prompt(RDMISS,targetmsg);
      bound=0;
    }
    targetmsg=-1;


    /* Lock the current message */

    if(msgno!=oldmsgno){
      dontshow=0;

      if(lock[0])lock_rm(lock);
      sprintf(tmp,"%d",msgno);
      sprintf(lock,MSGREADLOCK,thisuseronl.channel,EMAILCLUBNAME,tmp);
      lock_place(lock,"reading");
    }


    /* Read and display the message header, if we need to. */

    if(!dontshow){

      /* Read the message header. Be paranoid about it. */
    
      if(getmsgheader(msgno,&msg)!=BSE_FOUND){
	if(dir==BSD_GT)i=msgno+1;
	else i=msgno-1;
	continue;
      }

      /* Show the message's header. */

      showheader(EMAILCLUBNAME,&msg);
    };
    nummsgs++;

    
    /* Header menu */

  bound_hit:
    opt=headermenu(defopt);
    
    for(optdecided=0;!optdecided;){
      switch(opt){
      case 'N':
	if(bound==BSD_GT){
	  prompt(RDEND);
	  goto bound_hit;
	}
	dontshow=0;
	optdecided=1;
	i=msgno+1;
	dir=BSD_GT;
	break;

      case 'P':
	if(bound==BSD_LT){
	  prompt(RDBEG);
	  goto bound_hit;
	}
	dontshow=0;
	optdecided=1;
	i=msgno-1;
	dir=BSD_LT;
	break;

      case '#':
	{
	  int newmsgno=msgno;
	  if(getrdmsgno(&newmsgno,RDGONUM,RDGOHLP,0,0)){
	    i=msgno=newmsgno;
	    sequencebroken=1;
	    dontshow=0;
	  } else {
	    i=msgno;
	    dontshow=1;
	  }
	  targetmsg=msgno;
	  optdecided=1;
	  dir=BSD_GT;
	  break;
	}

      case 'R':
	readmsg(&msg);
	readupdatemsg(mode,&msg);
	do{
	  opt=readmenu(&msg,dir==BSD_GT?'N':'P');
	  optdecided=1;

	  if(opt<0){
	    targetmsg=i=-opt;
	    dir=BSD_GT;
	    opt=1;
	  } else if(!opt){
	    oldmsgno=msgno;
	    opt=0;
	  } else if(opt==1) {
	    sequencebroken=1;
	    opt='N';
	    optdecided=0;
	    break;
	  } else {
	    optdecided=0;
	    break;
	  }
	} while(opt<=0);
	break;

      case 'C':
      case 'X':
      default:
	cnc_end();
	return opt;
      }
    }
  }

  return 'X';
}


void
emailscan(int reademail, int readopt, int startmsg)
{
  char res='C';
  int count;

  if(reademail)res=startreading(readopt,startmsg);
  if(res!='C')return;

  startqsc();
  count=0;
  do{
    struct lastread *l=getqsc();
    if(l==NULL)break;
    if(getclubax(&thisuseracc,l->club)<CAX_READ)continue;
    count++;
  }while(nextqsc());
  doneqsc();

  if(count){
    prompt(RDTRCLUB);
    quickscan=1;
    keyscan=0;
    filescan=0;
    inemail=readopt;
    allclubs=1;
    scanmessages();
    allclubs=0;
  }
}


void
emailread()
{
  char opt;
  int startmsg, readopt=0, msgno=-1, j;
  struct emailuser ecuser;

  if(!readecuser(thisuseracc.userid,&ecuser))return;

  if(!get_menu(&opt,1,0,RDWHAT,RDWHATR,"TPF",0,0))return;
  switch(opt){
  case 'T':
    readopt=0;
    break;
  case 'P':
    readopt=1;
    break;
  case 'F':
    readopt=2;
    break;
  }


  /* Locate the first new or last old email message */

  setclub(NULL);
  if(readopt==OPT_FROMYOU){
    j=findmsgfrom(&msgno,thisuseracc.userid,ecuser.lastemailread+1,BSD_GT);
    if(j!=BSE_FOUND){
      j=findmsgfrom(&msgno,thisuseracc.userid,ecuser.lastemailread+1,BSD_LT);
    }
  } else {
    j=findmsgto(&msgno,thisuseracc.userid,ecuser.lastemailread+1,BSD_GT);
    if(j!=BSE_FOUND){
      j=findmsgto(&msgno,thisuseracc.userid,ecuser.lastemailread+1,BSD_LT);
    }
  }

  /* If we're only reading personal mail and there is none, stop here */

  if(j!=BSE_FOUND){
    prompt(RDNOMSGT+readopt);
    cnc_end();
    if(readopt==OPT_PTOYOU)return;
    emailscan(0,readopt,startmsg);
    rmlocks();
    return;
  }/* else msgno=ecuser.lastemailread+1;*/


  /* Ask the starting message number */

  if(!getrdmsgno(&startmsg,RDASKNO,RDASKH,RDASKNOR,msgno))return;


  /* And begin reading at that point */

  emailscan(1,readopt,startmsg);


  /* And remove all the club locks as a sanity check */

  rmlocks();  
}
