/*****************************************************************************\
 **                                                                         **
 **  FILE:     mksysvar.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Creates global system variables/configuration file           **
 **  NOTES:    Reads system configuration from sysvar.mbk and stores them   **
 **            in /bbs/sysvar. That file also stores system statistics,     **
 **            and other accounting stuff. If the file exists, all that is  **
 **            not affected in any way. If the file is inexistent, it is    **
 **            created by this utility.                                     **
 **                                                                         **
 **            It is highly recommended (ie *DO*IT*!) to run mksysvar once  **
 **            in a while (eg every morning). Of course you have to run it  **
 **            to update sysvar if you change config options like the name  **
 **            of the BBS (found in sysvar.msg)                             ** 
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
 * Revision 1.5  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/19 13:20:11  alexios
 * Brought into the new build tree; ran it through indent(1).
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.6  1999/08/13 17:11:01  alexios
 * Cosmetic changes, mostly, plus a clean return from main().
 *
 * Revision 1.5  1999/07/18 22:11:40  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.4  1998/12/27 16:38:56  alexios
 * Added autoconf support. Added code to handle new variables.
 *
 * Revision 1.3  1998/07/24 10:32:39  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.2  1997/11/06 20:19:27  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/11/06 17:09:17  alexios
 * Fixed a leftover silly bug.
 *
 * Revision 1.0  1997/08/28 11:34:24  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER
#define RCS_VER "$Id$"
const char *__RCS = RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>

#include <mbk/mbk_sysvar.h>

promptblock_t *sysvars;


int
main ()
{
	FILE   *sysvarf;
	struct sysvar sysvar;
	int     exists = 0;

	sysvars = msg_open ("sysvar");

	if ((sysvarf = fopen (mkfname (SYSVARFILE), "r+")) != NULL)
		exists = 1;
	else if ((sysvarf = fopen (mkfname (SYSVARFILE), "w+")) != NULL)
		exists = 0;
	else
		error_fatalsys ("Unable to open/create %s.",
				mkfname (SYSVARFILE), 0);

	if (!exists) {
		fprintf (stderr, "%s does not exist, creating it.\n",
			 mkfname (SYSVARFILE));
		memset (&sysvar, 0x00, sizeof (struct sysvar));
	} else {
		if (fread (&sysvar, sizeof (struct sysvar), 1, sysvarf) != 1) {
			error_fatalsys ("Error reading %s.",
					mkfname (SYSVARFILE), 0);
		}
	}

	strcpy (sysvar.bbstitle, msg_string (BBSTTL));
	strcpy (sysvar.company, msg_string (COMPANY));
	strcpy (sysvar.address1, msg_string (ADDRES1));
	strcpy (sysvar.address2, msg_string (ADDRES2));
	strcpy (sysvar.city, msg_string (CITY));
	strcpy (sysvar.dataphone, msg_string (DATAPH));
	strcpy (sysvar.voicephone, msg_string (VOICEPH));
	strcpy (sysvar.livephone, msg_string (LIVEPH));
	sysvar.idlezap = msg_int (IDLZAP, 0, 32767);
	sysvar.idlovr = msg_int (IDLOVR, 0, 129);
	sysvar.saverate = msg_int (SVRATE, 0, 32767);
	strcpy (sysvar.chargehour, msg_string (CHGHOUR));
	strcpy (sysvar.mincredits, msg_string (CHGTIME));
	strcpy (sysvar.minmoney, msg_string (CHGMIN));
	sysvar.bbsrst = msg_int (BBSRST, 0, 9999);

	sysvar.pswexpiry = msg_int (PSWEXP, 0, 360);
	sysvar.pagekey = msg_int (PAGEKEY, 0, 129);
	sysvar.pgovkey = msg_int (PGOVKEY, 0, 129);
	sysvar.pallkey = msg_int (PALLKEY, 0, 129);
	sysvar.glockie = msg_bool (GLOCKIE);
	sysvar.lonaud = msg_bool (LONAUD);
	sysvar.lofaud = msg_bool (LOFAUD);
	sysvar.tnlmax = msg_int (TNLMAX, 1, 32767);

	/* Stamp it with the magic number */

	memcpy (sysvar.magic, SYSVAR_MAGIC, sizeof (sysvar.magic));

	if (fseek (sysvarf, 0, SEEK_SET)) {
		error_fatalsys ("Error seeking %s.", mkfname (SYSVARFILE), 0);
	}
	if (fwrite (&sysvar, sizeof (struct sysvar), 1, sysvarf) != 1) {
		error_fatalsys ("Error writing %s.", mkfname (SYSVARFILE), 0);
	}
	fclose (sysvarf);

	return 0;
}
