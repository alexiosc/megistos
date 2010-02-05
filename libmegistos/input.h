/*! @file     input.h
    @brief     Low and high-level user input functions.
    @author   Alexios

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     input.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Interface to input.c                                         **
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
 * $Id: input.h,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: input.h,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/09/27 20:31:25  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/07/28 23:09:07  alexios
 * *** empty log message ***
 *
 * Revision 0.7  1999/07/18 21:13:24  alexios
 * Made inputflags public to allow for user-supplied high
 * level input functions.
 *
 * Revision 0.6  1998/12/27 15:19:19  alexios
 * Moved function declarations from miscfx.h.
 *
 * Revision 0.5  1998/08/14 11:23:21  alexios
 * Added function to set monitor ID (initially channel number,
 * but user's user ID after login).
 *
 * Revision 0.4  1998/07/26 21:17:06  alexios
 * Removed obsoleted extern injothfile.
 *
 * Revision 0.3  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 12:45:25  alexios
 * Added resetblocking() to remember previous states of block-
 * ing/non-blocking and switch between them.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.

@endverbatim
*/


#ifndef RCS_VER 
#define RCS_VER "$Id: input.h,v 2.0 2004/09/13 19:44:34 alexios Exp $"
#endif


#ifndef INPUT_H
#define INPUT_H



/** @defgroup input Reading data from the user

    Here you can find low-, medium- and high-level functions to acquire and
    validate input from the user. These functions do all sorts of weird and
    wonderful things with the user's input.

    Thankfully, despite the wealth of functionality you can find here, getting
    input from the user is a straightforward thing in most cases. The most
    complex API is that of the concatenated command parser, and it @e really
    should be made simpler (read: transparent).

@{*/




/** @defgroup INF_flags Input option flags (INF_x)

    @memo Input flags.

    @doc These flags control the operation of subsequent input
    operations. They're ORred together and stored in the global variable
    ::inp_flags.

    - #INF_HELP. High-level menuing and data-validation functions will return
      the default help action (option `<tt>?</tt>') to the caller so they can
      provide their own `help' functionality. If #INF_HELP is not set, then the
      high-level entry/validation functions will deal with help requests on
      their own, typically printing a longer version of a menu or redisplaying a
      full prompt.

    - #INF_PASSWD. The mid-level inp_get() function will echo stars instead of
      the characters typed. This is intended for password entry.  This flag is
      cleared after calling an input function. This is meant to prevent normal
      data input operations from echoing asterisks because of programmer
      oversight or bug.

    - #INF_REPROMPT. This variable is set to a non-zero value by the low-level
      input functions when the user is `injected' with a paged message from
      another user (or the system). Traditional Major BBS behaviour simulated a
      carriage return in such cases. We just flag such events and let the caller
      deal with them. You must <em>always</em> check this value (use the
      inp_reprompt() function) in mid-to-high-level functions, to see if you
      need to reprompt the user. You must reprompt the user after an injected
      message, because the previous prompt may have scrolled off the screen, or
      it just might be out of context.

    - #INF_NOINJOTH. Disables processing of incoming injoth() injected
      messages. In this state, the user will not receive pages, audit entries,
      et cetera. You should use this <em>only</em> when it's necessary. The user
      should not be cut off from other users and the system for too long.

    - #INF_TIMEOUT. Is set by inp_readstring() to indicate that it exited
      because of a timeout arranged by inp_timeout() or a signal handler.

    @see inp_flags.

*/
/*@{*/

#define INF_HELP     0x0001 /**< High-level help requests to be handled by caller. */
#define INF_PASSWD   0x0002 /**< Echo asterisks (for password entry) */
#define INF_REPROMPT 0x0004 /**< You must reprompt, <tt>injoth()</tt> received */
#define INF_NOINJOTH 0x0008 /**< Set to disable incoming <tt>injoth()</tt>s */
#define INF_TIMEOUT  0x0010 /**< Set to indicate that a timeout occurred */

/*@}*/


/** The input flags. */

extern uint32 inp_flags;


