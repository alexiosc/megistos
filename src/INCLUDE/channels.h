/*****************************************************************************\
 **                                                                         **
 **  FILE:     channels.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  Interface to channels.c                                      **
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
 * Revision 1.1  2001/04/16 14:48:48  alexios
 * Initial revision
 *
 * Revision 1.1  1999/07/18 21:13:24  alexios
 * Cosmetic changes. Added MetaBBS support.
 *
 * Revision 1.0  1998/12/27 15:19:02  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef CHANNELS_H
#define CHANNELS_H


/* Channel modes */

#define LST_NORMAL   0		/* Normal bahaviour (answers calls, logins) */
#define LST_NOANSWER 1		/* Do not answer incoming calls */
#define LST_BUSYOUT  2		/* Keep the line off-hook so it appears busy */
#define LST_OFFLINE  3		/* Answer calls, say something and hang up */

#define LST_NUMSTATES 4		/* The number of line states available */


/* Channel results */

#define LSR_INIT    0		/* The line is being initialised */
#define LSR_OK      1		/* Line initialised and awaiting connection */
#define LSR_RING    2		/* Incoming modem connection */
#define LSR_ANSWER  3		/* Answering call */
#define LSR_LOGIN   4		/* User is logging in */
#define LSR_USER    5		/* User occupies the channel */
#define LSR_FAIL    6		/* Initialisation failed */
#define LSR_RELOGON 7		/* User is re-logging in. */
#define LSR_LOGOUT  8		/* Session has ended, awaiting new bbsgetty */

#ifdef HAVE_METABBS
#define LSR_METABBS 9		/* The user is using the MetaBBS client */

#define LSR_NUMRESULTS 10
#else
#define LSR_NUMRESULTS  9
#endif


/* String values for the channel modes: DO NOT CHANGE THESE, unless
   you also change the LST_ and LSR_ defines above to reflect the
   changes! */

#ifdef CHANNELS_C

char *line_states[]={
  "NORMAL",
  "NO-ANSWER",
  "BUSY-OUT",
  "OFF-LINE"
};

char *line_results[]={
  "INIT",
  "OK",
  "RING",
  "ANSWER",
  "LOGIN",
  "USER",
  "FAIL",
  "RELOGON",
  "LOGOUT"
#ifdef HAVE_METABBS
  ,"METABBS"
#endif
};

#else
extern char *line_states[];
extern char *line_results[];
#endif


struct linestatus {
  int  state;			/* The line state (from line_states) */
  int  result;			/* Last result (from line_results) */
  int  baud;			/* The "baud" rate of the line */

#ifndef HAVE_METABBS
  char user[24];		/* The user occupying the line, if any */
#else
  char user[256];		/* MetaBBS uses the user field to store the
                                   remote system the line is connected
                                   to. Hence we need this to be longer. */
#endif
};


int getlinestatus(char *tty, struct linestatus *status);

int setlinestatus(char *tty, struct linestatus *status);

void setlinestate(char *tty, int state);

void setlineresult(char *tty, int result);

void hangup();

int disconnect(char *ttyname);

char *baudstg(int baud);


#endif CHANNELS_H
