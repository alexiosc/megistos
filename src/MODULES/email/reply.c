/*****************************************************************************\
 **                                                                         **
 **  FILE:     reply.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 1995, Version 0.5                                    **
 **  PURPOSE:  Reply to messages                                            **
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
 * Revision 0.6  1999/07/18 21:21:38  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:04:17  alexios
 * Fixed bug that would prohibit quoting club messages while
 * replying.
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
#ifdef USE_LIBZ
#define WANT_ZLIB_H 1
#endif


#ifdef USE_LIBZ


int
quotemessage(struct message *msg, char *quotefn)
{
  struct emailuser ecuser;
  struct message dummy;
  int yes, col1=1;
  FILE *quote;
  gzFile *zfp;
  char fname[256];
  
  readecuser(thisuseracc.userid,&ecuser);
  if(ecuser.prefs&ECP_QUOTEASK){
    if(!get_bool(&yes,QMASK,QMERR,0,0))return 0;
  } else yes=(ecuser.prefs&ECP_QUOTEYES)!=0;

  if(!yes)return 1;

  sprintf(fname,"%s/%s/"MESSAGEFILE,mkfname(MSGSDIR),
	  msg->club[0]?msg->club:EMAILDIRNAME,
	  (long)msg->msgno);
  if((zfp=gzopen(fname,"rb"))==NULL){
    gzclose(zfp);
    return 1;
  }
  if((quote=fopen(quotefn,"w"))==NULL){
    gzclose(zfp);
    fclose(quote);
    return 1;
  }
  
  if(gzread(zfp,&dummy,sizeof(struct message))<=0){
    gzclose(zfp);
    fclose(quote);
    return 1;
  }
  
  for(;;){
    char buffer[1025]={0}, *cp, *ep;
    int bytes=0;
    
    bytes=gzread(zfp,buffer,sizeof(buffer)-1);
    if(bytes<=0)break;
    else buffer[bytes]=0;
    
    if(msg->cryptkey)bbscrypt(buffer,bytes,dummy.cryptkey);
    
    cp=buffer;
    while(*cp){
      if((ep=strchr(cp,'\n'))==NULL){
	if(col1)fprintf(quote,"> ");
	col1=0;
	fprintf(quote,"%s",cp);
	break;
      } else {
	*ep=0;
	if(col1)fprintf(quote,"> %s\n",cp);
	else fprintf(quote,"%s\n",cp);
	col1=1;
	cp=ep+1;
      }
    }
  }
  fprintf(quote,"\n");
  
  gzclose(zfp);
  fclose(quote);
  return 1;
}


#else /* DON'T USE_LIBZ */


int
quotemessage(struct message *msg, char *quotefn)
{
  struct emailuser ecuser;
  struct message dummy;
  int yes, col1=1;
  FILE *fp, *quote;
  char fname[256];
  
  readecuser(thisuseracc.userid,&ecuser);
  if(ecuser.prefs&ECP_QUOTEASK){
    if(!get_bool(&yes,QMASK,QMERR,0,0))return 0;
  } else yes=(ecuser.prefs&ECP_QUOTEYES)!=0;

  if(!yes)return 1;

  sprintf(fname,"%s/%s/"MESSAGEFILE,mkfname(MSGSDIR),
	  msg->club[0]?msg->club:EMAILDIRNAME,
	  msg->msgno);
  if((fp=fopen(fname,"r"))==NULL){
    fclose(fp);
    return 1;
  }
  if((quote=fopen(quotefn,"w"))==NULL){
    fclose(fp);
    fclose(quote);
    return 1;
  }
  
  if(fread(&dummy,sizeof(struct message),1,fp)!=1){
    fclose(fp);
    fclose(quote);
    return 1;
  }
  
  while(!feof(fp)){
    char buffer[1025]={0}, *cp, *ep;
    int bytes=0;
    
    bytes=fread(buffer,1,sizeof(buffer)-1,fp);
    if(!bytes)break;
    else buffer[bytes]=0;
    
    if(msg->cryptkey)bbscrypt(buffer,bytes,dummy.cryptkey);
    
    cp=buffer;
    while(*cp){
      if((ep=strchr(cp,'\n'))==NULL){
	if(col1)fprintf(quote,"> ");
	col1=0;
	fprintf(quote,"%s",cp);
	break;
      } else {
	*ep=0;
	if(col1)fprintf(quote,"> %s\n",cp);
	else fprintf(quote,"%s\n",cp);
	col1=1;
	cp=ep+1;
      }
    }
  }
  fprintf(quote,"\n");
  
  fclose(fp);
  fclose(quote);
  return 1;
}


