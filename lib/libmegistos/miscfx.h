/** @file    miscfx.h
    @brief   Miscelaneous functions
    @author  Alexios

    These functions are declared here because, frankly, they wouldn't fit
    anywhere else. Some of them should be considered deprecated. All in due
    course, I suppose.

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     miscfx.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Interface to miscfx.h, implementing various useful functs.   **
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
 * Revision 1.5  2003/12/19 13:25:19  alexios
 * Updated include directives.
 *
 * Revision 1.4  2003/09/27 20:31:51  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/07/18 21:13:24  alexios
 * Supplied own version of usleep for borken (sic) bastard
 * operating systems that don't define it.
 *
 * Revision 0.7  1998/12/27 15:19:19  alexios
 * Moved functions that didn't really belong here to other
 * header files.
 *
 * Revision 0.6  1998/08/14 11:23:21  alexios
 * Added long-awaited function stripspace() to remove leading
 * and trailing white space from a string.
 *
 * Revision 0.5  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/03 00:29:40  alexios
 * Optimised stgxlate for speed; created a new translation
 * function, faststgxlate that is suitable for very fast
 * applications with complete translation tables.
 *
 * Revision 0.3  1997/09/12 12:45:25  alexios
 * Added lowerc() and upperc() functions.
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Removed bladcommand(), replaced it by bbsdcommand() (different
 * syntax).
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 *

@endverbatim
} */

#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#ifndef MISCFX_H
#define MISCFX_H

#define WANT_TIME_H 1
#define WANT_UNISTD_H 1
#include <megistos/bbsinclude.h>



/** @defgroup miscfx Miscellaneous Functionality

@{*/


#define PHONETIC "\000\000\000\000\000\000\000\000"  /* 0-7              */ \
                 "\000\000\000\000\000\000\000\000"  /* 8-15             */ \
                 "\000\000\000\000\000\000\000\000"  /* 16-23            */ \
                 "\000\000\000\000\000\000\000\000"  /* 24-31            */ \
                 "\000\000\000\000\000\000\000\000"  /* 32-39    !"#$%&' */ \
                 "\000\000\000\000\000\000\000\000"  /* 40-47   ()*+,-./ */ \
                 "\060\061\062\063\064\065\066\067"  /* 48-55   01234567 */ \
                 "\070\071\000\000\000\000\000\000"  /* 56-63   89:;<=>? */ \
                 "\000\101\102\103\104\105\106\107"  /* 64-71   @ABCDEFG */ \
                 "\110\111\112\113\114\115\116\117"  /* 72-79   HIJKLMNO */ \
                 "\120\121\122\123\124\125\126\127"  /* 80-87   PQRSTUVW */ \
                 "\130\131\132\000\000\000\000\000"  /* 88-95   XYZ[\]^_ */ \
                 "\000ABCDEFG"                       /* 96-103  `abcdefg */ \
                 "HIJKLMNO"                          /* 104-111 hijklmno */ \
                 "PQRSTUVW"                          /* 112-119 pqrstuvw */ \
                 "XYZ\000\000\000\000\000"           /* 120-127 xyz{|}~  */ \
                 "ABGDEZIT"                          /* 128-135 ABGDEZHU */ \
                 "IKLMNXOP"                          /* 136-143 IKLMNJOP */ \
                 "RSTYFXCO"                          /* 144-151 RSTYFXCV */ \
                 "ABGDEZIT"                          /* 152-159 abgdezhu */ \
                 "IKLMNXOP"                          /* 160-167 iklmnjop */ \
                 "RSSTYFXC"                          /* 168-175 rsstyfxc */ \
                 "\000\000\000\000\000\000\000\000"  /* 176-183 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 184-191 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 192-199 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 200-207 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 208-215 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 216-223 graphics */ \
                 "OAEIIIOY"                          /* 224-231 waehiioy */ \
                 "YO\000\000\000\000\000"            /* 232-239 yv       */ \
                 "\000\000\000\000\000\000\000\000"  /* 240-247 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 248-255 graphics */


