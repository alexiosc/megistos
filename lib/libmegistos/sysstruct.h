/** @file    sysstruct.h
    @brief   System-wide statistics and data types.
    @author  Alexios

    Documentation for this header file is relatively scarce, since it'll soon
    be undergoing many changes. The file contains global data structures to
    store BBS state and global settings.

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     sysstruct.h                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Define system structures, system variable structs, etc       **
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
 * Revision 1.4  2003/09/27 20:32:05  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1998/12/27 15:19:19  alexios
 * Added magic number fields etc.
 *
 * Revision 0.5  1998/08/14 11:23:21  alexios
 * Increased width of monitor.channel to accommodate a full
 * user name for the new modus operandi of the MONITOR command.
 *
 * Revision 0.4  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/05 10:52:05  alexios
 * Removed SVR_SOPAUD. With the new auditing scheme, this is
 * obsolete; the operator has far more features than just
 * turning auditing notification on and off.
 *
 * Revision 0.2  1997/11/03 00:29:40  alexios
 * Made emuqueue and monitor volatile.
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




#ifndef SYSSTRUCT_H
#define SYSSTRUCT_H


/*@{*/


/** User emulation structure.

    This structure contains enough information to help in emulating a user (the
    user-to-emulator part). It isn't well documented because you won't need to
    use it. */

struct emuqueue {
	volatile char queue [16376];	/**< User output queue.  */
	volatile int  index;		/**< The pointer in the queue.  */
	volatile int  xlation;          /**< Currently active translation mode. */
}; 


/** User monitoring structure.

    This structure allows monitoring of user input, which only works where
    supported by modules and other user-side software. This structure is less
    than thoroughly documented because there is no need for you to use it. */

struct monitor {
	volatile long timestamp;	/**< Time and date of last inpuit. */
	volatile char channel[24];	/**< Channel where input came from. */
	volatile char input[8192-28];	/**< The input itself. */
};


/** System variables blocks.

    This is a very old and almost vestigial part of Megistos. It was modeled
    after the corresponding part of the Major BBS. However, Megistos' design was
    very different from the design that imposed the system variable block on the
    Major BBS. As a result, this part of the system really shows its age. It
    should be removed at some point, for a very large number of reasons:

    - Stability: even given the unbelievably paranoid backup policy of the
      system variable file, this is the most common point-of-failure for the
      BBS. It has numerous natural enemies, including stupidity, race
      conditions, disk crashes, et cetera.

    - It's a binary structure (and file) and that always spells disaster for
      maintenance and recovery.

    - Most of the fields no longer make sense. For that matter, many of the
      fields found in Major's system variable block weren't really applicable
      when I started programming the Major BBS in 1992. Having room for a single
      voice phone is stupid, if your BBS has 32 lines and a telnet
      connection. Having by-the-minute charges is silly, if you have monthly
      subscriptions. Having @e charges is silly if you run a free system.

    - All of the fields here should be present because there is absolutely no
      other place to put them. This clearly does not hold for most fields. Even
      the statistics block could easily be moved to the <tt>data/stats</tt>
      directory where all the other statistics are. BBS names, addresses, et
      cetera are handled by substitution variables. No need to involve global
      state for things that are seldom needed.

    - The system variable block was meant to service a centralised system, where
      everything was a single process, with a single view of memory. Megistos is
      pretty distributed. The BBS is split among different processes, with
      global state (such as it is) being kept by the BBS daemon (<tt>bbsd</tt>).

    Given all that, I'm not going to document the entire structure.  */

