/** @file    useracc.h
    @brief    Definitions related to user accounts.
    @author  Alexios

    This header declares a veritable hodge-podge of structures and functions
    dealing with user accounts. There is a wide collection of low-level and
    high-level functions. Some of these could be living somewhere else, but
    they seem to fit right here.

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     useracc.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Define data structures used for storing users et al.         **
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
 * Revision 1.5  2003/12/19 13:25:18  alexios
 * Updated include directives.
 *
 * Revision 1.4  2003/09/27 20:32:38  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.11  2000/01/06 11:40:19  alexios
 * Added field lastconsolepage to denote the time of the user's
 * last page to the console (if any). The field was, of course,
 * added to the onlinerec structure.
 *
 * Revision 0.10  1998/12/27 15:19:19  alexios
 * Added user magic numbers and declarations for the functions
 * migrated from miscfx.h.
 *
 * Revision 0.9  1998/08/14 11:23:21  alexios
 * Added on-line flag to tell bbsd and emud that we're not
 * logging off completely (this is only for auditing purposes).
 *
 * Revision 0.8  1998/07/26 21:17:06  alexios
 * Added a flag to force idle zapping of users on telnet
 * connections.
 *
 * Revision 0.7  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.6  1997/11/06 16:49:10  alexios
 * Renamed USY_AUDITPAGE to USY_PAGEAUDIT so it's easier to
 * find in the remsys module. Added new command flags for the
 * new commands in remsys (USY_SECURITY, USY_SIGNUPS and
 * USY_FILTAUD).
 *
 * Revision 0.5  1997/11/05 10:52:05  alexios
 * Cosmetic changes. Added field auditfiltering in useracc to
 * store operator's audit filtering preferences. Added remote
 * sysop command flags USY_AUDITPAGE. Changed the values of
 * USY_INVIS and USY_GDET (shouldn't have; they're not in
 * alpha order anyway). Obsoleted OLF_SOPAUD since
 * useracc.auditfiltering is used now.
 *
 * Revision 0.4  1997/11/03 00:29:40  alexios
 * Removed defines for hardwired xlation tables, added code
 * and defines for generalised tables.
 *
 * Revision 0.3  1997/09/12 12:48:48  alexios
 * Added the last selected library to onlinerec. Also added a
 * field injothqueue to hold the IPC ID of the injoth queue for
 * this user.
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Added OLF_LOGGEDOUT to distinguish between normal and unexpected
 * disconnections from the system.
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



#ifndef USERACC_H
#define USERACC_H

#ifndef CHAR
#define CHAR unsigned char
#endif

#include <megistos/config.h>


/** @defgroup useracc User Account Handling

    This part of the API defines structures used to manage user
    accounts and operators on them.

@{ */




#define DELIM    "!@#$%^&*-_=+.:"

/** User account structure.

     This is the permanent user account record. It holds a user's particulars,
     along with additional preferences, access levels, statistics and state
     information. This is a pretty long structure. Here's a length description
     of the fields. I've grouped similar fields together to make the
     description a bit more readable:

     - @c userid, @c passwd, @c username, @c company, @c address1, @c address2,
       @c phone, @c age, @c sex. The user's particulars. Things that we need to
       know for billing, et cetera: the user's user ID (their handle within the
       system), their password, full name, company name (if any), address (two
       lines), contact phone number, age (in years) and sex (`yes, please'
       isn't an option --- see the <tt>USX_x</tt> constants).

     - @c prefs, @c flags. A set of preferences and flags respectively,
       comprising of @c UPF_x flags and @c UFL_x flags respectively (the flags
       are ORred together).

     - @c sysaxs. An array of flags, each of which corresponds to one operator
       command or privilege. Have a look at the @c USY_x flags for a full
       description.

     - @c system. The user's system, for statistics.

     - @c language. The user's preferred language number.

     - @c scnwidth, @c scnheight. User's preferred screen resolution (columns,
       rows respectively).

     - @c datecre, @c datelast. The date (and time, under the new API) of the
       account's creation and last login.

     - @c passexp. Counts the days until the user's password expires.  Set to
       zero to denote that the user's password will @e not expire.

     - @c tempclss, @c curclss. The user's temporary class and permanent
       class. User classes are a way of managing user accounts with
       subscriptions, freebies, et cetera. The temporary class is where a user
       is placed when they run out of credits. The user stays in this class for
       the remainder of the day, until the daily cleanup either moves them to a
       new class or back to their original one.

     - @c timetdy. User's total connection time for today (i.e. after the last
       cleanup).

     - @c classdays. Number of days since the user was moved to their current
       permanent class.

     - @c credits. Credits left.

     - @c totcreds, totpaid. Respectively, the total number of credits debited
       to this account, ever, and the total number of @e paid credits debited
       to this account. The number of free credits debited to the account is
       equal to <tt>totcreds-totpaid</tt>.

     - @c keys. The user's personal keyring.

     - @c timever, credsever. The total time the user has spent online, and the
       total number of credits spent ever.

     - @c pagetime, pagestate. The time (in minutes) that must pass between
       pages to this user. This is done so as not to annoy the user. Not many
       people use it, at least on our systems. The page state restricts paging
       to the user in a small range of ways, listed as the <tt>PGS_x</tt>
       constants.

     - @c filesdnl, @c bytesdnl, @c filesupl, @c bytesupl, @c msgswritten, @c
       connections. Respectively the number of files downloaded by the user,
       the grand total of bytes downloaded, files and bytes uploaded, total
       number of messages written and total number of connections made
       ever. These are used for statistical purposes.

     - @c lastclub. The last club accessed by the user. This is remembered in
       between sessions.

     - @c auditfiltering. Flags used to decide which audit trail entries (if
       any) are to be paged to the user. Uses the <tt>AUX_x</tt> flags, the
       same ones used by the audit trail functions to flag different severities
       and types of entries.

*/

typedef struct {
	char     userid   [24];    /**< User ID.                              */
	char     passwd   [16];    /**< Password.                             */
	char     username [32];    /**< Real name.                            */
	char     company  [32];    /**< User's company.                       */
	char     address1 [32];    /**< Address, line 1 of 2.                 */
	char     address2 [32];    /**< Address, line 2 of 2.                 */
	char     phone    [24];    /**< Phone number.                         */
	uint32   prefs;            /**< Preference flags (<tt>UPF_x</tt> flags). */
	uint32   flags;            /**< General flags (<tt>UFL_x</tt> flags).    */
	uint32   sysaxs   [ 3];    /**< Sysop flags (<tt>USY_x</tt> constants).  */
	uint8    age;              /**< Age in years.                         */
	char     sex;              /**< Sex (<tt>USX_x</tt> constants).          */
	uint8    system;           /**< User's computer system type.          */
	uint8    language;         /**< Language preferred.                   */
	uint8    scnwidth;         /**< Screen width (columns, usually 80).   */
	uint8    scnheight;        /**< Screen height (rows, usually 24).     */
	uint32   datecre;          /**< Date user signed up.                  */
	uint32   datelast;         /**< Date last logged on.                  */
	int32    passexp;          /**< Days till password expires.           */
	char     tempclss [10];    /**< Previous Class.                       */
	char     curclss  [10];    /**< Current Class.                        */
	int32    timetdy;          /**< Time spent today.                     */
	int32    classdays;        /**< Days spent in current class.          */
	uint32   credits;          /**< Credits left.                         */
	int32    totcreds;         /**< Total credits received ever.          */
	int32    totpaid;          /**< Total paid credits received ever.     */
	bbskey_t keys[KEYLENGTH];  /**< Personal keyring array.               */
	uint32   timever;          /**< Total online time spent ever.         */
	uint32   credsever;        /**< Total credits spent ever.             */
	int32    pagetime;         /**< Time between allowing pages.          */
	int32    pagestate;        /**< Page prefs (<tt>PGS_x</tt> flags)        */
	uint32   filesdnl;         /**< Total number of files downloaded.     */
	uint32   bytesdnl;         /**< Number of bytes downloaded.           */
	uint32   filesupl;         /**< Number of files uploaded.             */
	uint32   bytesupl;         /**< Number of bytes downloaded.           */
	uint32   msgswritten;      /**< Number of messages written.           */
	uint32   connections;      /**< Number of connections.                */
	char     lastclub[16];     /**< Last club visited.                    */
	uint32   auditfiltering;   /**< Flag mask for showing audit paging.   */
	
	char     dummy[1020-348];  /**< Scratch space. */
	char     magic[4];         /**< Magic number (<tt>USR_MAGIC</tt>).       */
} useracc_t;


