/** @name    ttynum.h
    @memo    Mapping between devices and BBS channels.
    @author  Alexios

    @doc

    This header provides function to map between the physical, UNIX device
    names users are riding and the convenient, numerical BBS channels.

    Original banner, legalese and change history follow.

    {\footnotesize
    \begin{verbatim}

 *****************************************************************************
 **                                                                         **
 **  FILE:     ttynum.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Interface to ttynum.c                                        **
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
 * Revision 0.6  1999/07/18 21:13:24  alexios
 * Added MetaBBS flag to control whether the MetaBBS client
 * should be enabled for a line.
 *
 * Revision 0.5  1998/12/27 15:19:19  alexios
 * Added some comments and the channel file magic number.
 *
 * Revision 0.4  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/03 00:29:40  alexios
 * Added xlation field to struct channeldef to keep the number
 * of the default translation table for a channel. Removed
 * defines for hardwired xlation tables.
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Added a config field to allow for the new handling of bbsgetty
 * configuration.
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


#ifndef TTYNUM_H
#define TTYNUM_H


/** The channel file magic number */

#define CHANNEL_MAGIC "MEGISTOS BINARY CHANNEL FILE\n\n\n"


/** Channel definition.

    Each channel entry in the file etc/channel.defs/CHANNELS is parsed into
    this structure. All of the information in the CHANNELS table is available
    here, too.

    \begin{description}

    \item[{\tt ttyname}] The name of the device special this channel is on,
    minus the {\tt "/dev/"}. For instance, the third virtual console on a Linux
    box is {\tt "tty3"}.

    \item[{\tt config}] The name of the {\tt bbsgetty} config file to load for
    this channel. Each config file corresponds to one type of hardware (one
    make and model of modem, serial hardware, et cetera), and prepares it for
    use by the BBS. In the case of a modem, for example, it sends
    initialisation strings, sets the bps rate, and instructs {\tt bbsgetty} to
    wait for a {\tt RING}.

    \item[{\tt channel}] The channel number. This is printed as a hexadecimal
    number to keep it short and for traditional reasons: Major did it because a
    Galactibox had 16 slots, and there were Galacticomm multiple modems with
    power-of-two devices on each card, up to, I think, eight. Besides, with
    Major only supporting 64 (and then 256) lines, a 16x4 and then 16x16
    arrangement was a good idea. Thus, bear in mind that channel {\tt "20"},
    is, in fact, channel 0x20, i.e. 32. Channels are almost always referred to
    in this confusing manner (i.e. without any indication of base). It is
    considered a good idea to avoid (if possible) using numbers such as {\tt
    1a} because they've been known to drive computer-naive users nuts.

    \item[{\tt key}] The key required to allow users to login on this channel.

    \item[{\tt lang}] The default language to use for this channel. Different
    channels can have different languages. The reason is simple: certain
    encodings don't mix well with certain connections (older telnet clients,
    7-bit ASCII serial connections, et cetera). It'd be a good idea to be able
    to display a language the users can {\em read} in order to login. The
    default language may be negative, in which case a language selection menu
    is presented to the user, and the default language is the absolute value of
    this field.

    \item[{\tt flags}] Flags for this channel, in the form of {\tt TTF_x} flags
    ORred together. This field sets the channel's defaults and assumptions,
    like whether to assume that users have ANSI enabled, et cetera.

    \item[{\tt xlation}] The default translation mode for this channel. It's
    here for the same reasons as the default language field, {\tt lang}.

    \end{description}

 */

struct channeldef {
  char          ttyname [16];	/** Name of the device, minus {\tt "/dev/"}. */
  char          config  [32];	/** Config file for {\tt bbsgetty}. */
  unsigned int  channel;	/** BBS channel number. */
  bbskey_t      key;		/** Key required to login. */
  int32         lang;		/** Default language for this channel. */
  uint32        flags;		/** Channel flags ({\tt TTF_x} flags). */
  int32         xlation;	/** Default translation mode. */
};


