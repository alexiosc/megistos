/*****************************************************************************\
 **                                                                         **
 **  FILE:     errors.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Include file for errors.c. Provides fatal error logging.     **
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
 * Revision 1.1  2001/04/16 14:48:51  alexios
 * Initial revision
 *
 * Revision 0.5  1999/07/18 21:13:24  alexios
 * Added an #include directive to read in errno.h. Some systems
 * don't define this in other include files and we need it.
 *
 * Revision 0.4  1998/12/27 15:19:19  alexios
 * Added functions to report system errors.
 *
 * Revision 0.3  1998/07/26 21:17:06  alexios
 * Automated the process of reporting the exact position of an
 * error.
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




#ifndef ERRORS_H
#define ERRORS_H


#include <errno.h>


/* Log an error from program p, using printf format f and params p1..6 */

void _logerror(char *file, int line, char *format, ...);
void _logerrorsys(char *file, int line, int err, char *format, ...);

#define logerror(f...) _logerror(__FILE__,__LINE__,##f)

#define logerrorsys(f...) \
{\
   int i=errno; \
   _logerrorsys(__FILE__,__LINE__,i,##f);\
}


/* Same as logerr, but reports internal errors (no user notification) */

void _interror(char *file, int line, char *format, ...);
void _interrorsys(char *file, int line, int err, char *format, ...);

#define interror(f...) _interror(__FILE__,__LINE__,##f)

#define interrorsys(f...) \
{\
   int i=errno; \
   _interrorsys(__FILE__,__LINE__,i,##f);\
}


/* Log a fatal error. Like logerr, but exits the program as well */

void _fatal(char *file, int line, char *format, ...);
void _fatalsys(char *file, int line, int err, char *format, ...);

#define fatal(f...) _fatal(__FILE__,__LINE__,##f)

#define fatalsys(f...) \
{\
   int i=errno; \
   _fatalsys(__FILE__,__LINE__,i,##f);\
}


/* NO error messages dumped to the tty. Useful for gettys and things */

void noerrormessages();


/* YES error messages. To those sitting in front of a screen for too  */
/* long, like me: This was a joke guys. So there.                     */

void yeserrormessages();


#endif /* ERRORS_H */
