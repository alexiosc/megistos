/*****************************************************************************\
 **                                                                         **
 **  FILE:     remsys.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94, Version 0.05 alpha                               **
 **  PURPOSE:  Ye Arcane Menu of God-like Powers                            **
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
 * Revision 1.1  2001/04/16 14:58:07  alexios
 * Initial revision
 *
 * Revision 0.7  2000/01/06 11:42:07  alexios
 * Added variable pgstmo to denote the length of time after a
 * user's page to the system console that the event stays flagged
 * in the channel list and the main console itself.
 *
 * Revision 0.6  1998/12/27 16:07:28  alexios
 * Added autoconf support. Fixed slight locking bug.
 *
 * Revision 0.5  1998/07/24 10:23:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/06 16:59:23  alexios
 * Cosmetic fixes. Added new commands to the command array.
 * Sorted it.
 *
 * Revision 0.2  1997/09/12 13:24:18  alexios
 * Added code to read in values for options KEYCHU, DFWARN and
 * DFCRIT. Corrected showmenu() so that group delimiters (blank
 * lines) aren't shown for command groups with no commands in
 * them (i.e. if a Sysop has few commands in the REMSYS menu,
 * a lot of blank lines would appear).
 *
 * Revision 0.1  1997/08/28 11:05:52  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "remsys.h"

#include "mbk_remsys.h"

int       COMMANDS=0;
promptblk *msg;
char      lock[256];


char *unixsh;
char *sxfdesc;
int  keychu;
int  kydnam;
int  kydcom;
int  kydadr;
int  kydpho;
int  kydage;
int  kydsex;
int  kydpss;
int  hidepass;
int  dfwarn;
int  dfcrit;
int  pgstmo; 

struct rsysopt commands[]={
  {"CHANGE",    0, USY_CHANGE,    rsys_change},
  {"EMULATE",   0, USY_EMULATE,   rsys_emulate},
  {"MONITOR",   0, USY_MONITOR,   rsys_monitor},
  {"SEND",      0, USY_SEND,      rsys_send},
  {"DELETE",    1, USY_DELETE,    rsys_delete},
  {"DETAIL",    1, USY_DETAIL,    rsys_detail},
  {"EXEMPT",    1, USY_EXEMPT,    rsys_exempt},
  {"HANGUP",    1, USY_HANGUP,    rsys_hangup},
  {"POST",      1, USY_POST,      rsys_post},
  {"SEARCH",    1, USY_SEARCH,    rsys_search},
  {"SUSPEND",   1, USY_SUSPEND,   rsys_suspend},
  {"AUDIT",     2, USY_AUDIT,     rsys_audit},
  {"CLEANUP",   2, USY_CLEANUP,   rsys_cleanup},
  {"EVENT",     2, USY_EVENT,     rsys_event},
  {"FILTAUD",   2, USY_FILTAUD,   rsys_filtaud},
  {"LOGON",     2, USY_LOGON,     rsys_logon},
  {"SECURITY",  2, USY_SECURITY,  rsys_security},
  {"SIGNUPS",   2, USY_SIGNUPS,   rsys_signups},
  {"AGESTATS",  3, USY_AGESTATS,  rsys_agestats},
  {"CLSSTATS",  3, USY_CLSSTATS,  rsys_clsstats},
  {"GENSTATS",  3, USY_GENSTATS,  rsys_genstats},
  {"LINSTATS",  3, USY_LINSTATS,  rsys_linstats},
  {"MODSTATS",  3, USY_MODSTATS,  rsys_modstats},
  {"SYSTATS",   3, USY_SYSTATS,   rsys_systats},
  {"TOP",       3, USY_TOP,       rsys_top},
  {"CLASSED",   4, USY_CLASSED,   rsys_classed},
  {"KEYS",      4, USY_KEYS,      rsys_keys},
  {"USERCLASS", 4, USY_CLASS,     rsys_class},
  {"COPY",      5, USY_COPY,      rsys_copy},
  {"DIR",       5, USY_DIR,       rsys_dir},
  {"EDITOR",    5, USY_EDITOR,    rsys_editor},
  {"REN",       5, USY_REN,       rsys_ren},
  {"RM",        5, USY_DEL,       rsys_del},
  {"RUN",       5, USY_SYS,       rsys_sys},
  {"SHELL",     5, USY_SHELL,     rsys_shell},
  {"TRANSFER",  5, USY_TRANSFER,  rsys_transfer},
  {"TYPE",      5, USY_TYPE,      rsys_type},
  {"GDET",      9, USY_GDET,      rsys_gdet},
  {"INVIS",     9, USY_INVIS,     rsys_invis},
  {"PAGEAUDIT", 9, USY_PAGEAUDIT, rsys_pageaudit},
  {"SYSOP",     9, USY_SYSOP,     rsys_sysop},
  {"",          0, 0,             NULL}
}; 


int
runcommand(char *s)
{
  int res;

  thisuseronl.flags|=OLF_BUSY|OLF_NOTIMEOUT;
  doneinput();
  donesignals();
  system(STTYBIN" sane intr 0x03");
  res=system(s);
  system(STTYBIN" -echo start undef stop undef intr undef susp undef");
  regpid(thisuseronl.channel);
  initinput();
  initsignals();
  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
  resetinactivity();
  if(res==127 || res==-1)prompt(EXECERR,NULL);
  return res;
}


void
init()
{
  initmodule(INITALL|INITTTYNUM);
  msg=opnmsg("remsys");
  setlanguage(thisuseracc.language);

  unixsh=stgopt(UNIXSH);
  sxfdesc=stgopt(SXFDESC);
  keychu=numopt(KEYCHU,0,129);
  kydnam=numopt(KYDNAM,0,129);
  kydcom=numopt(KYDCOM,0,129);
  kydadr=numopt(KYDADR,0,129);
  kydpho=numopt(KYDPHO,0,129);
  kydage=numopt(KYDAGE,0,129);
  kydsex=numopt(KYDSEX,0,129);
  kydpss=numopt(KYDPSS,0,129);
  hidepass=ynopt(HIDEPASS);
  dfwarn=numopt(DFWARN,0,100);
  dfcrit=numopt(DFCRIT,0,100);
  pgstmo=numopt(PGSTMO,1,9999)*60;

  for(COMMANDS=0;commands[COMMANDS].command[0];COMMANDS++);

  sprintf(lock,"LCK-remsys-%s",thisuseronl.channel);
  placelock(lock,"inside");
}


void
done()
{
  sprintf(lock,"LCK-remsys-%s",thisuseronl.channel);
  rmlock(lock);
}


int
remsaccess()
{
  int i;
  if(sameas(thisuseracc.userid,SYSOP)) {
    for(i=0;i<sizeof(thisuseracc.sysaxs)/sizeof(long);i++)
      thisuseracc.sysaxs[i]=-1L;
    for(i=0;i<sizeof(thisuseracc.keys)/sizeof(long);i++)
      thisuseracc.keys[i]=-1L;
    return 1;
  }

  for(i=0;i<COMMANDS;i++){
    if(HASAXS(thisuseracc.sysaxs,commands[i].accessflag))return 1;
  }

  return 0;
}


void
showmenu(long *sysaxs,int altshow)
{
  int i, group=-1, a=0, sep=1;
  char opton[80]={0},optoff[80]={0};

  if(altshow){
    strncpy(opton,getmsg(OPTON),sizeof(opton));
    strncpy(optoff,getmsg(OPTOFF),sizeof(optoff));
  }
  
  for(i=0;i<COMMANDS;i++){
    if(lastresult==PAUSE_QUIT)break;
    if(commands[i].group!=group && group!=-1 && !sep){
      prompt(OPTSEP);
      sep=1;
    }
    group=commands[i].group;
    a=HASAXS(sysaxs,commands[i].accessflag);
    if(a||altshow){
      prompt(RSCOM01+i,a?opton:optoff);
      sep=0;
    }
  }
}


void
run()
{
  int shownmenu=1;

  if(!remsaccess())return;
  for(;;){
    if(!shownmenu){
      prompt(RSHDR,NULL);
      showmenu(thisuseracc.sysaxs,0);
      shownmenu=1;
    }
    prompt(RSSMNU,NULL);
    getinput(0);
    bgncnc();
    if(!margc || reprompt)continue;
    else if(margc==1 && sameas(margv[0],"?"))shownmenu=0;
    else if(margc==1 && isX(margv[0]))return;
    else {
      char *command;
      int i, found=0,execute=-1;
      
      command=cncword();
      for(i=0;i<COMMANDS;i++){
	if(sameto(command,commands[i].command)){
	  if(HASAXS(thisuseracc.sysaxs,commands[i].accessflag)&&commands[i].action){
	    found++;
	    execute=i;
	  }
	}
      }
      if(!found){
	prompt(ERRCOM);
	endcnc();
      } else if(found==1)(commands[execute].action)();
      else {
	prompt(MORCHR,command);
	endcnc();
      }
    }
    if(lastresult==PAUSE_QUIT)resetvpos(0);
  }
}


int
main(int argc, char **argv)
{
  setprogname(argv[0]);
  atexit(done);
  init();
  run();
  return 0;
}
