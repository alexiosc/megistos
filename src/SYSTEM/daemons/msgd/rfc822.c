/*****************************************************************************\
 **                                                                         **
 **  FILE:     rfc822.c                                                     **
 **  AUTHORS:  [UNKNOWN]                                                    **
 **  REVISION: A, May 1995, Version 0.1                                     **
 **  PURPOSE:  Declare functions to deal with RFC822 mail headers           **
 **  NOTES:    The functions in this file are from the ELM 2.4b source      **
 **            suite.                                                       **
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
 * Revision 1.1  2001/04/16 15:00:42  alexios
 * Initial revision
 *
 * Revision 0.4  1998/12/27 16:28:24  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:27:56  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:16:29  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:16:40  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#include <bbsinclude.h>

#include <sys/termios.h>
#include "bbs.h"


/* The following functions are from the ELM 2.4b mailer source. */
/* All rights reserved:                                         */

/*******************************************************************************
 *  The Elm Mail System  -  $Revision$   $State$
 *
 *			Copyright (c) 1988-1992 USENET Community Trust
 *			Copyright (c) 1986,1987 Dave Taylor
 *******************************************************************************/


/* BEGINNING OF INCLUDED SOURCE */

/*
 * rfc822_toklen(str) - Returns length of RFC-822 token that starts at "str".
 *
 * We understand the following tokens:
 *
 *	linear-white-space
 *	specials
 *	"quoted string"
 *	[domain.literal]
 *	(comment)
 *	CTL  (control chars)
 *	atom
 */

#define charlen(s)	((s)[0] == '\\' && (s)[1] != '\0' ? 2 : 1)

#define IS822_SPECIAL(c) ( \
	((c) == '(') || ((c) == ')') || ((c) == '<') || ((c) == '>') \
	|| ((c) == '@') || ((c) == ',') || ((c) == ';') || ((c) == ':') \
	|| ((c) == '\\') || ((c) == '"') || ((c) == '.') || ((c) == '[') \
	|| ((c) == ']') \
)

/*
 * RFC-822 defines SPACE to be just < > and HTAB, but after LWSP folding
 * CR and NL should be equivalent.
 */
#define IS822_SPACE(c) ((c) == ' ' || (c) == '\t' || (c) == '\r' || (c) == '\n')

/*
 * We've thrown non-ASCII (value > 0177) into this.
 */
#define IS822_CTL(c)	((c) <= 037 || (c) >= 0177)

#define IS822_ATOMCH(c)	(!IS822_SPECIAL(c) && !IS822_SPACE(c) && !IS822_CTL(c))


int rfc822_toklen(str)
register char *str;
{
	char *str0;
	int depth;

	str0 = str;

	if (*str == '"') {			/* quoted-string */
		++str;
		while (*str != '\0' && *str != '"')
			str += charlen(str);
		if (*str != '\0')
			++str;
		return (str-str0);
	}

	if (*str == '(' ) {			/* comment */
		++str;
		depth = 0;
		while (*str != '\0' && (*str != ')' || depth > 0)) {
			switch (*str) {
			case '(':
				++str;
				++depth;
				break;
			case ')':
				++str;
				--depth;
				break;
			default:
				str += charlen(str);
				break;
			}
		}
		if (*str != '\0')
			++str;
		return (str-str0);
	}


	if (*str == '[') {			/* domain-literal */
		++str;
		while (*str != '\0' && *str != ']')
			str += charlen(str);
		if (*str != '\0')
			++str;
		return (str-str0);
	}

	if (IS822_SPACE(*str)) {		/* linear-white-space */
		while (++str, IS822_SPACE(*str))
			;
		return (str-str0);
	}

	if (IS822_SPECIAL(*str) || IS822_CTL(*str))
		return charlen(str);		/* specials and CTL */

	/*
	 * Treat as an "atom".
	 */
	while (IS822_ATOMCH(*str))
		++str;
	return (str-str0);
}


int
len_next_part(str)
register char *str;
{
	register char *s;

	switch (*str) {

	case '\0':
		return 0;

	case '\\':
		return (*++str != '\0' ? 2 : 1);

	case '"':
		for (s = str+1 ; *s != '\0' ; ++s) {
			if (*s == '\\') {
				if (*++s == '\0')
					break;
			} else if (*s == '"') {
				++s;
				break;
			}
		}
		return (s - str);

	default:
		return 1;

	}

	/*NOTREACHED*/
}


static char paren_buffer[1024];

char *strip_parens(src)
register char *src;
{
	register int len;
	register char *dest = paren_buffer;

	while (*src != '\0') {
		len = rfc822_toklen(src);
		if (*src != '(') {	/*)*/
			strncpy(dest, src, len);
			dest += len;
		}
		src += len;
	}
	*dest = '\0';
	return paren_buffer;
}


void
get_address_from(line, buffer)
char *line, *buffer;
{
	/** This routine extracts the address from either a 'From:' line
	    or a 'Reply-To:' line.  The strategy is as follows:  if the
	    line contains a '<', then the stuff enclosed is returned.
	    Otherwise we go through the line and strip out comments
	    and return that.  White space will be elided from the result.
	**/

    register char *s;
    register int l;

    /**  Skip start of line over prefix, e.g. "From:".  **/
    if ((s = index(line, ':')) != NULL)
	line = s + 1;

    /*
     * If there is a '<' then copy from it to '>' into the buffer.  We
     * used to search with an "index()", but we need to handle RFC-822
     * conventions (e.g. "<" within a double-quote comment) correctly.
     */
    for (s = line ; *s != '\0' && *s != '<' ; s += len_next_part(s))
	;
    if (*s == '<') {
	++s;
	while (*s != '\0' && *s != '>') {
	    if ((l = len_next_part(s)) == 1 && isspace(*s)) {
		++s; /* elide embedded whitespace */
	    } else {
		while (--l >= 0)
		    *buffer++ = *s++;
	    }
	}
	*buffer = '\0';
	return;
    }

    /**  Otherwise, strip comments and get address with whitespace elided.  **/
    s = strip_parens(line);
    while (*s != '\0') {
	l = len_next_part(s);
	if (l == 1) {
	  if ( !isspace(*s) )
	    *buffer++ = *s;
	  s++;
	} else {
	  while (--l >= 0)
	    *buffer++ = *s++;
	}
    }
    *buffer = '\0';

}

/* END OF INCLUDED SOURCE */
