/*! @file     bbsmod.h
    @brief    Entry points for BBS modules.
    @author   Alexios

    This header defines the main entry (and exit) points for Megistos
    modules. It handles initialising different subsets of the API depending on
    the type of module.

    Please be aware that this part of the library is undergoing an almost
    complete redesign.

    Original banner, legalese and change history follow

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     bbsmod.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Interface to module functions bbsmod.c                       **
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
 * Revision 1.4  2003/09/27 20:28:07  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 15:19:19  alexios
 * Declare the BBS user's UID and GID.
 *
 * Revision 0.3  1998/07/26 21:17:06  alexios
 * Added structure to declare modules and their individual
 * functions, plus functions to initialise said structure.
 * The setprogname() function is necessary for proper error
 * reporting.
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




#ifndef BBSMOD_H
#define BBSMOD_H


/** @defgroup toplevel Top-Level Module Definitions and Handlers

    These functions define the main entry (and exit) points for
    Megistos modules. Code here handles initialising different subsets
    of the API depending on the type of module.

@{*/


/*! \struct mod_handler_t

    @brief Module handler.

    @doc This is how a module handler is defined. There is a @c priority
    attached to the <tt>main()</tt>-like function pointer @c handler. When
    calling multiple modules (e.g. when logging in or out), the handlers are
    called in order of <em>increasing</em> priority. The entry points are called
    with pairs of @c argc and @c argv arguments, just like @c main().

    This structure is used within ::mod_info_t.

    @see mod_info_t.
*/

typedef struct {
	int32 priority;		        /**< Priority of this handler */
	int (*handler)(int,char**);	/**< Handler function call */
} mod_handler_t;


/** High-level module descriptor.

    This structure should be defined for all modules of the BBS. It contains
    enough information to identify the module and its capabilities to the BBS
    library, which can then deal with some basic command-line arguments on the
    module's behalf, <em>a la</em> X toolkit.

    A module should call the function mod_setinfo() early in its
    initialisation. A properly initialised ::mod_info_t should be provided as
    argument. All string information in this structure should be filled in and
    pointing to permanently allocated string buffers. Handlers may be
    <tt>NULL</tt>, in which case the library considers the corresponding feature
    of the module not available and does not invoke it.

    The handler functions login(), run(), et cetera have the same form as good
    old <tt>main()</tt>: they are passed the usual @c argc and @c argv arguments
    and are expected to return an integer exit code. This is what the handlers
    do:

      - @c login. You can arrange for a (small) part of the module to run
        immediately after the user has authenticated themselves. This can be
        used, for instance, to advertise the module, provide the user with
        urgently needed information, perform registration or housekeeping
        chores, et cetera.

      - @c run is the main runtime part of the module, called when a user
        interactively enters. This is what gives the main module menu, waits for
        a selection and acts on it.

      - @c logout gets activated immediately before the user logs out of the
        system in a normal manner. This allows the module to say goodbye and
        perhaps provide some information. Log-out fortune cookies use this
        handler.

      - @c hangup gets activated immediately after the user hangs up, or is
        kicked out of the system by an operator. There should be no
        interactivity here, because the user is no longer on-line. However,
        housekeeping tasks may need to be performed upon the user's exit from
        the system. Please note that due to perverse situations and possible
        race conditions, the @c logout handler might be called <em>in
        addition</em> to the @c hangup handler. If you need to do housekeeping
        upon a user's exit, you should check if this has already been done by
        another handler. Quite often both @c hangup and @c logout handlers have
        the same tasks to perform, and thus may call the same function which
        checks an internal flag to ensure it hasn't been called before.

      - @c cleanup gets (typically) activated once daily to perform
        non-interactive maintenance. Certain large operations should be
        performed in the background, for instance account aging, database
        maintenance, et cetera.

      - @c userdel is activated when a user needs to be deleted from the
        system. The module should remove all of its per-user files for the user
        ID (useracc_t::userid) that will be specified as @c argv[2] inside your
        module.

	@see mod_handler_t, mod_setinfo().
*/

typedef struct {
	char *progname;		/**< The module's program name */
	char *name;		/**< The module's full name, capitalised etc */
	char *author;		/**< The module's author(s) */
	char *descr;		/**< One-sentence description of module */
	char *version;		/**< Full RCS compatible version */
	char *shortversion;	/**< Short, decimal (x.yy[.zz]) version */
	mod_handler_t login;	/**< Login-time processing handler */
	mod_handler_t run;	/**< Runtime handler */
	mod_handler_t logout;	/**< Logout handler */
	mod_handler_t hangup;	/**< Hangup handler */
	mod_handler_t cleanup;	/**< Cleanup handler */
	mod_handler_t userdel;	/**< User deletion handler */
} mod_info_t;


mod_info_t __module;		/**< Internally used module information. */


extern uid_t bbs_uid;		/**< The UNIX user ID of the `bbs' user */
extern gid_t bbs_gid;		/**< The UNIX group ID of the `bbs' user */


/** A block of system-wide variables */

extern struct sysvar *sysvar;



/** @defgroup INI_flags Initialisation mode flags (INI_x)

    @memo Subsystems of the BBS API to be initialised.

    Different modules have different needs. In most cases, all of the API
    will have to be initialised, especially for interactive modules. However,
    non-interactive, pre-login or other unusual requirements may call for only
    a few of the subsystems to be initialised at a time (the <tt>bbslogin</tt>
    subsystem does this, for example).

    Unless you really know what you're doing, always initialise everything! Too
    many things rely on too many other things, and the breakage would be
    significant.

    @see mod_init()
*/

/*@{*/

