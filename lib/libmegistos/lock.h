/** @name     lock.h
    @memo     Resource locking.
    @author   Alexios

    @doc This header defines an interface to the locking features of the
    BBS. Locks are implemented with the aid of the lock daemon, which listens
    to commands on a socket.

    Lockd requests are strings sent to the daemon's socket. They look like
    this:

    \begin{verbatim}
    MAKE foo 42 bar  Creates lock "foo" with info "bar" for PID 42
    CHCK foo 42      Checks for the presence of lock "foo" (we're PID 42)
    KILL foo 42      Removes lock "foo" on behalf of process with PID 42
    \end{verbatim}

    Results are integers in decimal (matching the {\tt LKR_} constants below)
    followed by a string. A positive result code denotes the PID of a process
    holding the lock. In this case, the result code is followed by a string
    containing the {\tt info} field of the lock. Negative result codes denote
    error conditions.

    All this is slightly academic, though. The details of the transactions with
    the daemon are hidden from the user.

    Original banner, legalese and change history follow.

    {\small\begin{verbatim}

 *****************************************************************************
 **                                                                         **
 **  FILE:     lock.h                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94                                                 **
 **  PURPOSE:  Interface to lock.c                                          **
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
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/12/27 15:19:19  alexios
 * Rationalised locking to allow bbslockd to do all our
 * locking for us.
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
}*/

/*@{*/


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef LOCK_H
#define LOCK_H


/* The lock daemon's UNIX domain socket name */

#define BBSLOCKD_SOCKET mkfname(BBSETCDIR"/lock.socket")


/* Locking commands */

#ifdef __BBSLOCKD__
#define LKC_PLACE  "MAKE"
#define LKC_CHECK  "CHCK"
#define LKC_REMOVE "KILL"
#endif



/** @name Lock result codes
    @filename LKR_flags

    @memo Resource locking result codes.

    @doc These result codes allow the caller to know if a lock request
    succeeded, and, if not, why. They are a necessary part of resource
    locking.

    \begin{description}
    
    \item[{\tt LKR_OK}] All is well, the lock request was successful.

    \item[{\tt LKR_STALE}] The requested resource is locked, but the lock is
    stale. That is, the process that owned the lock has died. Your process may
    lock the resource.

    \item[{\tt LKR_OWN}] The lock exists, and belongs to you.

    \item[{\tt LKR_TIMEOUT}] There was a timeout while waiting for the lock to
    be removed. This result code is not returned by the daemon. Handling
    timeouts is the responsibility of the BBS library and they are reported
    locally.

    \item[{\tt LKR_ERROR}] A strange error has occur-ed. Whoops.

    \item[{\tt LKR_SYNTAX}] The lock daemon could not understand your request.

    \end{description}


    Any other result code greater than zero denotes the PID of a process
    holding the lock in question. */

/*@{*/

#define LKR_OK       0		/** Operation successful */
#define LKR_STALE   -1		/** Lock's owner is dead, lock is removed */
#define LKR_OWN     -2		/** Lock belongs to the caller */
#define LKR_TIMEOUT -3		/** Timeout waiting for lock to be removed */
#define LKR_ERROR   -4		/** Some other error occurred */
#define LKR_SYNTAX  -5		/** Lockd failed to parse the request */

/*@}*/


/** Place a lock.

    Registers a resource lock. The lock will first be checked to make sure you
    have permission to place it. Permission is given if the lock:

    \begin{itemize}
    \item does not exist;
    \item exists and is your own; or
    \item exists and is stale (i.e. belongs to a dead process).
    \end{itemize}

    @param name the name of the resource to be locked (filename of the lock,
    too).

    @param info a short description of the lock. This is for your benefit only,
    so that processes competing for a lock will know why a lock is in place.

    @return One of the {\tt LKR_x} result codes.  */

int lock_place(const char *name, const char *info);


/** Check if a lock exists.
    
    Checks for the existence of a lock. If the lock does not exist, {\tt
    LKR_OK} will be returned. If the lock exists, a PID (an integer greater
    than zero) will be returned. Please refer to the documentation for the {\tt
    LKR_x} constants for more information.
 
    @param name the name of the resource to be checked (filename of the lock,
    too).

    @param info if the lock exists, its {\tt info} field is copied to the
    supplied string.

    @return One of the {\tt LKR_x} result codes. */

int lock_check(const char *name, char *info);


/** Remove a lock.
    
    Removes the named lock.
 
    @param name the name of the lock to be removed.

    @return One of the {\tt LKR_x} result codes. {\tt LKR_ERROR} denotes an
    error with {\tt unlink()}, in which case the error will be left in {\tt
    errno} for your delectation. */

int lock_rm(const char *name);


/** Waits for a lock.
    
    Waits for a resource lock to become available. This function blocks,
    repeatedly checking if the specified lock has been released.
 
    @param name the name of the lock to check.

    @param delay the maximum time to wait in seconds.

    @return One of the {\tt LKR_x} result codes representing the state of the
    lock when the process exist. {\tt LKR_TIMEOUT} is reported when the time
    specified by {\tt delay} expired and the lock was still unavailable. */

int lock_wait(const char *name,int delay);


#endif /* LOCK_H */

/*@}*/

/*
LocalWords: Alexios doc BBS Lockd foo PID CHCK tt LKR legalese alexios Exp
LocalWords: bbs Rationalised bbslockd GPL ifndef VER endif BBSETCDIR ifdef
LocalWords: LKC Lock's param int const errno rm
*/
