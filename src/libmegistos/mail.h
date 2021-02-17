/*! @file     mail.h
    @brief    Definitions pertaining to email/club messages.
    @author   Alexios

    This header file includes declarations for various structures used in
    mail-related tasks throughout the system. You will typically want to include
    it for its definition of <tt>message_t</tt>, a BBS private or public
    message. There are other structures here, but most are used by the mail
    reading modules (Email and Clubs). I doubt you'll ever need any of them.

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     mail.h                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 95                                                    **
 **            B, July 95                                                   **
 **            C, July 95                                                   **
 **            D, August 96                                                 **
 **  PURPOSE:  Define mail and club headers                                 **
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
 * $Id: mail.h,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: mail.h,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/09/27 20:31:39  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/28 23:09:07  alexios
 * Cosmetic changes, added stuff for networked clubs.
 *
 * Revision 0.5  1999/07/18 21:13:24  alexios
 * Cosmetic changes. Added export access list field to struct
 * clubheader for use by the MetaBBS Distributed Club code.
 * Added flags for the IHAVE database used by DistClubs.
 *
 * Revision 0.4  1998/08/14 11:23:21  alexios
 * Shortened from and to fields to 80 bytes. Removed dummy
 * field to shorten size of message header.
 *
 * Revision 0.3  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 12:45:25  alexios
 * Minor cosmetic changes.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 *

@endverbatim

}*/

#ifndef RCS_VER 
#define RCS_VER "$Id: mail.h,v 2.0 2004/09/13 19:44:34 alexios Exp $"
#endif


#ifndef MAIL_H
#define MAIL_H


/** @defgroup mail Mail-Related Definitions

    Here you can find declarations for various structures used in mail-related
    tasks throughout the system. The most useful is the definition of
    <tt>message_t</tt>, a BBS private or public message. There are other
    structures here, but most are used by the mail reading modules (Email and
    Clubs). I doubt you'll ever need any of them, but a few subsystems do, so
    the declarations are available.

@{*/


/** An email or club message.

    This structure describes a BBS message, be it private or public. BBS
    messages differ from RFC-822 (Internet email) messages in a number of
    ways. In fact, in terms of philosophy BBS messages are a combination of
    email messages and newsgroup articles, with built-in (horribly weak)
    encryption and (optional single) file attachments. Here is a description of
    the fields:

    - @c from. The message's sender. This is usually a user ID, but could also be
      an RFC-822 email address (hence the larger length of the string).

    - @c to. The message's recipient (a BBS user ID or RFC-822 email
      address). BBS messages can either have a single recipient, or be public,
      in which case this field is set to #MSG_ALL. If a message needs to be
      private, yet must reach more than one recipient, <em>copies</em> are made,
      i.e. multiple individual messages are sent.

    - @c subject. A brief summary of the contents of the message.

    - @c history. A list of tortures this message has been subjected to in the
      recent past. These include forwarding from user to user, networking
      between systems, sending via off-line reader, being a reply to another
      message, et cetera. Don't print the contents of this field directly, if
      you can help it. The field should be tokenised, parsed and translated to
      improve readability.
 
    - @c fatt. The preferred filename of the optional file attachment. In default
      of a value for this field, the attachment name is constructed the @e
      Majoresque way: by appending the extension <tt>.ATT</tt>(achment) to the
      message's number. If the message has no attachment, the contents of this
      field should be considered undefined.

    - @c msgno. The aforementioned message number.

    - @c flags. Flags describing this message. Please see the documentation for the
      <tt>MSF_x</tt> flags.

    - @c crdate, crtime. These two 32-bit fields contain the date and time the
      message was created. This is <em>silly</em>, yes. The very names of the
      fields refer to the 16-bit days when date and time couldn't fit in one
      <tt>int</tt>. These days we only need 32 bits for both time and
      date. However, these fields are kept in place. We'll need to migrate to a
      64-bit {\tt time_t} soon.

    - replies. The number of replies to this message.

    - timesread. How many times the message was read or downloaded as part of an
      off-line reader message packet.

    - timesdnl. How many times the file attachment of this message was
      downloaded. The value should be treated as undefined if the message has no
      file attachment.

    - @c timesdnl. How many times the file attachment of this message was
      downloaded.

    - @c period. Megistos public messages can be <em>periodic</em>: they
      re-appear after a set period of time. This field sets the period in
      days. A value of zero means the message is not periodic. Re-appearance is
      implemented by forwarding, which implies that the original message is
      automatically deleted. This makes sense: you don't want <em>rabbit</em>
      messages in your system.

    - @c cryptkey. Private messages are weakly encrypted to protect them from
      the curious eyes of the unscrupulous, inept (and bored) Sysop. This really
      <em>is</em> weak. The unscrupulous but expert Sysop could crack this in a
      flash, but at least the contents aren't clearly visible to anyone. If you
      need strong encryption for private messages, I recommend you look into
      transparently encrypted filesystems. Although this still doesn't cure the
      Bastard Sysop From Hell problem, it keeps things safe from outsiders. Only
      private messages are encrypted. Public messages have this field set to
      zero.

    - @c club. The name of the club this message was published in. Set to the
      empty string if the message is private (in which case, @c cryptkey should
      also be non-zero). The club lacks the conventional leading slash.

    - @c origbbs. The BBS this message was originally posted to. This is useful
      for networked systems.

    - @c magic. A magic number (#MESSAGE_MAGIC) included as sort of an
      afterthought. It should avoid some nasty business with corrupted messages.

    - @c spare. Reserved for future expansion. Do not use.

    - @c origclub. The club the message was originally posted to. Used in
    networking.

    - @c msgid.Along with @c origbbs and <tt>origclub</tt>, this field forms a
      unique identifier for this message. This is used (unsurprisingly) to make
      sure that networked messages don't get exchanged if a system already has
      them.

    - @c replyto. A tentative reference to the number of the message this
      message replies to. Set to zero if this is an original message. Do @e not
      use this! It's a fallback field used in networking. The @c history field
      contains the @e full reference to the original message.

*/

