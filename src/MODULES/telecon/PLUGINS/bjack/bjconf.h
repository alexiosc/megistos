/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: bjconf.h                                                         **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: configuration header file                                     **
 **  NOTES:                                                                 **
 **                                                                         **
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
 * Revision 1.1  2001/04/16 15:00:04  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:51  alexios
 * Initial checkin.
 *
 * Revision 0.5  1999/10/17 09:18:30  valis
 * *** empty log message ***
 *
 * Revision 0.4  1999/09/20 21:43:19  valis
 * *** empty log message ***
 *
 * Revision 0.3  1999/09/04 13:57:57  valis
 * first stable release, tidy up source code,
 * references to LINUX_CONSOLE removed
 *
 * Revision 0.2  1999/09/01 22:18:56  valis
 * POST_LOG introduced
 *
 * Revision 0.1  1999/08/29 23:54:05  valis
 * Initial revision. Conditional defines moved from bj.h here.
 * Added LOGDIR and LOGFILE
 *
 */


#ifndef __BJCONF_H
#define __BJCONF_H
 
 
/* define if under development, enables special debugging and other options */
#define DEVEL


/* define if you want debugging information */
#define DEBUG


/* define if you want cheat commands to be active */
//#define CHEATS


/* define this to simulate credit posting.  ****USE WITH CARE**** */
/* otherwise, you are playing with users credits !!!              */
#define FAKE_POSTING


/****** LOG defines ******/
/* enable some loggings for debugging only */
//#define DEBUG_LOG

/* define to have the function name in the log lines */
//#define VERBOSE_LOG

/* define to log commands */
#define COMMAND_LOG

/* define to log forced actions (fold, stay, off) */
#define FORCE_LOG

/* define to log credit postings */
#define POST_LOG

/*************************/


/* define if we use bbs prompt subsystem */
#define BBSPROMPTS


/**********************************************************************************/
/* Define the right BBS program you use. So to enable correct code to be compiled */
/* Do not define more than one at the same time                                   */
/**********************************************************************************/
/* these will be defined in Makefile */
//#define MEGISTOS_BBS


/* define LOG directory */
#ifndef LOGDIR
#define LOGDIR		"/tmp"
#endif


#endif	/* __BJCONF_H */