/** User account magic. */

#define USR_MAGIC     "USER"


/** @defgroup UPF_flags User preference flags

    @brief User preference flags.

    These flags denote permanent user preferences as regards translation modes,
    ANSI directives, et cetera.

    - @c UPF_ANSION. If this flag is set, ANSI output is preferred by the user.

    - @c UPF_VISUAL. Set to denote that the user prefers visual (full-screen)
      tools, where these are available.

    - @c UPF_NONSTOP. Ignore the user's screen height; never pause the display
      for the user.

    - @c UPF_ANSIDEF. User likes to leave their ANSI setting to whatever was
      set at login.

    - @c UPF_ANSIASK. User likes to be asked about their ANSI setting at every
      login (if this wasn't already done <em>prior</em> to login).

    - @c UPF_TRDEF. User prefers to leave the translation mode to whatever was
      set at login.

    - @c UPF_TRASK. User likes to be asked for a translation mode at every
      login.

    - @c UPF_TR0--UPF_TR3. Four bits denoting the translation table the user
      prefers to use (only valid if @c UPF_TRDEF</tt> and @c PF_TRASK are
      clear).

@{*/

#define UPF_ANSION    0x0001 /**< User likes ANSI directives. */
#define UPF_VISUAL    0x0002 /**< User wants visual tools, where available. */
#define UPF_NONSTOP   0x0004 /**< Don't pause at the bottom the screen. */
#define UPF_ANSIDEF   0x0008 /**< Use channel default ANSI value. */
#define UPF_ANSIASK   0x0010 /**< Ask about use of ANSI at login. */
#define UPF_OBSOLETE  0x0020 /**< Obsolete flag value; re-use at will. */
#define UPF_TRDEF     0x0040 /**< Use default channel translation. */
#define UPF_TRASK     0x0080 /**< Ask for translation mode at login. */
#define UPF_TR0       0x0100 /**< Translation mode, bit 0. */
#define UPF_TR1       0x0200 /**< Translation mode, bit 1. */
#define UPF_TR2       0x0300 /**< Translation mode, bit 2. */
#define UPF_TR3       0x0400 /**< Translation mode, bit 3. */

#define UPF_TRANS     (UPF_TR0|UPF_TR1|UPF_TR2|UPF_TR3)
#define UPF_TRSHIFT   8



/** Extract permanent translation mode from user account.

    The following macro extracts the 0--9 (0--15, actually) translation table
    number from the user's flags. 

    @param u A user @e account structure, <tt>useracc_t</tt>. Pass the
    structure itself, not a pointer to it.

    @return The translation table specified by the user's preference flags.  */

#define usr_getpxlation(u)   (((u).flags&UPF_TRANS)>>UPF_TRSHIFT)


/** Set permanent translation mode in user account.

    This macro sets the translation mode in the user preference flags.

    @param u A user <em>account</em> structure, <tt>useracc_t</tt>. Pass the
    structure itself, not a pointer to it. 

    @param i The new translation mode. */

#define usr_setpxlation(u,i) ((u).flags=((u).flags&~UPF_TRANS)|\
			  (((i)&0xf)<<UPF_TRSHIFT))

/*@}*/




