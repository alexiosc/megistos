/** @name     config.h
    @memo     High-level, hardwired system configuration.
    @author   Alexios

    @doc

    This is a sensitive file that contains a lot of values that are hardwired
    into the system. In fact, it contains almost {\em all} of the values that
    aren't readily configurable by the end user (erm, Sysop).

    You can change these, but you shouldn't do so after your system has
    compiled and ran for the first time. Oh, unless you're into heavy wizardry
    and/or pain (to misquote Larry Wall).

    Subsequent documentation will clearly note which options can be frobbed and
    at what stage. But take it with a pinch of salt. Anything that isn't
    documented is almost certainly a no-no.

    Original banner, legalese and change history follow.

    {\small\begin{verbatim}

 *****************************************************************************
 **                                                                         **
 **  FILE:     config.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  define configuration macros                                  **
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
 * Revision 0.11  1999/08/13 16:58:25  alexios
 * Delete BBSTERM and made provisions for BBSUSERNAME to be
 * mutable using the configure script.
 *
 * Revision 0.10  1999/07/18 21:13:24  alexios
 * Added MetaBBS support.
 *
 * Revision 0.9  1998/12/27 15:19:19  alexios
 * Added autoconf support. Made directories relative to the
 * BBS prefix directory.
 *
 * Revision 0.8  1998/07/26 21:17:06  alexios
 * Major changes in directory structure.
 *
 * Revision 0.7  1997/12/02 20:39:00  alexios
 * Deleted file of viewers. Added MAXARCHIVERS, the maximum
 * number of archivers (and/or viewers), which share the same
 * global mbk file now.
 *
 * Revision 0.6  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.5  1997/11/05 10:52:05  alexios
 * Added NOTIFYDIR for the notify module.
 *
 * Revision 0.4  1997/11/03 00:29:40  alexios
 * Added XLATIONDIR, XLATIONFILE, XLATIONSRC and NUMXLATIONS
 * to define generalised translation tables.
 *
 * Revision 0.3  1997/09/12 12:45:25  alexios
 * Added directory definitions for the Filing module. Added a
 * definition for the full pathname to a user's injoth() file
 * (now obsolete since injoth doesn't use files anymore).
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Added definition of BBSD pipe file.
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




#ifndef CONFIG_H
#define CONFIG_H


#include <bbsconfig.defs.h>
#define WANT_SIGNAL_H 1
#include <bbsinclude.h>



/** @name Basic integer types
    @filename int_types

    @memo Aliases for the standard integer types.

    @doc The {\tt _t} suffix slows me down, but the standard integer
    types are very useful, so I'll just define a few {\tt typedefs} to
    make my life easier. */

/*@{*/

typedef int8_t  int8;		/** 8-bit signed integer */
typedef int16_t int16;		/** 16-bit signed integer */
typedef int32_t int32;		/** 32-bit signed integer */
typedef int64_t int64;		/** 64-bit signed integer */

typedef uint8_t  uint8;		/** 8-bit unsigned integer */
typedef uint16_t uint16;	/** 16-bit unsigned integer */
typedef uint32_t uint32;	/** 32-bit unsigned integer */
typedef uint64_t uint64;	/** 64-bit unsigned integer */

/*@}*/


typedef uint32 bbskey_t;	/** Type of security `keys' and `locks' */


/** @name Directory names
    @filename config_dir

    @memo Hardwired directory names for most of the basic system.

    @doc Lots of these here. You can change these, but there's no guarantee
    that this won't break some braindead module with hard-wired strings (eugh).

    Do {\em NOT} change anything after your system has ran for the first time,
    unless you're out for a ticket to breakage city.
*/

/*@{*/