#define INI_SIGNALS 0x00000001	/**< Initialise signal handlers. */
#define INI_INPUT   0x00000002	/**< Initialise user input handling. */
#define INI_SYSVARS 0x00000004	/**< Attach to system variable shared block. */
#define INI_CLASSES 0x00000008  /**< Load the user classes. */
#define INI_ERRMSGS 0x00000010	/**< Initialise hardwired fatal error messages. */
#define INI_ATEXIT  0x00000020  /**< Set internal at-exit handlers. */
#define INI_LANGS   0x00000040  /**< Prepare languages. */
#define INI_OUTPUT  0x00000080  /**< Initialise user output subsystem. */
#define INI_USER    0x00000100  /**< Load/attach to the user. */
#define INI_GLOBCMD 0x00000200  /**< Initialise global commands. */
#define INI_TTYNUM  0x00000400  /**< Read TTY to/from BBS channel mapping. */
#define INI_CHAT    0x00000800  /**< Initialise Sysop chat mode handlers. */
#define INI_ALL     0xffffffff  /**< Initialise everything.

Use this flag with mod_init() unless you know what you're doing. */

/*@}*/



/** Set module information block.

    You must call this function early in the module's initialisation to declare
    it to the system.

    @param mod a pointer to a module information block of type ::mod_info_t.
*/

void mod_setinfo (mod_info_t *mod);


/** Set program name.

    This function facilitates setting the program name for subsystems of the
    BBS that are not modules. This is important, since error reporting needs
    the program name.

    @param name the name of the program.  */

void mod_setprogname (char *name);


/** Module entry point.

    This is the function that turns your program into a full-blown, well-behaved
    BBS module. It deals with command-line arguments, can identify itself (and
    you, its author), et cetera. You must use mod_setinfo() before calling
    mod_main().

    The function never returns; it calls the entry point functions specified by
    your module's information block (::mod_info_t) and exits. It also handles
    error reporting et cetera.

    @param argc the number of elements in the array argv, exactly like the argc
    argument of main(). In fact, you should pass main()'s @c argc here.

    @param argv a string array of command line arguments. Pass the @c argv
    argument of your main() function here.
  */

int mod_main (int argc, char **argv);


/** Initialise a module.

    Prepares a module for running by installing signal handlers, initialising
    structures, and so on.

    @param initflags the #INI_ALL flag, or a number of @c INI_x flags ORred
    together. The named subsystems will be initialised. Unless you really know
    what you are doing, specify #INI_ALL here.

    @see mod_done(), mod_end().

*/

void mod_init (uint32 initflags);

/** Prepares a module for exit.

    Uninstalls signal handlers, resets terminal to normal operation, et cetera.

    @param services a set of @c INI_x flags denoting which subsystems are to be
    shut down. This argument is almost always equal to #INI_ALL. Certain
    operations may need to temporarily suspend a few BBS subsystems, which is
    why this function allows a partial shutdown. However, this is an exception
    and not the rule.

    @warning Services will be shut down @e only if they have been previously
    initialised by a corresponding call to mod_init(), hence #INI_ALL is safe to
    use whatever the actual invocation of mod_init(). This constitutes a slight
    change of semantics of the @c INI_x flags.

    @see mod_init(), mod_end().
*/

void mod_done (uint32 services);


/** Prepares a module for exit.

    This is the same as @c mod_done(INI_ALL). It's mostly used for graceful
    shutdowns of modules.

    @see mod_init(), mod_done().
*/

void mod_end();


/** Register this process as an interactive one.

    Sets the PID of the interactive process for the supplied terminal. This is
    used internally to send signals to the process which is currently handling a
    user's input. This function is called internally by mod_init(). In
    certain unusual cases, it may be necessary to re-register an interactive
    process without calling <tt>mod_init()</tt> (for instance, after a child
    interactive process has just terminated).

    @warning This is called internally. Unless you need to re-register your
    module with the system (for example after temporarily calling another
    Megistos module from your own), there's no need to ever call this function.

    @param tty the device name the process is attached to. Suitable values may
    be obtained using onlinerec_t::channel, or, as a last resort, the value of
    the environment variable @c CHANNEL. Do @b not use any of the otherwise
    obvious POSIX ways of doing this such as @c ttyname(3). The controlling tty
    of the running process is not necessarily the device of the BBS channel, as
    the user monitoring/emulation daemon, @c emud, allocates a pseudotty to
    insert itself between the process and the user.
*/

void mod_regpid (char *tty);


/** Check whether a process is a bot.

    @return Returns non-zero if the current module is being operated by a
    bot. Generally speaking, you should not need to treat bots any different
    from human users, but some subsystems do need this facility.
*/

int mod_isbot();

/** Enter or leave bot mode.

    In bot mode, output is drastically changed to make it much more
    machine-readable so that bots can operate the system using UNIX facilities
    as simple as @c chat(1) or @c expect(1). The facility to change to/from bot
    mode is provided for scripts that operate in bot mode for a set period of
    time, then relinquish control to a user (or, conversely, are spawned by a
    user while that user is logged into the system).

    @param isbot Specify zero to leave bot mode, non-zero to enter it.
*/

void mod_setbot (int isbot);


#endif /* BBSMOD_H */


/** \example mod_main.c

    This is a short example demonstrating how to initialise ::mod_info_t properly,
    and showing just how simple a module's main() function is.
*/


/*@}*/

/*
LocalWords:  bbsmod BBS Alexios doc Megistos initialising API legalese Exp
LocalWords:  alexios bbs UID GID initialise setprogname GPL ifndef VER tt
LocalWords:  endif em argc argv struct int setinfo progname descr yy zz uid
LocalWords:  shortversion uid gid gid sysvar sysvar INI pre bbslogin ATEXIT
LocalWords:  initmodule SYSVARS ERRMSGS LANGS GLOBCMD TTYNUM Sysop param
LocalWords:  initflags ORred init uint Uninstalls PID regpid */