/** @defgroup USY_flags Sysop commands and privileges

    @brief Sysop command and privilege constants.

    These constants are used inside <tt>useracc_t</tt> to encode any sysop
    command and/or privileges the user may have. There is a wide range of
    these, roughly broken in seven categories:

    <ul>
    <li> Channel management.

      - @c USY_CHANGE. Change mode of one channel, or all of them. Allows the
        Sysop to set certain channels to <tt>BUSY-OUT, NO-ANSWER</tt>, et
        cetera. Any change of status of a free telnet channel will affect all
        telnet lines.

      - @c USY_EMULATE. Allows the Sysop to see `with the eyes of a
        user'. Everything the user sees or types is presented to the operator
        and everything the sysop types appears like it was typed by the
        user. This enables the operator to help stuck users.

      - @c USY_MONITOR. Watches all input of all users. Unlike monitor, this
        only works with software that co-operates with the BBS (i.e. modules et
        cetera).

      - @c USY_SEND. Sends an operator message to one user or all users. This
        is slower to do than a page, but is much more official.

    <li> User account management

      - @c USY_DELETE. Marks a user for deletion. If the user is online, they
        are kicked out immediately. The actual deletion will take place at the
        coming cleanup. Until then, the same command can be used to lift the
        deletion mark from the victimised user.

      - @c USY_DETAIL. Display detailed information on the user's account. Some
        of the information may be restricted, depending on the BBS setup and
        the operator's access levels.

      - @c USY_EXEMPT. Forbids the system to delete a user. Deletions,
        automatic or otherwise, will not affect the specified user. Use the
        same command again to lift the exemption flag.

      - @c USY_HANGUP. Hangs up a channel, effectively kicking out a user.

      - @c USY_POST. Credit a user's account with free or paid credits.

      - @c USY_SEARCH. Search the database of user accounts. This command
        allows for powerful search criteria.

      - @c USY_SUSPEND. Suspends a user. If the user is online, they are kicked
        out. Suspended users cannot enter the system, getting a suitable
        message every time they try. You can lift the suspension by using the
        same command on a suspended user.

    <li> Logs, events and file transfer

      - @c USY_AUDIT. View the audit trail, starting either with the most
        recent or oldest entry first.

      - @c USY_CLEANUP. As above, but shows the cleanup log instead.

      - @c USY_EVENT. The event manager allows the operator to schedule
        commands to execute at specified times in the day.

      - @c USY_LOGON. Set the logon message-of-the-day for one channel or for
        all channels. A channel will display both its own, individual message
        and the global message at the login screen, provided of course the
        messages exist.

      - @c USY_TRANSFER. Allows the operator to upload and download BBS files.

      - @c USY_SECURITY. Like @c USY_AUDIT, but filters the audit trail for
        security-related entries.

      - @c USY_SIGNUPS. Like @c USY_SECURITY, but only shows new signups.

      - @c USY_FILTAUD. Allows complex filtering of the audit trail, including
        masking severity levels and specified entry types.

    <li> Statistics
    
      - @c USY_AGESTATS. Age demographics. Shows user ages, language use,
        computer systems, et cetera.

      - @c USY_CLSSTATS. Shows user class statistics.

      - @c USY_GENSTATS. Generates user defined bar-graphs plotting a number of
        quantities against another range of quantities, over a specified range
        of time and providing totals or averages.

      - @c USY_LINSTATS. UNIX/Linux statistics. Gives information on the system
        hosting the BBS.

      - @c USY_MODSTATS. Module usage statistics.

      - @c USY_SYSTATS. System-wide statistics: stuff like number of messages
        written, total number of connections, et cetera.

      - @c USY_TOP.Shows a wide range of top-<em>N</em>s (where {\em N</tt> is
        configurable) for things like the oldest user accounts, users with the
        most downloads or uploads, clubs with the most messages, et cetera.

    <li> User classes and keys
    
      - @c USY_CLASS. Moves a user from one class to another.

      - @c USY_CLASSED. The class editor allows the operator to manage classes
        by creating new ones, editing existing ones, and deleting old ones. All
        aspects of classes can be controlled, and users can be mass-moved from
        one class to another.

      - @c USY_KEYS. Edit a user's personal keyring.

    <li> Filing and command execution

      - @c USY_COPY. Copy a file, in a similar way to the shell command
        <tt>cp</tt>. Existing target files will be clobbered without
        confirmation!

      - @c USY_DEL. Remove a file, much like the shell command {\tt rm}. No
        confirmation will be required!

      - @c USY_DIR. Show the files in a directory.

      - @c USY_EDITOR. Run the editor on a file.

      - @c USY_REN. Rename a file, just like the shell command @c mv.

      - @c USY_SHELL. Run a child UNIX shell. This is a gigantic security
        risk. Only operators of the utmost trust should be granted this
        command, and only those who can use UNIX. As you probably know, the
        shell isn't exactly forgiving!

      - @c USY_SYS. Execute a UNIX command. Give this command to the same
        people who'd get the one above. If you have this command, running a
        full-blown shell is trivial.

      - @c USY_TYPE. Print the contents of a file, like the shell command
        <tt>cat</tt> would do.

    <li> Filing and command execution
    
      - @c USY_PAGEAUDIT. Pages the operator with audit trail entries, whenever
        they are logged. Using this command, the operator can select which
        severities and types of messages will be paged. This removes
        unnecessary noise on a large system, where unimportant audit trail
        entries fly by all the time.

      - @c USY_INVIS. Denotes the presence of the @e invisibility
        privilege. Operators owning this privilege can use the <tt>/invis</tt>
        global command to become `invisible' by other users. Invisible
        operators can only be seen and paged by operators with the @c USY_SYSOP
        privilege. Thus, an operator with @c USY_INVIS but without @c
        USY_SYSOP can turn invisible, but is isolated from everyone. Not a
        particularly bad idea, when you need to do some work on a large system.

      - @c USY_GDET. Denotes the presence of the <em>global detail</em>
        privilege. This enables the command <tt>/l</tt> which is synonymous to
        the <tt>USY_DETAIL</tt> command here: it displays the specified user's
        account particulars. Some fields may be hidden depending on the
        operator's access levels. Global detail hides different fields from
        <tt>USY_DETAIL</tt>, due to the global nature of the command.

      - @c USY_SYSOP, @c USY_MASTERKEY. Implies that this operator is a
        full-blown Sysop of the system. Keys no longer apply to them, and they
        can bypass most restrictions. For all intents and purposes, they behave
        a bit like <tt>root</tt> does on a UNIX system. Of course, this does
        not imply that Sysops are the UNIX superuser! Only one user can
        actually run this command: the user with ID `Sysop' (or whatever is
        specified by the <tt>SYSOP</tt> macro in <tt>config.h</tt>). For all
        other users, it is a mere notification of the Sysop privilege. Sysop
        can use this command to grant and life privileges and commands to other
        users, promoting them to operators or demoting them back to ordinary
        users.

    </ul>

@{*/

#define USY_CHANGE      0	/**< Alter channel modes. */
#define USY_EMULATE     1	/**< Emulate a user. */
#define USY_MONITOR     2	/**< Monitor all input. */
#define USY_SEND        3	/**< Send sysop message to user or all users. */
#define USY_DELETE     10	/**< Delete a user. */
#define USY_DETAIL     11	/**< User account information. */
#define USY_EXEMPT     12	/**< Delete-(un)protect a user. */
#define USY_HANGUP     13	/**< Hang up a channel. */
#define USY_POST       14	/**< Give credits to a user. */
#define USY_SEARCH     15	/**< Search user accounts. */
#define USY_SUSPEND    16	/**< (Un)suspend a user's account. */
#define USY_AUDIT      20	/**< View audit trail. */
#define USY_CLEANUP    21	/**< View cleanup logs. */
#define USY_EVENT      22	/**< Event manager. */
#define USY_LOGON      23	/**< Change logon messages. */
#define USY_TRANSFER   24	/**< Upload or download files. */
#define USY_SECURITY   25	/**< Security logs (subset of audit trail). */
#define USY_SIGNUPS    26	/**< Signup logs (subset of audit trail). */
#define USY_FILTAUD    27	/**< Search audit trail. */
#define USY_AGESTATS   30	/**< Demographic statistics. */
#define USY_CLSSTATS   31	/**< User class statistics. */
#define USY_GENSTATS   32	/**< Generic, user-defined statistics. */
#define USY_LINSTATS   33	/**< Linux/UNIX operating system statistics. */
#define USY_MODSTATS   34	/**< Module usage statistics. */
#define USY_SYSTATS    35	/**< System statistics. */
#define USY_TOP        36	/**< Various top-<em>n</em> charts. */
#define USY_CLASS      40	/**< Change user class. */
#define USY_CLASSED    41	/**< User class manager. */
#define USY_KEYS       42	/**< Edit user's personal keyring. */
#define USY_COPY       50	/**< Copy a file. */
#define USY_DEL        51	/**< Remove a file. */
#define USY_DIR        52	/**< Produce file listing. */
#define USY_EDITOR     53	/**< Text file editor. */
#define USY_REN        54	/**< Rename a file. */
#define USY_SHELL      55	/**< UNIX shell escape. */
#define USY_SYS        56	/**< Execute a UNIX command. */
#define USY_TYPE       57	/**< View contents of a file. */
#define USY_PAGEAUDIT  90	/**< Set types of audit entries to be paged. */
#define USY_INVIS      91	/**< Sysop invisibility privilege. */
#define USY_GDET       92	/**< Global detail privilege. */
#define USY_SYSOP      95	/**< User is a Sysop (same as below). */
#define USY_MASTERKEY  95	/**< User is a Sysop (same as above). */

/*@}*/


/** @defgroup UFL_flags User account flags (UFL_x)

    @brief User account flags.

    These flags flag a user's account in different ways.

    - @c UFL_SUSPENDED. User's account has been suspended.

    - @c UFL_DELETED. User has been marked for deletion. The account will be
      deleted at the coming cleanup.

    - @c UFL_EXEMPT. User cannot be deleted.

@{*/

#define UFL_SUSPENDED 0x00000001 /**< User has been suspended. */
#define UFL_DELETED   0x00000002 /**< User is marked for deletion tonight. */
#define UFL_EXEMPT    0x00000004 /**< User is exempt from deletions. */

/*@}*/


/** @defgroup USX_flags User sexes (USX_x)

    @brief User sexes.

    These flags give a user's sex. We take the prude approach and only define
    the two biological sexes. Feel free to make any additions yourself nd send
    us a patch for the sheer heck of it.

    - @c USX_MALE. User is male.

    - @c USX_FEMALE. User is female.

@{*/

#define USX_MALE   'M'		/**< User is male. */
#define USX_FEMALE 'F'		/**< User is female. */

/*@}*/



