/*****************************************************************************\
 **                                                                         **
 **  FILE:     menuman.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Define the page structures used by the menuman               **
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
 * Revision 1.1  2001/04/16 14:48:54  alexios
 * Initial revision
 *
 * Revision 0.2  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef MENUMAN_H
#define MENUMAN_H

#include "config.h"

#define PAGENAMELEN   16
#define PAGEDESCRLEN  44
#define MENUOPTNUM    64
#define FNAMELEN      64
#define INPUTSTRLEN   192
#define RUNSTRLEN     256

#define PAGETYPE_MENU 'M'
#define PAGETYPE_FILE 'F'
#define PAGETYPE_EXEC 'E'
#define PAGETYPE_RUN  'R'

#define DEFAULTCCR (-1<<30)

struct menuoption {
  char opt;
  char name[PAGENAMELEN];
};

struct menupage {
  char              name  [PAGENAMELEN];
  char              prev  [PAGENAMELEN];
  char              descr [NUMLANGUAGES] [PAGEDESCRLEN];
  char              type;
  int               creds;
  int               key;
  char              class [10];
  int               flags;
  char              fname [FNAMELEN];
  struct menuoption opts [MENUOPTNUM];
};

struct filepage {
  char              name  [PAGENAMELEN];
  char              prev  [PAGENAMELEN];
  char              descr [NUMLANGUAGES] [PAGEDESCRLEN];
  char              type;
  int               creds;
  int               key;
  char              class [10];
  int               flags;
  char              fname [FNAMELEN];
};
  
struct execpage {
  char              name  [PAGENAMELEN];
  char              prev  [PAGENAMELEN];
  char              descr [NUMLANGUAGES] [PAGEDESCRLEN];
  char              type;
  int               creds;
  int               key;
  char              class [10];
  int               flags;
  char              fname [FNAMELEN];
  char              input [INPUTSTRLEN];
};

struct runpage {
  char              name  [PAGENAMELEN];
  char              prev  [PAGENAMELEN];
  char              descr [NUMLANGUAGES] [PAGEDESCRLEN];
  char              type;
  int               creds;
  int               key;
  char              class [10];
  int               flags;
  char              command [RUNSTRLEN];
};

union menumanpage {
  struct menupage m;
  struct filepage f;
  struct execpage e;
  struct runpage  r;
};


#define MPF_HIDDEN  0x0001
#define MPF_INHIBIT 0x0002


#endif /* MENUMAN_H */
