/** @name    filexfer.h
    @memo    Uploading and downloading files.
    @author  Alexios

    @doc

    Like every self-respecting BBS worth the coffee it was coded on, Megistos
    allows users to transfer files from and to the system. The file transfer
    subsystem is a pretty complex thing in itself. Thankfully, its API is
    disproportionately easy to use.

    This interface provides functions to add files to the user's upload or
    download queue, call the file transfer module, and customise its actions
    before and after the file transfer itself.

    Original banner, legalese and change history follow.

    {\footnotesize
    \begin{verbatim}

 *****************************************************************************
 **                                                                         **
 **  FILE:     filexfer.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 94                                               **
 **  PURPOSE:  Interface to the upload/download stuff.                      **
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
 * Revision 0.5  1998/08/14 11:23:21  alexios
 * Added "transient" mode for files (transient files can be
 * downloaded, but not tagged). Updated addwild() to allow
 * specification of download mode.
 *
 * Revision 0.4  1998/07/26 21:17:06  alexios
 * Added scripts to be called after success or failure of a
 * file transfer.
 *
 * Revision 0.3  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 16:49:10  alexios
 * Changed the file transfer module to allow registration of
 * audit entries for the new auditing scheme.
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


#ifndef FILEXFER_H
#define FILEXFER_H


#define XFERLIST TMPDIR"/xfer%05d"
#define TAGLIST  TMPDIR"/tag%s%s"


/** File transfer item structure (deprecated)
    
    @deprecated Do not use the structure directly. Use {\tt filexfer_t} (the
    {\tt typedef} instead.

    @doc This has fields for all the information needed to upload or download a
    file. In short, the following capabilities of the file transfer subsystem
    are reflected here:

    \begin{itemize}

    \item Can allow files to be downloaded (BBS to user) or uploaded (user to
    BBS).

    \item Allows user-defined auditing of both successful and failed
    transfers. There are separate settings for each case.

    \item Allows a shell command to be executed immediately after successful or
    failed transfers. There are two separate commands for each occasion.

    \item Automatically refunds the user for canceled file transfers with a
    charge attached.

    \end{itemize}

    @see xfer_item_t.  */

struct xfer_item {
  uint32 magic;		  /** Magic number (XFER_ITEM_MAGIC) */
  char   dir;		  /** One of the {\tt FXM_x} constants  */
  char   fullname[256];	  /** Full path to the file */
  char   *filename;	  /** Pointer to basename inside {\tt fullname} */
  char   description[50]; /** Short description of the file */
  uint32 auditfok;	  /** Audit flags used to log successful transfer */
  char   auditsok[80];	  /** Audit summary used to log successful transfer */
  char   auditdok[80];    /** Audit detailed text template (used on success) */
  int    auditffail;	  /** Audit flags used to log failed transfer */
  char   auditsfail[80];  /** Audit summary used to log failed transfer */
  char   auditdfail[80];  /** Audit detailed text template (failed transfer) */
  char   cmdok[80];       /** Command to execute after successful transfer */
  char   cmdfail[80];     /** Command to execute after failed transfer */
  uint32 size;            /** File size (bytes) */
  int32  credspermin;     /** Credit consumption rate (times 100) */
  int32  refund;	  /** Credits to refund in case of failure */
  uint32 flags;           /** File transfer flags (internal use only) */
  int32  result;          /** File transfer result (internal use only) */
};

/** Proper way to refer to a transfer item.

    Use this instead of {\tt struct xfer_item}.

    @see struct xfer_item.
*/

typedef struct xfer_item xfer_item_t;


#define XFER_ITEM_MAGIC "Mxfi"


