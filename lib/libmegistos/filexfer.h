/*****************************************************************************\
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:48:51  alexios
 * Initial revision
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
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef FILEXFER_H
#define FILEXFER_H


#define XFERLIST TMPDIR"/xfer%05d"
#define TAGLIST  TMPDIR"/tag%s%s"


struct xferitem {
  char  dir;
  char  fullname[256];
  char  *filename;
  char  description[50];
  int   auditfok;
  char  auditsok[80];
  char  auditdok[80];
  int   auditffail;
  char  auditsfail[80];
  char  auditdfail[80];
  char  cmdok[80];
  char  cmdfail[80];
  int   size;
  int   credspermin;
  int   refund;
  int   flags;
  int   result;
};


#define FXM_UPLOAD    'U'
#define FXM_DOWNLOAD  'D'
#define FXM_TRANSIENT 'T'


void setaudit(int fok, char *sok, char *dok,
	      int ffail, char *sfail, char *dfail);

void setcmd(char *cmdok, char *cmdfail);

int addxfer(char mode, char *file, char *description,
	    int refund, int credspermin);

int addwild(char mode, char *filespec, char *description,
	    int refund, int credspermin);

int dofiletransfer();

int killxferlist();

int killtaglist();


#endif /* FILEXFER_H */
