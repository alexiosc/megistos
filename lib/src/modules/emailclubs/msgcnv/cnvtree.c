/*****************************************************************************\
 **                                                                         **
 **  FILE:     cnvtree.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 VESIGS database to Megistos format.        **
 **  NOTES:    This is NOT guarranteed to work on anything but MajorBBS     **
 **            version 5.31, for which it was written.                      **
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
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.2  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.1  1998/07/24 10:16:36  alexios
 * Initial revision.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_PWD_H 1
#define WANT_GRP_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include "bbs.h"
#include "email.h"
#include "clubs.h"
#include "../files/cnvutils.h"
#include "mbk_emailclubs.h"


void addmsg(FILE *fp,char *club,int msgno,int fpos,int flen);


struct msgnum {
  unsigned int    majornum;
  char            club[32];
  int             msgno;
  int             fpos;
  int             flen;
  struct msgnum  *lt,*gt;
};



struct msgnum *root=NULL;



static struct msgnum *
mknode(int majornum, char *club, int msgno, int fpos, int flen)
{
  struct msgnum *n=malloc(sizeof(struct msgnum));
  n->majornum=majornum;
  strcpy(n->club,club);
  n->msgno=msgno;
  n->gt=n->lt=NULL;
  n->fpos=fpos;
  n->flen=flen;
  return n;
}



static void
recurse(struct msgnum *node, int majornum, char *club, int msgno,
	int fpos, int flen)
{
  int delta=strcmp(club,node->club);

  if(delta<0){
    if(node->lt!=NULL)recurse(node->lt,majornum,club,msgno,fpos,flen);
    else node->lt=mknode(majornum,club,msgno,fpos,flen);
  } else if(delta>0){
    if(node->gt!=NULL)recurse(node->gt,majornum,club,msgno,fpos,flen);
    else node->gt=mknode(majornum,club,msgno,fpos,flen);
  } else {
    if(majornum<node->majornum){
      if(node->lt!=NULL)recurse(node->lt,majornum,club,msgno,fpos,flen);
      else node->lt=mknode(majornum,club,msgno,fpos,flen);
    } else if(majornum>node->majornum){
      if(node->gt!=NULL)recurse(node->gt,majornum,club,msgno,fpos,flen);
      else node->gt=mknode(majornum,club,msgno,fpos,flen);
    } else {
      fprintf(stderr,"ERROR: Duplicate message #%d! Argh!\n",majornum);
    }
  }
}



void indexmsg(int majornum, char *club, int msgno, int fpos, int flen)
{
  if(root==NULL)root=mknode(majornum,club,msgno,fpos,flen);
  else recurse(root,majornum,club,msgno,fpos,flen);
}



static char *
findrecurse(struct msgnum *node, char *club, int majornum)
{
  static char res[256];
  int delta;

  if(node==NULL)return NULL;

  delta=strcmp(club,node->club);
  if(delta<0)return findrecurse(node->lt,club,majornum);
  if(delta>0)return findrecurse(node->gt,club,majornum);
  if(majornum<node->majornum)return findrecurse(node->lt,club,majornum);
  if(majornum>node->majornum)return findrecurse(node->gt,club,majornum);
  sprintf(res,"%s/%d",node->club,node->msgno);
  return res;
}



char*
findmsg(char *club, int majornum)
{
  return findrecurse(root,club,majornum);
}



static char lastclub[32];
static int  lastno=0;


void inorder(struct msgnum *n,FILE *fp)
{
  if(n==NULL)return;
  inorder(n->lt,fp);
  if(strcmp(lastclub,n->club)){
    if(lastclub[0])printf("Converted %5d message(s) for %s\n",lastno,lastclub);
    lastno=1;
    strcpy(lastclub,n->club);
  }
  else lastno++;
  n->msgno=lastno;
  addmsg(fp,n->club,n->msgno,n->fpos,n->flen);
  inorder(n->gt,fp);
}


void
traverse(FILE *fp)
{
  lastno=0;
  lastclub[0]=0;
  inorder(root,fp);
}
