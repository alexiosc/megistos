/*****************************************************************************\
 **                                                                         **
 **  FILE:     useracc.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Define data structures used for storing users et al.         **
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
 * Revision 1.1  2001/04/16 14:49:00  alexios
 * Initial revision
 *
 * Revision 0.11  2000/01/06 11:40:19  alexios
 * Added field lastconsolepage to denote the time of the user's
 * last page to the console (if any). The field was, of course,
 * added to the onlinerec structure.
 *
 * Revision 0.10  1998/12/27 15:19:19  alexios
 * Added user magic numbers and declarations for the functions
 * migrated from miscfx.h.
 *
 * Revision 0.9  1998/08/14 11:23:21  alexios
 * Added on-line flag to tell bbsd and emud that we're not
 * logging off completely (this is only for auditing purposes).
 *
 * Revision 0.8  1998/07/26 21:17:06  alexios
 * Added a flag to force idle zapping of users on telnet
 * connections.
 *
 * Revision 0.7  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.6  1997/11/06 16:49:10  alexios
 * Renamed USY_AUDITPAGE to USY_PAGEAUDIT so it's easier to
 * find in the remsys module. Added new command flags for the
 * new commands in remsys (USY_SECURITY, USY_SIGNUPS and
 * USY_FILTAUD).
 *
 * Revision 0.5  1997/11/05 10:52:05  alexios
 * Cosmetic changes. Added field auditfiltering in useracc to
 * store operator's audit filtering preferences. Added remote
 * sysop command flags USY_AUDITPAGE. Changed the values of
 * USY_INVIS and USY_GDET (shouldn't have; they're not in
 * alpha order anyway). Obsoleted OLF_SOPAUD since
 * useracc.auditfiltering is used now.
 *
 * Revision 0.4  1997/11/03 00:29:40  alexios
 * Removed defines for hardwired xlation tables, added code
 * and defines for generalised tables.
 *
 * Revision 0.3  1997/09/12 12:48:48  alexios
 * Added the last selected library to onlinerec. Also added a
 * field injothqueue to hold the IPC ID of the injoth queue for
 * this user.
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Added OLF_LOGGEDOUT to distinguish between normal and unexpected
 * disconnections from the system.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef USERACC_H
#define USERACC_H

#ifndef CHAR
#define CHAR unsigned char
#endif

#include "config.h"


#define DELIM    "!@#$%^&*-_=+.:"

typedef struct {
  char userid   [24];    /* User ID                             */
  char passwd   [16];    /* Password                            */
  char username [32];    /* Real name                           */
  char company  [32];    /* User's company                      */
  char address1 [32];    /* Address, line 1                     */
  char address2 [32];    /* Address, line 2                     */
  char phone    [24];    /* Phone number                        */
  long prefs;            /* Preference flags                    */
  long flags;            /* General flags                       */
  long sysaxs   [ 3];    /* Sysop flags                         */
  char age;              /* Age                                 */
  char sex;              /* Sex (M/F)                           */
  char system;           /* System type                         */
  char language;         /* Language pref'd                     */
  CHAR scnwidth;         /* Screen width                        */
  CHAR scnheight;        /* Screen height                       */
  long datecre;          /* Signup date                         */
  long datelast;         /* Last logged on                      */
  long passexp;          /* Password expiry in N days           */
  char tempclss [10];    /* Previous Class                      */
  char curclss  [10];    /* Current Class                       */
  long timetdy;          /* Time spent today                    */
  long classdays;        /* Days spent in current class         */
  long credits;          /* Credits left                        */
  long totcreds;         /* Total credits posted                */
  long totpaid;          /* Total credits paid                  */
  long keys[KEYLENGTH];  /* 128 Key bits                        */
  long timever;          /* Time spent since signup             */
  long credsever;        /* Credits spent since signup          */
  long pagetime;         /* Time between allowing pages         */
  long pagestate;        /* Permanent page state                */
  long filesdnl;         /* Number of files downloaded          */
  long bytesdnl;         /* Number of bytes downloaded          */
  long filesupl;         /* Number of files uploaded            */
  long bytesupl;         /* Number of bytes downloaded          */
  long msgswritten;      /* Number of messages written          */
  long connections;      /* Number of connections               */
  char lastclub[16];     /* Last club visited                   */
  int  auditfiltering;   /* Flag mask for showing audit entries */
  
  char dummy[1020-348];
  char magic[4];         /* Magic number                        */
} useracc;

