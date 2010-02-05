/*****************************************************************************\
 **                                                                         **
 **  FILE:      gallups.c                                                   **
 **  AUTHORS:   Antonis Stamboulis (Xplosion)                               **
 **  PURPOSE:   Questionnaire module                                        **
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
 * $Id: gallups.c,v 2.0 2004/09/13 19:44:52 alexios Exp $
 *
 * $Log: gallups.c,v $
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.3  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 *
 */


static const char rcsinfo[] =
    "$Id: gallups.c,v 2.0 2004/09/13 19:44:52 alexios Exp $";


#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>


#include <megistos/bbs.h>
#include <megistos/mbk_gallups.h>
#include <megistos/gallups.h>


promptblock_t *msg;
struct question *poll = NULL;

int     entrykey;
int     crkey;

void
init ()
{
	mod_init (INI_ALL);
	msg = msg_open ("gallups");
	msg_setlanguage (thisuseracc.language);

	entrykey = msg_int (ENTRYKEY, 0, 129);
	crkey = msg_int (CRKEY, 0, 129);
}

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

void
freegallup (void)
{

	unsigned int i;

	if (poll) {
		for (i = 0; i < pollinfo.numquestions; i++) {
			if (poll[i].chorep)
				free (poll[i].chorep);
			if (poll[i].text)
				free (poll[i].text);
		}
		free (poll);
	}
	poll = NULL;
	if (pollinfo.description)
		free (pollinfo.description);
	pollinfo.filename[0] = '\0';

}

void
nullupgallup (void)
{

	unsigned int i;

	for (i = 0; i < pollinfo.numquestions; i++)
		poll[i].chorep = poll[i].text = NULL;

}

int
savegallup (void)
{

	char    filename[256];
	FILE   *dat;
	unsigned int i;

	if (poll == NULL) {
		prompt (NOGALSEL);
		return 0;
	}

	sprintf (filename, GALLUPSDIR "/%s.dat", pollinfo.filename);
	dat = fopen (filename, "w");
	if (dat == NULL) {
		prompt (OOPS);
		return 0;
	}

	if (!outputcharp (pollinfo.description, dat))
		return 0;
	if (fwrite (&pollinfo.numquestions, sizeof (unsigned int), 1, dat) !=
	    1) {
		prompt (OOPS);
		return 0;
	}
	if (fwrite (&pollinfo.flags, sizeof (char), 1, dat) != 1) {
		prompt (OOPS);
		return 0;
	}

	for (i = 0; i < pollinfo.numquestions; i++) {
		if (fwrite (&poll[i].qtype, sizeof (unsigned int), 1, dat) !=
		    1) {
			prompt (OOPS);
			return 0;
		}
		switch (poll[i].qtype & 3) {
		case GQ_NUMBER:
		case GQ_FREETEXT:
			if (!outputcharp (poll[i].text, dat))
				return 0;
			break;
		case GQ_CHOICES_SINGLE:
		case GQ_CHOICES_MULTIPLE:
			if (!outputcharp (poll[i].text, dat))
				return 0;
			if (!outputcharp (poll[i].chorep, dat))
				return 0;
			break;
		}
	}

	fclose (dat);
	return 1;

}

int
loadgallup (char *fn)
{

	char    filename[256];
	FILE   *dat;
	unsigned int i;

	if (poll != NULL)
		freegallup ();

	sprintf (filename, GALLUPSDIR "/%s.dat", fn);
	strcpy (pollinfo.filename, fn);
	dat = fopen (filename, "r");
	if (dat == NULL) {
		prompt (OOPS);
		return 0;
	}

	if (!inputcharp (&pollinfo.description, dat))
		return 0;
	if (fread (&pollinfo.numquestions, sizeof (unsigned int), 1, dat) != 1) {
		prompt (OOPS);
		return 0;
	}
	if (fread (&pollinfo.flags, sizeof (char), 1, dat) != 1) {
		prompt (OOPS);
		return 0;
	}

	poll =
	    (struct question *) alcmem (sizeof (struct question) *
					pollinfo.numquestions);
	nullupgallup ();

	for (i = 0; i < pollinfo.numquestions; i++) {
		if (fread (&poll[i].qtype, sizeof (unsigned int), 1, dat) != 1) {
			prompt (OOPS);
			return 0;
		}
		switch (poll[i].qtype & 3) {
		case GQ_NUMBER:
		case GQ_FREETEXT:
			if (!inputcharp (&poll[i].text, dat))
				return 0;
			poll[i].chorep = NULL;
			break;
		case GQ_CHOICES_SINGLE:
		case GQ_CHOICES_MULTIPLE:
			if (!inputcharp (&poll[i].text, dat))
				return 0;
			if (!inputcharp (&poll[i].chorep, dat))
				return 0;
			break;
		}
	}

	fclose (dat);
	return 1;

}