typedef struct {
	char   from    [80];	/**< User ID or RFC-822 address of message sender */
	char   to      [80];	/**< User ID or RFC-822 address of message recipient */
	char   subject [64];	/**< Message subject */
	char   history [80];	/**< History of message */
	char   fatt    [16];	/**< Name of attached file (if any) */
	uint32 msgno;		/**< Message number */
	uint32 flags;		/**< Message flags (<tt>MSF_x</tt>) */
	uint32 crdate;		/**< Creation date */
	uint32 crtime;		/**< Creation time */
	uint32 replies;         /**< Number of replies to this message */
	uint32 timesread;       /**< Times this message was read */
	uint32 timesdnl;        /**< Times the attached file was downloaded */
	uint32 period;          /**< Resurfacing period */
	uint32 cryptkey;        /**< Key for weak private mail cryptography */
	char   club     [16];   /**< Club this message was posted to */
	char   origbbs  [12];   /**< Original BBS message was posted to */
	uint32 magic;		/**< Magic number (<tt>MESSAGE_MAGIC</tt>) */
	char   spare    [16];	/**< A little of spare space */
	char   origclub [16];   /**< Original remote BBS club message was posted to */
	char   msgid    [32];   /**< Message ID (for networking) */
	uint32 replyto;         /**< Reference to a message that this one replies to */
} message_t;


#define MESSAGE_MAGIC "Mmsg"

/** Used to mark a message as intended for all users.

    Do not change after you start using your system. This string does
    <em>not</em> appear to the user. Instead, a nice, user-defined version is
    shown. See? You really, really don't have to change this. */

#define MSG_ALL "***ALL***"

