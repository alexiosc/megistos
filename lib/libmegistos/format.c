/*****************************************************************************\
 **                                                                         **
 **  FILE:     format.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Low level text formatting and output routines                **
 **  NOTES:    This critter defines a formatting language of its own. You   **
 **            embed formatting commands in BBS prompts. Commands have the  **
 **            following format:                                            **
 **                                                                         **
 **            <ESC>!<command>           or                                 **
 **            <ESC>!<number><command>                                      **
 **                                                                         **
 **            These are the commands:                                      **
 **                                                                         **
 **            L: Start formatting text. Format mode will be left-flush.    **
 **                                                                         **
 **            R: Start formatting text. Format mode will be right-flush.   **
 **                                                                         **
 **            C: Start formatting text. Format mode will be centering.     **
 **                                                                         **
 **            W: Start formatting text. Format mode will be wrap-around.   **
 **               This mode allows you to format rugged-edge text so that   **
 **               words are not split in two lines.                         **
 **                                                                         **
 **            J: Start formatting text. Format mode will be justify. This  **
 **               one produces straight-edge text from left to right        **
 **               border.                                                   **
 **                                                                         **
 **            l (lower case 'L'): Place left margin. If preceded by a      **
 **               number, this sets the left margin to <number> characters: **
 **                                                                         **
 **               |<--------- physical line length -------->|               **
 **               |<-- number-->|Left Margin                |               **
 **                                                                         **
 **               If not preceded by a number, this command sets the left   **
 **               margin to the current cursor position.                    **
 **                                                                         **
 **            i: Works just like 'l', but sets the left margin AFTER the   **
 **               current line ('l' affects the current line too). This     **
 **               is useful for paragraphs like the one you are reading     **
 **               now, where an indentation is required for all but the     **
 **               first paragraph line.                                     **
 **                                                                         **
 **            r: Place right margin. If preceded by a number, this sets    **
 **               the right margin to <number> characters:                  **
 **                                                                         **
 **               |<--------- physical line length -------->|               **
 **               |               Right Margin|<-- number-->|               **
 **                                                                         **
 **               If not preceded by a number, this command sets the right  **
 **               margin to the current cursor position.                    **
 **                                                                         **
 **            F: If preceded by a number, this command repeats the char    **
 **               following it <number> times. That is, <esc>!10F- will     **
 **               format as ----------. If not preceded by a number, the    **
 **               character following the 'F' is repeated all the way to    **
 **               the right border.                                         **
 **                                                                         **
 **            ( (open parenthsesis): Begin formatting using last set mode. **
 **               This begins formatting, starts taking into account        **
 **               margins, etc. When wrapping/justifying, use this to       **
 **               begin a new paragraph.                                    **
 **                                                                         **
 **            ): Stop formatting. All subsequent output will be dumped to  ** 
 **               the output stream as-is, until another format command is  **
 **               encountered. Stops using set margins, etc. When wrap-     **
 **               ping/justifying, use this to end a paragraph so that      **
 **               newline characters are not transformed into horizontal    **
 **               spacing.                                                  **
 **                                                                         **
 **            Z: Zero the horizontal position counter. Start formatting    **
 **               from this position.                                       **
 **                                                                         **
 **            v: Set parsing of variables (@VAR@-style embedded vars).     **
 **               Requires a value. A value of 0 inhibits parsing of vars,  **
 **               allowing normal use of the '@' symbol (use this in        **
 **               places where the user is likely to use this symbol, eg    **
 **               pages, reading mail, etc. A non-zero value enables        **
 **               variables, giving the '@' symbol its special meaning      **
 **               (ie you'll have to use '@@' to echo '@', etc).            **
 **                                                                         **
 **            P: Force a pause, wait for the user to press any key.        **
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
 * $Id$
 *
 * $Log$
 * Revision 1.6  2003/12/19 13:24:10  alexios
 * Updated include directives.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.9  2000/01/06 10:56:23  alexios
 * Changed calls to write(2) to send_out().
 *
 * Revision 0.8  1998/12/27 14:31:16  alexios
 * Added support for autoconf.
 *
 * Revision 0.7  1998/07/24 10:08:57  alexios
 * No changes.
 *
 * Revision 0.6  1997/12/02 20:42:14  alexios
 * Fixed formatting bug when (Q)uit is pressed.
 *
 * Revision 0.5  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/06 16:52:10  alexios
 * Fixed slight formatting bug with PAUSE_QUIT.
 *
 * Revision 0.3  1997/11/03 00:34:41  alexios
 * Changed all calls to xlwrite() to write() since emud now
 * handles all translations itself.
 *
 * Revision 0.2  1997/09/12 12:49:41  alexios
 * Fixed blocking bug by calling resetblocking() instead of just
 * blocking().
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SEND_OUT 1
#include <megistos/bbsinclude.h>

#include <megistos/config.h>
#include <megistos/bbsmod.h>
#include <megistos/useracc.h>
#include <megistos/miscfx.h>
#include <megistos/prompts.h>
#include <megistos/format.h>
#include <megistos/output.h>
#include <megistos/input.h>

#include "mbk_sysvar.h"


#define INHIBIT_FORMATTING (inhibit||IS_BOT)
#define IS_BOT (out_flags&OFL_ISBOT)

#define FFL_FORMAT     0x0000000f
#define FFL_FLUSHLEFT  0x00000000
#define FFL_FLUSHRIGHT 0x00000001
#define FFL_CENTRE     0x00000002
#define FFL_WRAP       0x00000004
#define FFL_JUSTIFY    0x00000008
#define FFL_BEGIN      0x00000010
#define FFL_END        0x00000020
#define FFL_NOMARGINS  0x00000040
#define FFL_SUBINDENT  0x00000080

#define CLEAR   (FFL_FORMAT|FFL_NOMARGINS|FFL_END)
#define INDENTS (FFL_NOMARGINS|FFL_SUBINDENT)


static int inhibit = 0;
static int LINELEN = 80;
static int RMARGIN = 1;
static int LMARGIN = 0;
static int SINDLM = 0;
static long flags = FFL_FLUSHLEFT;
static int xpos = 0;
static char prevline[1024];
static int plidx = 0;
static char command[64];
static int comidx = 0;
static int comstate = 0;
static char lastc = 32;
static int lastpos = 0;
static char *lastp = NULL;
static int screenvpos = 0;
static int savepos = 0;
static char fmtbuf[16384];
static char *pausetxt = NULL;
int     fmt_verticalformat = 0;
int     fmt_screenheight = 23;
int     fmt_lastresult = 0;


void
fmt_setpausetext (char *s)
{
	if (pausetxt != NULL) {
		free (pausetxt);
		pausetxt = NULL;
	}
	if (s != NULL)
		pausetxt = s;
}


char   *
strins (char *s, int index, char *what)
{
	char    before[1024] = { 0 }, *cp = s + index;
	static char retbuf[8192];

	if (index)
		memcpy (before, s, index);
	sprintf (retbuf, "%s%s%s", before, what, cp);
	return retbuf;
}


void
justify (char *s)
{
	int     numspaces = LINELEN - RMARGIN - LMARGIN - lastpos;
	float   spacing;
	int     i;
	char   *cp, *p;

	if (numspaces <= 0)
		return;
	spacing = strlen (s) / numspaces;
	for (i = 0; i < numspaces; i++) {
		cp = s + (int) (((float) (i + 1)) * spacing);
		for (p = cp; *p && !(*p == 32); p++);
		if (*p) {
			strcpy (s, strins (s, p - s, " "));
		} else {
			for (p = cp; p >= s && !(*p == 32); p--);
			if (p >= s) {
				strcpy (s, strins (s, p - s, " "));
			} else
				break;
		}
	}
}


void
formatandoutput (char *s)
{
	char   *cp = s;
	char    c;

	lastp = NULL;
	while ((c = *cp) != 0) {
		if (flags & FFL_BEGIN && flags & (FFL_WRAP | FFL_JUSTIFY)) {
			if (c == 10 || c == 13)
				c = 32;
			if (lastc != 32 && c == 32) {
				lastpos = xpos;
			}
			lastc = c;
		}

		prevline[plidx] = 0;
		switch (comstate) {
		case 0:
			if (c == 27) {
				command[0] = 0;
				comidx = 0;
				comstate = 1;
				comidx = 0;
			} else if (c >= 0 && c < 32) {
				prevline[plidx++] = c;
			} else {
				prevline[plidx++] = c;
				xpos++;
			}
			prevline[plidx] = 0;
			break;
		case 1:
			if (c == '[') {
				comstate = 2;
			} else if (c == '!') {
				comstate = 3;
			} else {
				comstate = 0;
				prevline[plidx++] = c;
			}
			prevline[plidx] = 0;
			break;
		case 2:
			if (!comidx) {
				prevline[plidx++] = 27;
				prevline[plidx++] = '[';
				prevline[plidx] = 0;
			}
		case 3:
			if (comstate != 3) {
				prevline[plidx++] = c;
				prevline[plidx] = 0;
			}
			if (isdigit (c) || c == ';') {
				command[comidx++] = c;
			} else {
				command[comidx] = 0;
				if (comstate == 2) {
					switch (c) {
					case 'C':
						if (command[0])
							xpos =
							    min (LINELEN - 1,
								 xpos +
								 atoi
								 (command));
						else
							xpos =
							    min (LINELEN - 1,
								 xpos + 1);
						break;
					case 'D':
						if (command[0])
							xpos =
							    max (0,
								 xpos -
								 atoi
								 (command));
						else
							xpos =
							    max (0, xpos - 1);
						break;
					case 'J':
						xpos = 0;
						break;
					case 'H':
						{
							int     i, j;

							if (sscanf
							    (command, "%d;%d",
							     &i, &j) == 2)
								xpos = j - 1;
							else
								xpos = 0;
							if (xpos < 0)
								j = 0;
							else if (xpos >=
								 LINELEN)
								xpos =
								    LINELEN -
								    1;
							break;
						}
					case 's':
						savepos = xpos;
						break;
					case 'u':
						xpos = savepos;
						break;
					}
				} else if (comstate == 3) {
					if (!INHIBIT_FORMATTING) {
						switch (c) {
						case 'L':
							flags =
							    (flags & ~CLEAR) |
							    FFL_FLUSHLEFT |
							    FFL_BEGIN;
							break;
						case 'R':
							flags =
							    (flags & ~CLEAR) |
							    FFL_FLUSHRIGHT |
							    FFL_BEGIN;
							break;
						case 'C':
							flags =
							    (flags & ~CLEAR) |
							    FFL_CENTRE |
							    FFL_BEGIN;
							break;
						case 'W':
							flags =
							    (flags & ~CLEAR) |
							    FFL_WRAP |
							    FFL_BEGIN;
							break;
						case 'J':
							flags =
							    (flags & ~CLEAR) |
							    FFL_JUSTIFY |
							    FFL_BEGIN;
							break;
						case '(':
							flags =
							    (flags &
							     ~FFL_SUBINDENT) |
							    FFL_BEGIN;
							break;
						case ')':
							flags |= FFL_END;
							break;
						case 'r':
							if (strlen (command))
								RMARGIN =
								    min
								    (LINELEN -
								     10,
								     atoi
								     (command));
							else
								RMARGIN =
								    min
								    (LINELEN -
								     10,
								     LINELEN -
								     xpos);
							break;
						case 'i':
							flags |= FFL_SUBINDENT;
							if (strlen (command))
								SINDLM =
								    min
								    (LINELEN -
								     10,
								     atoi
								     (command));
							else
								SINDLM =
								    min
								    (LINELEN -
								     10, xpos);
							break;
						case 'l':
							if (strlen (command))
								LMARGIN =
								    min
								    (LINELEN -
								     10,
								     atoi
								     (command));
							else
								LMARGIN =
								    min
								    (LINELEN -
								     10, xpos);
							SINDLM = LMARGIN;
							break;
						case 'F':
							if (*(cp + 1)) {
								char















								 
								    
								    
								    
								    
								    
								    
								    multiple
								    [256] =
								    { 0 };
								char














								 
								    
								    
								    
								    
								    
								    
								    temp[1024];
								int















								 
								    
								    
								    
								    
								    
								    
								    reps =
								    atoi
								    (command);
								memset
								    (multiple,
								     *(cp + 1),
								     (reps ?
								      reps :
								      LINELEN -
								      LMARGIN -
								      RMARGIN -
								      xpos));

								sprintf (temp,
									 "%s%s",
									 multiple,
									 cp +
									 2);
								strcpy (cp + 1,
									temp);
							}
							break;
						case 'Z':
							xpos = 0;
							break;
						case 'v':
							if (!strlen (command))
								out_clearflags
								    (OFL_INHIBITVARS);
							else
								__out_setclear
								    (OFL_INHIBITVARS,
								     (atoi
								      (command)
								      == 0));
							break;
						case 'P':
							{
								char
								        c;
								char
								       *buf;

								msg_set
								    (msg_sys);
								buf =
								    msg_get
								    (W2CLR);
								out_send
								    (fileno
								     (stdout),
								     buf,
								     strlen
								     (buf));
								msg_reset ();
								read (0, &c,
								      1);
								inp_resetidle
								    ();
							}
						}
					}
				}
				comstate = 0;
			}
			break;
		}

		if (flags & (FFL_WRAP | FFL_JUSTIFY) && flags & FFL_BEGIN) {
			char   *sp = strrchr (prevline, 32);

			if (xpos > LINELEN - RMARGIN - LMARGIN) {
				char    lpadding[256] = { 0 };
				if (sp) {
					*sp = 0;
					if (flags & FFL_JUSTIFY)
						justify (prevline);
					if (LMARGIN && (flags & INDENTS) == 0) {
						memset (lpadding, 32, LMARGIN);
					}
					flags &= ~INDENTS;
					LMARGIN = SINDLM;
					sprintf (fmtbuf, "%s%s\n", lpadding,
						 prevline);
					out_send (fileno (stdout), fmtbuf,
						  strlen (fmtbuf));
					if (fmt_screenpause () == PAUSE_QUIT) {
						flags = FFL_FLUSHLEFT;
						plidx = 0;
						prevline[plidx] = 0;
						return;
					}
					flags &= ~FFL_SUBINDENT;
/*	  cp-=strlen(prevline)-(sp-prevline); */
					{
						char    c =
						    *(cp + 1), *tp =
						    (cp + 1), nl, *np;
						*(cp + 1) = 0;
						nl = *cp;
						if (*cp == 13 || *cp == 10) {
							*cp = 32;
						}
						for (np = &s[(int)
							     (strlen (s) - 1)];
						     s != np && *np != 32 &&
						     *np != 10; np--);
						cp = np;
						*cp = nl;
						*tp = c;
					}
				} else {
					if (LMARGIN && (flags & INDENTS) == 0) {
						memset (lpadding, 32, LMARGIN);
					}
					flags &= ~INDENTS;
					LMARGIN = SINDLM;
					sprintf (fmtbuf, "%s%s\n", lpadding,
						 prevline);
					out_send (fileno (stdout), fmtbuf,
						  strlen (fmtbuf));
					if (fmt_screenpause () == PAUSE_QUIT) {
						flags = FFL_FLUSHLEFT;
						plidx = 0;
						prevline[plidx] = 0;
						return;
					}
					flags &= ~FFL_SUBINDENT;
				}
				xpos = 0;
				plidx = 0;
			}
			if (flags & FFL_END)
				flags &= ~(FFL_BEGIN);
		}

		if (((flags & FFL_BEGIN) != 0)
		    && (((flags & FFL_CENTRE) != 0) ||
			((flags & FFL_FLUSHRIGHT) != 0))
		    && ((c == 10) || (c == 13))) {
			char    padding[256] = { 0 }, lpadding[256] = {
			0};
			int     numspaces =
			    LINELEN - RMARGIN - LMARGIN - xpos + 1;

			if (flags & FFL_CENTRE)
				numspaces /= 2;
			if (numspaces < 0 || numspaces > 255) {
				padding[0] = 0;
			} else
				memset (padding, 32, numspaces);
			prevline[plidx] = 0;

			if (LMARGIN && (flags & INDENTS) == 0) {
				memset (lpadding, 32, LMARGIN);
			}
			flags &= ~INDENTS;
			LMARGIN = SINDLM;
			sprintf (fmtbuf, "%s%s%s", lpadding, padding,
				 prevline);
			if (fmt_screenpause () == PAUSE_QUIT) {
				flags = FFL_FLUSHLEFT;
				plidx = 0;
				prevline[plidx] = 0;
				return;
			}
			out_send (fileno (stdout), fmtbuf, strlen (fmtbuf));
			flags &= ~FFL_SUBINDENT;
			if (flags & FFL_END)
				flags &= ~(FFL_BEGIN);
			xpos = 0;
			plidx = 0;
		} else if (flags & FFL_BEGIN &&
			   ((flags & FFL_FORMAT) == FFL_FLUSHLEFT)
			   && (c == 10 || c == 13)) {
			char    lpadding[256] = { 0 };
			if (LMARGIN && (flags & INDENTS) == 0) {
				memset (lpadding, 32, LMARGIN);
			}
			flags &= ~INDENTS;
			LMARGIN = SINDLM;
			sprintf (fmtbuf, "%s%s", lpadding, prevline);
			if (fmt_screenpause () == PAUSE_QUIT) {
				flags = FFL_FLUSHLEFT;
				plidx = 0;
				prevline[plidx] = 0;
				return;
			}
			out_send (fileno (stdout), fmtbuf, strlen (fmtbuf));
			flags &= ~FFL_SUBINDENT;
			if (flags & FFL_END)
				flags &= ~(FFL_BEGIN);
			lastpos = 0;
			lastc = -1;
			xpos = 0;
			plidx = 0;
		} else if ((flags & FFL_BEGIN) == 0 && (c == 10 || c == 13)) {
			char    lpadding[256] = { 0 };
			if (flags & FFL_END) {
				if (LMARGIN && (flags & INDENTS) == 0) {
					memset (lpadding, 32, LMARGIN);
				}
				flags &= !FFL_END;
			}
			flags &= ~INDENTS;
			LMARGIN = SINDLM;
			sprintf (fmtbuf, "%s%s", lpadding, prevline);
			if (fmt_screenpause () == PAUSE_QUIT) {
				flags = FFL_FLUSHLEFT;
				plidx = 0;
				prevline[plidx] = 0;
				return;
			}
			out_send (fileno (stdout), fmtbuf, strlen (fmtbuf));
			flags &= ~FFL_SUBINDENT;
			if (flags & FFL_END)
				flags &= ~(FFL_BEGIN | FFL_END);
			lastpos = 0;
			lastc = -1;
			xpos = 0;
			plidx = 0;
		}
		cp++;
	}
	{
		char    lpadding[256] = { 0 };
		if (flags & (FFL_BEGIN | FFL_END) && (flags & INDENTS) == 0) {
			memset (lpadding, 32, LMARGIN);
		}
		flags &= ~INDENTS;
		LMARGIN = SINDLM;
		prevline[plidx] = 0;
		if (flags & (FFL_WRAP | FFL_JUSTIFY) ||
		    ((flags & FFL_FORMAT) == 0)) {
			sprintf (fmtbuf, "%s%s", lpadding, prevline);
/*      if(fmt_screenpause()==PAUSE_QUIT){
	flags=FFL_FLUSHLEFT;
	plidx=0;
	prevline[plidx]=0;
	return;
      } */
			out_send (fileno (stdout), fmtbuf, strlen (fmtbuf));
			flags &= ~FFL_SUBINDENT;
			plidx = 0;
			prevline[plidx] = 0;
			flags |= FFL_NOMARGINS;
		}
	}
}


