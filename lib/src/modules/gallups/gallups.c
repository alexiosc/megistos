/*****************************************************************************\
 **                                                                         **
 **  FILE:      gallups.c                                                   **
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
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.5  2000/10/01 10:10:19  bbs
 * added options to log user age and sex (used for statistics)
 * original script, is not removes but stored as .script in the gallup dir
 *
 * Revision 1.4  2000/09/30 09:20:12  bbs
 * functions strndup() and strnfill() for more delicate viewing of results
 * variable gallup_loaded to indicate if a gallup is loaded
 * chaged many print() calls to prompt() calls
 * added option to allow the user to format the multiple choice selections
 *  the module does not show any menu.
 *
 * Revision 1.3  2000/09/28 18:43:55  bbs
 * About menu complete
 * bug fixed in takepoll() to inhibit prompting of QUESTSAME
 * gallup_analysis() complete
 *
 * Revision 1.2  2000/09/27 18:26:25  bbs
 * source beautifications
 * added magic check in gallup data file
 * added locking when writing answers in answer files
 * added various prompts for quiz gallups
 * user cannot use /go to exit quiz filling
 * userid in index file is not written first
 * various changes to the run_compiler() function
 * used a bbs dialog to enter a new gallup
 * added Information menu
 * added Operators menu
 *
 * Revision 1.1  2000/09/21 17:27:52  bbs
 * new improved version of Gallups Module
 * support for quizzes and tracking of user ids
 *
 * Revision 1.0  2000/09/21 17:16:11  bbs
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




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

#include <megistos/crc.h>

promptblock_t *msg;
const unsigned int MAXCHOICES = (2 << sizeof (int)) - 2;
struct question *questions = NULL;
struct gallup gallupinfo, *ginfo = &gallupinfo;
struct answer *answers = NULL;

int     points;
time_t  time_used;

int     entrykey;
int     crkey;
char   *gscpath = NULL;
int     galnew_days;

char    tempstr[16384];

char   *
strndup (int c, int count)
{
	memset (tempstr, 0, count + 1);
	memset (tempstr, c, count);

	return tempstr;
}

char   *
strnfill (char *s, int c, int count)
{
	if (count < 0) {
		count = -count;
		if (strlen (s) >= count)
			return s;
		memset (tempstr, 0, count + 1);
		memset (tempstr, c, count);
		memcpy (&tempstr[count - strlen (s)], s, strlen (s));
	} else {
		if (strlen (s) >= count)
			return s;
		memset (tempstr, 0, count + 1);
		memset (tempstr, c, count);
		memcpy (tempstr, s, strlen (s));
	}

	return tempstr;
}


void
init (void)
{
	mod_init (INI_ALL);
	msg = msg_open ("gallups");
	msg_setlanguage (thisuseracc.language);

	entrykey = msg_int (ENTRYKEY, 0, 129);
	crkey = msg_int (CRKEY, 0, 129);
	gscpath = msg_string (GSCPATH);
	galnew_days = msg_int (NEWGALDAYS, 0, 999);
}


char   *
listandselectgallup (void)
{
	FILE   *pipe, *pollf;
	char    temp1[256], temp2[256], *dscr, **galfiles;
	unsigned int galnum = 0, availgal = 0, i;
	struct gallup ghead, *gin = &ghead;
	long int ddatenew;

	sprintf (temp1, "\\ls -trF %s/ | grep /$", GALLUPSDIR);

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

	/* if greater than this date then mark it as new */

	ddatenew = cofdate (today ()) - galnew_days;

	prompt (SELGALHEAD);

	while (fscanf (pipe, "%s", temp1) == 1) {
		galnum++;
		*(strrchr (temp1, '/')) = '\0';
		strncpy (galfiles[galnum - 1], temp1, GI_MAXFNLEN - 1);
		galfiles[galnum - 1][GI_MAXFNLEN - 1] = '\0';
		sprintf (temp2, "%s/%s/DATA", GALLUPSDIR, temp1);
		pollf = fopen (temp2, "r");
		if (!pollf) {
			galnum--;
			continue;
		}

		fread (gin, sizeof (struct gallup), 1, pollf);

		fclose (pollf);

		if (!memcmp (gin->magic, GAL_MAGIC, 4)) {
			prompt (SELGALLIST, galnum,
				gflgs (gin) & GF_LOGUSERID ? '*' : ' ',
				galfiles[galnum - 1], gdesc (&ghead),
				msg_getunit (GALNEW,
					     cofdate (gdset (gin)) >=
					     ddatenew));
		} else {
			galnum--;
			continue;
		}

		if (fmt_lastresult == PAUSE_QUIT)
			break;
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
selectgallup (void)
{
	char    fn[11];

	strcpy (fn, listandselectgallup ());

	if (fn[0] == '\0')
		return;

	if (!loadgallup (fn, &gallupinfo)) {
		prompt (OOPS);
		if (gallup_loaded)
			freegallup ();
		return;
	}
}


/* Add user id into submit file. We do not log the actual user
   id, but a crc32 checksum of the id, and then the list is
   sorted in alphabetical order. All this is done to ensure
   users' privacy. Of course matching can be done, but it needs
   some work, and of course is of no use, as there is not match
   with the answers to the questions. */


struct submitrec {
	char    uid[24];
	long    dat;
};


/* add user in submit file.
 * Log userid and user account creation date.
 * Userid and creation date, are placed in a submitrec structure,
 * and then their crc32 checksum is computed. This checksum is
 * actually stored in the sumbit file. Finally sort the file */

void
addtosubmitted (useracc_t * u)
{
	FILE   *fp;
	char    filename[128], tfname[128];
	char    cmd[256];
	unsigned long int crc;
	struct submitrec buf;


	bzero (buf.uid, 24);
	strcpy (buf.uid, u->userid);
	buf.dat = u->datecre;

	sprintf (tfname, "%s", tmpnam (0));
	sprintf (filename, "%s/%s/%s", GALLUPSDIR, gfnam (ginfo), GSUBFILE);

	fcopy (filename, tfname);

	fp = fopen (tfname, "a");
	crc = cksum ((char *) &buf, sizeof (struct submitrec));
	fprintf (fp, "%8lx\n", crc);
	fclose (fp);

	/* sort and return */
	sprintf (cmd, "\\sort %s -o %s", tfname, filename);
	system (cmd);
}


/* the file that contains the submitted entries, is a text file, holding
 * the CRC32 checksums of the user ids. Calculate the user checksum, and
 * then compare it with those found in the submit file */

int
submitted (useracc_t * u)
{
	FILE   *fp;
	char    filename[256], c = 0;
	unsigned long thiscrc, othercrc;
	struct submitrec buf;

	bzero (buf.uid, 24);
	strcpy (buf.uid, u->userid);
	buf.dat = u->datecre;
	thiscrc = cksum ((char *) &buf, sizeof (struct submitrec));

	sprintf (filename, "%s/%s/%s", GALLUPSDIR, gfnam (ginfo), GSUBFILE);
	fp = fopen (filename, "r");
	if (!fp)
		return 0;
	while (!feof (fp)) {
		if (fscanf (fp, "%lx\n", &othercrc) > 0) {
			if (othercrc == thiscrc)
				c = 1;
		} else
			break;
	}

	fclose (fp);

	return (c);
}


/* The format of the answers has undergone a great deal of discussion (in my mind!)
 * As the best way to save the answers, I decided to keep a different file for each
 * question. Each answer is appended to the answer file, and its position index is
 * stored in an index file */

void
saveans ()
{
	FILE   *fp, *idx;
	char    filename[128];
	unsigned int i;
	long int pos;
	struct answer *a;
	struct question *q;

/* do some locking to ensure that two users do not write their
 * answers to the same positition in the answer files */
	if (lock_check (gfnam (ginfo), filename) > 0) {
		print
		    ("Some one else is accessing gallup. Just wait a minute\n");
		if (lock_wait (gfnam (ginfo), 180) == LKR_TIMEOUT) {
			// 180 seconds should be enough for every gallup

			print
			    ("Lock waiting has timed out. Lock is considered stale, and will be removed\n");
			lock_rm (gfnam (ginfo));
		}
	}

/* ok, we can lock it for ourselves */
	lock_place (gfnam (ginfo), "index");

	sprintf (filename, "%s/%s/%s", GALLUPSDIR, gfnam (ginfo), GINDEXFILE);
	idx = fopen (filename, "a");
	if (!idx) {
		prompt (OOPS);
		return;
	}

	if (gflgs (ginfo) & GF_LOGUSERID)
		fprintf (idx, "%-12s ", thisuseronl.userid);

	if (gflgs (ginfo) & GF_QUIZ)
		fprintf (idx, "%08i ", points);
	if (gflgs (ginfo) & GF_TIMED)
		fprintf (idx, "%08i ", (int) time_used);


/* shall we enable age and sex logging when no user ids are logged? */
#if 0
	if (!(gflgs (ginfo) & GF_LOGUSERID)) {
//              if(gflgs(ginfo) & GF_LOGAGE)
		fprintf (idx, "%08i ", thisuseracc.age);
//              if(gflgs(ginfo) & GF_LOGSEX)
		fprintf (idx, "%c ", thisuseracc.sex);
	}
#endif

	for (i = 0; i < gnumq (ginfo); i++) {

		sprintf (filename, "%s/%s/%s%i", GALLUPSDIR, gfnam (ginfo),
			 GRESFILE, i);
		fp = fopen (filename, "a");

		a = &answers[i];
		q = &questions[i];
		pos = ftell (fp);

		fprintf (idx, "%08lx ", pos);	// log position in index file

		switch (qtyp (q)) {
		case GQ_NUMBER:
			fwrite (&anumdt (a), sizeof (int), 1, fp);
			break;
		case GQ_FREETEXT:
			outputcharp (atxtdt (a), fp);
			free (atxtdt (a));
			break;
		case GQ_SELECT:
			fwrite (&aseldt (a), sizeof (int), 1, fp);
			break;
		case GQ_COMBO:
			outputcharp (acomdt (a), fp);
			free (acomdt (a));
			break;
		}

		fclose (fp);
	}

	free (answers);
	answers = NULL;

	fprintf (idx, "\n");
	fclose (idx);

	if (!(gflgs (ginfo) & GF_MULTISUBMIT))
		addtosubmitted (&thisuseracc);

	lock_rm (gfnam (ginfo));
}

int
findlongest (char *data[], int count)
{
	int     i, max;

	max = 0;
	for (i = 0; i < count; i++)
		if (strlen (data[i]) > max)
			max = strlen (data[i]);

	return max;
}



void
takegallup (void)
{
	unsigned int i = 0, selint;
	struct question *q;
	struct answer *a;
	time_t  t_start = 0, t_end = 0;

	if (!gallup_loaded) {
		prompt (NOGALSEL);
		return;
	}

	if (!(gflgs (ginfo) & GF_MULTISUBMIT) && submitted (&thisuseracc)) {
		prompt (ALREADYSUB);
		return;
	}

	answers = malloc (sizeof (struct answer) * gnumq (ginfo));

	inp_nonblock ();
	thisuseronl.flags |= OLF_BUSY;

	if (gflgs (ginfo) & GF_TIMED) {
		prompt (THISTIMED);
	}


	if (gflgs (ginfo) & GF_QUIZ) {
		points = gcrd2 (ginfo);

		prompt (THISQUIZ);

		if (gflgs (ginfo) & GF_EXTRA) {
			prompt (QUIZEXTRA);
			if (gflgs (ginfo) & GF_GONEXT)
				prompt (QUESTNEXT);
			else
				prompt (QUESTSAME);
		}

		if (!get_bool (&i, DOQUIZ, SELERR, 0, 0)) {
			inp_block ();
			return;
		}
		if (!i) {
			prompt (COMEBACK);
			inp_block ();
			return;
		}

		thisuseronl.flags |= OLF_INHIBITGO;
	}


	if (gflgs (ginfo) & GF_TIMED)
		t_start = time (0);

	for (i = 0; i < gnumq (ginfo); i++) {
		fmt_lastresult = 0;

		q = &questions[i];
		a = &answers[i];

		switch (qtyp (q)) {
		case GQ_NUMBER:
			print (qprm (q));
			cnc_end ();

			for (;;) {
				if (!get_number (&selint, NUMBERINP,
						 qnummn (q), qnummx (q),
						 SELERR, 0, 0)) {

					if (gflgs (ginfo) & GF_QUIZ) {
						prompt (CANNOTQUIT);
						cnc_end ();
						continue;
					}

					inp_block ();
					return;
				} else
					break;
			}

			anumdt (a) = selint;

			if (gflgs (ginfo) & GF_QUIZ) {
				if (anumdt (a) == anumdt (qans (q)))
					points += qcrd0 (q);
				else
					points -= qcrd1 (q);
			}

			break;

		case GQ_FREETEXT:
			for (;;) {
				print (qprm (q));
				memset (inp_buffer, 0, MAXINPLEN + 1);
				inp_get (qtxtln (q));
				inp_raw ();
				atxtdt (a) = strdup (inp_buffer);
				if (inp_isX (atxtdt (a))) {
					if (gflgs (ginfo) & GF_QUIZ) {
						prompt (CANNOTQUIT);
						cnc_end ();
						continue;
					}
					inp_block ();
					return;
				}

				if (!strlen (atxtdt (a))) {
					cnc_end ();
					continue;
				}
				cnc_end ();
				break;
			}
//                              phonetic(atxtdt(a));

			if (gflgs (ginfo) & GF_QUIZ) {
				if (!strcasecmp
				    (atxtdt (a), atxtdt (qans (q))))
					points += qcrd0 (q);
				else
					points -= qcrd1 (q);
			}

			break;

		case GQ_SELECT:{
				int     n = 0;

				print (qprm (q));

				if (!(qflg (q) & QF_SELECTNOMENU))
					for (n = 0; n < qseldatacnt (q); n++)
						prompt (MCHEADER, n + 1,
							qseldataidx (q)[n]);

				n = qseldatacnt (q);
				cnc_end ();
				for (;;) {
					if (!get_number
					    (&selint, SINGLESEL, 1, n, SELERR,
					     0, 0)) {
						if (gflgs (ginfo) & GF_QUIZ) {
							prompt (CANNOTQUIT);
							cnc_end ();
							continue;
						}

						inp_block ();
						return;
					} else
						break;
				}
				aseldt (a) = selint - 1;

				if (gflgs (ginfo) & GF_QUIZ) {
					if (aseldt (a) == aseldt (qans (q)))
						points += qcrd0 (q);
					else
						points -= qcrd1 (q);
				}

			};
			break;

		case GQ_COMBO:{
				int     n, m, rep, l;
				char    c;

				print (qprm (q));
				acomdt (a) = NULL;

				l = findlongest (qcomdataidx (q),
						 qcomdatacnt (q)) + 1;

				for (n = 0; n < qcomdatacnt (q); n++) {
					rep = 1;

					do {
						cnc_end ();
						prompt (MCHEADERASK, n + 1,
							strnfill (qcomdataidx
								  (q)[n], ' ',
								  l));

						phonetic (qcomch (q));
						print ("(");
						for (m = 0;
						     m < qcompromcnt (q);
						     m++) {
							print ("%s",
							       qcompromidx (q)
							       [m]);

							if (m <
							    qcompromcnt (q) -
							    1)
								print (",");
						}
						print (") [%s]: ", qcomch (q));

						inp_get (1);
						inp_raw ();

						if (inp_isX (inp_buffer)) {
							inp_block ();
							return;
						}

						phonetic (inp_buffer);

						for (m = 0;
						     m < qcompromcnt (q);
						     m++) {
							if (inp_buffer[0] ==
							    qcomch (q)[m]) {
								if (acomdt (a))
									strcpy
									    (inp_buffer,
									     acomdt
									     (a));
								else
									strcpy
									    (inp_buffer,
									     "");
								c = m + '0';
								strncat
								    (inp_buffer,
								     &c, 1);
								strcat
								    (inp_buffer,
								     "\n");
								if (acomdt (a))
									free (acomdt (a));
								acomdt (a) =
								    strdup
								    (inp_buffer);
								rep = 0;
								break;
							}
						}
					} while (rep);
				}
			};
			break;

		}
	}

	if (gflgs (ginfo) & GF_TIMED) {
		t_end = time (0);
		time_used = t_end - t_start;
		prompt (TIME, time_used);
	}

	if (gflgs (ginfo) & GF_QUIZ) {
		prompt (SCORE, points);

		thisuseronl.flags &= ~OLF_INHIBITGO;
	}

	if (i == gnumq (ginfo)) {
		prompt (THANKS);
		saveans ();
	}
	inp_block ();
}



void
viewresults (void)
{
	FILE   *fp, *idx;
	unsigned int i, j, n, *selsum = NULL, **comsum = NULL;
	char    filename[128], userid[24];
	struct answer aa, *a = &aa;
	struct question *q;
	int     count, spos, l;

	if (!gallup_loaded) {
		prompt (NOGALSEL);
		return;
	}

	if (!(gflgs (ginfo) & GF_VIEWRESALL || key_owns (&thisuseracc, crkey))) {
		prompt (NOPERMRES);
		return;
	}

	sprintf (filename, "%s/%s/%s", GALLUPSDIR, gfnam (ginfo), GINDEXFILE);
	idx = fopen (filename, "r");
	if (!idx) {
		prompt (NORESULTS);
		return;
	}


	if (gflgs (ginfo) & GF_QUIZ) {
		if (gflgs (ginfo) & GF_TIMED)
			prompt (RESQUIZTHEAD);
		else
			prompt (RESQUIZHEAD);

		fgets (tempstr, sizeof (tempstr), idx);
		while (!feof (idx)) {
			/* if(strchr(tempstr, '\n'))(*strchr(tempstr, '\n')) = '\0'; */

			if (gflgs (ginfo) & GF_LOGUSERID)
				sscanf (tempstr, "%s %n", userid, &spos);

			sscanf (&tempstr[spos], "%d %d", &n, &j);
			if (gflgs (ginfo) & GF_TIMED)
				prompt (RESQUIZTENTRY, userid, n, j);
			else
				prompt (RESQUIZENTRY, userid, n);

			fgets (tempstr, sizeof (tempstr), idx);
		}

		prompt (RESQFOOT);

		fclose (idx);
		return;
	}



	for (i = 0; i < gnumq (ginfo); i++) {
		fmt_lastresult = 0;

		fseek (idx, 0, SEEK_SET);

		sprintf (filename, "%s/%s/%s%i", GALLUPSDIR, gfnam (ginfo),
			 GRESFILE, i);
		fp = fopen (filename, "r");
		if (!fp) {
			prompt (NORESULTS);
			return;
		}

		q = &questions[i];
		print (qprm (q));
		count = 0;

		switch (qtyp (q)) {
		case GQ_SELECT:
			selsum = malloc (sizeof (int) * qseldatacnt (q));

			for (j = 0; j < qseldatacnt (q); j++) {
				selsum[j] = 0;
			}

			if (!(qflg (q) & QF_SELECTNOMENU)) {
				print ("\n");
				for (j = 0; j < qseldatacnt (q); j++)
					prompt (MCHEADER, j + 1,
						qseldataidx (q)[j]);
				print ("\n");
			}


			break;
		case GQ_COMBO:
			comsum =
			    malloc (sizeof (int *) * (qcomdatacnt (q) + 1));

			for (j = 0; j < qcomdatacnt (q) + 1; j++) {
				comsum[j] =
				    malloc (sizeof (int) * qcompromcnt (q));
				for (n = 0; n < qcompromcnt (q); n++)
					comsum[j][n] = 0;
			}

			print ("\n");

			for (j = 0; j < qcompromcnt (q); j++)
				prompt (MCANSWER, j + 1, qcomch (q)[j],
					qcompromidx (q)[j]);
			print ("\n");
			break;
		}

		prompt (RESQFTHEAD);

		memset (tempstr, 0, sizeof (tempstr));

		fgets (tempstr, sizeof (tempstr), idx);
		while (!feof (idx)) {
			if (strchr (tempstr, '\n'))
				(*strchr (tempstr, '\n')) = '\0';
			if (gflgs (ginfo) & GF_LOGUSERID)
				sscanf (tempstr, "%s", userid);
			else
				strcpy (userid, "------");

//                      print("%-11s", userid);


			switch (qtyp (q)) {
			case GQ_NUMBER:
				fread (&anumdt (a), sizeof (int), 1, fp);
				print ("%i\n", anumdt (a));
				break;
			case GQ_FREETEXT:
				inputcharp (&atxtdt (a), fp);
				print ("%s\n", atxtdt (a));
				free (atxtdt (a));
				break;
			case GQ_SELECT:
				fread (&aseldt (a), sizeof (int), 1, fp);
				selsum[aseldt (a)]++;
				count++;
				break;
			case GQ_COMBO:{
					char  **anspromidx;

					inputcharp (&acomdt (a), fp);
					splitstring (acomdt (a), &anspromidx,
						     &j);
					count++;

					for (j = 0; j < qcomdatacnt (q); j++) {
						comsum[j][anspromidx[j][0] -
							  48]++;
						comsum[qcomdatacnt (q)]
						    [anspromidx[j][0] - 48]++;
					}

					free (anspromidx);
					free (acomdt (a));
				};
				break;
			}
			fgets (tempstr, sizeof (tempstr), idx);
		}

		switch (qtyp (q)) {
		case GQ_SELECT:
			l = findlongest (qseldataidx (q), qseldatacnt (q)) + 1;
			if (l < 30)
				l = 30;

			for (j = 0; j < qseldatacnt (q); j++)
				prompt (ANSSELECT,
					strnfill (qseldataidx (q)[j], ' ', l),
					selsum[j], count,
					(selsum[j] * 100.0 / count));
//                                      print("%s %i/%i %.2f\n", strnfill(qseldataidx(q)[j], ' ', l), selsum[j], count, (selsum[j] * 100.0 / count));
			free (selsum);
			break;
		case GQ_COMBO:
			l = findlongest (qcompromidx (q), qcompromcnt (q)) + 1;
			if (l < 30)
				l = 30;

			prompt (ANSCOMBOSTR,
				strnfill (msg_getunit (ANSCOMBOFIELDS, 1), ' ',
					  -l));

			for (n = 0; n < qcompromcnt (q); n++)
				prompt (ANSCOMBOCHAR, qcomch (q)[n]);

			print ("\n!F-\n");

			for (j = 0; j < qcomdatacnt (q); j++) {
				print ("%-30s", qcomdataidx (q)[j]);

				for (n = 0; n < qcompromcnt (q); n++)
					prompt (ANSCOMBORES, comsum[j][n],
						comsum[qcomdatacnt (q)][n]
						? (comsum[j][n] * 100.0 /
						   comsum[qcomdatacnt (q)][n])
						: 0.0);

				print ("\n");

				free (comsum[j]);
			}

			print ("!F-\n");
			prompt (ANSCOMBOSTR,
				strnfill (msg_getunit (ANSCOMBOSUM, 1), ' ',
					  -l));

//                              print("%-30s", "‘¬¤¦¢¦  ");
			for (n = 0; n < qcompromcnt (q); n++)
				prompt (ANSCOMBOINT,
					comsum[qcomdatacnt (q)][n]);
//                                      print("%3i       ", comsum[qcomdatacnt(q)][n]);
			print ("\n");

			free (comsum[qcomdatacnt (q)]);
			free (comsum);


			break;
		}


		prompt (RESQFOOT);

		fclose (fp);
	}

	fclose (idx);
}


#define RC_TEST	1
#define RC_TYPE	2
#define RC_DONE	3


/* return 0 on error, 1 on success */
int
run_compiler (char *fname, char *oname, int vis, int *info)
{
	char    cmd[256];
	int     er, suc = 0;
	FILE   *fp;


/* create the string to execute via system() */
	strcpy (cmd, gscpath);

	if (*info == RC_TEST)
		strcat (cmd, " -y");
	if (*info == RC_TYPE)
		strcat (cmd, " -y -i");

	if (gflgs (ginfo) & GF_VIEWRESALL)
		strcat (cmd, " -a");
	if (gflgs (ginfo) & GF_MULTISUBMIT)
		strcat (cmd, " -m");
	if (gflgs (ginfo) & GF_LOGUSERID)
		strcat (cmd, " -l");
	if (gflgs (ginfo) & GF_TIMED)
		strcat (cmd, " -t");
	if (gflgs (ginfo) & GF_EXTRA) {
		if (gflgs (ginfo) & GF_GONEXT)
			strcat (cmd, " -x2");
		else
			strcat (cmd, " -x1");
	} else
		strcat (cmd, " -x0");

	sprintf (tempstr, "%li", gtset (ginfo));
	strcat (cmd, " -et");
	strcat (cmd, tempstr);

	sprintf (tempstr, "%li", gdset (ginfo));
	strcat (cmd, " -ed");
	strcat (cmd, tempstr);

	// gallup name
	strcat (cmd, " -n");
	strcat (cmd, gfnam (ginfo));

	// author name
	strcat (cmd, " -c");
	strcat (cmd, thisuseronl.userid);

	if (oname[0]) {
		strcat (cmd, " -o");
		strcat (cmd, oname);
	}
	// script name
	strcat (cmd, " ");
	strcat (cmd, fname);


//      print("command to execute : %s\n", cmd);
	if (vis) {
		print ("Compiling script... (output)\n!F-\n");
	}

	fp = popen (cmd, "r");

	fgets (cmd, 256, fp);
	while (!feof (fp)) {
		if (*info == RC_TYPE) {
			if (strstr (cmd, "GF_POLL"))
				suc = GF_POLL;
			if (strstr (cmd, "GF_QUIZ"))
				suc = GF_QUIZ;
		}

		if (strstr (cmd, "Success"))
			break;
		if (vis)
			print (cmd);
		fgets (cmd, 256, fp);
	}

	er = pclose (fp);

	if (vis)
		print ("!F-\n");

	*info = suc;

	if (!er)
		return 1;
	else
		return 0;
}




void
newgallup (void)
{
	FILE   *fp;
	char    filename[256], cmd[256], fedit[128], oname[256], *ch;
	struct stat st;
	int     t1, editscript = 0, rc;
	float   v;
	struct gallup gi, *oldgi;

	if (gallup_loaded)
		freegallup ();

	if (!gscpath) {
		prompt (NOGSC);
		return;
	}


	oldgi = ginfo;
	ginfo = &gi;

	gflgs (ginfo) = 0;

	if (stat (gscpath, &st)) {
		prompt (ERRORGSC);
		error_log ("Could not locate gallup script compiler (%s)",
			   gscpath);
		return;
	}

	sprintf (cmd, "%s -v", gscpath);
	fp = popen (cmd, "r");
	fgets (cmd, 256, fp);
	pclose (fp);
	sscanf (cmd, "%*f %f", &v);
	prompt (COMPILERVER, v);

	gflgs (ginfo) = 0;
	strcpy (gfnam (ginfo), "");

	sprintf (filename, "%s/gallup-%d", TMPDIR, getpid ());
	sprintf (oname, "%s.bin", filename);

	strcpy (fedit, "");
	gflgs (ginfo) |= GF_LOGAGE | GF_LOGSEX;

	do {
		sprintf (inp_buffer,
			 "%s\n%s\n%s\n%s\nSCRIPT\nTEST\nOK\nCANCEL\n",
			 gfnam (ginfo),
			 gflgs (ginfo) & GF_VIEWRESALL ? "on" : "off",
			 gflgs (ginfo) & GF_LOGUSERID ? "on" : "off",
			 gflgs (ginfo) & GF_MULTISUBMIT ? "on" : "off");


		dialog_run ("gallups", NEWGVT, NEWGLT, inp_buffer, MAXINPLEN);

		dialog_parse (inp_buffer);

		if (sameas (margv[8], margv[4]) || sameas (margv[8], margv[5])
		    || sameas (margv[8], "OK")) {
			strcpy (gfnam (ginfo), margv[0]);

			if (sameas (margv[1], "ON"))
				gflgs (ginfo) |= GF_VIEWRESALL;
			else
				gflgs (ginfo) &= ~GF_VIEWRESALL;
			if (sameas (margv[2], "ON"))
				gflgs (ginfo) |= GF_LOGUSERID;
			else
				gflgs (ginfo) &= ~GF_LOGUSERID;
			if (sameas (margv[3], "ON"))
				gflgs (ginfo) |= GF_MULTISUBMIT;
			else
				gflgs (ginfo) &= ~GF_MULTISUBMIT;

			if (sameas (margv[8], margv[4])) {	// execute editor
				sprintf (fedit, "%s", tmpnam (0));
				if (editscript)
					fcopy (filename, fedit);

				editor (fedit, 1 << 20);
				if (!stat (fedit, &st)) {
					editscript = 1;
					fcopy (fedit, filename);
					unlink (fedit);
				}
				continue;
			}

			if (sameas (margv[8], margv[5])) {	// execute compiler to test
				if (!editscript) {
					prompt (NOSCRIPT);
					continue;
				}

				rc = RC_TEST;
				if (!run_compiler (filename, oname, 1, &rc)) {
					prompt (COMPFAILED);
				} else
					prompt (COMPSUCCESS);

				print ("!P");

				continue;
			}
		}
		break;
	} while (1);

	unlink (fedit);

//      for(t1 = 0;t1<=margc;t1++)print("margv[ %i ] = %s\n", t1, margv[t1]);

	if (sameas (margv[8], "CANCEL") || sameas (margv[8], margv[7])) {
		prompt (PROCCANCEL);
		unlink (filename);
		return;
	}

	if (!editscript) {
		prompt (NOSCRIPT);
		ginfo = oldgi;
		return;
	}

	gtset (ginfo) = now ();
	gdset (ginfo) = today ();

	rc = RC_TYPE;
	run_compiler (filename, oname, 0, &rc);

	if (rc == GF_QUIZ) {
		prompt (QUIZHEAD);

		if (!get_bool (&t1, TIMEQUIZ, SELERR, ENTERNO, 0))
			return;
		if (t1)
			gflgs (ginfo) |= GF_TIMED;

#ifdef ENABLE_EXTRA
		if (!get_bool (&t1, EXTRACHECK, SELERR, ENTERNO, 0))
			return;
		if (t1) {
			gflgs (ginfo) |= GF_EXTRA;
			if (!get_bool (&t1, ADVANCENEXT, SELERR, ENTERYES, 1))
				return;
			if (!t1)
				gflgs (ginfo) |= GF_GONEXT;
		}
#endif


#ifdef ENABLE_EXPIRATION
		if (!get_bool (&t1, EXPIREQ, SELERR, ENTERNO, 0))
			return;
#endif

	}


	rc = RC_DONE;
	if (!run_compiler (filename, oname, 0, &rc)) {
		prompt (CREATEFAIL);

	} else {
		// delete any old data files
		sprintf (cmd, "\\rm -Rf %s/%s", GALLUPSDIR, gfnam (ginfo));
		system (cmd);

		// create directory             
		sprintf (cmd, "\\mkdir %s/%s/", GALLUPSDIR, gfnam (ginfo));
		system (cmd);

		// copy file
		sprintf (cmd, "\\cp %s %s/%s/%s", oname, GALLUPSDIR,
			 gfnam (ginfo), GDATAFILE);
		system (cmd);

		/* keep back up file *//* GREAT SECURITY RISK (IN QUIZZES) */
		sprintf (cmd, "\\cp %s %s/%s/.script", filename, GALLUPSDIR,
			 gfnam (ginfo));
		system (cmd);

		prompt (CREATEOK);

		if ((ch = getenv ("CHANNEL")) != NULL)
			audit (ch, AUDIT (NEWGALLUP), thisuseracc.userid,
			       gfnam (ginfo));
		else
			audit ("[no channel]", AUDIT (NEWGALLUP),
			       thisuseracc.userid, gfnam (ginfo));
	}

	ginfo = oldgi;
	unlink (filename);
	unlink (oname);
}


void
erasegallup (void)
{
	char    fn[11], cmd[256], *ch;
	int     t1;

	strcpy (fn, listandselectgallup ());
	if (fn[0] == '\0')
		return;

	if (!get_bool (&t1, ERASECONFIRM, SELERR, 0, 0) || !t1)
		return;
	if (!strcmp (fn, gfnam (ginfo)))
		freegallup ();

	sprintf (cmd, "\\rm -Rf %s/%s", GALLUPSDIR, fn);
	system (cmd);

	prompt (OKERASED);

	if ((ch = getenv ("CHANNEL")) != NULL)
		audit (ch, AUDIT (ERASEGALLUP), thisuseracc.userid, fn);
	else
		audit ("[no channel]", AUDIT (ERASEGALLUP), thisuseracc.userid,
		       fn);

}

void
about (void)
{
	int     shownmenu = 0;
	char    c = 0;		// initialize to stop gcc complaining
	char   *path = NULL;
	char    desc[50];

	for (;;) {
		thisuseronl.flags &= ~OLF_BUSY;
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownmenu) {
				prompt (ABOUTMNU);
				prompt (SHABOUTHEAD);
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
					shownmenu = 1;
//                                      return;
				}
				if (shownmenu == 1) {
					prompt (SHABOUTHEAD);
					prompt (SHABOUTMENU);
				} else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			switch (c) {
			case '1':
				path = msg_string (DOCFILE);
				sprompt (desc, DOCFILEPRM);
				break;
			case '2':
				path = msg_string (SECFILE);
				sprompt (desc, SECFILEPRM);
				break;
			case '3':
				path = msg_string (FRMFILE);
				sprompt (desc, FRMFILEPRM);
				break;
			case 'X':
				prompt (LEAVEABOUT);
				return;
			case '?':
				shownmenu = 0;
				break;
			default:
				prompt (ERRSEL, c);
				cnc_end ();
				continue;
			}

			if (path) {
				if (xfer_add (FXM_DOWNLOAD, path, desc, 0, -1)) {
					xfer_run ();
					xfer_kill_list ();
				}
				free (path);
				path = NULL;
			}
		}
		if (fmt_lastresult == PAUSE_QUIT)
			fmt_resetvpos (0);
		cnc_end ();
	}
}


