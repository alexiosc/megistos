/** @name    format.h
    @memo    Low-level text formatting and output.
    @author  Alexios

    @doc

    This header file provides low-level access to the formatter engine. You
    really shouldn't use anything in here, unless you know what you're
    doing. It's far better to use the higher-level functions provided elsewhere
    and to leave the low level formatting chores to the library.

    This part of the documentation also includes an explanation of the various
    {\em ad hoc} escape sequences used for formatting purposes.

    Original banner, legalese and change history follow.

    {\footnotesize
    \begin{verbatim}

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


#ifndef FORMAT_H
#define FORMAT_H


/** @name Paging result codes
    @filename PAUSE_flags

    @memo Results codes from the last paging pause.

    @doc These provide information on what user's request at the last paging
    pause (the Nonstop/Quit/Continue/Step message you get when a message won't
    fit the screen).

    Of these constants, the most important one is {\tt PAUSE_QUIT}. You should
    test this when printing large lists or tables with loops. The output
    library will interrupt the message currently printed when the user hits
    `{\tt Q}', but there is no way for the library to know what {\em you} are
    doing. Use something like this:

    \begin{verbatim}
    if (fmt_lastresult == PAUSE_QUIT) {
        prompt (LISTCANCEL);
        break;
    }
    \end{verbatim}

    Otherwise, the user will be able to interrupt individual messages from
    being printed, but not your entire listing or tabulation loop. It is a good
    convention to print something like `this listing was aborted' (prompt {\tt
    LISTCANCEL} in this case) after doing this so that users will later know
    the entire list has not been shown.

    Anyway, here are the defined values:

    \begin{description}
    
    \item[{\tt PAUSE_NONSTOP}] The user selected non-stop operation. No further
    paging breaks will be issued until the next request for user input.

    \item[{\tt PAUSE_QUIT}] The user interrupted the list. If you are currently
    printing a list, table, or generally issuing many messages in a loop, you
    should break out of the loop, notify the user of the interruption and
    return the user to the previous menu.

    \item[{\tt PAUSE_CONTINUE}] The simply requested a continuation of the
    list.

    \end{description}

    You'll notice that there is no result code for the `Step' command. This is
    because stepping is handled within the formatter, not the pager.

    @see fmt_lastresult.  */
/*@{*/

#define PAUSE_NONSTOP   1
#define PAUSE_QUIT      2
#define PAUSE_CONTINUE  3

/*@}*/



/** The last paging result.

    Test this variable against one of the {\tt PAUSE_x} results codes to see
    what the user did at the last page break. Please see the documentation of
    the {\tt PAUSE_x} codes for more information.
*/

extern int  fmt_lastresult;


/** The current screen height in rows. */

extern int fmt_screenheight;


extern int fmt_verticalformat;


/** Change the pager prompt.

    This function changes the `Nonstop/Quit/Continue/Pause' message to a user
    supplied value.

    @param pausetext the new pause text. */

void fmt_setpausetext(char *pausetext);


/** Low level output function.

    This function does the actual formatting and printing of prompts, messages
    and what not. It should not be used because of its low level. If you need
    to print a prompt, put it in a prompt block and use {\tt prompt()}. If you
    need to print a string, use the {\tt print()} function, which is nice and
    {\tt printf()}-like.

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
    text. As with most functions in {\tt format.h}, you should not use this
    unless you know what you're doing. The BBS library uses this function to
    temporarily inhibit formatting in order to print certain things (like the
    verbatim contents of a file).

    Calling this function resets {\tt fmt_lastresult} to {\tt 0}.

    @param i the new state of the formatting engine. A value of zero disables
    formatting. Non-zero values enable it.  */

void fmt_setformatting(int i);


/** Set paging mode.

    This function controls screen paging. You shouldn't turn screen paging off,
    unless you really know what you're doing. Turning off the pager results in
    no pauses for long messages or lists. This implies that users won't
    (normally) be able to stop any lists once they have started displaying.

    @param i the new state of the pager. A value of zero disables screen
    paging. Non-zero values enable it.  */

void fmt_setverticalformat(int i);


/** Set screen height.

    This function changes the perceived height of the screen. This is the same
    as the number of rows, typically 25 on a terminal without status
    lines. This function is mostly used internally to set the formatter to what
    the user prefers as their screen height.

    @param i the new screen height in rows. */

void fmt_setscreenheight(int i);


/** Invokes the screen pager.

    This function causes the screen pager to issue the
    Nonstop/Quit/Continue/Step message, if that is necessary. You should not
    use this from within user modules. The function is called from within the
    formatting engine.

    @param i the new screen height in rows. */

int  fmt_screenpause(void);


/** Forces a screen pause.

    This function forces a screen pause regardless of our current vertical
    position. I can think of no reason users programs should need this, but
    it's available.  */

int  fmt_forcedpause(void);


/** Sets the perceived vertical position.

    This function resets the formatter's idea of where we currently are on the
    screen. You really shouldn't use this (there are formatting directives that
    provide better access to this feature).

    @param i the new vertical position. A value of zero means top-of-screen. */

void fmt_resetvpos(int i);


