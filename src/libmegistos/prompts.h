/** @file    prompts.h
    @brief   Prompt block management
    @author  Alexios

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     prompts.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Interface to prompts.c                                       **
 **            files.                                                       **
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
 * $Id: prompts.h,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: prompts.h,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2004/05/03 05:36:48  alexios
 * Added size and data fields to the promptblock_t struct to allow
 * message blocks to reside in memory.
 *
 * Revision 1.4  2003/09/27 20:32:00  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 15:19:19  alexios
 * Added the message block magic number.
 *
 * Revision 0.4  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/05 10:52:05  alexios
 * Removed definitions of xlgetmsg() and xlgetmsglang(), since
 * emud now performs all translations on the fly.
 *
 * Revision 0.2  1997/09/01 10:25:46  alexios
 * Added macros to call getmsglang() and getmsg() and translate
 * the returned string according to the currently set
 * xlation_table.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 *

@endverbatim
*/

#ifndef RCS_VER 
#define RCS_VER "$Id: prompts.h,v 2.0 2004/09/13 19:44:34 alexios Exp $"
#endif


#ifndef PROMPTS_H
#define PROMPTS_H


/** @defgroup prompts Accessing Prompt Blocks

    Prompt (or message) blocks are effectively configuration files. In their
    source form, they contain hierarchies of options or messages that are output
    to the user. In their compiled form, they are reduced to key-value
    pairs. This header file allows you to read these key-value pairs and act on
    them.

    Keys aren't really keys, they're integer indices into the file. However, the
    prompt block indexer is nice enough to make a header file with definitions
    for each of those numeric indices. The symbolic names it chooses are the
    same as the symbolic names of the options themselves.

    The low-level, compiled prompt block format is bound to change soon, so I
    won't go into much detail just yet.

    By the way, the name `prompt block' originates from the Major BBS. Even on
    Major, it was somewhat inaccurate, as prompt blocks didn't just contain
    prompts.

@{ */


/** MBK magic */

#define MBK_MAGIC "MMBK"

typedef struct {
	uint32 offset;		/**< Offset to the prompt string */
	char   id[28];		/**< String ID of the prompt */
} idx_t;


/** A prompt block descriptor.

    This is the structure used to hold state et cetera for an open prompt
    block. The data type is instantiated by <tt>msg_open()</tt>. This data type
    should be considered opaque.

*/

typedef struct {
	char      fname[64];	/**< Filename of the prompt block  */
	FILE     *handle;	/**< Open prompt block file */
	uint32_t  indexsize;	/**< Size of prompt index */
	uint32_t  language;	/**< Currently active language */
	uint32_t  langoffs[NUMLANGUAGES]; /**< Indices to where languages start */
	idx_t    *index;	/**< Prompt index structure */
	uint32_t  size;		/**< Size of data block. */
	char     *data;		/**< Prompt data */
} promptblock_t;


extern char           *msg_buffer;  /**< Used internally to format prompts */
extern promptblock_t  *msg_cur;     /**< The currently active block */
extern promptblock_t  *msg_last;    /**< The `other' block */
extern promptblock_t  *msg_sys;     /**< The system block  */


/** Names of all the languages supported */

extern char msg_langnames [NUMLANGUAGES] [64];


/** The number of defined languages. */

extern int msg_numlangs;


/** Initialise prompt subsystem.
    
    Load language descriptions, number of available languages, et cetera. You
    should not call this directly, use mod_init() instead. */

void msg_init();


/** Open a prompt block.

    Opens a prompt block file, validates its magic number, reads its index and
    creates a descriptor for it. The descriptor is automatically allocated by
    the function, just like @c fopen() allocates a new <tt>FILE</tt>.

    The current block (::msg_cur) becomes the last block (::msg_last). The newly
    opened block becomes the current block. If the function is called from a
    user-servicing module, the user's language is also selected for subsequent
    prompting.

    @param name The @e basename of the prompt block file, without its @c .mbk
    suffix. By convention, prompt blocks are named the same as the directory of
    their modules (and, in most cases, the main module source file). This isn't
    binding, though.

    @return A pointer to a freshly allocated prompt block descriptor. This
    function always returns on success. Failure causes the process to halt with
    a fatal error. */

promptblock_t *msg_open(char *name);