/** @defgroup MSF_flags Message Flags (MSF_x)

    @brief Flags used to describe private and public messages.

    These following flags are available:

    - MSF_EXEMPT. The message is protected from accidental deletion. This
      applies to public messages only. Deletion-exempt messages (also known as
      `tagged' messages) will not be automatically deleted by the system when
      they expire. The sysop will have to `untag' them before being able to
      delete them manually.

    - MSF_RECEIPT. A read receipt has been requested for this message. When the
      recipient reads the message (or uses the off-line mailer to create a
      message packet containing the message), the system will notify the sender
      by personal message. This flag only applies to private messages.

    - MSF_FILEATT. Signifies that this message has a file attached.

    - MSF_APPROVD. Public messages only. It may be necessary to moderate public
      file attachments for viri, illegal content, et cetera. Files attached to
      public messages are, by default, not available for download before an
      operator approves them. This flag is set to denote a public message with
      an approved file attachment. #MSF_FILEATT must also be set. If it isn't,
      the state of this flag should be considered undefined.

    - MSF_CANTMOD. Usually, the sender of a message can modify it, even after
      its delivery (of course, if it's a private message, there's no guarantee
      that the recipient will re-read it). Certain types of messages should not
      be modifiable by their senders. The canonical example is the message sent
      by the system to the Sysop to notify them of a new user signing up. This
      is sent in the user's name, but it is a very bad idea for the user to be
      able to change the message. Can you say `spoof'?

    - MSF_SIGNUP. While we're at it, here's another interesting flag. When the
      sysop is presented with a signup message, they get a very special command
      that <em>deletes the sender of the message</em>! This flag enables this
      command. It's quite obvious that you should stay clear of this one, unless
      you really, @e really know what you're doing!

    - MSF_AUTOFW. Set by the mailing subsystem to indicate that a message has
      been auto-forwarded. Auto-forwarding is the Megistos equivalent of
      forwarding Internet mail with <tt>.forward</tt> files. People can specify
      an alternative username to receive all their mail instead of them. It's
      useful for people who have multiple IDs and only read messages on one, for
      people away on holidays, et cetera.

    - MSF_REPLY. Set if a message is a reply to another.

    - MSF_NET. Set to indicate that a message was not written locally, but was
      obtained over the network.

@{*/

#define MSF_EXEMPT   0x0001  /**< Message is `tagged', i.e. can't be deleted */
#define MSF_RECEIPT  0x0002  /**< Read receipt requested */
#define MSF_FILEATT  0x0004  /**< A file is attached */
#define MSF_APPROVD  0x0008  /**< The file has been approved by the Sysop */
#define MSF_CANTMOD  0x0010  /**< Sender cannot modify this message */
#define MSF_SIGNUP   0x0020  /**< This is a signup special message */
#define MSF_AUTOFW   0x0080  /**< Message has been auto-forwarded */
#define MSF_REPLY    0x0100  /**< This is a reply to another message */
#define MSF_NET      0x0200  /**< Message came in through the network */

/** Flags to clear when forwarding and copying messages. */
#define MSF_COPYMASK (MSF_FILEATT|MSF_REPLY)

/** Flags to clear when transmitting messages over the network. */
#define MSF_NETMASK  (MSF_EXEMPT|MSF_APPROVD|MSF_FILEATT)

/*@}*/



#define HST_CC      "Cc:"
#define HST_CP      "CpBy:"
#define HST_FW      "FwBy:"
#define HST_NETMAIL "Netmail"
#define HST_RECEIPT "RRR:"
#define HST_REPLY   "ReplyTo:"
#define HST_AUTOFW  "Autofw:"
#define HST_DIST    "Distributed"
#define HST_OFFLINE "Offline"
#define HST_NET     "RemoteBBS:"


/** Preferences for the private mail reader

    This structure holds per-user personal preferences (and other state) used
    by the private mail reader.

    - @c forwardto. Defines recipient user ID for autoforwarding. Please not
      that only BBS users can be recipients. Clubs and RFC-822 email addresses
      aren't valid. Set to the user's own user ID to disable auto-forwarding.

    - @c flags. State-saving flags, in the form of a set of <tt>ECF_x</tt>
      flags.

    - @c prefs. User preferences, in the form of a set of <tt>ECP_x</tt> flags.

    - @c lastmailread. The maximum number of any private message read.

    - @c lastemailqwk. The maximum number of any private message inserted into an
      off-line mail packet.

    - @c magic. A magic number used to detect corrupted structures. This should be
      set to #EMAILUSER_MAGIC.

    - @c dummy. Reserved for future expansion.

*/

struct emailuser {
	char    forwardto[24];	/**< Auto-forward recipient. */
	uint32  flags;		/**< Mail flags (<tt>ECF_x</tt> flags) */
	uint32  prefs;		/**< User preferences (<tt>ECP_x</tt> flags) */
	uint32  lastemailread;	/**< Last email read (maximum msg number) */
	uint32  lastemailqwk;	/**< Last email downloaded (max msg num) */
	uint32  magic;		/**< Magic number (#EMAILUSER_MAGIC) */

	char    dummy [512-44]; /**< Reserved for future expansion */
};


/** This spells 'Memu' on big endians, umeM on little endians. */

#define EMAILUSER_MAGIC "Memu"

