/** @name     errorprompts.h
    @memo     Hardwired fatal error messages.
    @author   Alexios

    @doc

    Megistos is almost completely configurable. Because there are almost no
    strings hardwired to the binaries, fatal error reporting is a tricky
    business. We solve this problem by hard-wiring two prompts into the system:
    those issued to a user to notify them of fatal and non-fatal errors.

    The two messages here are conditionally compiled based on the GREEK
    symbol. This is just selfish, really, but we like to be able to have code
    that compiles and incorporates into our existing BBS with minimal
    hassle. This solution is {\em very} inelegant. I'm investigating a better,
    possibly multilingual one. It's likely we can just read these messages off
    a message prompt file at compilation time and store one set per supported
    language.

    Original banner, legalese and change history follow.

    {\small\begin{verbatim}

 *****************************************************************************
 **                                                                         **
 **  FILE:     errorprompts.h                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Define hard-wired user-friendly no-nonsense no-more-hyphens  **
 **            error messages for use with errors.c                         **
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
} */

/*@{*/


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#ifndef ERRORPROMPTS_H
#define ERRORPROMPTS_H


/** Hard-wired, non-fatal error message.

    This message is issued whenever a non-fatal message occurs. Feel free to
    customise them at will to fit the general look and feel of your system.
*/

#ifdef GREEK
#define ERRORMESSAGE \
	"\033[0;1;31;5m¨¦©¦®ã: \033[0;1;31m" \
	"‹ ¡¨å© £¦ ©­á¢£˜ œ£§æ› ©œ «¤ ¦¢¦¡¢ã¨à© «ª œ¨š˜©å˜ª.\n" \
	"         ˜¨˜¡˜¢¦ç£œ œ¤£œ¨é©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª\n" \
	"         ©¬¤Ÿã¡œª §¦¬ «¦ ›£ ¦ç¨š©˜¤. …«¦ç£œ ©¬šš¤é£ š ˜ «¤\n" \
	"         «˜¢˜ §à¨å˜.\033[0;1m\n\n"
#else
#define ERRORMESSAGE \
	"\033[0;1;31;5mCaution: \033[0;1;31m" \
	"A non-fatal error has interrupted this process.\n" \
	"         Please notify the Sysop about the conditions\n" \
	"         that led to it. We apologise for the inconvenience." \
	"\033[0;1m\n\n"
#endif /* GREEK */


/** Hard-wired, fatal error message.

    This message is issued whenever a fatal message occurs. These usually
    result in the running module dying there and then. Feel free to customise
    the message to fit the general look and feel of your system.  */

#ifdef GREEK
#define FATALMESSAGE \
	"\033[0;1;31;5m¨¦©¦®ã: \033[0;1;31m" \
	"‘¦™˜¨æ ©­á¢£˜ œ£§æ› ©œ «¤ ¦¢¦¡¢ã¨à© «ª œ¨š˜©å˜ª.\n" \
	"         ˜¨˜¡˜¢¦ç£œ œ¤£œ¨é©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª\n" \
	"         ©¬¤Ÿã¡œª §¦¬ «¦ ›£ ¦ç¨š©˜¤. …«¦ç£œ ©¬šš¤é£ š ˜ «¤\n" \
	"         «˜¢˜ §à¨å˜.\033[0;1m\n\n"
#else
#define FATALMESSAGE \
	"\033[0;1;31;5mCAUTION: \033[0;1;31m" \
	"A fatal error has interrupted this process.\n" \
	"         Please notify the Sysop about the conditions\n" \
	"         that led to it. We apologise for the inconvenience." \
	"\033[0;1m\n\n"
#endif /* GREEK */


#endif /* ERRORPROMPTS_H */

/*@}*/

/*
LocalWords: errorprompts Alexios doc Megistos BBS em legalese alexios Exp
LocalWords: bbs GPL ifndef VER endif ifdef ERRORMESSAGE mCaution Sysop
LocalWords: FATALMESSAGE mCAUTION
*/