#if 0
#define BBSDIR         __BASEDIR
#endif
#define BBSDATADIR     "data"
#define BBSETCDIR      "etc"
#define BBSFILEDIR     BBSDATADIR"/files"
#define BBSLIBDIR      "lib"
#define BBSMODULEDIR   BBSLIBDIR"/modules"
#define BINDIR         "bin"
#define BLTDBDIR       MSGSDIR"/..bltdb"
#define CHANDEFDIR     BBSETCDIR"/channel.defs"
#define CLUBAXDIR      MSGSDIR"/..access"
#define CLUBHDRDIR     MSGSDIR"/..clubhdr"
#define CONFIGDIR      BBSETCDIR"/config"
#define COOKIEDIR      BBSDATADIR"/cookie"
#define DEVDIR         "/dev"
#define DOCDIR         "doc"
#define EMAILATTDIR    EMAILDIR"/"MSGATTDIR
#define EMAILDIR       MSGSDIR"/"EMAILDIRNAME
#define EMUFIFODIR     "etc"
#define EMULOGDIR      "etc"
#define EVENTDIR       BBSDATADIR"/events"
#define FILELIBDBDIR   BBSFILEDIR"/.DB"
#define FILELIBDIR     BBSDATADIR"/files"
#define GCSDIR         BBSLIBDIR"/gcs"
#define IHAVEDIR       MSGSDIR"/..ihave"
#define LOCKDIR        "lock"
#define LOGDIR         "log"
#define MAILERDIR      BBSDATADIR"/mailer"
#define MAILERFILESDIR MAILERDIR"/QWKfiles"
#define MAILERREQDIR   MAILERDIR"/requests"
#define MAILERUSRDIR   MAILERDIR"/usr"
#define MBKDIR         BBSLIBDIR"/prompts"
#define MENUMANDIR     BBSDATADIR"/menuman"
#define MSGATTDIR      ".ATT"
#define MSGBLTDIR      ".BLT"
#define MSGSDIR        BBSDATADIR"/msgs"
#define MSGSDISTDIR    MSGSDIR"/..dist"
#define MSGSIGDIR      MSGSDIR"/..sig"
#define MSGUSRDIR      MSGSDIR"/..usr"
#define NEWSDIR        BBSDATADIR"/news"
#define ONLINEDIR      BBSETCDIR"/online"
#define QSCDIR         MSGSDIR"/..quickscan"
#define RECENTDIR      BBSDATADIR"/recent"
#define REGISTRYDIR    BBSDATADIR"/registry"
#define STATDIR        BBSDATADIR"/stats"
#define TELEACTIONDIR  TELEETCDIR
#define TELEDIR        BBSDATADIR"/telecon"
#define TELEETCDIR     TELEDIR"/.etc"
#define TELEPLUGINDIR  TELEETCDIR
#define TELEQDIR       TELEETCDIR
#define TELEUSRDIR     TELEDIR"/.usr"
#define USRDIR         BBSDATADIR"/usr"
#define XLATIONDIR     BBSETCDIR"/xlation"

#define NETMAILDIR     "/var/spool/mail"
#define PROCDIR        "/proc"
#define TMPDIR         "/tmp"

/*@}*/


/** @name Standard BBS subsystem names
    @filename config_bin

    @memo Names of useful modules and subsystems.

    @doc Names of modules and subsystems that are usually called from
    within other modules or subsystems.  As the Linux kernel used to
    say, it's safe to leave these untouched (meaning: touch and die).  */

/*@{*/

#define BBSDIALOGBIN   BINDIR"/bbsdialog"
#define BBSMAILBIN     BINDIR"/bbsmail"
#define BULLETINBIN    BINDIR"/bulletins"
#define EMUDBIN        BINDIR"/emud"
#define IDLERBIN       BINDIR"/idler"
#define LINEDBIN       BINDIR"/lined"
#define LOGINBIN       "/bin/login"
#define BBSLOGINBIN    BINDIR"/bbslogin"
#define LOGOUTBIN      BINDIR"/bbslogout"
#define REMSYSBIN      BINDIR"/remsys"
#define SIGNUPBIN      BINDIR"/signup"
#define STATSBIN       BINDIR"/stats"
#define STTYBIN        "/bin/stty"
#define UPDOWNBIN      BINDIR"/updown"
#define USERADDBIN     BINDIR"/bbsuseradd"
#define USERDELBIN     BINDIR"/bbsdeluser"
#define VISEDBIN       BINDIR"/vised"