/** @defgroup ECP_flags User Mail Preference Flags (ECP_x)

    @brief Flags used to describe user preferences as regards private email
    reading.

    The following flags are available:

    <ul>
    <li>@c ECP_QUOTEYES and @c ECP_QUOTEASK. Two-bit (pardon the pun) setting that
      controls whether or not messages are quoted when replying to them. The
      following combinations are valid:

      - None: no quoting at all.

      - @c ECP_QUOTEASK: when replying to a message, the user is asked if they
        want the message quoted or not. The state of #ECP_QUOTEYES is a
        don't-care.
    
      - @c ECP_QUOTEYES: always quote messages without asking.

    <li>@c ECP_LOGINYES and @c ECP_LOGINASK. Another two-bit setting that controls
      how new mail is presented to the user. The following three combinations
      are valid:

      - None: users are notified about new messages immediately after they
        login. No further action is taken.

      - @c ECP_LOGINYES: users are immediately and unconditionally taken to the
        Email module to read their mail on login. Quite intrusive.
    
      - @c ECP_LOGINASK: if new mail exists, users are asked if they wish to
        read it immediately. On positive answer, they are taken to the Email
        module to read their messages. Otherwise, they can always read their
        mail afterwards. If #ECP_LOGINASK is set, the state of #ECP_LOGINYES is
        a don't-care.

     </ul>
*@{*/

#define ECP_QUOTEYES 0x0001	/**< Always quote */
#define ECP_QUOTEASK 0x0002	/**< Ask before quoting */
#define ECP_LOGINYES 0x0004	/**< Unconditionally read mail on login */
#define ECP_LOGINASK 0x0008	/**< Ask if user wants to read mail on login */

/*@}*/



/** @defgroup User Mail Flags (ECF_x)

    @brief Flags used to store user state with respect to mail reading.

    - @c ECF_QSCCFG. The user has configured their quickscan. The clubs module
      takes the user into the quickscan configuration tool on the user's first
      visit to the module. After the first quickscan, this flag is set and the
      Clubs module behaves the normal way.

@{*/

#define ECF_QSCCFG   0x0001	/**< User has configured quickscan. */

/*@}*/



/** Per-user, per-club message reading state.

    This structure holds per-user, per-club preferences and state used by the
    public message reader (the Clubs module).

    - @c club. Name of club this structure applies to.

    - @c lastmsg. The maximum number of any public message read (in
      <tt>club</tt>).

    - @c flags. State-saving flags, in the form of a set of {\tt LRF_x</tt>
      flags.

    - @c emllast. Like <tt>lastmsg</tt>, but used by the Email reader (don't
      ask, it's messy).

    - @c entrymsg. General-purpose temporary variable.

    - @c qwklast. Like <tt>lastmsg</tt>, but used by the off-line mailer.

    - @c magic. A magic number used to detect corrupted structures. This should
      be set to #EMAILUSER_MAGIC.

    - @c dummy. Reserved for future expansion (not much of it, mind).

*/

struct lastread {
	char   club[16];	/**< Club to which preferences apply */
	uint32 lastmsg;		/**< Last message read in club */
	uint32 flags;		/**< Last-read flags (<tt>LRF_x</tt>) */
	uint32 emllast;		/**< Last club message read from Email module */
	int32  entrymsg;	/**< General purpose temporary field */
	uint32 qwklast;		/**< Last message downloaded in msg packet */
	uint32 magic;		/**< Magic number (<tt>LASTREAD_MAGIC</tt>) */

	char dummy[4];		/**< Reserved space */
};


 /** Magic number for <tt>lastread</tt>. */

#define LASTREAD_MAGIC "Mlrd"




/** @defgroup LRF_flags Last-Read Block Flags (LRF_x)

    @brief Flags used to store state with respect to public mail reading.

    Here are the available flags:

    - @c LRF_QUICKSCAN. The @c club is in this user's quickscan list. I will be
      scanned automatically for new messages, along with the other quickscanned
      clubs.

    - @c LRF_INQWK. Similarly, @c club is included in this user's off-line mail
      packets.

    - @c LRF_DELETED. Last-read blocks are stored in sparse arrays (I'm
      lazy). When a last-read block is deleted, this flag is set. The next
      addition of a last-read block will overwrite the first entry with the @c
      LRF_DELETED flag set.

    - @c LRF_INITQWK. Used by the off-line mailer to initialise the last-read
      pointers.

@{*/