/** User class.

    This structure describes one user class. Classes are there to help you
    manage your users in a large system, with many different types of people
    and services. For instance, you can design a monthly subscription system
    whereby users pay to get full access for a month. Or, you could make a
    class where people are allowed two hours a day online time for a month,
    then are moved to a full-access class where the normal credit charging
    system applies. The possibilities are endless.

    The set of classes in use define a graph. Transitions between classes
    happen based on various events: the user's absence from the system; the
    user staying in a class for a number of days; the user running out of
    credits; and the user receiving credits. The operator can also move a user
    to an arbitrary class.

    Here are the class fields. They'll show exactly what you can do with
    classes.

    - @c name. The name of the class. For no reason in particular, convention
      is to make class names upper case.

    - @c notaround, @c nadays. This pair of fields define the name of a class
      (<tt>notaround</tt>) the user will be moved to if they don't use the
      system for @c nadays days. This is useful for revoking privileges of
      people who've stopped using the system. Setting @c notaround to be equal
      to @c name effectively disables this class transition.

    - @c around, @c ardays. Like above, but the user is moved to class
      <tt>around</tt> if they've been in their current class for at least @c
      ardays. Setting @c around to be equal to @c name effectively disables
      this class transition.

    - @c nocreds, @c credpost. Users running out of credits are temporarily
      moved to class specified by @c nocreds for the rest of the day (provided
      the coming cleanup posts credits to them). Users receiving credits are
      moved to the class specified by @c credpost. Disabling this transitions
      is done in the usual manner, setting the target class to @c name.

    - @c limpercall, @c limperday. Denote respectively the maximum online time
      per call and maximum daily online time for a user in this
      class. Regardless of the amount of credits a user has, they will be
      (politely) kicked out when they exceed their time limits. For time limits
      on a per-call basis, the user can redial later and get another @c
      limpercall minutes online, as long as they have credits. These values may
      be set to -1 to denote no limitations on time.

    - @c crdperday. Specifies the minimum number of credits the user should
      have at the beginning of each day. If the user has less credits than @c
      crdperday, the cleanup process posts enough credits to bring the user to
      the minimum. If the user has more credits than the minimum, nothing is
      done.

    - @c crdperweek, crdpermonth. These fields specify bonuses (or taxes, if
      negative) given to users on a weekly and monthly basis. Unlike the above
      field, these amounts are <em>posted</em> to the user's account (i.e. they
      don't work as minima).

    - @c flags. A set of flags describing minor features of the class, given by
      zero or more <tt>CLF_x</tt> flags ORred together.

    - @c users. The number of users in this class. Updated every cleanup.

    - @c keys. The class keyring. This is combined with users' personal
      keyrings to provide the full set of keys owned by the user.

*/

typedef struct {
	char     name        [10];    /**< Name of class                          */
	char     notaround   [10];    /**< Class to go to when user not logged on */
	int32    nadays;              /**< ... for nadays number of days          */
	char     around      [10];    /**< Class to go to after user has been     */
	int32    ardays;              /**< ... around for ardays number of days   */
	char     nocreds     [10];    /**< Class to go to when no credits left    */
	char     credpost    [10];    /**< Class to go to when paid creds posted  */
	int32    limpercall;          /**< Time limit per call (-1 disables)      */
	int32    limperday;           /**< Time limit per day (-1 disables)       */
	int32    crdperday;           /**< Free time per day                      */
	int32    crdperweek;          /**< Bonus time posted every week           */
	int32    crdpermonth;         /**< Bonus time posted every month          */
	uint32   flags;               /**< Flags bits                             */
	uint32   users;               /**< Number of users in this class          */
	bbskey_t keys[KEYLENGTH];     /**< 128 Key bits                           */
	
	char dummy[512-104];
} classrec_t;


/** @defgroup CLF_flags Class flags (CLF_x)

    @brief Class behaviour flags.

    These flags modify class behaviour and provide class features.

    - @c CLF_NOCHRGE. Users belonging to this class are exempt from credit
      charges. Their credits are never reduced for any reason. This is useful
      for operators who need to stay online for long periods of time, or for
      monthly subscriptions, where you don't care about credits since the user
      has paid for a month of full access.

    - @c CLF_LINUX. This flag allows users to bypass the BBS and login into the
      underlying Linux system by prepending an at-sign (<tt>@</tt>) to their
      user ID at logon time. Their user ID must also be an existing UNIX
      username (including capitalisation) and they must, of course, have a
      password to gain access to the account.

    - @c CLF_LOCKOUT. Users in this class are unable to login at all. Used in
      the special <tt>DELETED</tt> class (where users go to be deleted) and for
      things like special user account suspension modes.

    - @c CLF_CRDXFER. Members of this class are allowed to transfer credits to
      others. This flag should really be removed and replaced by a key/lock, it
      has no place here.

@{*/

#define CLF_NOCHRGE 0x0002   /**< Class is exempt from credit charges.  */
#define CLF_LINUX   0x0004   /**< Users have access to Linux shell.     */
#define CLF_LOCKOUT 0x0008   /**< Users not allowed to login at all.    */
#define CLF_CRDXFER 0x0010   /**< Allowed to transfer credits to others.*/

/*@}*/

#define ML NUMLANGUAGES


/** User online structure.

    This is a temporary record of user details that change a lot while the user
    is online. Most of the fields are derived from the user's account
    record. The rest are filled in by the system while the user is
    online. Unlike <tt>useracc_t</tt>, this record is not saved to disk.

    - @c userid. The user's handle in the system. Mainly used for sanity
      checks, since including the user ID here is redundant.

    - @c channel. The field name is slightly misleading: it contains the
      <em>device name</em> (minus the <tt>"/dev/"</tt> the user's channel is
      using.

    - @c emupty. This is the device name (minus the {\tt "/dev/"</tt>) where
      processes servicing the user are running. This is not the same as @c
      channel because of @c emud, the emulation/translation daemon, which sits
      on the device denoted by <tt>channel</tt> and creates a new, pseudo-tty
      <tt>emupty</tt> for the processes to run on.

    - @c baudrate. The user's <em>bps</em> rate (@e Baud is such a misnomer),
      as returned by <tt>bbsgetty</tt>. This may be a real bps value if the
      number is positive, or a special, non-positive (i.e less than one) value
      denoting special connections. For instance, telnet connections don't have
      an easily measurable bps rate, so they're denoted as such.

    - @c curpage, @c prevpage. The user's current and previous pages in the
      menu structure of the BBS. Used by the Menu Manager meta-module.

    - @c flags. A set of flags defining per-session, volatile user preferences
      and state. This field is formed by ORring together zero or more of the
      <tt>OLF_x</tt> flags.

    - @c input. User's remaining input before entering a module. Menu Manager
      fills this in before running a module with concatenated commands still to
      be processed. It is the module's responsibility to process those as soon
      as it starts.

    - @c descr. The user's current position in the BBS described in all
      available languages (if available). Again, this is filled in by the Menu
      Manager and is the description of the user's current page,
      <tt>curpage</tt>.

    - @c pagestate, lastpage. The page state restricts paging to the user in a
      small range of ways, listed as the <tt>PGS_x</tt> constants. The
      <tt>lastpage</tt> field gives the time of the last successful page to the
      user. It's used internally to enforce the paging restrictions.

    - @c tick, @c fraccharge. Used internally by the BBS daemon (<tt>bbsd</tt>)
      to charge fraction-credits.

    - @c credspermin. The credit consumption rate for this user (this varies
      with the user's location in the system). The unit is credits per 100
      minutes. That is, for a typical 1 credit per minute, you need to specify
      100 for this field. A value of 250 gives a credit consumption rate of 2.5
      credits per minute.

    - @c onlinetime. The time (in minutes) the user has spent on this
      connection.

    - @c timeoutticks, @c idlezap. The inactivity counter and inactivity
      timeout setting. Used internally. The two fields do not have the same
      units. The former is in @c bbsd @c ticks (fractions of a minute), the
      latter in minutes.

    - @c statptrs, @c statcreds. Used by @c statd, the statistics daemon.
     
    - @c loggedin. Time the user logged in. Used to keep track of the user's
      recent connections.

    - @c telechan, @c telecountdown. State used for the Teleconference
      module. The former field stores the last channel accessed by the user;
      the latter keeps track of the number of times the user is allowed to talk
      in the Teleconference module (this is an optional restriction on non-paid
      users).

    - @c lastlib. State used by the Files module. Denotes the last file library
      (directory) visited by the user.
     
    - @c injothqueue. System V IPC message queue ID used to page messages to
      this user.

    - @c lastconsolepage. The time of the user's last page to the system
      console.

    - @c magic. A magic number used to avoid data corruption. Set to
      <tt>ONL_MAGIC</tt>.

*/

