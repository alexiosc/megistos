/*! @file    errors.h
    @brief    Error logging functionality.
    @author  Alexios

    Original banner, legalese and change history follow

    @par
    @verbatim

 *****************************************************************************
 **                                                                         **
 **  FILE:     errors.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Include file for errors.c. Provides fatal error logging.     **
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
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/09/27 20:30:29  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:13:24  alexios
 * Added an #include directive to read in errno.h. Some systems
 * don't define this in other include files and we need it.
 *
 * Revision 0.4  1998/12/27 15:19:19  alexios
 * Added functions to report system errors.
 *
 * Revision 0.3  1998/07/26 21:17:06  alexios
 * Automated the process of reporting the exact position of an
 * error.
 *
 * Revision 0.2  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
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



#ifndef ERRORS_H
#define ERRORS_H



/** @defgroup errors Reporting errors

    This header file defines means of reporting errors to various
    types of recipients. There are basically three different levels of
    errors:
    
    - Internal errors. These are recorded internally by appending them to the
      error log. The fact that an error occurred is also logged into the audit
      trail (though the exact nature of the error isn't). This type of error
      reporting is silent, making it suitable for situations where we don't want
      the user to know (mostly because we're sneaky offspring of female
      canines).

    - (Plain) errors. They are identical to internal errors, but a message is
      sent to the user after the error is logged and audited.

    - Fatal errors. These ones are pretty intrusive. In addition to logging,
      auditing and notifying the user, the current process is terminated.

    There are variants of the above error logging styles to log UNIX system
    errors. These are exactly as above, but the logging functions interpret the
    value of the UNIX @c errno variable and log its numerical value and textual
    explanation.
    
    Since error reporting should be available to non-interactive processes too,
    there is a mechanism to inhibit the user notification part of the reporting
    process. Please note that, any people with enough access to receive audit
    trail entries by automatic system paging will still get notified about
    these silent errors, since they are audited (depending on their setup of
    the personal audit trail filters, et cetera).

@{*/



#include <errno.h>


/** Log a plain error.

    Logs and audits an error, notifying the user. Don't worry about the unusual
    nature of most of the arguments. They are filled in automatically by the
    helper macro, #logerror. In fact, you <em>must not</em> use this function
    directly.

    @deprecated For internal use only. Please use #logerror instead.

    @param file the source filename where the error occurred.
    
    @param line the line number executing at the time of the error.

    @param format a printf()-like format string, followed by any necessary
           arguments, as required by the format specifiers.

    @see error_log() */

void _logerror(char *file, uint32 line, char *format, ...);


/** Log a plain system error.

    Logs and audits a system error, along with its standard UNIX
    explanation. The user is notified. Don't worry about the unusual nature of
    most of the arguments. They are filled in automatically by the helper macro,
    #logerror. In fact, you <em>must not</em> use this function directly.

    @deprecated For internal use only. Please use #logerror instead.

    @param file the source filename where the error occurred.
    
    @param line the line number executing at the time of the error.

    @param err the value of <tt>errno</tt>.

    @param format a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.

    @see error_logsys() */

void _logerrorsys(char *file, uint32 line, int32 err, char *format, ...);


/** Proper way to log a plain error.

    Logs and audits a non-fatal error. <em>This</em> is the function you should
    use in order to log an error.

    @param fmt a printf()-like format string, followed by any necessary
           arguments, as required by the format specifiers.
*/

#define error_log(fmt...) _logerror(__FILE__,__LINE__,##fmt)


/** Proper way to log a system error.

    Logs and audits a non-fatal system error, along with the explanation of the
    current value of @c errno. @e This is the function you should use in order
    to log a system error.

    @param fmt a printf()-like format string, followed by any necessary
           arguments, as required by the format specifiers.
*/

