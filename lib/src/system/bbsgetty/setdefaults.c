/*****************************************************************************\
 **                                                                         **
 **  FILE:     setdefaults.c                                                **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  Set default values for the getty                             **
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
 * Revision 1.5  2003/12/23 08:18:08  alexios
 * Corrected minor #include discrepancies.
 *
 * Revision 1.4  2003/12/22 17:23:37  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  1999/07/18 21:54:26  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Added support for
 * the pre/postconnect fields.
 *
 * Revision 1.1  1998/12/27 16:15:40  alexios
 * Renamed connect to connectstr.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";



#define WANT_ERRNO_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "bbsgetty.h"



#define YESNO(x)  (sameas((x),"YES")?1:(sameas((x),"NO")?0:-1))
#define KEY(x) {#x,KEY_##x}



#define KEY_BUSYOUT       1
#define KEY_CONNECT       2
#define KEY_DEBUG         3
#define KEY_DELAY         4
#define KEY_GETTYDEF      5
#define KEY_HANGUP        6
#define KEY_INIT          7
#define KEY_LOCK          8
#define KEY_OFFLINE       9
#define KEY_TERM         10
#define KEY_WAITCHAR     11
#define KEY_WAITFOR      12
#define KEY_LOCKNAME     13
#define KEY_ALTLOCKNAME  14
#define KEY_INITIAL      15
#define KEY_FINAL        16
#define KEY_PRECONNECT   17
#define KEY_POSTCONNECT  18



struct keylist {
	char   *name;
	int     ref;
};



struct keylist keys[] = {
	KEY (BUSYOUT),
	KEY (CONNECT),
	KEY (DEBUG),
	KEY (DELAY),
	KEY (GETTYDEF),
	KEY (HANGUP),
	KEY (INIT),
	KEY (LOCK),
	KEY (OFFLINE),
	KEY (TERM),
	KEY (WAITCHAR),
	KEY (WAITFOR),
	KEY (LOCKNAME),
	KEY (ALTLOCKNAME),
	KEY (INITIAL),
	KEY (FINAL),
	KEY (PRECONNECT),
	KEY (POSTCONNECT),
	{"", -1}
};



static int
yesno (char *name, char *value, int *bool, int line)
{
	int     res = YESNO (value);

	if (res < 0) {
		debug (D_DEF,
		       "Line %d: expecting YES or NO value for %s, got \"%s\".",
		       line, name, value);
		error_fatal
		    ("Line %d: expecting YES or NO value for %s, got \"%s\".",
		     line, name, value);
	} else
		*bool = res;
	return res;
}



static void
processpair (char *name, char *value, int line)
{
	int     i, debuglevel;


	/* Look for the key's reference number */

	for (i = 0; keys[i].ref >= 0; i++) {
		if (sameas (name, keys[i].name))
			break;
	}



	/* Not found? */

	if (keys[i].ref < 0) {
		debug (D_DEF,
		       "Line %d: unknown configuration argument \"%s\".", line,
		       name);
		error_log ("Line %d: unknown configuration argument \"%s\".",
			   line, name);
		return;
	}


	/* Got it! Process the values */

	switch (keys[i].ref) {

	case KEY_DEBUG:
		if (value[0] == '0' && value[1] == 'x') {
			if (!sscanf (value, "%x", &debuglevel)) {
				debug (D_DEF,
				       "Line %d: DEBUG level \"%s\" is not a hexadecimal number.",
				       line, value);
				error_log
				    ("Line %d: DEBUG level \"%s\" is not a hexadecimal number.",
				     line, value);
			}
		} else if (value[0] == '0') {
			if (!sscanf (value, "%o", &debuglevel)) {
				debug (D_DEF,
				       "Line %d: DEBUG level \"%s\" is not an octal number.",
				       value);
				error_log
				    ("Line %d: DEBUG level \"%s\" is not an octal number.",
				     value);
			}
		} else {
			if (!sscanf (value, "%d", &debuglevel)) {
				debug (D_DEF,
				       "Line %d: DEBUG level \"%s\" is not a decimal number.",
				       line, value);
				error_log
				    ("Line %d: DEBUG level \"%s\" is not a decimal number.",
				     line, value);
			}
		}
		setdebuglevel (debuglevel);
		break;

	case KEY_HANGUP:
		yesno (name, value, &nohangup, line);
		nohangup = !nohangup;
		break;

	case KEY_WAITCHAR:
		yesno (name, value, &waitchar, line);
		break;

	case KEY_DELAY:
		if (!sscanf (value, "%d", &delay)) {
			debug (D_DEF,
			       "Line %d: value for DELAY \"%s\" is not a decimal number.",
			       line, value);
			error_log
			    ("Line %d: value for DELAY \"%s\" is not a decimal number.",
			     line, value);
		}
		break;

	case KEY_CONNECT:
		connectstr = strdup (value);
		break;

	case KEY_WAITFOR:
		waitfor = strdup (value);
		waitchar = 1;
		break;

	case KEY_INIT:
		initstr = strdup (value);
		break;

	case KEY_LOCK:
		yesno (name, value, &lockedbaud, line);
		break;

	case KEY_LOCKNAME:
		strcpy (lock, value);
		break;

	case KEY_ALTLOCKNAME:
		strcpy (altlock, value);
		break;

	case KEY_BUSYOUT:
		busyout = strdup (value);
		break;

	case KEY_OFFLINE:
		offline = strdup (value);
		break;

	case KEY_INITIAL:
		initial = strdup (value);
		break;

	case KEY_FINAL:
		final = strdup (value);
		break;

	case KEY_PRECONNECT:
		preconnect = strdup (value);
		break;

	case KEY_POSTCONNECT:
		postconnect = strdup (value);
		break;

	default:
		debug (D_DEF, "Sanity check failed! Yaaaaaargh! (code=%d)",
		       keys[i].ref);
		return;
	}
}



