/*! @file    format.h
    @brief   Low-level text formatting and output.
    @author  Alexios

    This module provides low-level access to the formatter engine. You
    really shouldn't use anything in here, unless you know what you're
    doing. It's far better to use the higher-level functions provided elsewhere
    and to leave the low level formatting chores to the library.

    Original banner, legalese and change history follow.

    @par
    @verbatim

 ***************************************************************************** 
 **                                                                         **
 **  FILE:     format.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Low level text formatting and output routines                **
 **  NOTES:    Interface to format.c                                        **
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
 * Revision 1.4  2003/09/27 20:30:51  alexios
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

#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#ifndef FORMAT_H
#define FORMAT_H


/** @defgroup format Formatting Text

    This module provides low-level access to the formatter engine. You
    really shouldn't use anything in here, unless you know what you're
    doing. It's far better to use the higher-level functions provided elsewhere
    and to leave the low level formatting chores to the library.

    This part of the documentation also includes an explanation of the various
    <em>ad hoc</em> escape sequences used for formatting purposes.


    \section format_directives Formatting Directives

    Megistos includes a reasonably sophisticated formatting system, inspired by
    the really basic one included in the Major BBS. Major offered a pretty
    useful line wrapping feature, which came in handy for the built-in (line)
    editor, among other things. It was only applied to the user's input,
    though. Megistos applies it to the output, where it's most useful. It
    supports setting left and right margins, paragraph indentations, left and
    right alignment, centering, and full justification (my favourite).

    This takes full advantage of any user's terminal. I'm pretty sensitive to
    this type of need, because I've always had larger than normal text
    resolutions (things like 132 by 30, even on the poor little 286 I had in
    1991). Major couldn't take advantage of them, and it always annoyed me. I
    suppose it annoyed me enough to make this beast!

    Right, then. Formatting directives are escape sequences, just like most
    terminal directives (also known as `ANSI' in the BBS world, to refer to a
    minute subset of the ANSI X3.64 Standard for Control Sequences for Video
    Terminals and Peripherals).

    All formatting directives start with the sequence `<tt>ESC !</tt>', or ASCII
    codes <tt>27 33</tt> (in decimal). A character identifying the directive
    follows. Many directives take an optional argument, a base ten integer.

    In default of any formatting directives, characters are printed in the
    normal way, left-aligned, without any word wrapping, justification or any
    margin or indentation adjustments. If your prompts are 80 columns wide and a
    user has a 64 column screen, they'll get ugly wrap-around effects.

    Here are the specific commands. Spaces have been inserted between command
    elements. This was done for clarity. <em>No spaces</em> are actually used
    within the directives.

    <ul>

    <li><tt>ESC ! L</tt>. Start formatting text. The current and subsequent lines
      will be rendered left-aligned. This is the default.

    <li><tt>ESC ! R</tt>. Start formatting text. Current and subsequent lines will
      be rendered right-aligned.

    <li><tt>ESC ! C</tt>. Start formatting text. Current and subsequent lines will
      be centred.

    <li><tt>ESC ! W</tt>. Start formatting text. Current and subsequent lines will
      be rendered in wrap-around mode. This mode allows you to format
      ragged-edge text so that words are not split in two lines. There is, of
      course, no hyphenation!

    <li><tt>ESC ! J</tt>. Start formatting text. Current and subsequent lines will
      be justified. This mode one produces professional-looking straight-edge
      text from left to right border.

    <li><tt>ESC ! l</tt>. (lower case `L') Place left margin. If preceded by an
      optional decimal argument (<tt>ESC ! arg l</tt>), this sets the left
      margin to as many characters as the argument (zero denotes the physical
      left margin of the screen):

      @verbatim
|<--------- physical line length -------->|
|<-- arg -->|Left Margin                  |
      @endverbatim

      If the argument is not specified, this directive sets the left margin to
      the current cursor position.

    <li><tt>ESC ! i</tt>. Works just like 'l', but sets the left margin on {\em
      subsequent} lines, whereas `l' affects the current line too. This is
      useful for paragraphs where the first line is indented, or for lists,
      where subsequent lines are indented.

    <li><tt>ESC ! r</tt>. Place right margin. If the optional decimal argument
      is specified immediately before the `<tt>r</tt>', this sets the right
      margin to the specified number of characters (zero denotes the physical
      right margin of the screen):
                            
      @verbatim
|<------- physical line length -------->|
|               Right Margin|<-- arg -->|
      @endverbatim

      If not preceded by a number, this command sets the right margin to the
      current cursor position.

    <li><tt>ESC ! F</tt>. With the optional integer argument, this directive
      repeats the char following it as many times as specified by the
      argument. That is, <tt>ESC!10F-</tt> will render as
      `<tt>----------</tt>'. If not preceded by a number, the character
      following the `F' is repeated all the way to the right margin.

    <li><tt>ESC ! (</tt>. (open parenthesis) Begin formatting using the last
      formatting mode specified.  This begins formatting, starts taking into
      account margins, etc. When wrapping/justifying, use this to begin a new
      paragraph. Specify the mode (left, right, centre or justify) for the first
      paragraph, and use this directive for subsequent ones. This way, if you
      later change your mind, you only need to change the first paragraph, not
      all of them. To end a paragraph, you need the following command:

    <li><tt>ESC ! )</tt>. (closed parenthesis) Stop formatting. All subsequent
      output will be dumped to the output stream as-is, until another format
      command is encountered. Stops using set margins, etc. When
      wrapping/justifying, use this to end a paragraph so that newline
      characters are not transformed into horizontal spacing.
                                                                          
    <li><tt>ESC ! Z</tt>. Zero the horizontal position counter. Start formatting
      from this position. Can cause really nasty formatting problems unless you
      know what you're doing. We like to allow you to shoot your foot.
                                                                          
    <li><tt>ESC ! v</tt>. Controls the expansion of substitution variables (<tt>
      @@VAR@@</tt>-style embedded vars). This directive <em>requires</em> an
      argument. A value of 0 inhibits variable expansion, allowing normal use of
      the at-sign `<tt>@@</tt>' symbol. Use this in places where the user is
      likely to use this symbol, e.g.  pages, reading mail, etc. Non-zero values
      enable variable expansion, giving the at-sign its special meaning. You'll
      have to use `<tt>@@@@</tt>' (two at-signs) to get `<tt>@@</tt>', et
      cetera. The default is full variable expansion.
                                                                          
    <li><tt>ESC ! P</tt>. Causes a forced pause at the current point. Waits for
      the user to press any key, then continues printing. Use this sparingly,
      because it tends to annoy users.

    </ul>

 @{*/



