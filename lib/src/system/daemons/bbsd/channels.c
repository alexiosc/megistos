/*****************************************************************************\
 **                                                                         **
 **  FILE:     channels.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997                                               **
 **  PURPOSE:  Channel related functions                                    **
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
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 16:21:05  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/26 21:11:32  alexios
 * No changes.
 *
 * Revision 0.2  1997/11/06 20:04:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/30 13:10:43  alexios
 * Initial revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif


#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_SIGNAL_H 1
#define WANT_PWD_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIO_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"
#include "bbsd.h"


struct getty   *gettys=NULL;


void
readchannels()
{
  int i;
  mod_init(INI_TTYNUM);
  if(gettys)free(gettys);
  gettys=malloc(sizeof(struct getty)*chan_count);
  bzero(gettys,sizeof(struct getty)*chan_count);
  for(i=0;i<chan_count;i++){
    gettys[i].channel=channels[i].channel;
    strcpy(gettys[i].ttyname,channels[i].ttyname);
    bzero(gettys[i].user,sizeof(gettys[i].user));
    gettys[i].flags=channels[i].flags;
    gettys[i].pid=gettys[i].disabled=0;
    gettys[i].shmid=-1;
  }
}