#ifdef HAVE_METABBS
#define METABBSBIN     BINDIR"/metabbs-client"
#define METABBSDBIN    BINDIR"/metabbs-server"
#endif

/*@}*/


/** @name Filenames used throughout the system.
    @filename config_fname

    @memo Common filenames.

    @doc Full names of files used by the system for all sorts of storage
    requirements. I suppose you {\em could} change a few of these, {\em BEFORE}
    you install the BBS. I've documented those that are the most likely not to
    hurt anything (much).  */


/*@{*/

#define AUDITFILE      LOGDIR"/audit" /** Full path to the Audit Trail */
#define BADPASSFILE    BBSETCDIR"/stupid.passwords" /** A list of forbidden passwords */
#define BADUIDFILE     BBSETCDIR"/bad.userids" /** A list of forbidden user IDs */
#define BAUDSTATFILE   STATDIR"/baudstats" /** Speed statistics log file */
#define BBSDPIPEFILE   BBSETCDIR"/pbbsd"
#define BBSRESTARTFILE BBSETCDIR"/rc.bbs"
#define CHANDEFFILE    CHANDEFDIR"/channels" /** Binary file where channels are defined */
#define GETTYDEFFILE   CHANDEFDIR"/bbsgetty." /** bbsgetty channel definition file */
#define CHANDEFSRCFILE CHANDEFDIR"/CHANNELS" /** Text file where channels are defined */
#define CLASSFILE      BBSETCDIR"/userclasses" /** Binary file where user classes are stored */
#define CLNUPAUDITFILE LOGDIR"/audit.cleanup" /** Cleanup log file */
#define CLSSTATFILE    STATDIR"/clsstats" /** User class statistics log file */
#define COOKIEFILE     COOKIEDIR"/cookies-%02d.dat"
#define COOKIEIDXFILE  COOKIEDIR"/cookies-%02d.idx"
#define DAYSTATFILE    STATDIR"/daystats" /** Daily traffic log file */
#define DEMOSTATFILE   STATDIR"/demographics" /** Demographics log file */
#define EMLLISTFILE    EMAILDIR"/"MSGLISTFILE
#define ERRORFILE      LOGDIR"/errors" /** Fatal error log file */
#define ETCTTYFILE     "/etc/ttys" /** The UNIX /etc/ttys file that maps terminal types to ttys */
#define FLETTRWORDS    BBSETCDIR"/four.letter.words" /** A list of words used to create passwords */
#define LANGUAGEFILE   BBSETCDIR"/languages" /** List of languages of the BBS */
#define LOGINMSGFILE   BBSETCDIR"/login.message" /** The login message of the day */
#define LOGINSCRIPT    BINDIR"/bbs.session" /** The script that manages a user's entire session */
#define MENUMANINDEX   MENUMANDIR"/.index" /** Index file for Menuman */
#define MENUMANPAGES   MENUMANDIR"/.pages" /** Page directory for Menuman */
#define MODSTATFILE    STATDIR"/modstats" /** Module usage statistics log file */
#define MONITORFILE    BBSETCDIR"/monitor" /** The system monitor file */
#define MSGLISTFILE    ".LIST"
#define PROTOCOLFILE   BBSETCDIR"/protocols" /** The file transfer protocol definition file */
#define RECENTFILE     LOGDIR"/recent.global" /** The Megistos equivalent of utmp */
#define SYSVARFILE     BBSETCDIR"/sysvar" /** The main system variable block */
#define SYSVARBKFILE   BBSETCDIR"/sysvar-backup" /** Backup of the system variables */
#define SYSVARSHMFILE  BBSETCDIR"/sysvar-shm" /** Shared memory ID of the system variable block */
#define TELEACTIONFILE MBKDIR"/teleactions.mbk"
#define TELEACTMSGFILE TELEACTIONDIR"/teleactions.msg"
#define TELEACTSRCFILE TELEACTIONDIR"/ACTIONS"
#define TELEPISRCFILE  TELEPLUGINDIR"/PLUGINS"
#define TELEPLUGINFILE TELEPLUGINDIR"/plugins"
#define TTYINFOFILE    CHANDEFDIR"/msg-%s" /** Per-channel message of the day */ 
#define TTYSTATFILE    STATDIR"/ttystats" /** Channel usage statistics log file */
#define XLATIONFILE    XLATIONDIR"/xlation-binary" /** Encoding translation table */

