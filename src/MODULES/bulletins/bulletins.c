/*****************************************************************************\
 **                                                                         **
 **  FILE:     bulletins.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Bulletin (article) reader for the clubs                      **
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
 * Revision 1.1  2001/04/16 14:54:47  alexios
 * Initial revision
 *
 * Revision 0.4  1999/07/28 23:10:22  alexios
 * Added a command to download a bulletin.
 *
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added legalese (how did we miss this file?). Added auto-
 * conf support, plus code to allow entry to the Bulletins
 * module from the Clubs module.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6. Added support for conversion of
 * Major BBS-based bulletin database.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
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
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


promptblk *msg, *clubmsg;

int   entrykey;
int   sopkey;
int   flaxes;
int   audins;
int   auddel;
int   audedt;
int   audrd;
int   askdef;
int   indsel;
int   indspd;
int   ainsdef;
char *dnldesc;


void
init()
{
  initmodule(INITALL);
  clubmsg=opnmsg("emailclubs");
  msg=opnmsg("bulletins");
  setlanguage(thisuseracc.language);

  initbltsubstvars();

  entrykey=numopt(ENTRYKEY,0,129);
  sopkey=numopt(SOPKEY,0,129);
  if((flaxes=tokopt(FLAXES,"CO-OPS","CLUBOP","PRIVILEGED")-1)<0){
    fatal("LEVEL2 option FLAXES (bulletins.msg) has bad value.");
  }
  audins=ynopt(AUDINS);
  auddel=ynopt(AUDDEL);
  audedt=ynopt(AUDEDT);
  audrd=ynopt(AUDRD);
  askdef=ynopt(ASKDEF);
  ainsdef=ynopt(AINSDEF);
  indsel=ynopt(INDSEL);
  indspd=numopt(INDSPD,1,500);
  dnldesc=stgopt(DNLDESC);

  dbopen();
}


void
about()
{
  prompt(ABOUT);
}


void
run()
{
  int shownmenu=0, ax;
  char c;

  if(thisuseronl.flags&OLF_JMP2BLT){
    strcpy(club,thisuseracc.lastclub);
    thisuseronl.flags&=~OLF_JMP2BLT;
  }

  if(!haskey(&thisuseracc,entrykey)){
    prompt(NOAXES);
    return;
  }

  for(;;){
    ax=getaccess(club)>=flaxes;
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(ax?SMENU:MENU);
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
	  if(club[0])prompt(CURSIG,club);
	  prompt(ax?SSHMENU:SHMENU);
	} else shownmenu=1;
	getinput(0);
	bgncnc();
      }
    }

    if((c=morcnc())!=0){
      cncchr();
      switch (c) {
      case 'H':
	about();
	break;
      case 'S':
	selectclub();
	thisuseronl.flags&=~OLF_MMCONCAT;
	if(!morcnc())endcnc();
	break;
      case 'I':
	if(getaccess(club)>=flaxes)insertblt();
	else {
	  prompt(ERRSEL,c);
	  endcnc();
	  continue;
	}
	break;
      case 'P':
	if(getaccess(club)>=flaxes)bltdel();
	else {
	  prompt(ERRSEL,c);
	  endcnc();
	  continue;
	}
	break;
      case 'E':
	if(getaccess(club)>=flaxes)bltedt();
	else {
	  prompt(ERRSEL,c);
	  endcnc();
	  continue;
	}
	break;
      case 'A':
	if(getaccess(club)>=flaxes)autoins();
	else {
	  prompt(ERRSEL,c);
	  endcnc();
	  continue;
	}
	break;
      case 'L':
	list(0);
	break;
      case 'F':
	list(1);
	break;
      case 'R':
	bltread();
	break;
      case 'D':
	bltdnl();
	break;
      case 'K':
	keysearch();
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
  dbclose();
}


int bltcnv_main(int argc, char *argv[]);


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  if(strstr(argv[0],"bltcnv"))return bltcnv_main(argc,argv);
  if(argc>1 && !strcmp(argv[1],"-cleanup")){
    cleanup();
    exit(0);
  }
  atexit(done);
  init();
  if(argc>1 && !strcmp(argv[1],"-login"))login();
  else if(argc==3 && !strcmp(argv[1],"-insert"))extins(argv[2]);
  else run();
  return 0;
}
