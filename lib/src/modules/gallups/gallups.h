/*****************************************************************************\
 **                                                                         **
 **  FILE:      gallups.h                                                   **
 **  AUTHORS:   Antonis Stamboulis (Xplosion), Vangelis Rokas (Valis)       **
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
 * $Id$
 *
 * $Log$
 * Revision 1.5  2003/12/31 06:59:19  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.5  2000/10/01 10:10:19  bbs
 * added macros for logging user sex and age
 *
 * Revision 1.4  2000/09/30 09:20:12  bbs
 * added QF_SELECTNOMENU for the new type of select questions
 * deleted qselcr() macro (was left here)
 * rearranged order of function prototypes
 *
 * Revision 1.3  2000/09/28 18:43:55  bbs
 * added expiration date and time fields in gallup structure
 * (not yet implemented, but they will be soon)
 * added GF_ flags too
 *
 * Revision 1.2  2000/09/27 18:26:25  bbs
 * source beautifications
 * added GAL_MAGIC
 * GALLUPSDIR in no more needed for GSC
 * added macros GF_EXTRA and GF_GONEXT
 * added magic field in gallup structure
 * added author field in gallup structure
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


#ifndef __GALLUPS_H
#define __GALLUPS_H

#if !defined(__GSC__)
#  include "bbs.h"
#  define GALLUPSDIR mkfname(BBSDATADIR"/gallups")
#endif

/* EXTRA and GONEXT are not fully implemented yet, so disable them */
/* #define ENABLE_EXTRA */


/* audit trail flags */
#define AUS_NEWGALLUP	"GALLUP CREATED"
#define AUS_ERASEGALLUP	"GALLUP ERASED"

#define AUD_NEWGALLUP	"%s created gallup %s"
#define AUD_ERASEGALLUP	"%s erased gallup %s"

#define AUT_NEWGALLUP	(AUF_OPERATION|AUF_INFO)
#define AUT_ERASEGALLUP (AUF_OPERATION|AUF_INFO)



#define GAL_MAGIC	"GALL"

#define GI_MAXFNLEN	11
#define GI_MAXDESCLEN	128


#define GQ_NUMBER	1
#define GQ_FREETEXT	2
#define GQ_SELECT	3
#define GQ_COMBO	4

#define QF_COMBODEFAULT		0x0001
#define QF_COMBOUSER		0x0002
#define QF_SELECTNOMENU		0x0004

struct answer {
	union {
		char   *anstext;
		int     ansnumber;
		int     ansselect;
		char   *anscombo;
	} u;
};

#define atxtdt(a)	((a)->u.anstext)
#define anumdt(a)	((a)->u.ansnumber)
#define aseldt(a)	((a)->u.ansselect)
#define acomdt(a)	((a)->u.anscombo)

struct question {
	unsigned char qtype;
	unsigned int qflags;
	int     credits[2];

	char   *prompt;

	union {
		struct {
			int     textlen;
		} u_text;

		struct {
			int     numbermin;
			int     numbermax;
		} u_number;

		struct {
			char   *selectdata;
			int     datacount;
			char  **dataidx;
		} u_select;

		struct {
			char   *combodata;
			int     datacount;
			char  **dataidx;

			char   *comboprompt;
			int     promptcount;
			char  **promptidx;

			char   *combochar;
		} u_combo;
	} u;

	struct answer *ans;
};

#define qtyp(q)	((q)->qtype)
#define qflg(q)	((q)->qflags)
#define qprm(q)	((q)->prompt)
#define qcrd0(q)	((q)->credits[0])
#define qcrd1(q)	((q)->credits[1])
#define qtxtln(q)	((q)->u.u_text.textlen)
#define qnummn(q)	((q)->u.u_number.numbermin)
#define qnummx(q)	((q)->u.u_number.numbermax)
#define qseldt(q)	((q)->u.u_select.selectdata)
//#define qselcr(q)     ((q)->u.u_select.selectcorrect)
#define qcomdt(q)	((q)->u.u_combo.combodata)
#define qcompr(q)	((q)->u.u_combo.comboprompt)
#define qcomch(q)	((q)->u.u_combo.combochar)
#define qans(q)		((q)->ans)

