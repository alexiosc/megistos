/** @name    output.h
    @memo    Outputting data to the user
    @author  Alexios

    @doc
    
    This header file includes functions used to send output to the user, and to
    control how this output is sent. It largely implements high-level
    functions, with the really low-level ones abstracted away (they're
    horrible, ugly and kludgy, anyway).

    Original banner, legalese and change history follow.

    {\footnotesize
    \begin{verbatim}

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
 * Revision 1.2  2001/04/16 21:56:28  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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

\end{verbatim}
} */

/*@{*/


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif

#ifndef OUTPUT_H
#define OUTPUT_H


#define _ASCIIVARCHAR '@'
#define _VARCHAR      0x7f


extern char   out_buffer[8192];	/** Temporary output buffer */
extern uint32 out_flags;	/** Output flags ({\tt OFL_x} flags) */


/** @name Output flags
    @filename OFL_flags

    @memo Output flags.

    @doc These flags control the behaviour of the low-level output subsystem.

    \begin{description}
    
    \item[{\tt OFL_ANSIENABLE}] If this flag is set, ANSI output is
    enabled. Actually, the flag works the other way round: if it's clear, ANSI
    directives are stripped from all output.

    \item[{\tt OFL_WAITTOCLEAR}] Set to indicate that, if a clear screen ANSI
    directive is received, and this does not happen {\em immediately} a user
    input request, a screen pause will be forced. This is done to make sure
    that the user can see all output of the system. If even a single character
    (even white space or ANSI directives) has been output to the user between
    the user's last input and the screen clear, the pause will be forced. For
    that reason, try to place clear screen directives at the top of message
    prompts.

    \item[{\tt OFL_AFTERINPUT}] Set by the low-level input subsystem to
    indicate that user input has just been received. This is used, among other
    things, in co-operation with the flag above to generate screen pauses.

    \item[{\tt OFL_INHIBITVARS}] Substitution variables are variables enclosed
    in at-signs. These variables will be replaced by their value before being
    printed. For instance, you can issue the name of the BBS by using {\tt
    @BBS@}, and the current time using {\tt @TIME@}. Setting this flag inhibits
    interpretation of at-signs as variable delimiters. Effectively, no variable
    substitution will occur. This is useful as a security measure. You
    certainly don't want users to be able to use substitution variables in
    their messages or pages. It could be used by crackers to confuse people or
    for `social engineering'.

    \item[{\tt OFL_PROTECTVARS}] If the above flag is clear, you can set this
    flag to partially inhibit variable substitution to {\em only} system
    prompts. Expansion in user-contributed material will not occur.

    \end{description} */
/*@{*/

#define OFL_ANSIENABLE  0x01	/** Enable ANSI output */
#define OFL_WAITTOCLEAR 0x02	/** Pause before clearing screen */
#define OFL_AFTERINPUT  0x04	/** First output after an input */
#define OFL_INHIBITVARS 0x08	/** Do not interpret substitution variables */
#define OFL_PROTECTVARS 0x10	/** Only interpret subst vars inside prompts */

/*@}*/


/** Substitution variable record

    This is used in two ways. Internally, it represents one record in the
    substitution variable registry. Externally, i.e. within modules, it can be
    used to register new, local substitution variables. Most of the larger
    modules do this to provide extra flexibility for customisation. There are
    three fields here: {\tt varname} is the string name of the variable (in
    upper case by convention); {\tt varcalc} is the function executed to return
    the value of the variable; and {\tt next} is only used internally to make a
    linked list of variables. */

struct substvar {
  char *varname;	   /** Name of substitution variable (upper case) */
  char *(*varcalc)(void);  /** Function that returns variable contents */
  void *next;		   /** Next handler in linked list */
};


/** Initialise output subsystem.

    Prepares for output to the user by opening the system prompt block ({\tt
    sysvar}), initialising substitution variables, and giving default values to
    the output flags. */

void out_init();


/** Shut down output to the user.

    Nothing much to this function, really. Almost everything is handled by the
    operating system, anyway. */

void out_done();


/** Initialise substitution variables.

    This function is called by {\tt out_init()}, which is in turn called by
    {\tt mod_init()}. You shouldn't have to call it yourself. It adds a wide
    collection of built-in, system-wide substitution variables, using calls to
    out_addsubstvar().
    
    @see out_substvar(). */

void out_initsubstvars ();