/** User's input buffer (sized <tt>MAXINPLEN</tt>).

    This is where users' input is kept. This is a <tt>char</tt> array, but don't
    assume it represents the user's entire input. Concatenation commands may
    insert nulls to break the command line into ::margv arguments. */

extern char inp_buffer[];

/** Length of user's last input line. */

extern int  inp_len;                   


/* These guys violate the naming convention of publicly available symbols,
   but they're (a) far too traditional (the `em' originally stood for Major,
   not Megistos), and (b) they're just so convenient this way! */

extern char *margv[];  /**< Input arguments, no spaces, <tt>argv[]</tt>-style */
extern int  margc; /**< Number of input arguments passed, in <tt>argc</tt> style */


extern char inp_del[];            /** The backspace-space-backspace sequence */


extern volatile struct monitor *monitor;            /** Monitoring structure */


/** Message buffer for injoth().

    This is the injoth() buffer, identical to the archetypal IPC struct
    <tt>msgbuf</tt>. injoth() works via IPC messages. */

struct injothbuf {
	long mtype;
	char mtext [1];
};



/** Last <tt>msecs</tt> argument to inp_timeout(). */
extern int inp_timeout_msecs;

/** Last <tt>intrusive</tt> argument to inp_timeout(). */
extern int inp_timeout_intr;

/** @defgroup inp_lowlevel Low-Level Input Functionality

    You should generally not need to mess around with these. Use the mid- or
    high-level functions instead. They will make your life much
    easier. Functionality of this level is provided for the advanced author who
    needs to add features not present in the mid- or high-level functions.

    @{
*/


/** Initialise input subsystem.

    Prepares for user input by tweaking terminal, setting variables to a sane
    status, et cetera. Don't call this, mod_init() does it for you when you
    request #INI_INPUT or #INI_ALL. */

void inp_init(); 


/** Shutdown input system.

    Don't call this yourself, mod_done() and mod_end() do it for you. */

void inp_done();                                    


/** Display any queued injected messages.

    In implementing low-level input functions (i.e. those that wait for
    individual keystrokes from the user), you should call this function while
    waiting for user input.

    If you won't be accepting injected messages, you had better flag this in
    the user's online structure so that other users know that injected messages
    aren't presented to this user. Hell hath no fury like a user ignored.

    @return One if one or more injected messages were shown to the user. Zero
    if nothing was sent to the user. */

int  inp_acceptinjoth();


/** Set tty or username for monitoring.

    You can do this yourself, but <em>don't</em>. It's set by inp_init().

    @param tty_or_uid a user ID or UNIX tty name shown to any monitoring
    sysops. */

void inp_setmonitorid(char *tty_or_uid);


/** Monitor a line.

    Writes the current value of ::inp_buffer to the monitor structure.
    Passwords are protected. Do not call this yourself, unless you're building a
    low-level input function (one that waits for individual keystrokes from the
    user). */

void inp_monitor();


/** Low-level input function.

    Reads a string of a certain maximum length into ::inp_buffer. Does nothing
    else. The input length can be limited to an arbitrary number of characters,
    in which case the function will interactively block input until characters
    are deleted, making the length limitation plain to the user.

    You should not call this function directly. Use inp_get() instead. If you
    need raw strings, not margc/margv-style parsing, use inp_raw() immediately
    afterwards.

    The function waits for user input. If the user has entered nothing (or has
    deleted everything), inp_acceptinjoth() is called periodically to present
    any waiting injected messages. If any are shown, the function exits, setting
    #INF_REPROMPT, so that the caller can re-issue the last prompt.

    If a timeout set with inp_timeout() expires, the function issues a last call
    to inp_acceptinjoth(), sets the #INF_TIMEOUT flag, and exits.

    @param maxlen the maximum number of characters to allow. Don't set this too
    low unless absolutely necessary. Even if you only need a single-character
    string, it's better to check the length and rebuff the user than to do
    this. You must @e always allow the user to enter long global commands.
    <em>DO NOT SET THIS ARGUMENT TO VALUES GREATER THAN
    <tt>MAXINPLEN-1</em>.</tt>

    @see inp_get(). */

