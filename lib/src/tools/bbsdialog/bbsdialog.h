/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsdialog.h                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 94                                               **
 **  PURPOSE:  Header file for the dialog/form manager.                     **
 **  NOTES:    Internal use only.                                           **
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
 * Revision 1.5  2003/12/24 18:31:19  alexios
 * Removed detrimental rcsinfo declaration.
 *
 * Revision 1.4  2003/12/23 23:20:24  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/07/24 10:29:41  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:02:58  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:35:04  alexios
 * Added the fieldhelp() function to display help on visual
 * dialog fields.
 *
 * Revision 0.1  1997/08/28 11:21:38  alexios
 * First registered revision. Adequate.
 *
 *
 */


struct stringfield {
	char    type;
	long    flags;
	char   *template;
	int     color, x, y;
	int     max, shown, cp;
	unsigned char *data;
};


struct numfield {
	char    type;
	long    flags;
	char   *template;
	int     color, x, y;
	int     min, max, shown, cp;
	unsigned char *data;
};


struct list {
	char    type;
	long    flags;
	char   *template;
	int     color, x, y, size;
	unsigned char *options;
	unsigned char *data;
};


struct toggle {
	char    type;
	long    flags;
	char   *template;
	int     color, x, y;
	unsigned char on, off;
	int     data;
};


struct button {
	char    type;
	long    flags;
	char   *template;
	int     color, x, y, size;
	unsigned char *label, key;
};


union object {
	struct stringfield s;
	struct numfield n;
	struct list l;
	struct toggle t;
	struct button b;
};


#define OBJ_STRING  's'
#define OBJ_NUM     'n'
#define OBJ_LIST    'l'
#define OBJ_TOGGLE  't'
#define OBJ_BUTTON  'b'

#define VISUAL 1
#define LINEAR 0


#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


#define ISPRINT(c) (((c)>=32||(c)<0))


extern union object *object;
extern int numobjects;
extern promptblock_t *msg;
extern promptblock_t *templates;
extern int mode;
extern char *mbkname;
extern int vtnum;
extern int ltnum;
extern char *dfname;

void    runvisual ();

void    visualhelp ();

void    fieldhelp (int field);

void    runlinear ();

void    endsession (char *event);


/* End of File */
