/*****************************************************************************\
 **                                                                         **
 **  FILE:     download.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, October 94, Version 0.5 alpha                             **
 **  PURPOSE:  Download files                                               **
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
 * Revision 1.1  2001/04/16 15:02:58  alexios
 * Initial revision
 *
 * Revision 0.10  1999/07/18 22:09:33  alexios
 * Changed a few fatal() calls to fatalsys(). Added code to deal
 * with transient files. Minor bug fixes.
 *
 * Revision 0.9  1998/12/27 16:34:28  alexios
 * Added autoconf support.
 *
 * Revision 0.8  1998/11/30 22:13:02  alexios
 * Changed the sleep period in the wait-for-child loop to .5 sec.
 *
 * Revision 0.7  1998/11/30 22:06:09  alexios
 * Temporarily disables character translation for viewers and
 * protocols with the PRF_BINARY (bin yes) option set. This
 * fixes a serious design bug that mangled up binary protocol
 * file transfers when people were using character translation.
 * Added a waitpid() to make sure no zombie processes are left
 * after downloading. Added comments and beautified a bit.
 *
 * Revision 0.6  1998/07/26 21:50:23  alexios
 * Added support for per-file ok/fail shell commands.
 *
 * Revision 0.5  1998/07/24 10:31:31  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/12/02 20:47:45  alexios
 * Switched to using the archiver file instead of the viewer
 * file.
 *
 * Revision 0.3  1997/11/06 20:18:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 17:06:53  alexios
 * Switched to the new auditing scheme().
 *
 * Revision 0.1  1997/08/28 11:25:42  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_STRING_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_WAIT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "updown.h"
#include "mbk_updown.h"


int firstentry=0;


static void
showmenu()
{
  int i, pos=0;
  
  if(NUMFILES==1)
    prompt(DNLHDR,xferlist[firstentry].filename,xferlist[firstentry].description,
	   filesize,xfertime,getpfix(MINSNG,xfertime),filetype);
  else prompt(DNLHDR1,filesize,xfertime,getpfix(MINSNG,xfertime));

  for(i=0;i<numprotocols;i++){
    if((protocols[i].flags&PRF_UPLOAD)==0 &&
       (NUMFILES==1 || protocols[i].flags&PRF_BATCH)){
      char flush[80];
      int j=(i/2)%2+1;
      
      sprintf(flush,"%33s",protocols[i].name);
      while(flush[j]==32 && flush[j+1]==32){
	flush[j]='.';
	j+=2;
      }
      prompt(PROTLIN1+pos,protocols[i].select,flush);
      pos=(pos+1)%2;
    }
  }
  if(pos)prompt(PROTLIN2,"","");
  if(!logout){
    prompt(DNLFTR,getpfix(YES,xfertagged));
    prompt(DNLFTRI,NUMFILES,xfertagged?0:numtagged);
  }
  prompt(DNLFTRL);
}


static int
viewcontents()
{
  int i;
  char fmt[512], command[512],fname[256];
  
  if(NUMFILES!=1)return 0;
  for(i=0;i<numprotocols;i++){
    if((protocols[i].flags&PRF_UPLOAD)==0 && 
       protocols[i].flags&PRF_VIEWER){
      
      sprintf(fname,TMPDIR"/fv%05d",getpid());
      sprintf(fmt,"%s &>%s",protocols[i].command,fname);
      sprintf(command,fmt,xferlist[firstentry].fullname);
      prompt(VIEWWRK);
      
      /* Turn off translation if the protocol is binary */
      if(protocols[i].flags&PRF_BINARY)setxlationtable(XLATION_OFF);
      
      system(command);
      
      /* Turn translation back on if necessary */
      if(protocols[i].flags&PRF_BINARY)setxlationtable(XLATION_ON);
      prompt(VIEWBEG,xferlist[firstentry].filename);
      printfile(fname);
      prompt(VIEWEND);
      unlink(fname);
      break;
    }
  }
  return 1;
}


