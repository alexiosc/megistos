/*****************************************************************************\
 **                                                                         **
 **  FILE:     mkaction.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 1.0                                    **
 **  PURPOSE:  Teleconferences, compile the action verb definition file     **
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
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/11 10:21:33  alexios
 * Fixed serious multilingual bug.
 *
 * Revision 0.4  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1998/03/10 11:17:28  alexios
 * Changed an instance of "/bbs/bin" to BINDIR in the interest
 * of directory independence.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




#define MKACTION

#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/telecon.h>
#include <megistos/actions.h>


union action *actions = NULL;
int     verbs = 0;


int
keycmp (const void *A, const void *B)
{
	const struct keyword *a = A, *b = B;

	return strcmp (a->keyword, b->keyword);
}


int
verbcmp (const void *A, const void *B)
{
	const union action *a = A, *b = B;

	return strcmp (a->s.verb, b->s.verb);
}


void
check (union action *a)
{
	switch (a->s.type) {
	case TYPE_SIMPLE:
		if (!a->s.simple[0]) {
			fprintf (stderr,
				 "Verb '%s' (S) has no 'simple' strings.\n",
				 a->s.verb);
			exit (1);
		}
		break;
	case TYPE_OBJECT:
		if (!a->o.other[0]) {
			fprintf (stderr,
				 "Verb '%s' (O) has no 'other' strings.\n",
				 a->o.verb);
			exit (1);
		} else if (!a->o.all[0]) {
			fprintf (stderr,
				 "Verb '%s' (O) has no 'all' strings.\n",
				 a->o.verb);
			exit (1);
		} else if (!a->o.target[0]) {
			fprintf (stderr,
				 "Verb '%s' (O) has no 'target' strings.\n",
				 a->o.verb);
			exit (1);
		} else if (!a->o.secret[0]) {
			fprintf (stderr,
				 "Verb '%s' (O) has no 'secret' strings.\n",
				 a->o.verb);
			exit (1);
		}
		break;
	case TYPE_DOUBLE:
		if (!a->d.other[0]) {
			fprintf (stderr,
				 "Verb '%s' (D) has no 'other' strings.\n",
				 a->d.verb);
			exit (1);
		} else if (!a->d.all[0]) {
			fprintf (stderr,
				 "Verb '%s' (D) has no 'all' strings.\n",
				 a->d.verb);
			exit (1);
		} else if (!a->d.target[0]) {
			fprintf (stderr,
				 "Verb '%s' (D) has no 'target' strings.\n",
				 a->d.verb);
			exit (1);
		} else if (!a->d.secret[0]) {
			fprintf (stderr,
				 "Verb '%s' (D) has no 'secret' strings.\n",
				 a->d.verb);
			exit (1);
		} else if (!a->d.simple[0]) {
			fprintf (stderr,
				 "Verb '%s' (D) has no 'simple' strings.\n",
				 a->d.verb);
			exit (1);
		}
		break;
	case TYPE_ADVERB:
		if (!a->a.adverb[0]) {
			fprintf (stderr,
				 "Verb '%s' (A) has no 'adverb' strings.\n",
				 a->a.verb);
			exit (1);
		} else if (!a->a.simple[0]) {
			fprintf (stderr,
				 "Verb '%s' (A) has no 'simple' strings.\n",
				 a->a.verb);
			exit (1);
		}
		break;
	case TYPE_GENERIC:
		if (!a->g.generic[0]) {
			fprintf (stderr,
				 "Verb '%s' (G) has no 'generic' strings.\n",
				 a->a.verb);
			exit (1);
		}
		break;
	}
}


static void
expand (char **s)
{
	int     i;
	char   *prev = s[0];

	/* check() guarrantees there's at least ONE string, so no need to check */

	for (i = 1; i < ML; i++) {
		if (s[i] == NULL || strlen (s[i]) == 0)
			s[i] = prev;
		prev = s[i];
	}
}


static void
expandlanguages (union action *a)
{
	switch (a->s.type) {
	case TYPE_SIMPLE:
		expand (a->s.user);
		expand (a->s.simple);
		break;
	case TYPE_OBJECT:
		expand (a->o.user);
		expand (a->o.other);
		expand (a->o.all);
		expand (a->o.target);
		expand (a->o.secret);
		break;
	case TYPE_DOUBLE:
		expand (a->d.user);
		expand (a->d.simple);
		expand (a->d.other);
		expand (a->d.all);
		expand (a->d.target);
		expand (a->d.secret);
		break;
	case TYPE_ADVERB:
		expand (a->a.user);
		expand (a->a.simple);
		expand (a->a.adverb);
		break;
	case TYPE_GENERIC:
		expand (a->g.user);
		expand (a->g.generic);
		break;
	}
}