/* count lines in index file */
int
count_entries (struct gallup *gin)
{
	FILE   *idx;
	char    filename[128];
	int     entries = 0;

	sprintf (filename, "%s/%s/%s", GALLUPSDIR, gfnam (gin), GINDEXFILE);

	idx = fopen (filename, "r");
	if (!idx)
		return 0;

	fgets (tempstr, sizeof (tempstr), idx);
	while (!feof (idx)) {
		entries++;
		fgets (tempstr, sizeof (tempstr), idx);
	}

	fclose (idx);

	return entries;
}


void
gallup_information (void)
{
	char   *galname, fname[128];
	char    yes[20], no[20];
	FILE   *fp;
	struct gallup gal, *gin = &gal;

	sprompt (yes, GALYES);
	sprompt (no, GALNO);

	galname = listandselectgallup ();
	if (!galname[0])
		return;

	sprintf (fname, "%s/%s/%s", GALLUPSDIR, galname, GDATAFILE);
	fp = fopen (fname, "r");
	fread (gin, sizeof (struct gallup), 1, fp);
	fclose (fp);

	out_setwaittoclear (0);

	prompt (GALENTRYHEAD);
	prompt (GALENTRYTMPL,
		gdesc (gin),
		gfnam (gin),
		msg_getunit (GALLUPPOLL, gflgs (gin) & GF_POLL),
		gauth (gin),
		gnumq (gin),
		gflgs (gin) & GF_LOGUSERID ? yes : no,
		gflgs (gin) & GF_MULTISUBMIT ? yes : no,
		gflgs (gin) & GF_VIEWRESALL ? yes : no,
		gflgs (gin) & GF_TIMED ? yes : no);

	prompt (GALENTRYMORE,
		strdate (gdset (gin)),
		cofdate (today ()) - cofdate (gdset (gin)), count_entries (gin)
	    );



	prompt (GALENTRYFOOT);

	out_setwaittoclear (1);
}