#define LRF_QUICKSCAN 0x0001	/**< Club is in user's quickscan */
#define LRF_INQWK     0x0002	/**< Club is in user's off-line packets */
#define LRF_DELETED   0x0004	/**< This preference block has been deleted */
#define LRF_INITQWK   0x0010	/**< For use by the off-line mailer. */

/*@}*/



/** Club header.

    This structure describes all aspects club, except per-user access levels
    (except except Club operator accesses), the club's banner and
    messages. This really is a biggy. Allrighty, here goes:

    - @c club. Short name of the club.
    - @c magic. A magic number (#CLUBHEADER_MAGIC).
    - @c reserved. ...for future expansion.

    - @c clubidq. A unique integer identifying this club. Historically, the
      Major BBS stored its club headers in a statically allocated array, which
      imposed a (usually quite low) limit on the maximum number of clubs. The
      club ID was used as an index in that array. Megistos doesn't do this (I'm
      not <em>that</em> lazy), but the (braindead, IMHO) QWK format still needs
      club indices.

    - @c descr. A 63-character short description of the club. Typically
      describes the club's content, or gives the club motto. It's usually
      displayed right next to the club's name, if there's space.

    - @c clubop. The user ID of the main club's operator (ClubOP). At least one
      user must be associated with the club in this way. Further (identically
      privileged) clubops may be added by setting their individual access levels
      in the club.

    - @c crdate, @c crtime. Old-style club creation date and time. We kept these
      in view of the eventual migration to a 64-bit <tt>time_t</tt>.

    - @c msgno. Highest message number in this club.

    - @c nmsgs. Number of messages existing in the club at the time of the last
      cleanup.

    - @c nper. Number of periodic messages existing in the club at the time of the
      last cleanup.

    - @c nblts. Number of bulletins associated with the club at the time of the
      last cleanup.

    - @c nfiles. Number of files in the club at the time of the last
      cleanup. Approved and unapproved files are included in this count.

    - @c nfunapp. Number of @e unapproved files in the club at the time of the
      last cleanup.

    - @c keyreadax. Key needed to read this club (or, indeed, @e see it in
      lists).

    - @c keydnlax.  Key needed to download files from this club.

    - @c keywriteax. Key needed to write messages in this club.

    - @c keyuplax. Key needed to upload files to this club.

    - @c flags. Flags describing this club, as a set of <tt>CLF_x</tt>
      constants.

    - @c postchg. Charge (in credits) for posting a message to this club. Can be
      negative, in which case users get rewarded.

    - @c uploadchg. Charge (in credits) for uploading a file to this club. Can
      be negative, in which case users get rewarded.

    - @c dnloadchg. Charge (in credits) for downloading a file to this club. Can
      be negative, in which case users get rewarded.

    - @c credspermin. Credits per 100 minutes spent while the user is in the
      club. To charge 2.5 credits per minute, set this field to 250. Negative
      values reward the user. Zero means being in the club consumes no
      credits. A special case: <tt>-1</tt> is the default credit consumption
      rate for the Clubs module.

    - @c export_access_list. Access control list for networked clubs. This
      string specifies which remote systems can or can't access this club.

*/

struct clubheader {
	char     club[16];	/**< Name of the club */
	uint32   magic;		/**< Magic number (<tt>CLUBHEADER_MAGIC</tt>) */
	char     reserved[12];	/**< For future expansion */
	uint32   clubid;	/**< Number of the club */
	char     descr[64];	/**< Club description */
	char     clubop[24];	/**< Main club operator */
	uint32   crdate;	/**< Club creation date */
	uint32   crtime;	/**< Club creation time */
	
	uint32   msgno;		/**< Highest message number */
	uint32   nmsgs;		/**< Number of messages */
	uint32   nper;		/**< Number of periodic messages */
	uint32   nblts;		/**< Number of bulletins */
	uint32   nfiles;	/**< Number of files */
	uint32   nfunapp;	/**< Number of unapproved files */
	
	bbskey_t keyreadax;	/**< Key required for read access */
	bbskey_t keydnlax;	/**< Key required for download access */
	bbskey_t keywriteax;	/**< Key required for write access */
	bbskey_t keyuplax;	/**< Key required for upload access */
	
	uint32   flags;		/**< Club options */
	