typedef struct { 
	char   userid     [24];     /**< User's ID, just for checking.        */
	char   channel    [16];     /**< User's channel, minus "/dev/".       */
	char   emupty     [16];     /**< Emulation PTY, user's 'real' tty.    */
	int32  baudrate;            /**< User's baud rate.                    */
	char   curpage    [32];     /**< User's current page in the menuman.  */
	char   prevpage   [32];     /**< User's previous menuman page.        */
	uint32 flags;               /**< Generic on-line flags.               */
	char   input      [256];    /**< User's last input concatenation.     */
	char   descr      [ML][44]; /**< User's position described.           */
	uint32 pagestate;           /**< Page enable flags.                   */
	uint32 lastpage;            /**< Time this user was last paged.       */
	uint32 tick;                /**< bbsd ticks (used for credit charge). */
	int32  credspermin;         /**< Credit consumption, creds/100 min.   */
	uint32 onlinetime;          /**< Time (in min) user has been on-line. */
	int32  fraccharge;          /**< Fractional charge (bbsd).            */
	int32  timeoutticks;        /**< Inactivity counter.                  */
	int32  idlezap;             /**< Minutes of inactivity allowed.       */
	int32  statptrs;            /**< Used internally by statd.            */
	int32  statcreds;           /**< Used internally by statd.            */
	uint32 loggedin;            /**< Time logged in: used by /recent.     */
	char   telechan[32];        /**< Last teleconference channel.         */
	int32  telecountdown;       /**< Times left to talk in telecons.      */
	int32  lastlib;             /**< Last file library visited.           */
	int32  injothqueue;         /**< IPC message queue ID for injoth().   */
	uint32 lastconsolepage;     /**< Time of last page to system console. */
	
	char dummy[1020-476-44*ML]; /**< Scratch space. */
	char magic[4];              /**< Online User magic                   */
} onlinerec_t;



#define ONL_MAGIC     "OUSR"


/** @defgroup OLF_FLAGS Online user flags (OLF_x)

    @brief Temporary user state and preferences.

    These flags denote volatile, temporary user preferences as regards
    translation modes, ANSI directives, et cetera.

    - @c OLF_MMEXITING, @c OLF_MMCALLING}, @c OLF_MMCONCAT, @c OLF_MMGCDGO.
      Flags used by the Menu Manager (hence the `<tt>MM</tt>'). @c
      OLF_MMEXITING is used to remind a module to exit after processing a
      concatenated command that originated from outside the module. This flags
      is also set by the module in question so that the Menu Manager can return
      the user to the appropriate page. <tt>OLF_CALLING</tt> is set by the Menu
      Manager prior to calling a module and <tt>OLF_CONCAT</tt> is set by the
      Menu Manager to notify a module that there is concatenated input left
      over for it to process. <tt>OLF_MMGCDGO</tt> is set by a module prior to
      calling the Menu Manager to handle a <tt>/go</tt> global command.

    - @c OLF_ISYSOP. Is obsolete. Feel free to re-use this particular flag
      value.

    - @c OLF_INVISIBLE. Set to indicate that the sysop invisibility mode is
      enabled.

    - @c OLF_BUSY. Set to indicate that the user is in a state where they
      cannot receive or send pages.

    - @c OLF_NOTIMEOUT, @c OLF_FORCEIDLE, @c OLF_ZAPBYPASS. These flags control
      the system's behaviour with respect to inactivity timeouts. @c
      OLF_NOTIMEOUT is set to @e recommend to the system that the user should
      not be kicked out if they are inactive for too long. The system will not
      respect this recommendation if <tt>OLF_FORCEIDLE</tt> is set. This is
      done for telnet lines where the connection may be dropped and an
      inactivity timeout is the best way to trap abruptly lost
      connections. <tt>OLF_ZAPBYPASS</tt> indicates that inactivity timeouts
      should not be applied to this user. Unlike <tt>OLF_NOTIMEOUT</tt>, which
      is a relatively mutable flag, this flag remains constant for a user's
      entire session. Thus, it is used to indicate that the user is a
      privileged operator.<tt>OLF_NOTIMEOUT</tt> is used for temporary
      reprieves while the system is performing some long-winded task.

    - @c OLF_ANSION. Indicates that the user's terminal (emulator) can support
      ANSI X3.64 terminal directives.

    - @c OLF_TR0--UPF_TR3. Four bits denoting the translation table currently
      in use by the user.

    - @c OLF_INHIBITGO. Set to disable the global command @c/go that takes the
      user to an arbitrary Menu Manager page. This is a necessary action if you
      need the user to be `locked' in a module for one reason or another.

    - @c OLF_INTELECON. Set by the teleconferences module to signify that a
      user is currently within the confines of a teleconference channel, and is
      therefore a candidate for receiving teleconference text.

    - @c OLF_TLCUNLIST. Set to indicate that the user's personal teleconference
      channel is unlisted.

    - @c OLF_LOGGEDOUT. Set by the system to indicate that the user has just
      logged out, although the user-related data structures are still around.

    - @c OLF_RELOGGED. Notifies @c emud that the user is `relogging on',
      i.e. has asked to log out without the connection dropped, so that another
      user can have a go at the BBS.

    - @c OLF_JMP2BLT. Used by the Clubs module to denote an exit to the
      Bulletin reader.

    - @c OLF_INSYSCHAT. Set to indicate that the user is in sysop chat mode.

    - @c OLF_AFTERINP. User to store the last state of @c OFL_AFTERINPUT for
      smoother transitions between modules.

    - @c OLF_ISBOT. This online structure belongs to a robot, a script or other
      automated process.
@{*/

