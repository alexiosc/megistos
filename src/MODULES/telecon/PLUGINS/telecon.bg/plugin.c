/*****************************************************************************\
 **                                                                         **
 **  FILE:     telecon.test.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 99                                                 **
 **  PURPOSE:  Test teleconference plugin.                                  **
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
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/08/13 17:03:41  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif


#define debug(fmt...) \
{ usr_insys(player[0],0); sprintf(outbuf,##fmt); usr_injoth(&othruseronl,outbuf,0); }


#define __TELEPLUGIN__


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>
#include <mbk/mbk_telecon.bg.h>

#include "bbs.h"
#include "telecon.h"
#include "plugins.h"
#include "telecon.bg.h"


int lucky_number;
char fx_prompt[8192];
struct pluginmsg p;


char player[2][24];		/* Player user IDs */
char sex   [2];			/* Player sexes */


/* Config variables */

int  waitacc;


static void
controllingpart()
{
  if(thisuseronl.flags&OLF_MMCONCAT){
    strcpy(inp_buffer,thisuseronl.input);
    cnc_begin();
  }

  if(margc==1){
    if(sameas(margv[0],"-")){
      print("HERE: Playing against computer\n");
      exit(0);
    } else if(!(sameas(margv[0],"?")||sameas(margv[0],"help"))){
      char *userid=margv[0];

      /* Validate the given user name */

      if(!tlcuidxref(userid,0)){
	prompt(UNKUID,userid);
	exit(1);
      } else if(!usr_insys(userid,1)||!(othruseronl.flags&OLF_INTELECON)){
	prompt(UNKUID,userid);
	exit(1);
      } else if(!strcmp(userid,thisuseracc.userid)){
	prompt(NOTSELF);
	exit(1);
      } else {
	char buf[16384];
	char fmt[8192];

	/* Ok, the oponent is fine. */

	prompt(OKUID,msg_getunit(SEXM,othruseracc.sex==USX_MALE),othruseracc.userid);


	/* Notify the other user. */

	strcpy(fmt,msg_getl(BGREQ,othruseracc.language));
	sprompt_other(othrshm,buf,BGREQ,
		      msg_getunitl(SEXM,
				   thisuseracc.sex==USX_MALE,
				   othruseracc.language),
		      thisuseracc.userid,thisuseracc.userid);
	usr_injoth(&othruseronl,buf,0);


	/* Store the two user names */

	strcpy(player[0],thisuseracc.userid);
	strcpy(player[1],othruseracc.userid);
	sex[0]=thisuseracc.sex;
	sex[1]=othruseracc.sex;

	return;
      }
    }
  }

  /* Anything else is either an error or a request for help. Issue help in
     either case. */

  prompt(HELP0);
  exit(0);
}



static char *
fx_announce(struct chanusr *u)
{
  sprintf(fx_prompt,msg_getl(ANNOUNCE,othruseracc.language),
	  player[0],player[1]);
  return fx_prompt;
}


static char *
fx_end(struct chanusr *u)
{
  strcpy(fx_prompt,"Finished with plugin, removing...\n");
  return fx_prompt;
}


static void
wait_for_acceptance()
{
  int n;
  time_t t0=time(NULL)+waitacc;

  for(;;){

    if(t0<time(NULL))break;

    n=msgrcv(qid,(struct msg_buffer*)&p,sizeof(p)-sizeof(long),0,IPC_NOWAIT);

    /* Got a message? */

    if(n>0){

      /* Is the challenger issuing commands? Foo! */

      if(sameas(p.userid,player[0])){
	if(!usr_insys(player[0],0))exit(0);
	if(sameas(p.text,"?") || sameas(p.text,"help")){
	  sprintf(out_buffer,msg_getl(HELP1,othruseracc.language));
	} else {
	  sprompt_other(othrshm,out_buffer,ACCPAT,
			msg_getunitl(SEXML,
				     sex[1]==USX_MALE,
				     othruseracc.language),
			player[1]);
	}
	usr_injoth(&othruseronl,out_buffer,0);
      }


      /* Has the challengee accepted the challenge? */

      else if(sameas(p.userid,player[1])){
	if(!usr_insys(player[1],0))exit(0);
	if(sameas(p.text,"?") || sameas(p.text,"help")){
	  sprompt_other(othrshm,out_buffer,HELP1);
	} else if(sameas(p.text,player[0])){
	  print("challengee accepted challenge.\n");
	  return;
	} else {
	  sprompt_other(othrshm,out_buffer,REQPAT,player[0]);
	}
	usr_injoth(&othruseronl,out_buffer,0);
      }


      /* How about a third party? */

      else {
	usr_insys(p.userid,0);
	sprompt_other(othrshm,out_buffer,BGALR);
	usr_injoth(&othruseronl,out_buffer,0);
      }
    }
    usleep(50000);
  }


  /* Timed out. Notify both parties. */

  if(usr_insys(player[0],0)){
    sprompt_other(othrshm,out_buffer,ACCTMOUT,
		  msg_getunitl(SEXML,sex[1]==USX_MALE,othruseracc.language),
		  player[1]);
    usr_injoth(&othruseronl,out_buffer,0);
  }
  if(usr_insys(player[1],0)){
    sprompt_other(othrshm,out_buffer,REQTMOUT);
    usr_injoth(&othruseronl,out_buffer,0);
  }

  exit(0);
}


static void
run()
{
  int n;
  int a=0;

  /* First thing to do: wait for opponent to accept challenge */

  wait_for_acceptance();


  /* So far so good. Start a game at last! */

  broadcastchnall(channel,fx_announce,1);

  bg_set_players(2);		/* Number of players */
  bg_initialise();		/* Initialise board etc */
  bg_firstroll();		/* Set order of players */
  bg_board(0);			/* Print board for player 1 */
  bg_board(1);			/* ...and player 2 */
  exit(0);

  for(a=0;a<10;){
    n=msgrcv(qid,(struct msg_buffer*)&p,sizeof(p)-sizeof(long),0,IPC_NOWAIT);
    print("n=%d, p.userid=(%s), p.text=(%s)\n",n,p.userid,p.text);
    if(n>0){
      a++;
      /*broadcastchnall(channel,fx_test,1);*/
    }
    usleep(50000);
  }
  broadcastchnall(channel,fx_end,1);
}


static void
init_bg()
{
  mod_init(INI_ALL);
  msg=msg_open("telecon.bg");
  msg_setlanguage(thisuseracc.language);
  waitacc=msg_int(WAITACC,2,60)*60;
}


int
main(int argc, char *argv[])
{
  mod_setprogname(argv[0]);
  initplugin(argc,argv);
  init_bg();
  controllingpart();
  becomeserver();
  run();
  return 0;
}
