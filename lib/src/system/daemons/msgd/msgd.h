/*****************************************************************************\
 **                                                                         **
 **  FILE:     msgd.h                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.1                                     **
 **  PURPOSE:  The message daemon header file.                              **
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
 * Revision 0.3  1998/07/24 10:27:56  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:16:29  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:16:40  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



/* #define DEBUG 1 */


extern int  tmreidx;
extern int  tmnetml;


/* netmail.c: */

void getnetmail();


/* rfc822.c: */

void get_address_from(char *line, char *buffer);


/* reindex.c */

void doreindex();
