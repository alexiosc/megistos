/** @file    output.h
    @brief   Outputting data to the user
    @author  Alexios

    This header file includes functions used to send output to the user, and to
    control how this output is sent. It largely implements high-level
    functions, with the really low-level ones abstracted away (they're
    horrible, ugly and kludgy, anyway).

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     output.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Provide an interface to output.c, autoconfig the kernel,     **
 **            solve differential equations, speed up Windows, and other    **
 **            legends.                                                     **
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
 * Revision 1.5  2003/12/19 13:25:18  alexios
 * Updated include directives.
 *
 * Revision 1.4  2003/09/27 20:31:57  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  2000/01/06 11:37:41  alexios
 * Added declaration for send_out(), a wrapper for write(2) that
 * deals with overruns due to non-blocking I/O.
 *
 * Revision 0.5  1998/12/27 15:19:19  alexios
 * Added declarations that allow us to enable/disable auto-
 * matic translation.
 *
 * Revision 0.4  1998/07/26 21:17:06  alexios
 * Added function printlongfile() that outputs a very long file
 * checking if the user has interrupted the listing.
 *
 * Revision 0.3  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/03 00:29:40  alexios
 * Removed hardwired translation tables.
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

#ifndef OUTPUT_H
#define OUTPUT_H


/** @defgroup output Outputting to the User

    This module includes functions used to send output to the user, and to
    control how this output is sent. It largely implements high-level functions,
    with the really low-level ones abstracted away (they're horrible, ugly and
    kludgy, anyway).
    
    @{ */


#define _ASCIIVARCHAR '@'
#define _VARCHAR      0x7f


#include <megistos/useracc.h>


extern char   out_buffer[8192];	/** Temporary output buffer */
extern uint32 out_flags;	/** Output flags (<tt>OFL_x</tt> flags) */


/** @defgroup OFL_flags Output Flags (OFL_x)

    @memo Output flags.

    @doc These flags control the behaviour of the low-level output subsystem.

    - @c OFL_ANSIENABLE. If this flag is set, ANSI output is enabled. Actually,
      the flag works the other way round: if it's clear, ANSI directives are
      stripped from all output.

    - @c OFL_WAITTOCLEAR. Set to indicate that, if a clear screen ANSI directive
      is received, and this does not happen @e immediately a user input request,
      a screen pause will be forced. This is done to make sure that the user can
      see all output of the system. If even a single character (even white space
      or ANSI directives) has been output to the user between the user's last
      input and the screen clear, the pause will be forced. For that reason, try
      to place clear screen directives at the top of message prompts.

    - @c OFL_AFTERINPUT. Set by the low-level input subsystem to indicate that
      user input has just been received. This is used, among other things, in
      co-operation with the flag above to generate screen pauses.

    - @c OFL_INHIBITVARS. Substitution variables are variables enclosed in
      at-signs. These variables will be replaced by their value before being
      printed. For instance, you can issue the name of the BBS by using
      <tt>@@BBS@@</tt>, and the current time using <tt>@@TIME@@</tt>. Setting
      this flag inhibits interpretation of at-signs as variable
      delimiters. Effectively, no variable substitution will occur. This is
      useful as a security measure. You certainly don't want users to be able to
      use substitution variables in their messages or pages. It could be used by
      crackers to confuse people or for `social engineering'.

    - @c OFL_PROTECTVARS. If the above flag is clear, you can set this flag to
      partially inhibit variable substitution to <em>only</em> system
      prompts. Expansion in user-contributed material will not occur.

    - @c OFL_ISBOT. Set to mark a non-human user of the system. Output is
      reformatted for easier parsing by scripts, AIs etc and output in a nice,
      easily parsable format. You shouldn't need to touch this flag. It's set by
      the BBS library whenever needed.

@{*/

#define OFL_ANSIENABLE  0x01	/**< Enable ANSI output */
#define OFL_WAITTOCLEAR 0x02	/**< Pause before clearing screen */
#define OFL_AFTERINPUT  0x04	/**< First output after an input */
#define OFL_INHIBITVARS 0x08	/**< Do not interpret substitution variables */
#define OFL_PROTECTVARS 0x10	/**< Only interpret subst vars inside prompts */
#define OFL_ISBOT       0x20	/**< Output is for a bot/AI/script */

/*@}*/


/** Substitution variable record

    This is used in two ways. Internally, it represents one record in the
    substitution variable registry. Externally, i.e. within modules, it can be
    used to register new, local substitution variables. Most of the larger
    modules do this to provide extra flexibility for customisation. There are
    three fields here: <tt>varname</tt> is the string name of the variable (in
    upper case by convention); <tt>varcalc</tt> is the function executed to return
    the value of the variable; and <tt>next</tt> is only used internally to make a
    linked list of variables. */