char   *
listandselectpoll (void)
{

	FILE   *pipe, *pollf;
	char    temp1[256], temp2[256], *dscr, **galfiles;
	unsigned int galnum = 0, availgal = 0, i;

	sprintf (temp1, "\\ls %s/ | grep dat$", GALLUPSDIR);

	pipe = popen (temp1, "r");
	if (pipe == NULL) {
		prompt (NOGALEXIST);
		return "";
	}
	while (fscanf (pipe, "%s", temp2) == 1)
		availgal++;
	pclose (pipe);

	if (!availgal) {
		prompt (NOGALEXIST);
		return "";
	}
	galfiles = (char **) alcmem (sizeof (char *) * availgal);
	for (i = 0; i < availgal; i++)
		galfiles[i] = (char *) alcmem (sizeof (char) * GI_MAXFNLEN);

	pipe = popen (temp1, "r");
	if (pipe == NULL) {
		prompt (NOGALEXIST);
		return "";
	}

	inp_nonblock ();
	fmt_lastresult = 0;

	prompt (SELGALHEAD);

	while (fscanf (pipe, "%s", temp1) == 1) {
		galnum++;
		*(strrchr (temp1, '.')) = '\0';
		strncpy (galfiles[galnum - 1], temp1, GI_MAXFNLEN - 1);
		galfiles[galnum - 1][GI_MAXFNLEN - 1] = '\0';
		sprintf (temp2, GALLUPSDIR "/%s.dat", temp1);
		pollf = fopen (temp2, "r");
		if (!pollf) {
			prompt (OOPS);
			return "";
		}
		if (!inputcharp (&dscr, pollf))
			return "";
		fclose (pollf);
		prompt (SELGALLIST, galnum, galfiles[galnum - 1], dscr);
		if (fmt_lastresult == PAUSE_QUIT)
			break;
		free (dscr);
	}
	prompt (SELGALFOOT);
	inp_block ();

	pclose (pipe);

	if (!get_number (&galnum, SELGALPROMPT, 1, availgal, SELERR, 0, 0))
		return "";

	strcpy (temp1, galfiles[galnum - 1]);

	for (i = 0; i < availgal; i++)
		free (galfiles[i]);
	free (galfiles);

	cnc_end ();

	dscr = (char *) alcmem (sizeof (char) * 11);
	strcpy (dscr, temp1);
	return (dscr);

}

void
selectpoll (void)
{

	char    fn[11];

	strcpy (fn, listandselectpoll ());

	if (fn[0] == '\0')
		return;

	if (!loadgallup (fn)) {
		prompt (OOPS);
		if (poll != NULL)
			free (poll);
		return;
	}

}

int
numchoices (unsigned int q)
{

	char   *ct1, *ct2;
	int     cn;

	ct1 = poll[q].chorep;
	cn = 0;
	while (cn < MAXCHOICES) {
		for (; *ct1 == 32; ct1++);
		for (ct2 = ct1; *ct2 != '\n' && *ct2 != '\0'; ct2++);
		if (ct2 != ct1)
			cn++;
		else
			break;
		if (*ct2 == '\0')
			break;
		ct1 = ct2 + 1;
	}
	return cn;
}

void
addtosubmitted (char *id)
{

	FILE   *sub;
	char    filename[256], usersub[24];

	sprintf (filename, GALLUPSDIR "/%s.sub", pollinfo.filename);
	sub = fopen (filename, "a");
	strcpy (usersub, id);
	fwrite (usersub, sizeof (char), 24, sub);
	fclose (sub);

}

