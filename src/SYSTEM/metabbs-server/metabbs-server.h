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
 * Revision 1.1  2001/04/16 15:01:01  alexios
 * Initial revision
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


extern char *              rcs_ver;
extern char                host_name[];
extern int                 locksocket;
extern struct sockaddr_in  name;
extern int                 bbsuid,bbsgid;
extern int                 under_inetd;


void handleconnection (int fd);




/* Result codes */


/* Information              (2xx) */
/* Requests from the client (3xx) */
/* Errors                   (4xx) */

#define RET_INF_HELLO    201	/* Welcome message(s) */
#define RET_INF_LOGGEDIN 202	/* Client is now logged in */
#define RET_INF_GOODBYE  299	/* Disconnecting */

#define RET_ASK_LOGIN    301	/* Asking for login ("hostname.fqdn/bbscode") */
#define RET_ASK_PASSWORD 302	/* Asking for password */

#define RET_ERR_LOGIN    501	/* Login/password incorrect */
