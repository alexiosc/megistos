/*****************************************************************************\
 **                                                                         **
 **  FILE:     mansied.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 95, Version 0.1                                      **
 **  PURPOSE:  Header file for the ANSI editor                              **
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
 * Revision 1.1  2001/04/16 14:48:40  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:21  alexios
 * Initial checkin.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




struct line{
  int         text[1024];
  struct line *next;
};

extern int         numlines;
extern int         topx, topy;
extern struct line *line;


/* display.c */

void showstatus();