void inp_readstring(int maxlen);


/** Check if a reprompt is necessary.

    @return Non-zero if the #INF_REPROMPT flag is set. */

int inp_reprompt();


/** Set non-blocking mode.

    Puts the terminal into non-blocking mode. In this mode, read operations
    return immediately, regardless of whether there is data to be read or
    not. This is absolutely useless (dangerous, actually) for most conventional
    input operations, but it allows you to set up for real-time operations, like
    key combinations to break out of lists (recommended as a second means of
    stopping @e long lists in case the user was stupid enough to disable paging
    or choose a non-stop listing), or for MUDs.

    @warning Don't forget to set blocking mode as soon as you're done! Failure
    to do so may cause nasty behaviour.

    @warning The low-level line input operations always switch you back to
    blocking mode on termination.

    @see inp_nonblock(), inp_resetblocking(). */

void inp_nonblock();


/** Set blocking mode.

    Puts the terminal into blocking mode, the default, sane condition. In this
    mode, read operations block the caller until data is available. 

    @see inp_nonblock(), inp_resetblocking(). */

void inp_block();


/** Revert to previous blocking mode.

    Takes you back to the previously active blocking mode. Every time you call
    inp_block() or inp_nonblock(), the previous state of the terminal is saved
    internally. You can use this function to revert to it.
    
    Although I doubt the usefulness of this function, it might come in handy.

    @see inp_nonblock(), inp_resetblocking(). */

void inp_resetblocking();


/** Set user inactivity timeout.
    
    Not to be confused with input timeouts arranged by inp_timeout(). This
    function sets the user inactivity timeout for the current user. When the
    timeout counter reaches approximately 60 seconds, the @c bbsd daemon lets
    the user know that they will be kicked out in a minute. If the counter
    reaches zero, the user is kicked out of the system so as not to consume
    credits and possibly busy BBS channels. In the meantime, any single
    character input by the user resets the timer to the value specified here.

    Idle timeouts are imposed on all users except those with the Master Key
    (i.e. Sysops). Certain conditions may force timeouts even on Sysops (like
    logging in over telnet in Megistos 0.98 and 0.99 -- this may change in the
    future).

    There is absolutely no reason why you should change this.

    @param t the inactivity time in seconds.

    @see inp_resetidle().  */

void inp_setidle (int t); /* inactivity timeout */


/** Reset user inactivity timer.

    This is called every time user input is received, to reset the inactivity
    timeout.

    There are very few cases when you need to do this.

    @see inp_setidle() */

void inp_resetidle ();


/** Check for the eXit command.

    This simple function checks if the given string contains the exit command (X).

    @param s a string to test.

    @returns Non-zero if <tt>s</tt> was the exit command, zero otherwise. */

int  inp_isX (char *s);


/** Set user input timeout.

   This one allows getinput() to timeout for some reason or other. Not
   recommended as it doesn't fit in with the entire BBS philosophy, but there
   are applications (like MUDs or the <em>adventure</em> module) where this is
   needed.

   @param msec the number of milliseconds (ms) after which to terminate (this
   is accurate to <em>at most</em> 10 ms, the delay between checks for new
   keyboard input).

   @param intrusive supply a non-zero value for <tt>intrusive</tt> to cause
   getinput() to terminate even if the user has started typing something. The
   default behaviour, <tt>intrusive=0</tt> is to only timeout if the user is
   100% idle (empty input line). Intrusive mode is not recommended, as it
   interrupts the user --- the system should <em>never</em> interrupt the user
   unless there's a very, very good reason.

   Upon timeout, global variables ::inptimeout_msec and ::inptimeout_intrusive
   are reset to <tt>0</tt>. This is the official method of checking whether
   getinput() has timed out. Variable ::inptimeout_msec is used as a counter by
   inputstring(). This means you have to call setinputtimeout() before every
   call to getinput() that needs a timeout.  */

