/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsgetty.h                                                   **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  Interface to everything else in bbsgetty.                    **
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
\*****************************************************************************/


/*
 * $Id: bbsgetty.h,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: bbsgetty.h,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/22 18:19:06  alexios
 * Added more Bxxx bps control bits for those kernels that support
 * them. Values up to 4 Mbps (on FIR ports) are supported. No-one's ever
 * going to use them, but who cares?
 *
 * Revision 1.4  2003/12/22 17:23:37  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  1999/07/18 21:54:26  alexios
 * Added support for the pre/postconnect fields.
 *
 * Revision 1.1  1998/12/27 16:15:40  alexios
 * Changed connect to connectstr so as to disambiguate the
 * connect() system call (debugging this was a pain).
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


#ifndef __BBSGETTY_H
#define __BBSGETTY_H


#define WANT_TERMIOS_H 1
#include <megistos/bbsinclude.h>


/* UUCP tty lock */

#define UUCPLOCK "/var/spool/uucp/LCK..%s"


/* The default connect string */
#define DEF_CONNECT "CONNECT\\s\\A\r\n"



/* debug levels */

#define D_OPT   0x01		/* option settings */
#define D_DEF   0x02		/* defaults file processing */
#define D_CHAT  0x04		/* expect/send debugging */
#define D_INIT  0x08		/* line initialization (INIT) */
#define D_GTAB  0x10		/* gettydefs-like LINETYPE processing */
#define D_GETL  0x20		/* get login name routine */
#define D_RUN   0x40		/* other runtime diagnostics */
#define D_LOCK  0x80		/* locking-related messages */


/* default EXPECT timeout */

#define EXPFAIL 30


/* Speed table for modems. Caution: this is UGLY */

struct speedtab {
	unsigned cbaud;		/* Baud rate flag */
	int     nspeed;		/* Speed in numeric format */
	char   *speed;		/* Speed in string format */
};

#ifdef OPENTTY_C
static struct speedtab speedtab[] = {
#ifdef B50
	{B50, 50, "50"},
#endif
#ifdef B75
	{B75, 75, "75"},
#endif
#ifdef B110
	{B110, 110, "110"},
#endif
#ifdef B134
	{B134, 134, "134"},
#endif
#ifdef B150
	{B150, 150, "150"},
#endif
#ifdef B200
	{B200, 200, "200"},
#endif
	{B300, 300, "300"},
	{B600, 600, "600"},
	{B1200, 1200, "1200"},
	{B1800, 1800, "1800"},
	{B2400, 2400, "2400"},
	{B4800, 4800, "4800"},
	{B9600, 9600, "9600"},

#ifdef  B19200
	{B19200, 19200, "19200"},
#endif
#ifdef  B38400
	{B38400, 38400, "38400"},
#endif
#ifdef  B57600
	{B57600, 57600, "57600"},
#endif
#ifdef  B115200
	{B115200, 115200, "115200"},
#endif
#ifdef  B230400
	{B230400, 230400, "230400"},
#endif
#ifdef  B460800
	{B460800, 460800, "460800"},
#endif

#ifdef  B500000
	{B500000, 500000, "500000"},
#endif

#ifdef  B576000
	{B576000, 576000, "576000"},
#endif

#ifdef  B921600
	{B921600, 921600, "921600"},
#endif

#ifdef  B1000000
	{B1000000, 1000000, "1000000"},
#endif

#ifdef  B1152000
	{B1152000, 1152000, "1152000"},
#endif

#ifdef  B1500000
	{B1500000, 1500000, "1500000"},
#endif

#ifdef  B2000000
	{B2000000, 2000000, "2000000"},
#endif

#ifdef  B2500000
	{B2500000, 2500000, "2500000"},
#endif

#ifdef  B3000000
	{B3000000, 3000000, "3000000"},
#endif

#ifdef  B3500000
	{B3500000, 3500000, "3500000"},
#endif

#ifdef  B4000000
	{B4000000, 4000000, "4000000"},
#endif

	{0, 0, ""}
};
#endif				/* OPENTTY_C */



/* Variables */

extern char autorate[256];
extern char device[256];
extern char devname[256];
extern char lock[256];
extern char altlock[256];
extern char term[256];
extern char speed[256];

extern char *progname;
extern char *waitfor;
extern char *connectstr;
extern char *defname;
extern char *initstr;
extern char *busyout;
extern char *offline;
extern char *initial;
extern char *final;
extern char *preconnect;
extern char *postconnect;

extern int autobaud;
extern int debug;
extern int bbsgid;
extern int bbsuid;
extern int nohangup;
extern int delay;
extern int waitchar;
extern int lockedbaud;
extern int reportedlinespeed;
extern int linestate;
extern int localline;
extern int chanidx;

extern struct termios itermios;	/* Pre-connection termio flags */
extern struct termios ftermios;	/* Post-connection termio flags */



/* init.c */

void    init (int argc, char **argv);


/* debug.c */


void    initdebug ();

void    setdebuglevel (int i);

void    _debug (int level, char *file, int line, char *format, ...);

#define debug(l,f...) _debug(l,__FILE__,__LINE__,##f)


/* setdefaults.c */

void    parsefile (char *suffix);

void    validate ();

void    setdefaults (int argc, char **argv);


/* initline.c */

void    initline ();


/* uucplocks.c */

void    waituucplocks ();
void    watchuucplocks ();
int     checkuucplock (char *name);
void    lockline ();
void    killminder ();


/* opentty.c */

void    opentty ();


/* gettydefs.c */

void    parselinetype ();
void    settermios (struct termios *termios, int state);


/* misc.c */

void    readlinestatus ();
void    writelinestatus (int result);
void    idler ();
void    execute_as_mortal (char *command);


/* chat.c */

int     chat (char *s);
int     expect (char *s);


#endif


/* End of File */