/*@}*/


/** @name Miscellaneous.
    @filename config_misc

    @memo Permanent settings.

    @doc All documented settings can be changed at will. Some will require
    additional work. This is shown in parentheses. It's all right to change any
    settings without parentheses, but you'll have to recompile the entire system.
*/


/*@{*/

#define CLUBLOCK       "LCK..club.%s"
#define ECUSERLOCK     "LCK..ecuser.%s"
#define INCLUBLOCK     "LCK..club.%s.%s"
#define MESSAGELOCK    "LCK..msg.%s.%s"
#define MSGREADLOCK    "LCK..msg.%s.%s.%s"
#define NEMESSAGELOCK  "LCK..emsgn"
#define BLTREADLOCK    "LCK..BLT"

#define BBSD_IPC       0x42425344  /** This spells "BBSD" (BBS restart) */
#ifndef BBSUSERNAME
#define BBSUSERNAME    "bbs" /** BBS UNIX username ({\tt chown}s and BBS restart) */
#endif
#define DELETEDCLASS   "DELETED" /** Where do deleted users go? (may need to change other classes) */
#define EMAILCLUBNAME  "Email"
#define EMUD_IPC       0x454d5544 /** This spells "EMUD" (BBS restart) */
#define EMULOGSIZE     4e096
#define FILEATTACHMENT "%d.att" /** The format of message attachments */
#define KEYLENGTH      4
#define LOGINSTRIKES   3 /** Hard-wired number of login attempts */
#define MAXARCHIVERS   20 /** Maximum number of archivers allowed */
#define MAXCLASS       64 /** Maximum number of classes allowed (rebuild class file) */
#define MAXINPLEN      2048 /** Length of user input buf (may cause overflows in silly modules) */
#define NUMLANGUAGES   9 /** Maximum number of languages */
#define NUMXLATIONS    10 /** Maximum number of encodings */
#define MESSAGEFILE    "%010d"
#define MSGBUFSIZE     8192 /** Buffer for preparing user prompts */
#define MSGINDEX       ".INDEX%d"
#define RECENT_ENTRIES 20 /** Number of recent per-user logons retained */
#define REGISTRYSIZE   1024 /** Size of user registry record */
#define SIGCHAT        SIGUSR1 /** The signal used to toggle Sysop chat */
#define SIGMAIN        SIGUSR2 /** Signal to drop to main channel in teleconferences */
#define SIGNUPID       "new" /** What new users have to type to signup */
#ifdef HAVE_METABBS
#define METABBSID      "out" /** What users have to type to start the MetaBBS client */
#endif
#define SYSOP          "Sysop" /** The username of the Sysop */
#define TOP_N_ENTRIES  30 /** Number of entries in the Top listings */
#define EMAILDIRNAME   ".email"
#define INJOTHFNAME    ONLINEDIR"/.injoth-%s"
#define XLATIONSRC     "xlation.%d" /** Output translation tables */
#define KBDXLATIONSRC  "kbdxlation.%d" /** Input translation tables */


/** @memo Characters allowed in user-supplied filenames. */
#define FNAMECHARS     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" \
                       "1234567890@#%^()-_+=[]."

/*@}*/


#endif /* CONFIG_H */


/*@}*/