struct substvar {
	char *varname;	        /**< Name of substitution variable (upper case) */
	char *(*varcalc)(void);	/**< Function that returns variable contents */
	void *next;		/**< Next handler in linked list */
};


/** Initialise output subsystem.

    Prepares for output to the user by opening the system prompt block
    (::sysvar), initialising substitution variables, and giving default values
    to the output flags. */

void out_init();


/** Shut down output to the user.

    Nothing much to this function, really. Almost everything is handled by the
    operating system, anyway. */

void out_done();


/** Initialise substitution variables.

    This function is called by out_init(), which is in turn called by
    mod_init(). You shouldn't have to call it yourself. It adds a wide
    collection of built-in, system-wide substitution variables, using calls to
    out_addsubstvar().
    
    @see out_substvar(). */

void out_initsubstvars ();


/** Install a new substitution variable.

    This function may be called from within your own modules to install new,
    local substitution variables. This function only adds a single variable. You
    might find it handy to add multiple variables by using this little trick
    (also available as example out_subst.c):

@verbatim
struct substvar table []={
	{"BBS",      sv_bbstitle, NULL},
	{"COMPANY",  sv_company,  NULL},
	{"ADDRESS1", sv_address1, NULL},
	{"",         NULL,        NULL}
};

. . .

int i=0;

while (table [i].varname [0]) {
	out_addsubstvar (table [i].varname, table [i].varcalc);
	i++;
}
@endverbatim

    This has the additional advantage of reusing the struct substvar datatype
    for our own, vile purposes. Note how the <tt>next</tt> (i.e. the third)
    field isn't used here and is initialised to @c NULL.

    @param name The name of the substitution variable, as a string. You can
    either specify the name with the enclosing at-signs <tt>@@</tt>, or
    plain. The function will add any missing at-signs internally.

    @param varcalc A function of that returns a string. This function will be
    called in response to encountering a variable <tt>name</tt>. The return
    value of the function will used instead of the variable. This allows pretty
    complex functionality.
    
    @see out_initsubstvars(). */

void out_addsubstvar(char *name, char *(*varcalc)(void));


/** Control character translation.

    This function controls how characters will be translated, if at all.

    @param mode The number of the translation table to use for both input and
    output characters. Alternatively, one of the following:

    - @c XLATION_OFF. Disables automatic translation. This is necessary before
      running software that talks to the user (or some client) in binary, or
      simply to display something to the user without translation (though I
      can't think of a reason at 2am).

    - @c XLATION_ON. Enables automatic translation, using whatever table used to
      be active at the time of de-activation. Useful for turning translation
      back on (see above).

    Please bear in mind that the translation itself is done by <tt>emud</tt>,
    and so any settings are persistent throughout the user's session with the
    system. The translation table is initialised by <tt>emud</tt> itself in the
    beginning, so don't change it unless you can guarantee the user will be able
    to read whatever you're sending!

    Currently, the only use for @c XLATION_OFF and @c XLATION_ON is to disable
    (temporarily) translation while a binary file transfer protocol (like
    Z-Modem) is running. The only use for the function itself is during the
    logon or signup processes, or after changing translation preferences in the
    Account module. */

void out_setxlation(int mode);

#define XLATION_OFF -1		/**< Disable automatic translation */
#define XLATION_ON  -2		/**< Re-enable automatic translation */



#ifndef OUTPUT_O


/** Format and display a prompt.

    Ah, the building block of every module in the system. This function performs
    almost all of the output of your average module. It works in much the same
    was as <tt>printf()</tt>. Unlike the omnipresent C function, however,
    prompt() doesn't use a string format string, but a <tt>number</tt>. The
    number indices one of the prompts inside the currently active prompt
    block. These indices have symbolic names attached to them, that are also
    defined in C headers. A prompt block called <tt>test.mbk</tt> containing a
    prompt called HELLO would thus have an include file <tt>test.h</tt> with
    something like <tt>#define HELLO 4</tt>.

    The prompt() function takes just this symbolic name for a prompt, where it
    obtains the format string. Most prompts have no format specifiers, and thus
    take no arguments, just like you can use <tt>printf()</tt> to print a string
    without formatting numbers et cetera inside it. Format specifiers within
    prompt blocks are exactly the same as those used by <tt>printf()</tt> and
    friends. The same rules about number and type of additional arguments hold
    here, too.

    The format specifiers are substituted with formatted strings, numbers (and
    what have you) <em>before</em> anything else. Variable substitution, line
    wrapping, et cetera happen immediately afterwards.

    This function is not without its limits. Expect horrific breakage if the
    prompt is longer than 8 kbytes. Actually, the breakages may occur somewhere
    between 8 and 16 kbytes. This is a reasonable limit: given an 80 by 25 text
    mode, 8 kbytes is around four <em>completely</em> full screens. If you need
    to print something this large, you're probably doing something wrong (try
    using the Menu Manager, which prints out the contents of entire files
    without size limitations), or just use out_printfile() or out_catfile()
    within your module.

    @param num The prompt number to use, followed by any arguments needed by
    the prompt in question.

    @see printf(), sprompt(), sprompt_other(), print(), sprint(),
    sprint_other(). */

