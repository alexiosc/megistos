/** @name    security.h
    @memo    Definitions pertaining to access levels and security.
    @author  Alexios

    @doc

    This header implements system security. Namely, sysop privilege checking
    and key/lock security.
    
    Sysops have an array of flags denoting a number of different command and
    privileges. Most of those privileges are available within the Remote Sysop
    module, but they have to be checked for in other places, too.

    Keys are similar to sysop privileges, but are available everywhere. Keys
    are numerical (work is underway to establish a better, database-driven,
    alphanumeric key system). On a normal system (i.e. not hacked and kludged),
    there are 130 keys, 128 of which are available to people:

    \begin{description}

    \item[{\tt 0}] All users implicitly have this key. It cannot be added or
    removed, but it can be checked for.

    \item[{\tt 1--128}] These keys can be added or removed freely.

    \item[{\tt 129}] Only the user ID `Sysop' has this key, or whatever user ID
    is specified in the {\tt SYSOP} macro in {\tt config.h}. The key cannot be
    added to anyone and it cannot be removed from Sysop's keyring.

    \end{description}

    BBS features have locks on them. Each lock can only be unlocked by one,
    specified key. A user needs to possess this key in order to access locked
    features.

    There are two sources of keys for users: their class keyring, and their
    own, personal keyring. The class keyring is a set of keys granted to an
    entire user class. Belonging to the class implies ownership of those
    keys. The personal keyring is the obvious: a keyring that only the user
    possesses. Operators can grant keys to individuals in addition to the keys
    their classes provide.

    Original banner, legalese and change history follow.

    {\footnotesize
    \begin{verbatim}

 *****************************************************************************
 **                                                                         **
 **  FILE:     security.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  Interface to security.c                                      **
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
 * Revision 1.0  1998/12/27 15:19:02  alexios
 * Initial revision
 *
 *
 *

\end{verbatim}
} */

/*@{*/


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef SECURITY_H
#define SECURITY_H


/** Check if a user has a certain operator command.
    
    This function checks a user account record for the existence of a specified
    operator privilege or command.

    @param user Pointer to the account record of the user in question.

    @param index The number of the privilege or operator command in
    question. This is one of the {\tt USY_x} constants.

    @return Zero if the user lacks the privilege or command, non-zero if they
    have it. */

int hassysaxs(useracc_t *user,int index);


/** Unites user and class keyrings.

    This function combines user and class keys to form the complete set of keys
    that a user has. A user has a key if it's contained in the keyring of the
    user's class, or if the user has been given this key on an individual
    basis.

    @param userkeys a pointer to the user's keyring array.

    @param classkeys a pointer to the user's class' keyring array.

    @param unionkeys a pointer to a keyring array that will be filled in with
    tue union of the two keyrings. This is effectively the return value of the
    function. 

    @return The function returns {\tt unionkeys} for no particular reason. */

bbskey_t * key_make(bbskey_t *userkeys,
		    bbskey_t *classkeys,
		    bbskey_t *unionkeys);


/** Check for a key in a key array.

    Examines the given key array for ownership of the specified key. Two keys
    are handled specially: key 0 is the `non-key'. All users implicitly have
    this one. Key 129 is the Sysop key. Only user `Sysop' (or whatever the
    value of the macro {\tt SYSOP} is) has this key. Not even users with the
    master key (usually 128, but can be changed at will) can unlock features
    locked with the Sysop key. All other keys are explicitly specified in the
    key array.

    If you need to check a user for ownership of a key, this isn't the right
    function. You need {\tt key_owns()}.
    
    @param keys A key array to test for key ownership.

    @parm key Key number to check.

    @return Zero if the key array does not contain the key; non-zero if it
    does.

    @see key_owns(). */

int key_exists(bbskey_t *keys,int key);


/** Check if a user owns a key.
    
    Checks if a user owns a key, taking into account the Master Key privilege
    and the user's class keyring. This is the function to use if you need to
    check a user for ownership of a key.

    @param user Pointer to the user's account structure.
    
    @param key Number of the key to check for.

    @return Zero if the user does not have the key; non-zero if they do. */

int key_owns(useracc_t *user,int key);


/** Add or remove keys from a key array.

    Sets or clears keys within the specified key array.

    @param keys The key array to modify.

    @param key The key to add or remove. Key 0 cannot be added or removed, it
    is implicitly present in all keyrings. Key 129 cannot be added or removed,
    it is implicitly absent from all keyrings (won't even fit, on a normal
    system). Specifying an invalid key number causes no error, but no operation
    either.

    @param set If non-zero, the specified key will be added to the keyring. If
    zero, the key will be removed. */

void key_set(bbskey_t *keys, int key, int set);


#endif SECURITY_H

/*@}*/

/*
LocalWords:  Alexios doc legalese otnotesize alexios Exp bbs ifndef VER tt
LocalWords:  endif param USY int hassysaxs useracc keyrings keyring tue sysop
LocalWords:  userkeys classkeys unionkeys Sysop parm Sysops config Sysop's
*/
