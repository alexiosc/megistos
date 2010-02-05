/*****************************************************************************\
 **                                                                         **
 **  FILE:      compiler.c                                                  **
 **  AUTHORS:   Antonis Stamboulis (Xplosion), Vangelis Rokas (Valis)       **
 **  PURPOSE:   Gallups Script Compiler                                     **
 **  NOTES:     This was originally in the gallups.c                        **
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
 * $Id: compiler.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: compiler.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/31 06:59:19  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.4  2000/09/30 14:39:28  bbs
 * changed the handling of errors and warnings
 * added more error messages to be more user friendly
 * added message with number of warnings and errors
 *
 * Revision 1.3  2000/09/30 09:25:13  bbs
 * changed extract_str() to return 2 if a dash was found before {}
 * changed extract_options() to return the index of the correct
 *  option (if it is prefixed with a star,*)
 * option separator is now | (; is obsolete)
 *
 * Revision 1.2  2000/09/27 18:35:06  bbs
 * changed the options separator from ; to |
 * a bug in extract_options() corrected
 *
 * Revision 1.1  2000/09/21 18:15:54  bbs
 * improved script compiler conforming to 4.0 Standard
 *
 *
 */


static const char rcsinfo[] =
    "$Id: compiler.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";

/*
 *	script compiler for gallops module
 */



#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "gsc.h"

#if defined(__BORLANDC__)
#  include "glps-bcc.h"
#else
#  include "gallups.h"
#endif


#ifdef __BORLANDC__
#  define	strcasecmp	strcmpi
#endif


struct question *questions;
struct answer *answers;

int     line = 0;		// script line
int     errors = 0;		// errors count
int     warnings = 0;		// warnings count


/* is that enough? */
char    tempstr[8192];

/* reads from FP a string inside brackets. A \ can be used as an escape character
 * to enter a } or \ in the text.
 * There must be enough space in STR to hold the string. Return 1 on success, 0 otherwise
 *
 * Return 0, on error, >0 on success that is: 2 if a dash (-) was found before "{", 1 otherwise
 */
int
scan_string (FILE * fp, char *str)
{
	int     escape = 0, scanend = 0, nlcnt = 0, res = 0;
	char    c;

	strcpy (str, "");

	/* find the opening bracket, no escape translation yet */
	while (!feof (fp)) {
		c = fgetc (fp);
		if (c == '-')
			res = 1;
		if (c == '\n')
			nlcnt++;
		if (c == '{')
			break;
	}
	if (feof (fp))
		return 0;

	/* start string copying */
	while (!feof (fp) && !scanend) {
		c = fgetc (fp);
		if (c == '\n')
			nlcnt++;
		if (!escape)
			switch (c) {
			case '\\':
				escape = 1;
				continue;
				break;
			case '}':
				scanend = 1;
				continue;
				break;
			case '\r':
				continue;
				break;
		} else
			escape = 0;

		strncat (str, &c, 1);
	}

	line += nlcnt;

	while (fgetc (fp) != '\n');	/* reach end-of-line */

	if (feof (fp))
		return 0;

	return (res == 1) ? 2 : 1;
}


/* copy from str to ostr any text beginning from position pos,
   then strip any spaces or tab from the begin or the end of ostr*/
void
extract_str (char *str, int pos, char *ostr)
{
	strcpy (ostr, "");
	strcpy (ostr, &str[pos]);
	while (strchr (" \t\n", ostr[0]))
		memmove (ostr, ostr + 1, strlen (ostr));
	while (strchr (" \t\n", ostr[strlen (ostr) - 1]))
		ostr[strlen (ostr) - 1] = '\0';
}


/* extract a |-separated list of options from str, into ostr
 * as NL-terminated at ostr.
 *
 * Return a number indicating, in which option a star was found
 * as the first character (which means that this is the answer)
 */
