/*****************************************************************************\
 **                                                                         **
 **  FILE:     audit.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94                                                 **
 **  PURPOSE:  Interface to audit.c                                         **
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
 * Revision 1.1  2001/04/16 14:48:45  alexios
 * Initial revision
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
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef AUDIT_H
#define AUDIT_H


#define AUF_SECURITY   0x0001	/* Security auditing */
#define AUF_ACCOUNTING 0x0002	/* Accounting (statistics etc) */
#define AUF_TRANSFER   0x0004	/* File transfers/reads, etc */
#define AUF_EVENT      0x0008	/* Event execution/logging */
#define AUF_OPERATION  0x0010	/* System operation of some kind */
#define AUF_USERLOG    0x0020	/* User logs (login/logout etc) */
#define AUF_OTHER      0x0040	/* Other kinds of auditing */
#define AUF_INFO       0x0080   /* }                      { Informational log */
#define AUF_CAUTION    0x0100   /* } Exactly One of these { Cautionary log */
#define AUF_EMERGENCY  0x0200	/* }                      { Emergency */

#define AUF_SEVERITY   (AUF_INFO|AUF_CAUTION|AUF_EMERGENCY)
#define AUF_SEVSHIFT   7
#define GETSEVERITY(f) ((((f)&AUF_SEVERITY)>>AUF_SEVSHIFT)-1)


/*                   123456789012345678901234567890 */
#define AUS_HACKTRY "INVALID PASSWORD ATTEMPT"
#define AUS_UNKUSER "INVALID USERID ATTEMPT"
#define AUS_DUPUSER "DUPLICATE LOGIN ATTEMPT"
#define AUS_LOGIN   "USER LOGIN"
#define AUS_RELOGON "USER LOGOUT, RELOGGING ON"
#define AUS_LOGOUT  "USER LOGOUT"
#define AUS_SIGNUP  "NEW USER SIGNED UP"
#define AUS_DISCON  "LINE HANGUP"
#define AUS_TIMEOUT "USER KICKED OUT (TIMEOUT)"
#define AUS_CREDHUP "USER KICKED OUT (NO CREDITS)"
#define AUS_TIMEHUP "USER KICKED OUT (TIME LIMIT)"
#define AUS_KICKED  "USER FORCEFULLY DISCONNECTED"
#define AUS_EVSPAWN "EVENT ACTIVATION"
#define AUS_EVEND   "EVENT FINISHED"
#define AUS_CRDPOST "CREDIT POST"
#define AUS_NEWCLSS "CLASS CHANGE"
#define AUS_USERDEL "USER DELETED"
#define AUS_RSMDEL  "USER MARKED FOR DELETION"
#define AUS_RSMUDEL "USER DELETION MARK REMOVED"
#define AUS_RSSUSP  "USER SUSPENDED"
#define AUS_RSUSUSP "USER UNSUSPENDED"
#define AUS_RSXMPT  "USER EXEMPTED"
#define AUS_RSUXMPT "USER UNEXEMPTED"
#define AUS_ESUPLS  "FILE ATTACHMENT UPLOADED"
#define AUS_ESDNLS  "FILE ATTACHMENT DOWNLOADED"
#define AUS_ESUPLF  "FAILED FILE ATT UPLOAD"
#define AUS_ESDNLF  "FAILED FILE ATT DOWNLOAD"
#define AUS_BLTINS  "NEW BULLETIN ADDED"
#define AUS_BLTDEL  "BULLETIN DELETED"
#define AUS_BLTEDT  "BULLETIN MODIFIED"
#define AUS_BLTRD   "BULLETIN READ"
#define AUS_BLTDNL  "BULLETIN DOWNLOADED"
#define AUS_QWKDNL  "QWK PACKET DOWNLOADED"
#define AUS_QWKUPL  "QWK PACKET UPLOADED"
#define AUS_ERROR   "ERROR CONDITION OCCURRED"
#define AUS_FATAL   "FATAL ERROR OCCURRED!!!"


