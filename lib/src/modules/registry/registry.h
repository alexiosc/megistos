/*****************************************************************************\
 **                                                                         **
 **  FILE:     registry.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 94, version 1.0                                  **
 **  PURPOSE:  Provide an interface to the registry module.                 **
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
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/07/26 21:17:06  alexios
 * Took full advantage of the 1k of registry data. Made registry
 * more MBBS(R) compatible.
 *
 * Revision 0.2  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




#ifndef REGISTRY_H
#define REGISTRY_H

#define SUMSIZE 40
#define REGSIZE 980


struct registry {
	int     template;
	char    summary[SUMSIZE];
	char    registry[REGSIZE];

	/*char spare    [REGISTRYSIZE-1024]; */
};


#endif				/* REGISTRY_H */


/* End of File */
