/*****************************************************************************\
 **                                                                         **
 **  FILE:      glps-bcc.h                                                  **
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
 * added GF_EXTRA and GF_GONEXT macros
 * added magic field in gallup structure
 * added author field in gallup structure
 *
 * Revision 1.0  2000/09/21 18:15:30  bbs
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";

#ifndef __GALLUPS_H
#define __GALLUPS_H

#define GAL_MAGIC	"GALL"

#define GI_MAXFNLEN	11
#define GI_MAXDESCLEN	128


#define GQ_NUMBER	1
#define GQ_FREETEXT	2
#define GQ_SELECT	3
#define GQ_COMBO	4

#define QF_COMBODEFAULT	1
#define QF_COMBOUSER	2


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
#define qselcr(q)	((q)->u.u_select.selectcorrect)
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
	char    creator[24];
	char    dummy[512 - 188];
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
#define gcrtr(g)	((g)->creator)

extern struct gallup gallupinfo;
extern struct question *questions;
extern struct answer *answers;


void    init ();
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
char   *listandselectpoll (void);
void    selectpoll (void);

#ifndef __GSC__
void    addtosubmitted (useracc_t * u);
int     submitted (useracc_t * u);
#endif

void    saveans ();
void    takepoll ();
void    viewresults ();
void    newgallup (void);
void    erasegallup (void);

int     scriptcompiler (char *script);

#if defined(__GSC__)
extern int gscflags;
#endif


#endif



/* End of File */
