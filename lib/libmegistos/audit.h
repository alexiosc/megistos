/*! @file    audit.h
    @brief   Auditing (logging) events.
    @author  Alexios

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     audit.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94 (originally)                                    **
 **  PURPOSE:  Audit trail features                                         **
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
 * Revision 1.5  2003/09/27 20:27:37  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.4  2001/05/20 13:58:13  alexios
 * Wisely changed HACKTRY to CRACKTRY. Cosmetic changes.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.10  1999/07/28 23:09:07  alexios
 * Added audit entry for downloading bulletins.
 *
 * Revision 0.9  1999/07/18 21:13:24  alexios
 * Added new entries to distinguish reasons why users hang up
 * or are kicked out.
 *
 * Revision 0.8  1998/08/14 11:23:21  alexios
 * Removed sysop hangup logging from security logs. Added
 * audit entry for relogons.
 *
 * Revision 0.7  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.6  1997/11/06 16:49:10  alexios
 * One change of flags for AUT_SIGNUP.
 *
 * Revision 0.5  1997/11/05 10:52:05  alexios
 * Radical changes. Audit entries are now flagged by type and
 * severity (created a set of flags to take care of that, as
 * well as macros to take care of setting and clearing flags).
 * audit() now needs the message's flag as well. To simplify
 * things, a new macro has been generated to specify all three
 * audit arguments (AUT_, AUS_, AUD_) in one fell swoop. Added
 * AUT_ definitions for all entries already in this file. Finally,
 * added two entries that appear when logerror() or fatal()
 * are called, so as to attract the Sysop's attention when
 * something goes wrong with some user.
 *
 * Revision 0.4  1997/09/14 13:47:56  alexios
 * Added an audit entry for finished events (EVEND).
 *
 * Revision 0.3  1997/09/12 12:45:25  alexios
 * A couplpe of new audit entries added here.
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Updated contents of DISCON entry.
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



#ifndef AUDIT_H
#define AUDIT_H



/** @defgroup audit Auditing (logging)

    This header file provides functionality needed to use Megistos logging
    facilities. The system logs a variety of information:

    - Date,
    - Time,
    - BBS channel (or daemon/service name, where a channel isn't
	  available),
    - Message flags, giving the type and severity of the log entry,
    - Entry summary (typically a canned string), and
    - Detailed entry text.

    The default log file set up by the BBS library is the Audit Trail (Major
    users should be at home with the name). The API defined here allows you to
    switch to other files.

    In addition to the API, this include file predefines most of the entries
    that are most widely used by the standard modules.

@{
*/

/** @name Audit entry flags
    @filename AUF_flags

    @memo Audit entry types and severity levels.

    @doc Each log entry has one of more types associated with it, as well as one
    (and only one) severity level. The types and severity levels are used for
    log search, filtering and colour-coding.

*/
/*@{*/

#define AUF_SECURITY   0x0001	/**< Security auditing */
#define AUF_ACCOUNTING 0x0002	/**< Accounting (statistics etc) */
#define AUF_TRANSFER   0x0004	/**< File transfers/reads, etc */
#define AUF_EVENT      0x0008	/**< Event execution/logging */
#define AUF_OPERATION  0x0010	/**< System operation of some kind */
#define AUF_USERLOG    0x0020	/**< User logs (login/logout etc) */
#define AUF_OTHER      0x0040	/**< Other, miscellaneous kinds of auditing */

#define AUF_INFO       0x0080   /**< Informational (severity) */
#define AUF_CAUTION    0x0100   /**< Cautionary (severity) */
#define AUF_EMERGENCY  0x0200	/**< Emergency (severity) */

#define AUF_SEVERITY   (AUF_INFO|AUF_CAUTION|AUF_EMERGENCY)
#define AUF_SEVSHIFT   7
#define GETSEVERITY(f) ((((f)&AUF_SEVERITY)>>AUF_SEVSHIFT)-1)

/*@}*/