#define MONOFF(g)	(g?"on":"off")
#define GONOFF(m,g)	do { if(sameas(margv[m], "on"))g=1;else g=0; } while(0)
void
gallup_statistics (void)
{
	char   *galname;
	struct {
		int     t_sexage:1;
		int     t_sex:1;
		int     t_age:1;
		int     t_options:1;
		int     g_sexage:1;
		int     g_sex:1;
		int     g_age:1;
		int     g_options:1;
	} sinf = {
	1, 0, 0, 0, 1, 0, 0, 0};


	galname = listandselectgallup ();
	if (!galname[0])
		return;


	sprintf (inp_buffer, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\nOK\nCANCEL\n",
		 MONOFF (sinf.t_sexage),
		 MONOFF (sinf.t_sex),
		 MONOFF (sinf.t_age),
		 MONOFF (sinf.t_options),
		 MONOFF (sinf.g_sexage),
		 MONOFF (sinf.g_sex),
		 MONOFF (sinf.g_age), MONOFF (sinf.g_options));

	dialog_run ("gallups", STATGALVT, STATGALLT, inp_buffer, MAXINPLEN);

	dialog_parse (inp_buffer);

	GONOFF (0, sinf.t_sexage);
	GONOFF (1, sinf.t_sex);
	GONOFF (2, sinf.t_age);
	GONOFF (3, sinf.t_options);
	GONOFF (4, sinf.g_sexage);
	GONOFF (5, sinf.g_sex);
	GONOFF (6, sinf.g_age);
	GONOFF (7, sinf.g_options);

	if (sameas (margv[10], "CANCEL") || sameas (margv[10], margv[9])) {
		prompt (PROCCANCEL);
		return;
	}

	if (sameas (margv[10], "OK") || sameas (margv[10], margv[8])) {
		char    cmd[128], out[128];

		sprintf (cmd, "%s/gstat ", mkfname (BINDIR));
		if (sinf.t_sexage)
			strcat (cmd, "-t4 ");
		if (sinf.t_sex)
			strcat (cmd, "-t2 ");
		if (sinf.t_age)
			strcat (cmd, "-t3 ");
		if (sinf.t_options)
			strcat (cmd, "-t1 ");

		if (sinf.g_sexage)
			strcat (cmd, "-g4 ");
		if (sinf.g_sex)
			strcat (cmd, "-g2 ");
		if (sinf.g_age)
			strcat (cmd, "-g3 ");
		if (sinf.g_options)
			strcat (cmd, "-g1 ");

		strcat (cmd, galname);

		sprintf (out, "%s/%s.rep", TMPDIR, galname);

		strcat (cmd, " >");
		strcat (cmd, out);

		print ("command to execute: %s\n", cmd);

		system (cmd);


		if (xfer_add (FXM_TRANSIENT, out, msg_get (GALREPDESC), 0, -1)) {
			xfer_run ();
			xfer_kill_list ();
		}

//              out_printfile(out);

		unlink (out);
	}

}