/** @defgroup PAUSE_flags Paging result codes (PAUSE_x)

    @memo Results codes from the last paging pause.

    @doc These provide information on what user's request at the last paging
    pause (the Nonstop/Quit/Continue/Step message you get when a message won't
    fit the screen).

    Of these constants, the most important one is #PAUSE_QUIT. You should test
    this when printing large lists or tables with loops. The output library will
    interrupt the message currently printed when the user hits `Q', but there is
    no way for the library to know what @e you are doing. Use something like
    this:

    @verbatim
while (some_condition) {

	. . .

	print (SOME_LIST_FORMAT, . . . );

	. . .
	 
	if (mt_lastresult == PAUSE_QUIT) {
		prompt (LISTCANCEL);
		break;	
	}
}
    @endverbatim

    Otherwise, the user will be able to interrupt individual messages from being
    printed, but not your entire listing or tabulation loop. It is a good
    convention to print something like `this listing was aborted' (prompt @c
    LISTCANCEL in this case) after doing this so that users will later know the
    entire list has not been shown.

    Anyway, here are the defined values:

    - #PAUSE_NONSTOP. The user selected non-stop operation. No further paging
      breaks will be issued until the next request for user input.

    - #PAUSE_QUIT. The user interrupted the list. If you are currently printing
      a list, table, or generally issuing many messages in a loop, you should
      break out of the loop, notify the user of the interruption and return the
      user to the previous menu.

    - #PAUSE_CONTINUE. The simply requested a continuation of the list.

    You'll notice that there is no result code for the `Step' command. This is
    because stepping is handled within the formatter, not the pager.

    @see fmt_lastresult.
*/
/*@{*/

