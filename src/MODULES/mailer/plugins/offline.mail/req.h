/*****************************************************************************\
 **                                                                         **
 **  FILE:     req.h                                                        **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Request definitions, to be included by other plugins.        **
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
 * Revision 1.1  2001/04/16 14:57:52  alexios
 * Initial revision
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define RQF_POSTPONE 0x01
#define RQF_ATT      0x02
#define RQF_INVIS    0x04
#define RQF_CTLMSG   0x08
#define RQF_BULLETIN 0x10

#define RQP_POSTPONE  1
#define RQP_ATT       2
#define RQP_ATTREQ    3
#define RQP_OTHER     4
#define RQP_CTLMSG   99

void openreqdb();

int mkrequest(char *area, char *dosfname, char *fname,
	      int msgno, int priority, int flags);

int getfirstreq(struct reqidx *idx);

int getnextreq(struct reqidx *idx);

int rmrequest(struct reqidx *idx);

int updrequest(struct reqidx *idx);

