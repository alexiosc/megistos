/*! @file     bbs.h
    @brief    The Mother of All BBS Include Files.
    @author   Alexios

    This is a wildcard header file that includes <em>all</em> of the other header
    files. This is the strongly recommended way to include BBS header files in
    your code.

    Original banner, legalese and change history follow

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     bbs.h                                                        **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  #include all useful header files and just that!              **
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
 *****************************************************************************


 *
 * $Id$
 *
 * $Log$
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2003/12/19 13:23:29  alexios
 * Updated include directives; updated some of the directory #defines.
 *
 * Revision 1.5  2003/09/28 22:27:04  alexios
 * Added gettext.h inclusion.
 *
 * Revision 1.4  2003/09/27 20:27:45  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/12/27 15:19:19  alexios
 * Now includes the new header files (channels.h and security.h).
 *
 * Revision 0.2  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 *

@endverbatim
*/

/*@{*/


#ifndef BBS_H
#define BBS_H

#include <bbsinclude.h>

#include <megistos/gettext.h>

#include <megistos/config.h>
#include <megistos/errors.h>
#include <megistos/prompts.h>
#include <megistos/useracc.h>
#include <megistos/miscfx.h>
#include <megistos/bbsmod.h>
#include <megistos/input.h>
#include <megistos/format.h>
#include <megistos/output.h>
#include <megistos/sysstruct.h>
#include <megistos/timedate.h>
#include <megistos/globalcmd.h>
#include <megistos/ttynum.h>
#include <megistos/lock.h>
#include <megistos/audit.h>
#include <megistos/filexfer.h>
#include <megistos/mail.h>
#include <megistos/security.h>
#include <megistos/channels.h>
#include <megistos/dialog.h>
#include <megistos/bots.h>


#endif /* BBS_H */

/*@}*/

/*
LocalWords: bbs Alexios doc wildcard em legalese alexios Exp GPL ifndef
LocalWords: VER endif bbsinclude config useracc miscfx bbsmod sysstruct
LocalWords: timedate globalcmd ttynum filexfer */
