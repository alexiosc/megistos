/*****************************************************************************\
 **                                                                         **
 **  FILE:      io.c                                                        **
 **  AUTHORS:   Antonis Stamboulis (Xplosion), Vangelis Rokas (Valis)       **
 **  PURPOSE:   Questionnaire module (Polls and Quizzes)                    **
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
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/31 06:59:19  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.3  2000/09/30 09:20:12  bbs
 * using gallup_loaded to determine if a gallup is loaded
 *
 * Revision 1.2  2000/09/28 18:43:55  bbs
 * dummy field is zeroed when saving a new gallup
 * bug fixed in nullupgallup, questions field was not zeroed
 *
 * Revision 1.1  2000/09/27 18:26:25  bbs
 * check magic while loading gallup
 *
 * Revision 1.0  2000/09/21 17:42:35  bbs
 * Initial revision
 *
 * Revision 1.0  2000/09/21 17:27:47  bbs
 * Initial revision
 *
 */


static const char rcsinfo[] =
    "$Id$";

/* Gallops input/output functions */

#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>


#include "bbs.h"
#include "mbk_gallups.h"
#include "gallups.h"

int     gallup_loaded = 0;

int
outputcharp (char *charp, FILE * filep)
{

	unsigned int i = strlen (charp) + 1;
	if (fwrite (&i, sizeof (unsigned int), 1, filep) != 1) {
		prompt (OOPS);
		return 0;
	}
	if (fwrite (charp, sizeof (char), i, filep) != i) {
		prompt (OOPS);
		return 0;
	}
	return 1;

}

int
inputcharp (char **charp, FILE * filep)
{

	unsigned int i;

	if (fread (&i, sizeof (unsigned int), 1, filep) != 1) {
		prompt (OOPS);
		return 0;
	}
	*charp = (char *) alcmem (sizeof (char) * i);
	if (fread (*charp, sizeof (char), i, filep) != i) {
		prompt (OOPS);
		return 0;
	}
	return 1;

}

#ifndef __GSC__

int
loadgallup (char *fn, struct gallup *gallp)
{
	char    filename[128];

	sprintf (filename, "%s/%s/%s", GALLUPSDIR, fn, GDATAFILE);

	return _loadgallup (filename, fn, gallp);
}

#endif


int
_loadgallup (char *filename, char *fn, struct gallup *gallp)
{
	FILE   *fp;
	unsigned int i;
	struct question *q;
	struct answer *a;

	ginfo = gallp;


	if (gallup_loaded)
		freegallup ();

	strcpy (gfnam (ginfo), fn);

	fp = fopen (filename, "r");
	if (fp == NULL) {
		prompt (OOPS);
		return 0;
	}


	if (fread (ginfo, sizeof (struct gallup), 1, fp) != 1) {
		prompt (OOPS);
		return 0;
	}

	if (memcmp (ginfo->magic, GAL_MAGIC, 4)) {
		prompt (OOPSMAGIC);
		return 0;
	}

	questions =
	    (struct question *) alcmem (sizeof (struct question) *
					gnumq (ginfo));

	nullupgallup ();

	if (gflgs (ginfo) & GF_QUIZ) {
		answers =
		    (struct answer *) alcmem (sizeof (struct answer) *
					      gnumq (ginfo));
	}


	for (i = 0; i < gnumq (ginfo); i++) {
		q = &questions[i];

		fread (&qtyp (q), sizeof (unsigned char), 1, fp);
		fread (&qflg (q), sizeof (unsigned int), 1, fp);

		if (gflgs (ginfo) & GF_QUIZ) {
			fread (&qcrd0 (q), sizeof (int), 1, fp);
			fread (&qcrd1 (q), sizeof (int), 1, fp);
		}

		inputcharp (&qprm (q), fp);

		switch (qtyp (q)) {
		case GQ_NUMBER:
			fread (&qnummn (q), sizeof (int), 1, fp);
			fread (&qnummx (q), sizeof (int), 1, fp);
			break;
		case GQ_FREETEXT:
			fread (&qtxtln (q), sizeof (int), 1, fp);
			break;
		case GQ_SELECT:
			inputcharp (&qseldt (q), fp);
			break;

		case GQ_COMBO:
			inputcharp (&qcomdt (q), fp);
			inputcharp (&qcompr (q), fp);
			inputcharp (&qcomch (q), fp);
			break;
		}

		if (gflgs (ginfo) & GF_QUIZ) {
			a = qans (q) = malloc (sizeof (struct answer));
			switch (qtyp (q)) {
			case GQ_NUMBER:
				fread (&anumdt (a), sizeof (int), 1, fp);
				break;
			case GQ_FREETEXT:
				inputcharp (&atxtdt (a), fp);
				break;
			case GQ_SELECT:
				fread (&aseldt (a), sizeof (int), 1, fp);
				break;
			}
		}
	}

	fclose (fp);

	gallup_loaded = 1;

	setupgallup ();

	return 1;
}

long
today ()
{
	struct tm *dt;
	time_t  t;

	t = time (0);
	dt = localtime (&t);
	return ((dt->tm_mday) & 0x1f) | ((dt->
					  tm_mon) << 8) | (((dt->tm_year -
							     70) & 0xff) <<
							   16);
}


long
now ()
{
	struct tm *dt;
	time_t  t;

	t = time (0);
	dt = localtime (&t);
	return maketime (dt->tm_hour, dt->tm_min, dt->tm_sec);
}


