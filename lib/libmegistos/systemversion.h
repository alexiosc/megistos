/*****************************************************************************\
 **                                                                         **
 **  FILE:     systemversion.h                                              **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Declare the version of the system                            **
 **  NOTES:    Proud to say this file has been thoroughly debugged to the   **
 **            point where even Murphy's Law on Bugs does not apply to it.  **
 **            Now, if only we can find an interesting name to give to the  **
 **            damn thing...                                                **
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
 * Revision 1.1  2001/04/16 14:48:56  alexios
 * Initial revision
 *
 * Revision 0.4  1998/07/26 21:17:06  alexios
 * Made version more complete and OS-like.
 *
 * Revision 0.3  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/03 00:29:40  alexios
 * Changed the version to 0.5a, obviously.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#include "ver.h"


#ifndef SYSTEMVERSION
#define SHORTVERSION  "Megistos "__MAJORVERSION"."__MINORVERSION
#define SYSTEMVERSION SHORTVERSION" ("__COMPILED_BY") #"__MAKE_NUMBER" "__DATE
#endif /* SYSTEMVERSION */
