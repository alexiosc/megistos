/*****************************************************************************\
 **                                                                         **
 **  FILE:     email.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **            B, August 1996, Version 0.6                                  **
 **  PURPOSE:  Front end to the BBS mail system                             **
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
 * Revision 1.1  2001/04/16 14:55:09  alexios
 * Initial revision
 *
 * Revision 0.7  1999/07/18 21:21:38  alexios
 * Changed return value of main() from void (silly) to int.
 *
 * Revision 0.6  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/11 10:03:22  alexios
 * Club listings are now case sensitive. Fixed previous RCS
 * logs. Added parameters to set default accesses for new clubs.
 * User's first connection now adds all clubs to their quick-
 * scan *and* off-line configuration and assumes all messages
 * are read.
 * Minor login mode bug fix.
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:04:17  alexios
 * Fixed bug in login() that would cause a SIGSEGV while
 * entering clubs to check for new mail. Fixed newclubmsgs()
 * so it initialises the user's Quickscan record properly and
 * doesn't display old club messages as new.
 * Also, added call to writeecuser() to save the user's email
 * preferences (and last read email message) when mail is read
 * from the login process
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "email.h"
#include "clubs.h"


promptblk *msg;


int  entrykey;
int  sopkey;
int  wrtkey;
int  netkey;
int  rrrkey;
int  attkey;
int  dnlchg;
int  wrtchg;
int  netchg;
int  rrrchg;
int  attchg;
int  mkaudd;
int  mkaudu;
int  maxccs;
int  emllif;
int  msglen;
char *eattupl;
int  sigbmax;
int  siglmax;
int  sigckey;
int  sigchg;
int  afwkey;
int  dlkey;
int  maxdlm;
int  msskey;
int  addnew;
int  drdaxkey;
int  ddlaxkey;
int  dwraxkey;
int  dulaxkey;


void
init()
{
  initmodule(INITALL);
  msg=opnmsg("emailclubs");
  setlanguage(thisuseracc.language);

  entrykey=numopt(ENTRYKEY,0,129);
  sopkey=numopt(SOPKEY,0,129);
  wrtkey=numopt(WRTKEY,0,129);
  netkey=numopt(NETKEY,0,129);
  rrrkey=numopt(RRRKEY,0,129);
  attkey=numopt(ATTKEY,0,129);
  dnlchg=numopt(DNLCHG,-32767,32767);
  wrtchg=numopt(WRTCHG,-32767,32767);
  netchg=numopt(NETCHG,-32767,32767);
  rrrchg=numopt(RRRCHG,-32767,32767);
  attchg=numopt(ATTCHG,-32767,32767);
  mkaudd=ynopt(MKAUDD);
  mkaudu=ynopt(MKAUDU);
  emllif=numopt(EMLLIF,-1,32767);
  maxccs=numopt(MAXCCS,0,32767);
  msglen=numopt(MSGLEN,1,256)<<10;
  eattupl=stgopt(EATTUPL);
  sigbmax=numopt(SIGBMAX,16,1024);
  siglmax=numopt(SIGLMAX,1,32);
  sigckey=numopt(SIGCKEY,0,129);
  sigchg=numopt(SIGCHG,-32767,32767);
  afwkey=numopt(AFWKEY,0,129);
  dlkey=numopt(DLKEY,0,129);
  maxdlm=numopt(MAXDLM,2,256);
  msskey=numopt(MSSKEY,0,129);
  addnew=ynopt(ADDNEW);
  defclub=stgopt(DEFCLUB);
  bzero(defaultclub,sizeof(defaultclub));
  strncpy(defaultclub,defclub,sizeof(defaultclub));
  if(*defclub=='/')defclub++;

  initlist();
  initecsubstvars();
}


static void makenewqsc()
{
  initialise();
  all(1);
  all(1);
  saveqsc();
  doneqsc();
  prompt(CLUBINFO);
}


void
newclubmsgs()
{
  struct lastread *l;
  struct dirent **clubs;
  int i,j,n,t,done=0,msgno;
  struct stat st;
  char fname[256];
  struct emailuser ecuser;

  bzero(&ecuser,sizeof(ecuser));
  if(!readecuser(thisuseracc.userid,&ecuser))bzero(&ecuser,sizeof(ecuser));
  sprintf(fname,"%s/%s",QSCDIR,thisuseracc.userid);
  if(stat(fname,&st)||st.st_size==0||(ecuser.flags&ECF_QSCCFG)==0){
    makenewqsc();
    return;
  }


  /* If it's empty, the user is new; add all the clubs. */

  if(!startqsc()){
    makenewqsc();
    return;
  }

  /* Old user, scan for new messages */

  n=scandir(CLUBHDRDIR,&clubs,hdrselect,ncsalphasort);

  prompt(CHKNCLB);
  for(i=0;i<n;free(clubs[i]),i++){
    char *cp=&clubs[i]->d_name[1];
    if(done)continue;
    if(!loadclubhdr(cp))continue;
    if(getclubax(&thisuseracc,cp)>=CAX_ZERO){
      if((l=findqsc(cp))!=NULL)t=max(l->lastmsg,l->emllast)+1;
      else t=0;
      setclub(cp);
      j=findmsgto(&msgno,thisuseracc.userid,t,BSD_GT);
      if((j==BSE_FOUND)&&(msgno>=t)){
	prompt(NEWCLUB);
	done=1;
      }
    }
  }
  free(clubs);
  doneqsc();
  if(!done)prompt(NNEWCLB);
}