#define OLF_MMEXITING 0x00000001 /**< Exit module after concatenated command. */
#define OLF_MMCALLING 0x00000002 /**< Menuman has just executed a module.  */
#define OLF_MMCONCAT  0x00000004 /**< Module should process menuman input. */
#define OLF_ISYSOP    0x00000008 /**< Obsolete. Re-use at will. */
#define OLF_INVISIBLE 0x00000010 /**< Sysop invisibility mode activated. */
#define OLF_BUSY      0x00000020 /**< User is unable to accept pages etc. */
#define OLF_NOTIMEOUT 0x00000040 /**< Don't enforce inactivity timeouts. */
#define OLF_ANSION    0x00000080 /**< ANSI directives are allowed. */
#define OLF_TR0       0x00000100 /**< Translation mode, bit 0 */
#define OLF_TR1       0x00000200 /**< Translation mode, bit 1 */
#define OLF_TR2       0x00000400 /**< Translation mode, bit 2 */
#define OLF_TR3       0x00000800 /**< Translation mode, bit 3 */
#define OLF_MMGCDGO   0x00001000 /**< Module exit due to <tt>"/go"</tt> command. */
#define OLF_INHIBITGO 0x00002000 /**< Disables <tt>"/go"</tt> command. */
#define OLF_INTELECON 0x00004000 /**< User is in teleconference module. */
#define OLF_TLCUNLIST 0x00008000 /**< Personal telecon channel is unlisted. */
#define OLF_FORCEIDLE 0x00010000 /**< Always force inactivity timeouts. */
#define OLF_LOGGEDOUT 0x00020000 /**< User is logging out or has logged out. */
#define OLF_RELOGGED  0x00040000 /**< User is re-logging on. */
#define OLF_ZAPBYPASS 0x00080000 /**< Eligible to bypass inactivity timeouts. */
#define OLF_JMP2BLT   0x00100000 /**< Jumping from clubs to bulletins. */
#define OLF_INSYSCHAT 0x00200000 /**< User is in Sysop chat mode. */
#define OLF_AFTERINP  0x00400000 /**< Persistent version of OFL_AFTERINPUT. */
#define OLF_ISBOT     0x00800000 /**< This is a bot/script/etc. */

#define OLF_TRSHIFT      8
#define OLF_TRANS        (OLF_TR0|OLF_TR1|OLF_TR2|OLF_TR3)


/** Extract current translation mode from user online record.

    The following macro extracts the 0--9 (0--15, actually) translation table
    number from the user's flags.

    @param u A user <em>onlinerec</em> structure, <tt>onlinerec_t</tt>. Pass
    the structure itself, not a pointer to it.

    @return The translation table specified by the user's preference flags.  */

#define usr_getoxlation(o)   (((o).flags&OLF_TRANS)>>OLF_TRSHIFT)


/** Set current translation mode in user online record.

    This macro sets the translation mode in the user preference flags.

    @param u A user <em>onlinerec</em> structure, <tt>onlinrec_t</tt>. Pass the
    structure itself, not a pointer to it.

    @param i The new translation mode. */

#define usr_setoxlation(o,i) ((o).flags=((o).flags&~OLF_TRANS)|\
			     (((i)&0xf)<<OLF_TRSHIFT))
/*@}*/


/** @defgroup PGS_flags Page states (PGS_x)

    @brief User paging restrictions.

    These constants outline the user's preferred restrictions on incoming pages
    from other users. The following mutually exclusive constants are available:

    - @c PGS_OFF. The user wants to receive no pages from other users.

    - @c PGS_ON. The user will accept pages, but with a minimum of @c pagetime
      minutes in between pages. The <tt>pagetime</tt> field is in the user
      account structure, <tt>useracc_t</tt>.

    - @c PGS_OK. The user will always accept pages, regardless of their number
      and frequency.

    - @c PGS_STORE. Just like @c PGS_OK, but pages to the user sent while the
      user is busy (i.e. when the <tt>OLF_BUSY</tt> flag is set in their
      <tt>onlinerec_t</tt>) will be stored by the system and sent to the user
      <em>en masse</em> as soon as the <tt>OLF_BUSY</tt> flag is cleared. This
      is the default state on our system, since it guarantees that pages to the
      user will not be lost. Historically, it dates all the way back to 1992,
      when it was one of our most favoured custom additions to our (then)
      freshly licensed source of the Major BBS.

    Please note that any restrictions imposed above do not apply to users with
    the @c USY_SYSOP privilege flag. Even if a user is in the @c PGS_OFF state,
    an operator can page them as if they were in the <tt>PGS_STORE</tt>
    state.

@{*/

#define PGS_STORE     0
#define PGS_OK        1
#define PGS_ON        2
#define PGS_OFF       3

/*@}*/


#define CRD_PAID      1
#define CRD_FREE      0

#define STF_FIRST     1


/** @defgroup user_shm Users and shared memory

    @brief Shared user particulars.

    Since Megistos is a distributed system, no central authority keeps
    state. Each process is individually responsible for the user running it.

    However, every now and then transactions between users will have to be
    performed (that is ultimately the point of being of any BBS --- interaction
    and communication between <em>users</em>, the underlying BBS system should
    try to be as transparent as possible).

    Thus, the BBS Daemon allocates one 4 kbyte System V IPC shared memory
    segment for each user. Each process ran by the user automatically has this
    segment attached, but it is also able to attach the segments of other
    users, so as to effect transactions between them. The current user is
    referred to by the highly technical term `this user'. The optional
    additional user is known as `other user'. You can use certain functions
    within this part of the BBS API to attach other users' segments to your
    `other user' pointer. `This user' pointer is always and immutably set to
    the user owning the current process.

    @see thisuseracc, othruseracc, thisuseronl, othruseronl, _thisuseraux,
    _othruseraux.

@{*/

/** Per-user shared memory segment.
    
    This structure is allocated when a user logs in. It is shared throughout
    the system and contains the user's account (<tt>useracc_t</tt>), the online
    record, <tt>onlinerec_t</tt> and a 2 kbyte free-for-all, generic scratch
    buffer.

    For each runtime, there are two pointers to such structures:
    <tt>thisshm</tt> and <tt>othrshm</tt>. The former holds the current user's
    particulars. The latter is normally unused, but is instantiated by function
    in this part of the API to point to some other user's shared
    structure. This is used to allow transactions between users.

    There are six macro shortcuts to access the three fields of each of the two
    shared memory segments.

    @see thisuseracc, othruseracc, thisuseronl, othruseronl, _thisuseraux,
    _othruseraux. */

struct shmuserrec {
	useracc_t   acc;	/**< User's account. */
	onlinerec_t onl;	/**< User's online record. */
	char        aux[2048];	/**< Generic shared scratch space. */
};

extern struct shmuserrec *thisshm, *othrshm;

#define thisuseracc   (thisshm->acc) /**< This user's account. */
#define othruseracc   (othrshm->acc) /**< Other user's account. */

#define thisuseronl   (thisshm->onl) /**< This user's online record. */
#define othruseronl   (othrshm->onl) /**< Other user's online record. */

#define _thisuseraux  (thisshm->aux) /**< This user's shared scratch space. */
#define _othruseraux  (othrshm->aux) /**< Other user's shared scratch space. */

/*@}*/


/* Buffer used by injoth and friends. */

struct injoth_buf {
	long mtype;			/**< One of the @c INJ_x constants */

	union {
		char simple[1];		/**< Simple message (variable length) */
		
		struct {
			char   sender[24];	/**< Sender of message */
			uint32 ackofs;		/**< Length of message+1 */
			char   msg[1];		/**< Message (variable length) */
		} withack;
	} m;
};

#define INJ_MESSAGE      1	/**< Simple injected message */
#define INJ_MESSAGE_ACK  2	/**< Injected message with acknowledgement */


extern classrec_t *cls_classes; /**< Array of all defined user classes. */
extern int         cls_count;   /**< Number of classes in <tt>cls_classes</tt>. */



/** Find a user class.

    @param s The name of a class to look for. The match is full-string and case
    sensitive.

    @return A pointer to the @c classrec_t for the required class, or @c NULL
    if the class could not be located. */

classrec_t *cls_find (char *s);


/** Check for the existence of a user.

    Checks if the specified user exists. If the user does exist, the canonical
    form of the user ID (i.e. the properly capitalised version of the ID
    provided) overwrites the provided user ID.

    @param uid A user ID to look for. The match is case insensitive. The
    properly capitalised user ID overwrites this string on success.

    @return Zero if the user could not be located. One if the user is located,
    in which case, <tt>uid</tt> will contain the canonical form of the ID. */

