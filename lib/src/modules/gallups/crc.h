/*****************************************************************************\
 **                                                                         **
 **  FILE:      crc.h                                                       **
 **  AUTHORS:   Vangelis Rokas (Valis)                                      **
 **  PURPOSE:   CRC32 checkcum computing function                           **
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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  2000/09/27 18:24:02  bbs
 * Initial revision
 *
 *
 */

#ifndef RCS_VER
#define RCS_VER	"$Id$"
#endif

#ifndef __CRC_H
#define __CRC_H


/* Calculate the CRC32 check sum of buffer */
extern unsigned long int cksum (char *buffer, unsigned long int size);

#endif