	int32    msglife;	/**< Message lifetime */
	int32    postchg;	/**< Charge for posting */
	int32    uploadchg;	/**< Charge for uploading */ 
	int32    dnloadchg;	/**< Charge for downloading */
	int32    credspermin;	/**< Credits*100 mins, -1=default */
	
	char export_access_list[128]; /**< Allow/deny access list */
	
	char dummy[1024-324];
};


#define CLUBHEADER_MAGIC "Mclb"


/** @defgroup CLF_flags Club Flags (CLF_x)

    @brief Flags used to describe clubs in the club header.

    There are three flags defined here, but, to the best of my knowledge, they
    are vestigial. I certainly can't find a reference to them anywhere.

@{*/

#define CLF_MMODAX 0x0001	/**< Unknown/unused */
#define CLF_MMODCH 0x0002	/**< Unknown/unused */
#define CLF_MMODHD 0x0004	/**< Unknown/unused */

/*@}*/


/** @defgroup CAX_levels Club Access Levels (CAX_x)

    @brief These constants denote the various club access levels.

    You'll notice the access level values are nicely spaced out to allow for
    future expansion. Here they are:

    - @c CAX_SYSOP. We're not worthy! We're not worthy! We're scum!  Sysops can,
      of course, do anything they want in clubs.

    - @c CAX_CLUBOP. All hail the mighty clubop! These guys are normal users,
      but have operator privileges within their respective clubs.

    - @c CAX_COOP. Like clubops, but can't modify users' access levels and are
      limited in a few other minor ways.

    - @c CAX_UPLOAD. Full access, normal user. Can read and write messages, as
      well as download and upload files. Their files need operator approval

    - @c CAX_WRITE. Like above, but can't upload files: they can read and write
      messages and download files only.

    - @c CAX_DNLOAD. Like above, but can't write messages: they can only read
      messages and download files.

    - @c CAX_READ. Like above, but can't even download files: they can only read
      club messages.

    - @c CAX_ZERO. Absolutely no access. Users in this level can't even see the
      club in club lists.

    - @c CAX_DEFAULT. Transparent access level. Used in per-user access level
      specifications to mean `don't make exceptions for this user, use whatever
      default access is defined for this club'. This `level' effectively removes
      a per-user specification of access levels. Not stored anywhere, used only
      internally while changing levels.

@{*/

#define CAX_SYSOP    70
#define CAX_CLUBOP   60
#define CAX_COOP     50
#define CAX_UPLOAD   40
#define CAX_WRITE    30
#define CAX_DNLOAD   20
#define CAX_READ     10
#define CAX_ZERO      0
#define CAX_DEFAULT  -1

/*@}*/


/* Guest flags for the IHAVE structures */

#define IHT_MESSAGE        0
#define IHT_CONTROL_DELETE 1	/* oooh, can we have ALT too? */



#endif /* MAIL_H */

/*@}*/

/*
LocalWords: Alexios doc tt BBS legalese alexios Exp bbs struct clubheader
LocalWords: MetaBBS IHAVE DistClubs GPL ifndef VER endif RFC MSG em fatt
LocalWords: Majoresque ATT achment msgno MSF crdate crtime int timesread
LocalWords: timesdnl Megistos cryptkey Sysop Sysop origbbs origclub msgid
LocalWords: replyto uint Mmsg sysop untag FILEATT APPROVD viri CANTMOD IDs
LocalWords: SIGNUP signup AUTOFW username COPYMASK NETMASK HST CC Cc CP FW
LocalWords: CpBy FwBy NETMAIL Netmail RRR ReplyTo Autofw DIST OFFLINE ECF
LocalWords: Offline RemoteBBS forwardto autoforwarding prefs ECP EMAILUSER
LocalWords: lastmailread lastemailqwk emailuser lastemailread msg num Memu
LocalWords: endians umeM QUOTEYES QUOTEASK LOGINYES LOGINASK QSCCFG LRF
LocalWords: quickscan lastmsg emllast entrymsg qwklast lastread Mlrd INQWK
LocalWords: quickscanned INITQWK biggy Allrighty clubid braindead IMHO QWK
LocalWords: descr clubop ClubOP clubops nmsgs nper nblts nfiles nfunapp
LocalWords: keyreadax keydnlax keywriteax keyuplax CLF postchg uploadchg
LocalWords: dnloadchg credspermin bbskey msglife mins Mclb MMODAX MMODCH
LocalWords: MMODHD CAX Sysops DNLOAD IHT oooh ALT
*/