#define LATINIZE "\000\000\000\000\000\000\000\000"  /* 0-7              */ \
                 "\000\000\000\000\000\000\000\000"  /* 8-15             */ \
                 "\000\000\000\000\000\000\000\000"  /* 16-23            */ \
                 "\000\000\000\000\000\000\000\000"  /* 24-31            */ \
                 "\000\000\000\000\000\000\000\000"  /* 32-39    !"#$%&' */ \
                 "\000\000\000\000\000\000\000\000"  /* 40-47   ()*+,-./ */ \
                 "\000\000\000\000\000\000\000\000"  /* 48-55   01234567 */ \
                 "\000\000\000\000\000\000\000\000"  /* 56-63   89:;<=>? */ \
                 "\000\000\000\000\000\000\000\000"  /* 64-71   @ABCDEFG */ \
                 "\000\000\000\000\000\000\000\000"  /* 72-79   HIJKLMNO */ \
                 "\000\000\000\000\000\000\000\000"  /* 80-87   PQRSTUVW */ \
                 "\000\000\000\000\000\000\000\000"  /* 88-95   XYZ[\]^_ */ \
                 "\000\000\000\000\000\000\000\000"  /* 96-103  `abcdefg */ \
                 "\000\000\000\000\000\000\000\000"  /* 104-111 hijklmno */ \
                 "\000\000\000\000\000\000\000\000"  /* 112-119 pqrstuvw */ \
                 "\000\000\000\000\000\000\000\000"  /* 120-127 xyz{|}~  */ \
                 "ABGDEZHU"                          /* 128-135 ABGDEZHU */ \
                 "IKLMNJOP"                          /* 136-143 IKLMNJOP */ \
                 "RSTYFXCV"                          /* 144-151 RSTYFXCV */ \
                 "abgdezhu"                          /* 152-159 abgdezhu */ \
                 "iklmnjop"                          /* 160-167 iklmnjop */ \
                 "rsstyfxc"                          /* 168-175 rsstyfxc */ \
                 "\000\000\000\000\000\000\000\000"  /* 176-183 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 184-191 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 192-199 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 200-207 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 208-215 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 216-223 graphics */ \
                 "vaehiioy"                          /* 224-231 waehiioy */ \
                 "yv\000\000\000\000\000\000"        /* 232-239 yv       */ \
                 "\000\000\000\000\000\000\000\000"  /* 240-247 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 248-255 graphics */



/** A simple way to get (pseudo-)random numbers

    This macro is just a wrapper for the C function <tt>rand()</tt>.

    @warning DO NOT USE THIS FUNCTION FOR RANDOMNESS-SENSITIVE TASKS
    LIKE KEY GENERATION.

    @param num The maximum random number (plus 1) that will be generated.

    @return A (pseudo-)random number between 0 and <tt>num</tt>-1.

    @see randomize() */

#define rnd(num)      (int)((long)rand()%(num))


/** Seed the random number generator.

    A macro that uses the current time and process ID to seed the pseudo-random
    number generator. Future versions should look for the @c /dev/random or @c
    /dev/urandom devices and use those, if they're available.

    @see rnd() */
    
#define randomize()   srand((unsigned)time(NULL)+(unsigned)getpid())


/** Returns the minimum of two numbers.

    A bog-standard but precious little macro.

    @param a A number of any type.
    @param b A number of any type.
    
    @return The minimum of the two numbers.  */

#define min(a,b)      (((a)<(b))?(a):(b))


/** Returns the maximum of two numbers.

    A bog-standard but precious little macro.

    @param a A number of any type.
    @param b A number of any type.
    
    @return The maximum of the two numbers.  */

#define max(a,b)      (((a)>(b))?(a):(b))


#define phonetic(s)   stgxlate(s,PHONETIC)
#ifdef GREEK
#define latinize(s)   stgxlate(s,LATINIZE)
#define tolatin(c)    (LATINIZE[c]?LATINIZE[c]:(c))
#else
#define latinize(s)   (s)
#define tolatin(c)    (c)
#endif


/** Safe memory allocation.

    Attempts to allocate memory, halting the module with an error_fatal() if
    memory couldn't be allocated. The arguments are identical to those of
    malloc(), which this function calls internally.

    @param size The number of bytes to allocate.

    @return a pointer to the block of memory allocated. This function never
    returns <tt>NULL</tt>. If an allocation error occurs, the current program is
    terminated. */

void *alcmem (size_t size);


/** Convert a string to lower case.

    @param s A null-terminated string.

    @return The string <tt>s</tt> with all upper case characters converted to
    lower case.

    @see upperc() */

char *lowerc (char *s);


/** Convert a string to upper case.

    @param s A null-terminated string.

    @return The string <tt>s</tt> with all lower case characters converted to
    upper case.

    @see lowerc() */