int
extract_options (char *str, char *ostr)
{
	char    white[] = "\t\n ";
	int     es = 0, ans = 0, opt = 0;
	char   *c;
	char    st[1024];

	strcpy (ostr, "");
	strcpy (st, "");

	c = str;

	while (c && (*c) != '\0') {
		if (!es) {
			switch (*c) {
			case '|':
				while (st[0] && strchr (white, st[0]))
					memmove (st, st + 1, strlen (st));
				while (st[0] &&
				       strchr (white, st[strlen (st) - 1]))
					st[strlen (st) - 1] = '\0';
				if (strlen (st)) {
					opt++;
					strcat (ostr, st);
					strcat (ostr, "\n");
					strcpy (st, "");
				};
				break;
			case '\\':
				es = 1;
				break;
			case '*':
				ans = opt + 1;
				break;
			default:
				strncat (st, c, 1);
			}
		} else {
			strncat (st, c, 1);
			es = 0;
		}
		c++;
	}

	if (strlen (st)) {
		while (st[0] && strchr (" \t\n", st[0]))
			memmove (st, st + 1, strlen (st));
		while (st[0] && strchr (" \t\n", st[strlen (st) - 1]))
			st[strlen (st) - 1] = '\0';
		if (strlen (st)) {
			strcat (ostr, st);
			strcat (ostr, "\n");
		}
	}

	return ans;
}

#define doerror(frm,f...)	errormsg(0, frm, ##f)
#define error(frm,f...)		{ doerror(0, frm, ##f); goto loop; }
#define fatal(frm,f...)		errormsg(1, frm, ##f)

void
errormsg (int fatal, char *frm, ...)
{
	va_list ap;
	char    st[128];

	va_start (ap, frm);
	vsprintf (st, frm, ap);
	va_end (ap);

	printf ("line %i: error: %s\n", line, st);

	if (fatal)
		exit (10);
	errors++;
}


void
dowarning (char *frm, ...)
{
	va_list ap;
	char    st[128];

	va_start (ap, frm);
	vsprintf (st, frm, ap);
	va_end (ap);

	printf ("line %i: warning: %s\n", line, st);
	warnings++;
}

int     scriptcompiler (char *script);
int     question (FILE * fp);

