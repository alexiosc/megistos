/*****************************************************************************\
 **                                                                         **
 **  FILE:     metabbs-server.h                                             **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Function interface.                                          **
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
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/22 17:23:36  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  2000/01/23 20:46:33  alexios
 * Initial revision
 *
 *
 */



/*#define DEBUG 1*/



/* This is almost certainly not allocated. The Assigned Numbers RFC
   certainly doesn't list it as taken. */

#define METABBS_PORT 33333


extern char *rcs_ver;
extern char host_name[];
extern int locksocket;
extern struct sockaddr_in name;
extern int bbsuid, bbsgid;
extern int under_inetd;
extern char tty[32];


void    mainloop ();




/* Result codes */


/* Information              (2xx) */
/* Requests from the client (3xx) */
/* Errors                   (4xx) */

#define RET_INF_HELLO    201	/* Welcome message(s) */
#define RET_INF_LOGGEDIN 202	/* Client is now logged in */
#define RET_INF_HELP     280	/* Help */
#define RET_INF_MISC     290	/* Miscellaneous information */
#define RET_INF_GOODBYE  299	/* Disconnecting */

#define RET_ASK_LOGIN    301	/* Asking for login */
#define RET_ASK_PASSWORD 302	/* Asking for password */
#define RET_ASK_COMMAND  303	/* Asking for command */

#define RET_ERR_LOGIN    501	/* Login/password incorrect */
#define RET_ERR_COMMAND  502	/* Unknown command */
#define RET_ERR_LINEDOWN 503	/* This line not available */
#define RET_ERR_TOOMANY  504	/* System too busy */



/* End of File */
