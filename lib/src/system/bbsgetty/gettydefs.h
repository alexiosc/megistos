/*****************************************************************************\
 **                                                                         **
 **  FILE:     gettydefs.h                                                  **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  handle /etc/gettydefs-like LINETYPE declarations             ** 
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
 * $Id$
 *
 * $Log$
 * Revision 1.6  2003/12/23 08:18:44  alexios
 * Removed rcsinfo from header file.
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
 * Slight changes to make the #definitions better behaved.
 *
 * Revision 1.1  1998/12/27 16:15:40  alexios
 * No changes effectively.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


/* Define the default line discipline, unless already defined */

#ifndef	LDISC0
#define	LDISC0	0		/* Default line discipline */
#endif



/* Default communication speed */

#define SSPEED  (B9600)


/* Default bit width */

#define DEF_CFL (CS8)


/* Linux default control chars etc */

#ifndef CNUL
#define CNUL    0
#endif
#ifndef CERASE
#define CERASE  127		/* ^? */
#endif
#ifndef CKILL
#define CKILL   025		/* ^U */
#endif
#ifndef CINTR
#define CINTR   03		/* ^C */
#endif
#ifndef CQUIT
#define CQUIT   034		/* ^\ */
#endif
#ifndef CSTART
#define CSTART  021		/* ^Q */
#endif
#ifndef CSTOP
#define CSTOP   023		/* ^S */
#endif
#ifndef CEOF
#define CEOF    04		/* ^D */
#endif
#ifndef CMIN
#define CMIN    06		/* satisfy read at 6 chars */
#endif
#ifndef CTIME
#define CTIME   01		/* .1 sec inter-character timer */
#endif



/* Table for the various flags */

struct symtab {
	char   *name;		/* Symbolic name */
	unsigned long value;	/* Actual value */
};



/* Input mode flags */

struct symtab imodes[] = {
	{"IGNBRK", IGNBRK},
	{"BRKINT", BRKINT},
	{"IGNPAR", IGNPAR},
	{"PARMRK", PARMRK},
	{"INPCK", INPCK},
	{"ISTRIP", ISTRIP},
	{"INLCR", INLCR},
	{"IGNCR", IGNCR},
	{"ICRNL", ICRNL},
	{"IUCLC", IUCLC},
	{"IXON", IXON},
	{"IXANY", IXANY},
	{"IXOFF", IXOFF},
	{"IMAXBEL", IMAXBEL},
	{NULL, 0}
};



/* Output mode flags */

struct symtab omodes[] = {
	{"OPOST", OPOST},
	{"OLCUC", OLCUC},
	{"ONLCR", ONLCR},
	{"OCRNL", OCRNL},
	{"ONOCR", ONOCR},
	{"ONLRET", ONLRET},
	{"OFILL", OFILL},
	{"OFDEL", OFDEL},
	{"NLDLY", NLDLY},
	{"NL0", NL0},
	{"NL1", NL1},
	{"CRDLY", CRDLY},
	{"CR0", CR0},
	{"CR1", CR1},
	{"CR2", CR2},
	{"CR3", CR3},
	{"TABDLY", TABDLY},
	{"TAB0", TAB0},
	{"TAB1", TAB1},
	{"TAB2", TAB2},
	{"TAB3", TAB3},
	{"BSDLY", BSDLY},
	{"BS0", BS0},
	{"BS1", BS1},
	{"VTDLY", VTDLY},
	{"VT0", VT0},
	{"VT1", VT1},
	{"FFDLY", FFDLY},
	{"FF0", FF0},
	{"FF1", FF1},
	{NULL, 0}
};



/* Communication rates etc. Ye gawds, what ugly code */

