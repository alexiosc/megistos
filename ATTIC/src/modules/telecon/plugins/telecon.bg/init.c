/*****************************************************************************\
 **                                                                         **
 **  FILE:     init.c                                                       **
 **  AUTHORS:  Alexios (et al)                                              **
 **  PURPOSE:                                                               **
 **  NOTES:                                                                 **
 **  LEGALESE: See below.                                                   **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id: init.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: init.c,v $
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
    "$Id: init.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



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



/*
 * variable initialization.
 */

				/* name of executable object programs */

int     pnum = 2;		/* color of player:
				   -1 = white
				   1 = red
				   0 = both
				   2 = not yet init'ed */

int     acnt = 0;		/* length of args */
int     aflag = 1;		/* flag to ask for rules or instructions */
int     bflag = 0;		/* flag for automatic board printing */
int     cflag = 0;		/* case conversion flag */
int     hflag = 1;		/* flag for cleaning screen */
int     mflag = 0;		/* backgammon flag */
int     raflag = 0;		/* 'roll again' flag for recovered game */
int     rflag = 0;		/* recovered game flag */
int     iroll = 0;		/* special flag for inputting rolls */
int     rfl = 0;

char   *color[] = { "White", "Red", "white", "red" };


/* End of File */