#define PAUSE_NONSTOP   1 /**< The user opted for a non-stop listing. */
#define PAUSE_QUIT      2 /**< The user quit a listing. */
#define PAUSE_CONTINUE  3 /**< The user continued a paged listing. */

/*@}*/



/** The last paging result.

    Test this variable against one of the <tt>PAUSE_x</tt> results codes to see
    what the user did at the last page break. Please see the documentation of
    the <tt>PAUSE_x</tt> codes for more information.
*/

extern int fmt_lastresult;


/** The current screen height in rows. */

extern int fmt_screenheight;


extern int fmt_verticalformat;


/** Change the pager prompt.

    This function changes the `Nonstop/Quit/Continue/Step' message to a user
    supplied value. This is executed internally to set the value read from the
    system customisation block. You should not need to use it yourself.

    @param pausetext the new pause text. */

void fmt_setpausetext (char *pausetext);


/** Low level output function.

    This function does the actual formatting and printing of prompts, messages
    and what not. It should not be used because of its low level. If you need
    to print a prompt, put it in a prompt block and use <tt>prompt()</tt>. If you
    need to print a string, use the <tt>print()</tt> function, which is nice and
    <tt>printf()</tt>-like.

    @param s a string to print. The string may contain special formatting
    directives which are processed and output.
*/

void fmt_output(char *s);


/** Set the length of a line.

    This function alters the formatter's idea of what the length of a line
    is. This is the same as the number of columns (80, for instance). You
    should not use this function in user programs. It is only used by the
    initialisation code to set the line length to match the one preferred by
    the user.

    @param i the new length of the line.  */

void fmt_setlinelen(int i);


/** Enable or disable formatting.

    You can use this function to enable or disable automatic formatting of
    text. As with most functions in <tt>format.h</tt>, you should not use this
    unless you know what you're doing. The BBS library uses this function to
    temporarily inhibit formatting in order to print certain things (like the
    verbatim contents of a file).

    Calling this function resets ::fmt_lastresult to 0.

    @param i the new state of the formatting engine. A value of zero disables
    formatting. Non-zero values enable it.  */

void fmt_setformatting (int i);


/** Set paging mode.

    This function controls screen paging. You shouldn't turn screen paging off,
    unless you really know what you're doing. Turning off the pager results in
    no pauses for long messages or lists. This implies that users won't
    (normally) be able to stop any lists once they have started displaying.

    @param i the new state of the pager. A value of zero disables screen
    paging. Non-zero values enable it.  */

void fmt_setverticalformat (int i);


/** Set screen height.

    This function changes the perceived height of the screen. This is the same
    as the number of rows, typically 25 on a terminal without status
    lines. This function is mostly used internally to set the formatter to what
    the user prefers as their screen height.

    @param i the new screen height in rows. */

void fmt_setscreenheight(int i);


/** Invokes the screen pager.

    This function causes the screen pager to issue the
    Nonstop/Quit/Continue/Step message, if that is necessary. You should not use
    this from within user modules. The function is called from within the
    formatting engine.

    @warning If you need to force a pause, use fmt_forcedpause(), not this
    function.

    @param i the new screen height in rows. */

int fmt_screenpause (void);


/** Forces a screen pause.

    This function forces a screen pause regardless of our current vertical
    position. I can think of no reason users programs should need this, but it's
    available. */

int  fmt_forcedpause(void);


/** Sets the perceived vertical position.

    This function resets the formatter's idea of where we currently are on the
    screen. You really shouldn't use this (there are formatting directives that
    provide better access to this feature).

    @param i the new vertical position. A value of zero means top-of-screen. */

void fmt_resetvpos(int i);


#endif /* FORMAT_H */


/*@}*/

/*
LocalWords: Alexios doc em legalese otnotesize alexios Exp bbs GPL ifndef
LocalWords: VER endif tt fmt lastresult LISTCANCEL int param pausetext ESC
LocalWords: setpausetext printf setlinelen setformatting setverticalformat
LocalWords: setscreenheight screenpause forcedpause resetvpos Megistos arg
LocalWords: centred vars
*/