int
submitted (char *id)
{

	FILE   *sub;
	char    filename[256], usersub[24], c = 0;

	sprintf (filename, GALLUPSDIR "/%s.sub", pollinfo.filename);
	sub = fopen (filename, "r");
	if (sub)
		while (fread (usersub, sizeof (char), 24, sub) == 24 && !c)
			if (!strcmp (usersub, id))
				c = 1;
	return (c);

}

void
saveans ()
{

	FILE   *rsl, *tmp;
	char    tempfile[256], filename[256], c, **freetext;
	unsigned int multiple[30], temp, i, l, *times, k;

	sprintf (filename, GALLUPSDIR "/%s.rsl", pollinfo.filename);
	sprintf (tempfile, TMPDIR "/gallups%d", getpid ());

	rsl = fopen (filename, "r");
	tmp = fopen (tempfile, "w");

	if (tmp == NULL) {
		prompt (OOPS);
		return;
	}
	if (rsl) {
		if (fread (&temp, sizeof (unsigned int), 1, rsl) != 1) {
			prompt (OOPS);
			return;
		}
		temp++;
	} else
		temp = 1;
	if (fwrite (&temp, sizeof (unsigned int), 1, tmp) != 1) {
		prompt (OOPS);
		return;
	}

	for (i = 0; i < pollinfo.numquestions; i++) {

		switch (poll[i].qtype & 3) {

		case GQ_CHOICES_SINGLE:
		case GQ_CHOICES_MULTIPLE:

			temp = numchoices (i);

			for (l = 0; l < temp; l++)
				multiple[l] = 0;
			if (rsl)
				if (fread
				    (multiple, sizeof (unsigned int), temp,
				     rsl) != temp) {
					prompt (OOPS);
					return;
				}

			for (l = 0; l < temp; l++)
				if (poll[i].qtype & (1 << (l + 2)))
					multiple[l]++;
			if (fwrite (multiple, sizeof (unsigned int), temp, tmp)
			    != temp) {
				prompt (OOPS);
				return;
			}

			break;

		case GQ_NUMBER:
		case GQ_FREETEXT:

			if ((poll[i].qtype & 3) == GQ_FREETEXT)
				k = ((poll[i].qtype >> 2) + 1);
			else
				k = (2 << sizeof (int)) + 1;

			if (rsl) {

				c = 0;
				if (fread
				    (&temp, sizeof (unsigned int), 1,
				     rsl) != 1) {
					prompt (OOPS);
					return;
				}
				freetext =
				    (char **) alcmem (sizeof (char *) * temp);
				times =
				    (unsigned int *)
				    alcmem (sizeof (unsigned int) * temp);
				for (l = 0; l < temp; l++)
					freetext[l] =
					    (char *) alcmem (sizeof (char) *
							     k);
				for (l = 0; l < temp; l++) {
					if (fread
					    (&times[l], sizeof (unsigned int),
					     1, rsl) != 1) {
						prompt (OOPS);
						return;
					}
					if (fread
					    (freetext[l], sizeof (char) * k, 1,
					     rsl) != 1) {
						prompt (OOPS);
						return;
					}
					if (!strcmp
					    (freetext[l], poll[i].chorep)) {
						times[l]++;
						c = 1;
					}
				}
				if (c == 0)
					temp++;
				if (fwrite
				    (&temp, sizeof (unsigned int), 1,
				     tmp) != 1) {
					prompt (OOPS);
					return;
				}
				for (l = 0; l < temp - (c == 0); l++) {
					if (fwrite
					    (&times[l], sizeof (unsigned int),
					     1, tmp) != 1) {
						prompt (OOPS);
						return;
					}
					if (fwrite
					    (freetext[l], sizeof (char) * k, 1,
					     tmp) != 1) {
						prompt (OOPS);
						return;
					}
					free (freetext[l]);
				}
				if (c == 0) {
					temp = 1;
					if (fwrite
					    (&temp, sizeof (unsigned int), 1,
					     tmp) != 1) {
						prompt (OOPS);
						return;
					}
					if (fwrite
					    (poll[i].chorep, sizeof (char) * k,
					     1, tmp) != 1) {
						prompt (OOPS);
						return;
					}
				}

				free (times);
				free (freetext);

			} else {

				temp = 1;
				if (fwrite
				    (&temp, sizeof (unsigned int), 1,
				     tmp) != 1) {
					prompt (OOPS);
					return;
				}
				if (fwrite
				    (&temp, sizeof (unsigned int), 1,
				     tmp) != 1) {
					prompt (OOPS);
					return;
				}
				if (fwrite
				    (poll[i].chorep, sizeof (char) * k, 1,
				     tmp) != 1) {
					prompt (OOPS);
					return;
				}

			}

			break;

		}

	}

	fclose (tmp);
	if (rsl)
		fclose (rsl);
	if (fcopy (tempfile, filename)) {
		prompt (OOPS);
		return;
	}
	unlink (tempfile);
	if (!(pollinfo.flags & GF_MULTISUBMIT))
		addtosubmitted (thisuseracc.userid);

}



