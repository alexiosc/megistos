/*****************************************************************************\
 **                                                                         **
 **  FILE:     format.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, March 95, Version 0.5 alpha                               **
 **  PURPOSE:  The Visual Editor formatting functions                       **
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
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2003/12/29 07:50:12  alexios
 * Renamed getline() to vised_getline() to disambiguate it from a GNU
 * extension in stdio.h.
 *
 * Revision 1.5  2003/12/24 19:43:34  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/23 23:20:22  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1998/12/27 16:35:48  alexios
 * Added autoconf support.
 *
 * Revision 0.6  1998/08/14 12:01:28  alexios
 * No changes.
 *
 * Revision 0.5  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 10:50:43  alexios
 * Stopped using xlgetmsg() and reverted to getmst() since emud
 * now performs all translations itself.
 *
 * Revision 0.3  1997/09/12 13:41:18  alexios
 * Used translated message blocks instead of raw ones.
 *
 * Revision 0.2  1997/08/31 09:23:15  alexios
 * Removed calls to the visual library, replaced them with ncurses
 * calls.
 *
 * Revision 0.1  1997/08/28 11:26:56  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "vised.h"
#include "mbk_vised.h"


void
formatline ()
{
	int     insp = min (cx, strlen (current->text));

	if (!NOWRAP) {
		char   *sp;

		numbytes -= strlen (current->text);
		sp = strrchr (current->text, 32);
		if (!sp)
			sp = &current->text[rmargin];
		*sp = 0;
		numbytes += strlen (current->text);
		insertline (current, sp + 1);
		showtext (-(cy - toprow + 1));
		movecursor (1, 2);
		insp = strlen (current->text);
	} else {
		if (formatmode == RIGHT) {
			char    temp[1024];
			int     len = strlen (current->text);

			if (len && len < rmargin) {
				memset (temp, 32, sizeof (temp));
				strcpy (&temp[rmargin - len], current->text);
				numbytes -= strlen (current->text);
				if (numbytes + strlen (temp) <= maxsize)
					strcpy (current->text, temp);
				else
					bel (ERRSIZ);
				numbytes += strlen (current->text);
				showtext (cy - toprow + 1);
				cx = strlen (current->text);
			}
		} else if (formatmode == CENTRE) {
			char    temp[1024], *cp = current->text;
			int     len;

			while (*cp == 32)
				cp++;
			len = strlen (cp);
			if (len && len < rmargin) {
				memset (temp, 32, sizeof (temp));
				strcpy (&temp[(rmargin - len) >> 1], cp);
				numbytes -= strlen (current->text);
				if (numbytes + strlen (temp) <= maxsize)
					strcpy (current->text, temp);
				else
					bel (ERRSIZ);
				numbytes += strlen (current->text);
				showtext (cy - toprow + 1);
				cx = strlen (current->text);
			}
		}
		newline ();
		insp = 0;
	}
}


void
rmspaces (unsigned char *s)
{
	char    temp[2048] = { 0 };
	int     i, j = 0, sp = 0;

	memset (temp, 0, sizeof (temp));
	for (i = 0; s[i]; i++) {
		if ((s[i] == 32) || (s[i] == 255))
			sp++;
		else
			sp = 0;
		if (sp <= 1)
			temp[j++] = s[i];
	}
	strcpy (s, temp);
}



char   *
nohsp (unsigned char *s)
{
	char   *cp = s;

	while (*cp == 32)
		cp++;
	return cp;
}


void
justify (char *s)
{
	char   *cp = s, *ep, *sp, temp[1024], c, *tp;
	int     len, l, n, i, t;

	while (cp[strlen (cp) - 1] == 32)
		cp[strlen (cp) - 1] = 0;
	while (*cp == 32)
		cp++;
	rmspaces (cp);
	len = rmargin - strlen (s);
	if ((tp = strchr (cp, 32)) != NULL)
		cp = tp;
	ep = strrchr (cp, 32);
	if (!ep)
		return;
	l = strlen (cp);
	n = ep - cp + 1;
	for (i = 0; i < len; i++) {
		t = (int) (((float) i) * (float) l / (float) len);
		ep = cp + t + i;
		if ((sp = strchr (ep, 32)) == NULL)
			sp = strrchr (cp, 32);
		if (!sp)
			return;
		c = *sp;
		*sp = 0;
		strcpy (temp, cp);
		strcat (temp, " ");
		*sp = c;
		strcat (temp, sp);
		strcpy (cp, temp);
	}
}



void
formatwrap (int pass)
{
	char    line[1024], temp[1024], carry[2048];
	struct line *l, *p = NULL;
	struct line *tf = NULL, *tl = NULL, *tip;
	int     len, dlines = 0, oldcy = cy, done = 0, added = 0;

	carry[0] = line[0] = 0;

	oldcy = cy;
	while (cy <= numlines && sameas (nohsp (current->text), ""))
		current = vised_getline (++cy);
	if (cy > numlines) {
		cy = oldcy;
		return;
	}

	if (cy > 1)
		tip = vised_getline (cy - 1);
	else {
		struct line *new = alcmem (sizeof (struct line));

		tip = NULL;
		cy++;
		added = 1;
		new->next = first;
		first = new;
		new->text = alcmem (1);
		new->text[0] = 0;
		numlines++;
	}

	for (; (cy <= numlines || carry[0]);) {
		if (cy <= numlines && !done) {
			if (cy > 1) {
				char    s[1024];
				int     i;

				p = vised_getline (cy - 1);
				strcpy (s, p->text);
				i = strlen (s) - 1;
/*	while((i>=0)&&(s[i]==32))s[i--]=0; */
				if (strcmp (p->text, s)) {
					numbytes -= strlen (p->text);
					free (p->text);
					p->text = alcmem (strlen (s) + 1);
					numbytes += strlen (s);
					strcpy (p->text, s);
				}
				l = p->next;
			} else {
				p = NULL;
				l = vised_getline (cy);
			}

			strcpy (temp, l->text);
			if (formatmode == JUSTIFY)
				rmspaces (temp);
			line[0] = 0;
			if (carry[0])
				sprintf (line, "%s ", carry);
			strcat (line, temp);
			if (temp[0] == 0 || sameas (temp, " "))
				done = 1;
			else
				deleteline (cy);
		} else if (!done && cy > numlines) {
			done = 1;
			continue;
		} else if (done && carry[0])
			strcpy (line, carry);
		else if (!carry[0])
			break;

		len = strlen (line);

		if (len == rmargin) {
			struct line *new = alcmem (sizeof (struct line));

			if (new) {
				new->text = (char *) alcmem (MAXLEN);
				strncpy (new->text, line, MAXLEN);
				new->next = NULL;
				if (!tf)
					tf = new;
				if (tl)
					tl->next = new;
				tl = new;
				numbytes += len + 1;
				dlines++;
			}
			carry[0] = 0;
		} else if (len > rmargin) {
			char   *cp, *sp = &line[rmargin], c;

			c = *sp;
			*sp = 0;
			cp = strrchr (line, 32);
			*sp = c;
			if (!cp)
				cp = sp;
			else
				c = 0;
			*cp = 0;

			{
				struct line *new =
				    alcmem (sizeof (struct line));
				if (new) {
					char    temp[1024];

					strcpy (temp, line);
					new->text = (char *) alcmem (MAXLEN);
					if (formatmode == JUSTIFY)
						justify (temp);
					strncpy (new->text, temp, MAXLEN);
					new->next = NULL;
					if (!tf)
						tf = new;
					if (tl)
						tl->next = new;
					tl = new;
					numbytes += len + 1;
					dlines++;
				}
			}
			if (!c)
				strcpy (carry, cp + 1);
			else
				sprintf (carry, "%c%s", c, cp + 1);
		} else {
			strcpy (carry, line);
			if (done)
				break;
		}
	}
	if (dlines && tf) {
		numlines += dlines;
		tl->next = p->next;
		p->next = tf;
		p = tl;
	}
	if (carry[0])
		insertline (p, carry);

	if (added) {
		struct line *new = first;

		first = first->next;
		cy--;
		added = 0;
		free (new->text);
		free (new);
		numlines--;
	}

	current = p->next;
	cy = getlinenum (current);
	movecursor ((pass == 0) && (cy < numlines), 2);
	if (pass) {
		formatwrap (0);
		counttext ();
		if (cy - toprow + 1 >= LINES - 2) {
			centerline ();
			showtext (0);
		} else {
			if (toprow == 1)
				centerline ();
			showtext (-(cy - toprow + 1));
		}
	} else {
		top = vised_getline (toprow);
		showtext (0);
	}
}


