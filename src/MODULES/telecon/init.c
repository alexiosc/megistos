/*****************************************************************************\
 **                                                                         **
 **  FILE:     init.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **            B, August 96, Version 0.6                                    **
 **  PURPOSE:  Teleconferences, Initialise teleconferences/plugins          **
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
 * Revision 1.1  2001/04/16 14:58:24  alexios
 * Initial revision
 *
 * Revision 0.3  1998/12/27 16:10:27  alexios
 * Added autoconf support. One slight bug fix.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
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
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "telecon.h"
#include "mbk_telecon.h"


promptblk *msg;

int  entrkey;
int  normkey;
int  npaymx;
int  maxcht;
int  lnvcht1;
int  lnvcht2;
int  lnvcht3;
int  tinpsz;
int  msgkey;
int  amsgch;
int  msgchg;
char *maintopic;
int  defcol;
int  sopkey;
int  chtkey;
int  ichtkey;
int  defint;
int  chatcol1;
int  chatcol2;
char *stgall1;
char *stgall2;
char *stgsec1;
char *stgsec2;
int  actkey;
int  defact;


void
init()
{
  initmodule(INITALL);

  msg=opnmsg("telecon");
  setlanguage(thisuseracc.language);

  entrkey=numopt(ENTRKEY,0,129);
  normkey=numopt(NORMKEY,0,129);
  npaymx=numopt(NPAYMX,-1,32767);
  maxcht=numopt(MAXCHT,0,32767);
  tinpsz=numopt(TINPSZ,1,2047);
  msgkey=numopt(MSGKEY,0,129);
  actkey=numopt(ACTKEY,0,129);
  amsgch=ynopt(AMSGCH);
  msgchg=numopt(MSGCHG,-32767,32767);
  defcol=tokopt(DEFCOL,"DARKBLUE","DARKGREEN","DARKCYAN","DARKRED",
		"DARKMAGENTA","BROWN","GREY","DARKGREY","BLUE","GREEN",
		"CYAN","RED","MAGENTA","YELLOW","WHITE");
  sopkey=numopt(SOPKEY,0,129);
  chtkey=numopt(CHTKEY,0,129);
  ichtkey=numopt(ICHTKEY,0,129);
  defint=numopt(DEFINT,0,999);
  defact=ynopt(DEFACT);
  chatcol1=tokopt(CHATCOL1,"DARKBLUE","DARKGREEN","DARKCYAN","DARKRED",
		"DARKMAGENTA","BROWN","GREY","DARKGREY","BLUE","GREEN",
		"CYAN","RED","MAGENTA","YELLOW","WHITE");
  chatcol2=tokopt(CHATCOL2,"DARKBLUE","DARKGREEN","DARKCYAN","DARKRED",
		"DARKMAGENTA","BROWN","GREY","DARKGREY","BLUE","GREEN",
		"CYAN","RED","MAGENTA","YELLOW","WHITE");
  stgall1=strdup(getmsg(STGALL1));
  stgall2=strdup(getmsg(STGALL2));
  stgsec1=strdup(getmsg(STGSEC1));
  stgsec2=strdup(getmsg(STGSEC2));

  signal(SIGMAIN,actionhandler);
}
