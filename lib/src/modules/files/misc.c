/*****************************************************************************\
 **                                                                         **
 **  FILE:     misc.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  Misc functions                                               **
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
 * Revision 1.5  2003/12/27 09:00:31  alexios
 * Adjusted #includes. Recoded time and charge calculations using integer
 * operations.
 *
 * Revision 1.4  2003/12/24 20:12:12  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Modified fileinfo() to display keywords even for files that
 * haven't been approved yet.
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Function fileheader() to print the full header of a file.
 * Function lcase() to convert a string to lower case. Funcs
 * calcxfertime() calccharge() to do what their respective
 * names suggest.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <math.h>
#include <libtyphoon/typhoon.h>
#include <megistos/bbs.h>
#include "files.h"
#include "mbk_files.h"


char   *
leafname (char *s)
{
	char   *cp = strrchr (s, '/');

	if (cp == NULL)
		return s;
	else
		return cp + 1;
}


char
       *
zonkdir (char *s)
{
	static char tmp[256];
	int     i, j;

	bzero (tmp, sizeof (tmp));
	for (i = j = 0; s[i]; i++, j++) {
		if (s[i] == '/') {
			if (s[i + 1] == '/')
				j--;
			else if (s[i + 1] == 0)
				break;
			else
				tmp[j] = s[i];
		} else
			tmp[j] = s[i];
	}

	return tmp;
}


int
nesting (char *s)
{
	int     i, c;

	for (i = c = 0; s[i]; i++)
		c += (s[i] == '/' || s[i] == '\\');
	return c;
}


void
libinfo ()
{
	struct stat st;
	char    fname[256], *cp, *s = strdup (othrdme);

	libreadnum (library.libnum, &library);
	sprintf (fname, "%s/%s", library.dir, rdmefil);
	if (!stat (fname, &st)) {
		prompt (INFOHDR);
		out_printfile (fname);
	} else {
		cp = strtok (s, " \n\r\t,");
		while (cp) {
			if (!strlen (cp))
				continue;
			sprintf (fname, "%s/%s", library.dir, cp);
			if (!stat (fname, &st)) {
				prompt (INFOHDR);
				out_printfile (fname);
				break;
			}
			cp = strtok (NULL, " \n\r\t");
		}
	}
	free (s);
}


void
fullinfo ()
{
	char    tmp[16386];

	libinfo ();
	if (library.flags & LBF_OSDIR) {
		strcpy (tmp, msg_get (LIBINFOO));
		strcat (tmp, msg_get (LIBINFO9));
	} else
		strcpy (tmp, msg_get (libop ? LIBINFO2 : LIBINFO1));
	if (library.flags & LBF_UPLAUD)
		strcat (tmp, msg_get (LIBINFO3));
	if (library.flags & LBF_DNLAUD)
		strcat (tmp, msg_get (LIBINFO4));
	if (library.flags & (LBF_LOCKUPL | LBF_LOCKDNL | LBF_LOCKENTR))
		strcat (tmp, msg_get (LIBINFO5));
	if (library.flags & LBF_READONLY)
		strcat (tmp, msg_get (LIBINFO6));
	if ((library.flags & LBF_OSDIR) == 0)
		strcat (tmp, msg_get (LIBINFO10));
	strcat (tmp, msg_get (LIBINFOF));
	print (tmp);
}


char   *
_getfiletype (char *fname, int recurse)
{
	FILE   *fp;
	static char filetype[256];
	char    command[256], line[1024], *cp = line;

	strcpy (filetype, msg_get (FTUNK));
	if (!recurse)
		return filetype;

	sprintf (command, "file %s", fname);
	if ((fp = popen (command, "r")) == NULL)
		return filetype;
	line[0] = 0;
	fgets (line, sizeof (line), fp);
	fclose (fp);

	if ((cp = strchr (line, 10)) != NULL)
		*cp = 0;
	if ((cp = strchr (line, 13)) != NULL)
		*cp = 0;
	if (!line[0])
		return filetype;

	if ((cp = strchr (line, 32)) == NULL)
		return filetype;
	else
		cp++;
	if (sameto (SYMLINKTO, cp)) {
		cp += strlen (SYMLINKTO);
		return _getfiletype (cp, recurse - 1);
	} else
		strcpy (filetype, cp);

	return filetype;
}


/* Loads of parens and typecasts here, but I once slaved over metres
   of printout for over a week, only to find a bleeding int<-->float
   conversion/rounding bug crashing a whole MajorBBS system. Be
   afraid; be /very/ afraid.

   So I'd rather have my luser ratio increased by using superfluous
   parens rather than quit paranoia mode and have to debug this kind
   of bollocks again. If you can do better, you can watch me not
   care.

    The formula used here is the same as in the updown tool: 

                           file size * 10 bits
     time in mins = ---------------------------------
                      60 * efficiency * (bps/38400) 


   2003-12-27: rearranged as an integer expression (with simulated
   rounding).

*/