void
takepoll ()
{

	unsigned int i = 0, cn, sel, len, l;
	char   *ct1, *ct2, *ct3;

	if (poll == NULL) {
		prompt (NOGALSEL);
		return;
	}

	if (!(pollinfo.flags & GF_MULTISUBMIT) &&
	    submitted (thisuseracc.userid)) {
		prompt (ALREADYSUB);
		return;
	}

	inp_nonblock ();
	thisuseronl.flags |= OLF_BUSY;

	for (i = 0; i < pollinfo.numquestions; i++) {

		fmt_lastresult = 0;

		switch (poll[i].qtype & 3) {

		case GQ_NUMBER:
			print (poll[i].text);
			cnc_end ();
			if (!get_number (&sel, NUMBERINP,
					 (poll[i].
					  qtype & GN_MASKMIN) >> GN_MINSHIFT,
					 (poll[i].
					  qtype & GN_MASKMAX) >> GN_MAXSHIFT,
					 SELERR, 0, 0)) {
				inp_block ();
				return;
			}
			poll[i].chorep =
			    (char *) alcmem (sizeof (char) *
					     ((2 << sizeof (int)) + 1));
			sprintf (poll[i].chorep, "%d", sel);
			break;

		case GQ_FREETEXT:
			for (;;) {
				print (poll[i].text);
				bzero (inp_buffer, MAXINPLEN + 1);
				inp_get (poll[i].qtype >> 2);
				poll[i].chorep =
				    (char *) alcmem (sizeof (char) *
						     ((poll[i].qtype >> 2) +
						      1));
				inp_raw ();
				strcpy (poll[i].chorep, inp_buffer);
				if (inp_isX (poll[i].chorep)) {
					inp_block ();
					return;
				}
				if (!strlen (poll[i].chorep)) {
					cnc_end ();
					continue;
				}
				cnc_end ();
				break;
			}
			phonetic (poll[i].chorep);
			break;

		case GQ_CHOICES_SINGLE:
			len = 0;
			print (poll[i].text);
			ct1 = poll[i].chorep;
			cn = 0;
			while (cn < MAXCHOICES) {
				len = 0;
				for (; *ct1 == 32; ct1++);
				for (l = 0, ct2 = ct1;
				     *ct2 != '\n' && *ct2 != '\0'; ct2++, l++);
				if (ct2 != ct1) {
					cn++;
					prompt (MCHEADER, cn);
				} else
					break;
				ct3 =
				    (char *) alcmem (sizeof (char) * (l + 2));
				while (ct1 < ct2) {
					ct3[len] = *ct1;
					ct1++;
					len++;
				}
				ct3[len] = '\n';
				ct3[++len] = '\0';
				print (ct3);
				free (ct3);
				if (*ct2 == '\0')
					break;
				ct1 = ct2 + 1;
			}
			cnc_end ();
			if (!get_number (&sel, SINGLESEL, 1, cn, SELERR, 0, 0)) {
				inp_block ();
				return;
			}
			poll[i].qtype = (1 << (sel + 1)) | GQ_CHOICES_SINGLE;
			break;

		case GQ_CHOICES_MULTIPLE:
			print (poll[i].text);
			poll[i].qtype = GQ_CHOICES_MULTIPLE;
			ct1 = poll[i].chorep;
			cn = 0;
			while (cn < MAXCHOICES) {
				for (; *ct1 == 32; ct1++);
				for (l = 0, ct2 = ct1;
				     *ct2 != '\n' && *ct2 != '\0'; ct2++, l++);
				len = 0;
				if (ct2 != ct1) {
					cn++;
					prompt (MCHEADER, cn);
				} else
					break;
				ct3 =
				    (char *) alcmem (sizeof (char) * (l + 1));
				while (ct1 < ct2) {
					ct3[len] = *ct1;
					ct1++;
					len++;
				}
				ct3[len] = '\0';
				cnc_end ();
				print (ct3);
				free (ct3);
				if (!get_bool (&sel, MULTISEL, SELERR, 0, 0)) {
					inp_block ();
					return;
				}
				poll[i].qtype |= sel << (cn + 1);
				if (*ct2 == '\0')
					break;
				ct1 = ct2 + 1;
			}
			break;

		}

	}

	if (i == pollinfo.numquestions) {
		prompt (THANKS);
		saveans ();
	}
	inp_block ();

}