void
fmt_output (char *s)
{
	if (((!strstr (s, "\033!")) && ((flags & FFL_FORMAT) == 0)) || inhibit) {
		char   *cp, *lp = s;

		while (*lp) {
			cp = lp;
			while (*cp && (*cp != '\n'))
				cp++;
			if (*cp) {
				char    c = '\n';

				*cp = 0;
				out_send (fileno (stdout), lp, strlen (lp));
				out_send (fileno (stdout), &c, 1);
				if (fmt_screenpause () == PAUSE_QUIT)
					return;
				*cp = c;
				lp = cp + 1;
			} else {
				out_send (fileno (stdout), lp, strlen (lp));
				break;
			}
		}
		return;
	}

	formatandoutput (s);
}


void
fmt_setlinelen (int i)
{
	LINELEN = i;
}


void
fmt_setformatting (int i)
{
	inhibit = (i == 0);
	fmt_lastresult = 0;
}


void
fmt_setverticalformat (int i)
{
	fmt_verticalformat = i;
	fmt_lastresult = 0;
}


void
fmt_setscreenheight (int i)
{
	fmt_screenheight = i;
	fmt_lastresult = 0;
}


int
fmt_screenpause ()
{
	/* Bots don't need to pause */
	if (IS_BOT)
		return 0;

	screenvpos++;
	if (screenvpos >= fmt_screenheight - 2) {
		screenvpos = 0;
		if (!fmt_verticalformat || fmt_lastresult == PAUSE_NONSTOP)
			return 0;
		else
			return fmt_forcedpause ();
	}
	return 0;
}


int
fmt_forcedpause ()
{
	char    c;
	int     i, j;

	inp_block ();

	if (pausetxt != NULL)
		out_send (fileno (stdout), pausetxt, strlen (pausetxt));

	read (0, &c, 1);
	inp_resetidle ();
	switch (toupper (c)) {
	case 'N':
		fmt_lastresult = PAUSE_NONSTOP;
		break;
	case 'Q':
		fmt_lastresult = PAUSE_QUIT;
		flags = FFL_FLUSHLEFT;
		SINDLM = 0;
		xpos = 0;
		break;
	case 'S':
		screenvpos = fmt_screenheight;
	default:
		fmt_lastresult = PAUSE_CONTINUE;
	}

	if (pausetxt) {
		j = strlen (pausetxt);
		for (i = 0; i < j; i++) {
			const char s[] = "\010 \010";

			out_send (fileno (stdout), (char *) s, strlen (s));
		}
	}

	inp_resetblocking ();
	return fmt_lastresult;
}


void
fmt_resetvpos (int i)
{
	screenvpos = i;
	fmt_lastresult = 0;
}