void inp_timeout(int msec, int intrusive);


/** Abort pending user input.

    This function is for use by signal handlers in conjunction with
    inp_timeout(). It causes inp_readstring() to exit, setting #INF_TIMEOUT.
    
    @see inp_timeout(), inp_readstring. */

void inp_cancel();


/** Set input flags.

    Sets a number of input flags.

    @param f a number of <tt>INF_x</tt> flags ORred together.

    @see inp_clearflags(). */

void inp_setflags(uint32 f);


/** Set input flags.

    Clears a number of input flags.

    @param f a number of <tt>INF_x</tt> flags ORred together.

    @see inp_setflags(). */

void inp_clearflags(uint32 f);



/** @} */




/** @defgroup inp_midlevel Mid-Level Input Functionality

    These functions provide you with user input at the middle-level. Some
    processing is carried out, but not much. Perhaps the most useful function
    here is inp_get(), which will yield one full line of user's input. The other
    functions allow you to break input strings into arrays of white
    space-separated words, storing them in ::margv. They can also reverse this,
    yielding back a single input line.

    @{*/
   

/** Mid-level input function.

    You can call this function to receive a line of input from the system and
    parse it into a number of space-delimited arguments. The input length can
    be limited to an arbitrary number of characters, in which case the function
    will interactively block input until characters are deleted, making the
    length limitation plain to the user.

    @param maxlen the maximum number of characters to allow. Don't set this too
    low unless absolutely necessary. Even if you only need a single-character
    string, it's better to check the length and rebuff the user than to do
    this. You must <em>always</em> allow the user to enter long global commands.
    <em>DO NOT SET THIS ARGUMENT TO VALUES GREATER THAN <tt>MAXINPLEN-1</em>.</tt>

    @return a pointer to the first argument, <tt>margv[0]</tt>). The input
    string is automatically partitioned into space-delimited arguments. To
    restore the raw input line, call inp_raw() afterwards. You should @e not use
    inp_readstring() unless necessary, because it does not deal with reprompts
    and other aspects of the user interface.

    @see inp_raw(), inp_readstring(). */

char *inp_get(int maxlen);


/** Parse input.

    Splits ::inp_buffer into white space-separated arguments. Sets ::margc to
    the number of such arguments, and ::margv[i] to point to the first non-space
    character of the <tt>i</tt>-th argument. */

void inp_parsin();


/** Clear input buffers.

    Resets the input subsystem by clearing everything. */

void inp_clear();


/** Restores raw input.

    `Unparses' the input by restoring the white space in ::inp_buffer.  This
    gives you back the original, full input line as entered by the user.

    Please note that ::margc and ::margv are invalidated by this function. If
    you use these variables afterwards, bad things will happen.

    @see inp_get(). */

void inp_raw();


/** @} */


/** @defgroup input_cnc Command Concatenation (Mid-to-High-Level)

    @memo Processing multiple commands typed together.

    I don't know if this was supported anywhere else before the Major BBS, but
    that's where I first saw it. The concept is nice: expert users can
    concatenate multiple commands, instead of typing them one by one and getting
    menu after menu sent to them. This makes a lot of sense for both advanced
    users and those on a slow line.

    This group of functions helps handle such commands. Commands processing
    <em>must</em> use these function as much as possible. There are many
    guidelines on how to use them, but most are empirical. A few I can remember
    right now are:

    - Call cnc_end() before asking for confirmation on something dangerous, like
      deleting important information.

    - Call cnc_end() after errors, to stop the rest of the user's command from
      being executed.

    - Use cnc_more() to see if more input is available, or rely on what the
      other functions return.

    - Try to use the <tt>get_</tt> high-level input functions wherever
      possible. They deal with concatenation in the canonical way and save you
      almsot all of the work.

    - For that matter, to learn more about how to work with concatenation, refer
      to the code of those functions.

    The <tt>cnc_</tt> functions will provide you with information from the
    user's input in an incremental way. You should only ask for what you
    need. If you only need a single menu option, don't call cnc_word(). Doing so
    will gobble any other commands the user has stuck after the one you need.

    Before calling one of the main <tt>cnc_</tt> functions, make sure there @e
    input for you. The cnc_more() function should be handy. If there's no more
    input, you should call inp_get() to obtain some. Yes, this is tedious
    stuff. That's why it's recommended you use the <tt>get_</tt> functions.

    @see cnc_nxtcmd, cnc_begin(), cnc_end(), cnc_chr(), chr_int(), cnc_word(),
    cnc_long(), cnc_yesno(), cnc_hex(), cnc_word(), cnc_all(), cnc_more(),
    cnc_num(), inp_raw().

*/
/*@{*/

