/*! @file     globalcmd.h
    @brief    Global command plugin interface.
    @author   Alexios

    This header file defines functions used by the global command manager. You
    don't need to know about this API, unless you want to add a global command
    handler for your module only.

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     globalcmd.h                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Interface to globalcmd.c                                     **
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
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/09/27 20:31:12  alexios
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


#ifndef GLOBALCMD_H
#define GLOBALCMD_H


/** @defgroup gcs Declaring Global Commands

    Global commands are commands that work almost anywhere on the
    system. Although it's no rule of thumb, commands that start with a
    slash (<tt>/</tt>) are global commands.

    Megistos implements a dynamic plugin system for global commands. We used to
    put everything in this source file, which made things inelegant, big and
    ugly. Now, GCS (global command service) plugins can be compiled as
    dynamically loaded shared objects (DLLs in the DOS/Windows world, SOs in the
    UNIX world) and loaded at runtime. This way, commands are implemented by the
    modules that contribute them. I can't even begin to list the advantages of
    this scheme.

    To see a simple example of a global command handler, please see the Cookie
    module and file @c gcs_cookie.c in particular. A more complete collection is
    in file @c gcs_builtin.c in the main BBS library directory.

@{*/


/** Declaration for a GCS handler.

    This is a pointer to a function similar to:

    @verbatim
int handler (void)
    @endverbatim
    
    The handler takes no arguments. Its duties include parsing a user command
    that has already been input. You may use any means provided by the BBS
    library to this effect. I usually use the ::margc and ::margv technique
    because it's more elegant (and because I started my BBS programming days
    writing for the Major BBS, where this was right about the only decent way of
    parsing input).

    The handler must check to see if the user input is the command it
    implements. If so, it must perform any processing and return a value of 1
    to the caller. If the command is not the one dealt with by the handler, the
    handler must return 0 to the caller.

    Please do not modify the user input in any way until you make sure is
    contains the command you service. */

typedef int (*gcs_t)(void);


/** Add a local-global command.

    This somewhat surreal function is mostly used internally. You can use it to
    add your own handlers, but they will only be valid while the user is in
    your module. This is still useful to implement commands that work anywhere
    within <em>one</em> module only.

    @param gcs the global command service handler.  */

void gcs_add (gcs_t gcs);


/** Initialise the global command services.

    This scans the directory lib/gcs for GCS plugins, loads them and installs
    the handlers. It is called by mod_init() when specified with #INI_GLOBCMD
    (or, of course, #INI_ALL). No need for you to call it manually, unless
    you're doing something strange. */

void gcs_init();


/** Handle GCS.

    Executes all of the registered global command handlers in turn.

    @return If any handler returns non-zero, no more handlers are executed and
    a value of 1 is returned. Otherwise, zero is returned. */

int gcs_handle();


#endif /* GLOBALCMD_H */

/** \example gcs_builtin.c

    A very long example demonstrating how to write global commands. This file
    implements the builtin global commands for this system. It serves as an
    example of numerous BBS methods.
*/


/*@}*/

/*
LocalWords: globalcmd plugin Alexios doc tt Megistos GCS plugins DLLs SOs
LocalWords: em gcs builtin LIB API legalese alexios Exp bbs GPL ifndef VER
LocalWords: endif int margc margv param Initialise lib init INI
*/