/*                    123456789012345678901234567890 */
#define AUS_CRACKTRY "INVALID PASSWORD ATTEMPT"
#define AUS_UNKUSER  "INVALID USERID ATTEMPT"
#define AUS_DUPUSER  "DUPLICATE LOGIN ATTEMPT"
#define AUS_LOGIN    "USER LOGIN"
#define AUS_RELOGON  "USER LOGOUT, RELOGGING ON"
#define AUS_LOGOUT   "USER LOGOUT"
#define AUS_SIGNUP   "NEW USER SIGNED UP"
#define AUS_DISCON   "LINE HANGUP"
#define AUS_TIMEOUT  "USER KICKED OUT (TIMEOUT)"
#define AUS_CREDHUP  "USER KICKED OUT (NO CREDITS)"
#define AUS_TIMEHUP  "USER KICKED OUT (TIME LIMIT)"
#define AUS_KICKED   "USER FORCEFULLY DISCONNECTED"
#define AUS_EVSPAWN  "EVENT ACTIVATION"
#define AUS_EVEND    "EVENT FINISHED"
#define AUS_CRDPOST  "CREDIT POST"
#define AUS_NEWCLSS  "CLASS CHANGE"
#define AUS_USERDEL  "USER DELETED"
#define AUS_RSMDEL   "USER MARKED FOR DELETION"
#define AUS_RSMUDEL  "USER DELETION MARK REMOVED"
#define AUS_RSSUSP   "USER SUSPENDED"
#define AUS_RSUSUSP  "USER UNSUSPENDED"
#define AUS_RSXMPT   "USER EXEMPTED"
#define AUS_RSUXMPT  "USER UNEXEMPTED"
#define AUS_ESUPLS   "FILE ATTACHMENT UPLOADED"
#define AUS_ESDNLS   "FILE ATTACHMENT DOWNLOADED"
#define AUS_ESUPLF   "FAILED FILE ATT UPLOAD"
#define AUS_ESDNLF   "FAILED FILE ATT DOWNLOAD"
#define AUS_BLTINS   "NEW BULLETIN ADDED"
#define AUS_BLTDEL   "BULLETIN DELETED"
#define AUS_BLTEDT   "BULLETIN MODIFIED"
#define AUS_BLTRD    "BULLETIN READ"
#define AUS_BLTDNL   "BULLETIN DOWNLOADED"
#define AUS_QWKDNL   "QWK PACKET DOWNLOADED"
#define AUS_QWKUPL   "QWK PACKET UPLOADED"
#define AUS_ERROR    "ERROR CONDITION OCCURRED"
#define AUS_FATAL    "FATAL ERROR OCCURRED!!!"


/*                    1234567890123456789012345678901234567890123456789012... */
#define AUD_CRACKTRY "User %-24s  Speed: %5s"
#define AUD_UNKUSER  "User %-24s  Speed: %5s"
#define AUD_DUPUSER  "%s is already online, Attempted speed: %5s"
#define AUD_LOGIN    "User %-24s  Speed: %5s"
#define AUD_RELOGON  "User %-24s  Speed: %5s"
#define AUD_LOGOUT   "User %-24s  Speed: %5s"
#define AUD_SIGNUP   "User %s"
#define AUD_DISCON   "User %-24s  Speed: %5s"
#define AUD_TIMEOUT  "User %-24s  Speed: %5s"
#define AUD_CREDHUP  "User %-24s  Speed: %5s"
#define AUD_TIMEHUP  "User %-24s  Speed: %5s"
#define AUD_KICKED   "%s kicked out %s"
#define AUD_EVSPAWN  "%s activated %s"
#define AUD_EVEND    "Event %s has finished (exit code %d)"
#define AUD_CRDPOST  "Posted %d %s credit(s) to %s"
#define AUD_NEWCLSS  "%s changed class %s -> %s"
#define AUD_USERDEL  "%s, CL:%s, CR:%d"
#define AUD_RSMDEL   "%s marked %s"
#define AUD_RSMUDEL  "%s unmarked %s"
#define AUD_RSSUSP   "%s suspended %s"
#define AUD_RSUSUSP  "%s unsuspended %s"
#define AUD_RSXMPT   "%s exempted %s"
#define AUD_RSUXMPT  "%s unexempted %s"
#define AUD_ESUPLS   "%s -> %s/%d.ATT"
#define AUD_ESDNLS   "%s <- %s/%d.ATT"
#define AUD_ESUPLF   "%s -) %s/%d.ATT"
#define AUD_ESDNLF   "%s (- %s/%d.ATT"
#define AUD_BLTINS   "%s added %s to /%s"
#define AUD_BLTDEL   "%s deleted %s from /%s"
#define AUD_BLTEDT   "%s edited %s in /%s"
#define AUD_BLTRD    "%s read %s in /%s"
#define AUD_BLTDNL   "%s downloaded %s in /%s"
#define AUD_QWKDNL   "%s <- QWK, %d bytes"
#define AUD_QWKUPL   "%s -> QWK"
#define AUD_ERROR    "Please see bbs/log/errors for details"
#define AUD_FATAL    "CHECK bbs/log/errors NOW!"