/** @name File transfer modes
    @filename FXM_flags

    @memo File transfer modes.

    @doc These control the direction and type of a file to be
    transferred. Please note that they are {\em NOT} to be ORred
    together. Although they don't look that way, they are mutually exclusive:
    {\tt FXM_TRANSIENT} implies a download.

    \begin{description}
    
    \item[{\tt FXM_UPLOAD}] The user will upload a file to the BBS.

    \item[{\tt FXM_DOWNLOAD}] The user will download a file from the BBS. The
    file is considered permanent. It will be there (at least) until the user's
    exit from the system.

    \item[{\tt FXM_TRANSIENT}] The user will download a temporary file from the
    BBS. Transient files are built by a module and are deleted at some
    undefined time {\em before} the user's exit from the system. As such, their
    download cannot be postponed until later.

    \end{description}

    @see xfer_add(), xfer_addwild().
*/
/*@{*/

#define FXM_UPLOAD    'U'
#define FXM_DOWNLOAD  'D'
#define FXM_TRANSIENT 'T'

/*@}*/


/** Customise post-transfer auditing.

    This function should be executed before adding a file to the transfer
    list. It will affect any subsequent additions to the list, but not existing
    items.

    The arguments of this function are ordered in such a way as to allow the
    use of the {\tt AUDIT} macro, as used in normal auditing. If any of the
    string arguments is {\tt NULL}, the corresponding logging action will not
    be performed. This way you can add logging for, say, failed transfers, but
    not successful ones.

    Please note that, unlike {\tt audit()}, you {\em cannot} provide arguments
    to the detailed information format strings ({\tt dok} and {\tt
    dfail}). These must always contain the following two format specifiers,
    {\em in order}:

    \begin{enumerate}

    \item A string ({\tt \%s}) specifier. This will be substituted by the user
    ID of the user performing the transfer.

    \item A string ({\tt \%s}) specifier to be substituted by the transfer
    filename.

    \end{enumerate}

    It might be nice to use (loosely) the Major shorthand for successful and
    failed file transfers: `{\tt user <- file}' for successful downloads, `{\tt
    user (- file}' (think of a blunt arrow) for failed downloads. For uploads,
    the arrow points to the right. Of course, you can always add any required
    information to this.

    @param fok audit type and severity for successful transfer logging.
    @param sok audit summary for successful transfers.
    @param dok audit detailed text template for successful transfers.

    @param ffail audit type and severity for failed transfer logging.
    @param sfail audit summary for failed transfers.
    @param dfail audit detailed text template for failed transfers.

    @see AUDIT, xfer_add(), xfer_addwild(). */

void xfer_setaudit(uint32 fok, char *sok, char *dok,
		   uint32 ffail, char *sfail, char *dfail);


/** Customise post-transfer commands.

    This function sets a pair of commands to be executed after a successful or
    failed download respectively. Please uses this responsibly and with an eye
    open for security risks. The command will, of course, be executed by the
    {\tt bbs} user, but be wary of untested {\tt rm}s, or commands with
    components that may be filled in by users.

    This will affect any subsequent additions to the transfer queue, but not
    existing entries. Use this function before adding files to the queue and
    {\em REMEMBER TO RESET IT AFTERWARDS} if you'll be transferring other files
    from within the current module.

    To disable a command execution, pass a {\tt NULL} to the corresponding
    argument. To reiterate, if you use this function, you should call {\tt
    xfer_setcmd(NULL,NULL)} immediately after calling {\tt xfer_run()}.

    @param cmdok a command to execute if the transfer succeeds.
    @param cmdfail a command to execute if the transfer fails.

    @see xfer_add(), xfer_addwild(). */

void xfer_setcmd(char *cmdok, char *cmdfail);


/** Add a file to the transfer queue.

    This function adds a file for transfer. A number of arguments are required:

    @param mode one of the {\tt FXM_x} file transfer modes.
    
    @param file the full pathname to a file. If this file is about to be
    uploaded (user to BBS), this is the recommended (but {\em NOT} certain)
    name of the file.

    @param description a short (50 bytes including terminating null)
    description of the file.

    @param refund how many credits we will refund the user for canceling this
    transfer.

    @param credspermin credit consumption rate during the file transfer. {\em
    This quantity is times 100}. To specify consumption of 2.5 credits per
    minute, use 250. Specify 0 for no time-based credit charges, or -1 for the
    current per-minute charge, whatever that is.

    @return This function returns 0 if the file is being downloaded and {\tt
    fstat()} could not access {\tt file}, or (regardless of file direction) if
    the file transfer queue for this user could not be appended to.

    @see xfer_setaudit(), xfer_setcmd(), xfer_addwild() */

