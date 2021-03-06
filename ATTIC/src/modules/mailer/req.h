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
 * $Id: req.h,v 2.0 2004/09/13 19:44:52 alexios Exp $
 *
 * $Log: req.h,v $
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.1  2004/05/03 06:00:48  alexios
 * Reimported (the original file's CVS entry was lost somehow).
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: req.h,v 2.0 2004/09/13 19:44:52 alexios Exp $";


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

void    openreqdb ();

int     mkrequest (char *area, char *dosfname, char *fname,
		   int msgno, int priority, int flags);

int     getfirstreq (struct reqidx *idx);

int     getnextreq (struct reqidx *idx);

int     rmrequest (struct reqidx *idx);

int     updrequest (struct reqidx *idx);



/* End of File */
