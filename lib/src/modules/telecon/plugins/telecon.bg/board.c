/*****************************************************************************\
 **                                                                         **
 **  FILE:     board.c                                                      **
 **  AUTHORS:  Alexios (et al)                                              **
 **  PURPOSE:                                                               **
 **  NOTES:                                                                 **
 **  LEGALESE: See below.                                                   **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.4  2003/12/25 08:26:19  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/08/13 17:03:41  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



#include <bbs.h>
#include <mbk/mbk_telecon.bg.h>
#include <megistos/back.h>
#include <megistos/telecon.bg.h>


#define sgn(x) ((x)>0?1:((x)==0?0:-1))


static char *
mkrow (int *row, int lang, int top)
{
	static char s[256];
	int     cur = 0, i;

	s[0] = 0;
	for (i = 0; i < 6; i++) {
		if (sgn (row[i]) != cur) {
			if (row[i])
				strcat (s,
					msg_getl (row[i] > 0 ? BDCOL1 : BDCOL2,
						  lang));
			cur = sgn (row[i]);
		}

		if (row[i] == 0)
			strcat (s, msg_getl (BDEMPT, lang));
		else if (row[i] == 1)
			strcat (s, msg_getl (BDSTN1, lang));
		else if (row[i] == -1)
			strcat (s, msg_getl (BDSTN2, lang));
		else if (row[i] > 1) {
			char    tmp[16];

			sprintf (tmp, msg_getl (BDSTNN, lang), row[i] - 5);
			strcat (s, tmp);
		} else if (row[i] < -1) {
			char    tmp[16];

			sprintf (tmp, msg_getl (BDSTNN, lang),
				 abs (row[i]) - 5);
			strcat (s, tmp);
		}
	}
	return s;
}


void
bg_board (int n)
{
	int     i, j;
	char    b[24][256];	/* 24 rows, not columns (coincidence) */

	if (!usr_insys (player[n], 0))
		exit (0);

	for (i = 0; i < 6; i++) {
		int     row[6];

		/* The top left quadrant (0-5) */

		bzero (row, sizeof (row));
		if (i < 5) {
			for (j = 1; j <= 6; j++)
				if (abs (board[j]) > i)
					row[j - 1] = (board[j] > 0) ? 1 : -1;
		} else {
			for (j = 1; j <= 6; j++)
				if (abs (board[j]) > i)
					row[j - 1] = board[j];
		}
		strcpy (b[i], mkrow (row, othruseracc.language, 1));


		/* The top right quadrant (6-11) */

		bzero (row, sizeof (row));
		if (i < 5) {
			for (j = 1; j <= 6; j++)
				if (abs (board[6 + j]) > i)
					row[j - 1] =
					    (board[6 + j] > 0) ? 1 : -1;
		} else {
			for (j = 1; j <= 6; j++)
				if (abs (board[6 + j]) > i)
					row[j - 1] = board[6 + j];
		}
		strcpy (b[6 + i], mkrow (row, othruseracc.language, 1));


		/* The lower right quadrant (12-17) */

		bzero (row, sizeof (row));
		if (i < 5) {
			for (j = 1; j <= 6; j++)
				if (abs (board[19 - j]) > i)
					row[j - 1] =
					    (board[19 - j] > 0) ? 1 : -1;
		} else {
			for (j = 1; j <= 6; j++)
				if (abs (board[19 - j]) > i)
					row[j - 1] = board[19 - j];
		}
		strcpy (b[12 + i], mkrow (row, othruseracc.language, 0));


		/* The lower left quadrant (18-23) */

		bzero (row, sizeof (row));
		if (i < 5) {
			for (j = 1; j <= 6; j++)
				if (abs (board[25 - j]) > i)
					row[j - 1] =
					    (board[25 - j] > 0) ? 1 : -1;
		} else {
			for (j = 1; j <= 6; j++)
				if (abs (board[25 - j]) > i)
					row[j - 1] = board[25 - j];
		}
		strcpy (b[18 + i], mkrow (row, othruseracc.language, 0));
	}

	sprompt_other (othrshm, out_buffer, BOARD,
		       b[0], b[6],
		       b[1], b[7],
		       b[2], b[8],
		       b[3], b[9],
		       b[4], b[10],
		       b[5], b[11],
		       b[23], b[17],
		       b[22], b[16],
		       b[21], b[15], b[20], b[14], b[19], b[13], b[18], b[12]);

	usr_injoth (&othruseronl, out_buffer, 0);
}


/* End of File */
