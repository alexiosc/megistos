/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubs.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Dealing with club stuff (selecting, listing etc)             **
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
 * Revision 1.1  2001/04/16 14:54:53  alexios
 * Initial revision
 *
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
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
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"

#undef ENTRYKEY
#undef SOPKEY
#undef ERRSEL
#undef NOAXES
#undef ABOUT
#undef SCASK
#undef SCERR

#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


char club[16];


void
selectclub()
{
  if(!getclub(club,SCASK,SCERR,0,"."))return;
  if(sameas(club,"."))club[0]=0;
}


static int
hdrselect(const struct dirent *d)
{
  return d->d_name[0]=='h';
}


void
listclubs()
{
  struct dirent **clubs;
  int n,i;
  
  setmbk(clubmsg);
  n=scandir(CLUBHDRDIR,&clubs,hdrselect,alphasort);
  prompt(LCHDR);
  for(i=0;i<n;free(clubs[i]),i++){
    char *cp=&clubs[i]->d_name[1];
    if(!loadclubhdr(cp))continue;
    if(lastresult==PAUSE_QUIT)break;
    if(getclubax(&thisuseracc,cp)==CAX_ZERO)continue;
    prompt(LCTAB,clubhdr.club,clubhdr.clubop,clubhdr.descr);
  }
  free(clubs);
  if(lastresult==PAUSE_QUIT){
    setmbk(msg);
    return;
  }
  prompt(LCFTR);
  setmbk(msg);
}
