/*****************************************************************************\
 **                                                                         **
 **  FILE:     mailer.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Off line mailer                                              **
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
 * Revision 1.1  2001/04/16 14:57:35  alexios
 * Initial revision
 *
 * Revision 0.7  1998/12/27 15:45:11  alexios
 * Added autoconf support.
 *
 * Revision 0.6  1998/08/14 11:31:09  alexios
 * No changes.
 *
 * Revision 0.5  1998/08/11 10:11:15  alexios
 * Minor changes.
 *
 * Revision 0.4  1998/07/24 10:19:54  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/12/02 20:45:35  alexios
 * Switched to using the archiver file instead of locally
 * defined compression/decompression programs.
 *
 * Revision 0.2  1997/11/06 20:06:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:42:54  alexios
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
#include <bbsinclude.h>

#include "bbs.h"
#include "mailer.h"
#include "mbk_mailer.h"


promptblk *msg, *archivers, *mailer_msg;


char *bbsid;
char *ctlname[6];
int entrykey;
int sopkey;
int chgdnl;
int defgrk;
int stpncnf;
int qwkuc;
int auddnl;
int audupl;
int uplkey;


void
about()
{
  prompt(ABOUT);
}


void
init()
{
  int i;

  initmodule(INITALL);
  archivers=opnmsg("archivers");
  msg=mailer_msg=opnmsg("mailer");
  setlanguage(thisuseracc.language);

  bbsid=stgopt(BBSID);
  entrykey=numopt(ENTRYKEY,0,129);
  chgdnl=numopt(CHGDNL,-100000,100000);
  defgrk=ynopt(DEFGRK);
  stpncnf=ynopt(STPNCNF);
  if((qwkuc=tokopt(QWKUC,"LOWERCASE","UPPERCASE"))==0){
    fatal("Option QWKUC in mailer.msg has bad value.");
  }else qwkuc--;
  auddnl=ynopt(AUDDNL);
  audupl=ynopt(AUDUPL);
  for(i=0;i<6;i++)ctlname[i]=stgopt(CTLNAME1+i);
  uplkey=numopt(UPLKEY,0,129);

  parseplugindef();
}


void
run()
{
  int shownmenu=0;
  char c;

  bzero(&userqwk,sizeof(userqwk));

  if(!haskey(&thisuseracc,entrykey)){
    prompt(NOAXES);
    return;
  }

  if(loadprefs(USERQWK,&userqwk)<0){
    endcnc();
    prompt(NEWCNF);
    setup();
    endcnc();
  }

  for(;;){
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(MENU);
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
	  prompt(SHORT);
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
      case 'S':
	setup();
	break;
      case 'D':
	download();
	break;
      case 'U':
	upload();
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
}


int
main(int argc, char *argv[])
{
  setprogname("mailer");
  atexit(done);
  init();
  run();
  done();
  return 0;
}
