/*****************************************************************************\
 **                                                                         **
 **  FILE:     sysstruct.h                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Define system structures, system variable structs, etc       **
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
 * Revision 1.1  2001/04/16 14:48:56  alexios
 * Initial revision
 *
 * Revision 0.6  1998/12/27 15:19:19  alexios
 * Added magic number fields etc.
 *
 * Revision 0.5  1998/08/14 11:23:21  alexios
 * Increased width of monitor.channel to accommodate a full
 * user name for the new modus operandi of the MONITOR command.
 *
 * Revision 0.4  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/05 10:52:05  alexios
 * Removed SVR_SOPAUD. With the new auditing scheme, this is
 * obsolete; the operator has far more features than just
 * turning auditing notification on and off.
 *
 * Revision 0.2  1997/11/03 00:29:40  alexios
 * Made emuqueue and monitor volatile.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef SYSSTRUCT_H
#define SYSSTRUCT_H


struct emuqueue {
  volatile char queue [16376];
  volatile int  index;
  volatile int  xlation;
}; 


struct monitor {
  volatile long timestamp;
  volatile char channel[24];
  volatile char input[8192-28];
};


struct sysvar {
  char bbstitle   [52];
  char company    [48];
  char address1   [48];
  char address2   [48];
  char city       [48];
  char dataphone  [48];
  char voicephone [48];
  char livephone  [48];
  long idlezap;
  long saverate;
  char chargehour [32];
  char mincredits [32];
  char minmoney   [32];
  long flags;
  long pswexpiry;
  long injaudit;
  int  pagekey;
  int  pgovkey;
  int  pallkey;
  int  glockie;
  int  lonaud;
  int  lofaud;
  int  tnlmax;
  int  idlovr;
  int  bbsrst;
  
  char dummy1 [6144 - 540];

  int  tcredspaid;        /* Total paid credits posted ever        */
  int  tcreds;            /* Total credits (paid+free) posted ever */
  int  timever;           /* Total on-line time ever               */
  int  filesupl;          /* Total number of files uploaded ever   */
  int  filesdnl;          /* Total number of files downloaded ever */
  long bytesupl;          /* Total bytes * 100 uploaded ever       */
  long bytesdnl;          /* Total bytes * 100 downloaded ever     */
  int  sigmessages;       /* Total SIG messages written            */
  int  emessages;         /* Total Email messages written          */
  int  nmessages;         /* Total outgoing (net) messages written */
  int  connections;       /* Total number of connections ever      */
  int  incnetmsgs;        /* Total incoming net messages received  */
  int  emsgslive;         /* Email messages active at this time    */
  int  clubmsgslive;      /* Club messages active at this time     */

  char dummy2 [2044 - 56];

  char magic[4];	  /* Magic number is last to make sure
                             everything has been written properly
			     to the file */
};


#define SVR_MAGIC "SVAR"


#define SVR_STARTANSI  0x3
#define SVR_ANSIOFF    0x00000000
#define SVR_ANSION     0x00000001
#define SVR_ANSIASK    0x00000002


struct clsstats {
  char name[10];
  long credits;
  long minutes;
};


struct ttystats {
  char name[32];
  int  channel;
  long credits;
  long minutes;
  long calls;
};


struct baudstats {
  long baud;
  long credits;
  long minutes;
  long calls;
};


struct usagestats {
  long credits;
  long minutes;
};


struct modstats {
  char name[44];
  long credits;
  long minutes;
};


struct event {
  char descr[41];
  char command[256];
  int  hour, min;
  long flags;
  long lastrun;
};


#define EVF_ONLYONCE   0x0001
#define EVF_UNIQUE     0x0002
#define EVF_WARN       0x0004
#define EVF_ASAP       0x0008
#define EVF_NOW        0x0010


struct top {
  char label[40];
  char scorestg[16];
  int  score;
};


#endif /* SYSSTRUCT_H */