void prompt(int num,...);


/** Format a prompt and store it in a string. 

    This function behaves somewhat like prompt(), but stores the formatted text
    in a string, instead of printing it out directly. There are a few subtle but
    important differences, due to the way sprint() works. See the documentation
    for sprint() for a list of the differences in formatting.

    @param buf The buffer to hold the resultant prompt string.

    @param num The prompt number to use, followed by any arguments needed by the
    prompt in question.

    @see prompt(), sprompt_other(), printf(), print(), sprint(),
    sprint_other(). */

void sprompt(char *buf, int num,...);


/** Format a prompt for another user and store it in a string. 

    This function behaves just like like sprompt(), but takes into account the
    other user's (::othruser) setup. If the other user is a bot, the string will
    be in a suitable format. It will also be in the other user's language. Other
    than that, semantics are identical to those of sprint().

    @param ushm The struct shmuserrec structure for the other user. This will
    almost always be ::othrshm.

    @param buf The buffer to hold the resultant prompt string.

    @param num The prompt number to use, followed by any arguments needed by
    the prompt in question.

    @return A pointer to the resultant <tt>buf</tt>.

    @see prompt(), sprompt(), printf(), print(), sprint(), sprint_other(). */

char *sprompt_other(struct shmuserrec *ushm, char *buf, int num,...);


/** Format and print a string.

    This is the equivalent of <tt>printf()</tt> in the context of Megistos. It
    performs <em>exactly</em> like <tt>printf()</tt>, which is small wonder,
    considering it uses <tt>vsprintf()</tt> interally.

    You <em>should not</em> use this function to print literal strings. BBS
    internationalisation and customisation depend on having all strings inside
    prompt blocks. Okay, so we don't always follow this rule, but we try to,
    and we (usually) only print white space.

    `Why is this function here, then', I hear you ask (among death threats and
    other severe complaints). It's useful for formatting and printing strings
    that you've previously constructed from prompts and stored for
    later. Really, it <em>does</em> have its uses.

    Like all of the output functions in this subsystem, print() does line
    wrapping, justification, et cetera in order to print out your string. This,
    of course, depends on your wishes, as embedded within the string in the form
    of format directives.

    @param buf A string with zero or more format specifiers, followed by zero or
    more additional arguments based on the number and type of format specifiers.

    @see printf(), sprint(), prompt(), sprompt(). */

void print (char *buf,...);


/** Format and store a string.

    This function resembles print(), but stores its results in a string instead
    of printing them. Its workings are <em>not</em> identical! There are subtle
    but important differences in semantics. Unlike print(), sprint():

    - Does not offer page breaks.
    - Does not interpret, expand, strip or translate ANSI directives.
    - Does not interpret or act on formatting directives.
    - Does not consult or alter the output flags.
    - Generally alters no state.

    However, like print(), sprint() @e does expand substitution variables.

    This function is useful for delayed evaluation of user prompts. Strings
    created with sprint() can be stored and later shown to the user with
    print(), which will take care of page breaks, ANSI and formatting
    directives. However, substitution variables will be expanded at the time
    sprint() was called.

    Alternatively, you can prepare a message using msg_getu() and sprint(). Then
    invoke usr_injoth() to send the string to another user. The string will be
    formatted @e locally for that user's terminal and preferences. Substitution
    variables will reflect the state of affairs of the user calling sprint().

    @param stg The string to store the formatted text in.
    
    @param buf A string with zero or more format specifiers, followed by zero or
    more additional arguments based on the number and type of format specifiers.

    @see printf(), print(), prompt(), sprompt(). */

void sprint (char *stg,char *buf,...);



#endif /* OUTPUT_O */

#ifdef WANT_SEND_OUT


/** Low-level string output.

    This function has exactly the same syntax and semantics as
    <tt>write()</tt>. The reason for its existence is complex: if non-blocking
    I/O is used, excessive output may overrun the OS output buffer. Under Linux,
    this is 4 kbytes, a fact that can account for long listings getting
    garbled. So we loop, trying to write as much of the string as we can,
    waiting a bit between writes --- but only if the entire string couldn't be
    sent. The performance impact should be minimal, as the bottleneck is likely
    to be the user's bandwidth anyway.

    The trick is to wait for the output buffer to have some more space, unless
    of course we've managed to send the whole string in the first attempt. This
    depends on bandwidth. It doesn't need to be big for the Linux console.
    Modems can't send out information as fast, so we have to wait more. To cover
    all cases, we wait for a pretty long time. This might produce slightly jerky
    output on the console (though I personally can't detect it), but won't
    easily be detectable on a modem.

    I really want to do away with this horror. It's a great big kludge and it
    stinks, and I hate it. Please, <em>please</em>, tell me there's a nice,
    elegant, standard way to either flush the output buffer and wait till it's
    empty, or to get a measure of how full the output buffer is.

    @param fd A file descriptor to write to.

    @param s A string to write to <tt>fd</tt>.

    @param count The number of bytes to write to <tt>fd</tt>.

    @return The number of bytes written, as returned by internal calls to
    <tt>write()</tt>. */

