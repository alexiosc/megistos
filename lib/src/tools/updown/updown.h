/*****************************************************************************\
 **                                                                         **
 **  FILE:     updown.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 94, Version 0.5 alpha                           **
 **  PURPOSE:  Definitions for updown.c                                     **
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
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 22:09:33  alexios
 * Added a flag to signify file transfer success.
 *
 * Revision 0.4  1998/11/30 22:06:09  alexios
 * Removed useless declarations. Added declarations for the
 * PRF_BINARY option in the protocols file.
 *
 * Revision 0.3  1998/07/24 10:31:31  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:18:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:25:42  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




struct directive {
	char    name[10];
	int     code;
};


struct viewer {
	char    string[80];
	char    type[80];
	char    command[256];
};


#define XFF_KILLED   0x00000001
#define XFF_TAGGED   0x00000002
#define XFF_CHECK    0x00000004
#define XFF_AUDIT    0x00000008
#define XFF_AUDITED  0x00000010
#define XFF_SUCCESS  0x00000020


struct protocol {
	char    name[40];
	char    select[8];
	char    command[80];
	char    stopkey[16];
	long    flags;
};


#define PRF_BATCH  0x0001
#define PRF_UPLOAD 0x0002
#define PRF_NEEDN  0x0004
#define PRF_VIEWER 0x0008
#define PRF_LINK   0x0010
#define PRF_BINARY 0x0020


extern promptblock_t *msg;


extern int peffic;
extern char *vprsel;
extern int dissec;
extern int lnkkey;
extern char *lnksel;
extern int refnd;
extern int refper;

extern struct protocol *protocols;
extern int numprotocols;
extern struct viewer *viewers;
extern int numviewers;
extern char *xferlistname;
extern xfer_item_t *xferlist;
extern int totalitems;
extern int numitems;
extern char *taglistname;
extern int numtagged;
extern int xfertagged;
extern int taggedsize;
extern int autodis;
extern int logout;

extern char filetype[256];
extern long filesize;
extern long xfertime;
extern int firstentry;


#define NUMFILES   (xfertagged?(numitems+numtagged):numitems)
#define MAXRECURSE 10
#define SYMLINKTO  "symbolic link to "

void    autodisconnect ();

void    readprotocols ();
void    readviewers ();
void    readtransferlist ();

void    extraprotocols ();
void    getfilesize ();
void    getfiletype ();

void    downloadrun ();
void    getfirstentry ();

void    uploadrun ();


/* End of File */
