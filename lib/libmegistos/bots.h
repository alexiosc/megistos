/** @file    bots.h
    @brief    Support for (ro)bots, AIs, artificial users and scripts
    @author  Alexios

    @doc

    This header file provides functionality used in interfacing with non-human
    users of the system. Many a task can be automated this way, and things like
    networked clubs use this facility to exchange messages with other systems.

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     bots.h                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Bot support                                                  **
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
 * Revision 1.2  2003/09/27 20:29:41  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.1  2001/04/22 15:20:51  alexios
 * Initial checkin.
 *

@endverbatim
*/

/*@{*/

#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef BOTS_H
#define BOTS_H



/** @name Three-digit state codes
    @filename BTS_flags

    @memo Three digit codes denoting state, errors and other messages.

    @doc Just like FTP and similar protocols, the bot API issues these
    three-digit numbers to notify the bot of the current state of affairs. The
    hundreds digit denotes the message type (information, error, etc); the other
    two digits uniquely identify the message type.

*/
/*@{*/

#define BTS_PROMPT_STARTS   601	/**< Beginning of a prompt */
#define BTS_PROMPT_ARGUMENT 602	/**< A prompt argument (%s etc) follows */
#define BTS_PROMPT_TEXT     603 /**< Human-readable prompt follows */
#define BTS_PROMPT_ENDS     609 /**< End of prompt */

#define BTS_FILE_STARTS     610 /**< Beginning of a long file display */
#define BTS_FILE_ENDS       619 /**< End of a long file display */

#define BTS_INJECTED_PROMPT 630 /**< Message from other user follows */

#define BTS_INPUT_EXPECTED  650 /**< Input expected now */

/*@}*/



/** Escape a string before it's sent to a bot
    
    @doc Bots depend on rigidly defined return codes. However, since return
    codes consist of easily used ASCII characters, it's necessary to escape
    arbitrary user-provided strings. Any character sequences that look like
    <tt>new-line digit digit digit space</tt> are escaped by changing the
    newline to an <tt>ESC</tt> (ASCII 27). You can use bot_unescape() to reverse
    this.

    @param s The string to escape. The string itself is modified, not a copy
    thereof.

    @return The escaped string. You can either call the function for its side
    effect, it's return value, or both, just like <tt>strcpy()</tt>.

    @see bot_unescape().  */

char *bot_escape (char *s);


/** Unescape a string after it's been received by a bot
    
    @doc Bots depend on rigidly defined return codes. However, since return
    codes consist of easily used ASCII characters, it's necessary to escape
    arbitrary user-provided strings. This function reverses this process,
    yielding the original, unescaped string. It's meant to be used by bots that
    have received a prompt string from the system.

    @param s The string to unescape. The string itself is modified, not a copy
    thereof.

    @return The original string. You can either call the function for its side
    effect, it's return value, or both, just like <tt>strcpy()</tt>.

    @see bot_escape().  */

char *bot_unescape (char *s);




#endif /* BOTS_H */


/*@}*/

/*

LocalWords: Alexios doc Megistos BBS API legalese alexios Exp bots ro AIs Bot 
LocalWords:  otnotesize ifndef VER endif BTS bot tt unescape param strcpy
LocalWords:  unescaped

*/
