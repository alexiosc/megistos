/*! @file     errorprompts.h
    @brief     Hardwired fatal error messages.
    @author   Alexios

    @doc

    Megistos is almost completely configurable. Because there are almost no
    strings hardwired to the binaries, fatal error reporting is a tricky
    business. We solve this problem by hard-wiring two prompts into the system
    (and not by using I18N and locales): those issued to a user to notify them
    of fatal and non-fatal errors.

    The two messages here are conditionally compiled based on the GREEK
    symbol. This is just selfish, really, but we like to be able to have code
    that compiles and incorporates into our existing BBS with minimal
    hassle. This solution is <em>very</em> inelegant. I'm investigating a
    better, possibly multilingual one. It's likely we can just read these
    messages off a message prompt file at compilation time and store one set per
    supported language.

    Original banner, legalese and change history follow.

    @par
    @verbatim

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
 * $Id: errorprompts.h,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: errorprompts.h,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.7  2003/12/19 13:23:55  alexios
 * Updated include directives; updated some of the directory #defines.
 *
 * Revision 1.6  2003/09/28 22:30:20  alexios
 * Included gettext.h.
 *
 * Revision 1.5  2003/09/28 13:12:18  alexios
 * Added support for I18N to this file (indeed, this is the main reason
 * why I18N is necesary in libmegistos, as the fatal error messages are
 * the only hardwired strings in the system that the users will ever see.
 *
 * Revision 1.4  2003/09/27 20:30:08  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
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


#ifndef RCS_VER 
#define RCS_VER "$Id: errorprompts.h,v 2.0 2004/09/13 19:44:34 alexios Exp $"
#endif


#ifndef ERRORPROMPTS_H
#define ERRORPROMPTS_H


#include <megistos/gettext.h>


/* Fall back to locale-driven messages. The symbol GREEK is only kept
 * here for traditional purposes. The Greek messages are in the CP737
 * encoding and thus not very useful in this day and age. */

#if ENABLE_NLS
#  undef GREEK
#endif


/** Hard-wired, non-fatal error message.

    This message is issued whenever a non-fatal message occurs. Feel free to
    customise them at will to fit the general look and feel of your system.
*/

#ifdef GREEK
#define ERRORMESSAGE \
	"\033[0;1;31;5mè®¶©¶Æ„: \033[0;1;31m" \
	"ãû °®Â©†£¶ ©≠·¢£ò ú£ßÊõ†©ú ´û§ ¶¢¶°¢„®‡©û ´û™ ú®öò©Âò™.\n" \
	"         èò®ò°ò¢¶Á£ú ú§û£ú®È©´ú ´¶§ ïú†®†©´„ ë¨©´„£ò´¶™ ö†ò ´†™\n" \
	"         ©¨§ü„°ú™ ß¶¨ ´¶ õû£†¶Á®öû©ò§. Öû´¶Á£ú ©¨öö§È£û ö†ò ´û§\n" \
	"         ´ò¢ò†ß‡®Âò.\033[0;1m\n\n"
#else
#define ERRORMESSAGE \
	_("\033[0;1;31;5mCaution: \033[0;1;31m" \
	  "A non-fatal error has interrupted this process.\n" \
	  "         Please notify the Sysop about the conditions\n" \
	  "         that led to it. We apologise for the inconvenience." \
	  "\033[0;1m\n\n")
#endif /* GREEK */


/** Hard-wired, fatal error message.

    This message is issued whenever a fatal message occurs. These usually
    result in the running module dying there and then. Feel free to customise
    the message to fit the general look and feel of your system.  */

#ifdef GREEK
#define FATALMESSAGE \
	"\033[0;1;31;5mè®¶©¶Æ„: \033[0;1;31m" \
	"ë¶ôò®Ê ©≠·¢£ò ú£ßÊõ†©ú ´û§ ¶¢¶°¢„®‡©û ´û™ ú®öò©Âò™.\n" \
	"         èò®ò°ò¢¶Á£ú ú§û£ú®È©´ú ´¶§ ïú†®†©´„ ë¨©´„£ò´¶™ ö†ò ´†™\n" \
	"         ©¨§ü„°ú™ ß¶¨ ´¶ õû£†¶Á®öû©ò§. Öû´¶Á£ú ©¨öö§È£û ö†ò ´û§\n" \
	"         ´ò¢ò†ß‡®Âò.\033[0;1m\n\n"
#else
#define FATALMESSAGE \
	_("\033[0;1;31;5mCAUTION: \033[0;1;31m" \
	  "A fatal error has interrupted this process.\n" \
	  "         Please notify the Sysop about the conditions\n" \
	  "         that led to it. We apologise for the inconvenience." \
	  "\033[0;1m\n\n")
#endif /* GREEK */


#endif /* ERRORPROMPTS_H */

/*@}*/

/*
LocalWords: errorprompts Alexios doc Megistos BBS em legalese alexios Exp
LocalWords: bbs GPL ifndef VER endif ifdef ERRORMESSAGE mCaution Sysop
LocalWords: FATALMESSAGE mCAUTION
*/
