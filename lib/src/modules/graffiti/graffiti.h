/*****************************************************************************\
 **                                                                         **
 **  FILE:     graffiti.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 0.5 alpha                              **
 **  PURPOSE:  Graffiti Wall definitions                                    **
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
 * Revision 1.2  1998/07/24 10:19:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:11:34  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 10:42:25  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WALLFILE BBSDATADIR"/graffiti/graffiti.wall"
#define WALLLOCK "LCK.graffiti"


struct wallmsg {
  char userid[24];
  char message[256];
};


#ifndef NOCOLORS
char *colors[11]={
  "\033[1;31m", "\033[1;32m", "\033[1;33m", "\033[1;35m", "\033[1;36m", 
  "\033[1;37m"
};

#define MAXCOLOR 6

#endif /* NOCOLORS */
