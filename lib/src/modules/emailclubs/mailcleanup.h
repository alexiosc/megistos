/*****************************************************************************\
 **                                                                         **
 **  FILE:     mailcleanup.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95                                              **
 **  PURPOSE:  Perform cleanup on email and club messages                   **
 **  NOTES:    Actions performed:                                           **
 **            email: delete old messages                                   **
 **            clubs: delete old messages if applicable,                    **
 **                   sync club statistics (msgs, files, blts, unapp, etc)  **
 **                   repost periodic messages                              **
 **                   reindex messages                                      **
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
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/25 13:33:28  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1997/11/06 20:09:08  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/30 12:52:57  alexios
 * Initial revision
 *
 * Revision 1.0  1997/08/30 12:51:55  alexios
 * Initial revision
 *
 *
 */


#define DAYSSINCEFILE "..LAST.CLEANUP"


/*                   123456789012345678901234567890 */
#define AUS_MAILCUB "MAIL ACCOUNT CLEANUP"
#define AUS_MAILCUE "END OF MAIL ACCOUNT CLEANUP"

/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_MAILCUB "%d day(s) since last user cleanup"


extern struct top *topposters, *toppop, *topmsgs, *topfiles, *topblts;

extern int dayssince;
extern int numusers;
extern int nummodified;
extern int emllif;


void    clubcleanup ();

void    doreindex ();




/* End of File */
