/*****************************************************************************\
 **                                                                         **
 **  FILE:     gcs_cookie.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Implement the /cookie global command                         **
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
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#include <bbs.h>


/** The entry point to the global command */


/* This global command is CRAP. It must be fixed. */

int
__INIT_GCS__ ()
{
	if (margc == 1 && sameas (margv[0], "/cookie") && sysvar->glockie) {
		char    command[256];

		sprintf (command, "%s/cookie --run", mkfname (BINDIR));
		system (command);
		return 1;
	} else
		return 0;
}


/* End of File */
