/*****************************************************************************\
 **                                                                         **
 **  FILE:     format.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Low level text formatting and output routines                **
 **  NOTES:    Interface to format.c                                        **
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
 * Revision 1.1  2001/04/16 14:48:51  alexios
 * Initial revision
 *
 * Revision 0.2  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef FORMAT_H
#define FORMAT_H


#define PAUSE_NONSTOP   1
#define PAUSE_QUIT      2
#define PAUSE_CONTINUE  3


extern int  verticalformat;
extern int  screenheight;
extern int  screenvpos;
extern int  lastresult;
extern char *pausetxt;


void formatoutput(char *s);

void setlinelen(int i);

void setformatting(int i);

void setverticalformat(int i);

void setscreenheight(int i);

int  screenpause(void);

int  forcedpause(void);

void resetvpos(int i);


#endif /* FORMAT_H */
