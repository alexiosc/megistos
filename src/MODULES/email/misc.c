/*****************************************************************************\
 **                                                                         **
 **  FILE:     misc.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 1995, Version 0.5                                    **
 **  PURPOSE:  Miscellaneous mail handling commands                         **
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
 * Revision 1.1  2001/04/16 14:55:26  alexios
 * Initial revision
 *
 * Revision 0.8  1999/07/18 21:21:38  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.7  1998/12/27 15:33:03  alexios
 * Added autoconf support. Added support for new getlinestatus().
 * Migrated to the new locking functions.
 *
 * Revision 0.6  1998/08/11 10:03:22  alexios
 * Club listings are now case insensitive.
 *
 * Revision 0.5  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/05 11:13:45  alexios
 * Changed calls to audit() to use the new auditing scheme.
 *
 * Revision 0.2  1997/08/30 12:58:35  alexios
 * Changed bladcommand() call to bbsdcommand().
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "email.h"
#ifdef USE_LIBZ
#define WANT_ZLIB_H 1
#endif


void
stopautofw(struct message *msg) 
{
  struct emailuser user;
  char userid[256], *cp;
  int ok=0, yes=0;

  if((msg->flags&MSF_AUTOFW)&&((cp=strstr(msg->history,HST_AUTOFW))!=NULL)){
    ok=(sscanf(cp,"%*s %s",userid)==1);
  }

  if(!ok){
    prompt(RDSAR1);
    return;
  }

  if(!userexists(userid)){
    prompt(RDSAR2,userid);
    return;
  }

  readecuser(userid,&user);
  
  if(strcmp(thisuseracc.userid,user.forwardto)){
    prompt(RDSAR3,userid);
    return;
  }

  prompt(RDSAI,userid);
  if(!getbool(&yes,RDSAQ,RDSAQR,0,0)){
    prompt(RDSAC);
    return;
  }
  if(!yes){
    prompt(RDSAC);
    return;
  }

  readecuser(userid,&user);
  if(!strcmp(user.forwardto,thisuseracc.userid)){
    strcpy(user.forwardto,userid);
    writeecuser(userid,&user);
  }
  prompt(RDSAS);
}


void
erasemsg(int forward, struct message *msg)
{
  char fname[512], clubdir[256];

  /* Can't modify the message */

  if(msg->flags&MSF_CANTMOD && (!hassysaxs(&thisuseracc,USY_MASTERKEY))){
    prompt(EMERR);
    return;
  }


  /* The message is exempt from deletions */

  if(msg->flags&MSF_EXEMPT){
    prompt(EMXMPT);
    return;
  }


  /* The message is locked */

  if(!checklocks(msg)){
    prompt(forward?FWCONF:USING);
    return;
  }


  /* Remove the message files */

  if(msg->club[0])sprintf(clubdir,"%s/%s",MSGSDIR,msg->club);
  else strcpy(clubdir,EMAILDIR);

  sprintf(fname,"%s/"MESSAGEFILE,clubdir,msg->msgno);
  unlink(fname);
  sprintf(fname,"%s/.ATT/%ld.att",clubdir,msg->msgno);
  unlink(fname);


  /* Remove the database index */

  dbrm(msg);


  /* Adjust club header if it's a club message */

  if(msg->club[0]){
    loadclubhdr(msg->club);
    clubhdr.nmsgs--;
    if(msg->flags&MSF_FILEATT)clubhdr.nfiles--;
    if(msg->period)clubhdr.nper--;
    if(msg->flags&MSF_FILEATT && ((msg->flags&MSF_APPROVD)==0))clubhdr.nfunapp--;
    saveclubhdr(&clubhdr);
  }


  /* Decrease the number of replies of the parent message */
  
  if(msg->replyto && msg->flags&MSF_REPLY){
    FILE *fp;
    
    struct message replied;
    char lock[256],s[64],*cp,club[256],t[256],*clp;
    int ok;


    /* Parse the message history */

    if((cp=strstr(msg->history,HST_REPLY))!=NULL){
      ok=(sscanf(cp,"%*s %s",t)==1);
      if(ok){
	ok=(clp=strchr(t,'/'))!=NULL;
	if(ok){
	  *clp=0;
	  strcpy(club,t);
	}
      }
      if(sameas(club,EMAILCLUBNAME))strcpy(club,EMAILDIRNAME);
    }


    /* Lock the parent message */

    sprintf(s,"%ld",msg->replyto);
    sprintf(lock,MESSAGELOCK,club,s);
    if(waitlock(lock,10)==LKR_TIMEOUT)return;
    placelock(lock,"updating");


    /* And update it */
    
    decompressmsg(msg);
    sprintf(fname,"%s/%s/"MESSAGEFILE,MSGSDIR,club,msg->replyto);
    if((fp=fopen(fname,"r+"))!=NULL){
      if(fread(&replied,sizeof(replied),1,fp)){
	int i=replied.replies;
	if((--replied.replies)<0)replied.replies=0;
	if(replied.replies!=i){
	  rewind(fp);
	  fwrite(&replied,sizeof(replied),1,fp);
	}
      }
    }
    compressmsg(msg);
    fclose(fp);
    rmlock(lock);
  }
}