void
addtolist (union action *a)
{
	union action *tmp;

	expandlanguages (a);
	tmp = alcmem (++verbs * sizeof (union action));
	memcpy (tmp, actions, (verbs - 1) * sizeof (union action));
	memcpy (&tmp[verbs - 1], a, sizeof (union action));
	if (actions)
		free (actions);
	actions = tmp;
}


int
verbexists (char *verb)
{
	int     i;

	for (i = 0; i < verbs; i++)
		if (sameas (actions[i].s.verb, verb))
			return 1;
	return 0;
}


void
parsein (int num, char *keyword, char *array[], char *data)
{
	int     n;

	for (n = 0; n < ML && array[n]; n++);
	if (n >= ML) {
		fprintf (stderr,
			 "Line %d: more than %d '%s' lines in this def.\n",
			 num, ML, keyword);
		exit (1);
	} else
		array[n] = strdup (data);
}


int
main (int argc, char *argv[])
{
	FILE   *fin, *fout;
	char    line[2048], *cp, keyword[256], *data, tmp[2048];
	int     num = 0, i, n, nkeywords = 0, first = 1;
	struct keyword *k;
	union action a;

	mod_setprogname (argv[0]);
	if ((fin = fopen (mkfname (TELEACTSRCFILE), "r")) == NULL) {
		fprintf (stderr, "%s: Unable to open %s\n", argv[0],
			 mkfname (TELEACTSRCFILE));
		exit (1);
	}

	if ((fout = fopen (mkfname (TELEACTMSGFILE), "w")) == NULL) {
		fprintf (stderr, "%s: Unable to create %s\n", argv[0],
			 mkfname (TELEACTMSGFILE));
		exit (1);
	}

	printf ("\nParsing %s\n", mkfname (TELEACTSRCFILE));

	for (i = 0; keywords[i].code >= 0; i++)
		nkeywords++;

	while (!feof (fin)) {
		if (!fgets (line, sizeof (line), fin))
			break;
		num++;

		if ((cp = strrchr (line, '\n')) != NULL)
			for (; (*cp == '\n') || (*cp == '\r') || isspace (*cp);
			     cp--)
				*cp = 0;
		for (cp = line; isspace (*cp); cp++);
		if (*cp == '#')
			continue;
		if (!strlen (cp))
			continue;

		if ((sscanf (cp, "%s %n", keyword, &n) != 1))
			continue;

		data = &cp[n];

		if ((k =
		     bsearch (keyword, keywords, nkeywords,
			      sizeof (struct keyword), keycmp)) == NULL) {
			fprintf (stderr, "Line %d: unknown keyword '%s'.\n",
				 num, keyword);
			exit (1);
		}

		switch (k->code) {
		case CODE_VERB:
			if (!first) {
				check (&a);
				addtolist (&a);
				fflush (stdout);
			}
			first = 0;
			memset (&a, 0, sizeof (a));
			if (sscanf (data, "%c %s", &a.s.type, tmp) != 2) {
				fprintf (stderr,
					 "Line %d: bad format for 'verb'.\n",
					 num);
				exit (1);
			} else
			    if (!strchr
				(ACTIONTYPES, a.s.type = toupper (a.s.type))) {
				fprintf (stderr,
					 "Line %d: bad verb type '%c'.\n", num,
					 a.s.type);
				exit (1);
			} else if (verbexists (tmp)) {
				fprintf (stderr,
					 "Line %d: duplicate verb '%s'.\n",
					 num, tmp);
				exit (1);
			}
			a.s.verb = strdup (tmp);
			break;

		case CODE_USER:
			parsein (num, "user", a.s.user, data);
			break;

		case CODE_SIMPLE:
			if (a.s.type == TYPE_SIMPLE)
				parsein (num, "simple", a.s.simple, data);
			else if (a.s.type == TYPE_DOUBLE)
				parsein (num, "simple", a.d.simple, data);
			else if (a.s.type == TYPE_ADVERB)
				parsein (num, "simple", a.a.simple, data);
			else {
				fprintf (stderr,
					 "Line %d: can't use 'simple' for this verb type.\n",
					 num);
				exit (1);
			}
			break;

		case CODE_OTHER:
			if (a.s.type == TYPE_OBJECT)
				parsein (num, "other", a.o.other, data);
			else if (a.s.type == TYPE_DOUBLE)
				parsein (num, "other", a.d.other, data);
			else {
				fprintf (stderr,
					 "Line %d: can't use 'other' for this verb type.\n",
					 num);
				exit (1);
			}
			break;

		case CODE_ALL:
			if (a.s.type == TYPE_OBJECT)
				parsein (num, "all", a.o.all, data);
			else if (a.s.type == TYPE_DOUBLE)
				parsein (num, "all", a.d.all, data);
			else {
				fprintf (stderr,
					 "Line %d: can't use 'all' for this verb type.\n",
					 num);
				exit (1);
			}
			break;

		case CODE_TARGET:
			if (a.s.type == TYPE_OBJECT)
				parsein (num, "target", a.o.target, data);
			else if (a.s.type == TYPE_DOUBLE)
				parsein (num, "target", a.d.target, data);
			else {
				fprintf (stderr,
					 "Line %d: can't use 'target' for this verb type.\n",
					 num);
				exit (1);
			}
			break;

		case CODE_SECRET:
			if (a.s.type == TYPE_OBJECT)
				parsein (num, "secret", a.o.secret, data);
			else if (a.s.type == TYPE_DOUBLE)
				parsein (num, "secret", a.d.secret, data);
			else {
				fprintf (stderr,
					 "Line %d: can't use 'secret' for this verb type.\n",
					 num);
				exit (1);
			}
			break;

		case CODE_ADVERB:
			if (a.s.type == TYPE_ADVERB)
				parsein (num, "adverb", a.a.adverb, data);
			else {
				fprintf (stderr,
					 "Line %d: can't use 'adverb' for this verb type.\n",
					 num);
				exit (1);
			}
			break;

		case CODE_GENERIC:
			if (a.s.type == TYPE_GENERIC)
				parsein (num, "generic", a.g.generic, data);
			else {
				fprintf (stderr,
					 "Line %d: can't use 'generic' for this verb type.\n",
					 num);
				exit (1);
			}
			break;

		case CODE_ACCESS:
			{
				char    tmp2[16384];

				if (a.s.access)
					strcpy (tmp2, a.s.access);
				else
					tmp2[0] = 0;
				for (cp = data; *cp; cp++)
					*cp = toupper (*cp);
				cp = strtok (data, " \t");
				while (cp) {
					sprintf (tmp, "(%s)", cp);
					strcat (tmp2, tmp);
					cp = strtok (NULL, " \t");
				}
				if (a.s.access)
					free (a.s.access);
				a.s.access = strdup (tmp2);
				break;
			}

		case CODE_KEY:
			if (sscanf (data, "%d", &a.s.key) != 1) {
				fprintf (stderr,
					 "Line %d: bad format for 'key'.\n",
					 num);
				exit (1);
			} else if (a.s.key < 0 || a.s.key > 129) {
				fprintf (stderr,
					 "Line %d: key must be 0-129.\n", num);
				exit (1);
			}
			break;
		}
	}

	fclose (fin);

	check (&a);
	addtolist (&a);

	printf ("Sorting.\n\n");
	qsort (actions, verbs, sizeof (union action), verbcmp);

	for (i = 0; i < verbs; i++) {
		printf ((i + 1) % 4 ? "%c%-15s" : "%c%-15s\n",
			actions[i].s.key || actions[i].s.access ? '*' : ' ',
			actions[i].s.verb);
	}
	printf ("\n\n* Locked/Restricted actions\n\n");

	printf ("%s is %d line(s) long and defines %d verb(s).\n\n",
		mkfname (TELEACTSRCFILE), num, verbs);

	printf ("Outputting to %s in MSG format.\n", mkfname (TELEACTMSGFILE));

	fprintf (fout, PREAMBLE, verbs);

	for (i = 0; i < verbs; i++) {
		fprintf (fout, HEADER,
			 i, STRING (actions[i].s.verb),
			 i, actions[i].s.type,
			 i, actions[i].s.key, i, STRING (actions[i].s.access));

		DUMP (USER, actions[i].s.user[n]);

		switch (actions[i].s.type) {
		case TYPE_SIMPLE:
			DUMP (SMPL, actions[i].s.simple[n]);
			break;
		case TYPE_OBJECT:
			DUMP (OTHR, actions[i].o.other[n]);
			DUMP (SALL, actions[i].o.all[n]);
			DUMP (TRGT, actions[i].o.target[n]);
			DUMP (SCRT, actions[i].o.secret[n]);
			break;
		case TYPE_DOUBLE:
			DUMP (SMPL, actions[i].d.simple[n]);
			DUMP (OTHR, actions[i].d.other[n]);
			DUMP (SALL, actions[i].d.all[n]);
			DUMP (TRGT, actions[i].d.target[n]);
			DUMP (SCRT, actions[i].d.secret[n]);
			break;
		case TYPE_ADVERB:
			DUMP (SMPL, actions[i].a.simple[n]);
			DUMP (ADVB, actions[i].a.adverb[n]);
			break;
		case TYPE_GENERIC:
			DUMP (GNRC, actions[i].g.generic[n]);
			break;
		}

		fprintf (fout, FOOTER);
	}

	fclose (fout);

	printf ("\n");
	{
		char    command[256];

		strcpy (command, mkfname ("%s/msgidx ", BINDIR));
		strcat (command, mkfname (TELEACTMSGFILE));
		system (command);
	}
	printf ("\n");

	return 0;
}


/* End of File */
