/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.news.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Off line mailer, news plugin                                 **
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
 * Revision 1.1  2001/04/16 14:57:54  alexios
 * Initial revision
 *
 * Revision 0.5  1998/12/27 15:53:37  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:42:12  alexios
 * Moved to the stable status.
 *
 * Revision 0.3  1998/07/24 10:21:14  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:51  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:58:05  alexios
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
#include <bbsinclude.h>

#include "bbs.h"
#include "offline.news.h"
#include "../../mailer.h"
#include "mbk_offline.news.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __NEWS_UNAMBIGUOUS__
#include "mbk_news.h"


promptblk *msg;
promptblk *news_msg;


int  onkey;
int  defnews;
char *newsfile;

int  sopkey;


char *progname;

void
init()
{
  initmodule(INITALL);

  news_msg=opnmsg("news");
  sopkey=numopt(NEWS_SOPKEY,0,129);

  msg=opnmsg("offline.news");
  onkey=numopt(ONKEY,0,129);
  defnews=ynopt(DEFNEWS);
  newsfile=stgopt(NEWSFILE);
  setlanguage(thisuseracc.language);
}


void
done()
{
  clsmsg(msg);
}


void
warn()
{
  fprintf(stderr,"This is a Mailer plugin. ");
  fprintf(stderr,"It should not be run by the user.\n");
  exit(1);
}


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  if(argc<2)warn();
  atexit(done);
  progname=argv[0];
  init();
  if(!strcmp(argv[1],"-setup"))setup();
  else if(!strcmp(argv[1],"-download"))return ondownload();
  else warn();
  done();
  return 0;
}
