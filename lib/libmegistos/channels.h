/*! @file     channels.h
    @brief    BBS Channel status manipulations (aka lines, TTYs)
    @author   Alexios

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     channels.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  Interface to channels.c                                      **
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
 * Revision 1.6  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.5  2003/09/27 20:29:47  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.4  2003/08/15 18:12:08  alexios
 * Slight cpp fix to silence warning.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1999/07/18 21:13:24  alexios
 * Cosmetic changes. Added MetaBBS support.
 *
 * Revision 1.0  1998/12/27 15:19:02  alexios
 * Initial revision
 *
 *
 *

@endverbatim
*/


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef CHANNELS_H
#define CHANNELS_H


#include <bbsconfig.h>


/** @defgroup channels BBS Channel Functionality

    This file provides an API for controlling BBS channels. Each
    channel has a number of status components:

    - Channel mode (e.g. Normal, No-Answer, Busy, etc).
    - Result code (e.g. OK, RING, ERROR, etc).
    - Line speed where applicable (e.g. 33600 bps),
    - Occupant of line (a user ID, usually).

    The functionality declared here helps deal with these aspects of
    channels. This is usually not for modules' use. Unless of course
    you have some strange module that touches channels.

@{*/




/** @defgroup LST_flags Channel modes (LST_x)

    @memo Basic line states.

    These control the behaviour of each BBS channel with respect to
    incoming calls. Here's how it works:

    \begin{description}
    
    - #LST_NORMAL. Normal BBS behaviour. The channel is open for business,
       answering calls and allowing connections.

    - #LST_NOANSWER. The channel will not answer incoming connections.

    - #LST_BUSYOUT. The modem is off the hook and the channel behaves as if the
      line is busy. This, of course, only works with modems.

    - #LST_OFFLINE. The channel answers incoming calls, but does not allow
      connections. Instead, a message is printed and the line is connection
      dropped. This way you can let people know the system is down for
      maintenance, or whatever. Of course, this also means that people get
      charged for each call.
*/
/*@{*/

/* Channel modes */

#define LST_NORMAL   0   /**< Normal behaviour (answers calls, logins) */
#define LST_NOANSWER 1   /**< Do not answer incoming calls */
#define LST_BUSYOUT  2   /**< Keep the line off-hook so it appears busy */
#define LST_OFFLINE  3   /**< Answer calls, say something and hang up */

#define LST_NUMSTATES 4  /**< The number of line states available */

/*@}*/



/** @defgroup LSR_flags Channel result codes (LSR_x)

    @memo Result codes.

    @doc These constants give an idea of what a channel is doing now, or what
    has gone wrong with what it was instructed to do.
    
    - LSR_INIT. A modem or other line hardware is being initialised.
    - LSR_OK. Everything is in order.
    - LSR_RING. An incoming call is being detected.
    - LSR_ANSWER. Answering an incoming call.
    - LSR_LOGIN. Call connected, a user is logging in.
    - LSR_USER. There is a user occupying this channel.
    - LSR_FAIL. Hardware initialisation has failed on this channel.
    - LSR_RELOGON. A user is re-logging in without disconnecting.
    - LSR_LOGOUT. A user has just logged out and @c bbsgetty is respawning.
    - LSR_METABBS. A user who hasn't yet logged in is using the MetaBBS client
      to access another system.
    - LSR_INTERBBS. Another BBS is using this line for networking.

    The last two result codes are only available when MetaBBS is compiled in.
*/
/*@{*/

/* Channel results */

#define LSR_INIT    0   /**< The line is being initialised */
#define LSR_OK      1   /**< Line initialised and awaiting connection */
#define LSR_RING    2	/**< Incoming modem connection */
#define LSR_ANSWER  3	/**< Answering call */
#define LSR_LOGIN   4	/**< User is logging in */
#define LSR_USER    5	/**< User occupies the channel */
#define LSR_FAIL    6	/**< Initialisation failed */
#define LSR_RELOGON 7	/**< User is re-logging in. */
#define LSR_LOGOUT  8   /**< Session has ended, awaiting new bbsgetty */

#ifdef HAVE_METABBS
#define LSR_METABBS 9	/**< The user is using the MetaBBS client */
#define LSR_INTERBBS 10	/**< Another BBS is using this channel for networking */

#define LSR_NUMRESULTS 11
#else
#define LSR_NUMRESULTS  9
#endif

/*@}*/


/* String values for the channel modes: DO NOT CHANGE THESE, unless
   you also change the LST_ and LSR_ defines above to reflect the
   changes! */

#ifdef CHANNELS_C


/** String versions of the <tt>LST_x</tt> flags. */

char *channel_states[]={
	"NORMAL",
	"NO-ANSWER",
	"BUSY-OUT",
	"OFF-LINE"
};


