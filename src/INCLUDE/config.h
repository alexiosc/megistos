/*****************************************************************************\
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:48:48  alexios
 * Initial revision
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
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef CONFIG_H
#define CONFIG_H


#include <bbsconfig.defs.h>
#define WANT_SIGNAL_H 1
#include <bbsinclude.h>



#define BBSDIR         __BASEDIR
#define BBSDATADIR     BBSDIR"/data"
#define BBSETCDIR      BBSDIR"/etc"
#define BBSFILEDIR     BBSDATADIR"/files"
#define BBSLIBDIR      BBSDIR"/lib"
#define BINDIR         BBSDIR"/bin"
#define BLTDBDIR       MSGSDIR"/..bltdb"
#define CHANDEFDIR     BBSETCDIR"/channel.defs"
#define CLUBAXDIR      MSGSDIR"/..access"
#define CLUBHDRDIR     MSGSDIR"/..clubhdr"
#define CONFIGDIR      BBSETCDIR"/config"
#define COOKIEDIR      BBSDATADIR"/cookie"
#define DEVDIR         "/dev"
#define DOCDIR         BBSDIR"/doc"
#define EMAILATTDIR    EMAILDIR"/"MSGATTDIR
#define EMAILDIR       MSGSDIR"/"EMAILDIRNAME
#define EMUFIFODIR     BBSDIR"/etc"
#define EMULOGDIR      BBSDIR"/etc"
#define EVENTDIR       BBSDATADIR"/events"
#define FILELIBDBDIR   BBSFILEDIR"/.DB"
#define FILELIBDIR     BBSDATADIR"/files"
#define IHAVEDIR       MSGSDIR"/..ihave"
#define LOCKDIR        BBSDIR"/lock"
#define LOGDIR         BBSDIR"/log"
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
#define NOTIFYDIR      BBSDATADIR"/notify"
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

#define BBSDIALOGBIN   BINDIR"/bbsdialog"
#define BBSMAILBIN     BINDIR"/bbsmail"
#define BULLETINBIN    BINDIR"/bulletins"
#define EMUDBIN        BINDIR"/emud"
#define IDLERBIN       BINDIR"/idler"
#define LINEDBIN       BINDIR"/lined"
#define LOGINBIN       "/bin/login"
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
#endif

#define AUDITFILE      LOGDIR"/audit"
#define BADPASSFILE    BBSETCDIR"/stupid.passwords"
#define BADUIDFILE     BBSETCDIR"/bad.userids"
#define BAUDSTATFILE   STATDIR"/baudstats"
#define BBSDPIPEFILE   BBSETCDIR"/pbbsd"
#define BBSLOGIN       BINDIR"/bbslogin"
#define BBSRESTARTFILE BBSETCDIR"/rc.bbs"
#define CHANDEFFILE    CHANDEFDIR"/channels"
#define GETTYDEFFILE   CHANDEFDIR"/bbsgetty."
#define CHANDEFSRCFILE CHANDEFDIR"/CHANNELS"
#define CLASSFILE      BBSETCDIR"/userclasses"
#define CLNUPAUDITFILE LOGDIR"/audit.cleanup"
#define CLSSTATFILE    STATDIR"/clsstats"
#define COOKIEFILE     COOKIEDIR"/cookies-%02d.dat"
#define COOKIEIDXFILE  COOKIEDIR"/cookies-%02d.idx"
#define DAYSTATFILE    STATDIR"/daystats"
#define DEMOSTATFILE   STATDIR"/demographics"
#define EMLLISTFILE    EMAILDIR"/"MSGLISTFILE
#define ERRORFILE      LOGDIR"/errors"
#define ETCTTYFILE     "/etc/ttys"
#define FLETTRWORDS    BBSETCDIR"/four.letter.words"
#define LANGUAGEFILE   BBSETCDIR"/languages"
#define LOGINMSGFILE   BBSETCDIR"/login.message"
#define LOGINSCRIPT    BINDIR"/bbs.session"
#define MENUMANINDEX   MENUMANDIR"/.index"
#define MENUMANPAGES   MENUMANDIR"/.pages"
#define MODSTATFILE    STATDIR"/modstats"
#define MONITORFILE    BBSETCDIR"/monitor"
#define MSGLISTFILE    ".LIST"
#define PROTOCOLFILE   BBSETCDIR"/protocols"
#define RECENTFILE     LOGDIR"/recent.global"
#define SIGNUPSCRIPT__ BBSDIR"/signup.script" /* OBSOLETED */
#define SYSVARFILE     BBSETCDIR"/sysvar"
#define SYSVARBKFILE   BBSETCDIR"/sysvar-backup"
#define SYSVARSHMFILE  BBSETCDIR"/sysvar-shm"
#define TELEACTIONFILE MBKDIR"/teleactions.mbk"
#define TELEACTMSGFILE TELEACTIONDIR"/teleactions.msg"
#define TELEACTSRCFILE TELEACTIONDIR"/ACTIONS"
#define TELEPISRCFILE  TELEPLUGINDIR"/PLUGINS"
#define TELEPLUGINFILE TELEPLUGINDIR"/plugins"
#define TTYINFOFILE    CHANDEFDIR"/msg-%s"
#define TTYSTATFILE    STATDIR"/ttystats"
#define XLATIONFILE    XLATIONDIR"/xlation-binary"

#define CLUBLOCK       "LCK..club.%s"
#define ECUSERLOCK     "LCK..ecuser.%s"
#define INCLUBLOCK     "LCK..club.%s.%s"
#define MESSAGELOCK    "LCK..msg.%s.%s"
#define MSGREADLOCK    "LCK..msg.%s.%s.%s"
#define NEMESSAGELOCK  "LCK..emsgn"
#define BLTREADLOCK    "LCK..BLT"

#define BBSD_IPC       0x42425344         /* This spells "BBSD" */
#ifndef BBSUSERNAME
#define BBSUSERNAME    "bbs"
#endif
#define DELETEDCLASS   "DELETED"
#define EMAILCLUBNAME  "Email"
#define EMUD_IPC       0x454d5544         /* This spells "EMUD" */
#define EMULOGSIZE     4096
#define FILEATTACHMENT "%ld.att"
#define KEYLENGTH      4
#define LOGINSTRIKES   3
#define MAXARCHIVERS   20
#define MAXCLASS       64
#define MAXINPLEN      2048
#define NUMLANGUAGES   9
#define NUMXLATIONS    10
#define MESSAGEFILE    "%010ld"
#define MSGBUFSIZE     8192
#define MSGINDEX       ".INDEX%d"
#define RECENT_ENTRIES 20
#define REGISTRYSIZE   1024
#define SIGCHAT        SIGUSR1
#define SIGMAIN        SIGUSR2
#define SIGNUPID       "new"
#ifdef HAVE_METABBS
#define METABBSID      "out"
#endif
#define SYSOP          "Sysop"
#define TOP_N_ENTRIES  30
#define EMAILDIRNAME   ".email"
#define INJOTHFNAME    ONLINEDIR"/.injoth-%s"
#define XLATIONSRC     "xlation.%d"
#define KBDXLATIONSRC  "kbdxlation.%d"

#define FNAMECHARS     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" \
                       "1234567890@#%^()-_+=[]."


#endif /* CONFIG_H */