void
copymsg(struct message *msg)
{
  FILE *fp1, *fp2, *fp3;
  int net=0;
  struct message checkmsg;
  char temp[256], source[256], fatt[256], lock[256], clubdir[256];
  char clubname[256];
  char header[256], body[256], command[256], original[256], origclub[256];
  char origdir[256];
  int bytes, res, clubmsg=0;

  if(msg->club[0])strcpy(origclub,msg->club);
  else strcpy(origclub,EMAILCLUBNAME);
  strcpy(origdir,msg->club);

  /* Get message recipient */

  for(;;){
    res=getrecipient(CPWHO,msg->to);
    if(!res)return;
    else if(res==2){
      strcpy(msg->club,msg->to);
      if(getclubax(&thisuseracc,msg->club)<CAX_WRITE){
	prompt(CPCERR,msg->club);
	endcnc();
	continue;
      }
      strcpy(msg->to,ALL);
      clubmsg=1;
      strcpy(clubdir,msg->club);
      strcpy(clubname,clubdir);
      loadclubhdr(msg->club);
      if(morcnc()=='-'){
	cncchr();
	if(!getclubrecipient(WEFCAU,WEFCAUR,WEFCAUR,msg->to))return;
      }
      break;
    } else {
      strcpy(msg->club,"");
      if(!haskey(&thisuseracc,wrtkey)){
	prompt(CPNOAXES);
	return;
      }
      clubmsg=0;
      if(msg->to[0]=='!')prompt(FWERR);
      strcpy(clubdir,EMAILDIRNAME);
      strcpy(clubname,EMAILCLUBNAME);
      break;
    }
  }
  net=strchr(msg->to,'@')||strchr(msg->to,'%');
  prompt(net?CPRCPOKN:CPRCPOK,msg->to);


  /* Check if we can copy the file attachment */

  if(clubmsg && (msg->flags&MSF_FILEATT)){
    int ax=getclubax(&thisuseracc,msg->club);
    if(ax<CAX_UPLOAD){
      prompt(CPCERR2,msg->club);
      msg->flags&=~(MSF_FILEATT|MSF_APPROVD);
    } else if(ax>=CAX_COOP){
      msg->flags|=MSF_APPROVD;
    }
  }


  /* Check if user has enough credits */
  
  if(!clubmsg){
    if(!canpay((net?wrtchg+netchg:wrtchg)+
	       (msg->flags&MSF_FILEATT?attchg:0))){
      prompt(WERNEC);
      return;
    }
  } else {
    if(!canpay(clubhdr.postchg+(msg->flags&MSF_FILEATT?clubhdr.uploadchg:0))){
      prompt(WCRNEC);
      return;
    }
  }


  /* Mail the message */
  
  sprintf(temp,"%ld",msg->msgno);
  sprintf(lock,MESSAGELOCK,clubname,temp);
  if((waitlock(lock,20))==LKR_TIMEOUT)return;
  placelock(lock,"reading");
  decompressmsg(msg);

  sprintf(original,"%s/%ld",clubdir,msg->msgno);
  sprintf(temp,"%s %s",HST_CP,thisuseracc.userid);
  addhistory(msg->history,temp,sizeof(msg->history));
  msg->flags&=(MSF_COPYMASK|MSF_APPROVD);
  msg->replies=0;
  msg->timesread=0;
  msg->timesdnl=0;
  msg->period=0;

  if(!origdir[0]){
    sprintf(source,EMAILDIR"/"MESSAGEFILE,msg->msgno);
  } else {
    sprintf(source,"%s/%s/"MESSAGEFILE,MSGSDIR,origdir,msg->msgno);
  }

  if((fp1=fopen(source,"r"))==NULL){
    prompt(CPIO);
    return;
  }

  sprintf(body,TMPDIR"/cc%05dB",getpid());
  if((fp2=fopen(body,"w"))==NULL){
    prompt(CPIO);
    return;
  }

  sprintf(header,TMPDIR"/cc%05dH",getpid());
  if((fp3=fopen(header,"w"))==NULL){
    prompt(CPIO);
    return;
  }

  fwrite(msg,sizeof(struct message),1,fp3);
  fclose(fp3);

  fseek(fp1,sizeof(struct message),SEEK_SET);
  do{
    if((bytes=fread(temp,1,sizeof(temp),fp1))!=0){
      if(msg->cryptkey)bbscrypt(temp,bytes,msg->cryptkey);
      fwrite(temp,bytes,1,fp2);
    }
  }while(bytes);
  
  fclose(fp1);
  fclose(fp2);

  rmlock(lock);

  if(!origdir[0]){
    sprintf(fatt,EMAILDIR"/"MSGATTDIR"/"FILEATTACHMENT,(long)msg->msgno);
  } else {
    sprintf(fatt,"%s/%s/%s/"FILEATTACHMENT,
	    MSGSDIR,origdir,MSGATTDIR,(long)msg->msgno);
  }

  if(!(msg->flags&MSF_FILEATT)){
    sprintf(command,"%s %s %s",BBSMAILBIN,header,body);
  }else {
    sprintf(command,"%s %s %s -h %s",BBSMAILBIN,header,body,fatt);
  }
  system(command);

    
  /* Notify the user(s) */
    
  if((fp1=fopen(header,"r"))==NULL){
    fatalsys("Unable to read message header %s",header);
  }
  if(fread(&checkmsg,sizeof(checkmsg),1,fp1)!=1){
    int i=errno;
    fclose(fp1);
    errno=i;
    fatalsys("Unable to read message header %s",header);
  }
  fclose(fp1);

  if(checkmsg.msgno)prompt(WECONFC,origclub,msg->msgno,clubname,
			   checkmsg.msgno,checkmsg.to);
      
  if(uinsys(checkmsg.to,1)){
    if(!clubmsg){
      sprintf(outbuf,getmsglang(WERNOTC,othruseracc.language-1),
	      checkmsg.from,checkmsg.subject);
    } else {
      sprintf(outbuf,getmsglang(WERNOTCC,othruseracc.language-1),
	      checkmsg.from,checkmsg.club,checkmsg.subject);
    }
    if(injoth(&othruseronl,outbuf,0))prompt(WENOTFD,othruseronl.userid);
  }


  /* Clean up */

  if(!clubmsg){
    chargecredits((net?wrtchg+netchg:wrtchg)+
		  (msg->flags&MSF_FILEATT?attchg:0));
  } else {
    chargecredits(clubhdr.postchg+
		  (msg->flags&MSF_FILEATT?clubhdr.uploadchg:0));
  }
  thisuseracc.msgswritten++;
  unlink(header);
  unlink(body);
}