static int
checksuccess(char *fname)
{
  DIR    *dp;
  struct dirent *dirent;
  char   command[256];
  int    filesleft=0,i;
  int    retry=0,total=0;

  for(i=0;i<totalitems;i++){
    if(xferlist[i].flags&XFF_KILLED)continue;
    if(xferlist[i].flags&XFF_TAGGED && (!xfertagged))continue;

    /* Execute the success command */

    /*
    if((xferlist[i].flags&XFF_AUDIT) && xferlist[i].cmdok[0]){
      char command[4096];
      sprintf(command,"%s %d '%s'",
	      xferlist[i].cmdok,
	      i,
	      xferlist[i].fullname);
      system(command);
    }
    */

    /* Audit the download */

    if((xferlist[i].flags&(XFF_AUDIT|XFF_AUDITED))==XFF_AUDIT){
      if(xferlist[i].auditsok[0] && xferlist[i].auditdok[0]){
	audit(thisuseronl.channel,
	      xferlist[i].auditfok,
	      xferlist[i].auditsok,
	      xferlist[i].auditdok,
	      thisuseracc.userid,
	      xferlist[i].filename);
      }
      xferlist[i].flags|=XFF_AUDITED|XFF_SUCCESS;
      xferlist[i].flags&=~XFF_AUDIT;
    }
    

    xferlist[i].flags|=XFF_CHECK;
  }
  
  if((dp=opendir(fname))==NULL) return 1;
  while((dirent=readdir(dp))!=NULL){
    if(strcmp(dirent->d_name,".")&&strcmp(dirent->d_name,"..")){
      filesleft++;
      for(i=0;i<totalitems;i++){
	if(xferlist[i].flags&(XFF_KILLED /* |XFF_CHECK */ ))continue;
	if(xferlist[i].flags&XFF_TAGGED && (!xfertagged))continue;
	if(!strcmp(xferlist[i].filename,dirent->d_name)){
	  if(xferlist[i].auditsfail[0] && xferlist[i].auditdfail[0]){
	    audit(thisuseronl.channel,
		  xferlist[i].auditffail,
		  xferlist[i].auditsfail,
		  xferlist[i].auditdfail,
		  thisuseracc.userid,
		  xferlist[i].filename);
	  }
	  if(xferlist[i].cmdfail[0]){
	    char command[4096];
	    sprintf(command,"%s %d '%s'",
		    xferlist[i].cmdfail,
		    i,
		    xferlist[i].fullname);
	    system(command);
	  }
	  xferlist[i].flags&=~XFF_CHECK;
	}
      }
    }
  }
  closedir(dp);
  
  if(filesleft){
    autodis=0;
    prompt(DNLFAIL,filesleft);
    if(!getbool(&retry,RETRY,0,0,0))retry=0;
  }
  
  sprintf(command,"rm -rf %s &>/dev/null",fname);
  system(command);
  
  for(i=0;i<totalitems;i++){
    if(xferlist[i].flags&XFF_KILLED)continue;
    if(xferlist[i].flags&XFF_TAGGED && (!xfertagged))continue;
    if(xferlist[i].flags&XFF_CHECK && retry)xferlist[i].flags&=~XFF_CHECK;
    else if(xferlist[i].flags&XFF_CHECK && !retry){
      xferlist[i].flags&=~XFF_CHECK;
      xferlist[i].flags|=XFF_KILLED;
      if((xferlist[i].flags&XFF_AUDITED)==0){
	if(xferlist[i].auditsok[0] && xferlist[i].auditdok[0]){
	  audit(thisuseronl.channel,
		xferlist[i].auditfok,
		xferlist[i].auditsok,
		xferlist[i].auditdok,
		thisuseracc.userid,
		xferlist[i].filename);
	}
	xferlist[i].flags|=XFF_AUDITED|XFF_SUCCESS;

	if(xferlist[i].cmdok[0]){
	  char command[4096];
	  sprintf(command,"%s %d '%s'",
		  xferlist[i].cmdok,
		  i,
		  xferlist[i].fullname);
	  system(command);
	}
      }

      thisuseracc.filesdnl++;
      if(sysvar)sysvar->filesdnl++;
      total+=xferlist[i].size;
    }
    thisuseracc.bytesdnl+=total;
    if(sysvar)sysvar->bytesdnl+=(total/100);
  }
  
  return !retry;
}


