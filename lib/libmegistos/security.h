/*****************************************************************************\
 **                                                                         **
 **  FILE:     security.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, December 98                                               **
 **  PURPOSE:  Interface to security.c                                      **
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
 * Revision 1.1  2001/04/16 14:48:56  alexios
 * Initial revision
 *
 * Revision 1.0  1998/12/27 15:19:02  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef SECURITY_H
#define SECURITY_H


int hassysaxs(useracc *user,int index);

void makekey(long *userflags, long *classflags, long *combo);

int keyhasflag(long *keys,int key);

int haskey(useracc *user,int key);

void setkeyflag(long *keys, int key, int set);


#endif SECURITY_H
