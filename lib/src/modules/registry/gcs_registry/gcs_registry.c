/*****************************************************************************\
 **                                                                         **
 **  FILE:     gcs_registry.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Implement the /r global command                              **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_STAT_H 1
#include <bbsinclude.h>

#include <bbs.h>
#include <megistos/registry.h>
#include <megistos/mbk_registry.h>


static promptblock_t *regmsg = NULL;
static int template[3][30];


/** The entry point to the global command */

int
__INIT_GCS__ ()
{
	struct stat st;
	char    fname[256], userid[32];

	if (margc == 2 && sameas (margv[0], "/r")) {
		if (regmsg == NULL) {
			int     i, j;

			regmsg = msg_open ("registry");
			for (i = 0; i < 3; i++)
				for (j = 0; j < 30; j++)
					template[i][j] =
					    msg_int (T1F1 + i * 30 + j, 0,
						     255);
		}

		msg_set (regmsg);
		strcpy (userid, margv[1]);
		usr_uidxref (userid, 0);
		if (!usr_exists (userid)) {
			prompt (REGERR);
			msg_reset ();
			return 1;
		}
		sprintf (fname, "%s/%s", mkfname (REGISTRYDIR), userid);
		if (stat (fname, &st)) {
			prompt (REGERR);
			msg_reset ();
			return 1;
		}

		{
			FILE   *fp;
			char   *format[33];
			struct registry registry;
			int     i, j, pos;

			msg_set (regmsg);
			memset (&registry, 0, sizeof (registry));

			sprintf (fname, "%s/%s", mkfname (REGISTRYDIR),
				 userid);
			if ((fp = fopen (fname, "r")) == NULL) {
				sprompt_other (othrshm, out_buffer, UIDERR);
				usr_injoth (&othruseronl, out_buffer, 0);
				return 1;
			}

			if (fread (&registry, sizeof (struct registry), 1, fp)
			    != 1) {
				error_fatalsys ("Unable to read registry %s",
						fname);
			}
			registry.template = registry.template % 3;
			fclose (fp);

			format[0] = userid;
			for (i = pos = 0, j = 1; i < 30;
			     pos += template[registry.template][i++] + 1) {
				if (template[registry.template][i])
					format[j++] = &registry.registry[pos];
			}
			format[j++] = registry.summary;
			format[j] = NULL;
			vsprintf (out_buffer,
				  msg_get (T1LOOKUP + registry.template),
				  format);
			print (out_buffer);
		}

		return 1;
	} else if (margc == 1 && sameas (margv[0], "/r")) {
		if (regmsg == NULL) {
			int     i, j;

			regmsg = msg_open ("registry");
			for (i = 0; i < 3; i++)
				for (j = 0; j < 30; j++)
					template[i][j] =
					    msg_int (T1F1 + i * 30 + j, 0,
						     255);
		}

		msg_set (regmsg);
		prompt (REGHELP);
		msg_reset ();
		return 1;
	}
	msg_reset ();
	return 0;
}


/* End of File */