void
viewresults ()
{

	FILE   *rsl;
	unsigned int i, l, numsub, t1, t2, multiple[30], k;
	char    filename[256], *freetext, *ct1, *ct2;

	if (poll == NULL) {
		prompt (NOGALSEL);
		return;
	}
	if (!
	    (pollinfo.flags & GF_VIEWRESALL ||
	     key_owns (&thisuseracc, crkey))) {
		prompt (NOPERMRES);
		return;
	}

	sprintf (filename, GALLUPSDIR "/%s.rsl", pollinfo.filename);
	rsl = fopen (filename, "r");
	if (rsl == NULL) {
		prompt (NORESULTS);
		return;
	}

	if (fread (&numsub, sizeof (unsigned int), 1, rsl) != 1) {
		prompt (OOPS);
		return;
	}

	for (i = 0; i < pollinfo.numquestions; i++) {
		fmt_lastresult = 0;
		switch (poll[i].qtype & 3) {
		case GQ_NUMBER:
		case GQ_FREETEXT:
			print (poll[i].text);
			prompt (RESQFTHEAD);
			if (fmt_lastresult == PAUSE_QUIT)
				return;
			if ((poll[i].qtype & 3) == GQ_FREETEXT)
				k = (poll[i].qtype >> 2) + 1;
			else
				k = (2 << sizeof (int)) + 1;
			freetext = (char *) alcmem (sizeof (char) * k);
			if (fread (&t1, sizeof (unsigned int), 1, rsl) != 1) {
				prompt (OOPS);
				return;
			}
			for (l = 0; l < t1; l++) {
				if (fread (&t2, sizeof (unsigned int), 1, rsl)
				    != 1) {
					prompt (OOPS);
					return;
				}
				if (fread (freetext, sizeof (char), k, rsl) !=
				    k) {
					prompt (OOPS);
					return;
				}
				prompt (RESQFREETEXT, freetext, t2, numsub,
					(float) (t2 * 100) / (float) (numsub));
				if (fmt_lastresult == PAUSE_QUIT) {
					prompt (RESQFTFOOT);
					return;
				}
			}
			prompt (RESQFTFOOT);
			free (freetext);
			break;

		case GQ_CHOICES_MULTIPLE:
		case GQ_CHOICES_SINGLE:
			print (poll[i].text);
			prompt (RESQMCHEAD);
			if (fmt_lastresult == PAUSE_QUIT)
				return;
			ct1 = poll[i].chorep;
			t1 = 0;
			t2 = numchoices (i);
			if (fread (multiple, sizeof (unsigned int), t2, rsl) !=
			    t2) {
				prompt (OOPS);
				return;
			}
			while (t1 < MAXCHOICES) {
				l = 0;
				for (; *ct1 == 32; ct1++);
				for (ct2 = ct1; *ct2 != '\n' && *ct2 != '\0';
				     ct2++, l++);
				if (ct2 != ct1)
					t1++;
				else {
					prompt (RESQMCFOOT);
					break;
				}
				freetext =
				    (char *) alcmem ((l + 1) * sizeof (char));
				l = 0;
				while (ct1 < ct2) {
					freetext[l] = *ct1;
					ct1++;
					l++;
				}
				freetext[l] = '\0';
				prompt (RESQMCHOICES, t1, freetext,
					multiple[t1 - 1], numsub,
					(float) (multiple[t1 - 1] * 100) /
					(float) numsub);
				if (fmt_lastresult == PAUSE_QUIT) {
					prompt (RESQMCFOOT);
					break;
				}
				free (freetext);
				if (*ct2 == '\0') {
					prompt (RESQMCFOOT);
					break;
				}
				ct1 = ct2 + 1;
			}
			break;

		}
	}

}


