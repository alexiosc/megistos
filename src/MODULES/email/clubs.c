/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubs.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1995, Version 0.5                                    **
 **            B, August 1996, Version 0.6                                  **
 **  PURPOSE:  Main module for the Clubs (SIGs)                             **
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
 * Revision 1.1  2001/04/16 14:55:02  alexios
 * Initial revision
 *
 * Revision 0.6  1999/07/18 21:21:38  alexios
 * Added support for the network manager menu.
 *
 * Revision 0.5  1998/12/27 15:33:03  alexios
 * Added autoconf support. Added code to enter bulletins from
 * within the main club menu (at last).
 *
 * Revision 0.4  1998/08/11 10:03:22  alexios
 * Added msg parameters to set the default accesses for new
 * clubs.
 *
 * Revision 0.3  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
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
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"

#define __CLUBS_C
#include "clubs.h"
#include "email.h"


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
int  tlckey;
int  bltkey;
char *tlcpag;
char *bltpag;
int  addnew;
int  drdaxkey;
int  ddlaxkey;
int  dwraxkey;
int  dulaxkey;

int  defaultrate;



void
init()
{
  initmodule(INITALL);
  msg=opnmsg("emailclubs");
  setlanguage(thisuseracc.language);

  defaultrate=thisuseronl.credspermin;
  strcpy(inclublock,"dummy");

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
  tlckey=numopt(TLCKEY,0,129);
  bltkey=numopt(BLTKEY,0,129);
  tlcpag=stgopt(TLCPAG);
  bltpag=stgopt(BLTPAG);

  clntrkey=numopt(CLNTRKEY,0,129);
  clsopkey=numopt(CLSOPKEY,0,129);
  tlckey=numopt(TLCKEY,0,129);
  bltkey=numopt(BLTKEY,0,129);
  clbwchg=numopt(CLBWCHG,-32767,32767);
  clbuchg=numopt(CLBUCHG,-32767,32767);
  clbdchg=numopt(CLBDCHG,-32767,32767);
  clblif=numopt(CLBLIF,0,32767);
  cdnlaud=ynopt(CDNLAUD);
  cuplaud=ynopt(CUPLAUD);
  defclub=stgopt(DEFCLUB);
  bzero(defaultclub,sizeof(defaultclub));
  strncpy(defaultclub,defclub,sizeof(defaultclub));
  if(*defclub=='/')defclub++;
  modaxkey=numopt(MODAXKEY,0,129);
  modchkey=numopt(MODCHKEY,0,129);
  modhdkey=numopt(MODHDKEY,0,129);
  drdaxkey=numopt(DRDAXKEY,0,129);
  ddlaxkey=numopt(DDLAXKEY,0,129);
  dwraxkey=numopt(DWRAXKEY,0,129);
  dulaxkey=numopt(DULAXKEY,0,129);
  addnew=ynopt(ADDNEW);

  initlist();
  initecsubstvars();
}


void
login()
{
}


void
about()
{
  prompt(CLABOUT);
}


void
information()
{
  showbanner();
  prompt(CLINFO);
}



int
selectclub()
{
  char *i;
  char c;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      if(sameas(nxtcmd,"?")){
	listclubs();
	endcnc();
	continue;
      }
      i=cncword();
    } else {
      prompt(SCASK);
      getinput(0);
      bgncnc();
      i=cncword();
      if(!margc){
	endcnc();
	continue;
      } else if(isX(margv[0]))return 0;
      if(sameas(margv[0],"?")){
	listclubs();
	endcnc();
	continue;
      }
    }

    if(*i=='/')i++;

    if(!findclub(i)){
      prompt(SCERR);
      endcnc();
      continue;
    } else break;
  }

  strcpy(thisuseracc.lastclub,i);
  enterdefaultclub();
  return 1;
}


void
run()
{
  int shownmenu=0;
  int shownbanner=0;
  int access=CAX_ZERO;
  char c;

  if(!haskey(&thisuseracc,clntrkey)){
    prompt(CLNONTR);
    return;
  }

  if(!thisuseracc.lastclub[0])strcpy(thisuseracc.lastclub,defclub);
  if(!findclub(defclub)){
    fatal("Default club %s does not exist!",defclub);
  }

  rmlocks();

  for(;;){
    enterdefaultclub();
    access=getclubax(&thisuseracc,clubhdr.club);

    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownbanner){
	showbanner();
	shownbanner=1;
      }
      if(!shownmenu){
	switch(access){
	case CAX_SYSOP:
	case CAX_CLUBOP:
	  prompt(CLMNU3,clubhdr.nfunapp);
	  break;
	case CAX_COOP:
	  prompt(CLMNU2,clubhdr.nfunapp);
	  break;
	default:
	  prompt(CLMNU1,clubhdr.nfunapp);
	  break;
	}
	shownmenu=2;
      }
    } else shownmenu=1;
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(nxtcmd==NULL){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return;
	}
	if(shownmenu==1){
	  switch(access){
	  case CAX_SYSOP:
	  case CAX_CLUBOP:
	    prompt(SHCLMNU3);
	    break;
	  case CAX_COOP:
	    prompt(SHCLMNU2);
	    break;
	  default:
	    prompt(SHCLMNU1);
	    break;
	  }
	} else shownmenu=1;
	getinput(0);
	bgncnc();
      }
    }

    if((c=morcnc())!=0){
      cncchr();
      shownbanner=1;
      switch (c) {
      case 'H':
	about();
	endcnc();
	break;
      case 'I':
	information();
	endcnc();
	break;
      case 'S':
	if(selectclub())shownbanner=0;
	thisuseronl.flags&=~OLF_MMCONCAT;
	if(!morcnc())endcnc();
	break;
      case 'L':
	longlistclubs();
	endcnc();
	break;
      case 'W':
	clubwrite();
	endcnc();
	break;
      case 'R':
	clubread(0);
	endcnc();
	break;
      case 'D':
	clubread(1);
	endcnc();
	break;
      case 'A':
	if(access>=CAX_COOP)fileapp();
	else prompt(ERRSEL,c);
	endcnc();
	break;
      case 'O':
	if(access>=CAX_CLUBOP)operations();
	else prompt(ERRSEL,c);
	endcnc();
	break;
#ifdef HAVE_METABBS
      case 'N':
	if(access>=CAX_CLUBOP)networking();
	else prompt(ERRSEL,c);
	endcnc();
	break;
#endif
      case 'T':
	if(haskey(&thisuseracc,tlckey)){
	  sprintf(thisuseronl.telechan,"/%s",clubhdr.club);
	  gopage(tlcpag);
	} else prompt(TLCNAX);
	endcnc();
	break;
      case 'B':
	if(haskey(&thisuseracc,bltkey)){
	  thisuseronl.flags|=OLF_JMP2BLT;
	  gopage(bltpag);
	} else prompt(BLTNAX);
	endcnc();
	break;
      case 'X':
	prompt(CLLEAVE);
	return;
      case '?':
	shownmenu=0;
	endcnc();
	break;
      default:
	prompt(ERRSEL,c);
	endcnc();
	continue;
      }
    }
    if(lastresult==PAUSE_QUIT)resetvpos(0);
    if(!morcnc())endcnc();
  }
}


void
done()
{
  if(uqsc)saveqsc();
  rmlock(inclublock);
  rmlocks();
}


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  if(strstr(argv[0],"msgcnv"))return msgcnv_main(argc,argv);
  atexit(done);
  init();
  if(argc>1 && !strcmp(argv[1],"-login"))login();
  else run();
  exit(0);
}