/*
LocalWords: config Alexios doc em erm Sysop wizardry misquote frobbed Exp
LocalWords: legalese alexios bbs BBSTERM BBSUSERNAME MetaBBS autoconf mbk
LocalWords: MAXARCHIVERS GPL NOTIFYDIR XLATIONDIR XLATIONFILE XLATIONSRC
LocalWords: NUMXLATIONS generalised injoth BBSD ifndef VER endif int tt ld
LocalWords: bbsinclude uint bbskey dir braindead eugh BBSDIR BASEDIR lib
LocalWords: BBSDATADIR BBSETCDIR BBSFILEDIR BBSLIBDIR BINDIR BLTDBDIR dev
LocalWords: MSGSDIR CHANDEFDIR CLUBAXDIR CLUBHDRDIR CONFIGDIR COOKIEDIR
LocalWords: DEVDIR DOCDIR EMAILATTDIR EMAILDIR MSGATTDIR EMAILDIRNAME gcs
LocalWords: EMUFIFODIR EMULOGDIR EVENTDIR FILELIBDBDIR FILELIBDIR GCSDIR
LocalWords: IHAVEDIR LOCKDIR LOGDIR MAILERDIR MAILERFILESDIR QWKfiles usr
LocalWords: MAILERREQDIR MAILERUSRDIR MBKDIR MENUMANDIR menuman ATT BLT
LocalWords: MSGBLTDIR msgs MSGSDISTDIR MSGSIGDIR MSGUSRDIR NEWSDIR QSCDIR
LocalWords: ONLINEDIR RECENTDIR REGISTRYDIR STATDIR stats TELEACTIONDIR
LocalWords: TELEETCDIR TELEDIR telecon TELEPLUGINDIR TELEQDIR TELEUSRDIR
LocalWords: USRDIR xlation NETMAILDIR PROCDIR proc TMPDIR tmp BBSDIALOGBIN
LocalWords: bbsdialog BBSMAILBIN bbsmail BULLETINBIN EMUDBIN emud IDLERBIN
LocalWords: LINEDBIN LOGINBIN BBSLOGINBIN bbslogin LOGOUTBIN bbslogout IDs
LocalWords: REMSYSBIN remsys SIGNUPBIN signup STATSBIN STTYBIN UPDOWNBIN
LocalWords: updown USERADDBIN bbsuseradd USERDELBIN bbsdeluser VISEDBIN
LocalWords: ifdef METABBSBIN metabbs METABBSDBIN fname AUDITFILE baudstats
LocalWords: BADPASSFILE BADUIDFILE BAUDSTATFILE BBSDPIPEFILE pbbsd dat idx
LocalWords: BBSRESTARTFILE CHANDEFFILE GETTYDEFFILE bbsgetty CLASSFILE shm
LocalWords: CHANDEFSRCFILE userclasses CLNUPAUDITFILE CLSSTATFILE clsstats
LocalWords: COOKIEFILE COOKIEIDXFILE DAYSTATFILE daystats DEMOSTATFILE msg
LocalWords: EMLLISTFILE MSGLISTFILE ERRORFILE ETCTTYFILE FLETTRWORDS utmp
LocalWords: LANGUAGEFILE LOGINMSGFILE LOGINSCRIPT MENUMANINDEX MODSTATFILE
LocalWords: MENUMANPAGES modstats MONITORFILE PROTOCOLFILE RECENTFILE misc
LocalWords: Megistos uquivalent SYSVARFILE sysvar SYSVARBKFILE PLUGINS IPC
LocalWords: SYSVARSHMFILE TELEACTIONFILE TELEACTMSGFILE TELEACTSRCFILE att
LocalWords: TELEPISRCFILE TELEPLUGINFILE plugins TTYINFOFILE TTYSTATFILE
LocalWords: ttystats CLUBLOCK ECUSERLOCK INCLUBLOCK MESSAGELOCK username
LocalWords: MSGREADLOCK NEMESSAGELOCK BLTREADLOCK chown DELETEDCLASS buf
LocalWords: EMAILCLUBNAME EMULOGSIZE FILEATTACHMENT KEYLENGTH LOGINSTRIKES
LocalWords: MAXCLASS MAXINPLEN NUMLANGUAGES MESSAGEFILE MSGBUFSIZE logons
LocalWords: MSGINDEX REGISTRYSIZE SIGCHAT SIGUSR SIGMAIN SIGNUPID
LocalWords: METABBSID INJOTHFNAME KBDXLATIONSRC kbdxlation FNAMECHARS
*/