int xfer_add(char mode, char *file, char *description,
	     int32 refund, int32 credspermin);

/** Add a number of files to the transfer queue.

    This function adds zero or more files for transfer, based on a UNIX glob
    (filename with wildcards). This function is very similar to {\tt
    xfer_add()}, but is more useful for downloads than uploads. Be warned, this
    function executes the {\tt find} UNIX command to expand the glob. This
    implies a relative lack of speed and a serious lack of security.

    {\em DO NOT CALL THIS FUNCTION WITH USER-SUPPLIED VALUES FOR THE {\tt
    filespec} ARGUMENT}.

    @param mode one of the {\tt FXM_x} file transfer modes.
    
    @param filespec a glob that will be expanded in order to get the
    filenames. Anything that you could give to, say, {\tt ls} is
    acceptable. Incorrectly formed globs will simply yield no filenames.

    @param description a short (50 bytes including terminating null)
    description of the files. The description will be common to all files.

    @param refund how many credits we will refund the user for canceling {\em
    EACH FILE} in this transfer.

    @param credspermin credit consumption rate during the file transfer. {\em
    This quantity is times 100}. To specify consumption of 2.5 credits per
    minute, use 250. Specify 0 for no time-based credit charges, or -1 for the
    current per-minute charge, whatever that is.

    @return This function returns 0 if the {\tt find} command could not run to
    expand the glob, or if the file transfer queue for this user could not be
    appended to.

    @see xfer_setaudit(), xfer_setcmd(), xfer_add() */

int xfer_addwild(char mode, char *filespec, char *description,
		 int32 refund, int32 credspermin);


/** Begin the file transfer.

    This very simple function begins the file transfer. It should be run after
    one of more files have been added to the transfer queue, or if you can
    guarantee that the queue contains files. The file transfer subsystem will
    exit gracefully if the list is empty, but not before notifying the user of
    this. You don't want to appear stupid in front of your users, do you?

    @return The UNIX exit code of the file transfer module. This is the same as
    that returned by the C {\tt system()} function. A value of 0 means that the
    subsystem has exited normally. Anything else represents an abnormal
    termination.
*/

int xfer_run();


/** Empties the transfer queue.

    Run this function to delete the user's transfer queue. Do not use this
    function unless you really, really know what you're doing. The transfer
    queue may contain file transfer requests other than your own module's.

    @return The same as the {\tt unlink()} system call: zero if everything went
    well, -1 if not (in which case, {\tt errno} will be set accordingly).
*/

int xfer_kill_list();


/** Clears the tagged file list.

    Run this function to delete the user's tagged file list. Do not use this
    function unless you really, really know what you're doing. The transfer
    queue may contain postponed file transfer requests other than your own
    module's.

    @return The same as the {\tt unlink()} system call: zero if everything went
    well, -1 if not (in which case, {\tt errno} will be set accordingly).
*/

int xfer_kill_taglist();


#endif /* FILEXFER_H */

/*@}*/

/*
LocalWords: filexfer Alexios doc BBS Megistos API customise legalese Exp
LocalWords: otnotesize alexios bbs addwild GPL ifndef VER endif XFERLIST
LocalWords: TMPDIR xfer TAGLIST tt struct uint dir FXM fullname basename
LocalWords: auditfok auditsok auditdok int auditffail auditsfail cmdok em
LocalWords: auditdfail cmdfail credspermin Mxfi ORred dok dfail param fok
LocalWords: sok ffail sfail setaudit rm setcmd fstat wildcards filespec ls
LocalWords: globs errno taglist
*/