int out_send (int fd, char *s, int count);

#endif /* WANT_SEND_OUT */


/** Print a file.

    This function causes a file to be opened and its contents printed using
    successive calls to the <tt>print()</tt> function. Any substitution variables
    within the file will be expanded, and any formatting directives will be
    obeyed as usual.

    @param fname The filename of the file to print. 

    @return One on success, zero if opening the file failed, in which case {\tt
    errno} will contain the exact error. 

    @see out_printlongfile(), out_catfile(). */

int out_printfile (char *fname);


/** Print a file.

    Works exactly like out_printfile(). This function, however, puts the
    terminal in non-blocking mode. The user may press a special control
    character (Enter, New Line, Line Feed, Escape, Control-C or Control-O) to
    stop the transmission. The terminal is reset to its previous mode of
    operation after the function finishes, using inp_resetblocking(). Do not use
    this latter function with out_printlongfile().

    @param fname The filename of the file to print. 

    @return One on success, zero if opening the file failed, in which case {\tt
    errno} will contain the exact error.

    @see out_printfile(), out_catfile(). */

int out_printlongfile (char *fname);


/** Print a file verbatim.

    Works a bit like out_printfile(), but does @e not format the file before
    output. Substitution variables will not expand, formatting directives will
    be printed as-is, et cetera.

    @param fname The filename of the file to print. 

    @return One on success, zero if opening the file failed, in which case @c
    errno will contain the exact error.

    @see out_printfile(), out_printlongfile(). */

int out_catfile (char *fname);


/** Set output flags.

    This function sets the given output flags.

    @param flags A set of flags, ORred together.

    @return Nothing. This is a macro and should be only be used for its
    side-effect. 

    @see out_clearflags(), out_setansiflag(), out_setwaittoclear(). */

#define out_setflags(flags) __out_setclear(1,flags)

/** Clear output flags.

    This function clears the given output flags.

    @param flags A set of flags, ORred together.

    @return Nothing. This is a macro and should be only be used for its
    side-effect.

    @see out_setflags(), out_setansiflag(), out_setwaittoclear(). */

#define out_clearflags(flags) __out_setclear(0,flags)


void __out_setclear(int set, uint32 f);


/** Set or clear the #OFL_ANSIENABLE flag.

    This function is only a legacy interface to the #out_setflags and
    #out_clearflags} macros. It's used to control the #OFL_ANSIENABLE flag,
    which in turn controls whether or not ANSI directives are stripped before
    output.

    @param f Causes the flag to be set if non-zero, or to be cleared if
    zero. */

#define out_setansiflag(f) __out_setclear(f,OFL_ANSIENABLE)


/** Set or clear the #OFL_WAITTOCLEAR flag.

    This function is only a legacy interface to the #out_setflags and
    #out_clearflags macros. It's used to control the #OFL_WAITTOCLEAR flag. This
    flag controls whether or not pauses will be forced before screen clears to
    make sure the user has time to read the last characters of the previous
    screen.

    @param f Causes the flag to be set if non-zero, or to be cleared if
    zero. */

#define out_setwaittoclear(f) __out_setclear(f,OFL_WAITTOCLEAR)


/** \example out_subst.c

    A short example demonstrating how to add substitution variables inside your
    own modules (they will, of course, only be accessible to prompts @e within
    your module).

*/


#endif /* OUTPUT_H */



/*
LocalWords: Alexios doc kludgy legalese otnotesize autoconfig alexios Exp
LocalWords: bbs matic printlongfile GPL ifndef VER endif ASCIIVARCHAR uint
LocalWords: VARCHAR tt OFL ANSIENABLE WAITTOCLEAR em AFTERINPUT co subst
LocalWords: INHIBITVARS PROTECTVARS vars varname varcalc struct substvar
LocalWords: Initialise sysvar init addsubstvar initsubstvars sv bbstitle
LocalWords: int datatype param XLATION de emud logon signup ifdef fd fname
LocalWords: setxlation printf mbk horrific kbytes num sprompt stg Megistos
LocalWords: vsprintf interally buf errno catfile printfile inp ORred
LocalWords: resetblocking clearflags setansiflag setwaittoclear setflags
LocalWords: setclear
*/