extern char *cnc_nxtcmd;         /** Next character in command concatenation */


/** Begin concatenation handling.

    Parses command line and prepares to handle concatenation. If you want to
    handle concatenation, make sure you call this after getting input, but do @e
    NOT call it at any other time. It will reset ::cnc_nxtcmd to the beginning
    of the line and may get you into endless loops (which, my sources tell me,
    Linux executes in a measly five seconds anyway).

    Oh, and other modules may rely on this. The whole concept of concatenation
    joins modules together to form what appears to be a single system. If you
    break the chain, other modules will be unhappy. A bug in Menuman 0.1 broke
    the chain in 1994. Three minutes after that, a <tt>gdb</tt> fell on it,
    killing it. The clubs module has followed the chain from the beginning and
    look at it: it's the biggest one of'em all.

    Oh. Sorry. */

void cnc_begin();


/** End concatenation processing.

    This stops processing concatenated input. It re-parses the input line into
    space-delimited arguments and invalidates ::inp_nxtcmd.

    @return non-zero if the input line was empty. Zero otherwise. */

int cnc_end();


/** Read a concatenated character.

    Takes a single character from the input string.

    @return The character read from the concatenated commands. Zero (<tt>\\0</tt>)
    is returned if no more commands are available. */

char cnc_chr();


/** Read a concatenated 32-bit integer.

    Parses a concatenated 32-bit signed integer. Consecutive integers are, of
    course, space-delimited. The function knows about this <tt>sscanf()</tt> to
    the dirty work).

    @return The integer read from the concatenated commands. Zero (<tt>\\0</tt>)
    is returned if there was a parse error. This is a <em>bug</em>, and should
    be rectified. */

int32 cnc_int();


/** Read a concatenated 64-bit integer.

    Parses a concatenated 64-bit signed integer. Consecutive integers are, of
    course, space-delimited. The function knows about this <tt>sscanf()</tt> to
    the dirty work).

    The nomenclature was inspired from the Major BBS, which was 16-bit. There,
    <tt>int</tt>s were 16 bits long (eurgh) and <tt>long</tt>s were a nice 32
    bits. We go a bit further and read 64-bit `longs'.

    @return The integer read from the concatenated commands. Zero (<tt>\\0</tt>)
    is returned if there was a parse error. This is a <em>bug</em>, and should be
    rectified. */

int64 cnc_long();


/** Read a concatenated `Y' or `N'.

    Parses a simple yes/no answer.

    @return the parsed character, in upper case (if it's a `y' or `n'). Zero is
    returned if no more input is available, as per cnc_chr(), which this
    function calls. */

char cnc_yesno();


/** Read a space-delimited word.

    Parses a space-delimited word.

    @return a pointer to the word. The pointed entity is statically
    allocated. Don't <tt>free()</tt> the pointer! @c NULL is returned if no more
    input is available. */

char *cnc_word();


/** Return all remaining concatenated commands.

    Gobbles and returns all remaining input.

    @return the value of ::cnc_nxtcmd, or @c NULL if there was no remaining
    input. */

char *cnc_all();                                      /* Gobble rest of input */


/** Check remaining input.

    Checks if there is any concatenated input remaining.

    @return the first character of the remaining input. The character is not
    gobbled, so you have to call cnc_chr() if you want it removed from the
    command string. This makes cnc_more() perfect for peeking at the next
    character. */