#ifndef __GSC__

/* this is an alternate entry point to _savegallup() */
int
savegallup (void)
{
	char    filename[128];

	sprintf (filename, "%s/%s/%s", GALLUPSDIR, gfnam (ginfo), GDATAFILE);

	return _savegallup (filename);
}

#endif



int
_savegallup (char *filename)
{
	FILE   *fp;
	unsigned int i;
	struct question *q;
	struct answer *a;


#ifndef __GSC__
	if (!gallup_loaded) {
		prompt (NOGALSEL);
		return 0;
	}
#endif

	fp = fopen (filename, "w");
	if (!fp) {
		prompt (OOPS);
		return 0;
	}

	memcpy (ginfo->magic, GAL_MAGIC, 4);
	memset (ginfo->dummy, 0, sizeof (ginfo->dummy));	// clear dummy field for future use

	if (fwrite (ginfo, sizeof (struct gallup), 1, fp) != 1) {
		prompt (OOPS);
		return 0;
	}

	for (i = 0; i < gnumq (ginfo); i++) {

		q = &questions[i];
		fwrite (&qtyp (q), sizeof (unsigned char), 1, fp);
		fwrite (&qflg (q), sizeof (unsigned int), 1, fp);

		if (gflgs (ginfo) & GF_QUIZ) {
			fwrite (&qcrd0 (q), sizeof (int), 1, fp);
			fwrite (&qcrd1 (q), sizeof (int), 1, fp);
		}

		outputcharp (qprm (q), fp);

		switch (qtyp (q)) {
		case GQ_NUMBER:
			fwrite (&qnummn (q), sizeof (int), 1, fp);
			fwrite (&qnummx (q), sizeof (int), 1, fp);
			break;
		case GQ_FREETEXT:
			fwrite (&qtxtln (q), sizeof (int), 1, fp);
			break;
		case GQ_SELECT:
			outputcharp (qseldt (q), fp);
			break;
		case GQ_COMBO:
			outputcharp (qcomdt (q), fp);
			outputcharp (qcompr (q), fp);
			outputcharp (qcomch (q), fp);
			break;
		}

		if (gflgs (ginfo) & GF_QUIZ) {
			a = qans (q);
			switch (qtyp (q)) {
			case GQ_NUMBER:
				fwrite (&anumdt (a), sizeof (int), 1, fp);
				break;
			case GQ_FREETEXT:
				outputcharp (atxtdt (a), fp);
				break;
			case GQ_SELECT:
				fwrite (&aseldt (a), sizeof (int), 1, fp);
				break;
			}
		}
	}

	fclose (fp);
	return 1;
}


/* free a gallup questions/answers list */
void
freegallup (void)
{
	unsigned int i;
	struct question *q;
	struct answer *a;

	if (gallup_loaded) {
		for (i = 0; i < gnumq (ginfo); i++) {
			q = &questions[i];

			if (qprm (q))
				free (qprm (q));
			switch (qtyp (q)) {
			case GQ_SELECT:
				if (qseldt (q))
					free (qseldt (q));
				break;
			case GQ_COMBO:
				if (qcomdt (q))
					free (qcomdt (q));
				if (qcompr (q))
					free (qcompr (q));
				if (qcomch (q))
					free (qcomch (q));
				break;
			}

			if (gflgs (ginfo) & GF_QUIZ) {
				a = qans (q);
				switch (qtyp (q)) {
				case GQ_FREETEXT:
					if (atxtdt (a))
						free (atxtdt (a));
					break;
				}
			}
		}

		free (questions);
	}

	questions = NULL;
	answers = NULL;

	gallup_loaded = 0;

	strcpy (gdesc (ginfo), "");
	strcpy (gfnam (ginfo), "");
}


/* new version */
void
nullupgallup (void)
{
	unsigned int i;

	for (i = 0; i < gnumq (ginfo); i++) {
		qprm (&questions[i]) = NULL;
	}
}




/* parses string STR, places a \0 at each \n and allocates idx to point at 
   the beginning of each substring */
void
splitstring (char *str, char ***idx, int *cnt)
{
	int     i = 0;
	char   *ct1, *ct2;

	ct1 = str;
	while (ct1) {
		ct1 = strchr (ct1, '\n');
		if (ct1)
			i++;
		else
			break;
		ct1++;
	}

	*cnt = i;

	*idx = malloc (sizeof (char *) * i);
	ct1 = ct2 = str;
	i = 0;
	while (ct1) {
		while (*ct2 && *ct2 != '\n')
			ct2++;
		if (!(*ct2))
			break;

		(*idx)[i++] = ct1;
		*ct2 = '\0';

		ct1 = ++ct2;
	}
}

void
setupgallup (void)
{
	int     i;
	struct question *q;

	for (i = 0; i < gnumq (ginfo); i++) {
		q = &questions[i];
		switch (qtyp (q)) {
		case GQ_SELECT:
			splitstring (qseldt (q), &qseldataidx (q),
				     &qseldatacnt (q));
			break;
		case GQ_COMBO:
			splitstring (qcomdt (q), &qcomdataidx (q),
				     &qcomdatacnt (q));
			splitstring (qcompr (q), &qcompromidx (q),
				     &qcompromcnt (q));
			break;
		}
	}
}


/* End of File */