struct sysvar {
	char      bbstitle   [52];	/**< Full name of the BBS */
	char      company    [48];	/**< Company owning the BBS, if any  */
	char      address1   [48];	/**< BBS mailing address, line 1 of 2  */
	char      address2   [48];	/**< BBS mailing address, line 2 of 2 */
	char      city       [48];	/**< City where BBS is */
	char      dataphone  [48];	/**< Main dialup phone */
	char      voicephone [48];	/**< Main voice phone */
	char      livephone  [48];	/**< Dialup for paid users */
	uint32    idlezap;		/**< Inactivity timeout (minutes, 0=off) */
	uint32    saverate;		/**< Minutes between saving sysvar to disk */
	char      chargehour [32];	/**< Charge per hour (textual description) */
	char      mincredits [32];	/**< Minimum time users can buy */
	char      minmoney   [32];	/**< Minimum charge on users */
	uint32    flags;		/**< Unknown */
	int32     pswexpiry;		/**< Password lifetime (days) */
	int32     injaudit;	       
	bbskey_t  pagekey;		/**< Key needed to page */
	bbskey_t  pgovkey;		/**< Key needed to override page restrictions */
	bbskey_t  pallkey;		/**< Key needed to page all users */
	int32     glockie;
	int32     lonaud;
	int32     lofaud;
	int32     tnlmax;
	int32     idlovr;
	int32     bbsrst;
	
	char dummy1 [6144 - 540];
	
	int32     tcredspaid;		/**< Total paid credits posted ever        */
	int32     tcreds;		/**< Total credits (paid+free) posted ever */
	uint32    timever;		/**< Total on-line time ever               */
	uint32    filesupl;		/**< Total number of files uploaded ever   */
	uint32    filesdnl;		/**< Total number of files downloaded ever */
	uint32    bytesupl;		/**< Total bytes * 100 uploaded ever       */
	uint32    bytesdnl;		/**< Total bytes * 100 downloaded ever     */
	uint32    sigmessages;	        /**< Total Club messages written           */
	uint32    emessages;		/**< Total Email messages written          */
	uint32    nmessages;		/**< Total outgoing (net) messages written */
	uint32    connections;	        /**< Total number of connections ever      */
	uint32    incnetmsgs;		/**< Total incoming net messages received  */
	uint32    emsgslive;		/**< Email messages active at this time    */
	uint32    clubmsgslive;	        /**< Club messages active at this time     */
	
	char dummy2 [2044 - 56];
	
	char magic[4];		        /**< Magic number (<tt>SYSVAR_MAGIC</tt>) */
};


#define SYSVAR_MAGIC "SVAR"


#define SVR_STARTANSI  0x3
#define SVR_ANSIOFF    0x00000000
#define SVR_ANSION     0x00000001
#define SVR_ANSIASK    0x00000002


struct clsstats {
	char   name[10];
	uint32 credits;
	uint32 minutes;
};


struct ttystats {
	char   name[32];
	uint32 channel;
	uint32 credits;
	uint32 minutes;
	uint32 calls;
};


struct baudstats {
	int32  baud;
	uint32 credits;
	uint32 minutes;
	uint32 calls;
};


struct usagestats {
	uint32 credits;
	uint32 minutes;
};


struct modstats {
	char   name[44];
	uint32 credits;
	uint32 minutes;
};


struct event {
	char   descr[41];
	char   command[256];
	int    hour, min;
	uint32 flags;
	uint32 lastrun;
};


#define EVF_ONLYONCE   0x0001
#define EVF_UNIQUE     0x0002
#define EVF_WARN       0x0004
#define EVF_ASAP       0x0008
#define EVF_NOW        0x0010


struct top {
	char   label[40];
	char   scorestg[16];
	uint32 score;
};


#endif /* SYSSTRUCT_H */

/*@}*/

/*
LocalWords: sysstruct Alexios doc BBS legalese otnotesize structs alexios
LocalWords: Exp bbs GPL SVR SOPAUD emuqueue ifndef VER endif struct int em
LocalWords: xlation timestamp inpuit Megistos Major's tt stats bbsd sysvar
LocalWords: bbstitle dataphone dialup voicephone livephone uint idlezap
LocalWords: saverate chargehour mincredits minmoney pswexpiry injaudit min
LocalWords: bbskey pagekey pgovkey pallkey glockie lonaud lofaud tnlmax
LocalWords: idlovr bbsrst tcredspaid tcreds timever filesupl filesdnl SVAR
LocalWords: bytesupl bytesdnl sigmessages emessages nmessages incnetmsgs
LocalWords: emsgslive clubmsgslive STARTANSI ANSIOFF ANSION ANSIASK descr
LocalWords: clsstats ttystats baudstats usagestats modstats lastrun EVF
LocalWords: ONLYONCE scorestg
*/
