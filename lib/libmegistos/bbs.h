/** @name     bbs.h
    @memo     The Mother of All BBS Include Files.
    @author   Alexios

    @doc

    This is a wildcard header file that includes {\em all} of the other header
    files. This is the strongly recommended way to include BBS header files in
    your code.

    Original banner, legalese and change history follow

{\small
\begin{verbatim}

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
 * Revision 1.2  2001/04/16 21:56:28  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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

\end{verbatim}
} */

/*@{*/

#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef BBS_H
#define BBS_H

#include <bbsinclude.h>

#include "config.h"
#include "errors.h"
#include "prompts.h"
#include "useracc.h"
#include "miscfx.h"
#include "bbsmod.h"
#include "input.h"
#include "format.h"
#include "output.h"
#include "sysstruct.h"
#include "timedate.h"
#include "globalcmd.h"
#include "ttynum.h"
#include "lock.h"
#include "audit.h"
#include "filexfer.h"
#include "mail.h"
#include "security.h"
#include "channels.h"
#include "dialog.h"


#endif /* BBS_H */

/*@}*/

/*
LocalWords: bbs Alexios doc wildcard em legalese alexios Exp GPL ifndef
LocalWords: VER endif bbsinclude config useracc miscfx bbsmod sysstruct
LocalWords: timedate globalcmd ttynum filexfer */
