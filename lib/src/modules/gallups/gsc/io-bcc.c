/*****************************************************************************\
 **                                                                         **
 **  FILE:      io.c                                                        **
 **  AUTHORS:   Antonis Stamboulis (Xplosion), Vangelis Rokas (Valis)       **
 **  PURPOSE:   Gallups Script Compiler                                     **
 **  NOTES:     This file is specific for Borland C                         **
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
 * Revision 1.4  2003/12/31 06:59:19  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  2000/09/27 18:35:06  bbs
 * *** empty log message ***
 *
 * Revision 1.0  2000/09/21 18:15:30  bbs
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <megistos/gallups.h>

int
outputcharp (char *charp, FILE * filep)
{

	unsigned int i = strlen (charp) + 1;
	if (fwrite (&i, sizeof (unsigned int), 1, filep) != 1)
		return 0;
	if (fwrite (charp, sizeof (char), i, filep) != i)
		return 0;
	return 1;

}

int
inputcharp (char **charp, FILE * filep)
{

	unsigned int i;

	if (fread (&i, sizeof (unsigned int), 1, filep) != 1)
		return 0;
	*charp = (char *) malloc (sizeof (char) * i);
	if (fread (*charp, sizeof (char), i, filep) != i)
		return 0;
	return 1;

}

int
loadgallup (char *fn, struct gallup *gallp)
{
	char    filename[128];

	sprintf (filename, "%s/%s/%s", GALLUPSDIR, fn, GDATAFILE);

	return _loadgallup (filename, fn, gallp);
}

int
_loadgallup (char *filename, char *fn, struct gallup *gallp)
{
	FILE   *fp;
	unsigned int i;
	struct question *q;
	struct answer *a;

	ginfo = gallp;

	if (questions)
		freegallup ();

//      sprintf(filename, "%s/%s/DATA", GALLUPSDIR, fn);
	strcpy (gfnam (ginfo), fn);

	fp = fopen (filename, "r");
	if (fp == NULL)
		return 0;

	if (fread (ginfo, sizeof (struct gallup), 1, fp) != 1)
		return 0;

	questions =
	    (struct question *) malloc (sizeof (struct question) *
					gnumq (ginfo));

	if (gflgs (ginfo) & GF_QUIZ) {
		answers =
		    (struct answer *) malloc (sizeof (struct answer) *
					      gnumq (ginfo));
	}

	nullupgallup ();

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

	setupgallup ();
	return 1;
}


int
_savegallup (char *filename)
{
	FILE   *fp;
	unsigned int i;
	struct question *q;
	struct answer *a;

	if (!questions)
		return 0;

	fp = fopen (filename, "w");
	if (!fp)
		return 0;

	if (fwrite (ginfo, sizeof (struct gallup), 1, fp) != 1)
		return 0;

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

/* this is an alternate entry point to _savegallup() */
int
savegallup (void)
{
	char    filename[128];

	sprintf (filename, "%s/%s/%s", GALLUPSDIR, gfnam (ginfo), GDATAFILE);

	return _savegallup (filename);
}

/* free a gallup questions/answers list */
void
freegallup (void)
{
	unsigned int i;
	struct question *q;
	struct answer *a;

	if (questions) {
		for (i = 0; i < gnumq (ginfo); i++) {
			q = &questions[i];
			if (answers)
				a = &answers[i];
			else
				a = NULL;

			if (qprm (q))
				free (qprm (q));
			switch (qtyp (q)) {
			case GQ_FREETEXT:
				if (a)
					free (atxtdt (a));
				break;
			case GQ_SELECT:
				free (qseldt (q));
				break;
			case GQ_COMBO:
				free (qcomdt (q));
				free (qcompr (q));
				free (qcomch (q));
				if (a)
					free (acomdt (a));
				break;
			}

			if (gflgs (ginfo) & GF_QUIZ) {
				a = qans (q);
				switch (qtyp (q)) {
				case GQ_FREETEXT:
					free (atxtdt (a));
					break;
				}
			}
		}

	}

	questions = NULL;

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