int
question (FILE * fp)
{
	char    s[256], s1[50], c;
	char    cstring[8192], pstring[8192];
	long    pos;
	int     type, a, fin, n;
	struct question *q;
	struct answer *an;

	strcpy (cstring, "");
	strcpy (pstring, "");

	questions =
	    realloc (questions,
		     (gnumq (ginfo) + 1) * sizeof (struct question));
	q = &questions[gnumq (ginfo)];

	qtyp (q) = qflg (q) = type = fin = 0;
	qans (q) = NULL;
	qseldt (q) = qcomdt (q) = NULL;

	if (gflgs (ginfo) & GF_QUIZ) {
		qcrd0 (q) = gcrd0 (ginfo);
		qcrd1 (q) = gcrd1 (ginfo);
	}

	debug ("question parsing begins\n");

	pos = ftell (fp);
	fgets (s, 256, fp);
	while (!feof (fp)) {
		line++;
		if (strchr (s, '\r'))
			(*strchr (s, '\r')) = '\0';	// use this for DOS files
		if (strchr (s, '\n'))
			(*strchr (s, '\n')) = '\0';	// this for normal Linux file

		if (strlen (s) == 0)
			goto loop;
		if (s[0] == '#')
			goto loop;

		strcpy (s1, "");
		if (sscanf (s, "%s %n", s1, &n) < 1)
			goto loop;

		if (!strcasecmp (s1, "text") || !strcasecmp (s1, "number")
		    || !strcasecmp (s1, "select") || !strcasecmp (s1, "combo")) {

			if (type)
				error ("unexpected identifier `%s'", s1);

			if (!strcasecmp (s1, "text")) {
				type = GQ_FREETEXT;
				n = sscanf (s, "%*s %i", &a);

				if (!n)
					error ("number expected after `%s'",
					       s1);
				qtxtln (q) = a;
			} else if (!strcasecmp (s1, "number")) {
				type = GQ_NUMBER;
				n = sscanf (s, "%*s %i", &a);

				qnummx (q) = 0x7ffffffe;
				qnummn (q) = -qnummx (q);

				if (n > 0)
					qnummn (q) = a;

				n = sscanf (s, "%*s %*i %i", &a);

				if (n > 0)
					qnummx (q) = a;
			} else if (!strcasecmp (s1, "select")) {
				type = GQ_SELECT;
				qseldt (q) = NULL;

			} else if (!strcasecmp (s1, "combo")) {

				/* combos are not allowed in quizzes */
				if (gflgs (ginfo) & GF_QUIZ)
					fatal
					    ("combo questions are not allowed in polls");

				type = GQ_COMBO;

				n = sscanf (s, "%*s %i", &a);

				if (n == 1) {
					if (a < 2)
						fatal
						    ("user defined choices must be 2 or more");
					qflg (q) |= QF_COMBOUSER;
					qcompromcnt (q) = a;
					qcomch (q) =
					    malloc (sizeof (char) * a + 1);
					memset (qcomch (q), 0, a + 1);
				} else {
					qflg (q) |= QF_COMBODEFAULT;
					qcompromcnt (q) = 2;
					qcomch (q) = strdup ("YN");
					qcompr (q) =
					    strdup ("[Y]es=Œ˜å\n[N]o=Ž® \n");
				}

				qcomdt (q) = NULL;

				debug
				    ("Setting up combo question with %s flag\n",
				     n ==
				     1 ? "QF_COMBOUSER" : "QF_COMBODEFAULT");

			} else
				fatal ("unknown tag encountered `%s'", s1);

			debug ("Question type %s\n", s1);
			qtyp (q) |= type;
		} else if (!strcasecmp (s1, "answer")) {
			if (gflgs (ginfo) & GF_POLL)
				error
				    ("answer directive has no significance in polls");

			if (qans (q))
				dowarning ("multiple answer definitions");

			if (!qans (q))
				an = qans (q) =
				    malloc (sizeof (struct answer));
			else
				an = qans (q);

			switch (qtyp (q)) {
			case GQ_NUMBER:
				if (sscanf (s, "%*s %i", &a) < 1)
					error
					    ("the answer to a number question MUST be a number");
				anumdt (an) = a;
				break;
			case GQ_FREETEXT:
				extract_str (s, n, tempstr);
				if (!strlen (tempstr))
					error
					    ("no string, or error parsing answer text in question");
				atxtdt (an) = strdup (tempstr);
				break;
			case GQ_SELECT:
				if (sscanf (s, "%*s %i", &a) < 1)
					error
					    ("the answer to a multiple choice question MUST be the # of the correct option");
				aseldt (an) = a - 1;
				break;
			}

			debug ("Correct answer is %i\n", a - 1);

		} else if (!strcasecmp (s1, "options")) {
			if (type != GQ_SELECT && type != GQ_COMBO)
				fatal
				    ("options directive is only valid in SELECT and COMBO questions");

			if ((type == GQ_SELECT && qseldt (q))
			    || (type == GQ_COMBO && qcomdt (q)))
				fatal ("directive options encountered twince");

			fseek (fp, pos, SEEK_SET);
			n = scan_string (fp, tempstr);
			if (!n)
				fatal
				    ("text in {} expected after option directive");
			if (n == 2 && type == GQ_SELECT) {
				qflg (q) |= QF_SELECTNOMENU;
			}

			n = extract_options (tempstr, cstring);
			if (type == GQ_SELECT && gflgs (ginfo) & GF_QUIZ &&
			    n > 0) {
				if (!qans (q))
					an = qans (q) =
					    malloc (sizeof (struct answer));
				else
					an = qans (q);
				aseldt (an) = n - 1;

				debug ("Correct answer is %i\n", n - 1);
			}

			if (type == GQ_SELECT)
				qseldt (q) = strdup (cstring);
			if (type == GQ_COMBO)
				qcomdt (q) = strdup (cstring);

			debug ("Storing options `%s'\n", cstring);
		} else if (!strcasecmp (s1, "choice")) {
			if (type != GQ_COMBO && !(qflg (q) & QF_COMBOUSER))
				fatal
				    ("choice directove is only valid in COMBO questions");

			if (qcompromcnt (q) == strlen (qcomch (q)))
				error
				    ("choice directives exceed maximum choice specified");

			c = 0;
			sscanf (s, "%*s %c %n", &c, &n);
			if (!c)
				error
				    ("selection character expected as argument 1 in directive choice");

			if (c == 'X' || c == 'x' || c == '®' || c == '•')
				error
				    ("character `%c' may interfere with BBS internal eXit command",
				     c);
			if (strchr (qcomch (q), c))
				error
				    ("selection char `%c' is encoutered twice",
				     c);

			strncat (qcomch (q), &c, 1);

			extract_str (s, n, tempstr);
			if (!strlen (tempstr))
				error
				    ("selection text expected as argument 2 in directive choice");
			strcat (pstring, tempstr);
			strcat (pstring, "\n");
			debug ("Storing choice `%c' -> `%s'\n", c, tempstr);
		} else if (!strcasecmp (s1, "credits")) {
			if (!(gflgs (ginfo) & GF_QUIZ))
				error
				    ("directive credits has no significance in polls");
			n = sscanf (s, "%*s %s %i", s1, &a);
			if (!n)
				error
				    ("identifier expected as argument 1 in directive credits");
			if (n == 1)
				error
				    ("amount of credits expected as argument 2 of directive credits");
			if (!strcasecmp (s1, "correct"))
				qcrd0 (q) = a;
			else if (!strcasecmp (s1, "wrong"))
				qcrd1 (q) = a;
			else
				error
				    ("identifier `%s' is invalid. `correct' or `wrong' are only valid as argument 2 in directive credits",
				     s1);

			debug ("Question credits for %s answer %i\n", s1, a);
		} else if (!strcasecmp (s1, "end")) {

			if (!qprm (q))
				doerror
				    ("question definition ends without a question prompt");
			if (gflgs (ginfo) & GF_QUIZ && !qans (q))
				doerror ("directive answer is expected");

			if (qtyp (q) == GQ_SELECT) {
				if (!qseldt (q))
					doerror
					    ("directive options is expected");
			}

			if (qtyp (q) == GQ_COMBO) {
				if (!qcomdt (q))
					doerror
					    ("directive choice is expected");
			}

			gnumq (ginfo)++;
			if (type == GQ_COMBO) {
				qcomdt (q) = strdup (cstring);
				if (qflg (q) & QF_COMBOUSER)
					qcompr (q) = strdup (pstring);
			}

			debug ("question parsing ends\n");
			return 1;
		} else if (s1[0] == '{' /*strchr(s1, '{') */ ) {
			fseek (fp, pos, SEEK_SET);
			if (!scan_string (fp, tempstr))
				fatal ("error reading prompt text");
			qprm (q) = strdup (tempstr);
			debug ("Storing question prompt\n");
			debug ("Question prompt = {%s}\n", qprm (q));
			goto loop;
		} else
			error ("unknown directive `%s'", s1);

	      loop:
		pos = ftell (fp);
		fgets (s, 256, fp);
	}

	fatal ("error reading from script file. EOF reached.");

	return 0;
}