/** String versions of the <tt>LSR_x</tt> flags. */

char *channel_results[]={
	"INIT",
	"OK",
	"RING",
	"ANSWER",
	"LOGIN",
	"USER",
	"FAIL",
	"RELOGON",
	"LOGOUT"
#ifdef HAVE_METABBS
	,"METABBS"
	,"INTERBBS"
#endif
};

#else
extern char *channel_states[];
extern char *channel_results[];
#endif



/*! \struct channel_status_t

    \brief Channel status structure.

    This has fields for all the state information attached to channels. It is
    used by channel_getstatus() and channel_setstatus().

    @see channel_getstatus(), channel_setstatus()
*/

typedef struct {
	uint32 state;		/**< The line state (from line_states) */
	int32  result;		/**< Last result (from line_results) */
	int32  baud;		/**< The `baud' (bps, really) rate of the line */

#ifndef HAVE_METABBS
	char user [24];		/**< The user occupying the line, if any. */
#else

	/** MetaBBS uses the user field to store the remote system the line is
	    connected to. Hence we need this to be longer if MetaBBS is compiled
	    in.  */

	char user [256];
#endif
} channel_status_t;



/** Get channel status.

    Given a UNIX tty name, this function retrieves the respective channel
    status.

    @param tty a UNIX tty name minus <tt>"/dev/"</tt>.

    @param status a pointer to a ::channel_status_t status block where the
    channel status will be stored.

    @return if the status of the channel cannot be read from the status file, -1
    is returned and the default line status @c
    {LST_NORMAL,LSR_OK,0,"[NO-USER]"}) is copied to @c status. If all goes well,
    1 is returned.

    @see channel_status_t, channel_setstatus() */

int channel_getstatus(char *tty, channel_status_t *status);


/** Set channel status.

    Given a UNIX tty name, this function changes the channel status of the
    given tty according to the information passed in @c status.

    @param tty a UNIX tty name minus <tt>"/dev/"</tt>.

    @param status a pointer to a ::channel_status_t status block containing the
    updated state for the channel.

    @return always returns 1, which implies success. Failure to write the state
    to the state file causes the module to die, logging a fatal error. This is
    necessary and acceptable as the channel status is only changed during
    critical sections in the lifetime of a user session. Custom modules should
    never need to call this function.

    @see channel_status_t, channel_getstatus() */

int channel_setstatus(char *tty, channel_status_t *status);


/** Set channel mode.

    This sets the channel mode to one of the <tt>LST_x</tt> states. The function
    only affects a subset of the entire channel state, and is there for
    convenience.

    @param tty a UNIX tty name minus <tt>"/dev/"</tt>.

    @param mode the new mode of the line (one of the <tt>LST_x</tt> states).

    @see LST_x flags.
*/

void channel_setmode(char *tty, int32 mode);


/** Set channel result code.

    This sets a channel's result code to the supplied value. It only affects
    the result code, so it can be used to update a channel's state after its
    condition changes.

    @param tty a UNIX tty name minus <tt>"/dev/"</tt>.

    @param result the new result code for the line (one of the <tt>LSR_x</tt> flags).

    @see LSR_x flags.
*/

void channel_setresult (char *tty, int32 result);


/** Hangup this user's channel.

    This function causes a (UNIX) hangup of the current line. This is done the
    secure (and traditional) way, which is to set the baud rate of the current
    terminal to zero. Both UNIX and Megistos catch the death of the terminal and
    act accordingly.

    For a function to hangup another channel, see channel_disconnect().

    @see channel_disconnect().  */

void channel_hangup();


/** Disconnect a channel.

    This kills a channel, causing it to respawn from scratch. Any user logged at
    that time on is unceremoniously kicked out in the process.

    @param tty a UNIX tty name minus <tt>"/dev/"</tt>.

    @return If all goes well, 0 is returned. Anything else denotes an error
    and @c errno will be set accordingly).
*/

int channel_disconnect (char *ttyname);


/** Formats channel speed as a string.

    @param baud a channel speed, as obtained with <tt>channel_getstatus()</tt>.

    @return A string denoting the user's bps rate, if applicable, or a short
    string describing the connection type, e.g. <tt>"[NET]"</tt> if the user is
    connected using Telnet.
*/

char *channel_baudstg(int32 baud);


#endif /* CHANNELS_H */

/*@}*/

/*
LocalWords:  BBS aka TTYs Alexios doc API bps legalese alexios Exp bbs VER
LocalWords:  MetaBBS ifndef endif LST tt NOANSWER BUSYOUT OFFLINE NUMSTATES
LocalWords:  LSR INIT RELOGON bbsgetty INTERBBS ifdef NUMRESULTS getstatus
LocalWords:  setstatus struct uint int param dev setmode setresult Megistos
LocalWords:  errno ttyname baudstg */