/** Install a new substitution variable.

    This function may be called from within your own modules to install new,
    local substitution variables. This function only adds a single
    variable. You might find it handy to add multiple variables by using this
    little trick:

    \begin{verbatim}
    struct substvar table []={
            {"BBS",sv_bbstitle,NULL},
            {"COMPANY",sv_company,NULL},
            {"ADDRESS1",sv_address1,NULL},
            {"",NULL,NULL}
    };
    
    int i=0;
    while(table[i].varname[0]){
            out_addsubstvar(table[i].varname,table[i].varcalc);
            i++;
    }
    \end{verbatim}

    This has the additional advantage of reusing the {\tt struct substvar}
    datatype for our own, vile purposes. Note how the {\tt next} (i.e. the
    third) field isn't used here.

    @param name The name of the substitution variable, as a string. You can
    either specify the name with the enclosing at-signs {\tt @}, or plain. The
    function will add any missing at-signs internally.

    @param varcalc A function of that returns a string. This function will be
    called in response to encountering a variable {\tt name}. The return value
    of the function will used instead of the variable. This allows pretty
    complex functionality.
    
    @see out_initsubstvars(). */

void out_addsubstvar(char *name, char *(*varcalc)(void));


/** Control character translation.

    This function controls how characters will be translated, if at all.

    @param mode The number of the translation table to use for both input and
    output characters. Alternatively, one of the following:

    \begin{description}

    \item[{\tt XLATION_OFF}] Disables automatic translation. This is necessary
    before running software that talks to the user (or some client) in binary,
    or simply to display something to the user without translation (though I
    can't think of a reason at 2am).

    \item[{\tt XLATION_ON}] Enables automatic translation, using whatever table
    used to be active at the time of de-activation. Useful for turning
    translation back on (see above).

    \end{description}.

    Please bear in mind that the translation itself is done my {\tt emud}, and
    so any settings are persistent throughout the user's session with the
    system. The translation table is initialised by {\tt emud} itself in the
    beginning, so don't change it unless you can guarantee the user will be
    able to read whatever you're sending!

    Currently, the only use for {\tt XLATION_OFF} and {\tt XLATION_ON} is to
    disable (temporarily) translation while a binary file transfer protocol
    (like Z-Modem) is running. The only use for the function itself is during
    the logon or signup processes, or after changing translation preferences in
    the Account module. */

void out_setxlation(int mode);

#define XLATION_OFF -1		/* Disable automatic translation */
#define XLATION_ON  -2		/* Re-enable automatic translation */



#ifndef OUTPUT_O


/** Format and display a prompt.

    Ah, the building block of every module in the system. This is the function
    that performs almost all of the output of your average module. It works in
    much the same was as {\tt printf()}. Unlike the omnipresent C function,
    however, {\tt prompt()} doesn't use a string format string, but a {\tt
    number}. The number indices one of the prompts inside the currently active
    prompt block. These indices have symbolic names attached to them, that are
    also defined in C headers. A prompt block called {\tt test.mbk} containing
    a prompt called HELLO would thus have an include file {\tt test.h} with
    something like {\tt #define HELLO 4}.

    The {\tt prompt()} function takes just this symbolic name for a prompt,
    where it obtains the format string. Most prompts have no format specifiers,
    and thus take no arguments, just like you can use {\tt printf()} to print a
    string without formatting numbers et cetera inside it. Format specifiers
    within prompt blocks are exactly the same as those used by {\tt printf()}
    and friends. The same rules about number and type of additional arguments
    hold here, too.

    The format specifiers are substituted with formatted strings, numbers (and
    what have you) {\em before} anything else. Variable substitution, line
    wrapping, et cetera happen immediately afterwards.

    This function is not without its limits. Expect horrific breakage if the
    prompt is longer than 8 kbytes. Actually, the breakages may occur somewhere
    between 8 and 16 kbytes. This is a reasonable limit: given an 80 by 25 text
    mode, 8 kbytes is around four {\em completely} full screens. If you need to
    print something this large, you're probably doing something wrong (try
    using the Menu Manager, which prints out the contents of entire files
    without size limitations).

    @param num The prompt number to use.

    @see printf(), sprompt(), print(), sprint(). */

void prompt (int num,...);


/** Format a prompt and store it in a string. 

    This function behaves in exactly the same way as {\tt prompt()}, but stores
    the formatted text in a string, instead of printing it out directly. All
    formatting is performed, as per {\tt prompt()}. The string is suitably
    formatted based on the current user's preferences (e.e. screen width and
    height).

    @see prompt(), printf(), print(), sprint(). */

void sprompt (char *stg, int num,...);


/** Format and print a string.

    This is the equivalent of {\tt printf()} in the context of Megistos. It
    performs {\em exactly} like {\tt printf()}, which is small wonder,
    considering it uses {\tt vsprintf()} interally.

    You {\em should not} use this function to print literal strings. BBS
    internationalisation and customisation depend on having all strings inside
    prompt blocks. Okay, so we don't always follow this rule, but we try to,
    and we (usually) only print white space.

    `Why is this function here, then', I hear you ask (among death threats and
    other severe complaints). It's useful for formatting and printing strings
    that you've previously constructed from prompts and stored for
    later. Really, it {\em does} have its uses.

    Like all of the output functions in this subsystem, {\tt print()} does line
    wrapping, justification, et cetera in order to print out your string. This,
    of course, depends on your wishes, as embedded within the string in the
    form of format directives.

    @param buf A string with zero or more format specifiers, followed by zero
    or more additional arguments based on the number and type of format
    specifiers.

    @see printf(), sprint(), prompt(), sprompt(). */