void
forwardmsg(struct message *msg)
{
  FILE *fp1, *fp2, *fp3;
  int net=0;
  struct message checkmsg, orig;
  char temp[256], source[256], fatt[256], lock[256], clubdir[256];
  char clubname[256];
  char header[256], body[256], command[256], original[256], origclub[256];
  char origdir[256];
  int bytes, res, clubmsg=0;

  memcpy(&orig,msg,sizeof(orig));

  if(msg->club[0])strcpy(origclub,msg->club);
  else strcpy(origclub,EMAILCLUBNAME);
  strcpy(origdir,msg->club);

  /* Get message recipient */

  for(;;){
    res=getrecipient(FWWHO,msg->to);
    if(!res)return;
    else if(res==2){
      strcpy(msg->club,msg->to);
      if(getclubax(&thisuseracc,msg->club)<CAX_WRITE){
	prompt(CPCERR,msg->club);
	endcnc();
	continue;
      }
      strcpy(msg->to,ALL);
      clubmsg=1;
      strcpy(clubdir,msg->club);
      strcpy(clubname,clubdir);
      loadclubhdr(msg->club);
      if(morcnc()=='-'){
	cncchr();
	if(!getclubrecipient(WEFCAU,WEFCAUR,WEFCAUR,msg->to))return;
      }
      break;
    } else {
      strcpy(msg->club,"");
      if(!haskey(&thisuseracc,wrtkey)){
	prompt(FWNOAXES);
	return;
      }
      clubmsg=0;
      if(msg->to[0]=='!')prompt(FWERR);
      strcpy(clubdir,EMAILDIRNAME);
      strcpy(clubname,EMAILCLUBNAME);
      break;
    }
  }
  net=strchr(msg->to,'@')||strchr(msg->to,'%');
  prompt(net?FWRCPOKN:FWRCPOK,msg->to);


  /* Check if we can copy the file attachment */

  if(clubmsg && (msg->flags&MSF_FILEATT)){
    int ax=getclubax(&thisuseracc,msg->club);
    if(ax<CAX_UPLOAD){
      prompt(FWCERR2,msg->club);
      return;
    } else if(ax>=CAX_COOP){
      msg->flags|=MSF_APPROVD;
    }
  }


  /* Check if user has enough credits */
  
  if(!clubmsg){
    if(!canpay((net?wrtchg+netchg:wrtchg)+
	       (msg->flags&MSF_FILEATT?attchg:0))){
      prompt(WERNEC);
      return;
    }
  } else {
    if(!canpay(clubhdr.postchg+(msg->flags&MSF_FILEATT?clubhdr.uploadchg:0))){
      prompt(WCRNEC);
      return;
    }
  }


  /* Mail the message */
  
  sprintf(temp,"%ld",msg->msgno);
  sprintf(lock,MESSAGELOCK,clubname,temp);
  if((waitlock(lock,20))==LKR_TIMEOUT)return;
  placelock(lock,"reading");

  sprintf(original,"%s/%ld",clubdir,msg->msgno);
  sprintf(temp,"%s %s",HST_FW,thisuseracc.userid);
  addhistory(msg->history,temp,sizeof(msg->history));
  msg->flags&=(MSF_COPYMASK|MSF_APPROVD);
  msg->replies=0;
  msg->timesread=0;
  msg->timesdnl=0;
  msg->period=0;

  if(!origdir[0]){
    sprintf(source,EMAILDIR"/"MESSAGEFILE,msg->msgno);
  } else {
    sprintf(source,"%s/%s/"MESSAGEFILE,MSGSDIR,origdir,msg->msgno);
  }

  if((fp1=fopen(source,"r"))==NULL){
    prompt(FWIO);
    return;
  }

  sprintf(body,TMPDIR"/cc%05dB",getpid());
  if((fp2=fopen(body,"w"))==NULL){
    prompt(FWIO);
    return;
  }

  sprintf(header,TMPDIR"/cc%05dH",getpid());
  if((fp3=fopen(header,"w"))==NULL){
    prompt(FWIO);
    return;
  }

  fwrite(msg,sizeof(struct message),1,fp3);
  fclose(fp3);

  fseek(fp1,sizeof(struct message),SEEK_SET);
  do{
    if((bytes=fread(temp,1,sizeof(temp),fp1))!=0){
      if(msg->cryptkey)bbscrypt(temp,bytes,msg->cryptkey);
      fwrite(temp,bytes,1,fp2);
    }
  }while(bytes);
  
  fclose(fp1);
  fclose(fp2);

  rmlock(lock);

  if(!origdir[0]){
    sprintf(fatt,EMAILDIR"/"MSGATTDIR"/"FILEATTACHMENT,(long)msg->msgno);
  } else {
    sprintf(fatt,"%s/%s/%s/"FILEATTACHMENT,
	    MSGSDIR,origdir,MSGATTDIR,(long)msg->msgno);
  }

  if(!(msg->flags&MSF_FILEATT)){
    sprintf(command,"%s %s %s",BBSMAILBIN,header,body);
  }else {
    sprintf(command,"%s %s %s -h %s",BBSMAILBIN,header,body,fatt);
  }
  system(command);
    
  /* Notify the user(s) */
    
  if((fp1=fopen(header,"r"))==NULL){
    fatalsys("Unable to read message header %s",header);
  }
  if(fread(&checkmsg,sizeof(checkmsg),1,fp1)!=1){
    int i=errno;
    fclose(fp1);
    errno=i;
    fatalsys("Unable to read message header %s",header);
  }
  fclose(fp1);

  if(checkmsg.msgno)prompt(WECONFC,origclub,msg->msgno,clubname,
			   checkmsg.msgno,checkmsg.to);
      
  if(uinsys(checkmsg.to,1)){
    if(!clubmsg){
      sprintf(outbuf,getmsglang(WERNOTC,othruseracc.language-1),
	      checkmsg.from,checkmsg.subject);
    } else {
      sprintf(outbuf,getmsglang(WERNOTFW,othruseracc.language-1),
	      checkmsg.from,checkmsg.club,checkmsg.subject);
    }
    if(injoth(&othruseronl,outbuf,0))prompt(WENOTFD,othruseronl.userid);
  }


  /* Clean up */

  if(!clubmsg){
    chargecredits((net?wrtchg+netchg:wrtchg)+
		  (msg->flags&MSF_FILEATT?attchg:0));
  } else {
    chargecredits(clubhdr.postchg+
		  (msg->flags&MSF_FILEATT?clubhdr.uploadchg:0));
  }
  thisuseracc.msgswritten++;
  unlink(header);
  unlink(body);
  erasemsg(1,&orig);
}



