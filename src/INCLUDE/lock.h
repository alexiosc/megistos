/*****************************************************************************\
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:48:54  alexios
 * Initial revision
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
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef LOCK_H
#define LOCK_H


/* The lock daemon's UNIX domain socket name */

#define BBSLOCKD_SOCKET BBSETCDIR"/lock.socket"


/* Locking commands */

#ifdef __BBSLOCKD__
#define LKC_PLACE  "MAKE"
#define LKC_CHECK  "CHCK"
#define LKC_REMOVE "KILL"
#endif


/* Locking results */

#define LKR_OK       0		/* Operation successful */
#define LKR_STALE   -1		/* Lock's owner is dead, lock is removed */
#define LKR_OWN     -2		/* Lock belongs to the caller */
#define LKR_TIMEOUT -3		/* Timeout waiting for lock to be removed */
#define LKR_ERROR   -4		/* Some other error occured */
#define LKR_SYNTAX  -5		/* Lockd failed to parse the request */

/* LKR_TIMEOUT is not returned by the daemon itself, only by waitlock() */


/*

   Lockd requests are strings sent to the daemon's socket. They look like this:

   MAKE foo 42 bar         Creates lock "foo" with info "bar" for PID 42
   CHCK foo 42             Check for the presence of lock "foo" (we're PID 42)
   KILL foo 42             Remove lock "foo" on behalf of process with PID 42

   Results are integers in decimal (matching the LKR_* #defines above)
   followed by a string. If a positive result code is returned, it
   signifies the PID of a process holding the lock. In this case, the
   result code is followed by a string containing the "info" field of
   the lock.

*/


int placelock(const char *name, const char *info);

int checklock(const char *name, char *info);

int rmlock(const char *name);

int waitlock(const char *name,int delay);


#endif /* LOCK_H */