void print (char *buf,...);


/** Format and store a string.

    This function works exactly like {\tt print()}, but stores its results in a
    string instead of printing them.

    @param stg The string to store the formatted text in.
    
    @param buf A string with zero or more format specifiers, followed by zero
    or more additional arguments based on the number and type of format
    specifiers.

    @see printf(), print(), prompt(), sprompt(). */

void sprint (char *stg,char *buf,...);

#endif /* OUTPUT_O */

#ifdef WANT_SEND_OUT


/** Low-level string output.

    This function has exactly the same syntax and semantics as {\tt
    write()}. The reason for its existence is complex: if non-blocking I/O is
    used, excessive output may overrun the OS output buffer. Under Linux, this
    is 4 kbytes, a fact that can account for long listings getting garbled. So
    we loop, trying to write as much of the string as we can, waiting a bit
    between writes --- but only if the entire string couldn't be sent. The
    performance impact should be minimal, as the bottleneck is likely to be the
    user's bandwidth anyway.

    The trick is to wait for the output buffer to have some more space, unless
    of course we've managed to send the whole string in the first attempt. This
    depends on bandwidth. It doesn't need to be big for the Linux console.
    Modems can't send out information as fast, so we have to wait more. To
    cover all cases, we wait for a pretty long time. This might produce
    slightly jerky output on the console (though I personally can't detect it),
    but won't easily be detectable on a modem.

    I really want to do away with this horror. It's a great big kludge and it
    stinks, and I hate it. Please, {\em please}, tell me there's a nice,
    elegant, standard way to either flush the output buffer and wait till it's
    empty, or to get a measure of how full the output buffer is.

    @param fd A file descriptor to write to.

    @param s A string to write to {\tt fd}.

    @param count The number of bytes to write to {\tt fd}.

    @return The number of bytes written, as returned by internal calls to {\tt
    write()}. */

int out_send (int fd, char *s, int count);

#endif /* WANT_SEND_OUT */


/** Print a file.

    This function causes a file to be opened and its contents printed using
    successive calls to the {\tt print()} function. Any substitution variables
    within the file will be expanded, and any formatting directives will be
    obeyed as usual.

    @param fname The filename of the file to print. 

    @return One on success, zero if opening the file failed, in which case {\tt
    errno} will contain the exact error. 

    @see out_printlongfile(), out_catfile(). */

int out_printfile (char *fname);


/** Print a file.

    Works exactly like {\tt out_printfile()}. This function, however, puts the
    terminal in non-blocking mode. The user may press a special control
    character (Enter, New Line, Line Feed, Escape, Control-C or Control-O) to
    stop the transmission. The terminal is reset to its previous mode of
    operation after the function finishes, using {\tt inp_resetblocking()}. Do
    not use this latter function with {\tt out_printlongfile()}.

    @param fname The filename of the file to print. 

    @return One on success, zero if opening the file failed, in which case {\tt
    errno} will contain the exact error.

    @see out_printfile(), out_catfile(). */

int out_printlongfile (char *fname);


/** Print a file verbatim.

    Works a bit like {\tt out_printfile()}, but does {\em not} format the file
    before output. Substitution variables will not expand, formatting
    directives will be printed as-is, et cetera.

    @param fname The filename of the file to print. 

    @return One on success, zero if opening the file failed, in which case {\tt
    errno} will contain the exact error.

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


/** Set or clear the {\tt OFL_ANSIENABLE} flag.

    This function is only a legacy interface to the {\tt out_setflags} or {\tt
    out_clearflags} macros. It's used to control the {\tt OFL_ANSIENABLE} flag,
    which in turn controls whether or not ANSI directives are stripped before
    output.

    @param f Causes the flag to be set if non-zero, or to be cleared if
    zero. */

#define out_setansiflag(f) __out_setclear(f,OFL_ANSIENABLE)


/** Set or clear the {\tt OFL_WAITTOCLEAR} flag.

    This function is only a legacy interface to the {\tt out_setflags} or {\tt
    out_clearflags} macros. It's used to control the {\tt OFL_WAITTOCLEAR}
    flag. This flag controls whether or not pauses will be forced before screen
    clears to make sure the user has time to read the last characters of the
    previous screen.

    @param f Causes the flag to be set if non-zero, or to be cleared if
    zero. */

#define out_setwaittoclear(f) __out_setclear(f,OFL_WAITTOCLEAR)

#endif /* OUTPUT_H */

/*@}*/


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
