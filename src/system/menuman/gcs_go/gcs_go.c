/*****************************************************************************\
 **                                                                         **
 **  FILE:     gcs_go.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  The global /go command                                       **
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
 * $Id: gcs_go.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: gcs_go.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/22 17:23:36  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


static const char rcsinfo[] = "$Id: gcs_go.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";


#include <bbsinclude.h>
#include <bbs.h>
#include <mbk_sysvar.h>


/** The entry point to this global command handler */

int
__INIT_GCS__ ()
{
	if (margc == 2 && sameas (margv[0], "/go")) {
		gopage (margv[1]);
		return 1;
	}
	return 0;
}


/* End of File */