/** @name Channel definition flags.
    @filename TTF_flags

    @memo Flags controlling default channel behaviour.

    @doc The flags control the default behaviour of channels with respect to
    translation, language and terminal settings.

    \begin{description}
    
    \item[{\tt TTF_CONSOLE}] This channel is on the system console. Console
    lines behave slightly different during login. For instance, they interpret
    as blank user ID as a {\em redraw} command and redraw their screen. This is
    reminiscent of both the way {\tt getty} and the Major BBS operate.

    \item[{\tt TTF_SERIAL}] This channel is on a serial line, probably
    connected to a local terminal of sorts.

    \item[{\tt TTF_MODEM}] This channel is a modem. Modem channels have
    slightly different initialisation semantics from other types of channels.

    \item[{\tt TTF_TELNET}] This channel is for incoming telnet
    connections. This has {\em very} different semantics from other channels
    types! For one, it's the only type of line the BBS isn't watching on a
    constant basis. When a telnet connection is established, {\em then} the BBS
    knows about it.

    \item[{\tt TTF_SIGNUPS}] Allow new user signups on this line. This can be
    used to limit use of certain lines to existing users.

    \item[{\tt TTF_ASKXLT}] Present a menu so that the user can select the
    translation mode they require upon connection. If this flag is set, the
    {\tt xlation} field in {\tt struct channeldef} defines the translation mode
    selected when the user simply presses {\tt Enter} in this menu.

    \item[{\tt TTF_ANSI}] Set this flag to specify that this channel will
    output ANSI terminal directives by default.

    \item[{\tt TTF_ASKANSI}] Like {\tt TTF_ASKXLT}, present a menu so that the
    user can choose whether they'd like ANSI directives or not. The value of
    {\tt TTF_ANSI} is the default menu selection.

    \item[{\tt TTF_METABBS}] Allow use of the MetaBBS subsystem on this
    channel. Users are allows to use this line to connect to another friendly
    BBS, without connecting to yours (without even having an {\em account} on
    yours).

    \item[{\tt TTF_INTERBBS}] Allow other systems to use this channel for
    networking. This causes a slight pause before presenting a user-oriented
    login screen, so that automated systems can issue their respective
    handshakes. The timeout is small, so it should not annoy your users.

    \end{description} */
/*@{*/

#define TTF_CONSOLE  0x0001	/** Channel is on the system console */
#define TTF_SERIAL   0x0002	/** Channel is a plain serial line */
#define TTF_MODEM    0x0004	/** There's a modem on this channel */
#define TTF_TELNET   0x0008	/** This channel is for telnet connections */
#define TTF_SIGNUPS  0x0010	/** Signups are allowed here */
#define TTF_ASKXLT   0x0100	/** Ask people for translation mode */
#define TTF_ANSI     0x0200	/** ANSI enabled on this channel by default */
#define TTF_ASKANSI  0x0400	/** Ask people whether they need ANSI */

#ifdef HAVE_METABBS
#define TTF_METABBS  0x0800	/** Enable the MetaBBS client for this line */
#define TTF_INTERBBS  0x1000	/** Allow other BBSs to use this channel for
                                    MetaBBS networking. */
#endif

/*@}*/


/** The channels index, mapping ttys to channels. */

extern struct channeldef *channels;


/** Last referenced element of {\tt channels}. */

extern struct channeldef *chan_last;


/** Number of channels in {\tt channels}. */

extern int chan_count;


/** Initialise the channel map.

    Reads the binary channel file, initialising the channel map. */

void chan_init();


/** Find the channel number of a device.

    Maps device name to channel number, effectively yielding the number of a
    channel associated with the given device.

    @param tty The name of a device special, without the {\tt "/dev/"}.

    @return The channel number associated with the given device, or {\tt NULL}
    if the device is not associated with a BBS channel. */

uint32 chan_getnum(char *tty);


/** Find the index of a channel in {\tt channels}.

    Given a device name, this function yields the index of the channel
    structure in the {\tt channels} array.
    
    @param tty The name of a device special, without the {\tt "/dev/"}.

    @return The index of the channel associated with the given device, or -1 if
    the device is not associated with a BBS channel. */

uint32 chan_getindex(char *tty);


/** Find the device associated with a channel.

    Given the number of a channel, this function returns the device (minus the
    leading {\tt "/dev/"}) associated with it.

    @param num A channel number.

    @return The device name of channel {\tt num}, or {\tt NULL} if {\tt num} is
    not a existing BBS channel. */

char *chan_getname(uint32 num);


/** Count number of telnet lines in use.

    Returns the number of telnet lines that are currently in use.

    @return The number of telnet lines in use. */

uint32 chan_telnetlinecount();


#endif /* TTYNUM_H */

/*@}*/

/*
LocalWords: ttynum BBS Alexios doc legalese otnotesize alexios Exp bbs GPL
LocalWords: MetaBBS xlation struct channeldef config bbsgetty ifndef VER
LocalWords: endif MEGISTOS tt ttyname dev Galactibox Galacticomm lang em
LocalWords: TTF ORred int bbskey uint getty ASKXLT ASKANSI INTERBBS ifdef
LocalWords: BBSs chan Initialise init param getnum getindex num getname
LocalWords: counttelnetlinecount
*/
