/*****************************************************************************\
 **                                                                         **
 **  FILE:     ttynum.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Interface to ttynum.c                                        **
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
 * Revision 0.6  1999/07/18 21:13:24  alexios
 * Added MetaBBS flag to control whether the MetaBBS client
 * should be enabled for a line.
 *
 * Revision 0.5  1998/12/27 15:19:19  alexios
 * Added some comments and the channel file magic number.
 *
 * Revision 0.4  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/03 00:29:40  alexios
 * Added xlation field to struct channeldef to keep the number
 * of the default translation table for a channel. Removed
 * defines for hardwired xlation tables.
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Added a config field to allow for the new handling of bbsgetty
 * configuration.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef TTYNUM_H
#define TTYNUM_H


/* The channel file magic number */

#define CHANNEL_MAGIC "MEGISTOS BINARY CHANNEL FILE\n\n\n"


/* The channel definition */

struct channeldef {
  char          ttyname [16];	/* Name of the TTY, minus "/dev/" */
  char          config  [32];	/* BBSGETTY Config file to load */
  unsigned int  channel;	/* BBS channel number */
  int           key;		/* Key required to login */
  int           lang;		/* Default language for this channel */
  long          flags;		/* Channel flags */
  int           xlation;	/* Default translation mode for the channel */
};


/* Channel flags */

#define TTF_CONSOLE  0x0001	/* Channel is on the system console */
#define TTF_SERIAL   0x0002	/* Channel is a plain serial line */
#define TTF_MODEM    0x0004	/* There's a modem on this channel */
#define TTF_TELNET   0x0008	/* This channel is for telnet connections */
#define TTF_SIGNUPS  0x0010	/* Signups are allowed here */
#define TTF_ASKXLT   0x0100	/* Ask people for translation mode */
#define TTF_ANSI     0x0200	/* ANSI enabled on this channel by default */
#define TTF_ASKANSI  0x0400	/* Ask people whether they need ANSI */

#ifdef HAVE_METABBS
#define TTF_METABBS  0x0800	/* Enable the MetaBBS client for this line */
#endif


#define CHD_MAGIC "CHANDEFS"	/* At offset 0 of the binary channel file */


/* The channels index, mapping ttys to channels */

extern struct channeldef *channels;
extern struct channeldef *lastchandef;
extern int                numchannels;


void initchannels();

int getchannelnum(char *tty);

int getchannelindex(char *tty);

char *getchannelname(int num);

int telnetlinecount();


#endif /* TTYNUM_H */
