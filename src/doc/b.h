/** Extracts severity level from log entry flags. */

#define GETSEVERITY(f) ((((f)&AUF_SEVERITY)>>AUF_SEVSHIFT)-1)


/** @name Predefined audit entries

    These are the summaries for the most commonly used audit entries. I
    honestly don't know why they're defined here!

*/

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



extern char auditfile[256]; /** The currently active audit file */


/* The main auditing function.
  *
  * In most cases, this function is all you need to know. It takes quite a few
  * arguments.
  *
  * @param channel Is the name of the current channel, or a daemon/service name
  *        if a channel is not available.
  * @param ough.
*/

/** A global function.
  *
  * As promised, not only classes and members can be documented with
  * DOC++.  This is an example for how to document global scope
  * functions. You'll notice that there is no technical difference to
  * documenting member functions. The same applies to variables or macros.
  *
  *         @param c reference to input data object
  *         @return whatever
  *         @author Snoopy
  *         @version 3.3.12
  *         @see Derived_Class
  *
  * int function(const DerivedClass& c);
  * \end{verbatim}
  *
  * @param c reference to input data object
  * @return whatever
  * @author Snoopy
  * @version 3.3.12
  * @see Derived_Class
*/

int audit(char *channel, int flags, char *summary, char *format, ...);

/** Convenience macro

    This is a test.

    @param   x The name of an audit entry, without the AUF_, AUS_ or AUT_ prefixes.
    @return    A triplet AUT_x, AUS_x, AUD_x.

 */

#define AUDIT(x) AUT_##x,AUS_##x,AUD_##x


void setauditfile(char *s);

void resetauditfile();



#endif /* AUDIT_H */

