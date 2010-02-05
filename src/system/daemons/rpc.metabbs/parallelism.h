/*****************************************************************************\
 **                                                                         **
 **  FILE:     parallelism.h                                                **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Parallelise the server by kludging it to hell and back.      **
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
 * $Id: parallelism.h,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: parallelism.h,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/07/28 23:15:45  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id: parallelism.h,v 2.0 2004/09/13 19:44:53 alexios Exp $"
#endif



#ifndef __PARALLELISM_H
#define __PARALLELISM_H


#include "errno.h"


#ifdef DEBUG
#define __DEBUG_PREAMBLE__ \
fprintf(stderr,"FORKING TO CALL PROCEDURE: NEW PID=%d\n",(int)getpid());
#else
#define __DEBUG_PREAMBLE__
#endif



/* For compatibility with older rpcgens */

#define xdr_result _xdr_result
#define xdr_argument _xdr_argument



#define __CALL_PREAMBLE__ \
if(rqstp->rq_proc>10000){ \
  int pid=fork(); \
  if(pid>0) return; \
  else if(pid<0) { \
    int i=errno; \
    fprintf(stderr,"Unable to fork: %s\n",strerror(i)); \
  } \
  __DEBUG_PREAMBLE__ \
}



#define __CALL_POSTAMBLE__ \
if(rqstp->rq_proc>10000){ \
  if (result != NULL && !svc_sendreply(transp, _xdr_result, result)) { \
    svcerr_systemerr (transp); \
  } \
  if (!svc_freeargs (transp, _xdr_argument, (caddr_t) &argument)) { \
    _msgout ("unable to free arguments"); \
    exit (1); \
  } \
  exit(0); \
}


#endif /* __PARALLELISM_H */