/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_HACKTRY "User %-24s  Speed: %5s"
#define AUD_UNKUSER "User %-24s  Speed: %5s"
#define AUD_DUPUSER "%s is already online, Attempted speed: %5s"
#define AUD_LOGIN   "User %-24s  Speed: %5s"
#define AUD_RELOGON "User %-24s  Speed: %5s"
#define AUD_LOGOUT  "User %-24s  Speed: %5s"
#define AUD_SIGNUP  "User %s"
#define AUD_DISCON  "User %-24s  Speed: %5s"
#define AUD_TIMEOUT "User %-24s  Speed: %5s"
#define AUD_CREDHUP "User %-24s  Speed: %5s"
#define AUD_TIMEHUP "User %-24s  Speed: %5s"
#define AUD_KICKED  "%s kicked out %s"
#define AUD_EVSPAWN "%s activated %s"
#define AUD_EVEND   "Event %s has finished (exit code %d)"
#define AUD_CRDPOST "Posted %d %s credit(s) to %s"
#define AUD_NEWCLSS "%s changed class %s -> %s"
#define AUD_USERDEL "%s, CL:%s, CR:%d"
#define AUD_RSMDEL  "%s marked %s"
#define AUD_RSMUDEL "%s unmarked %s"
#define AUD_RSSUSP  "%s suspended %s"
#define AUD_RSUSUSP "%s unsuspended %s"
#define AUD_RSXMPT  "%s exempted %s"
#define AUD_RSUXMPT "%s unexempted %s"
#define AUD_ESUPLS  "%s -> %s/%d.ATT"
#define AUD_ESDNLS  "%s <- %s/%d.ATT"
#define AUD_ESUPLF  "%s -) %s/%d.ATT"
#define AUD_ESDNLF  "%s (- %s/%d.ATT"
#define AUD_BLTINS  "%s added %s to /%s"
#define AUD_BLTDEL  "%s deleted %s from /%s"
#define AUD_BLTEDT  "%s edited %s in /%s"
#define AUD_BLTRD   "%s read %s in /%s"
#define AUD_BLTDNL  "%s downloaded %s in /%s"
#define AUD_QWKDNL  "%s <- QWK, %d bytes"
#define AUD_QWKUPL  "%s -> QWK"
#define AUD_ERROR   "Please see bbs/log/errors for details"
#define AUD_FATAL   "CHECK bbs/log/errors NOW!"


#define AUT_HACKTRY (AUF_SECURITY|AUF_USERLOG|AUF_CAUTION)
#define AUT_UNKUSER (AUF_SECURITY|AUF_USERLOG|AUF_CAUTION)
#define AUT_DUPUSER (AUF_SECURITY|AUF_USERLOG|AUF_CAUTION)
#define AUT_LOGIN   (AUF_USERLOG|AUF_INFO)
#define AUT_RELOGON (AUF_USERLOG|AUF_INFO)
#define AUT_LOGOUT  (AUF_USERLOG|AUF_INFO)
#define AUT_SIGNUP  (AUF_SECURITY|AUF_USERLOG|AUF_CAUTION)
#define AUT_DISCON  (AUF_USERLOG|AUF_CAUTION)
#define AUT_TIMEOUT (AUF_USERLOG|AUF_INFO)
#define AUT_CREDHUP (AUF_USERLOG|AUF_INFO)
#define AUT_TIMEHUP (AUF_USERLOG|AUF_INFO)
#define AUT_KICKED  (AUF_OPERATION|AUF_USERLOG|AUF_INFO)
#define AUT_EVSPAWN (AUF_EVENT|AUF_INFO)
#define AUT_EVEND   (AUF_EVENT|AUF_INFO)
#define AUT_CRDPOST (AUF_ACCOUNTING|AUF_OPERATION|AUF_INFO)
#define AUT_NEWCLSS (AUF_ACCOUNTING|AUF_OPERATION|AUF_INFO)
#define AUT_USERDEL (AUF_SECURITY|AUF_ACCOUNTING|AUF_EVENT|AUF_USERLOG|AUF_OPERATION|AUF_INFO)
#define AUT_RSMDEL  (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_RSMUDEL (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_RSSUSP  (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_RSUSUSP (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_RSXMPT  (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_INFO)
#define AUT_RSUXMPT (AUF_SECURITY|AUF_ACCOUNTING|AUF_USERLOG|AUF_OPERATION|AUF_CAUTION)
#define AUT_ESUPLS  (AUF_TRANSFER|AUF_INFO)
#define AUT_ESDNLS  (AUF_TRANSFER|AUF_INFO)
#define AUT_ESUPLF  (AUF_TRANSFER|AUF_INFO)
#define AUT_ESDNLF  (AUF_TRANSFER|AUF_INFO)
#define AUT_BLTINS  (AUF_TRANSFER|AUF_OPERATION|AUF_INFO)
#define AUT_BLTDEL  (AUF_OPERATION|AUF_CAUTION)
#define AUT_BLTEDT  (AUF_OPERATION|AUF_INFO)
#define AUT_BLTRD   (AUF_TRANSFER|AUF_INFO)
#define AUT_BLTDNL  (AUF_TRANSFER|AUF_INFO)
#define AUT_QWKDNL  (AUF_TRANSFER|AUF_INFO)
#define AUT_QWKUPL  (AUF_TRANSFER|AUF_INFO)
#define AUT_ERROR   (AUF_OTHER|AUF_EMERGENCY)
#define AUT_FATAL   (AUF_OTHER|AUF_EMERGENCY)


extern char auditfile[256];


#define AUDIT(x) AUT_##x,AUS_##x,AUD_##x

int audit(char *channel, int flags, char *summary, char *format, ...);

void setauditfile(char *s);

void resetauditfile();



#endif /* AUDIT_H */
