/*****************************************************************************\
 **                                                                         **
 **  FILE:     exit.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 95, Version 0.5 alpha                                 **
 **  PURPOSE:  The Visual Editor exit functions                             **
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
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/08/13 17:10:05  alexios
 * Fixed things so that user inactivity timers are reset to handle
 * slightly borken (sic) telnet line timeouts. This is useless but
 * harmless, since emud handles these timeouts.
 *
 * Revision 0.7  1998/12/27 16:35:48  alexios
 * Added autoconf support.
 *
 * Revision 0.6  1998/08/14 12:01:28  alexios
 * No changes.
 *
 * Revision 0.5  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 10:50:43  alexios
 * Stopped using xlgetmsg() and reverted to getmst() since emud
 * now performs all translations itself.
 *
 * Revision 0.3  1997/09/12 13:41:18  alexios
 * Used translated message blocks instead of raw ones. Other
 * minor fixes.
 *
 * Revision 0.2  1997/08/31 09:23:15  alexios
 * Removed calls to the visual library, replaced them with ncurses
 * calls.
 *
 * Revision 0.1  1997/08/28 11:26:56  alexios
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
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "vised.h"
#include "mbk_vised.h"


int
doquit()
{
  int c;
  char s[2],t[2];

  move(LINES-2,0);
  printansi(msg_get(QUIT));
  refresh();

  while((c=mygetch())==ERR)usleep(20000);
  
  s[0]=c;
  s[1]=0;
  strcpy(t,latinize(s));
  c=toupper(t[0]);
  return(c=='Y');
}


void
golined()
{
  char n[16];
  savefile();
  sprintf(n,"%d",maxsize);
  out_setflags(OFL_AFTERINPUT);
  prompt(CLRSCR);
  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
  execl(mkfname(LINEDBIN),"lined",filename,n,NULL);
  clearok(stdscr,TRUE);
  showstatus();
  showtext(0);
}