void
parsefile (char *suffix)
{
	FILE   *fp;
	char    fname[512];
	int     linenum;

	strcpy (fname, mkfname (CHANDEFDIR "/bbsgetty.%s", suffix));
	debug (D_DEF, "parsefile(\"%s\") called", fname);

	if ((fp = fopen (fname, "r")) == NULL) {
		int     i = errno;

		error_log ("Unable to open config file %s", fname);
		debug (D_DEF, "fopen(\"%s\",\"r\") failed, errno=%d", fname,
		       i);
		return;
	}

	linenum = 0;
	while (!feof (fp)) {
		char    line[8192], *name, *value, *cp;

		if (fgets (line, sizeof (line), fp) == NULL)
			break;
		linenum++;

		/* Remove comments */
		if ((cp = strchr (line, '#')) != NULL)
			*cp = 0;

		/* Empty line? */
		if (!strlen (stripspace (line)))
			continue;

		/* Get the name and value */
		if ((cp = strchr (line, '=')) == NULL) {
			debug (D_DEF,
			       "line %d has bad format (not NAME=VALUE)",
			       linenum);
			error_log ("bad format (%s line %d)", fname, linenum);
			continue;
		}

		*cp = 0;
		name = line;
		value = cp + 1;
		name = strtok (name, " \t\f");
		cp = stripspace (value);
		strcpy (value, cp);
		cp = &value[strlen (value) - 1];
		for (;
		     cp >= value && (isspace (*cp) || *cp == '\n' ||
				     *cp == '\r'); cp--)
			*cp = 0;

		/* Debug the name=value pair */
		debug (D_DEF, "Parsed line: \"%s\" = \"%s\"", name, value);


		/* Processs the name/value pairs */
		processpair (name, value, linenum);

	}

	debug (D_DEF, "Options parsed successfully");
}



/* Setup validation and sanity checks */
void
validate ()
{
	if (!strlen (device)) {
		debug (D_DEF, "No device has been specified!");
		error_fatal ("No device has been specified!");
	}

	if (!initial || !strlen (initial)) {
		debug (D_DEF, "No INI_IAL flags have been specified!");
		error_fatal ("No INI_IAL flags have been specified!");
	} else if (!final || !strlen (final)) {
		final = strdup (initial);
	}
}



void
setdefaults (int argc, char **argv)
{
	register int c;
	int     debuglevel;


	/* Parse command line -- this is mostly uugetty stuff for slight
	   compatibility reasons */

	while ((c = getopt (argc, argv, "D:")) != EOF) {
		switch (c) {
		case 'D':
			if (optarg[0] == '0' && optarg[1] == 'x') {
				if (!sscanf (optarg, "%x", &debuglevel)) {
					error_fatal
					    ("Debug level \"%s\" is not a hexadecimal number.",
					     optarg);
				}
			} else if (optarg[0] == '0') {
				if (!sscanf (optarg, "%o", &debuglevel)) {
					error_fatal
					    ("Debug level \"%s\" is not an octal number.",
					     optarg);
				}
			} else {
				if (!sscanf (optarg, "%d", &debuglevel)) {
					error_fatal
					    ("Debug level \"%s\" is not a decimal number.",
					     optarg);
				}
			}
			setdebuglevel (debuglevel);
			break;
		}
	}



	/* Get tty name */

	if (optind < argc) {
		strcpy (device, argv[optind++]);
	} else {
		error_fatal ("No TTY device given in command line.");
		exit (2);
	}
}


/* End of File */
