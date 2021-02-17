/*****************************************************************************\
 **                                                                         **
 **  FILE:     metabbs.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Interface to the various MetaBBS functions and structures.   **
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
 * $Id: metabbs.h,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: metabbs.h,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1999/07/28 23:16:48  alexios
 * Added support for distributed (networked) clubs.
 *
 * Revision 1.0  1999/07/18 22:05:10  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id: metabbs.h,v 2.0 2004/09/13 19:44:53 alexios Exp $"
#endif



#ifndef __METABBS_H
#define __METABBS_H



#define SFL_NON_MEGISTOS    0x0001
#define SFL_DONT_DISCONNECT 0x0002



/* main.c */

extern SVCXPRT                         * server;



/* register.c */

extern struct registration_package_t   * registered_systems;
extern struct registration_package_t   * this_system;
extern int                               num_systems;


extern int     find_system(char *codename);
extern char  * my_hostname(void);
extern int     make_space();


/* request_info.c */

int match_acl(char *acl, struct sockaddr_in *client, char *codename);


/* distclub.c */

char *apply_prefix(char *fname);
int   getclubaccess(struct sockaddr_in *caller, char *codename);
int   loadclubhdr(char *club);


#endif /* __METABBS_H */