char cnc_more();


/** Read a concatenated hexadecimal 64-bit integer.

    Parses a concatenated hexadecimal integer and returns it as a 64-bit
    unsigned integer (because we can). Consecutive hex integers must, of course,
    be space-delimited. The function knows about this (it uses <tt>sscanf()</tt>
    to the dirty work).

    @return The integer read from the concatenated commands. Zero (<tt>\\0</tt>)
    is returned if there was a parse error. This is a <em>bug</em>, and should be
    rectified. */

uint64 cnc_hex();


/** Read an arbitrary precision integer.

    Parses a concatenated integer of arbitrary length and precision and returns
    it as a <tt>char</tt> string. The function stops parsing at the first
    non-digit character that follows an optional minus sign.

    @return The integer read from the concatenated commands as a string. @c NULL
    is returned if there was no input to play with. Absolutely no validation is
    performed (apart from making sure the minus sign is at the beginning). */

char *cnc_num();                                   /* Return an ASCII decimal */

/*@}*/



/** @defgroup inp_hilevel High-Level user-interacting input/validation

    @memo Very high-level input functionality.

    This group of functions implements most of the input functionality needed by
    Megistos modules. It is @e strongly recommended that you use them, as they
    keep the user interface consistent (and if the interface changes, the
    behaviour of your module will change without you having to rewrite code).

    These functions present the user with prompts, read and validate input,
    offer and handle defaults, deal with concatenated commands, and produce
    error messages and help. Unfortunately, they need quite a few
    arguments. Sorry!

    Fortunately, the calling interface is very similar for all these
    functions. Don't be scared by the long documentation, it's mostly cut and
    paste stuff!

    You can use them as examples to code your own, specialised functions in
    your modules. However, please only do so if the functionality isn't
    provided here.

    There are some common points in all these functions.

    - Prompts are provided to the user. Any prompts may be zero, in which case
      the user is not prompted at all. This may be inelegant in some cases.

    - Defaults are handled by providing a prompt number and default value. The
      prompt indexed by the prompt number displays the default value using a
      suitable format specifier. If the prompt number is zero, it is not printed
      (it is thus expected that the first prompt printed will tell the user what
      the default value is). If the default value is zero or NULL (depending on
      the function), the default facility is disabled and the user @e must enter
      a value. This is done so as to allow BBS prompts the flexibility to be
      issued with and without defaults with minimum hassle.

    - Reprompting after injected messages (see injoth()) is handled elegantly.

    - Help is available to the user by providing a help prompt index. If it is
      zero, no help will be available. In the case of menu handling, asking for
      help redisplays the long version of a menu.

    - Optionally, the caller can set #INP_HELP. In this case, if <tt>?</tt> is
      specified by the user, the function exits returning -1. The caller can
      then handle the help request themselves, e.g. by generating and printing a
      long list of possible values the user may enter.

    - The user may exit at any time by entering 'X'. In this case, these
      functions return 0 and do @e not return any input.

@{*/

/** Get an integer within certain limits.

    Prompt @c msg asking for a number between @c min and @c max. Return the
    number in <tt>num</tt>. If <tt>def!=0</tt>, there is a default value (prompt
    @c def displays it) which is passed in <tt>defval</tt>. Prompts @c err if
    bad value entered.

    @param num pointer to an <tt>int</tt>. This is written to if a valid number is
    entered.

    @param msg is the short prompt number to display. This should give the
    user a brief idea of what is expected of them. This prompt should belong to
    the current message block. It will not be displayed if the value is zero,
    but please don't do this as it makes things look inelegant.

    @param min minimum allowed value for the number.
    @param max likewise, the maximum allowed value for the number.

    @param err the error prompt to display. Specify zero to disable error
    printing. You can have an optional <tt>\%d</tt> format specifier in the error
    prompt. It will be substituted by the (wrong) number entered.

    @param def is the user prompt used when defaults are used (which must belong
    to the current prompt block). This is usually a short string added to the
    short menu prompt, and looks like `<tt>(Enter=\%d)</tt>' or
    `<tt>[\%d]</tt>'. The format specifier gets the value of
    <tt>defval</tt>. Use a zero to disable printing of <tt>defval</tt> where,
    for instance, the default value is printed by <tt>msg</tt>.

    @param defval is the default value for when the user presses <tt>Enter</tt>.

    @return Zero if X entered; one is returned if the number was valid, in which
    case it is stored in <tt>num</tt>. A value of @c -1 implies that #INF_HELP
    was set and the user entered `<tt>?</tt>'. */

