/*****************************************************************************\
 **                                                                         **
 **  FILE:     input.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Interface to input.c                                         **
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
 * Revision 0.8  1999/07/28 23:09:07  alexios
 * *** empty log message ***
 *
 * Revision 0.7  1999/07/18 21:13:24  alexios
 * Made inputflags public to allow for user-supplied high
 * level input functions.
 *
 * Revision 0.6  1998/12/27 15:19:19  alexios
 * Moved function declarations from miscfx.h.
 *
 * Revision 0.5  1998/08/14 11:23:21  alexios
 * Added function to set monitor ID (initially channel number,
 * but user's user ID after login).
 *
 * Revision 0.4  1998/07/26 21:17:06  alexios
 * Removed obsoleted extern injothfile.
 *
 * Revision 0.3  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 12:45:25  alexios
 * Added resetblocking() to remember previous states of block-
 * ing/non-blocking and switch between them.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef INPUT_H
#define INPUT_H


#define INF_NORMAL 0x0000
#define INF_HELP   0x0001


extern char input[];                        /* Input buffer, sized MAXINPLEN */
extern char *margv[];               /* Input arguments, no spaces, a la argv */
extern char *nxtcmd;                    /* Next character for command concat */
extern int  margc;                       /* Number of input arguments passed */
extern int  inplen;                                   /* Length of raw input */
extern int  inputflags;           /* Flags used by high level input routines */
extern int  reprompt;            /* Boolean: need reprompting after "injoth" */
extern int  dontinjoth;
extern char del[];
extern volatile struct monitor *monitor;
extern int oldblocking;
extern int newblocking;


void initinput();                                 /* Initialise input system */
void doneinput();                                   /* Shutdown input system */

int  acceptinjoth();           /* Check existence of injoth file and display */
void setmonitorid(char *tty_or_uid);   /* Set tty or username for monitoring */
void monitorinput(char *tty);             /* Write input monitor information */
char *getinput(int maxlen);             /* Call this to receive parsed input */
void inputstring(int maxlen);        /* Input a string of max. length maxlen */
void parsin();                                    /* Break up into arguments */
void clrinp();                                    /* Clear input buffers etc */
void rstrin();                                          /* Restore raw input */
void cancelinput();   /* For use by signal handlers, cancel input and return */

void bgncnc();                                /* Begin command concatenation */
int endcnc();                              /* Is this the end of the string? */
char cncchr();                                         /* Get next character */
int cncint();                              /* Parse an integer, atoi() style */ 
long cnclon();                              /* Parse a longint, atol() style */
char cncyesno();                                             /* Parse yes/no */
char *cncword();                                        /* Get the next word */
char *cncall();                                      /* Gobble rest of input */
char morcnc();             /* Check if there is more, and get next character */
int cnchex();                 /* Parse a hex number and return decimal value */
char *cncnum();                                   /* Return an ASCII decimal */

void setpasswordentry(int n);          /* Make getinput() echo stars if n!=0 */
void setinjoth(int n);             /* Allow or inhibit injection of messages */


/* This one allows getinput to timeout for some reason or other. Not
   recommended as it doesn't fit in with the entire BBS feeling, but there are
   applications (like MUDs or the adventure module) where this is needed.

   Arguments: msec is the number of milliseconds after which to terminate (this
   is accurate to 10 msec, the delay between checks for new keyboard input);
   supply a non-zero intrusive to cause getinput() to terminate even if the
   user has started writing something. The default behaviour (intrusive=0) is
   to only timeout if the user is 100% idle (empty input line). Intrusive mode
   is ugly, as it interrupts the user -- the system should NEVER interrupt the
   user unless there's a good reason.

   Output: upon timeout, global variables inptimeout_msec and
   inptimeout_intrusive are reset to 0. This is the official method of checking
   whether getinput() has timed out. inptimeout_msec is used as a counter by
   inputstring(). This means you have to call setinputtimeout() before every
   call to getinput() that needs a timeout.

*/

void setinputtimeout(int msec, int intrusive);

extern int inptimeout_msecs;
extern int inptimeout_intr;



void nonblocking();
void blocking();
void resetblocking();

void settimeout(int i);
void resetinactivity();

int isX(char *s);


/* Fancy input routines.                                                     */


void setinputflags(int f);

/* getnumber: Prompt msg asking for a number between min and max. Return the */
/*            number in num. If def!=0, there is a default value (prompt     */
/*            def displays it) which is passed in defval. Prompts err if bad */
/*            value entered. Returns 0 if X entered, 1 if the int result is  */
/*            in num.                                                        */

int getnumber(int *num,int msg,int min,int max,int err,int def,int defval);


/* getbool: Works just like getnumber. Prompts msg, asks for Y/N answer,     */
/*          prompts err if bad response, optionally prompts def with a       */
/*          default value (0 or 1) of defval. Returns result in bool, plus   */
/*          1 if boolean value entered, or 0 if X entered.                   */

int getbool(int *retbool,int msg,int err,int def,int defval);

/* getuserid: Same thing! Prompts msg asking for a user ID. If the user does */
/*            not exist (as returned by userexists()), err is prompted (with */
/*            a %s parameter containing the invalid user ID. If def!=0,      */
/*            prompt #def is displayed along with a default value of defval. */
/*            returns result in uid, plus 1 if user ID ok, or 0 if exiting.  */

int getuserid(char *uid,int msg,int err,int def,char *defval,int online);

/* getmenu: Handle a simple menu. Displays a long menu (lmenu) once per      */
/*          session (if showmenu), plus whenever ? is entered. The prompt is */
/*          a short version of the long menu (smenu). Options are single     */
/*          characters contained in opts. In case of error, err is prompted. */
/*          Defaults are handled in the usual way. The selection is returned */
/*          in option[0].                                                    */

int getmenu(char *option,int showmenu,int lmenu,int smenu,int err,char *opts,
	    int def,int defval);


#endif /* INPUT_H */