int usr_exists(char *uid);


/** Read a user account from file.

    Loads the specified account from disk. This function is called by the
    system. Under any normal circumstances, you won't need to call it.

    @param whose The canonical form of the user ID to load. You can use @c
    usr_exists() to obtain this.

    @param uacc A pointer to a pre-allocated <tt>useracc_t</tt> to hold the
    account structure.

    @return Zero if the user could not be loaded, in which case, <tt>errno</tt>
    will be set to the error reported by the system. One if the user was loaded
    successfully, in which case the account will be in <tt>uacc</tt>.

    @see usr_saveaccount(). */

int usr_loadaccount (char *whose, useracc_t *uacc);


/** Read a user online structure from file.

    Loads the specified structure from disk. Although online records are
    temporary and relatively volatile, they <em>are</em> saved to disk between
    module changes for security's sake. This function is called by the
    system. Under any normal circumstances, you won't need to call it.

    @param whose The canonical form of the user ID to load. You can use @c
    usr_exists() to obtain this.

    @param onlrec A pointer to a pre-allocated <tt>onlinerec_t</tt> to hold the
    online record.

    @return Zero if the user could not be loaded, in which case, <tt>errno</tt>
    will be set to the error reported by the system. One if the user was loaded
    successfully, in which case the account will be in <tt>onlrec</tt>.

    @see usr_saveonlrec(). */

int usr_loadonlrec (char *whose, onlinerec_t *onlrec);


/** Write a user account to disk.

    Saves the specified account to disk. This function is called by the
    system. Under any normal circumstances, you won't need to call it.

    @param uacc A pointer to a <tt>useracc_t</tt> holding the account structure.

    @return Zero if the user could not be saved, in which case, <tt>errno</tt>
    will be set to the error reported by the system. One if the user was
    written successfully.

    @see usr_loadaccount(). */

int usr_saveaccount (useracc_t *uacc);


/** Write a user online record to disk.

    Saves the specified online record to disk. This function is called by the
    system. Under any normal circumstances, you won't need to call it.

    @param onlrec Pointer to a <tt>onlinerec_t</tt> holding the online record to
    save.

    @return Zero if the record could not be saved, in which case, <tt>errno</tt>
    will be set to the error reported by the system. One if the record was
    written successfully.

    @see usr_loadonlrec(). */

int usr_saveonlrec (onlinerec_t *onlrec);


/** Post credits to a user account.

    This function adds credits to a user's account. The user's shared segment
    is automatically attached in order to do this. In the process, the current
    `other' user's shared segment is detached and thus is no longer valid.

    @param userid Canonical form of the user ID to credit.

    @param amount The amount of credits to add. This may be negative to denote
    debiting of the account, but I don't recommend it, since this function has
    all the wrong semantics. Use <tt>usr_chargecredits()</tt> to debit
    accounts.

    @param paid Can be <tt>CRD_FREE} to denote free credits, or
    <tt>CRD_PAID</tt> for paid credits. Zero is the same as <tt>CRD_FREE</tt>
    and any non-zero value is the same as <tt>CRD_PAID</tt>.

    @see usr_chargecredits(). */

void usr_postcredits (char *userid, int amount, int paid);


/** Charge a user's account.

    Debits (i.e removes) the specified amount of credits from this user's
    account. There is purposefully no functionality to debit other users'
    accounts. You can use <tt>usr_canpay()</tt> to determine if the user has
    enough credits to cover the <tt>amount</tt>.

    @param amount The amount of credits to debit to the current user. 

    @see usr_postcredits(), usr_canpay(). */

void usr_chargecredits (int amount);


/** Check if the user has enough credits.

    Checks if the current user has enough credits, presumably as a preamble to
    charging the user's account. Don't forget that credits are a constantly
    diminishing quantity. Always check if a user can pay, but do it right
    before charging the user. Otherwise, the user may be able to pay now, but
    not when you actually call <tt>usr_chargecredits()</tt>.

    @param amount The number of credits to check for.

    @return Non-zero if the user's credits are greater than or equal to {\tt
    amount}. Zero otherwise. 

    @see usr_postcredits(). */

int usr_canpay(int amount);


/** Change a user's class.
    
    Move a user to a new class.

    @param userid The canonical form of the user ID to operate on. You can use
    <tt>usr_exists()</tt> to render a user ID in its canonical form.
    
    @param newclass The name of an existing class to move the user to. Use {\tt
    cls_find()} to make sure the class exists.

    @param permanent Set to zero if the change in class is temporary (i.e. only
    for today). Non-zero values denote a permanent change of class. */

void usr_setclass (char *userid, char *newclass, int permanent);


/** Check if a user is online (deprecated).
    
    Checks if the specified user is online, taking invisibility into
    account. If the user <em>is</em> online, the corresponding shared segment
    is attached and a pointer to it is returned.

    @param userid The canonical form of the user ID to operate on. You can use
    @c usr_exists() to render a user ID in its canonical form.

    @param checkinvis If non-zero and the user is online but invisible, the
    function will pretend the user is not online. If <tt>checkinvis</tt> is
    zero and the user is online, invisibility is not taken into account and the
    function will not `lie'.

    @param buf A pointer (passed by reference) to a user shared segment. If the
    call is successful and user `<tt>userid</tt>' is online, the corresponding
    shared memory segment will be attached to this process and a pointer to the
    segment will be written to <tt>buf</tt>.

    @return Zero if the user is not online; one if they are.
    
    @deprecated Do not use this function. It is easy to misuse it. Please use
    the simpler <tt>usr_insys()</tt> function that does not suffer from the
    same problems. This function is for internal use only.

    @see usr_insys(). */

int usr_insystem(char *userid,int checkinvis, struct shmuserrec **buf);


/** Check if a user is online and attach shared segment.
    
    Checks if the specified user is online, taking invisibility into
    account. If the user <em>is</em> online, the corresponding shared segment
    is attached as the `other user'.

    @param userid The user ID to check for. It need not be in canonical form;
    the function will call <tt>usr_exists()</tt> internally.

    @param checkinvis If non-zero and the user is online but invisible, the
    function will pretend the user is not online. If <tt>checkinvis</tt> is
    zero and the user is online, invisibility is not taken into account and the
    function will not `lie'.

    @return Zero if the user is not online; one if they are. */

int usr_insys(char *userid,int checkinvis);


/** Page another user with a message.

    `Injects' a string to another user (hence the name).

    @param user A pointer to the other user's <tt>onlinerec_t</tt>. You should
    obviously attach the other user's shared segment first, by calling
    <tt>usr_insys()</tt>. As a side effect, this will also make sure the other
    user is actually on-line.

    @param msg A null-terminated string holding the message to send to the
    user. No need for the message to be fully formatted, but it should <em>in
    the other user's language</em>. Having attached the other user's online
    record, you know what language they're using. Use the function
    <tt>msg_getl()</tt> to obtain prompts in the other user's language, and
    <tt>sprintf()</tt> to embed information in them. Any substitution variables
    in the string will be expanded in the other user's context. The string
    should be smaller than the maximum System V IPC message size,
    <tt>MSGMAX</tt> (4080 bytes on Linux, your mileage may vary). This is
    acceptable, though. You should aim to send really small messages to other
    users. Large ones are bound to be annoying in the superlative.

    @param force If non-zero, the function will not respect the
    <tt>OLF_BUSY</tt> flag in the user's online record, sending the message
    even if the user is unable to receive it. Never do this unless absolutely
    necessary. The system does this to notify the user of imminent
    disconnections, but that's usually an emergency for the user. Bear in mind
    that the user may not be able to receive the message immediately. Stored
    pages work this way.

    @return Zero if the message could not be injected. One if it was
    successfully sent. This is asynchronous: the user may actually see the
    message at a later time.

    @see <tt>usr_injoth_ack()</tt>.
*/