char *upperc (char *s);


/** Strips leading and trailing white space.

    @param s A null-terminated string.

    @return The string <tt>s</tt> with all leading and trailing white space
    removed.

    @see lowerc() */

char *stripspace(char *s);


/** Case-insensitive initial substring match.

    @param shorts A string to search for.

    @param longs The string in which to search.

    @return Returns non-zero if <tt>shorts</tt> was found at the beginning of {\tt
    longs}. Zero is returned otherwise. Case-insensitive comparison is used.

    @see sameas()
*/

int sameto(char *shorts, char *longs);

/** Case-insensitive string match.

    @param stg1 The first string.

    @param stg2 The second string.

    @return Returns non-zero if the two strings are the same, zero if
    not. Case-insensitive comparison is used.

    @see sameto() */

int sameas(char *stg1, char *stg2);


/** Zero-pads a string array.

    This function zeroes any free space within an array holding a
    null-terminated string. Only characters after the terminating null will be
    terminated (including the terminating null, unless the moon is in its third
    quarter).

    This function appears inane, and it is (partially). The first version was
    written in 1992, when I was dealing with Major BBS modules. The database
    system, Novell's <em>BTrieve</em>, didn't know about terminating nulls in
    strings and the C API didn't care. If a key was 24 bytes long, equality
    meant an identical 24 bytes. So, all database keys had to be zero-padded to
    avoid some very obscure bugs. These days, <tt>zeropad</tt> is only useful
    where sensitive information is likely to be held in memory and we don't want
    it written to disk along with a string. But it's much easier (not to mention
    faster) to use <tt>bzero()</tt> or <tt>memchr()</tt> to do the trick.

    @param s The string array to zero-pad.

    @param count The size of the string array.

    @return A pointer to <tt>s</tt>, with any post-null bytes zero-padded.

    @see bzero(), memchr() */

char *zeropad(char *s, int count);


/** Performs character-for-character string translation.

    @param s A string to translate.

    @param table A translation table. This is a <tt>char</tt> array with 256
    elements. Translation of character x is done by the expression
    <tt>table[x]!=0 ? table[x] : x</tt>. That is, the <tt>x</tt>-th element of
    <tt>table</tt> holds the new value of character with ASCII code <tt>x}. If
    the <tt>x</tt>-th element of <tt>table</tt> is zero, the character is not
    translated. This is done for convenience to the programmer.

    @return A pointer to <tt>s</tt> with the characters translated as above. It
    should be obvious that this is a <em>destructive</em> function! The translated
    string overwrites the original one. 

    @see faststgxlate() */

inline char *stgxlate(char *s, char *table);

/** Performs faster character-for-character string translation.

    @param s A string to translate.

    @param table A translation table. This is a <tt>char</tt> array with 256
    elements. Translation of character @c x is done by the expression {\tt
    table[x]}. Unlike <tt>stgxlate()</tt>, @e all characters will be translated.

    @return A pointer to <tt>s</tt> with the characters translated as above. It
    should be obvious that this is a <em>destructive</em> function! The translated
    string overwrites the original one. 

    @see stgxlate() */

inline char *faststgxlate(char *s, char *table);


/** Sends a command to the BBS daemon.

    This function composes a command to the BBS daemon, <tt>bbsd</tt>, and sends
    it. BBS commands perform certain restricted tasks, like throwing other BBS
    users off the system, et cetera.

    This is a low-level command. Most existing <tt>bbsd</tt> commands have
    individual functions to simplify the interface for the user.

    @param command The command to send to <tt>bbsd</tt>.

    @param tty The first argument of the <tt>bbsd</tt> command is always a BBS
    channel name, in the form of a TTY device name, without the
    <tt>"/dev/"</tt>. For instance, the third Linux virtual console would be
    identified as <tt>"tty3"</tt>.

    @param arg The second argument of the command.  */

int bbsdcommand(char *command, char *tty, char *arg);


/** Search a string for a set of keywords.

    This function uses case-sensitive searching (<tt>strstr()</tt> to locate any
    of a set of keywords within a string. Partial matching is done, so that, for
    instance, <tt>"word"</tt> will match <tt>"keywords"</tt>.
    
    @warning THE <tt>keywords</tt> ARGUMENT WILL BE DESTROYED IN THE PROCESS OF
    SEARCHING}.

    @param string The string to search in.

    @param keywords A string holding space-delimited keywords to search for.

    @return Non-zero if one of the keywords was found, zero if not. */

