/*****************************************************************************\
 **                                                                         **
 **  FILE:     files.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  File Libraries                                               **
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
 * Revision 1.1  2001/04/16 14:55:44  alexios
 * Initial revision
 *
 * Revision 0.6  2000/01/06 10:37:25  alexios
 * Added string to hold the dummy file description of a file in
 * a OS-only library.
 *
 * Revision 0.5  1999/07/18 21:29:45  alexios
 * Minor changes to accommodate the changed calling conventions
 * of download() and filelisting().
 *
 * Revision 0.4  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Included PEFFIC from updown.msg to help in calculating
 * transfer times. More options parsed from the msg file. All
 * main menu commands are now functional. Lots of other minor
 * changes.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
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
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk_files.h"

#define __EMAILCLUBS_UNAMBIGUOUS__
#include "mbk_emailclubs.h"

#define __UPDOWN_UNAMBIGUOUS__
#include "mbk_updown.h"


promptblk *msg;

int  entrykey;
int  libopkey;
int  defrkey;
int  defdkey;
int  defukey;
int  defokey;
int  defflim;
int  defslim;
int  defllim;
int  defuchg;
int  defdchg;
int  defreb;
int  defuaud;
int  defdaud;
char *libmain;
int  maxnest;
char *rdmefil;
int  rdmesiz;
char *othrdme;
int  numtries;
char *filedes;
char *fnchars;
int  deslen;
int  maxkeyw;
int  accmtsd;
int  sldevto;
int  sldcmax;
int  sldctim;
int  sldcsmn;
char *filelst;
char *othrfls;
char *fileind;
char *fileindd;
char *mfilind;
char *mfilindd;
char *filetop;
int   numtops;
int   showhid;
char *filelstd;
char *topfild;
char *mfiletp;
int   nummtps;
char *mtpfild;
char *mfillst;
char *mfillstd;
int   srlstln;
char *osfdesc;

int  sopkey;

int  peffic;


void
readsettings()
{
  entrykey=numopt(ENTRYKEY,0,129);
  libopkey=numopt(LIBOPKEY,0,129);
  defrkey=numopt(DEFRKEY,0,129);
  defdkey=numopt(DEFDKEY,0,129);
  defukey=numopt(DEFUKEY,0,129);
  defokey=numopt(DEFOKEY,0,129);
  defflim=numopt(DEFFLIM,0,1000000);
  defslim=numopt(DEFSLIM,0,1000000);
  defllim=numopt(DEFLLIM,0,1000000);
  defuchg=numopt(DEFUCHG,-1000000,1000000);
  defdchg=numopt(DEFDCHG,-1000000,1000000);
  defreb=numopt(DEFREB,-100,100);
  defuaud=ynopt(DEFUAUD);
  defdaud=ynopt(DEFDAUD);
  libmain=stgopt(LIBMAIN);
  maxnest=numopt(MAXNEST,1,12);
  rdmefil=stgopt(RDMEFIL);
  rdmesiz=numopt(RDMESIZ,1,1024)<<10;
  othrdme=stgopt(OTHRDME);
  numtries=numopt(NUMTRIES,1,1000);
  filedes=stgopt(FILEDES);
  maxkeyw=numopt(MAXKEYW,1,100);
  accmtsd=ynopt(ACCMTSD);
  sldevto=numopt(SLDEVTO,1,3600);
  sldcmax=numopt(SLDCMAX,1,1024);
  sldctim=numopt(SLDCTIM,1,10000);
  sldcsmn=numopt(SLDCSMN,1,1048576);
  filelst=stgopt(FILELST);
  fileind=stgopt(FILEIND);
  fileindd=stgopt(FILEINDD);
  mfilind=stgopt(MFILIND);
  mfilindd=stgopt(MFILINDD);
  filetop=stgopt(FILETOP);
  numtops=numopt(NUMTOPS,5,1000);
  showhid=ynopt(SHOWHID);
  othrfls=stgopt(OTHRFLS);
  filelstd=stgopt(FILELSTD);
  topfild=stgopt(TOPFILD);
  mfiletp=stgopt(MFILETP);
  nummtps=numopt(NUMMTPS,5,1000);
  mtpfild=stgopt(MTPFILD);
  mfillst=stgopt(MFILLST);
  mfillstd=stgopt(MFILLSTD);
  srlstln=numopt(SRLSTLN,2,20);
  osfdesc=stgopt(OSFDESC);

  {
    char buf[256];
    sprintf(buf,"abcdefghijklmnopqrstuvwxyz01234567890%s",getmsg(FNCHARS));
    fnchars=strdup(lowerc(buf));
  }

  if(tokopt(DESLEN,"118","374","886","1398",
	    "1910","2422","2934","3446","3958")==0){
    fatal("Option DESLEN in files.msg has bad value");
  } else deslen=numopt(DESLEN,118,3958);
}


void
init()
{
  initmodule(INITALL);

  dblibopen();
  dbkeyopen();
  dbfileopen();

  msg=opnmsg("updown");
  peffic=numopt(UPDOWN_PEFFIC,1,1000);
  clsmsg(msg);

  msg=opnmsg("emailclubs");
  setlanguage(thisuseracc.language);
  sopkey=numopt(EMAILCLUBS_SOPKEY,0,129);
  clsmsg(msg);

  msg=opnmsg("files");
  setlanguage(thisuseracc.language);

  initslowdevs();
  readsettings();

  initlibsubstvars();		/* Initialise substitution variables */
  makemainlib();		/* If necessary, create the main library */
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

  enterlastlib();		/* Enter last used library */

  if(!haskey(&thisuseracc,entrykey)){
    prompt(NOAXES);
    return;
  }

  for(;;){
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(libop?OPMENU:MENU);
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
	  prompt(libop?OPSHORT:SHORT);
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
      case 'T':
	libtree();
	break;
      case 'S':
	selectlib();
	thisuseronl.flags&=~OLF_MMCONCAT;
	if(!morcnc())endcnc();
	break;
      case 'I':
	fullinfo();
	break;
      case 'U':
	upload();
	break;
      case 'F':
	filesearch();
	break;
      case 'D':
	download(NULL);
	break;
      case 'L':
	filelisting(1);
	break;
      case 'O':
	thisuseronl.flags&=~OLF_MMCONCAT;
	if(!morcnc())endcnc();
	if(!libop){
	  prompt(ERRSEL,c);
	  endcnc();
	  continue;
	} else operations();
	break;
      case 'X':
	prompt(LEAVE);
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
  unlocklib();
  adminunlock();
}


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  if(strstr(argv[0],"libcnv")){
    setprogname("libcnv");
    return cnvmain(argc,argv);
  } else if(!strcmp(argv[0],"filecleanup")){
    setprogname("filecleanup");
    return cleanup();
  }
  setprogname("files");
  atexit(done);
  init();
  run();
  done();
  return 0;
}