int get_number(int *num,int msg,int min,int max,int err,int def,int defval);


/** Get a boolean (yes or no) answer.

    Works just like getnumber(). Prompts @c msg, asks for a {\tt Y/N</tt>
    answer, prompts @c err if there was a bad response, optionally prompts @c
    def with a default value of @c defval: 0 for no or 1 for yes.

    @param retbool pointer to an <tt>int</tt>. This is written to if a valid (or
    default) answer is provided. The variable will be set to 1 if `yes' was
    chosen, and to 0 if the answer was `no'.

    @param msg is the short prompt number to display. This should give the user
    a brief idea of what is expected of them. This prompt should belong to the
    current message block. It will not be displayed if the value is zero, but
    please don't do this as it makes things look inelegant.

    @param err the error prompt to display. Specify zero to disable error
    printing.

    @param def is the user prompt used when defaults are used (which must belong
    to the current prompt block). This is usually a short string added to the
    short menu prompt, and looks like `<tt>(Enter=\%c)</tt>' or
    `<tt>[\%d]</tt>'. The format specifier gets either `Y' or `N', depending on
    the value of <tt>defval</tt>. Use a zero to disable printing of
    <tt>defval</tt> where, for instance, the default value is printed by
    <tt>msg</tt>.

    @param defval is the default value for when the user presses
    <tt>Enter</tt>. Non-zero values stand for yes; zero is no.

    @return Zero if X entered; one is returned if the answer was valid, in which
    case it is stored in <tt>retbool</tt> (1 for `yes', 0 for `no'). A value of
    <tt>-1</tt> implies that #INF_HELP was set and the user entered `?'. */

int get_bool(int *retbool,int msg,int err,int def,int defval);


/** Get and validate a user ID.

    Prompts @c msg asking for a user ID. If the user does not exist (as checked
    by uidxref()), @c err is prompted (with a <tt>\%s</tt> format specifier
    containing the invalid user ID. If <tt>def!=0</tt>, prompt @c def is
    displayed along with a default user ID of <tt>defval</tt>.

    The user can enter the first few characters of a user ID (three at least),
    and uidxref() will complete the user ID will when @c Enter is pressed. If
    there are more than one user IDs matching what the user entered, a short
    menu will be shown and the user can choose which one they meant.

    @param uid pointer to a <tt>char *</tt>. This is written to if a valid (or
    default) answer is provided. The variable will be set to the canonical form
    of the user ID, i.e. in full, and capitalised properly.

    @param msg is the short prompt number to display. This should give the user
    a brief idea of what is expected of them. This prompt should belong to the
    current message block. It will not be displayed if the value is zero, but
    please don't do this as it makes things look inelegant.

    @param err the error prompt to display. Specify zero to disable error
    printing.

    @param def is the user prompt used when defaults are used (which must belong
    to the current prompt block). This is usually a short string added to the
    short menu prompt, and looks like `<tt>(Enter=\%s)</tt>' or
    `<tt>[\%s]</tt>'. The format specifier gets the default user ID provided in
    <tt>defval</tt>. Use a zero to disable printing of @c defval where, for
    instance, the default value is static and included in <tt>msg</tt>.

    @param defval is the default value for when the user presses
    <tt>Enter</tt>. Specify @c NULL if there is no default.

    @param online if this is non-zero, the entered user ID must belong to a user
    who is currently on-line.

    @return a value of one is returned if input is valid, in which case the
    selected user ID can be found in <tt>uid</tt>. Zero is returned if the user
    bailed out with <tt>X</tt>. A value of @c -1 implies that #INF_HELP was set
    and the user entered `<tt>?</tt>'. */

