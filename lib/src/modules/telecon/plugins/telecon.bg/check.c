/*****************************************************************************\
 **                                                                         **
 **  FILE:     check.c                                                      **
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
 * Revision 1.2  2001/04/16 21:56:33  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 1.0  1999/08/13 17:03:41  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



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



#include <stdio.h>
#include "back.h"



void
getmove () {
  register int i, c;

  c = 0;
  for (;;) {
    i = checkmove(c);
    
    switch (i) {
    case -1:
      if (movokay(mvlim)) {
	for (i = 0; i < mvlim; i++) if (h[i]) wrhit(g[i]);
	nexturn();
	if (*offopp == 15) cturn *= -2;
	if (pnum) bflag = pnum;
	return;
      }
      
    case -4:
    case 0:
      wrboard();
      if (i != 0 && i != -4) break;

      /* HERE: error: player must/can only make a certain number of moves */
      
      writel (*Colorptr);
      if (i == -4) writel (" must make ");
      else writel (" can only make ");
      writec (mvlim+'0');
      writel (" move");
      if (mvlim > 1) writec ('s');
      writec ('.');
      writec ('\n');
      break;
      
    case -3:

      /* HERE: quitting, is this necessary now? */

      if (quit()) return;
    }
    
    proll ();
  }
}



int
movokay (int mv)
{
  register int	i, m;

  if (d0) swap;
  
  /* HERE: printing errors */

  for (i = 0; i < mv; i++) {
    if (p[i] == g[i]) {
      moverr (i);
      writel ("Attempt to move to same location.\n");
      return (0);
    }
    
    if (cturn*(g[i]-p[i]) < 0) {
      moverr (i);
      writel ("Backwards move.\n");
      return (0);
    }
    
    if (abs(board[bar]) && p[i] != bar) {
      moverr (i);
      writel ("Men still on bar.\n");
      return (0);
    }
    
    if ((m = makmove(i))) {
      moverr (i);
      switch (m) {
      case 1:
	writel ("Move not rolled.\n");
	break;
	
      case 2:
	writel ("Bad starting position.\n");
	break;
	
      case 3:
	writel ("Destination occupied.\n");
	break;
	
      case 4:
	writel ("Can't remove men yet.\n");
      }
      return (0);
    }
  }
  return (1);
}
