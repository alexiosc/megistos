/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbslogin.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: C, March 95, Version 0.3                                     **
 **            D, July 95, Version 0.4                                      **
 **  PURPOSE:  Header file for bbslogin                                     **
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
 * Revision 1.2  2001/04/16 21:56:33  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.5  1998/03/10 10:11:26  alexios
 * Reinstating the STABLE status. What a silly mistake.
 *
 * Revision 0.4  1998/03/10 10:09:34  alexios
 * No changes.
 *
 * Revision 0.3  1997/11/06 20:15:17  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 17:03:13  alexios
 * Fixed a few minor leftover bugs and switched to the new
 * auditing scheme.
 *
 * Revision 0.1  1997/08/28 11:13:27  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




void sendmail();