/** Set the current prompt block.

    Sets the current prompt block. All subsequent accesses will refer to this
    block, which must be a descriptor returned by msg_open(). As a side effect,
    the current block (::msg_cur) becomes the last block (::msg_last). The
    specified block becomes the current block.

    This function is used to switch between prompt blocks. Usually, each module
    has its own, single block. However, there are times when you need to access
    briefly another block and this is where this function comes in. The system
    block, ::msg_sys (automatically opened) is one such example.

    @param blk A prompt block descriptor returned by a previous call to
    msg_open().

    @see msg_open(), msg_reset(). */

void msg_set(promptblock_t *blk);


/** Return to the last prompt block used.

    This function simply swaps the current and last prompt block descriptors
    (::msg_cur and ::msg_last). This is a quick way to revert to the previous
    message. System functions that access prompts in the system block use this
    function to revert immediately to the one the user assumes is active,
    without needing to have access to its descriptor. */

void msg_reset();


/** Access a prompt by index and language.

    This is the generic prompt access function. It's used by most other
    prompt access functions.

    @param num The symbolic ID of the prompt.

    @param language The language you want to access.

    @return A null terminated string pointer to the prompt. */

#define msg_getl(num,lang) msg_getl_bot(num,lang,0)


/** Low level function to access a prompt by ID and language.

    This is the low level function to read a prompt by its ID @e and index.

    @deprecated Don't use this one, use the macro #msg_getl instead. It'll save
    you some effort.

    @param num The numeric index of the prompt.

    @param language The language you want to access.

    @return A null terminated string pointer to the prompt. */

char *msg_getl_bot(int num, int language, int checkbot);


/** Access a prompt by index.

    This is a macro that calls msg_getl() that retrieves a prompt by index,
    using the currently active language.

    @param num The prompt index. You will want to use the symbolic name here.

    @return A null terminated string pointer to the prompt. */

#define msg_get(num)  msg_getl_bot(num,(msg_cur->language),0)


/** Get the name of a unit.

    This function is similar to msg_getl(), with a catch: it retrieves either of
    two messages, based on the value of a variable. The function is used to
    format a unit's singular or plural form based on a value. For instance, you
    wouldn't want to say `1 Kbytes', and `1 Kbyte(s)' is an ugly way to avoid
    the problem. This function solves the problem.

    The way to do it is to define two little prompt blocks. The first holds the
    word `Kbyte', the second the word `Kbytes'. Your module uses this function
    to access the needed form of the unit and includes it in a message given to
    the user. Needless to say, this function can be used for anything that needs
    dual, value-selected prompting. User sexes are just one example.

    @param num The prompt index. You will want to use the symbolic name here.

    @param value The value mentioned above. If <tt>value</tt> is anything but one,
    <tt>num</tt> will be increased by one.

    @param language The language of the retrieved unit name. 

    @return A null terminated string pointer to the prompt. */

char *msg_getunitl(int num, int value, int language);


/** Get the name of a unit in the current language.

    This is a macro that calls msg_getunitl(). It retrieves a unit name, but
    uses the currently active language to save you a lot of typing.

    @param num The prompt index. You will want to use the symbolic name here.

    @param val The value mentioned above. If <tt>val</tt> is anything but
    one, string <tt>num+1</tt> will be retrieved instead.

    @return A null terminated string pointer to the prompt. */

#define msg_getunit(n,val) msg_getunitl((n),(val),msg_cur->language)


/** Close a prompt block

    Closes the specified prompt block, deallocates its descriptor. Any
    subsequent calls to prompt retrieval function will have unpredictable
    results, unless you open a new block, set another one as the current, or
    use <tt>msg_last()</tt>.

    @param blk The prompt block descriptor to close.  */

void msg_close(promptblock_t *blk);


/** Parse a <tt>long int</tt> in a prompt.

    Retrieves the requested prompt and parses a long integer contained
    therein. This function is used to extract configuration options from
    prompts. The number is checked to ensure it's within a user-defined range
    of values. If not, a fatal error is issued.

    @param num The prompt ID.

    @param floor The minimum acceptable value.

    @param ceiling The maximum acceptable value. 

    @return The parsed value. */

long msg_long(int num, long floor, long ceiling);