int
download(char *prot)
{
  int  i, f=-1;
  char fname[256], command[256], cwd[256];
  
  for(i=0;i<numprotocols;i++){
    if((protocols[i].flags&PRF_UPLOAD)==0 &&
       (NUMFILES==1 || protocols[i].flags&PRF_BATCH) &&
       (sameas(protocols[i].select,prot))){
      f=i;
      break;
    }
  }
  if(f==-1){
    prompt(ERRSEL,prot);
    return -1;
  }
  
  sprintf(fname,TMPDIR"/dnl%05d",getpid());
  sprintf(command,"rm -rf %s &>/dev/null",fname);

  system(command);
  mkdir(fname,0777);

  for(i=0;i<totalitems;i++){
    if(xferlist[i].flags&XFF_KILLED)continue;
    if(xferlist[i].flags&XFF_TAGGED && (!xfertagged))continue;
    sprintf(fname,TMPDIR"/dnl%05d/%s",getpid(),xferlist[i].filename);
    symlink(xferlist[i].fullname,fname);
  }

  sprintf(fname,TMPDIR"/dnl%05d",getpid());
  getcwd(cwd,sizeof(cwd));
  chdir(fname);
  sprintf(command,"%s `ls -A`",protocols[f].command);

  {
    char s1[80],s2[80];
    
    strncpy(s1,getmsg(SDNLOAD),80);
    strncpy(s2,getpfix(SSINGLE,NUMFILES),80);

    prompt(XFERBEG,s1,s2,protocols[f].name,protocols[f].stopkey);
  }

  {
    int pid, status;

    thisuseronl.flags|=OLF_BUSY;
    pid=fork();
    if(!pid){

      /* The child process -- run the protocol and exit */

      char stty[256];

      /* Turn off translation if the protocol is binary. It's ok to do
         this inside the child process since setxlationtable()
         modifies shared memory. */
      if(protocols[f].flags&PRF_BINARY)setxlationtable(XLATION_OFF);

      clsmsg(sysblk);
      doneoutput();
      doneinput();
      donesignals();
      sprintf(stty,"%s sane intr 0x03",STTYBIN);
      system(stty);
      system(command);
      system(STTYBIN" -echo start undef stop undef intr undef susp undef");
      system(stty);
      initoutput();
      setmbk(msg);
      initinput();
      initsignals();

      /* Turn translation back on if necessary */
      if(protocols[f].flags&PRF_BINARY)setxlationtable(XLATION_ON);

      exit(0);
    } else if(pid>0){

      /* Now wait for the child process to finish */

      char process[64],statfile[256];
      struct stat st;
      
      sprintf(process,"%s/%d",PROCDIR,pid);
      sprintf(statfile,"%s/stat",process);
      for(;!stat(process,&st);){
	FILE *fp=NULL;
	DIR    *dp;
	struct dirent *dirent;
	int    i;

	/* While the download process is running, keep checking for finished
	   files. We know they're finished because it's a requirement for
	   protocols to remove files as soon as they're done with them.

	   This way, we can audit downloads as soon as each file is finished by
	   looping through all the files to download and checking whether they
	   still exist or not (not to worry, they're all symlinks anyway, so
	   deleting them doesn't hurt the *actual* files. */
	
	for(i=0;i<totalitems;i++){
	  if(xferlist[i].flags&(XFF_KILLED|XFF_AUDITED))continue;
	  if(xferlist[i].flags&XFF_TAGGED && (!xfertagged))continue;
	  xferlist[i].flags|=XFF_AUDIT;
	}

	if((dp=opendir(fname))==NULL) return 1;
	while((dirent=readdir(dp))!=NULL){
	  if(strcmp(dirent->d_name,".")&&strcmp(dirent->d_name,"..")){
	    for(i=0;i<totalitems;i++){
	      if(xferlist[i].flags&(XFF_KILLED))continue;
	      if(xferlist[i].flags&XFF_TAGGED && (!xfertagged))continue;
	      if(!strcmp(xferlist[i].filename,dirent->d_name)){
		xferlist[i].flags&=~XFF_AUDIT;
	      }
	    }
	  }
	}
	closedir(dp);
	
	for(i=0;i<totalitems;i++){
	  if(xferlist[i].flags&XFF_KILLED)continue;
	  if(xferlist[i].flags&XFF_TAGGED && (!xfertagged))continue;
	  if(xferlist[i].flags&XFF_AUDIT){
	    xferlist[i].flags&=~XFF_AUDIT;
	    xferlist[i].flags|=XFF_AUDITED|XFF_SUCCESS;
	    if(xferlist[i].auditsok[0] && xferlist[i].auditdok[0]){
	      audit(thisuseronl.channel,
		    xferlist[i].auditfok,
		    xferlist[i].auditsok,
		    xferlist[i].auditdok,
		    thisuseracc.userid,
		    xferlist[i].filename);
	    }
	  }
	}

	/* Ok, now that we've logged files, go to sleep for a bit. */
	
	usleep(500000);		/* sleep for half a second */
	fp=fopen(statfile,"r");
	if(fp){
	  int  dummy1;
	  char dummy2[256];
	  char pstate=0;
	  
	  if(fscanf(fp,"%d %s %c",&dummy1,dummy2,&pstate)==3){
	    if(dummy1==pid && pstate=='Z'){
	      fclose(fp);
	      break;
	    }
	  }
	}
	if(fp)fclose(fp);
      }
    } else {
      fatal("Unable to fork download protocol for some obscure reason.");
    }
    
    /* Now that we know the child process is dead, wait() for it so that it
       dies peacfully. Zombies aren't vegetarians. We specify WNOHANG so that,
       if for some weird reason all hell breaks loose and the zombie won't die
       (or no zombie was born), we won't wait for ever. Mind you, this is
       extremely unlikely to happen, but a working system is the prize for
       paranoia (when they're not all out to get us). */

    pid=waitpid(-1,&status,WNOHANG);


    /* And re-init all the necessary stuff */

    initinput();
    initsignals();
    regpid(thisuseronl.channel);
    thisuseronl.flags&=~OLF_BUSY;
    chdir(cwd);
  }

  return checksuccess(fname);
}


