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
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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
const char *__RCS=RCS_VER;
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


promptblock_t *msg, *archivers, *mailer_msg;


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

  mod_init(INI_ALL);
  archivers=msg_open("archivers");
  msg=mailer_msg=msg_open("mailer");
  msg_setlanguage(thisuseracc.language);

  bbsid=msg_string(BBSID);
  entrykey=msg_int(ENTRYKEY,0,129);
  chgdnl=msg_int(CHGDNL,-100000,100000);
  defgrk=msg_bool(DEFGRK);
  stpncnf=msg_bool(STPNCNF);
  if((qwkuc=msg_token(QWKUC,"LOWERCASE","UPPERCASE"))==0){
    error_fatal("Option QWKUC in mailer.msg has bad value.");
  }else qwkuc--;
  auddnl=msg_bool(AUDDNL);
  audupl=msg_bool(AUDUPL);
  for(i=0;i<6;i++)ctlname[i]=msg_string(CTLNAME1+i);
  uplkey=msg_int(UPLKEY,0,129);

  parseplugindef();
}


void
run()
{
  int shownmenu=0;
  char c=0;

  bzero(&userqwk,sizeof(userqwk));

  if(!key_owns(&thisuseracc,entrykey)){
    prompt(NOAXES);
    return;
  }

  if(loadprefs(USERQWK,&userqwk)<0){
    cnc_end();
    prompt(NEWCNF);
    setup();
    cnc_end();
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
      if(!cnc_nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return;
	}
	if(shownmenu==1){
	  prompt(SHORT);
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

  sprintf(fname,"%s/%s",MAILERUSRDIR,victim);
  unlink(fname);

  return 0;
}


mod_info_t mod_info_mailer = {
  "mailer",
  "Off-Line Mailer",
  "Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
  "Packages parts of the BBS for off-line browsing and use.",
  RCS_VER,
  VERSION,
  {0,NULL},			/* Login handler */
  {0,handler_run},		/* Interactive handler */
  {0,NULL},			/* Install logout handler */
  {0,NULL},			/* Hangup handler */
  {0,NULL},			/* Cleanup handler */
  {50,handler_userdel}		/* Delete user handler */
};


int
main(int argc, char *argv[])
{
  mod_setinfo(&mod_info_mailer);
  return mod_main(argc,argv);
}