int get_userid(char *uid,int msg,int err,int def,char *defval,int online);

/** Validate input for a simple menu.

    Displays a long menu (<tt>lmenu</tt>) once per session (if <tt>showmenu</tt>
    is non-zero), plus whenever the question mark (<tt>?</tt>) is entered. The
    prompt is a short version of the long menu (<tt>smenu</tt>). Options are
    single characters contained in the string <tt>opts</tt>}. In case of error,
    @c err is prompted.  Defaults are handled in the usual way. The selection is
    returned in <tt>option</tt>.

    @param option pass a pointer to a single <tt>char</tt> variable here. On
    successful exit, the variable will hold the user's option in upper case.

    @param showmenu controls display of the long menu prompt <tt>lmenu</tt>. A
    non-zero value displays <tt>lmenu</tt> before doing anything else, or when
    the user types <tt>?</tt> to request for help. A zero only displays the @c
    lmenu when the user requests for help, unless input flag #INF_HELP is in
    effect, in which case the function exits and the caller is responsible for
    processing the help request themselves. Complicated? Yes, it is. Sorry.

    @param lmenu is the prompt number of the long menu to display. If @c lmenu
    is zero, no long menu will be displayed, no matter what the value of @c
    showmenu is. The long menu prompt must belong to the current message block.

    @param smenu is the short prompt number to display. This should give the
    user their options and little more besides. This prompt should belong to
    the current message block. It will not be displayed if the value is zero,
    but please don't do this as it makes things look inelegant.

    @param err the error prompt to display. As usual, specify zero to disable
    error printing. You can have an optional <tt>\%c</tt> format specifier in the
    error prompt. It will be substituted by the character entered by the user.

    @param opts is a string of upper case characters representing the options
    available to the user. Leave this empty and the user will only be able to
    exit this part of the module by using <tt>X</tt> (which should work
    everywhere).

    @param def is the default user prompt (which must belong to the current
    prompt block). This is usually a short string added to the short menu
    prompt, and looks like `<tt>(Enter=\%c)</tt>' or `<tt>[\%c]</tt>'. The
    format specifier gets the value of <tt>defval</tt>. Use a zero to disable
    printing of <tt>defval</tt> where, for instance, the default value is
    printed as part of the @c smenu prompt.

    @param defval is the default user option (in upper case) for when the user
    presses <tt>Enter</tt>. Zero indicates no default is available and Enter
    reprompts.

    @return Zero if the user bails out with <tt>X</tt>; one if the process was
    successful, in which case @c option is modified to hold the user's selection
    (or the default value). A value of <tt>-1</tt> means that #INF_HELP was set
    and the user pressed `<tt>?</tt>'. */

int get_menu(char *option,int showmenu,int lmenu,int smenu,int err,char *opts,
	    int def,int defval);

/*@}*/


#endif /* INPUT_H */


/*@}*/

/*
LocalWords: Alexios doc API em legalese alexios Exp bbs inputflags miscfx
LocalWords: initially injothfile GPL resetblocking ing ifndef VER endif tt
LocalWords: INF PASSWD inp REPROMPT reprompt NOINJOTH injoth readstring ms
LocalWords: MAXINPLEN margv int len Megistos argv margc argc del struct
LocalWords: Initialise init INI acceptinjoth username param uid sysops cnc
LocalWords: setmonitorid maxlen reprompts parsin Unparses getinput MUDs
LocalWords: msec inptimeout inputstring setinputtimeout ORred clearflags
LocalWords: setflags nxtcmd Menuman gdb of'em chr sscanf eurgh yesno uint
LocalWords: num msecs intr nonblock resetblock bbsd resetidle setidle eXit
LocalWords: isX highlevelinput msg min def defval getnumber bool
LocalWords: retbool uidxref IDs bailed userid lmenu showmenu smenu bails
*/