char   *
getstringff (FILE * filep, int allow_newlines)
{

	char    c, *stringp;
	long int pos;
	unsigned int endsigns = 0, len = 0;

	do
		if (fscanf (filep, "%c", &c) != 1)
			return NULL;
	while (c != '\n');

	if (!allow_newlines) {
		do
			if (fscanf (filep, "%c", &c) != 1)
				return NULL;
		while (c == '\n' || c == '\t' || c == ' ');
		if (fseek (filep, -1, SEEK_CUR))
			return NULL;
	}

	pos = ftell (filep);
	if (pos == -1)
		return NULL;

	while (fscanf (filep, "%c", &c) == 1) {
		len++;
		if (c == '#')
			endsigns++;
		else if (!allow_newlines && c == '\n')
			len--;
		else
			endsigns = 0;
		if (endsigns == 3) {
			len -= 2;
			break;
		}
	}

	if (endsigns != 3)
		return NULL;

	stringp = (char *) alcmem (sizeof (char) * len);
	if (fseek (filep, pos, SEEK_SET))
		return NULL;

	endsigns = 0;

	while (endsigns + 1 < len && fscanf (filep, "%c", &c) == 1) {
		if (allow_newlines || c != '\n') {
			stringp[endsigns] = c;
			endsigns++;
		}
	}
	stringp[endsigns] = '\0';

	for (endsigns = 0; endsigns < 3; endsigns++)
		if (fscanf (filep, "%c", &c) != 1)
			return NULL;

	return stringp;

}

