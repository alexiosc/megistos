/*****************************************************************************\
 **                                                                         **
 **  FILE:     security.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  Security-related functions                                   **
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
 * Revision 1.1  2001/04/16 14:51:07  alexios
 * Initial revision
 *
 * Revision 1.0  1998/12/27 14:31:03  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif

#include <bbsinclude.h>
#include "useracc.h"
#include "config.h"
#include "miscfx.h"



int
hassysaxs(useracc *user,int index)
{
  if(index<0 || index>(sizeof(user->sysaxs)*32))return 0;
  return(user->sysaxs[index/32] & (1<<(index%32)))!=0;
}


void
makekey(long *userflags, long *classflags, long *combo)
{
  int i;
  for(i=0;i<KEYLENGTH;i++)combo[i]=userflags[i]|classflags[i];
}


int
keyhasflag(long *keys,int key)
{
  if(!key) return 1;
  if(key<0 || key>(32*KEYLENGTH)) return 0;
  key--;
  return(keys[key/32]&(1<<(key%32)))!=0;
}


int haskey(useracc *user,int key)
{
  long combo[KEYLENGTH];
  classrec *class=findclass(user->curclss);

  if(!key)return 1;
  if(key==(32*KEYLENGTH+1))return(sameas(user->userid,SYSOP));
  if (hassysaxs(user,USY_MASTERKEY))return 1;
  makekey(user->keys,class->keys,combo);
  return(keyhasflag(combo,key));
}


void setkeyflag(long *keys, int key, int set)
{
  if(key<1 || key>(32*KEYLENGTH))return;
  key--;
  if(set) keys[key/32]|=(1<<(key%32));
  else keys[key/32]&=~(1<<(key%32));
}