int
calcxfertime (int size, int inseconds)
{
	int xfertime = (100 * size) /
		((thisuseronl.baudrate > 0 ? thisuseronl.baudrate : 38400) *
		 peffic * (inseconds ? 1 : 60));

	xfertime = (xfertime + 5) / 10;
	return xfertime;

#if 0	
	return (int)
	    (rint (((double) size) /
		   ((((double)
		      (thisuseronl.baudrate ? thisuseronl.baudrate : 38400) /
		      10.0) * (((double) peffic / 100.0))) *
		    (inseconds ? 1.0 : 60.0))));
#endif

}

/* Charge calculation:

   C0 = dnlcharge (in credits)
   C1 = thisuseronl->credspermin * 100  (in credits / 100 min)
   t  = download time (in seconds))

                     C1 cr             1 min
   Charge = C0 cr + --------- * t s * -------
                     100 min           60 s

                     C1 cr * t
   Charge = C0 cr + -----------
                     100 * 60

                      C1 t
   Charge = C0 cr + -------- cr
                      6000

   The extra accuracy of both the time (in seconds, not minutes) and
   charge (credits / 100 minutes, not credits per minute) aids in
   coding this as an integer expression directly (with the help of
   calcxfertime().
*/

int
calccharge (int size, struct libidx *l)
{
	return l->dnlcharge + 
		(thisuseronl.credspermin * calcxfertime (size, 1)) / 6000;

#if 0
	return (int)
	    (rint
	     (((double) l->dnlcharge) +
	      (((double) thisuseronl.credspermin) / 100.0) * ((double) size) /
	      ((((double) (thisuseronl.baudrate ? thisuseronl.baudrate : 38400)
		 / 10.0) * (((double) peffic / 100.0))) * 60.0)));
#endif

}



#define fracK(bytes) ((int)((float)((bytes)%(1<<10))/10.24))
#define fracM(bytes) ((int)((float)((bytes)%(1<<20))/10485.76))

int
fileinfo (struct libidx *l, struct fileidx *f)
{
	char   *filetype;
	struct stat st;
	struct tm *dt;
	char    fname[512];
	char    sizestg[256], timestg[256], chargestg[256];
	long    xfertime, charge;


	/* Get the file's actual full pathname and its type */
	sprintf (fname, "%s/%s", l->dir, f->fname);
	filetype = getfiletype (fname);


	/* Line 1: get size and its suitable unit (bytes, kbytes, Mbytes) */
	bzero (&st, sizeof (st));
	stat (fname, &st);
	if (st.st_size < (128 << 10))
		sprintf (sizestg, msg_get (FILINSB), st.st_size);
	else if (st.st_size < (1440 << 10))
		sprintf (sizestg, msg_get (FILINSK), st.st_size >> 10,
			 fracK (st.st_size));
	else
		sprintf (sizestg, msg_get (FILINSK), st.st_size >> 10,
			 fracM (st.st_size));


	/* Line 2: calculate download time and charge. */
	xfertime = calcxfertime (st.st_size, 0);
	charge = calccharge (st.st_size, &library);

	if (xfertime > 0)
		sprintf (timestg, msg_get (FILINTA), xfertime);
	else
		strcpy (timestg, msg_get (FILINTL));
	strcpy (chargestg, msg_getunit (CRDSNG, charge));


	dt = localtime ((const time_t *) &(f->timestamp));
	prompt (FILINFO,
		f->fname, sizestg,
		timestg, charge, chargestg,
		f->uploader, f->approved_by,
		strdate (makedate
			 (dt->tm_mday, dt->tm_mon + 1, 1900 + dt->tm_year)),
		strtime (maketime (dt->tm_hour, dt->tm_min, dt->tm_sec), 1),
		f->downloaded, msg_getunit (TIMSNG, f->downloaded), filetype,
		f->summary);


	/* Now scan the keywords */

	{
		struct filekey k;
		int     morekeys, keys = 0;
		char    keystg[8192];

		keystg[0] = 0;
		morekeys = keyfilefirst (l->libnum, f->fname, 1, &k);
		while (morekeys) {
			char    tmp[32];

			keys++;
			sprintf (tmp, "%s ", k.keyword);
			strcat (keystg, tmp);
			morekeys = keyfilenext (l->libnum, f->fname, 1, &k);
		}
		if (keys)
			prompt (FILINFOK, keystg);
		else {

			/* Try looking for unapproved keys */

			keystg[0] = 0;
			morekeys = keyfilefirst (l->libnum, f->fname, 0, &k);
			while (morekeys) {
				char    tmp[32];

				keys++;
				sprintf (tmp, "%s ", k.keyword);
				strcat (keystg, tmp);
				morekeys =
				    keyfilenext (l->libnum, f->fname, 0, &k);
			}
			if (keys)
				prompt (FILINFOK, keystg);
		}
	}

	/* Finally, show the long description */

	if (strlen (f->description))
		prompt (FILINFOD, f->description);

	return st.st_size;
}


char   *
lcase (char *s)
{
	char   *cp;

	for (cp = s; *cp; cp++)
		*cp = tolower (*cp);
	return s;
}


/* End of File */