struct symtab cmodes[] = {
#ifdef B0
	{"B0", B0},
#endif
#ifdef B50
	{"B50", B50},
#endif
#ifdef B75
	{"B75", B75},
#endif
#ifdef B110
	{"B110", B110},
#endif
#ifdef B134
	{"B134", B134},
#endif
#ifdef B150
	{"B150", B150},
#endif
#ifdef B200
	{"B200", B200},
#endif
	{"B300", B300},
	{"B600", B600},
	{"B1200", B1200},
	{"B1800", B1800},
	{"B2400", B2400},
	{"B4800", B4800},
	{"B9600", B9600},
#ifdef	B19200
	{"B19200", B19200},
#endif
#ifdef	B38400
	{"B38400", B38400},
#endif
#ifdef	B57600
	{"B57600", B57600},
#endif
#ifdef	B115200
	{"B115200", B115200},
#endif
#ifdef	B230400
	{"B230400", B230400},
#endif
#ifdef	B460800
	{"B460800", B460800},
#endif
#ifdef  B500000
	{"B500000", B500000},
#endif
#ifdef  B576000
	{"B576000", B576000},
#endif
#ifdef  B921600
	{"B921600", B921600},
#endif
#ifdef  B1000000
	{"B1000000", B1000000},
#endif
#ifdef  B1152000
	{"B1152000", B1152000},
#endif
#ifdef  B1500000
	{"B1500000", B1500000},
#endif
#ifdef  B2000000
	{"B2000000", B2000000},
#endif
#ifdef  B2500000
	{"B2500000", B2500000},
#endif
#ifdef  B3000000
	{"B3000000", B3000000},
#endif
#ifdef  B3500000
	{"B3500000", B3500000},
#endif
#ifdef  B4000000
	{"B4000000", B4000000},
#endif

	{"EXTA", EXTA},
	{"EXTB", EXTB},
	{"CS5", CS5},
	{"CS6", CS6},
	{"CS7", CS7},
	{"CS8", CS8},
	{"CSTOPB", CSTOPB},
	{"CREAD", CREAD},
	{"PARENB", PARENB},
	{"PARODD", PARODD},
	{"HUPCL", HUPCL},
	{"CLOCAL", CLOCAL},
#ifdef	LOBLK
	{"LOBLK", LOBLK},
#endif
	{"CRTSCTS", CRTSCTS},
	{NULL, 0},
};



/* lmodes */

struct symtab lmodes[] = {
	{"ISIG", ISIG},
	{"ICANON", ICANON},
	{"XCASE", XCASE},
	{"ECHO", ECHO},
	{"ECHOE", ECHOE},
	{"ECHOK", ECHOK},
	{"ECHONL", ECHONL},
	{"NOFLSH", NOFLSH},
	{"TOSTOP", TOSTOP},
	{"ECHOCTL", ECHOCTL},
	{"ECHOPRT", ECHOPRT},
	{"ECHOKE", ECHOKE},
	{"FLUSHO", FLUSHO},
	{"PENDIN", PENDIN},
	{"IEXTEN", IEXTEN},
#ifdef XCLUDE
	{"XCLUDE", XCLUDE},
#endif
	{NULL, 0}
};



/* Line disciplines (only one available, of course */

struct symtab discs[] = {
	{"LDISC0", LDISC0},
	{NULL, 0}
};



/* Default termios value */

#define DEFAULT_ITERMIOS { 0, 0, (SSPEED|CSANE), 0, 0, CC_SANE }
#define DEFAULT_FTERMIOS { ISANE, OSANE, (SSPEED|CSANE), LSANE, LDISC0, CC_SANE }



#define	VALUE(cptr)	((cptr == (char *) NULL) ? "NULL" : cptr)



/* Sane conditions */

#define	ISANE (BRKINT|IGNPAR|ISTRIP|ICRNL|IXON|IXANY)
#define	OSANE (OPOST|ONLCR)
#define	CSANE (DEF_CFL|CREAD|HUPCL)
#define	LSANE (ISIG|ICANON|ECHO|ECHOE|ECHOK)

#define	CC_SANE	{ CINTR, CQUIT, CERASE, CKILL, CEOF, CNUL, CNUL, CNUL }



/* End of File */
