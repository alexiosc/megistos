/*****************************************************************************\
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:48:54  alexios
 * Initial revision
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
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef MAIL_H
#define MAIL_H


struct message {
  char from    [80];
  char to      [80];
  char subject [64];
  char history [80];
  char fatt    [16];
  long msgno;
  long flags;
  int  crdate;
  int  crtime;
  int  replies;
  int  timesread;
  int  timesdnl;
  int  period;
  int  cryptkey;
  char club     [16];
  char origbbs  [32];
  char origclub [16];
  char msgid    [32];
  long replyto;
};



#define ALL "***ALL***"

#define MSF_EXEMPT   0x0001
#define MSF_RECEIPT  0x0002
#define MSF_FILEATT  0x0004
#define MSF_APPROVD  0x0008
#define MSF_CANTMOD  0x0010
#define MSF_SIGNUP   0x0020
#define MSF_AUTOFW   0x0080
#define MSF_REPLY    0x0100
#define MSF_NET      0x0200

#define MSF_COPYMASK (MSF_FILEATT|MSF_REPLY)
#define MSF_NETMASK  (MSF_EXEMPT|MSF_APPROVD|MSF_FILEATT|MSF_FILEATT)


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


struct emailuser {
  char forwardto[24];
  long flags;
  long prefs;
  int  lastemailread;
  int  lastemailqwk;
  
  char dummy[512-40];
};


#define ECP_QUOTEYES 0x0001
#define ECP_QUOTEASK 0x0002
#define ECP_LOGINYES 0x0004
#define ECP_LOGINASK 0x0008

#define ECF_QSCCFG   0x0001


struct lastread {
  char club[16];
  int  lastmsg;
  int  flags;
  int  emllast;
  int  entrymsg;     /* This is a general purpose temp field */
  int  qwklast;

  char dummy[8];
};


#define LRF_QUICKSCAN 0x0001
#define LRF_INQWK     0x0002
#define LRF_DELETED   0x0004
#define LRF_INITQWK   0x0010


struct clubheader {
  char club[32];                /* name of the club   */
  int  clubid;                  /* number of the club */
  char descr[64];               /* club description */
  char clubop[24];              /* main club operator */
  int  crdate;                  /* club creation date */
  int  crtime;                  /* club creation time */

  int  msgno;                   /* highest message number */
  int  nmsgs;                   /* number of messages */
  int  nper;                    /* number of periodic messages */
  int  nblts;                   /* number of bulletins */
  int  nfiles;                  /* number of files */
  int  nfunapp;                 /* number of unapproved files */

  int  keyreadax;               /* key required for read access */
  int  keydnlax;                /* key required for download access */
  int  keywriteax;              /* key required for write access */
  int  keyuplax;                /* key required for upload access */

  int  flags;                   /* club options */

  int  msglife;                 /* message lifetime */
  int  postchg;                 /* charge for posting */
  int  uploadchg;               /* charge for uploading */ 
  int  dnloadchg;               /* charge for downloading */
  int  credspermin;             /* credits/100 mins, -1=default */

  char export_access_list[128];	/* allow/deny access list */

  char dummy[1024-324];
};


#define CLF_MMODAX 0x0001
#define CLF_MMODCH 0x0002
#define CLF_MMODHD 0x0004


#define CAX_SYSOP    70
#define CAX_CLUBOP   60
#define CAX_COOP     50
#define CAX_UPLOAD   40
#define CAX_WRITE    30
#define CAX_DNLOAD   20
#define CAX_READ     10
#define CAX_ZERO      0
#define CAX_DEFAULT  -1



/* Guest flags for the IHAVE structures */

#define IHT_MESSAGE        0
#define IHT_CONTROL_DELETE 1	/* oooh, can we have ALT too? */



#endif /* MAIL_H */