int
backtrack(struct message *msg)
{
  char replyto[256], *cp;
  int msgno=0, ok=0, i, j;
  char fname[256];
  struct stat st;

  if((msg->flags&MSF_REPLY)&&((cp=strstr(msg->history,HST_REPLY))!=NULL)){
    ok=(sscanf(cp,"%*s %s",replyto)==1);
  }

  if(ok){
    if((cp=strchr(replyto,'/'))!=NULL){
      cp++;
      ok=(sscanf(cp,"%d",&msgno)==1);
    }
  }

  if(ok){
    j=findmsgnum(&i,msgno,BSD_GT);
    if(j!=BSE_FOUND) {
      ok=0;
    } else if(!dbchkemail(msgno)) ok=0;
  }

  if(ok){
    sprintf(fname,EMAILDIR"/"MESSAGEFILE,(long)msgno);
    ok=(stat(fname,&st)==0);
  }

  if(!ok){
    prompt(BKERR);
    return 0;
  }

  return msgno;
}


void
deleteuser(struct message *msg)
{
  useracc usracc, *uacc=&usracc;

  if(!(msg->flags&MSF_SIGNUP && strcmp(msg->from,thisuseracc.userid) &&
       (sameas(thisuseracc.userid,SYSOP)||hassysaxs(&thisuseracc,USY_DELETE))))
    return;
  
  if(!userexists(msg->from)){
    prompt(DUERR);
    return;
  }
  
  if(!uinsys(msg->from,0))loaduseraccount(msg->from,uacc);
  else uacc=&othruseracc;

  if((uacc->flags&UFL_EXEMPT||sameas(msg->from,SYSOP))
     &&(!(uacc->flags&UFL_DELETED))){
    prompt(DUXM);
    return;
  }
  
  if(uacc->flags&UFL_DELETED){
    prompt(DUDEL);
    return;
  }

  uacc->flags|=UFL_DELETED;
  
  if (!uinsys(msg->from,0))saveuseraccount(uacc);
  else bbsdcommand("hangup",othruseronl.channel,"");

  prompt(DUOK);
  audit(getenv("CHANNEL"),AUDIT(RSMDEL),thisuseracc.userid,msg->from);
}



static char lockchk[256];

int
lockselect(const struct dirent *d)
{
  return sameto(lockchk,((struct dirent *)d)->d_name);
}


void
rmlocks()
{
  char *cp, fname[256];
  struct dirent **locks;
  int i,n;

  sprintf(lockchk,MSGREADLOCK,thisuseronl.channel,"*","*");
  if((cp=strchr(lockchk,'*'))!=NULL)*cp=0;

  n=scandir(LOCKDIR,&locks,lockselect,ncsalphasort);

  for(i=0;i<n;i++){
    sprintf(fname,"%s/%s",LOCKDIR,locks[i]->d_name);
    unlink(fname);
    free(locks[i]);
  }
  free(locks);
}
