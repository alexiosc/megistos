/** @file     menuman.h
    @brief    Interface to the menu manager
    @author   Alexios

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     menuman.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Define the page structures used by the menuman               **
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
 * Revision 1.4  2003/09/27 20:31:46  alexios
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
}*/

#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef MENUMAN_H
#define MENUMAN_H

/** @defgroup menuman_h The Menu Manager Interface

    The discussion below is largely academic: you won't need to call the menu
    manager from your own modules (@e it calls <em>them</em>) and you definitely
    shouldn't include this header file. The API already defines enough
    menuman-related functionality for your modules.  I'll still include the
    description, in the hope that it'll be useful at some later stage.

    The menu manager was inspired by the corresponding subsystem in the Major
    BBS. Of course, Major's menuman was created for an entirely different
    environment. Megistos' Menu Manager is a more versatile thingy, but the
    experienced Major programmer may notice behavioural similarities.

    The menu manager is a `meta-module': it behaves as the glue that binds
    modules together. It handles all menuing outside modules. The operator
    defines a number of <em>pages</em>. There are four types of pages:

    - Menu pages. These offer menus to the user. Each of the menu's options take
      the user to another page.

    - File pages. These pages print out specific files to the user.  Different
      files can be specified for each supported language. Also, depending on the
      user's terminal settings (e.g. whether their terminal has VT-100/ANSI
      graphics capabilities), different files may be printed. All this is
      implemented using file suffixes. Intelligent fallbacks are supplied. Once
      the file has been printed, the user is returned to the Menu page they came
      from.

    - Command execution pages. Also known as `exec' pages. These execute a
      specified UNIX command when the user accesses them. Commands may be
      interactive or not. While the user is executing the command, he appears to
      be busy and no inactivity timeouts are enforced.

    - Module execution pages. Also known as `run' pages. These pass interactive
      control to a BBS module to handle further user input. Control passes to
      the calling page when the module is finished. Each page may specify a
      string of concatenated commands to be passed to the module. In this way,
      different pages may access different parts of a module, effectively
      allowing for different entry points.

    Pages have three basic security features built into them. They can be made
    available to only one user class; access may be limited to users who possess
    a key; and options may be hidden from view, even if they are available to a
    user.

    Each page has its own multilingual description used in statistics and when
    the user issues the <tt>/#</tt> global command. Individual per-page credit
    consumption rates may also be applied. Finally, each page has its own unique
    name. The names may be used by the user for quick, random access to pages
    using the <tt>/go</tt> global command.

@{*/


#include <megistos/config.h>

#define PAGENAMELEN   16
#define PAGEDESCRLEN  44
#define MENUOPTNUM    64
#define FNAMELEN      64
#define INPUTSTRLEN   192
#define RUNSTRLEN     256

#define PAGETYPE_MENU 'M'
#define PAGETYPE_FILE 'F'
#define PAGETYPE_EXEC 'E'
#define PAGETYPE_RUN  'R'

#define DEFAULTCCR (-1<<30)

struct menuoption {
	char opt;
	char name[PAGENAMELEN];
};

struct menupage {
	char              name  [PAGENAMELEN];
	char              prev  [PAGENAMELEN];
	char              descr [NUMLANGUAGES] [PAGEDESCRLEN];
	char              type;
	int               creds;
	int               key;
	char              class [10];
	int               flags;
	char              fname [FNAMELEN];
	struct menuoption opts [MENUOPTNUM];
};

struct filepage {
	char              name  [PAGENAMELEN];
	char              prev  [PAGENAMELEN];
	char              descr [NUMLANGUAGES] [PAGEDESCRLEN];
	char              type;
	int               creds;
	int               key;
	char              class [10];
	int               flags;
	char              fname [FNAMELEN];
};

struct execpage {
	char              name  [PAGENAMELEN];
	char              prev  [PAGENAMELEN];
	char              descr [NUMLANGUAGES] [PAGEDESCRLEN];
	char              type;
	int               creds;
	int               key;
	char              class [10];
	int               flags;
	char              fname [FNAMELEN];
	char              input [INPUTSTRLEN];
};

struct runpage {
	char              name  [PAGENAMELEN];
	char              prev  [PAGENAMELEN];
	char              descr [NUMLANGUAGES] [PAGEDESCRLEN];
	char              type;
	int               creds;
	int               key;
	char              class [10];
	int               flags;
	char              command [RUNSTRLEN];
};

union menumanpage {
	struct menupage m;
	struct filepage f;
	struct execpage e;
	struct runpage  r;
};


#define MPF_HIDDEN  0x0001
#define MPF_INHIBIT 0x0002


#endif /* MENUMAN_H */

/*@}*/

/*
LocalWords: menuman Alexios doc em API BBS Major's Megistos thingy VT tt
LocalWords: legalese alexios Exp bbs GPL ifndef VER endif config FNAMELEN
LocalWords: PAGENAMELEN PAGEDESCRLEN MENUOPTNUM INPUTSTRLEN RUNSTRLEN prev
LocalWords: PAGETYPE DEFAULTCCR struct menuoption menupage descr int creds
LocalWords: NUMLANGUAGES fname filepage execpage runpage menumanpage MPF
*/