void
operators_menu (void)
{
	int     shownmenu = 0;
	char    c = 0;

	for (;;) {
		thisuseronl.flags &= ~OLF_BUSY;
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownmenu) {
				prompt (OPERMNU, NULL);
				prompt (SHOPERHEAD);
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
					shownmenu = 1;
//                                      return;
				}
				if (shownmenu == 1) {
					prompt (SHOPERHEAD);
					prompt (SHOPERMENU);
				} else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			switch (c) {
			case 'C':
				newgallup ();
				break;
			case 'E':
				erasegallup ();
				break;
			case 'I':
				gallup_information ();
				break;
			case 'S':
				prompt (UNDERCONSTRUCT);
				gallup_statistics ();
				break;
			case 'X':
				prompt (LEAVEOPER, NULL);
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
run (void)
{
	int     shownmenu = 0;
	char    c = 0;

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
					MAINOMNU : MAINMNU, NULL);
				prompt (SHMAINHEAD);
				if (gallup_loaded)
					prompt (SELGAL, gfnam (ginfo), "", "");
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
//                                      return;
				}
				if (shownmenu == 1) {
					prompt (SHMAINHEAD);
					if (gallup_loaded)
						prompt (SELGAL, gfnam (ginfo),
							" - ", gdesc (ginfo));
					prompt (key_owns (&thisuseracc, crkey)
						? SHOMENU : SHMENU, NULL);
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
				about ();
				break;
			case 'S':
				selectgallup ();
				break;
			case 'T':
				takegallup ();
				break;
			case 'V':
				viewresults ();
				break;
			case 'O':
				if (key_owns (&thisuseracc, crkey))
					operators_menu ();
				else {
					prompt (ERRSEL, c);
					cnc_end ();
					continue;
				}
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
	"2.0",
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