void
formatflush (int pass)
{
	char    line[1024], temp[1024], carry[2048];
	struct line *l, *p = NULL;
	struct line *tf = NULL, *tl = NULL, *tip;
	int     len, dlines = 0, oldcy = cy;

	carry[0] = line[0] = 0;

	oldcy = cy;
	while (cy <= numlines && sameas (current->text, ""))
		current = vised_getline (++cy);
	if (cy > numlines) {
		cy = oldcy;
		return;
	}

	if (cy > 1)
		tip = vised_getline (cy - 1);
	else
		tip = NULL;

	for (; cy <= numlines || carry[0];) {
		if (cy <= numlines) {
			if (cy > 1) {
				p = vised_getline (cy - 1);
				l = p->next;
			} else {
				p = NULL;
				l = vised_getline (cy);
			}

			strcpy (temp, nohsp (l->text));
			line[0] = 0;
			if (carry[0])
				sprintf (line, "%s ", carry);
			strcat (line, temp);
			if (line[0] == 0 || sameas (line, " "))
				break;
			deleteline (cy);
		} else
			strcpy (line, carry);

		len = strlen (line);


		if (len >= rmargin) {
			struct line *new = alcmem (sizeof (struct line));

			if (new) {
				new->text = (char *) alcmem (MAXLEN);
				strncpy (new->text, line, MAXLEN);
				new->next = NULL;
				if (!tf)
					tf = new;
				if (tl)
					tl->next = new;
				tl = new;
				numbytes += len + 1;
				dlines++;
			}
			carry[0] = 0;
		} else {
			char    temp[1024];

			if (len && len < rmargin) {
				memset (temp, 32, sizeof (temp));
				strcpy (&temp
					[(rmargin - len) >> (formatmode ==
							     CENTRE)], line);
				strcpy (line, temp);
				numbytes += strlen (line);
			}
			{
				struct line *new =
				    alcmem (sizeof (struct line));
				if (new) {
					new->text = (char *) alcmem (MAXLEN);
					strncpy (new->text, line, MAXLEN);
					new->next = NULL;
					if (!tf)
						tf = new;
					if (tl)
						tl->next = new;
					tl = new;
					numbytes += len + 1;
					dlines++;
				}
			}
			carry[0] = 0;
		}
	}
	if (dlines && tf) {
		numlines += dlines;
		tl->next = p->next;
		p->next = tf;
		p = tl;
	}
	if (carry[0])
		insertline (p, carry);

	current = p->next;
	cy = getlinenum (current);
	movecursor ((pass == 0) && (cy < numlines), 2);
	if (pass) {
		counttext ();
		if (cy - toprow + 1 >= LINES - 2) {
			centerline ();
			showtext (0);
		} else {
			showtext (-(cy - toprow + 1));
		}
	}
}


void
formatpara ()
{
	switch (formatmode) {
	case LEFT:
	case JUSTIFY:
		formatwrap (1);
		break;
	case RIGHT:
	case CENTRE:
		formatflush (1);
		break;
	}
	if (numbytes > maxsize)
		bel (ERRFMT);
}


void
rightmargin ()
{
	char    s[1024];
	int     i;

	move (LINES - 2, 0);
	printansi (msg_get (RMARG));
	refresh ();
	for (;;) {
		sprintf (s, "%d", rmargin);
		strcpy (s, getstg (s, 3));
		if (inp_isX (s) || s[0] == 0) {
			showstatus ();
			return;
		} else {
			i = atoi (s);
			if (i < 20 || i > 999) {
				showstatus ();
				return;
			} else {
				rmargin = i;
				showstatus ();
				return;
			}
		}
	}
}


/* End of File */
