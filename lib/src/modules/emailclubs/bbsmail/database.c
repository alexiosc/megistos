/*****************************************************************************\
 **                                                                         **
 **  FILE:     utils.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **            D, August 1996, Version 2.0                                  **
 **  PURPOSE:  Various support functions for bbsmail                        **
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
 * Revision 1.1  2001/04/16 15:02:48  alexios
 * Initial revision
 *
 * Revision 1.3  1998/12/27 16:31:55  alexios
 * Added autoconf support. Migrated to new locking style.
 *
 * Revision 1.2  1998/07/24 10:29:57  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:17:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 11:23:40  alexios
 * Initial revision
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "bbsmail.h"
#include "ecdbase.h"
#include "typhoon.h"
#include "mbk_emailclubs.h"


void
addtodb(struct message *msg, int email)
{
  char lock[256], dir[256];

  /* Wait for locks to clear */

  sprintf(lock,CLUBLOCK,(email?EMAILCLUBNAME:msg->club));
  if(waitlock(lock,5)==LKR_TIMEOUT){
    if(usercaller)prompt(TIMEOUT1);
    if(waitlock(lock,55)==LKR_TIMEOUT){
      if(usercaller)prompt(TIMEOUT2);
      logerror("Timed out (60 sec) waiting for %s",lock);
      exit(1);
    }
  }


  /* Lock it */

  placelock(lock,"adding");


  /* Open the database */

  if(email)sprintf(dir,"%s/%s",EMAILDIR,DBDIR);
  else sprintf(dir,"%s/%s/%s",MSGSDIR,msg->club,DBDIR);
  mkdir(dir,0777);
  d_dbfpath(dir);
  d_dbdpath(DBDDIR);
  if(d_open(".ecdb","s")!=S_OKAY){
    rmlock(lock);
    logerror("Cannot open database for %s (db_status %d)\n",
	     email?EMAILCLUBNAME:msg->club,db_status);
    return;
  }


  /* Prepare index record */

  {
    struct ecidx idx;

    idx.num=msg->msgno;
    strcpy(idx.from,msg->from);
    strcpy(idx.to,msg->to);
    strcpy(idx.subject,msg->subject);
    idx.flags=msg->flags;
    d_fillnew(ECIDX,&idx);
  }

  
  /* Close the database */

  d_close();


  /* Done, remove lock */

  rmlock(lock);
}
