/*****************************************************************************\
 **                                                                         **
 **  FILE:     gcs_go.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  The global /go command                                       **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 15:00:52  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:13:53  alexios
 * Initial checkin.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif


#include <bbsinclude.h>
#include <bbs.h>
#include <mbk_sysvar.h>


/** The entry point to this global command handler */

int
__INIT_GCS__()
{
  if(margc==2 && sameas(margv[0],"/go")){
    gopage(margv[1]);
    return 1;
  }
  return 0;
}