int
scriptcompiler (char *script)
{

	FILE   *scr;
	unsigned int i, t1, t2;
	char    c, *charp;

	scr = fopen (script, "r");
	if (!scr) {
		prompt (OOPS);
		return 0;
	}

	do
		if (fscanf (scr, "%c", &c) != 1) {
			prompt (SCRIPTERR);
			return 0;
		}
	while (c == '\n' || c == '\t' || c == ' ' || c < '0' || c > '9');
	if (fseek (scr, -1, SEEK_CUR)) {
		prompt (SCRIPTERR);
		return 0;
	}
	if (fscanf (scr, "%u", &pollinfo.numquestions) != 1) {
		prompt (SCRIPTERR);
		return 0;
	}

	poll =
	    (struct question *) alcmem (sizeof (struct question) *
					pollinfo.numquestions);
	nullupgallup ();

	if (!(charp = getstringff (scr, 0))) {
		prompt (SCRIPTERR);
		return 0;
	}
	pollinfo.description =
	    (char *) alcmem (sizeof (char) * (strlen (charp) + 30));
	sprintf (pollinfo.description, "%s (%s)", charp, thisuseracc.userid);
	free (charp);

	for (i = 0; i < pollinfo.numquestions; i++) {

		do
			if (fscanf (scr, "%c", &c) != 1) {
				prompt (SCRIPTERR);
				return 0;
			}
		while (c == '\n' || c == '\t' || c == ' ' || c < '0' ||
		       c > '9');
		if (fseek (scr, -1, SEEK_CUR)) {
			prompt (SCRIPTERR);
			return 0;
		}
		if (fscanf (scr, "%u", &t1) != 1 || (--t1) > 3) {
			prompt (SCRIPTERR);
			return 0;
		}

		switch (t1) {

		case 0:
			poll[i].qtype = GQ_NUMBER;

			do
				if (fscanf (scr, "%c", &c) != 1) {
					prompt (SCRIPTERR);
					return 0;
				}
			while (c == '\n' || c == '\t' || c == ' ' || c < '0' ||
			       c > '9');
			if (fseek (scr, -1, SEEK_CUR)) {
				prompt (SCRIPTERR);
				return 0;
			}
			if (fscanf (scr, "%u", &t1) != 1) {
				prompt (SCRIPTERR);
				return 0;
			}

			do
				if (fscanf (scr, "%c", &c) != 1) {
					prompt (SCRIPTERR);
					return 0;
				}
			while (c == '\n' || c == '\t' || c == ' ' || c < '0' ||
			       c > '9');
			if (fseek (scr, -1, SEEK_CUR)) {
				prompt (SCRIPTERR);
				return 0;
			}
			if (fscanf (scr, "%u", &t2) != 1) {
				prompt (SCRIPTERR);
				return 0;
			}

			if (t1 > t2) {
				poll[i].qtype |= t1 << GN_MAXSHIFT;
				poll[i].qtype |= t2 << GN_MINSHIFT;
			} else {
				poll[i].qtype |= t1 << GN_MINSHIFT;
				poll[i].qtype |= t2 << GN_MAXSHIFT;
			}

			if (!(poll[i].text = getstringff (scr, 1))) {
				prompt (SCRIPTERR);
				return 0;
			}
			poll[i].chorep = NULL;
			break;

		case 1:

			do
				if (fscanf (scr, "%c", &c) != 1) {
					prompt (SCRIPTERR);
					return 0;
				}
			while (c == '\n' || c == '\t' || c == ' ' || c < '0' ||
			       c > '9');
			if (fseek (scr, -1, SEEK_CUR)) {
				prompt (SCRIPTERR);
				return 0;
			}
			if (fscanf (scr, "%u", &t1) != 1) {
				prompt (SCRIPTERR);
				return 0;
			}

			poll[i].qtype = GQ_FREETEXT | (t1 << 2);
			if (!(poll[i].text = getstringff (scr, 1))) {
				prompt (SCRIPTERR);
				return 0;
			}
			poll[i].chorep = NULL;
			break;

		case 2:
		case 3:
			if (t1 == 2)
				poll[i].qtype = GQ_CHOICES_SINGLE;
			else
				poll[i].qtype = GQ_CHOICES_MULTIPLE;
			if (!(poll[i].text = getstringff (scr, 1))) {
				prompt (SCRIPTERR);
				return 0;
			}
			if (!(poll[i].chorep = getstringff (scr, 1))) {
				prompt (SCRIPTERR);
				return 0;
			}
			break;
		}
	}

	return savegallup ();

}

void
newgallup (void)
{

	char    filename[256];
	struct stat st;
	int     t1;

	if (poll != NULL)
		freegallup ();

	inp_nonblock ();
	thisuseronl.flags |= OLF_BUSY;

	pollinfo.flags = 0;

	for (;;) {
		prompt (NEWGALFN);
		bzero (inp_buffer, MAXINPLEN + 1);
		inp_get (10);
		inp_raw ();
		strcpy (pollinfo.filename, inp_buffer);
		if (inp_isX (pollinfo.filename)) {
			inp_block ();
			return;
		}
		if (!strlen (pollinfo.filename)) {
			cnc_end ();
			continue;
		}
		cnc_end ();
		break;
	}

	if (!get_bool (&t1, NEWGALF_VRA, SELERR, 0, 0)) {
		inp_block ();
		return;
	}
	if (t1)
		pollinfo.flags |= GF_VIEWRESALL;
	if (!get_bool (&t1, NEWGALF_MS, SELERR, 0, 0)) {
		inp_block ();
		return;
	}
	if (t1)
		pollinfo.flags |= GF_MULTISUBMIT;
	prompt (SCRIPTHEAD);
	if (!get_bool (&t1, NEWGALQ_SCRHELP, SELERR, 0, 0)) {
		inp_block ();
		return;
	}
	if (t1)
		prompt (SCRIPTHELP);

	sprintf (filename, TMPDIR "/gallup%s%d.scr", pollinfo.filename,
		 getpid ());
	editor (filename, 4 << 20);
	if (!stat (filename, &st)) {
		if (!scriptcompiler (filename))
			freegallup ();
		else
			prompt (OKCREATE);
	}
	unlink (filename);
	inp_block ();

}

