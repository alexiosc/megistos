/*****************************************************************************\
 **                                                                         **
 **  FILE:     plugins.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 0.5                                    **
 **  PURPOSE:  Teleconferences, header file defining plug-in data structs.  **
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
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:39:05  alexios
 * Adjusted #includes. Removed extraneous rcsinfo. Renamed to
 * teleconplugins.h from plugins.h
 *
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef _TELECONPLUGINS_H
#define _TELECONPLUGINS_H


struct plugin {
	char    keyword[16];
	char    exec[128];
	int     key;
	char    descr[ML][64];
};


#define PLUGINQ TELEDIR"/queue-%s-%s"
#define LCKPIN  "LCK..%s.%s"


struct pluginmsg {
	long    mtype;
	char    userid[24];
	char    text[2048];
};

#define SIZE(s) (24*sizeof(char)+strlen(s)+1)


#define MTYPE_COMMAND 1




#ifdef __TELEPLUGIN__

extern char *keyword, *channel, *userid;
extern int qid;

void    initplugin (int argc, char **argv);

void    doneplugin ();

void    becomeserver ();

void    doneserver ();


#endif				/* __TELEPLUGIN__ */





#ifdef __MKPLUGIN__

#define CODE_PLUGIN    1
#define CODE_EXEC      2
#define CODE_KEY       3
#define CODE_DESCR     4


struct keyword {
	char    keyword[12];
	int     code;
} keywords[] = {
	{
	"descr", CODE_DESCR}, {
	"exec", CODE_EXEC}, {
	"key", CODE_KEY}, {
	"plugin", CODE_PLUGIN}, {
"", -1}};


#define STRING(s) (s?s:"")


#endif				/* __MKPLUGIN__ */


#endif				/* _PLUGINS_H */


/* End of File */
