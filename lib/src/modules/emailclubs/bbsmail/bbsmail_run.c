/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsmail_run.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **  PURPOSE:  Send a BBS E-mail message.                                   **
 **  NOTES:    See syntax() function for the syntax of this program.        **
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
 * Revision 1.2  2001/04/16 21:56:34  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 1.0  1999/07/28 23:18:23  alexios
 * Initial revision
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "bbsmail.h"

#define __SYSVAR_UNAMBIGUOUS__ 1
#include "mbk_sysvar.h"
#include "mbk_emailclubs.h"


void
bbsmail_run(char *fname, char *srcname, int copymode, char *attachment)
{
  int email=1;
  struct message msg, msg0;


#ifdef DEBUG
  printf("fname=(%s)\nsrcname=(%s)\ncopymode=%d\natt=(%s)\n",fname,srcname,copymode,attachment);
#endif

  /* Read message header from FILE1 */

  readmsghdr(fname,&msg);


  /* Is it an email or club message? */

  email=(msg.club[0]==0);


  /* Deal with auto-forwarded messages */

  if(email)checkautofw(&msg);


  /* Print nice debugging info. Maybe. */

#ifdef DEBUG
  printf("Club:    (%s)\n",msg.club);
  printf("From:    (%s)\n",msg.from);
  printf("To:      (%s)\n",msg.to);
  printf("Subject: (%s)\n",msg.subject);
  printf("History: (%s)\n",msg.history);
  printf("Fatt:    (%s)\n",msg.fatt);
  printf("Msgno:   (%ld)\n",msg.msgno);
  printf("flags:   (%lx)\n",msg.flags);
  printf("\n");
#endif


  /* Get new message number */

  if(email)getemsgnum(&msg);
  else getcmsgnum(&msg);


  /* Prepare the message header */

  preparemsghdr(&msg,email);


  /* Add the message index to the Typhoon database */

  addtodb(&msg,email);


  /* Write the message header and body */

  writemessage(srcname,&msg,email);
  memcpy(&msg0,&msg,sizeof(struct message));


  /* Add club messages to the IHAVE list */

  if(!email)addihave(&msg);


  /* Copy the optional file attachment */

  copyatt(copymode,&msg,email,attachment);


  /* Check for network mail */

  checknetmail(&msg,srcname);


  /* Write final message header back to source file */

  writemsghdr(fname,&msg);
}