int usr_injoth(onlinerec_t *user, char *msg, int force);


/** Page another user with a message and acknowledgement

    `Injects' a string to another user and sends back delivery ackowledgement
    to the original user. Injected messages are displayed asynchronously. If
    the recipient user is in the process of typing a line, the message will not
    appear until the user has pressed Enter (there's a way to force synchronous
    delivery, but it's not considered polite to the user because it disrupts
    their typing). However, the user may be unable to receive the message for a
    considerable length of time: maybe they're the Sysop and currently running
    a UNIX shell, or in the full screen editor. In such cases, it may be
    necessary to send an acknowledgement note back to the sender of the
    injected message when that message finally gets delivered. The /p(age)
    command does that if the recipient allows it.

    @param user A pointer to the other user's <tt>onlinerec_t</tt>. You should
    obviously attach the other user's shared segment first, by calling {\tt
    usr_insys()}. As a side effect, this will also make sure the other user is
    actually on-line.

    @param msg A null-terminated string holding the message to send to the
    user. No need for the message to be fully formatted, but it should {\em in
    the other user's language}. Having attached the other user's online record,
    you know what language they're using. Use the function <tt>msg_getl()</tt>
    to obtain prompts in the other user's language, and <tt>sprintf()</tt> to
    embed information in them. Any substitution variables in the string will be
    expanded in the other user's context.

    @param ack A null-terminated string holding the acknowledgement to be
    injected back to the original user upon delivery of the injected
    message. The total length of @c msg and @c ack must be less than the
    maximum System V IPC message size, <tt>MSGMAX</tt> (4080 bytes on Linux,
    your mileage may vary). This is acceptable, though. You should aim to send
    really small messages to other users. Large ones are bound to be annoying
    in the superlative.

    @param force If non-zero, the function will not respect the
    <tt>OLF_BUSY</tt> flag in the user's online record, sending the message
    even if the user is unable to receive it. Never do this unless absolutely
    necessary. The system does this to notify the user of imminent
    disconnections, but that's usually an emergency for the user. Bear in mind
    that the user may not be able to receive the message immediately. Stored
    pages work this way.

    @return Zero if the message could not be injected. One if it was
    successfully sent. This is asynchronous: the user may actually see the
    message at a later time. An acknowledgement will eventually be injected
    back to the sender <em>only</em> if the return value is 1 (i.e. no errors
    have occurred).

    @see <tt>usr_injoth()</tt>.  */

int usr_injoth_ack(onlinerec_t *user, char *msg, char *ack, int force);


/** User ID completion.

    Completes A partially specified user ID, offering a menu of similar user
    IDs if the given ID was ambiguous. This function has two side effects:

    - It renders user IDs in their canonical form, and

    - It attaches the final user IDs shared segment <em>if the user is
      online</em>.

    Partial user IDs of less than three characters will not even be
    considered. Most systems have huge numbers of users with the same first
    couple of letters.

    If the partial user ID is found to be online, it is canonicalised and the
    function returns immediately. The user's shared segment is also attached.

    Otherwise, the user ID is completed by building a list of all user IDs
    starting with the supplied user ID. If the list has only one member, the
    function returns it (and attaches the user's shared segment, if online).

    If more than one user IDs match the partial, provided ID, the user is
    presented with a menu of the matching user IDs. At this point, the user can
    either select one of those user IDs by number, or enter an altogether new
    (possibly partial) user ID and the function will begin all over again. At
    any rate, if the user selects a user ID, the name is returned and the other
    user's shared segment is attached, if that user is online. Complicated, eh?

    Oh, by the way, this function ends command concatenation if it is forced to
    present a menu. This makes sense, because the user wasn't expecting this,
    and it's probably best to not make any potentially dangerous assumptions
    about the operation being performed.

    This completion function should be used wherever the system asks for (or
    expects) a user ID. The <tt>get_userid()</tt> high-level input function
    uses it. Even normally non-interactive parts of the system use it, like the
    {\em page} global command (<tt>/p</tt>). I thoroughly recommend duplicating
    this behaviour for any other strings that can be numerous, long and/or
    complicated.

    @param userid A partially specified user ID. After successful completion of
    this function, the canonical form of the full user ID will overwrite this
    argument.

    @param online If non-zero, the function will only consider users currently
    on-line for completion, ignoring all other users.

    @return Zero if the user pressed <tt>X</tt> at the user ID selection
    menu. If this occurs, you should cancel whatever operation is in
    progress. If all went well and a user ID was located, a value of one is
    returned. */

int usr_uidxref(char *userid, int online);


#endif   /* USERACC_H */

/*@}*/

/*
LocalWords: useracc Alexios doc legalese otnotesize al alexios Exp bbs GPL
LocalWords: lastconsolepage onlinerec miscfx bbsd emud USY AUDITPAGE sysop
LocalWords: PAGEAUDIT remsys SIGNUPS FILTAUD auditfiltering INVIS GDET OLF
LocalWords: SOPAUD xlation generalised injothqueue IPC injoth LOGGEDOUT tt
LocalWords: ifndef VER endif config DELIM userid passwd username USX prefs
LocalWords: UPF UFL ORred sysaxs scnwidth scnheight datecre datelast API
LocalWords: passexp em tempclss curclss freebies timetdy classdays totpaid
LocalWords: totcreds timever credsever pagetime pagestate PGS filesdnl AUX
LocalWords: bytesdnl filesupl bytesupl msgswritten lastclub struct uint TR
LocalWords: int bbskey KEYLENGTH USR ANSION ANSIDEF ANSIASK TRDEF TRASK TR
LocalWords: PF TRANS TRSHIFT param usr getpxlation setpxlation co LOGON cp
LocalWords: logon AGESTATS CLSSTATS GENSTATS LINSTATS Linux MODSTATS DEL
LocalWords: SYSTATS rm DIR REN mv invis MASTERKEY Sysops un Signup prude
LocalWords: notaround nadays who've ardays nocreds credpost limpercall CLF
LocalWords: limperday crdperday crdperweek crdpermonth classrec creds dev
LocalWords: NOCHRGE capitalisation CRDXFER NUMLANGUAGES emupty baudrate en
LocalWords: bps bbsgetty curpage prevpage ORring descr lastpage fraccharge
LocalWords: credspermin onlinetime timeoutticks idlezap statptrs statcreds
LocalWords: statd loggedin telechan telecountdown lastlib ONL PTY menuman
LocalWords: min telecons OUSR MMEXITING MMCALLING MMCONCAT MMGCDGO CONCAT
LocalWords: ISYSOP NOTIMEOUT FORCEIDLE ZAPBYPASS INHIBITGO INTELECON JMP
LocalWords: TLCUNLIST RELOGGED relogging BLT INSYSCHAT telecon CRD
LocalWords: getoxlation onlinrec setoxlation masse STF shm Megistos kbyte
LocalWords: thisuseracc othruseracc thisuseronl othruseronl thisuseraux
LocalWords: othruseraux thisshm othrshm shmuserrec acc onl aux cls uid pre
LocalWords: capitalised uacc errno saveaccount loadaccount security's buf
LocalWords: onlrec saveonlrec loadonlrec chargecredits postcredits canpay
LocalWords: newclass setclass checkinvis insys insystem msg getl sprintf
LocalWords: MSGMAX IDs uidxref
*/