int search(char *string, char *keywords);


/** Executes a module.

    Runs an interactive, Megistos module or other subsystem.
    
    @param command The command to execute.
    
    @return The same values as <tt>system()</tt>.

    @see system() */

int runmodule(char *command);


/** Executes a command.

    Runs a UNIX command, making sure the module and BBS are aware of this for
    initialisation, charging, idling, statistics and other purposes. This is the
    best way to call external commands with minimal hassle.
    
    @param command The command to execute.
    
    @return The same values as <tt>system()</tt>.

    @see system() */

int runcommand(char *command);


/** Edit a file.

    Executes the visual or line editor (depending on user's settings) to edit a
    given file.

    The correct way to edit a file is to either create it in <tt>/tmp</tt>, or
    to make a symbolic link to it.

    @warning IF THE USER CANCELS THE EDITING PROCESS, <EM>THE FILE WILL BE
    DELETED</EM>.

    @param fname The full filename of the file to edit.

    @param limit The size limit of the file. BBS editors, unlike most other
    editors, can impose this limit on users.

    @return The same values as runmodule(), which are the same as
    <tt>system()</tt>. If the user saved the file, the <tt>fname</tt> will still
    exist and will contain the updated content. If the user chose to cancel the
    editing session without saving, <tt>fname</tt> will no longer exist. */

int editor(char *fname,int limit);


/** Call the menu manager.

    This function calls the menu manager from within a module. The menu manager
    will take the user to the specified page.

    @param page The name of a menu manager page to go to.
    
    @return The function never returns. */

void gopage(char *page);

#ifdef I_AM_MENUMAN
void mmgopage(char *page); /* This is for Menuman's use only */
#endif /* I_AM_MENUMAN */


/** Copy a file.

    A useful function to copy a file to another one. The semantics are almost
    identical to those of the shell command <tt>cp</tt>.

    @param source The filename of the source file.

    @param target Filename of the target file.
    
    @return Zero indicates success. Non-zero indicates an error, in which case
    <tt>errno</tt> will be set accordingly. */

int fcopy(char *source, char *target);


/** Sleep for a given number of microseconds.

    Some systems lack this particularly useful function. This is how we define
    it (the standard way, drawn from the standard include files). This is the
    actual documentation of the function from the person pages:

    The usleep() function suspends execution of the calling process for @c
    __usec microseconds.  The sleep may be lengthened slightly by any system
    activity or by the time spent processing the call.

    @param __usec The time delay in question.  */

/* Redeclare usleep() for some systems */
#ifndef HAVE_USLEEP
extern void usleep ((unsigned long __usec));
#endif /* HAVE_USLEEP */



/** Format a filename.

    This function formats a filename string for a subdirectory under the BBS
    prefix. The environment variables @c BBSPREFIX and @c PREFIX are first
    checked, followed by the BBS prefix defined at compile time.

    @param fmt A <tt>printf()</tt>-like format string, followed by any necessary
    parameters. The prefix will be automatically prepended to the format string
    to form the fully qualified filename.
    
    @return The fully qualified filename. */

#ifndef MISCFX_O
char *mkfname(char *fmt,...);
#endif /* MISCFX_O */



#endif /* MISCFX_H */

/*@}*/

/*
LocalWords: doc legalese otnotesize functs alexios Exp bbs usleep borken
LocalWords: stripspace GPL Optimised stgxlate faststgxlate lowerc upperc
LocalWords: bladcommand bbsdcommand ifndef VER endif UNISTD bbsinclude XYZ
LocalWords: ABCDEFG HIJKLMNO PQRSTUVW abcdefg hijklmno pqrstuvw xyz YO yv
LocalWords: ABGDEZIT ABGDEZHU IKLMNXOP IKLMNJOP RSTYFXCO RSTYFXCV abgdezhu
LocalWords: iklmnjop RSSTYFXC rsstyfxc OAEIIIOY waehiioy LATINIZE vaehiioy
LocalWords: tt rand em param num rnd int srand getpid min ifdef latinize
LocalWords: tolatin malloc alcmem sameas sameto stg BTrieve zeropad bzero
LocalWords: memchr inline bbsd dev arg strstr Megistos runmodule tmp fname
LocalWords: gopage cp errno fcopy usec
*/
