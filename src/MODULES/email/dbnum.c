/*****************************************************************************\
 **                                                                         **
 **  FILE:     dbnum.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.5                                     **
 **            B, August 1996, Version 0.9                                  **
 **  PURPOSE:  Database, findmsgnum() feature.                              **
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
 * Revision 1.2  2001/04/16 21:56:31  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
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
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "typhoon.h"
#include "email.h"
#include "ecdbase.h"


static int
getfl(int *first, int *last)
{

  /* Get the first key of the database. If there isn't one, the db is empty. */

  if(d_keyfrst(NUM)!=S_OKAY)return BSE_NFOUND;


  /* Read the first key. If we can't something's VERY wrong. Panic. */

  if(d_keyread(first)!=S_OKAY){
    error_fatal("Unable to read first NUM key.");
  }


  /* Get the last key of the database, panic if unable to do so */

  if(d_keylast(NUM)!=S_OKAY) {
    error_fatal("Got first NUM key but can't get last one.");
  }


  /* Read the last key. Panic if we can't. */

  if(d_keyread(last)!=S_OKAY){
    error_fatal("Unable to read last NUM key.");
    exit(1);
  }


  /* We've found the first and last records. Say so. */

  return BSE_FOUND;
}


static int
getmsgno(int *msgno, int dir)
{
  int first, last;

  /* Look for a message # msgno */

  if(d_keyfind(NUM,msgno)==S_OKAY)return BSE_FOUND;

  /* Couldn't find that specific message. Let's look for another one. */
  /* Start by getting first and last messages. */

  if(getfl(&first,&last)==BSE_NFOUND) return BSE_NFOUND;

  /* Now handle up (GT) and down (LT) directions slightly differently. */

  if(dir&BSD_LT){

    /* Moving down (LT). Distinguish three sub-cases. */


    /* msgno < first number? No record found. */

    if(*msgno<first) return BSE_BEGIN;


    /* msgno > last number? Since we're going down, the last # applies. */

    if(*msgno>last) return (*msgno=last, BSE_FOUND);


    /* Otherwise, we've hit a gap between messages. Choose the next one. */

    d_keyfind(NUM,msgno);

    if(d_keynext(NUM)!=S_OKAY){
      error_fatal("No next NUM key. This should never happen.");
    }
    
    if(d_keyread(msgno)!=S_OKAY){
      error_fatal("Unable to read NUM key. Should never happen.");
    }


  } else {

    /* Moving up (GT) */

    /* Distinguish the same three cases, but treat things a bit different. */


    /* msgno < first message. We're going up, so we choose #first. */

    if(*msgno<first) return (*msgno=first, BSE_FOUND);
    
    
    /* msgno > last. Since we're going up, we're out of messages. */

    if(*msgno>last) return BSE_END;


    /* This is the same as before. Got two copies of it for clarity. */

    d_keyfind(NUM,msgno);

    if(d_keynext(NUM)!=S_OKAY){
      error_fatal("No next NUM key. This should never happen.");
    }
    
    if(d_keyread(msgno)!=S_OKAY){
      error_fatal("Unable to read NUM key. Should never happen.");
    }
  }

  /* We've chosen a value for msgno, now say so. */

  return BSE_FOUND;
}

int x;

int
findmsgnum(int *msgno, int targetnum, int direction)
{
  long res;

  d_keyfind(NUM,&targetnum);


  /* If we're only checking for existence, return now */

  if(direction==BSD_EQ) return (db_status==S_OKAY)? BSE_FOUND: BSE_NFOUND;

  
  /* Now look for other applicable message numbers. */

  *msgno=targetnum;
  if((res=getmsgno(msgno, direction))==BSE_FOUND){
    d_keyfind(NUM,msgno);
    return BSE_FOUND;
  }
  return res;
}


int
npmsgnum(int *msgno, int targetnum, int dir)
{
  int j;

  if(dir==BSD_GT)j=d_keynext(NUM);
  else j=d_keyprev(NUM);

  if(j!=S_OKAY)return BSE_NFOUND;
  
  if(d_keyread(&j)!=S_OKAY){
    error_fatal("Unable to read key though it exists.\n");
  }

  if(dir==BSD_GT && j<targetnum)return BSE_NFOUND;
  if(dir==BSD_LT && j>targetnum)return BSE_NFOUND;

  *msgno=j;
  return BSE_FOUND;
}

