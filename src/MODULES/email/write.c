/*****************************************************************************\
 **                                                                         **
 **  FILE:     write.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995                                                  **
 **            B, August 1995                                               **
 **  PURPOSE:  Writing an email/club message                                **
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
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.10  1999/08/13 17:00:25  alexios
 * Fixed silly reprompt bug when asking for recipient name.
 *
 * Revision 0.9  1999/07/18 21:21:38  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Slight alterations
 * to the message storing code.
 *
 * Revision 0.8  1998/12/27 15:33:03  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Migrated to new locking functions. Other minor fixes.
 *
 * Revision 0.7  1998/08/14 11:30:20  alexios
 * Fixed the WRITE command so that users not possessing the
 * wrtkey can still write email to SYSOP.
 *
 * Revision 0.6  1998/08/11 10:03:22  alexios
 * Migrated file transfer calls to the new format.
 *
 * Revision 0.5  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/06 16:54:26  alexios
 * Changed calls to setaudit() so the new auditing scheme is
 * used.
 *
 * Revision 0.2  1997/09/14 13:49:59  alexios
 * Fixed problems with distribution lists.
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "email.h"


char clubdir[256];


void
emailwrite()
{
  struct message msg, checkmsg;
  struct stat    st;
  char           body[256],header[256],command[1024];
  FILE           *fp;
  int            attachment=0, rrr=0, numcopies=0, nomore=0, net=0, res=0;
  int            cleanupattachment=1, distlist=0, ndist=0, killit=0, sysop=0;
  int            clubmsg=0;
  uint32         original=0;
  char           attfile[256]={0}, origclub[256]={0};

  if(!key_owns(&thisuseracc,wrtkey)){
    prompt(OPONLY);
    sysop=1;
  }
  
  memset(&msg,0,sizeof(msg));
  strcpy(msg.from,thisuseracc.userid);

  for(;!nomore;){

    /* Get message recipient */

    if(!distlist){ /* distribution list still running */
      if(sysop){
	res=1;
	strcpy(msg.to,SYSOP);
      } else if((res=getrecipient(numcopies?WEWHOC:WEWHO,msg.to))==0)return;

      if(res==2){
	strcpy(msg.club,msg.to);
	if(getclubax(&thisuseracc,msg.club)<CAX_WRITE){
	  prompt(WERCLUB,msg.club);
	  cnc_end();
	  continue;
	}
	strcpy(msg.to,MSG_ALL);
	clubmsg=1;
	strcpy(clubdir,msg.club);
	if(cnc_more()&&cnc_chr()=='-'){
	  if(!getclubrecipient(WEFCAU,WEFCAUR,WEFCAUR,msg.to))return;
	}
      } else {
	clubmsg=0;
	strcpy(msg.club,"");
	strcpy(clubdir,EMAILCLUBNAME);
      }

      if(msg.to[0]!='!'){
	net=strchr(msg.to,'@')||strchr(msg.to,'%');
	if(!clubmsg)prompt(net?WERCPOKN:WERCPOK,msg.to);
	else if(sameas(msg.to,MSG_ALL))prompt(WERCPOKC,msg.club);
	else prompt(WERCPOKU,msg.club,msg.to);
      }else {
	prompt(WERCPOKL,msg.to); /* open distributinon list */
	distlist=1;
	ndist=0;
	if(!opendistribution(msg.to))return;
      }
    }

    if(!numcopies){
      
      /* Get message subject */
      
      if(!getsubject(msg.subject))return;
      
      
      /* Edit the message body */
      
      sprintf(body,TMPDIR"/B%d%08lx",getpid(),time(0));
      appendsignature(body);
      sprintf(header,TMPDIR"/H%d%08lx",getpid(),time(0));
      
      if(editor(body,msglen)||stat(body,&st)){
	unlink(body);
	unlink(header);
	cnc_end();
	return;
      } else cnc_end();
      
      
      /* Ask for file attachment */
      
      if(((clubmsg==0)&&key_owns(&thisuseracc,attkey)&&usr_canpay(attchg))||
	 (clubmsg&&(getclubax(&thisuseracc,msg.club)>=CAX_UPLOAD)&&
	  usr_canpay(clubhdr.uploadchg))){
	for(;;){
	  if(!askyesno(&attachment,WEATT,WERRSEL,
		       clubmsg?clubhdr.uploadchg:attchg)){
	    if(confirmcancel()){
	      unlink(body);
	      unlink(header);
	      return;
	    } else continue;
	  } else break;
	}
	if(attachment){
	  uploadatt(attfile,clubmsg?clubhdr.msgno+1:sysvar->emessages+1);
	  if(attfile[0]){
	    char *cp=NULL;
	    
	    usr_chargecredits(clubmsg?clubhdr.uploadchg:attchg);
	    msg.flags|=MSF_FILEATT;
	    if(!clubmsg){
	      msg.flags|=MSF_FILEATT|MSF_APPROVD;
	    } else {
	      if(getclubax(&thisuseracc,msg.club)>=CAX_COOP){
		msg.flags|=MSF_APPROVD;
	      } else {
		char lock[256];
		sprintf(lock,CLUBLOCK,msg.club);
		if(lock_wait(lock,10)==LKR_TIMEOUT)return;
		lock_place(lock,"updating");
		loadclubhdr(msg.club);
		clubhdr.nfunapp++;
		saveclubhdr(&clubhdr);
		lock_rm(lock);
	      }
	    }
		
	    cp=getattname(msg.subject,
			  clubmsg?clubhdr.msgno+1:sysvar->emessages+1);
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
      
      if(key_owns(&thisuseracc,rrrkey)&&usr_canpay(rrrchg)&&(clubmsg==0)){
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
    } else {
      if(attfile[0]){
	msg.flags|=MSF_FILEATT;
	if(!clubmsg)msg.flags|=MSF_APPROVD;
	else {
	  if(getclubax(&thisuseracc,msg.club)>=CAX_COOP){
	    msg.flags|=MSF_APPROVD;
	  }
	}
      }
      if(rrr)msg.flags|=MSF_RECEIPT;
      if(!distlist)sprintf(msg.history,HST_CC" %s/%d",origclub,original);
      else strcpy(msg.history,HST_DIST);
    }


    /* Handle distribution lists */

    if(distlist){
      char *s;
      char c;

      for(;;){
	if((s=readdistribution())==NULL)break;
	if(!usr_exists(s))prompt(WELUNKU,s);
	else break;
      }
      strcpy(msg.to,s?s:"");
      strcpy(msg.history,HST_DIST);
      if(!ndist){
	prompt(DISTBEG);
	inp_nonblock();
	thisuseronl.flags|=OLF_BUSY+OLF_NOTIMEOUT;
      } else if(read(fileno(stdin),&c,1)&&
		((c==13)||(c==10)||(c==27)||(c==15)||(c==3))){
	prompt(WECAN);
	break;
      }
    }

    /* Check if user has enough credits */

    if(!clubmsg){
      if(!usr_canpay(net?wrtchg+netchg:wrtchg)){
	prompt(distlist?WERLNEC:WERNEC);
	killit=1;
      }
    } else {
      if(!usr_canpay(clubhdr.postchg)){
	prompt(WCRNEC);
	killit=1;
      }
    }
    
    /* Mail the message */

    if(msg.to[0]){                        /* handle end of distribution list */
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

      if(!attfile[0])sprintf(command,"%s %s %s",BBSMAILBIN,header,body);
      else {
	sprintf(command,"%s %s %s -%c %s",BBSMAILBIN,header,body,
		numcopies?'h':'c',attfile);
	if(numcopies)cleanupattachment=0;
      }
      system(command);
      
      
      /* Notify the user(s) */

      if((thisuseronl.flags&OLF_INVISIBLE)==0){
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
	  if(distlist){
	    prompt(WECONFL,checkmsg.msgno,checkmsg.to); /* distribution */
	    ndist++;
	  } else if(!numcopies)prompt(WECONFS,
				      clubmsg?msg.club:EMAILCLUBNAME,
				      checkmsg.msgno);
	  else prompt(WECONFC,origclub,original,
		      clubmsg?msg.club:EMAILCLUBNAME,
		      checkmsg.msgno,
		      (sameas(MSG_ALL,checkmsg.to)?
		       msg_getunit(WEALL,1):checkmsg.to));
	  
	  if(usr_insys(checkmsg.to,1)){
	    if(!clubmsg){
	      sprintf(out_buffer,msg_getl(numcopies?WERNOTC:WERNOT,
					  othruseracc.language-1),
		      checkmsg.from,checkmsg.subject);
	    } else {
	      sprintf(out_buffer,msg_getl(numcopies?WCRNOTC:WCRNOT,
					  othruseracc.language-1),
		      checkmsg.from,checkmsg.club,checkmsg.subject);
	    }
	    if(usr_injoth(&othruseronl,out_buffer,0))
	      prompt(WENOTFD,othruseronl.userid);
	  }
	}
      }
      
      
      /* Clean up */
      
      if(!clubmsg)usr_chargecredits(net?wrtchg+netchg:wrtchg);
      else usr_chargecredits(clubhdr.postchg);
      thisuseracc.msgswritten++;
      if(!numcopies){
	original=checkmsg.msgno;
	strcpy(origclub,clubmsg?msg.club:EMAILCLUBNAME);
      }
      unlink(header);
      if(attfile[0] && cleanupattachment){
	unlink(attfile);
	sprintf(attfile,"%s/%s/"MSGATTDIR"/"FILEATTACHMENT,
		MSGSDIR,
		clubmsg?clubhdr.club:EMAILDIRNAME,
		original);
      }
    } else {
      closedistribution();
      inp_block();
      thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
      prompt(DISTINFO,ndist,msg_getunit(MSGSNG,ndist));
      distlist=0;
    }

    
    /* Ask for more copies */
  
    if(killit||sysop)break;
  
    if(!distlist){ /* distribution */
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
    } else {
      numcopies++;
      nomore=0;
    }
  }
  inp_block();
  thisuseronl.flags|=OLF_BUSY+OLF_NOTIMEOUT;
  unlink(body);
  closedistribution();
  cnc_end();
}



static void
recipienthelp()
{
  DIR *dp;
  struct dirent *dir;
  int i,shown=0,key;
  FILE *fp;
  char fname[256];

  prompt(WEHELP1,netchg,msg_getunit(CRDSING,netchg));

  if(!key_owns(&thisuseracc,dlkey))return;
  if(key_owns(&thisuseracc,msskey)){
    shown=1;
    prompt(WEHELP2);
    prompt(WEHELP3,"MASS");
    prompt(WEHELP3,"ALL");
    for(i=0;i<cls_count;i++){
      char s[80];
      if(fmt_lastresult==PAUSE_QUIT)return;
      sprintf(s,"!%s",cls_classes[i].name);
      prompt(WEHELP3,s);
    }
  }

  if((dp=opendir(MSGSDISTDIR))==NULL)return;
  while((dir=readdir(dp))!=NULL){
    if(sameas(dir->d_name,".")||sameas(dir->d_name,".."))continue;
    if(fmt_lastresult==PAUSE_QUIT){
      closedir(dp);
      return;
    }
    sprintf(fname,"%s/%s",MSGSDISTDIR,dir->d_name);
    if((fp=fopen(fname,"r"))==NULL)continue;
    if(fscanf(fp,"%d",&key)!=1){
      fclose(fp);
      continue;
    }
    fclose(fp);
    if(key_owns(&thisuseracc,key)&&
       (dir->d_name[0]!='.' || sameas(&(dir->d_name[1]),thisuseracc.userid) ||
	key_owns(&thisuseracc,sopkey))){
      if(!shown){
	shown=1;
	prompt(WEHELP2);
      }
      prompt(WEHELP3,dir->d_name);
    }
  }
  if(shown)prompt(WEHELP4);
  closedir(dp);
}


static int
checklistname(char *name)
{
  DIR *dp;
  struct dirent *dir;
  FILE *fp;
  char fname[256];
  int i, key;

  if(!key_owns(&thisuseracc,dlkey))return 0;

  if(key_owns(&thisuseracc,msskey)){
    if(name[0]==name[1]){
      for(i=0;i<cls_count;i++)if(sameas(cls_classes[i].name,&name[2])){
	return 1;
      }
      prompt(EWRLERR);
      return 0;
    }

    if(sameas(name,"!mass")||sameas(name,"!all")){
      strcpy(name,"!all");
      return 1;
    }
  }
  
  if(!strcmp(name,"!"))sprintf(name,"!.%s",thisuseracc.userid);

  if((dp=opendir(MSGSDISTDIR))==NULL)return 0;
  while((dir=readdir(dp))!=NULL){
    if(sameas(dir->d_name,".")||sameas(dir->d_name,".."))continue;

    sprintf(fname,"%s/%s",MSGSDISTDIR,dir->d_name);
    if((fp=fopen(fname,"r"))==NULL)continue;
    if(fscanf(fp,"%d",&key)!=1){
      fclose(fp);
      continue;
    }
    fclose(fp);
    if(key_owns(&thisuseracc,key)&&
       (dir->d_name[0]!='.' || sameas(&(dir->d_name[1]),thisuseracc.userid) ||
	key_owns(&thisuseracc,sopkey))){
      if(sameas(&name[1],dir->d_name)){
	sprintf(name,"!%s",dir->d_name);
	return 1;
      }
    }
  }
  closedir(dp);

  prompt(EWRLERR);
  return 0;
}


int
getrecipient(int pr,char *rec)
{
  char *s=NULL;

  for(;;){
    if(!usr_canpay(wrtchg)){
      cnc_end();
      prompt(WENCRDS);
    }
    if(cnc_more())s=cnc_word();
    else {
      prompt(pr);
      inp_clearflags(INF_REPROMPT);
      inp_get(0);
      cnc_begin();
      if(!margc && !inp_reprompt()){
	strcpy(rec,SYSOP);
	return 1;
      }
      s=cnc_word();
    }
    if(sameas(s,".")){
      strcpy(rec,SYSOP);
      return 1;
    } else if(sameas(s,"?")){
      cnc_end();
      recipienthelp();
      continue;
    } else if(inp_isX(s)){
      cnc_end();
      return 0;
    } else if(strchr(s,'@')||strchr(s,'%')){
      if(key_owns(&thisuseracc,netkey)&&usr_canpay(netchg)){
	strcpy(rec,s);
	return 1;
      } else if(!key_owns(&thisuseracc,netkey)){
	prompt(WERNNET);
	cnc_end();
	continue;
      } else if(!usr_canpay(netchg)){
	prompt(WERNNET2);
	cnc_end();
	continue;
      }
    } else if(s[0]=='/'){
      int ax;
      if(!findclub(s)){
	prompt(WCCLUBR);
      } else if((ax=getclubax(&thisuseracc,s))==CAX_ZERO){
	prompt(WCCLUBR);
      } else if(ax<CAX_WRITE){
	prompt(WCNAXES);
      } else if(!usr_canpay(clubhdr.postchg)){
	prompt(WCNCRDS);
      } else {
	if(s[0]!='/')strcpy(rec,s);
	else strcpy(rec,&s[1]);
	return 2;
      }
      cnc_end();
      continue;
    } else if(usr_uidxref(s,0)){
      strcpy(rec,s);
      if(usr_canpay(wrtchg)||sameas(rec,SYSOP))return 1;
      else continue;
    }else if(checklistname(s)){
      strcpy(rec,s);
      return 1;
    } else {
      cnc_end();
      if(s[0]!='!')prompt(WEUNKID,s);
      continue;
    }
  }
  return 0;
}



int
getclubrecipient(int pr, int err, int help, char *rec)
{
  char *s=NULL;

  for(;;){
    if(cnc_more())s=cnc_word();
    else {
      prompt(pr);
      inp_get(0);
      cnc_begin();
      if(!margc){
	strcpy(rec,MSG_ALL);
	return 1;
      }
      s=cnc_word();
    }
    if(sameas(s,".")||sameas(s,"ALL")){
      strcpy(rec,MSG_ALL);
      return 1;
    } else if(sameas(s,"?")){
      cnc_end();
      prompt(help);
      continue;
    } else if(inp_isX(s)){
      cnc_end();
      return 0;
    } else if(usr_uidxref(s,0)){
      strcpy(rec,s);
      return 1;
    } else {
      cnc_end();
      prompt(err,s);
      continue;
    }
  }
  return 0;
}


int
getsubject(char *subject)
{
  char *i;
  cnc_end();
  for(;;){
    if(cnc_more()){
      i=cnc_nxtcmd;
      inp_raw();
    } else {
      prompt(ASKSUBJ);
      inp_get(63);
      cnc_begin();
      if(!margc)continue;
      i=inp_buffer;
      inp_raw();
    }

    if(!i[0])continue;
    else if(inp_isX(i))return 0;
    else {
      strcpy(subject,i);
      while(subject[strlen(subject)-1]==32)subject[strlen(subject)-1]=0;
      return 1;
    }
  }
}


void
uploadatt(char *attname,int num)
{
  char fname[256],command[256],*cp,name[256],dir[256];
  FILE *fp;
  int  count=-1;
  char audit[4][80];
  
  name[0]=dir[0]=0;
  strcpy(audit[0],AUS_ESUPLS);
  sprintf(audit[1],AUD_ESUPLS,
	  thisuseracc.userid,clubdir,num);
  strcpy(audit[2],AUS_ESUPLF);
  sprintf(audit[3],AUD_ESUPLF,
	  thisuseracc.userid,clubdir,num);
  xfer_setaudit(AUT_ESUPLS,audit[0],audit[1],AUT_ESUPLF,audit[2],audit[3]);
  sprintf(attname,"%d.att",num);
  xfer_add(FXM_UPLOAD,attname,eattupl,attchg,-1);
  strcpy(attname,"");
  xfer_run();
  
  sprintf(fname,XFERLIST,getpid());
  
  if((fp=fopen(fname,"r"))==NULL){
    prompt(WENOATT);
    goto kill;
  }
  
  while (!feof(fp)){
    char line[1024];
    
    if(fgets(line,sizeof(line),fp)){
      count++;
      if(!count)strcpy(dir,line);
      else if(count==1)strcpy(name,line);
    }
  }
  
  if((cp=strchr(dir,'\n'))!=NULL)*cp=0;
  if((cp=strchr(name,'\n'))!=NULL)*cp=0;
  fclose(fp);
  
  if(count<1){
    prompt(WEXFERR);
    goto kill;
  } else if(count>1){
    prompt(WEXFER2);
  }
  
  sprintf(attname,TMPDIR"/att%d%08lx",getpid(),time(0));
  {
    char command[256];
    sprintf(command,"cp %s %s",name,attname);
    if(system(command)){
      prompt(WEXFERR);
      goto kill;
    }
  }
  
 kill:
  sprintf(command,"rm -rf %s %s",fname,dir);
  system(command);
  if(name[0]){
    sprintf(command,"rm -f %s >&/dev/null",name);
    system(command);
  }
  xfer_kill_list();
}


char *
getattname(char *subject,int num)
{
  static char word1[256];
  char apparent[256],*cp;
  int ok=0,yn=0;
  int i;

  strcpy(word1,"");
  sscanf(subject," %s ",word1);
  cp=strchr(word1,'.');
  if(cp)ok=(*(cp+1)!=0 && !(isspace(*(cp+1))) && isprint(*(cp+1)));
  for(i=0;word1[i];i++)if(!strchr(FNAMECHARS,word1[i]))ok=0;
  if(ok)return(latinize(word1));
  else sprintf(apparent,"%d.att",num);
  
  for(;;){
    if(!askyesno(&yn,WEREEFN,WECCAN,(int)apparent)){
      if(confirmcancel())return NULL;
      else continue;
    }
    break;
  }

  if(!yn){
    prompt(WEDFFN,apparent,subject);
    strcpy(word1,"");
    return word1;
  } else {
    char *s=apparent;

    for(;;){
      ok=1;
      fmt_lastresult=0;
      if(cnc_more())s=cnc_word();
      else {
	prompt(WEFFN);
	inp_get(15);
	if(margc){
	  if(inp_isX(margv[0])){
	    if(confirmcancel())return NULL;
	    else continue;
	  } else s=margv[0];
	} else s=apparent;
      }
      for(i=0;s[i];i++)if(!strchr(FNAMECHARS,s[i]))ok=0;
      if(!ok){
	prompt(WEFFNR);
	continue;
      } else break;
    }

    strcpy(word1,s);
    if(!strcmp(apparent,word1))strcpy(word1,"");
    prompt(WEDFFN,latinize(s),subject);
    return(latinize(word1));
    return NULL;
  }
}