void
login()
{
  int msgno=-1, ask=0, res;
  struct emailuser ecuser;

  newclubmsgs();

  if(!readecuser(thisuseracc.userid,&ecuser))return;

  setclub(NULL);
  res=findmsgto(&msgno,thisuseracc.userid,ecuser.lastemailread+1,BSD_GT);

  if(res==BSE_FOUND){
    prompt(NEWMAIL);
    ask=1;
  } else {
    res=findmsgto(&msgno,thisuseracc.userid,0,BSD_GT);
    if(res==BSE_FOUND)prompt(OLDMAIL);
    else msgno=-1;
  }

  if(msgno>=0){
    if(ecuser.prefs&(ECP_LOGINYES|ECP_LOGINASK)){
      int readnow=ecuser.prefs&ECP_LOGINYES;
      if((ecuser.prefs&ECP_LOGINASK) && ask){
	thisuseronl.flags|=OLF_INHIBITGO;
	if(!getbool(&readnow,ASKRDNOW,ASKRDERR,ASKRDDEF,0)){
	  prompt(HOW2READ);
	  thisuseronl.flags&=~OLF_INHIBITGO;
	  return;
	}
      }
      if(readnow){
	thisuseronl.flags|=OLF_INHIBITGO;
	startreading(0,msgno);
      } else {
	/*	ecuser.lastemailread=msgno;
		writeecuser(thisuseracc.userid,&ecuser);*/
	prompt(HOW2READ);
      }
      thisuseronl.flags&=~OLF_INHIBITGO;
    } else {
      prompt(HOW2READ);
    }
  }
}


void
about()
{
  prompt(ABOUT);
}


void
run()
{
  int shownmenu=0;
  char c;

  if(!haskey(&thisuseracc,entrykey)){
    prompt(NOENTRY);
    return;
  }

  rmlocks();

  for(;;){
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(haskey(&thisuseracc,sopkey)?EMMNU:EMMNU);
	shownmenu=2;
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
	if(shownmenu==1){
	  prompt(haskey(&thisuseracc,sopkey)?SHEMMNU:SHEMMNU);
	} else shownmenu=1;
	getinput(0);
	bgncnc();
      }
    }

    if((c=morcnc())!=0){
      cncchr();
      switch (c) {
      case 'A':
	about();
	break;
      case 'W':
	emailwrite();
	break;
      case 'R':
	emailread();
	break;
      case 'M':
	modifymail();
	break;
      case 'P':
	preferences();
	break;
      case 'D':
	confdistlist();
	break;
      case 'X':
	prompt(EMLEAVE);
	return;
      case '?':
	shownmenu=0;
	break;
      default:
	prompt(ERRSEL,c);
	endcnc();
	continue;
      }
    }
    if(lastresult==PAUSE_QUIT)resetvpos(0);
    endcnc();

  }
}


void
done()
{
  clsmsg(msg);
  if(uqsc)saveqsc();
  rmlock(inclublock);
  rmlocks();
}


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  atexit(done);
  init();
  if(argc>1 && !strcmp(argv[1],"-login"))login();
  else run();
  exit(0);
}