int
scriptcompiler (char *script)
{
	FILE   *fp;
	char    s[256], s1[50];
	int     a, n;
	long int pos = 0;

	if ((fp = fopen (script, "r")) == NULL) {
		fprintf (stderr, "could not open script file %s\n", script);
		return 0;
	}

	strcpy (gdesc (ginfo), "");
	gcrd0 (ginfo) = 1;
	gcrd1 (ginfo) = 0;
	gcrd2 (ginfo) = 0;

	fgets (s, 256, fp);
	while (!feof (fp)) {
		line++;
		if (strchr (s, '\r'))
			(*strchr (s, '\r')) = '\0';	// use this for DOS files
		if (strchr (s, '\n'))
			(*strchr (s, '\n')) = '\0';	// this for normal Linux file

//              while(strchr(" \t", s[0])!=NULL)memmove(s, s+1, strlen(s));

		if (strlen (s) == 0)
			goto loop;
		if (s[0] == '#')
			goto loop;

		strcpy (s1, "");
		if (sscanf (s, "%s %n", s1, &n) < 1)
			goto loop;

		if (!strcasecmp (s1, "title")) {
			strcpy (tempstr, &s[n]);
			while (tempstr[0] == ' ' || tempstr[0] == '\t')
				memmove (tempstr, tempstr + 1,
					 strlen (tempstr));

			debug ("Gallup Title: %s\n", tempstr);

			if (strlen (tempstr) > sizeof (gdesc (ginfo)))
				dowarning
				    ("title size exceeds maximum allowed length. It will be truncated to %i characters",
				     sizeof (gdesc (ginfo)));

			strncpy (gdesc (ginfo), tempstr,
				 sizeof (gdesc (ginfo)) - 1);
		} else if (!strcasecmp (s1, "type")) {
			sscanf (s, "%*s %s", s1);
			if (!strcasecmp (s1, "poll"))
				gflgs (ginfo) |= GF_POLL;
			else if (!strcasecmp (s1, "quiz"))
				gflgs (ginfo) |= GF_QUIZ;
			else
				error ("invalid tag `%s' in directive type",
				       s1);

			debug ("Gallop type : %s\n", s1);
			if (gflgs (ginfo) & GF_POLL && gflgs (ginfo) & GF_QUIZ)
				fatal ("gallup cannot be a POLL and a QUIZ");

			/* warn about multiple submits in a quiz */
			if ((gflgs (ginfo) & GF_QUIZ) &&
			    (gflgs (ginfo) & GF_MULTISUBMIT))
				dowarning
				    ("multiple submits are enabled in a Quiz-type gallup");

			if ((gflgs (ginfo) & GF_QUIZ) &&
			    !(gflgs (ginfo) & GF_LOGUSERID))
				fatal ("anonymous quiz is of no interest");

			/* warn and assume an error, when timing a poll */
			if ((gflgs (ginfo) & GF_POLL) &&
			    (gflgs (ginfo) & GF_TIMED)) {
				dowarning
				    ("timing a poll is meaningless. Timing will be disabled");
				gflgs (ginfo) &= ~GF_TIMED;
			}

			/* warn and assume an error, when extra check on a poll */
			if ((gflgs (ginfo) & GF_POLL) &&
			    (gflgs (ginfo) & (GF_EXTRA | GF_GONEXT))) {
				dowarning
				    ("flags GF_EXTRA or GF_GONEXT are not valid in a poll. They will be disabled");
				gflgs (ginfo) &= ~(GF_EXTRA | GF_GONEXT);
			}

		} else if (!strcasecmp (s1, "credits")) {
			if (!(gflgs (ginfo) & GF_QUIZ))
				error
				    ("directive credits has no significance in poll");
			n = sscanf (s, "%*s %s %i", s1, &a);
			if (!n)
				error
				    ("identifier expected as argument 1 in directive credits");
			if (n == 1)
				error
				    ("amount of credits expected as argument 2 of directive credits");
			if (!strcasecmp (s1, "correct"))
				gcrd0 (ginfo) = a;
			else if (!strcasecmp (s1, "wrong"))
				gcrd1 (ginfo) = a;
			else if (!strcasecmp (s1, "default"))
				gcrd2 (ginfo) = a;
			else
				error
				    ("identifier `%s' is invalid. `correct', `wrong' and `default' are only valid as argument 2 in directive credits",
				     s1);

			debug ("Credits for %s answer = %i\n", s1, a);
		} else
		    if (!strcasecmp (s1, "text") || !strcasecmp (s1, "number")
			|| !strcasecmp (s1, "select") ||
			!strcasecmp (s1, "combo")) {

			fseek (fp, pos, SEEK_SET);
			line--;
			question (fp);

		} else
			fatal ("unknown directive `%s'", s1);

	      loop:
		pos = ftell (fp);
		fgets (s, 256, fp);
	}

	if (!strlen (gdesc (ginfo)))
		doerror ("gallup title expecteed");
	if (!(gflgs (ginfo) & (GF_POLL | GF_QUIZ)))
		doerror ("gallup type is expected");

	if (errors > 0)
		return 0;

	printf ("%i warnings, %i errors\n", warnings, errors);

	if (gscflags & SYNTAX)
		return 1;
	if (!outname[0])
		return 1;

	return _savegallup (outname);
}



/* End of File */