#define AUT_CRACKTRY (AUF_SECURITY|AUF_USERLOG|AUF_CAUTION)
#define AUT_UNKUSER  (AUF_SECURITY|AUF_USERLOG|AUF_CAUTION)
#define AUT_DUPUSER  (AUF_SECURITY|AUF_USERLOG|AUF_CAUTION)
#define AUT_LOGIN    (AUF_USERLOG|AUF_INFO)
#define AUT_RELOGON  (AUF_USERLOG|AUF_INFO)
#define AUT_LOGOUT   (AUF_USERLOG|AUF_INFO)
#define AUT_SIGNUP   (AUF_SECURITY|AUF_USERLOG|AUF_CAUTION)
#define AUT_DISCON   (AUF_USERLOG|AUF_CAUTION)
#define AUT_TIMEOUT  (AUF_USERLOG|AUF_INFO)
#define AUT_CREDHUP  (AUF_USERLOG|AUF_INFO)
#define AUT_TIMEHUP  (AUF_USERLOG|AUF_INFO)
#define AUT_KICKED   (AUF_OPERATION|AUF_USERLOG|AUF_INFO)
#define AUT_EVSPAWN  (AUF_EVENT|AUF_INFO)
#define AUT_EVEND    (AUF_EVENT|AUF_INFO)
#define AUT_CRDPOST  (AUF_ACCOUNTING|AUF_OPERATION|AUF_INFO)
#define AUT_NEWCLSS  (AUF_ACCOUNTING|AUF_OPERATION|AUF_INFO)
#define AUT_USERDEL  (AUF_SECURITY|AUF_ACCOUNTING|AUF_EVENT|AUF_USERLOG|AUF_OPERATION|AUF_INFO)
#define AUT_RSMDEL   (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_RSMUDEL  (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_RSSUSP   (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_RSUSUSP  (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_RSXMPT   (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_INFO)
#define AUT_RSUXMPT  (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_ESUPLS   (AUF_TRANSFER|AUF_INFO)
#define AUT_ESDNLS   (AUF_TRANSFER|AUF_INFO)
#define AUT_ESUPLF   (AUF_TRANSFER|AUF_INFO)
#define AUT_ESDNLF   (AUF_TRANSFER|AUF_INFO)
#define AUT_BLTINS   (AUF_TRANSFER|AUF_OPERATION|AUF_INFO)
#define AUT_BLTDEL   (AUF_OPERATION|AUF_CAUTION)
#define AUT_BLTEDT   (AUF_OPERATION|AUF_INFO)
#define AUT_BLTRD    (AUF_TRANSFER|AUF_INFO)
#define AUT_BLTDNL   (AUF_TRANSFER|AUF_INFO)
#define AUT_QWKDNL   (AUF_TRANSFER|AUF_INFO)
#define AUT_QWKUPL   (AUF_TRANSFER|AUF_INFO)
#define AUT_ERROR    (AUF_OTHER|AUF_EMERGENCY)
#define AUT_FATAL    (AUF_OTHER|AUF_EMERGENCY)


/** The main auditing function.

    In most cases, this function is all you need to know. It takes quite a few
    arguments and comes with a helper macro, #AUDIT (which is quite handy).
    
    @param channel the name of the current user's channel, or a daemon/service
    name if a channel is not available. A value of <tt>NULL</tt> is equivalent to
    thisuesronl::channel.

    @param flags the type and severity of this message, using <tt>AUF_</tt>
    constants.

    @param summary a string summarising the logged event. This is in capital
    letters by (Majoresque) convention.

    @param format a <tt>printf()</tt>-like fmt string that formats the detailed
    log text. Like <tt>printf()</tt>, this argument is followed by as many
    additional arguments as are required by the format specifiers.

    @return If the audit file could not be appended to, zero is returned, and
    errno is set appropriately. A non-zero value denotes success.

    @see AUDIT, audit_setfile(), printf()
*/

int audit(char *channel, uint32 flags, char *summary, char *format, ...);


/** AUDIT convenience macro.

    This macro shortens considerably most calls to audit(). By convention, audit
    entry flags, summary and detailed text are <tt>#define</tt>d as
    <tt>AUT_x</tt>, <tt>AUS_x</tt> and <tt>AUD_x</tt> macros, where @c x is a
    name common to all three. Given an argument x, the macro expands to the
    triplet <tt>AUT_x,AUS_x,AUD_x</tt>. In this way, arguments 2 to 4 of audit()
    can be replaced by a simple #AUDIT call.

    @see audit()
*/

#define AUDIT(x) AUT_##x,AUS_##x,AUD_##x


/** Set the audit file.

    Specifies the audit file to which subsequent calls to audit() will append
    entries. In default of a call to this function, the Audit Trail will be
    used.

    @param filename the full pathname of a file to set as the current audit
    file. A value of @c NULL is equivalent to calling {\tt audit_resetfile</tt>.

    @see audit_resetfile()
*/

void audit_setfile(char *filename);


/** Revert to the previous audit file.

    Resets the audit filename to the Audit Trail.

    @see audit_setfile()
*/

void audit_resetfile();



#endif /* AUDIT_H */


/*@}*/

/*
LocalWords: Alexios doc Megistos BBS API legalese otnotesize alexios Exp
LocalWords: bbs downloading sysop hangup relogons GPL AUT SIGNUP AUS AUD
LocalWords: logerror Sysop's EVEND couplpe DISCON ifndef VER endif AUF ATT
LocalWords: USERLOG SEVSHIFT GETSEVERITY HACKTRY UNKUSER USERID DUPUSER CL
LocalWords: RELOGON RELOGGING CREDHUP TIMEHUP EVSPAWN CRDPOST NEWCLSS QWK
LocalWords: USERDEL RSMDEL RSMUDEL RSSUSP RSUSUSP RSXMPT RSUXMPT ESUPLS CR
LocalWords: UNEXEMPTED ESDNLS DOWNLOADED ESUPLF ESDNLF DOWNLOAD BLTINS tt
LocalWords: BLTDEL BLTEDT BLTRD BLTDNL QWKDNL QWKUPL unexempted downloaded
LocalWords: param thisuesronl Majoresque printf fmt errno setfile int uint
LocalWords: resetfile */