void
erasegallup (void)
{

	char    fn[11], ff[256];
	int     t1;

	strcpy (fn, listandselectpoll ());
	if (fn[0] == '\0')
		return;

	if (!get_bool (&t1, ERASECONFIRM, SELERR, 0, 0) || !t1)
		return;
	if (!strcmp (fn, pollinfo.filename))
		freegallup ();

	sprintf (ff, GALLUPSDIR "/%s.dat", fn);
	unlink (ff);
	sprintf (ff, GALLUPSDIR "/%s.rsl", fn);
	unlink (ff);
	sprintf (ff, GALLUPSDIR "/%s.sub", fn);
	unlink (ff);

	prompt (OKERASED);

}


void
run ()
{
	int     shownmenu = 0;
	char    c;

	if (!key_owns (&thisuseracc, entrykey)) {
		prompt (NOENTRY, NULL);
		return;
	}

	for (;;) {
		thisuseronl.flags &= ~OLF_BUSY;
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownmenu) {
				prompt (key_owns (&thisuseracc, crkey) ?
					GALCMNU : GALMNU, NULL);
				prompt (SHMENUHEAD);
				if (poll != NULL)
					prompt (SELGAL, pollinfo.filename, "",
						"");
				prompt (VSHMENU);
				shownmenu = 2;
			}
		} else
			shownmenu = 1;
		if (thisuseronl.flags & OLF_MMCALLING && thisuseronl.input[0]) {
			thisuseronl.input[0] = 0;
		} else {
			if (!cnc_nxtcmd) {
				if (thisuseronl.flags & OLF_MMCONCAT) {
					thisuseronl.flags &= ~OLF_MMCONCAT;
					return;
				}
				if (shownmenu == 1) {
					prompt (SHMENUHEAD);
					if (poll != NULL)
						prompt (SELGAL,
							pollinfo.filename,
							" - ",
							pollinfo.description);
					prompt (key_owns (&thisuseracc, crkey)
						? SHCMENU : SHMENU, NULL);
				} else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			switch (c) {
			case 'A':
				prompt (ABOUT, NULL);
				break;
			case 'S':
				selectpoll ();
				break;
			case 'T':
				takepoll ();
				break;
			case 'V':
				viewresults ();
				break;
			case 'C':
				if (key_owns (&thisuseracc, crkey))
					newgallup ();
				break;
			case 'E':
				if (key_owns (&thisuseracc, crkey))
					erasegallup ();
				break;
			case 'X':
				prompt (LEAVE, NULL);
				return;
			case '?':
				shownmenu = 0;
				break;
			default:
				prompt (ERRSEL, c);
				cnc_end ();
				continue;
			}
		}
		if (fmt_lastresult == PAUSE_QUIT)
			fmt_resetvpos (0);
		cnc_end ();
	}
}


void
done ()
{
	msg_close (msg);
	exit (0);
}

int
handler_run (int argc, char *argv[])
{
	init ();
	run ();
	done ();
	return 0;
}


mod_info_t mod_info_gallups = {
	"gallups",
	"Polls, gallups and questionnaires",
	"Antonis Stamboulis",
	"Issues questionnaires and generates statistics",
	RCS_VER,
	"1.0",
	{0, NULL}
	,			/* Login handler */
	{0, handler_run}
	,			/* Interactive handler */
	{0, NULL}
	,			/* Logout handler */
	{0, NULL}
	,			/* Hangup handler */
	{0, NULL}
	,			/* Cleanup handler */
	{0, NULL}		/* Delete user handler */
};


int
main (int argc, char *argv[])
{
	mod_setinfo (&mod_info_gallups);
	return mod_main (argc, argv);
}


/* End of File */
