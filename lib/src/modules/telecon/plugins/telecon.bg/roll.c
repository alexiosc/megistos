/*****************************************************************************\
 **                                                                         **
 **  FILE:     roll.c                                                       **
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
 * Revision 1.2  2001/04/16 21:56:33  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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



static int fx_d1, fx_d2;


static char *
fx_firstroll(struct chanusr *u)
{
  char s1[80], s2[80];

  if(sameas(u->userid,player[0])||sameas(u->userid,player[1]))return NULL;

  strcpy(s1,msg_getunitl(SEXM,sex[0]==USX_MALE,othruseracc.language));
  strcpy(s2,msg_getunitl(SEXML,sex[1]==USX_MALE,othruseracc.language));

  sprintf(fx_prompt,msg_getl(ROL13RD,othruseracc.language),
	  s1,player[0],fx_d1,
	  s2,player[1],fx_d2,
	  s1,player[0]);

  return fx_prompt;
}



/* Do the first roll. If necessary, swap the two players round. */

void
bg_firstroll()
{
  int d1, d2;
  

  /* Roll the dice */

  do {
    d1=rnd6();
    d2=rnd6();
  } while(d1==d2);


  /* Swap the players, if we needs to */

  if(d1>d2){
    cturn=1;
  } else {
    char tmp[24];

    strcpy(tmp,player[0]);	/* Swap player names. player[0] has white */
    strcpy(player[0],player[1]);
    strcpy(player[1],tmp);

    tmp[0]=sex[0];		/* Swapping sexes? Definitely kinky */
    sex[0]=sex[1];
    sex[1]=tmp[0];

    tmp[0]=d1;			/* Make sure d1 is the winning roll */
    d1=d2;
    d2=tmp[0];
    cturn=-1;
  }


  /* Notify winner */

  if(!usr_insys(player[0],0))exit(0);
  sprintf(out_buffer,msg_getl(ROLL1WIN,othruseracc.language),
	  msg_getunitl(SEXM,sex[1]==USX_MALE,othruseracc.language),
	  player[1],
	  d2,d1);
  usr_injoth(&othruseronl,out_buffer,0);
	  

  /* Notify loser */

  if(!usr_insys(player[1],0))exit(0);
  sprintf(out_buffer,msg_getl(ROLL1LOS,othruseracc.language),
	  msg_getunitl(SEXM,sex[0]==USX_MALE,othruseracc.language),
	  player[0],
	  d1,d2);
  usr_injoth(&othruseronl,out_buffer,0);
	  

  /* Notify everyone else */
  
  fx_d1=d1;
  fx_d2=d2;
  broadcastchnall(channel,fx_firstroll,1);
}