#endif /* USE_LIBZ */


void
reply(struct message *org, int forceemail)
{
  struct message msg, checkmsg;
  struct stat    st;
  char           body[256],header[256],command[1024];
  FILE           *fp;
  int            attachment=0, rrr=0, numcopies=0, nomore=0, net=0;
  int            cleanupattachment=1;
  uint32         original=0;
  char           attfile[256];
  int            clubmsg=0;

  clubmsg=(org->club[0]!=0);
  loadclubhdr(org->club);

  if(clubmsg && (!forceemail)){
    if(getclubax(&thisuseracc,org->club)<CAX_WRITE){
      prompt(WCNAXES);
      return;
    }
  } else if(!key_owns(&thisuseracc,wrtkey)){
    prompt(NOAXES);
    return;
  }

  memset(&msg,0,sizeof(msg));
  strcpy(msg.from,thisuseracc.userid);
  if(clubmsg&&(!forceemail))strcpy(msg.club,org->club);
  msg.replyto=org->msgno;
  

  for(;!nomore;){

    /* Get message recipient */
    
    strcpy(msg.to,org->from);

    if(!numcopies){
      
      /* Get message subject */

      strcpy(msg.subject,org->subject);
      

      /* Edit the message body */
      
      sprintf(body,TMPDIR"/B%d%08lx",getpid(),time(0));
      if(!quotemessage(org,body))return;
      appendsignature(body);
      sprintf(header,TMPDIR"/H%d%08lx",getpid(),time(0));
      
      if(editor(body,msglen)||stat(body,&st)){
	unlink(body);
	unlink(header);
	return;
      } else cnc_end();
      
      sprintf(msg.history,"%s %s/%d",HST_REPLY,
	      clubmsg?org->club:EMAILCLUBNAME,
	      org->msgno);
      msg.flags|=MSF_REPLY;
      
      /* Ask for file attachment */
      
      if(key_owns(&thisuseracc,attkey)&&usr_canpay(attchg)){
	for(;;){
	  if(!askyesno(&attachment,WEATT,WERRSEL,attchg)){
	    if(confirmcancel()){
	      unlink(body);
	      unlink(header);
	      return;
	    } else continue;
	  } else break;
	}
	if(attachment){
	  uploadatt(attfile,msg.club[0]?clubhdr.msgno+1:sysvar->emessages+1);
	  if(attfile[0]){
	    char *cp=NULL;
	    
	    usr_chargecredits(msg.club[0]?clubhdr.postchg:attchg);
	    msg.flags|=MSF_FILEATT;
	    if(!msg.club[0])msg.flags|=MSF_APPROVD;
	    else if(getclubax(&thisuseracc,org->club)>=CAX_COOP)
	      msg.flags|=MSF_APPROVD;
	    cp=getattname(msg.subject,
			  msg.club[0]?clubhdr.msgno+1:sysvar->emessages+1);
	    if(!cp){
	      unlink(body);
	      unlink(header);
	      unlink(attfile);
	      return;
	    } else strcpy(msg.fatt,cp);
	  }
	}
      }
      
      
      /* Ask for return receipt */

      if(!msg.club[0]){
	if(key_owns(&thisuseracc,rrrkey)&&usr_canpay(rrrchg)){
	  for(;;){
	    if(!askyesno(&rrr,WERRR,WERRSEL,rrrchg)){
	      if(confirmcancel()){
		unlink(body);
		unlink(header);
		return;
	      } else continue;
	    } else break;
	  }
	  if(rrr){
	    msg.flags|=MSF_RECEIPT;
	    usr_chargecredits(rrrchg);
	  }
	}
      }
    } else {
      char tmp[256];
      if(attfile[0])msg.flags|=MSF_FILEATT|MSF_APPROVD;
      if(rrr)msg.flags|=MSF_RECEIPT;
      sprintf(tmp,HST_CC" %s/%d",EMAILCLUBNAME,original);
      addhistory(msg.history,tmp,sizeof(msg.history));
    }

    
    /* Mail the message */
    
    if((fp=fopen(header,"w"))==NULL){
      error_fatalsys("Unable to create message header %s",header);
    }
    if(fwrite(&msg,sizeof(msg),1,fp)!=1){
      int i=errno;
      fclose(fp);
      errno=i;
      error_fatalsys("Unable to write message header %s",header);
    }
    fclose(fp);
    
    if(!attfile[0])sprintf(command,"%s %s %s",mkfname(BBSMAILBIN),header,body);
    else {
      sprintf(command,"%s %s %s -%c %s",mkfname(BBSMAILBIN),header,body,
	      numcopies?'h':'c',attfile);
      if(numcopies)cleanupattachment=0;
    }
    system(command);

    
    /* Notify the user(s) */
    
    if((fp=fopen(header,"r"))==NULL){
      error_fatalsys("Unable to read message header %s",header);
    }
    if(fread(&checkmsg,sizeof(msg),1,fp)!=1){
      int i=errno;
      fclose(fp);
      errno=i;
      error_fatalsys("Unable to read message header %s",header);
    }
    fclose(fp);

    if(checkmsg.msgno){
      if(!numcopies){
	prompt(WECONFS,msg.club[0]?clubhdr.club:EMAILCLUBNAME,checkmsg.msgno);
	org->replies++;
	writemsgheader(org);
      }else prompt(WECONFC,original,checkmsg.msgno,checkmsg.to);
      
      if(usr_insys(checkmsg.to,1)){
	if(!msg.club[0]){
	  sprompt_other(othrshm,out_buffer,numcopies?WERNOTC:WERNOT,
			checkmsg.from,checkmsg.subject);
	} else {
	  sprompt_other(othrshm,out_buffer,WCRNOT,
			checkmsg.from,checkmsg.club,checkmsg.subject);
	}
	if(usr_injoth(&othruseronl,out_buffer,0))
	  prompt(WENOTFD,othruseronl.userid);
      }
    }


    /* Clean up */
    
    usr_chargecredits(msg.club[0]?clubhdr.postchg:(net?wrtchg+netchg:wrtchg));
    thisuseracc.msgswritten++;
    if(!numcopies)original=checkmsg.msgno;
    unlink(header);
    if(attfile[0] && cleanupattachment){
      unlink(attfile);
      if(!msg.club[0]){
	strcpy(attfile,
	       mkfname(EMAILDIR"/"MSGATTDIR"/"FILEATTACHMENT,original));
      } else {
	strcpy(attfile,mkfname("%s/%s/"MSGATTDIR"/"FILEATTACHMENT,MSGSDIR,
			       clubhdr.club,original));
      }
    }

    
    /* Ask for more copies */

    if(!msg.club[0]){
      if(numcopies<maxccs){
	for(;;){
	  if(!askyesno(&nomore,WECC,WERRSEL,wrtchg)){
	    nomore=1;
	    break;
	  } else {
	    numcopies++;
	    nomore=!nomore;
	    break;
	  }
	}
      }
    } else nomore=1;
  }
  unlink(body);
}


