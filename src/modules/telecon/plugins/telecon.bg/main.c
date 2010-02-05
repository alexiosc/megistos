/*****************************************************************************\
 **                                                                         **
 **  FILE:     main.c                                                       **
 **  AUTHORS:  Alexios (et al)                                              **
 **  PURPOSE:  Main program                                                 **
 **  NOTES:                                                                 **
 **  LEGALESE: See below.                                                   **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id: main.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: main.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
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
    "$Id: main.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



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


#define WANT_STDIO_H 1
#define WANT_SIGNAL_H 1
#include <bbsinclude.h>

#include <bbs.h>
#include <megistos/back.h>


static char *copyright =
    "@(#) Copyright (c) 1980 Regents of the University of California.\n"
    "All rights reserved.\n";


#define MVPAUSE	5		/* time to sleep when stuck */
#define MAXUSERS 35		/* maximum number of users */

extern char *instr[];		/* text of instructions */
extern char *message[];		/* update message */
char    ospeed;			/* tty output speed */


#if 1

/* HERE: messages that should go to the MSG file */

static char user1a[] =
    "Sorry, you cannot play backgammon when there are more than ";

static char user1b[] = " users\non the system.";

static char user2a[] = "\nThere are now more than ";

static char user2b[] =
    " users on the system, so you cannot play\nanother game.  ";

static char rules[] = "\nDo you want the rules of the game?";

static char noteach[] = "Teachgammon not available!\n\007";

static char need[] = "Do you need instructions for this program?";

static char askcol[] =
    "Enter 'r' to play red, 'w' to play white, 'b' to play both:";

static char rollr[] = "Red rolls a ";

static char rollw[] = ".  White rolls a ";

static char rstart[] = ".  Red starts.\n";

static char wstart[] = ".  White starts.\n";

static char toobad1[] = "Too bad, ";

static char unable[] = " is unable to use that roll.\n";

static char toobad2[] = ".  Too bad, ";

static char cantmv[] = " can't move.\n";

static char bgammon[] = "Backgammon!  ";

static char gammon[] = "Gammon!  ";

static char again[] = ".\nWould you like to play again?";

static char svpromt[] = "Would you like to save this game?";

static char password[] = "losfurng";

#endif


static char pbuf[10];



void
bg_set_players (int num_players)
{
	if (num_players == 1)
		pnum = -1;
	else
		pnum = 0;
}



int
bg_initialise ()
{
	register int l;		/* non-descript index */
	register char c;	/* non-descript character storage */
	long    t;		/* time for random num generator */

	/* initialization */

	bflag = 2;		/* default no board */

	t = time (0);
	srandom (t);		/* 'random' seed */

	rscore = wscore = 0;	/* zero score */

	bg_initboard ();	/* initialize board */

#if 0





	for (;;) {		/* begin game! */

		/* initalize variables
		 * according to whose
		 * turn it is */

		if (cturn == 1) {	/* red */
			home = 25;
			bar = 0;
			inptr = &in[1];
			inopp = &in[0];
			offptr = &off[1];
			offopp = &off[0];
			Colorptr = &color[1];
			colorptr = &color[3];
			colen = 3;
		} else {	/* white */
			home = 0;
			bar = 25;
			inptr = &in[0];
			inopp = &in[1];
			offptr = &off[0];
			offopp = &off[1];
			Colorptr = &color[0];
			colorptr = &color[2];
			colen = 5;
		}


		/* do first move  (special case) */

		if (!(rflag && raflag)) {
			if (cturn == pnum)
				move (0);	/* Computer's move */
			else {	/* Player's move */
				mvlim = movallow ();

				/* reprint roll */

				proll ();
				getmove ();	/* Get player's move */
			}
		}


		/* no longer any difference between normal
		 * game and recovered game. */
		rflag = 0;


		/* move as long as it's someone's turn */
		while (cturn == 1 || cturn == -1) {

			/* board maintainence */

			/* HERE: redraw board? */

			wrboard ();


			/* do computer's move */

			if (cturn == pnum) {
				move (1);

				/* see if double refused */

				if (cturn == -2 || cturn == 2)
					break;


				/* check for winning move */

				if (*offopp == 15) {
					cturn *= -2;
					break;
				}

				continue;
			}


			/* (player's move) */


			/* if allowed, give him a chance to double */


			/* HERE: no doubles here! */

			if (dlast != cturn && gvalue < 64) {
				writel (*Colorptr);
				c = readc ();

				/* character cases */
				switch (c) {

				case 'Q':	/* HERE: quitting */
					quit ();
					break;

#if 0
				case 'D':	/* HERE: doubles disabled */
					dble ();
					break;
#endif

				case ' ':	/* HERE: rolling the dice */
				case '\n':
					roll ();
					writel (" rolls ");
					writec (D0 + '0');
					writec (' ');
					writec (D1 + '0');
					writel (".  ");

					/* see if he can move */
					if ((mvlim = movallow ()) == 0) {

						/* can't move */

						writel (toobad1);
						writel (*colorptr);
						writel (unable);

						nexturn ();
						break;
					}


					/* get move */
					getmove ();

					/* okay to clean screen */
					hflag = 1;
					break;

				default:	/* HERE: invalid characters don't get accepted */

					/* print help message */
					writec ('\n');

					/* don't erase */
					hflag = 0;
				}
			} else {	/* couldn't double */

				/* print roll */

				roll ();
				proll ();

				/* can he move? */
				if ((mvlim = movallow ()) == 0) {

					/* he can't */
					writel (toobad2);
					writel (*colorptr);
					writel (cantmv);
					nexturn ();
					continue;
				}

				/* get move */
				getmove ();
			}
		}


		/* don't worry about who won if quit */
		if (cturn == 0)
			break;

		/* fix cturn = winner */
		cturn /= -2;

		wrboard ();

		/* backgammon? */

		mflag = 0;
		l = bar + 7 * cturn;
		for (i = bar; i != l; i += cturn)
			if (board[i] * cturn)
				mflag++;

		/* compute game value */

		if (*offopp == 15) {
			if (mflag) {
				writel (bgammon);
				gvalue *= 3;
			} else if (*offptr <= 0) {
				writel (gammon);
				gvalue *= 2;
			}
		}


		/* report situation */

		if (cturn == -1) {
			writel ("Red wins ");
			rscore += gvalue;
		} else {
			writel ("White wins ");
			wscore += gvalue;
		}
		wrint (gvalue);
		writel (" point");
		if (gvalue > 1)
			writec ('s');
		writel (".\n");

		/* write score */
		wrscore ();

		/* HERE: we don't ask for another game, the plugin only plays a single
		   game */

		/* see if he wants another game */

		writel (again);
		if ((i = yorn ('S')) == 0)
			break;

		init ();

		/* yes, reset game */
		wrboard ();
	}


	/* leave peacefully */

	getout ();

#endif
}


/* End of File */
