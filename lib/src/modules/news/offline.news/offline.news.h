/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.news.h                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  News plugin definitions and stuff.                           **
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
 * Revision 0.3  1998/08/14 11:42:12  alexios
 * Moved to the stable status.
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


#include "typhoon.h"
#include "../offline.mail/request.h"


/* offline.news.c */

extern promptblk *msg;
extern promptblk *news_msg;

extern int  onkey;
extern int  defnews;
extern char *newsfile;

extern int sopkey;

extern char *progname;


/* setup.c */

struct prefs {
  int flags;

  char dummy[60];
};


struct prefs prefs;


#define ONF_YES    0x0001


void readprefs(struct prefs *prefs);

void writeprefs(struct prefs *prefs);

void setup();


/* download.c */

int ondownload();


/* setup.c */

void setup();