#define error_logsys(fmt...) \
{\
   int32 i=errno; \
   _logerrorsys(__FILE__,__LINE__,i,##fmt);\
}




/** Log an internal error.

    Logs and audits an error silently (no user notification). Don't worry about
    the unusual nature of most of the arguments. They are filled in
    automatically by the helper macro, #logerror. In fact, you <em>must not</em>
    use this function directly.

    @deprecated For internal use only. Please use #logerror instead.

    @param file the source filename where the error occurred.
    
    @param line the line number executing at the time of the error.

    @param format a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.

    @see error_int()
*/

void _interror(char *file, uint32 line, char *format, ...);


/** Log an internal system error.

    Logs and audits a system error, along with its standard UNIX
    explanation. The user is <em>not</em> notified. Don't worry about the unusual
    nature of most of the arguments. They are filled in automatically by the
    helper macro, <tt>logerror}. In fact, you <em>must not</em> use this function
    directly.

    @param file the source filename where the error occurred.
    
    @param line the line number executing at the time of the error.

    @param err the value of <tt>errno</tt>.

    @param format a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.

    @see error_intsys()
*/

void _interrorsys(char *file, uint32 line, int32 err, char *format, ...);


/** Proper way to log an internal error.

    Logs and audits an internal error. <em>This</em> is the function you should
    use in order to log such an error.

    @param fmt a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.
*/

#define error_int(fmt...) _interror(__FILE__,__LINE__,##fmt)


/** Proper way to log an internal system error.

    Logs and audits an internal system error, along with the explanation of the
    current value of <tt>errno}. {\em This</tt> is the function you should use in
    order to log a system error.

    @param fmt a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.
*/

#define error_intsys(fmt...) \
{\
   int32 i=errno; \
   _interrorsys(__FILE__,__LINE__,i,##fmt);\
}


/** Log a fatal error.

    Logs and audits a fatal error. The user is notified and the current process
    is terminated. Don't worry about the unusual nature of most of the
    arguments. They are filled in automatically by the helper macro, {\tt
    logerror}. In fact, you <em>must not</em> use this function directly.

    @param file the source filename where the error occurred.
    
    @param line the line number executing at the time of the error.

    @param format a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.

    @see error_fatal() */

void _fatal(char *file, int line, char *format, ...);


/** Log a fatal system error.

    Logs and audits a fatal system error, along with its standard UNIX
    explanation. The user is notified and the current process is
    terminated. Don't worry about the unusual nature of most of the
    arguments. They are filled in automatically by the helper macro, {\tt
    logerror}. In fact, you <em>must not</em> use this function directly.

    @param file the source filename where the error occurred.
    
    @param line the line number executing at the time of the error.

    @param err the value of <tt>errno</tt>.

    @param format a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.

    @see error_fatalsys() */

void _fatalsys(char *file, int line, int err, char *format, ...);


/** Proper way to log a fatal error.

    Logs and audits a fatal error. <em>This</em> is the function you should use in
    order to log such an error.

    @param fmt a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.  */

#define error_fatal(fmt...) _fatal(__FILE__,__LINE__,##fmt)


/** Proper way to log a fatal system error.

    Logs and audits a fatal system error, along with the explanation of the
    current value of <tt>errno</tt>. The user is notified and the current process
    is terminated. <em>This</em> is the function you should use in order to log a
    system error.

    @param fmt a <tt>printf()</tt>-like format string, followed by any
           necessary arguments, as required by the format specifiers.  */

#define error_fatalsys(fmt...) \
{\
   int32 i=errno; \
   _fatalsys(__FILE__,__LINE__,i,##fmt);\
}


/** Enable or disable user notifications.

    @param state Pass zero to disable all user notifications. Non-zero values
    enable notifications.
*/

void error_setnotify(int state);


#endif /* ERRORS_H */


/*@}*/

/*
LocalWords: Alexios doc tt errno legalese otnotesize alexios Exp bbs GPL
LocalWords: ifndef VER endif logerror em param printf uint logsys int fmt
LocalWords: logerrorsys interror intsys interrorsys fatalsys setnotify
*/
