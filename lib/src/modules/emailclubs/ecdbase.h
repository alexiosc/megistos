/** @name     ecdbase.h
    @memo     Header file to include email and clubs database definitions.
    @author   Alexios

    @doc

    This isn't an overly complicated header file. It simply includes the
    Typhoon definitions for the database of messages, private and public alike.

    Original banner, legalese and change history follow.

    {\small\begin{verbatim}

 *****************************************************************************
 **                                                                         **
 **  FILE:     ecdbase.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96                                                 **
 **  PURPOSE:  Typhoon RDBMS Interface for Email/Clubs                      **
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
 * Revision 0.2  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 *

\end{verbatim}
}*/

/*@{*/


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef ECDBASE_H
#define ECDBASE_H

#include "config.h"
#include "ecdb.h"


#define DATAFILE ".DATA"
#define KEYFILE0 ".KEY0"
#define KEYFILE1 ".KEY1"
#define KEYFILE2 ".KEY2"
#define KEYFILE3 ".KEY3"

#define DBDDIR MSGSDIR

#define DBDIR ".DB"


#endif /* ECDBASE_H */


/*@}*/

/*
LocalWords: ecdbase Alexios doc legalese RDBMS alexios Exp bbs GPL ifndef
LocalWords: VER endif config ecdb KEYFILE DBDDIR MSGSDIR DBDIR
*/

