/*****************************************************************************\
 **                                                                         **
 **  BlackJack game for AcroGATE Network                                    **
 **                                                                         **
 **  FILE: cards.c                                                          **
 **  AUTHOR: Vangelis Rokas                                                 **
 **  PURPOSE: card-drawing functions                                        **
 **  NOTES: This is a global card drawing library                           **
 **                                                                         **
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
 **                                                                         **
\*****************************************************************************/

/*
 * Special thanks to Antonis Stamboulis (Xplosion) for providing me source 
 * for the card drawing functions. I have used his primary source files with
 * slight modifications. (er 17-Oct-1999)
 *
 */

/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 15:00:09  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:53  alexios
 * Initial checkin.
 *
 * Revision 1.0  1999/10/17 09:17:49  valis
 * Initial revision
 *
 *
 */

#include <math.h>
#include <string.h>
#include <stdio.h>

#include "cards.h"

#ifdef MEGISTOS_BBS
#include "bbs.h"
#include "mbk_bjack.h"
#endif


#ifndef RCS_VER
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif

/* cards colors in ANSI format */

#ifndef MEGISTOS_BBS
#define ANSI_Black	"\033[0;30;47m"
#define ANSI_Red	"\033[0;31;47m"
#define ANSI_White	"\033[0;47m"
#define ANSI_Normal	"\033[0m"

char Card_Template[][7][9] = {
{ "ÚÄÄÄÄÄÄÄ¿",  "³2      ³",  "³   !   ³",  "³       ³",  "³   !   ³",  "³      2³",  "ÀÄÄÄÄÄÄÄÙ" },  
{ "ÚÄÄÄÄÄÄÄ¿",  "³3      ³",  "³   !   ³",  "³   !   ³",  "³   !   ³",  "³      3³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³4      ³",  "³  ! !  ³",  "³       ³",  "³  ! !  ³",  "³      4³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³5      ³",  "³  ! !  ³",  "³   !   ³",  "³  ! !  ³",  "³      5³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³6      ³",  "³  ! !  ³",  "³  ! !  ³",  "³  ! !  ³",  "³      6³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³7      ³",  "³ !   ! ³",  "³ ! ! ! ³",  "³ !   ! ³",  "³      7³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³8      ³",  "³ ! ! ! ³",  "³ !   ! ³",  "³ ! ! ! ³",  "³      8³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³9      ³",  "³ ! ! ! ³",  "³ ! ! ! ³",  "³ ! ! ! ³",  "³      9³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³10 !   ³",  "³ ! ! ! ³",  "³ !   ! ³",  "³ ! ! ! ³",  "³   ! 10³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³A      ³",  "³       ³",  "³   !   ³",  "³       ³",  "³      A³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³J  !   ³",  "³ ! ! ! ³",  "³ !   ! ³",  "³ ! ! ! ³",  "³   !  J³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³Q  !   ³",  "³ ! ! ! ³",  "³ !   ! ³",  "³ ! ! ! ³",  "³   !  Q³",  "ÀÄÄÄÄÄÄÄÙ" },
{ "ÚÄÄÄÄÄÄÄ¿",  "³K  !   ³",  "³ ! ! ! ³",  "³ !   ! ³",  "³ ! ! ! ³",  "³   !  K³",  "ÀÄÄÄÄÄÄÄÙ" }
};
#endif

char temp_buffer[15][150];		/* temporary buffer to store card images		*/


/* return card value as char, return 0 for 10 */
char card_value(int cardidx)
{
  char ar[] = "234567890AJQK";

	return (ar[cardidx % 13]);		// its 12 and not 13 because C counts from 0 (!!!)
}

/* return card sign as char */
char card_sign(int cardidx)
{
  char ar[] = "\003\004\005\006";	/* card suits */

  return (ar[cardidx/13]);
}


/* map a card row into internal buffer */
void map_card_row(char *buf,
		  int index,
		  int row,
		  int is_red,
		  int suit)
{
  int i;
  char b[500];
  char *s;

  if(row==0) {
    strcat(buf,msg_get(is_red?BJM_CARD_TOP_RED:BJM_CARD_TOP_BLACK));
  } else if(row==6) {
    strcat(buf,msg_get(is_red?BJM_CARD_BOTTOM_RED:BJM_CARD_BOTTOM_BLACK));
  } else {
    s=msg_get((is_red?BJM_CARD_L2R2:BJM_CARD_L2B2) + index*5 + row-1);

    for(i=0;i<strlen(s);i++) {
      if(s[i]=='!') b[0]=suit; else b[0]=s[i];
      b[1]='\0';
      strcat(buf, b);
    }
  }
}

/* map all cards passed through array to the internal buffer, uses map_card_row() */
void map_cards(int *array, int count)
{
  int i, k, st, en;

  st = 0;
  en = 7;

  for(i=0;i<15;i++) strcpy(temp_buffer[i], "");

  for(i=0;i<count;i++) {
    if(i>5) {st = 8; en = 16; strcpy(temp_buffer[7], " ");}
		
    for(k=st;k<en;k++)
      map_card_row(temp_buffer[k], array[i] % 13, k-st,
		   (card_sign(array[i]) <005), 
		   (int)card_sign(array[i]));
    
  }
}

/*
 * return a pointer to the internal card buffer, index represents the row
 * loop through 0 to 15 to display a maximum of 12 cards
 */
char *buf_index(int index)
{
	if(index<16) return temp_buffer[index];
  return "";
  
}


/* use printf() to draw cards on the screen */
void draw_cards(int *array, int count)
{
  int i;

	map_cards(array, count);
	for(i=0;i<15;i++) printf("%s (%i)\n", buf_index(i), strlen(temp_buffer[i]));
}

