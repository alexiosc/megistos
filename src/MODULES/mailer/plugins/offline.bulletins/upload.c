/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.bulletins.c                                          **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Bulletins plugin, download                                   **
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
 * Revision 1.1  2001/04/16 14:57:42  alexios
 * Initial revision
 *
 * Revision 0.4  1998/12/27 15:46:41  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:20:15  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:59  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:53:22  alexios
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
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "offline.bulletins.h"
#include "../../mailer.h"
#include "mbk_offline.bulletins.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __BULLETINS_UNAMBIGUOUS__
#include "mbk_bulletins.h"


static int bltdb;


static char *
zonk(char *s, int len)
{
  int i;
  for(i=len-1;i&&((s[i]==' ')||(s[i]==0));i--)s[i]=0;
  for(i=0;s[i]==' ';i++);
  return &s[i];
}


static int
process(char *command)
{
  if(sameas(command,"BLT-IDX")){
    if(prefs.flags&OBF_INDEX){
      prompt(OBULIDNN);
    } else {
      prompt(OBULIDOK);
      prefs.flags|=OBF_REQIDX;
      writeprefs(&prefs);
    }
  } else if(sameto("BLT-REQ",command)){
    char *cp;
    char blt[256];
    struct bltidx idx;

    /* Scan the argument first */

    if(sscanf(command,"%*s %s",blt)!=1){
      prompt(OBULRR,&command[7]);
      return 0;
    }

    /* Properly formulated? */

    if((cp=strchr(blt,'/'))==NULL){
      prompt(OBULRR,blt);
      return 0;
    }
    *cp++=0;

    /* Does the club exist? */
    if(!findclub(blt)){
      prompt(OBULUC,blt,cp);
      return 0;
    }

    /* Do we have permission to read the article? */
    if(getclubax(&thisuseracc,blt)<CAX_READ){
      prompt(OBULUC,blt,cp);
      return 0;
    }

    /* Does the bulletin exist? */
    d_dbset(bltdb);
    if(!dbexists(blt,cp)){
      prompt(OBULUB,blt,cp);
      return 0;
    }
   
    /* Load the bulletin and add a request record for it */
    
    dbget(&idx);

    mkrequest(idx.area,
	      "BULLETIN",
	      idx.fname,
	      -1,
	      RQP_OTHER,
	      RQF_INVIS|RQF_BULLETIN);

    prompt(OBULOK);

  } else return 1; /* Should never happen */

  return 0;
}


int
obupload()
{
  struct reqidx idx;
  int res, stop=0;
  char *s;
  int shown=0;

  readprefs(&prefs);
  openreqdb();
  dbopen();
  d_dbget(&bltdb);
  res=getfirstreq(&idx);

  for(res=getfirstreq(&idx);res;res=getnextreq(&idx)){
    if(idx.priority!=RQP_CTLMSG)continue;

    s=zonk(idx.reqfname,sizeof(idx.reqfname));
    if(!(sameas(s,"BLT-IDX")||sameto("BLT-REQ",s)))continue;
    if(!shown){
      shown=1;
      prompt(OBUPL);
    }
    stop=process(s);

    /* Remove the current request from the database */

    unlink(idx.dosfname);
    if(!rmrequest(&idx)){
      fatal("Unable to remove request %d from the database.",
	    idx.reqnum);
    }

    if(stop)break;
  }
  if(shown)prompt(OBULEND);

  return 0;
}