static void
restat()
{
  int i;

  numitems=0;
  numtagged=0;
  taggedsize=0;
  getfilesize();
  for(i=0;i<totalitems;i++){
    if(xferlist[i].flags&XFF_KILLED)continue;
    if(xferlist[i].flags&XFF_TAGGED){
      numtagged++;
      taggedsize+=xferlist[i].size;
    } else numitems++;
  }
}


static void
tageditor()
{
  char c;
  int i,firsttime=1;

  while(getmenu(&c,firsttime,TEMENU,TESHMNU,TEERR,"LTDS",0,0)){
    firsttime=0;
    switch(c){
    case 'L':
      {
	char mark[80];

	strncpy(mark,getmsg(TELMRK),sizeof(mark));
	prompt(TELHDR);
	for(i=0;i<totalitems;i++){
	  prompt(TELTAB,i+1,xferlist[i].filename,
		 xferlist[i].flags&XFF_TAGGED?mark:"",
		 xferlist[i].flags&XFF_KILLED?mark:"",
		 xferlist[i].description);
	  if(lastresult==PAUSE_QUIT)break;
	}
	if(lastresult!=PAUSE_QUIT)prompt(TELFTR);
	break;
      }
    case 'T':
      if(getnumber(&i,TENASK,1,totalitems,TENERR,0,0)){
	if(xferlist[i-1].dir==FXM_TRANSIENT
	   && (xferlist[i-1].flags&XFF_TAGGED)==0){
	  endcnc();
	  prompt(CANTAG,xferlist[i-1].filename);
	} else {
	  xferlist[--i].flags^=XFF_TAGGED;
	  prompt(xferlist[i].flags&XFF_TAGGED?TENTAG:TENUTG,
		 i+1,xferlist[i].filename);
	}
      }
      break;
    case 'D':
      if(getnumber(&i,TENASK,1,totalitems,TENERR,0,0)){
	xferlist[--i].flags^=XFF_KILLED;
	prompt(xferlist[i].flags&XFF_KILLED?TENKLL:TENUKL,
	       i+1,xferlist[i].filename);
      }
      break;
    case 'S':
      restat();
      prompt(TESTAT,numitems,filesize,xfertime,getpfix(MINSNG,xfertime),
	     numtagged,taggedsize);
      break;
    }
  }
  restat();
}