#define USR_MAGIC     "USER"

#define UPF_ANSION    0x00000001
#define UPF_VISUAL    0x00000002
#define UPF_NONSTOP   0x00000004
#define UPF_ANSIDEF   0x00000008
#define UPF_ANSIASK   0x00000010
#define _UPF_TR8BITGR 0x00000020 /* Obsolete; this flag value is free for the taking */
#define UPF_TRDEF     0x00000040
#define UPF_TRASK     0x00000080
#define UPF_TR0       0x00000100
#define UPF_TR1       0x00000200
#define UPF_TR2       0x00000300
#define UPF_TR3       0x00000400


/* The following macro extracts the 0-9 (0-15 actually) translation
   table number from the user's flags */

#define UPF_TRANS        (UPF_TR0|UPF_TR1|UPF_TR2|UPF_TR3)
#define UPF_TRSHIFT      8
#define getpxlation(u)   (((u).flags&UPF_TRANS)>>UPF_TRSHIFT)
#define setpxlation(u,i) ((u).flags=((u).flags&~UPF_TRANS)|\
			  (((i)&0xf)<<UPF_TRSHIFT))

#define USY_CHANGE      0
#define USY_EMULATE     1
#define USY_MONITOR     2
#define USY_SEND        3
#define USY_DELETE     10
#define USY_DETAIL     11
#define USY_EXEMPT     12
#define USY_HANGUP     13
#define USY_POST       14
#define USY_SEARCH     15
#define USY_SUSPEND    16
#define USY_AUDIT      20
#define USY_CLEANUP    21
#define USY_EVENT      22
#define USY_LOGON      23
#define USY_TRANSFER   24
#define USY_SECURITY   25
#define USY_SIGNUPS    26
#define USY_FILTAUD    27
#define USY_AGESTATS   30
#define USY_CLSSTATS   31
#define USY_GENSTATS   32
#define USY_LINSTATS   33
#define USY_MODSTATS   34
#define USY_SYSTATS    35
#define USY_TOP        36
#define USY_CLASS      40
#define USY_CLASSED    41
#define USY_KEYS       42
#define USY_COPY       50
#define USY_DEL        51
#define USY_DIR        52
#define USY_EDITOR     53
#define USY_REN        54
#define USY_SHELL      55
#define USY_SYS        56
#define USY_TYPE       57
#define USY_PAGEAUDIT  90
#define USY_INVIS      91
#define USY_GDET       92
#define USY_SYSOP      95
#define USY_MASTERKEY  95

#define UFL_SUSPENDED 0x00000001
#define UFL_DELETED   0x00000002
#define UFL_EXEMPT    0x00000004

#define USX_MALE   'M'
#define USX_FEMALE 'F'

typedef struct {
  char name        [10];    /* Name of class                          */
  char notaround   [10];    /* Class to go to when user not logged on */
  int  nadays;              /* ... for nadays number of days          */
  char around      [10];    /* Class to go to after user has been     */
  int  ardays;              /* ... around for ardays number of days   */
  char nocreds     [10];    /* Class to go to when no credits left    */
  char credpost    [10];    /* Class to go to when paid creds posted  */
  int  limpercall;          /* Time limit per call (-1 disables)      */
  int  limperday;           /* Time limit per day (-1 disables)       */
  int  crdperday;           /* Free time per day                      */
  int  crdperweek;          /* Bonus time posted every week           */
  int  crdpermonth;         /* Bonus time posted every month          */
  long flags;               /* Flags bits                             */
  long users;               /* Number of users in this class          */
  long keys[KEYLENGTH];     /* 128 Key bits                           */

  char dummy[512-104];
} classrec;

#define CF_NOCHRGE 0x0002   /* Class exempt from credit charges    */
#define CF_LINUX   0x0004   /* Users have access to linux shell    */
#define CF_LOCKOUT 0x0008   /* Users not allowed to login at all   */
#define CF_CRDXFER 0x0010   /* Allowed to xfer credits to others   */


#define ML NUMLANGUAGES

