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
 * $Id: crc.h,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: crc.h,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/31 06:59:21  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  2000/09/27 18:24:02  bbs
 * Initial revision
 *
 *
 */

static const char rcsinfo[] =
    "$Id: crc.h,v 2.0 2004/09/13 19:44:51 alexios Exp $";

#ifndef __CRC_H
#define __CRC_H


/* Calculate the CRC32 check sum of buffer */
extern unsigned long int cksum (char *buffer, unsigned long int size);

#endif


/* End of File */


/* End of File */
