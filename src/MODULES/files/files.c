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
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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
const char *__RCS=RCS_VER;
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


promptblock_t *msg;

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
  entrykey=msg_int(ENTRYKEY,0,129);
  libopkey=msg_int(LIBOPKEY,0,129);
  defrkey=msg_int(DEFRKEY,0,129);
  defdkey=msg_int(DEFDKEY,0,129);
  defukey=msg_int(DEFUKEY,0,129);
  defokey=msg_int(DEFOKEY,0,129);
  defflim=msg_int(DEFFLIM,0,1000000);
  defslim=msg_int(DEFSLIM,0,1000000);
  defllim=msg_int(DEFLLIM,0,1000000);
  defuchg=msg_int(DEFUCHG,-1000000,1000000);
  defdchg=msg_int(DEFDCHG,-1000000,1000000);
  defreb=msg_int(DEFREB,-100,100);
  defuaud=msg_bool(DEFUAUD);
  defdaud=msg_bool(DEFDAUD);
  libmain=msg_string(LIBMAIN);
  maxnest=msg_int(MAXNEST,1,12);
  rdmefil=msg_string(RDMEFIL);
  rdmesiz=msg_int(RDMESIZ,1,1024)<<10;
  othrdme=msg_string(OTHRDME);
  numtries=msg_int(NUMTRIES,1,1000);
  filedes=msg_string(FILEDES);
  maxkeyw=msg_int(MAXKEYW,1,100);
  accmtsd=msg_bool(ACCMTSD);
  sldevto=msg_int(SLDEVTO,1,3600);
  sldcmax=msg_int(SLDCMAX,1,1024);
  sldctim=msg_int(SLDCTIM,1,10000);
  sldcsmn=msg_int(SLDCSMN,1,1048576);
  filelst=msg_string(FILELST);
  fileind=msg_string(FILEIND);
  fileindd=msg_string(FILEINDD);
  mfilind=msg_string(MFILIND);
  mfilindd=msg_string(MFILINDD);
  filetop=msg_string(FILETOP);
  numtops=msg_int(NUMTOPS,5,1000);
  showhid=msg_bool(SHOWHID);
  othrfls=msg_string(OTHRFLS);
  filelstd=msg_string(FILELSTD);
  topfild=msg_string(TOPFILD);
  mfiletp=msg_string(MFILETP);
  nummtps=msg_int(NUMMTPS,5,1000);
  mtpfild=msg_string(MTPFILD);
  mfillst=msg_string(MFILLST);
  mfillstd=msg_string(MFILLSTD);
  srlstln=msg_int(SRLSTLN,2,20);
  osfdesc=msg_string(OSFDESC);

  {
    char buf[256];
    sprintf(buf,"abcdefghijklmnopqrstuvwxyz01234567890%s",msg_get(FNCHARS));
    fnchars=strdup(lowerc(buf));
  }

  if(msg_token(DESLEN,"118","374","886","1398",
	    "1910","2422","2934","3446","3958")==0){
    error_fatal("Option DESLEN in files.msg has bad value");
  } else deslen=msg_int(DESLEN,118,3958);
}


void
init()
{
  mod_init(INI_ALL);

  dblibopen();
  dbkeyopen();
  dbfileopen();

  msg=msg_open("updown");
  peffic=msg_int(UPDOWN_PEFFIC,1,1000);
  msg_close(msg);

  msg=msg_open("emailclubs");
  msg_setlanguage(thisuseracc.language);
  sopkey=msg_int(EMAILCLUBS_SOPKEY,0,129);
  msg_close(msg);

  msg=msg_open("files");
  msg_setlanguage(thisuseracc.language);

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
  char c=0;

  enterlastlib();		/* Enter last used library */

  if(!key_owns(&thisuseracc,entrykey)){
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
      if(!cnc_nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return;
	}
	if(shownmenu==1){
	  prompt(libop?OPSHORT:SHORT);
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
      case 'T':
	libtree();
	break;
      case 'S':
	selectlib();
	thisuseronl.flags&=~OLF_MMCONCAT;
	if(!cnc_more())cnc_end();
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
	if(!cnc_more())cnc_end();
	if(!libop){
	  prompt(ERRSEL,c);
	  cnc_end();
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
	cnc_end();
	continue;
      }
    }
    if(fmt_lastresult==PAUSE_QUIT)fmt_resetvpos(0);
    cnc_end();

  }
}


void
done()
{
  msg_close(msg);
  unlocklib();
  adminunlock();
}


int
handler_run(int argc, char *argv[])
{
  atexit(done);
  init();
  run();
  done();
  return 0;
}


int handler_cleanup(int argc, char **argv)
{
  cleanup();
  return 0;
}


mod_info_t mod_info_files = {
  "files",
  "File Library",
  "Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
  "Archives files thematically, allowing uploads, downloads et cetera.",
  RCS_VER,
  "1.0",
  {0,NULL},			/* Login handler */
  {0,handler_run},		/* Interactive handler */
  {0,NULL},			/* Install logout handler */
  {0,NULL},			/* Hangup handler */
  {50,handler_cleanup},		/* Cleanup handler */
  {0,NULL}			/* Delete user handler */
};


int
main(int argc, char *argv[])
{
  if(strstr(argv[0],"libcnv")){
    mod_setprogname("libcnv");
    return cnvmain(argc,argv);
  }

  mod_setinfo(&mod_info_files);
  return mod_main(argc,argv);
}
