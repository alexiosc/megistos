/*****************************************************************************\
 **                                                                         **
 **  FILE:     club_info.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1999.                                                **
 **  PURPOSE:  Show information on a remote club.                           **
 **  NOTES:    See syntax() function for the syntax of this program.        **
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
 * Revision 1.1  2001/04/16 15:02:53  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:14:11  alexios
 * Initial checkin.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "netclub.h"
#include "metaservices.h"



void
club_info(char *fname, char *sysname, char *clubname)
{
  CLIENT                        *cl=NULL;
  struct club_header_request_t   bbs;
  struct club_header_t          *hdr;
  club_header                   *result;
  char                           tmp[256], *cp;
    

  /* Separate the hostname from the codename */

  strcpy(tmp,sysname);
  if((cp=strchr(tmp,'/'))==NULL){
    fprintf(stderr,"System \"%s\" has invalid name!\n",sysname);
    return;
  }

  *cp++=0;			/* tmp=hostname, cp=codename */


  /* Make the connection */
  
  if(debug)fprintf(stderr,"Creating RPC client for host %s\n",tmp);
  if((cl=clnt_create(tmp,METABBS_PROG,METABBS_VERS,"tcp"))==NULL){
    clnt_pcreateerror(tmp);
    return;
  }


  /* Call the procedure */
  
  strcpy(bbs.codename,bbscode);
  strcpy(bbs.targetname,cp);
  strcpy(bbs.club,clubname);
  if(debug)fprintf(stderr,"Sending club header request to %s/%s\n",tmp,cp);
  if((result=distclub_request_header_1(&bbs,cl))==NULL){
    clnt_perror(cl,tmp);
    clnt_destroy(cl);
    fprintf(stderr,"RPC request wasn't answered by %s",tmp);
    return;
  }
  clnt_destroy(cl);

  if(debug||(result->result_code!=0)){
    int i=result->result_code;
    fprintf(stderr,"Server returns result %d (%s)\n",i,
	    i>0?strerror(i):clr_errorlist[-i]);
  }
  if(result->result_code)return;

  hdr=&(result->club_header_u.club);
  printf("System:       %s/%s\n",tmp,cp);
  printf("Club:         %s\n",hdr->club);
  printf("Description:  %s\n",hdr->descr);
  printf("ClubOp:       %s\n",hdr->clubop);
  printf("Created:      %s %s\n",strdate(hdr->crdate),strtime(hdr->crtime,1));
  printf("Messages:     %d\n",hdr->nmsgs);
  printf("Periodicals:  %d\n",hdr->nper);
  printf("Bulletins:    %d\n",hdr->nblts);
  printf("Files:        %d\n",hdr->nfiles);
  printf("Unapproved:   %d\n",hdr->nfunapp);
  printf("Msg lifetime: %d day(s)\n",hdr->msglife);

  printf("\nClub banner follows:\n");
  printf("-------------------------------------------------------------------------------\n");
  printf("%s\e[0m",hdr->banner);
  printf("-------------------------------------------------------------------------------\n\n");

  xdr_free((xdrproc_t)xdr_club_header,(caddr_t)result);
}
