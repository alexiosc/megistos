/*****************************************************************************\
 **                                                                         **
 **  FILE:     news.h                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 95, Version 1.0                                      **
 **  PURPOSE:  Structures and defines used in the news module.              **
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
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1997/11/06 20:13:48  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 11:02:32  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define NEWSFNAME NEWSDIR"/blt-%03d"
#define NEWSHDR   NEWSDIR"/hdr-%03d"


struct newsbulletin {
	int     date;
	int     time;
	int     numdays;
	int     priority;
	int     enabled;
	char    class[12];
	int     key;
	int     info;
	int     num;
	char    dummy[256 - 44];
};






/* End of File */
