/*****************************************************************************\
 **                                                                         **
 **  FILE:     telecon.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences header file                                  **
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
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/28 23:13:16  alexios
 * Added a magic number for the aux structure.
 *
 * Revision 0.6  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/14 11:45:25  alexios
 * Slight cosmetic changes. Added prototypes for new functions.
 *
 * Revision 0.4  1998/08/11 10:21:33  alexios
 * Moved chanscan().
 *
 * Revision 0.3  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 11:14:03  alexios
 * Changed calls to audit so that they take advantage of the
 * new auditing scheme.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef _TELECON_H
#define _TELECON_H


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_DIRENT_H 1
#define WANT_SIGNAL_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mbk_telecon.h>


/*                   123456789012345678901234567890 */
#define AUS_CHMSGE  "CHANGED TELECONFERENCE MESSAGE"
#define AUS_CHMSGX  "CHANGED TELECONFERENCE MESSAGE"


/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_CHMSGE  "%s's entry msg, %d creds charged"
#define AUD_CHMSGX  "%s's exit msg, %d creds charged"


#define AUT_CHMSGE (AUF_INFO|AUF_ACCOUNTING)
#define AUT_CHMSGX (AUF_INFO|AUF_ACCOUNTING)


#define LIVE (key_owns(&thisuseracc,normkey))


#define TELETICK 15


struct tlcuser {
	int     colour;
	char    entrystg[80];
	char    exitstg[80];
	char    topic[64];
	int     flags;
	int     chatinterval;
	int     actions;

	char    dummy[1024 - 240];
};

#define TLF_STARTMAIN  0x00001
#define TLF_BEGUNINV   0x00002
#define TLF_BEGINV     0x00004
#define TLF_BEGPANEL   0x00008

#define MAINCHAN "Main"

#define CHANLOCK "LCK..telechan-%s"


struct chanhdr {
	char    moderator[24];
	char    topic[64];
	int     flags;
};


#define CHF_ACCESS     (CHF_OPEN|CHF_PRIVATE|CHF_READONLY)
#define CHF_OPEN       0x0001
#define CHF_PRIVATE    0x0002
#define CHF_READONLY   0x0004
#define CHF_MODERATED  0x0008


struct chanusr {
	char    userid[24];
	char    sex;
	int     flags;
};


#define CUF_NONE       0x000	/* No flags                            */
#define CUF_PRESENT    0x001	/* Is currently present in the channel */
#define CUF_UNLISTED   0x002	/* Has UNLIST on                       */
#define CUF_EXPLICIT   0x004	/* Explicitly invited or uninvited     */
#define CUF_ACCESS     0x008	/* Allowed into the channel            */
#define CUF_READONLY   0x010	/* Can't write messages                */
#define CUF_MODERATOR  0x020	/* Is the moderator for this channel   */
#define CUF_CHATTING   0x040	/* Was in this channel, now chatting   */
#define CUF_ALL        0xfff	/* All flags                           */


#define TELEAUX_MAGIC  0x54454c45	/* "TELE" */


struct usraux {
	int     magic;
	int     action;
	int     access;
	char    chatparty[24];
	int     chatting;
	int     lastinvitation;
	int     interval;
	int     chatid;
	int     colour;
	int     entrytick;
	int     numentries;
	int     actions;
	char    plugin[16];
	int     pluginq;
};


#define ACT_DROPMAIN  1
#define ACT_STARTCHAT 2


#define thisuseraux (*((struct usraux*)&_thisuseraux))
#define othruseraux (*((struct usraux*)&_othruseraux))




/* init.c */


extern promptblock_t *msg;

extern int entrkey;
extern int normkey;
extern int npaymx;
extern int maxcht;
extern int lnvcht1;
extern int lnvcht2;
extern int lnvcht3;
extern int tinpsz;
extern int msgkey;
extern int amsgch;
extern int msgchg;
extern int defcol;
extern int sopkey;
extern int chtkey;
extern int ichtkey;
extern int defint;
extern int chatcol1;
extern int chatcol2;
extern char *stgall1;
extern char *stgall2;
extern char *stgsec1;
extern char *stgsec2;
extern int actkey;
extern int defact;


void    init ();


/* channel.c */

extern char curchannel[];

extern struct chanhdr chanhdr;

int     enterchannel (char *channel);

void    leavechannel ();

void    killpersonalchannel ();

void    leavechannels ();

struct chanhdr *readchanhdr (char *channel);

void    writechanhdr (char *channel, struct chanhdr *c);

int     makechannel (char *channel, char *userid);

void    setchanax (int ax);

void    chanscan ();


/* usr.c */

extern struct tlcuser tlcu;

int     loadtlcuser (char *userid, struct tlcuser *tlc);

int     savetlcuser (char *userid, struct tlcuser *tlc);

void    makenewuser ();


/* broadcast.c */


int     broadcastchnall (char *curchannel, char *(*fx) (struct chanusr * u),
			 int all);

int     broadcastchn (char *curchannel, char *(*fx) (struct chanusr * u));

int     broadcast (char *(*fx) (struct chanusr * u));

void    usermsg (int pr);

void    userent (int pr);

void    userexit (int pr);

void    miscinfo (char *buf);


/* talk.c */

void    say (char *s);

void    whisper (char *s);

void    sayto (char *s);


/* utils.c */

extern const char *colours[];

char   *getcolour ();

int     tlcuidxref (char *userid, int inchannel);

void    showinfo ();

char   *getcolour ();

char   *mkchfn (char *chan);

char   *gettopic (char *chan);

void    countdown ();

int     checktick ();


/* editprefs.c */

void    editprefs ();


/* misc.c */

int     chanselect (const struct dirent *d);

void    joinchan (char *s);

void    flagunlist (int on);

void    sendmain (char *tty);

void    sendaction (char *userid, int action);

void    actionhandler ();

void    droptomain ();

void    squelch (char *s);

void    unsquelch (char *s);

void    topic (char *s);


/* clubhdr.c */


extern struct clubheader clubhdr;


int     findclub (char *club);

int     loadclubhdr (char *club);

int     getclubax (useracc_t * ucac, char *club);


/* accesses.c */

int     getaccess (char *chan);

int     getdefusrax (char *channel, char *userid);

int     getusrax (char *channel, char *userid);

void    setusrax (char *channel, char *userid, char sex, int flagson,
		  int flagsoff);

void    moderate (char *channel, char *userid, char *moderator);


/* scan.c */

#define TSM_ALL     0
#define TSM_PRESENT 1
#define TSM_ABSENT  2

struct chanhdr *begscan (char *channel, int mode);

struct chanusr *getscan ();

void    endscan ();



/* chanusr.c */


struct chanusr *makechanusr (char *userid, int access);

struct chanusr *readchanusr (char *channel, char *userid);

int     writechanusr (char *channel, struct chanusr *wusr);

void    chanusrflags (char *userid, char *channel, int flagson, int flagsoff);



/* invitations.c */

void    invite (char *s);

void    uninvite (char *s);

void    invitero (char *s);


/* chat.c */

void    chat (char *s);

void    originatechat (char *userid);

void    startchat ();

void    finishchat ();


/* actions.c */

void    initactions ();

int     handleaction (char *inp_buffer);

void    actionctl (char *inp_buffer);


/* substvars.c */

void    initvars ();


/* plugins.c */

void    initplugins ();

void    listplugins ();

int     handleplugins (char *s);


#endif


/* End of File */