/** @name Formatting directives.
    @filename format_directives

    @memo {\em Ad hoc} escape sequences used for formatting purposes.

    @doc Megistos includes a reasonably sophisticated formatting system,
    inspired by the really basic one included in the Major BBS. Major offered a
    pretty useful line wrapping feature, which came in handy for the built-in
    (line) editor, among other things. It was only applied to the user's input,
    though. Megistos applies it to the output, where it's most useful. It
    supports setting left and right margins, paragraph indentations, left and
    right alignment, centering, and full justification (my favourite).

    This takes full advantage of any user's terminal. I'm pretty sensitive to
    this type of need, because I've always had larger than normal text
    resolutions (things like 132 by 30, even on my poor little 286). Major
    couldn't take advantage of them, and it always annoyed me. I suppose it
    annoyed me enough to make this beast!

    Right, then. Formatting directives are escape sequences, just like most
    terminal directives (also known as `ANSI' in the BBS world, to refer to a
    minute subset of the ANSI X3.64 Standard for Control Sequences for Video
    Terminals and Peripherals).

    All formatting directives start with the sequence `{\tt ESC !}', or ASCII
    codes {\tt 27 33} (in decimal). A character identifying the directive
    follows. Many directives take an optional argument, a base ten integer.

    In default of any formatting directives, characters are printed in the
    normal way, left-aligned, without any word wrapping, justification or any
    margin or indentation adjustments. If your prompts are 80 columns wide and
    a user has a 64 column screen, they'll get ugly wrap-around effects.

    Here are the specific commands. Spaces have been inserted between command
    elements. This was done for clarity. {\em No spaces} are actually used
    within the directives.

    \begin{description}

    \item[{\tt ESC ! L}] Start formatting text. The current and subsequent
    lines will be rendered left-aligned. This is the default.

    \item[{\tt ESC ! R}] Start formatting text. Current and subsequent lines
    will be rendered right-aligned.

    \item[{\tt ESC ! C}] Start formatting text. Current and subsequent lines
    will be centred.

    \item[{\tt ESC ! W}] Start formatting text. Current and subsequent lines
    will be rendered in wrap-around mode. This mode allows you to format
    ragged-edge text so that words are not split in two lines. There is, of
    course, no hyphenation!

    \item[{\tt ESC ! J}] Start formatting text. Current and subsequent lines
    will be justified. This mode one produces professional-looking
    straight-edge text from left to right border.

    \item[{\tt ESC ! l}] (lower case `L') Place left margin. If preceded by an
    argument, this sets the left margin to as many characters as the argument
    (zero denotes the physical left margin of the screen):

    \begin{verbatim}
                  |<--------- physical line length -------->|
                  |<-- arg -->|Left Margin                  |
    \end{verbatim}

    If the argument is not specified, this directive sets the left margin to
    the current cursor position.

    \item[{\tt ESC ! i}] Works just like 'l', but sets the left margin on {\em
    subsequent} lines, whereas `l' affects the current line too. This is useful
    for paragraphs where the first line is indented, or for lists, where
    subsequent lines are indented.

    \item[{\tt ESC ! r}] Place right margin. If the optional argument is
    specified immediately before the `{\tt r}', this sets the right margin to
    the specified number of characters (zero denotes the physical right margin
    of the screen):
                            
    \begin{verbatim}
                  |<------- physical line length -------->|
                  |               Right Margin|<-- arg -->|
    \end{verbatim}

    If not preceded by a number, this command sets the right margin to the
    current cursor position.

    \item[{\tt ESC ! F}] With the optional integer argument, this directive
    repeats the char following it as many times as specified by the
    argument. That is, {\tt ESC!10F-} will render as `{\tt ----------}'. If not
    preceded by a number, the character following the `F' is repeated all the
    way the right margin.

    \item[{\tt ESC ! (}] (open parenthesis) Begin formatting using the last
    formatting mode specified.  This begins formatting, starts taking into
    account margins, etc. When wrapping/justifying, use this to begin a new
    paragraph. To end a paragraph, you need the following command:

    \item[{\tt ESC ! )}] (closed parenthesis) Stop formatting. All subsequent
    output will be dumped to the output stream as-is, until another format
    command is encountered. Stops using set margins, etc. When
    wrapping/justifying, use this to end a paragraph so that newline characters
    are not transformed into horizontal spacing.
                                                                          
    \item[{\tt ESC ! Z}] Zero the horizontal position counter. Start formatting
    from this position.
                                                                          
    \item[{\tt ESC ! v}] Controls the expansion of substitution variables ({\tt
    @VAR@}-style embedded vars). This directive {\em requires} an argument. A
    value of 0 inhibits variable expansion, allowing normal use of the at-sign
    `{\tt @}' symbol. Use this in places where the user is likely to use this
    symbol, e.g.  pages, reading mail, etc. Non-zero values enable variable
    expansion, giving the at-sign its special meaning. You'll have to use `{\tt
    @@}' to get `{\tt @}', et cetera. The default is full variable expansion.
                                                                          
    \item[{\tt ESC ! P}] Causes a forced pause at the current point. Waits for
    the user to press any key, then continues printing. Use this sparingly,
    because it tends to annoy users. 

    \end{description}
*/


#endif /* FORMAT_H */


/*@}*/

/*
LocalWords: Alexios doc em legalese otnotesize alexios Exp bbs GPL ifndef
LocalWords: VER endif tt fmt lastresult LISTCANCEL int param pausetext ESC
LocalWords: setpausetext printf setlinelen setformatting setverticalformat
LocalWords: setscreenheight screenpause forcedpause resetvpos Megistos arg
LocalWords: centred vars
*/