void
getfirstentry()
{
  int i;
  
  for(i=0;i<totalitems;i++){
    if(xferlist[i].flags&XFF_KILLED)continue;
    if(xferlist[i].flags&XFF_TAGGED && (!xfertagged))continue;
    firstentry=i;
    break;
  }
}


void
dologout()
{
  int yes;
  if(!logout)return;
  prompt(LOGOUT,NUMFILES,getpfix(FILSNG,NUMFILES));
  for(;;)if(getbool(&yes,LOGOUT2,0,0,0))break;
  if(!yes)exit(0);
  if(nxtcmd==NULL||!*nxtcmd)endcnc();
}


static int
confirm_exit()
{
  int retval;
  if(!getbool(&retval,CONFX,0,0,0))return 0;
  return retval;
}


void
downloadrun()
{
  int  shownmenu=0;
  char *s;

  dologout();

  getfirstentry();
  for(;;){
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	showmenu();
	shownmenu=1;
      }
    } else shownmenu=1;
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return;
	}
	if(!shownmenu){
	  showmenu();
	  shownmenu=1;
	}
	prompt(SHORT);
	getinput(0);
	bgncnc();
      }
    }

    if(!margc || reprompt){
      endcnc();
      continue;
    }

    s=cncword();

    if(sameas(s,"?"))shownmenu=0;
    else if(sameas(s,"X")){
      if(confirm_exit())return;
    } else {
      char *excl=NULL;

      rstrin();
      excl=strchr(s,'!');
      if(excl || ((excl=strchr(nxtcmd,'!'))!=NULL)){
	autodis=1;
	if(excl)*excl=0;
      }

      if(sameas(s,"V")){
	if(!viewcontents())prompt(ERRSEL,s);
      } else if((!logout)&&sameas(s,"T")){
	int i, trans=0, nontrans=0;
	for(i=0;i<totalitems;i++){
	  if(xferlist[i].dir==FXM_TRANSIENT){
	    trans++;
	    prompt(CANTAG,xferlist[i].filename);
	  } else {
	    nontrans++;
	    xferlist[i].flags|=XFF_TAGGED;
	  }
	}
	if(!trans){
	  prompt(TAGFIL);
	  return;
	} else if(nontrans){
	  prompt(TAGSOM);
	  endcnc();
	  continue;
	}
      } else if((!logout)&&sameas(s,"TT")){
	shownmenu=0;
	xfertagged=!xfertagged;
	getfilesize();
      } else if((!logout)&&sameas(s,"TE")){
	tageditor();
	if(!NUMFILES){
	  prompt(NOFILES);
	  return;
	} else {
	  shownmenu=0;
	  getfirstentry();
	  getfilesize();
	  getfiletype(xferlist[firstentry].fullname,MAXRECURSE);
	}
      } else {
	switch(download(s)){
	case 0:
	  shownmenu=0;
	  break;
	case -1:
	  endcnc();
	  break;
	case 1:
	  if(autodis)autodisconnect();
	  return;
	default:
	  shownmenu=0;
	}
      }
    }
    endcnc();
  }
}

