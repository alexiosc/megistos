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
 * Revision 1.2  2001/04/16 21:56:31  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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


promptblock_t *msg;


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
  mod_init(INI_ALL);
  msg=msg_open("emailclubs");
  msg_setlanguage(thisuseracc.language);

  entrykey=msg_int(ENTRYKEY,0,129);
  sopkey=msg_int(SOPKEY,0,129);
  wrtkey=msg_int(WRTKEY,0,129);
  netkey=msg_int(NETKEY,0,129);
  rrrkey=msg_int(RRRKEY,0,129);
  attkey=msg_int(ATTKEY,0,129);
  dnlchg=msg_int(DNLCHG,-32767,32767);
  wrtchg=msg_int(WRTCHG,-32767,32767);
  netchg=msg_int(NETCHG,-32767,32767);
  rrrchg=msg_int(RRRCHG,-32767,32767);
  attchg=msg_int(ATTCHG,-32767,32767);
  mkaudd=msg_bool(MKAUDD);
  mkaudu=msg_bool(MKAUDU);
  emllif=msg_int(EMLLIF,-1,32767);
  maxccs=msg_int(MAXCCS,0,32767);
  msglen=msg_int(MSGLEN,1,256)<<10;
  eattupl=msg_string(EATTUPL);
  sigbmax=msg_int(SIGBMAX,16,1024);
  siglmax=msg_int(SIGLMAX,1,32);
  sigckey=msg_int(SIGCKEY,0,129);
  sigchg=msg_int(SIGCHG,-32767,32767);
  afwkey=msg_int(AFWKEY,0,129);
  dlkey=msg_int(DLKEY,0,129);
  maxdlm=msg_int(MAXDLM,2,256);
  msskey=msg_int(MSSKEY,0,129);
  addnew=msg_bool(ADDNEW);
  defclub=msg_string(DEFCLUB);
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
about()
{
  prompt(ABOUT);
}


void
done()
{
  msg_close(msg);
  if(uqsc)saveqsc();
  lock_rm(inclublock);
  rmlocks();
}



int
run(int argc, char **argv)
{
  int shownmenu=0;
  char c=0;

  atexit(done);
  init();

  if(!key_owns(&thisuseracc,entrykey)){
    prompt(NOENTRY);
    return 0;
  }

  rmlocks();

  for(;;){
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(key_owns(&thisuseracc,sopkey)?EMMNU:EMMNU);
	shownmenu=2;
      }
    } else shownmenu=1;
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!cnc_nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return 0;
	}
	if(shownmenu==1){
	  prompt(key_owns(&thisuseracc,sopkey)?SHEMMNU:SHEMMNU);
	} else shownmenu=1;
	inp_get(0);
	cnc_begin();
      }
    }

    if((c=cnc_more())!=0){
      cnc_chr();
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
	return 0;
      case '?':
	shownmenu=0;
	break;
      default:
	prompt(ERRSEL,c);
	cnc_end();
	continue;
      }
    }
    if(fmt_lastresult==PAUSE_QUIT)fmt_resetvpos(0);
    cnc_end();

  }
}


int handler_userdel(int argc, char **argv)
{
  char *victim=argv[2], fname[1024];

  if(strcmp(argv[1],"--userdel")||argc!=3){
    fprintf(stderr,"User deletion handler: syntax error\n");
    return 1;
  }

  if(!usr_exists(victim)){
    fprintf(stderr,"User deletion handler: user %s does not exist\n",victim);
    return 1;
  }

  sprintf(fname,"%s/%s",MSGUSRDIR,victim);
  unlink(fname);
  sprintf(fname,"%s/%s",MSGSDISTDIR,victim);
  unlink(fname);
  sprintf(fname,"%s/%s",MSGSIGDIR,victim);
  unlink(fname);
  sprintf(fname,"%s/%s",CLUBAXDIR,victim);
  unlink(fname);
  sprintf(fname,"%s/%s",QSCDIR,victim);
  unlink(fname);

  return 0;
}


int
login(int argc, char **argv)
{
  int msgno=-1, ask=0, res;
  struct emailuser ecuser;
  
  init();
  newclubmsgs();

  if(!readecuser(thisuseracc.userid,&ecuser))return 0;

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
	if(!get_bool(&readnow,ASKRDNOW,ASKRDERR,ASKRDDEF,0)){
	  prompt(HOW2READ);
	  thisuseronl.flags&=~OLF_INHIBITGO;
	  return 0;
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

  done();
  return 0;
}


mod_info_t mod_info_email = {
  "email",
  "Email",
  "Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
  "Read/write private BBS or Internet messages and set reading preferences.",
  RCS_VER,
  "1.0",
  {99,login},		/* Login handler */
  { 0,run},			/* Interactive handler */
  { 0,NULL},			/* Install logout handler */
  { 0,NULL},			/* Hangup handler */
  { 5,handler_cleanup},		/* Cleanup handler */
  {50,handler_userdel}		/* Delete user handler */
};


int
main(int argc, char *argv[])
{
  mod_setinfo(&mod_info_email);
  return mod_main(argc,argv);
}