typedef struct { 
  char userid     [24];      /* User's ID, just for checking        */
  char channel    [16];      /* User's channel, minus "/dev/"       */
  char emupty     [16];      /* Emulation PTY, user's 'real' tty    */
  long baudrate;             /* User's baud rate                    */
  char curpage    [32];      /* User's current page in the menuman  */
  char prevpage   [32];      /* User's previous menuman page        */
  long flags;                /* Generic on-line flags               */
  char input     [256];      /* User's last input concatenation     */
  char descr     [ML][44];   /* User's position described           */
  int  pagestate;            /* Page enable flags                   */
  int  lastpage;             /* Time this user was last paged       */
  int  tick;                 /* bbsd ticks (used for credit charge) */
  int  credspermin;          /* Credit consumption, creds/100 min   */
  int  onlinetime;           /* Time (in min) user has been on-line */
  int  fraccharge;           /* Fractional charge (bbsd)            */
  int  timeoutticks;         /* Inactivity counter                  */
  int  idlezap;              /* Minutes of inactivity allowed       */
  int  statptrs;             /* Used internally by statd            */
  int  statcreds;            /* Used internally by statd            */
  long loggedin;             /* Time logged in: used by /recent     */
  char telechan[32];         /* Last teleconference channel         */
  int  telecountdown;        /* Times left to talk in telecons      */
  int  lastlib;              /* Last file library visited           */
  int  injothqueue;          /* IPC message queue ID for injoth()   */
  int  lastconsolepage;	     /* Time of last page to system console */
  
  char dummy[1020-476-44*ML];
  char magic[4];             /* Online User magic                   */
} onlinerec;


#define ONL_MAGIC     "OUSR"


#define OLF_MMEXITING 0x00000001
#define OLF_MMCALLING 0x00000002
#define OLF_MMCONCAT  0x00000004
#define OLF_ISYSOP    0x00000008
#define OLF_INVISIBLE 0x00000010
#define OLF_BUSY      0x00000020
#define OLF_NOTIMEOUT 0x00000040
#define OLF_ANSION    0x00000080
#define OLF_TR0       0x00000100
#define OLF_TR1       0x00000200
#define OLF_TR2       0x00000400
#define OLF_TR3       0x00000800
#define OLF_MMGCDGO   0x00001000
#define OLF_INHIBITGO 0x00002000
#define OLF_INTELECON 0x00004000
#define OLF_TLCUNLIST 0x00008000
#define OLF_FORCEIDLE 0x00010000
#define OLF_LOGGEDOUT 0x00020000
#define OLF_RELOGGED  0x00040000
#define OLF_ZAPBYPASS 0x00080000
#define OLF_JMP2BLT   0x00100000
#define OLF_INSYSCHAT 0x00200000

#define OLF_TRSHIFT      8
#define OLF_TRANS        (OLF_TR0|OLF_TR1|OLF_TR2|OLF_TR3)
#define getoxlation(o)   (((o).flags&OLF_TRANS)>>OLF_TRSHIFT)
#define setoxlation(o,i) ((o).flags=((o).flags&~OLF_TRANS)|\
			  (((i)&0xf)<<OLF_TRSHIFT))

#define PGS_STORE     0
#define PGS_OK        1
#define PGS_ON        2
#define PGS_OFF       3

#define CRD_PAID      1
#define CRD_FREE      0

#define STF_FIRST     1
  

struct shmuserrec {
  useracc   acc;
  onlinerec onl;
  char      aux[2048];
  
/*  char dummy[4096-4096]; */
};

extern struct shmuserrec *thisshm, *othrshm;

#define thisuseracc   (thisshm->acc)
#define othruseracc   (othrshm->acc)

#define thisuseronl   (thisshm->onl)
#define othruseronl   (othrshm->onl)

#define _thisuseraux  (thisshm->aux)
#define _othruseraux  (othrshm->aux)

extern classrec   *userclasses;
extern int        numuserclasses;


int userexists(char *uid);

classrec *findclass (char *s);

int loaduseraccount (char *whose, useracc *uacc);

int loaduseronlrec (char *whose, onlinerec *onlrec);

int saveuseraccount (useracc *uacc);

int saveuseronlrec (onlinerec *onlrec);

void postcredits (char *userid, int amount, int paid);

void chargecredits (int amount);

void changeclass (char *userid, char *newclass, int permanent);

int canpay(int amount);

int uinsystem(char *userid,int checkinvis, struct shmuserrec **buf);

int uinsys(char *userid,int checkinvis);

int injoth(onlinerec *user, char *msg, int force);

int uidxref(char *userid, int online);


#endif   /* USERACC_H */
