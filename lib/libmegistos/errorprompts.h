/*****************************************************************************\
 **                                                                         **
 **  FILE:     errorprompts.h                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Define hard-wired user-friendly no-nonsense no-more-hyphens  **
 **            error messages for use with errors.c                         **
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
 * Revision 1.1  2001/04/16 14:48:51  alexios
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



#ifndef ERRORPROMPTS_H
#define ERRORPROMPTS_H


#define ERRORMESSAGE \
	"\033[0;1;31;5m¨¦©¦®ã: \033[0;1;31m" \
	"‹ ¡¨å© £¦ ©­á¢£˜ œ£§æ› ©œ «¤ ¦¢¦¡¢ã¨à© «ª œ¨š˜©å˜ª.\n" \
	"         ˜¨˜¡˜¢¦ç£œ œ¤£œ¨é©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª\n" \
	"         ©¬¤Ÿã¡œª §¦¬ «¦ ›£ ¦ç¨š©˜¤. …«¦ç£œ ©¬šš¤é£ š ˜ «¤\n" \
	"         «˜¢˜ §à¨å˜.\033[0;1m\n\n"

#define FATALMESSAGE \
	"\033[0;1;31;5m¨¦©¦®ã: \033[0;1;31m" \
	"‘¦™˜¨æ ©­á¢£˜ œ£§æ› ©œ «¤ ¦¢¦¡¢ã¨à© «ª œ¨š˜©å˜ª.\n" \
	"         ˜¨˜¡˜¢¦ç£œ œ¤£œ¨é©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª\n" \
	"         ©¬¤Ÿã¡œª §¦¬ «¦ ›£ ¦ç¨š©˜¤. …«¦ç£œ ©¬šš¤é£ š ˜ «¤\n" \
	"         «˜¢˜ §à¨å˜.\033[0;1m\n\n"



#endif /* ERRORPROMPTS_H */