#define qseldatacnt(q)	((q)->u.u_select.datacount)
#define qseldataidx(q)	((q)->u.u_select.dataidx)

#define qcomdatacnt(q)	((q)->u.u_combo.datacount)
#define qcomdataidx(q)	((q)->u.u_combo.dataidx)
#define qcompromidx(q)	((q)->u.u_combo.promptidx)
#define qcompromcnt(q)	((q)->u.u_combo.promptcount)


#define GDATAFILE	"DATA"
#define GINDEXFILE	"INDEX"
#define GRESFILE	"RESQ-"
#define GSUBFILE	"SUBMIT"

#define GF_VIEWRESALL	0x0000001	// all users can view the results
#define GF_MULTISUBMIT	0x0000002	// a user can take the gallup more than once
#define GF_LOGUSERID	0x0000004	// we are logging the user ids
#define GF_POLL		0x1000000	// the gallup is a poll
#define GF_QUIZ		0x2000000	// the gallup is a quiz

/* extras */
#define GF_TIMED	0x0000010	// the quiz is timed

/* these are to be implemented */
#define GF_EXTRA	0x0000020	// extra checking to finish the quiz is done
#define GF_GONEXT	0x0000040	// if GF_EXTRA also set, then when a user hangups
						// while filling a quiz, next time he will be prompted
						// with the *next* question in line. Otherwise, he will
						// be prompted with the same last question

/* these are to be implemented */
#define GF_EXPONDT	0x0000080	// gallup expires on date/time
#define GF_EXPDATE	0x0000100	// gallup expires on 23:59:59 of date
#define GF_EXPDAYS	0x0000200	// gallup expires in days
#define GF_EXPHOURS	0x0000400	// gallup expires in hours
#define GF_LOGAGE	0x0001000	// log user age
#define GF_LOGSEX	0x0002000	// log user sex


/* NOTE: GF_MULTISUBMIT and GF_EXTRA are two different things. When GF_MULTISUBMIT
   and GF_EXTRA are enabled, a user can enter a quiz more than once, but he should
   finish with the questions of the previous one. */

struct gallup {
	char    magic[4];
	unsigned int flags;
	unsigned int numquestions;
	char    filename[GI_MAXFNLEN];
	char    description[GI_MAXDESCLEN];
	int     credits[3];
	char    author[24];
	long    settime;
	long    setdate;
	long    exptime;
	long    expdate;
	char    dummy[512 - 204];
};
extern struct gallup *ginfo;

/* .credits[0]	is for correct answers
 * .credits[1]	is for wrong answers
 * .credits[2]	is for the starting credits */

#define gnumq(g)	((g)->numquestions)
#define gfnam(g)	((g)->filename)
#define gdesc(g)	((g)->description)
#define gflgs(g)	((g)->flags)
#define gcrd0(g)	((g)->credits[0])
#define gcrd1(g)	((g)->credits[1])
#define gcrd2(g)	((g)->credits[2])
#define gauth(g)	((g)->author)

#define gtset(g)	((g)->settime)
#define gdset(g)	((g)->setdate)
#define gtexp(g)	((g)->exptime)
#define gdexp(g)	((g)->expdate)


extern struct gallup gallupinfo;
extern struct question *questions;
extern struct answer *answers;
extern int gallup_loaded;

/* gallups.c */
void    init ();
char   *listandselectgallup (void);
void    selectgallup (void);
void    saveans ();
void    takegallup ();
void    viewresults ();
void    newgallup (void);
void    erasegallup (void);
int     scriptcompiler (char *script);

#ifndef __GSC__
void    addtosubmitted (useracc_t * u);
int     submitted (useracc_t * u);
#endif

/* io.c */
int     outputcharp (char *charp, FILE * filep);
int     inputcharp (char **charp, FILE * filep);
void    freegallup (void);
void    nullupgallup (void);
int     _savegallup (char *filename);
int     savegallup (void);
void    setupgallup (void);
void    splitstring (char *, char ***, int *);
int     _loadgallup (char *filename, char *fn, struct gallup *gallupinfo);
int     loadgallup (char *fn, struct gallup *gallupinfo);



#if defined(__GSC__)
extern int gscflags;
#endif


#endif


/* End of File */


/* End of File */
