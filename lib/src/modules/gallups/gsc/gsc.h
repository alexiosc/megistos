/*****************************************************************************\
 **                                                                         **
 **  FILE:      gsc.h                                                       **
 **  AUTHORS:   Antonis Stamboulis (Xplosion), Vangelis Rokas (Valis)       **
 **  PURPOSE:   Gallups Script Compiler                                     **
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
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 1.2  2000/09/27 18:35:06  bbs
 * various changes (nothing serious)
 *
 * Revision 1.1  2000/09/21 18:15:54  bbs
 * the universal gallup script compiler
 * support for GNU C and Borland C
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif

#ifndef __GSC_H
#define __GSC_H


#define DEBUG

#ifdef __BORLANDC__
#  ifdef DEBUG
#    define debug	printf
#  else
#    define debug	if(0)printf
#  endif
#else	/* !__BORLANDC__ */
#  ifdef DEBUG
#    define debug(f...)	if(gscflags&VERBOSE)printf(##f)
#  else
#    define debug(f...)
#  endif
#endif	/* !__BORLANDC__ */

#define SYNTAX		0x01
#define INFO		0x02
#define VERBOSE		0x04
#define QUIET		0x08
#define ANALYZE		0x80

extern struct gallup gallupsinfo;
extern char filename[128];
extern char outname[128];

extern void analyze(char *);

#endif

