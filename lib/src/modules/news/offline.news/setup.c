/*****************************************************************************\
 **                                                                         **
 **  FILE:     setup.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  News plugin setup part (not much of it)                      **
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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:46:06  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
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
const char *__RCS=RCS_VER;
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


struct prefs prefs;


void readprefs(struct prefs *prefs)
{
  if(loadprefs(progname,prefs)!=1){
    bzero(prefs,sizeof(struct prefs));
    prefs->flags=defnews?ONF_YES:0;
    writeprefs(prefs);
  }
}


void writeprefs(struct prefs *prefs)
{
  saveprefs(progname,sizeof(struct prefs),prefs);
}


void
setup()
{
  readprefs(&prefs);

  sprintf(inp_buffer,"%s\nOK\nCANCEL\n",prefs.flags&ONF_YES?"on":"off");

  if(dialog_run("offline.news",ONVT,ONLT,inp_buffer,MAXINPLEN)!=0){
    error_log("Unable to run data entry subsystem");
    return;
  }

  dialog_parse(inp_buffer);

  if(sameas(margv[3],"OK")||sameas(margv[3],margv[1])){
    if(sameas("on",margv[0]))prefs.flags|=ONF_YES;
    else prefs.flags&=~ONF_YES;

    saveprefs(progname,sizeof(prefs),&prefs);
  }
}