/** Parse a base-16 <tt>unsigned int</tt> in a prompt.

    Retrieves the requested prompt and parses a hexadecimal unsigned integer
    contained therein. This function is used to extract configuration options
    from prompts. The number is checked to ensure it's within a user-defined
    range of values. If not, a fatal error is issued.

    @param num The prompt ID as a symbolic name (constant).

    @param floor The minimum acceptable value.

    @param ceiling The maximum acceptable value. 

    @return The parsed value. */

unsigned msg_hex(int num, unsigned floor, unsigned ceiling);


/** Parse an <tt>int</tt> in a prompt.

    Retrieves the requested prompt and parses an integer contained therein. This
    function is used to extract configuration options from prompts. The number
    is checked to ensure it's within a user-defined range of values. If not, a
    fatal error is issued.

    @param num The prompt index. You will want to use the symbolic name here.

    @param floor The minimum acceptable value.

    @param ceiling The maximum acceptable value. 

    @return The parsed value. */

int msg_int(int num, int floor, int ceiling);


/** Parse a yes/no configuration prompt.

    Retrieves the requested prompt and parses a yes/no boolean value contained
    therein. This function is used to extract configuration options from
    prompts.

    @param id The prompt index as a symbolic name (constant).

    @return The parsed value: non-zero if `yes', zero if `no'. */

int msg_bool(int num);


/** Parse a single-character configuration prompt.

    Retrieves the requested prompt and parses a single character value contained
    therein. This function is used to extract configuration options from
    prompts.

    @param num The prompt index. You will want to use the symbolic name here.

    @return The parsed value: a single character. */

char msg_char(int num);


/** Copy a configuration prompt to a string.

    Retrieves the requested prompt, allocates a new string to hold its value,
    and returns the newly allocated string.  This function is used to extract
    configuration options from prompts.

    There is no need for you to allocate space for this string or to copy it
    over, this is done for you. You <em>will</em> need to free it once you're
    done with it, though, to avoid memory leaks.

    @param num The prompt index. You will want to use the symbolic name here.

    @return The parsed value: a single character. */

char *msg_string(int msgnum);


/** Extract a token from a configuration prompt.

    Retrieves and parses the requested prompt, trying to match it against a
    user-supplied list of tokens. This function is used to extract
    multiple-choice configuration options from prompt.

    The list of tokens is represented by one or more string arguments to the
    function. As this is perhaps the most complex of the parsing functions, here
    is an example that includes error recovery:
    
@verbatim
int value = tokopt (COLOUR, "DARKBLUE", "DARKGREEN",
                            "DARKCYAN", "DARKRED",
                            "DARKMAGENTA", "BROWN", "GREY",
                            "DARKGREY", "BLUE", "GREEN",
		            "CYAN", "RED", "MAGENTA", "YELLOW", "WHITE", NULL);

if (value < 1) error_fatal ("Option COLOUR has unacceptable value.");
@endverbatim

    @param num The prompt index. You will want to use the symbolic name here.

    @param toklst An arbitrary number of one or more string pointers. The last
    one <em>must be</em> <tt>NULL</tt>.

    @return Zero if the token didn't match any in the file. A value <tt>i</tt>
    greater than zero denoting a match against the <tt>i</tt>-th token supplied
    as an argument. */

int msg_token(int msgnum,char *toklst, ...);


/** Set the active language.

    Specifies the language of all subsequently retrieved prompts. Only the
    current language in the current and system blocks is changed (::msg_cur,
    ::msg_sys). The last block (::msg_last) is not touched at all.

    @param l The new language to set.  */

void msg_setlanguage(int l);


#endif /* PROMPTS_H */

/*@}*/


/*
LocalWords: Alexios doc BBS legalese otnotesize alexios Exp bbs GPL emud
LocalWords: xlgetmsg xlgetmsglang getmsglang getmsg xlation ifndef VER MBK
LocalWords: endif MMBK tt msg promptblock struct fname indexsize int fopen
LocalWords: langoffs NUMLANGUAGES promptblkock param em basename mbk blk
LocalWords: rstmbk num getl getmsgl Kbytes Kbyte getunitl getpfix
LocalWords: getpfixlang clsmsg bool msgnum tokopt COLOUR DARKBLUE DARKCYAN
LocalWords: DARKGREEN DARKRED DARKMAGENTA DARKGREY CYAN toklst setlanguage */
