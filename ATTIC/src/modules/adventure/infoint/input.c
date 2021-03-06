/*****************************************************************************\
 **                                                                         **
 **  FILE:     inp_buffer.c                                                      **
 **  AUTHORS:  Mark Howell (howell_ma@movies.enet.dec.com)                  **
 **            Alexios (porting to Megistos, adding some bells & whistles)  **
 **  PURPOSE:  Run Infocom games in a nice BBS environment.                 **
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
 **                                                                         **
 **  ORIGINAL CONDITION OF USE:                                             **
 **                                                                         **
 **  You are expressly forbidden to use this program if in so doing you     **
 **  violate the copyright notice supplied with the original Infocom game.  **
 **                                                                         **
 **  LICENSE AGREEMENT:                                                     **
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
 * $Id: input.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: input.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/24 20:30:29  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:16  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/08/13 16:59:43  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id: input.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";

/*
 * inp_buffer.c
 *
 * Input routines
 *
 */

#include "ztypes.h"

/* Statically defined word separator list */

static const char *separators = " \t\n\f.,?";
static zword_t dictionary_offset = 0;
static short dictionary_size = 0;
static unsigned int entry_size = 0;

static void tokenise_line (zword_t, zword_t, zword_t, zword_t);
static const char *next_token (const char *, const char **, int *,
			       const char *);
static zword_t find_word (int, const char *, long);



/*
 * read_character
 *
 * Read one character with optional timeout
 *
 *    argv[0] = # of characters to read (only 1 supported currently)
 *    argv[1] = timeout value in seconds (optional)
 *    argv[2] = timeout action routine (optional)
 *
 */

void
read_character (int argc, zword_t * argv)
{
	int     c;
	zword_t arg_list[2];

	/* Supply default parameters */

	if (argc < 3)
		argv[2] = 0;
	if (argc < 2)
		argv[1] = 0;

	/* Flush any buffered output before read */

	flush_buffer (FALSE);

	/* Reset line count */

	lines_written = 0;

	/* If more than one characters was asked for then fail the call */

	if (argv[0] != 1)

		c = 0;

	else {

		if ((c = playback_key ()) == -1) {

			/* Setup the timeout routine argument list */

			arg_list[0] = argv[2];
			arg_list[1] = argv[1];

			/* Read a character with a timeout. If the inp_buffer timed out then
			   call the timeout action routine. If the return status from the
			   timeout routine was 0 then try to read a character again */

			do {
				c = input_character ((int) argv[1]);
			} while (c == -1 && call (2, arg_list, ASYNC) == 0);

			/* Fail call if inp_buffer timed out */

			if (c == -1)
				c = 0;
			else
				record_key (c);
		}
	}

	store_operand (c);

}



/*
 * read_line
 *
 * Read a line of inp_buffer with optional timeout.
 *
 *    argv[0] = character buffer address
 *    argv[1] = token buffer address
 *    argv[2] = timeout value in seconds (optional)
 *    argv[3] = timeout action routine (optional)
 *
 */

void
read_line (int argc, zword_t * argv)
{
	int     i, in_size, out_size, terminator;
	char   *cbuf, *buffer;

	/* Supply default parameters */

	if (argc < 4)
		argv[3] = 0;
	if (argc < 3)
		argv[2] = 0;
	if (argc < 2)
		argv[1] = 0;

	/* Refresh status line */

	if (h_type < V4)
		display_status_line ();

	/* Flush any buffered output before read */

	flush_buffer (TRUE);

	/* Reset line count */

	lines_written = 0;

	/* Initialise character pointer and initial read size */

	cbuf = (char *) &datap[argv[0]];
	in_size = (h_type > V4) ? cbuf[1] : 0;

	/* Read the line then script and record it */

	terminator = get_line (cbuf, argv[2], argv[3]);
	script_line ((h_type > V4) ? &cbuf[2] : &cbuf[1]);
	record_line ((h_type > V4) ? &cbuf[2] : &cbuf[1]);

	/* Convert new text in line to lowercase */

	if (h_type > V4) {
		buffer = &cbuf[2];
		out_size = cbuf[1];
	} else {
		buffer = &cbuf[1];
		out_size = strlen (buffer);
	}

	if (out_size > in_size)
		for (i = in_size; i < out_size; i++)
			buffer[i] = (char) tolower (buffer[i]);

	/* Tokenise the line, if a token buffer is present */

	if (argv[1])
		tokenise_line (argv[0], argv[1], h_words_offset, 0);

	/* Return the line terminator */

	if (h_type > V4)
		store_operand ((zword_t) terminator);

}



/*
 * get_line
 *
 * Read a line of inp_buffer and lower case it.
 *
 */

int
get_line (char *cbuf, zword_t timeout, zword_t action_routine)
{
	char   *buffer;
	int     buflen, read_size, status, c;
	zword_t arg_list[2];

	/* Set maximum buffer size to width of screen minus any
	   right margin and 1 character for a terminating NULL */

	buflen = (screen_cols > 127) ? 127 : screen_cols;
	buflen -= right_margin + 1;
	if ((int) cbuf[0] <= buflen)
		buflen = cbuf[0];

	/* Set read size and start of read buffer. The buffer may already be
	   primed with same text in V5 games. The Z-code will have already
	   displayed the text so we don't have to do that */

	if (h_type > V4) {
		read_size = cbuf[1];
		buffer = &cbuf[2];
	} else {
		read_size = 0;
		buffer = &cbuf[1];
	}

	/* Try to read inp_buffer from command file */

	c = playback_line (buflen, buffer, &read_size);

	if (c == -1) {

		/* Setup the timeout routine argument list */

		arg_list[0] = action_routine;
		arg_list[1] = timeout;

		/* Read a line with a timeout. If the inp_buffer timed out then
		   call the timeout action routine. If the return status from the
		   timeout routine was 0 then try to read the line again */

		do {
			c = input_line (buflen, buffer, timeout, &read_size);
			status = 0;
		} while (c == -1 && (status = call (2, arg_list, ASYNC)) == 0);

		/* Throw away any inp_buffer if timeout returns success */

		if (status)
			read_size = 0;

	}

	/* Zero terminate line */

	buffer[read_size] = '\0';

	if (h_type > V4)
		cbuf[1] = (char) read_size;

	return (c);

}



/*
 * tokenise_line
 *
 * Convert a typed inp_buffer line into tokens. The token buffer needs some
 * additional explanation. The first byte is the maximum number of tokens
 * allowed. The second byte is set to the actual number of token read. Each
 * token is composed of 3 fields. The first (word) field contains the word
 * offset in the dictionary, the second (byte) field contains the token length,
 * and the third (byte) field contains the start offset of the token in the
 * character buffer.
 *
 */

static void
tokenise_line (zword_t char_buf, zword_t token_buf, zword_t dictionary,
	       zword_t flag)
{
	int     i, count, words, token_length;
	long    word_index, chop = 0;
	char   *cbuf, *tbuf, *tp;
	const char *cp, *token;
	char    punctuation[16];
	zword_t word;

	/* Initialise character and token buffer pointers */

	cbuf = (char *) &datap[char_buf];
	tbuf = (char *) &datap[token_buf];

	/* Initialise word count and pointers */

	words = 0;
	cp = (h_type > V4) ? cbuf + 2 : cbuf + 1;
	tp = tbuf + 2;

	/* Initialise dictionary */

	count = get_byte (dictionary++);
	for (i = 0; i < count; i++)
		punctuation[i] = get_byte (dictionary++);
	punctuation[i] = '\0';
	entry_size = get_byte (dictionary++);
	dictionary_size = (short) get_word (dictionary);
	dictionary_offset = dictionary + 2;

	/* Calculate the binary chop start position */

	if (dictionary_size > 0) {
		word_index = dictionary_size / 2;
		chop = 1;
		do
			chop *= 2;
		while (word_index /= 2);
	}

	/* Tokenise the line */

	do {

		/* Skip to next token */

		cp = next_token (cp, &token, &token_length, punctuation);
		if (token_length) {

			/* If still space in token buffer then store word */

			if (words <= tbuf[0]) {

				/* Get the word offset from the dictionary */

				word = find_word (token_length, token, chop);

				/* Store the dictionary offset, token length and offset */

				if (word || flag == 0) {
					tp[0] = (char) (word >> 8);
					tp[1] = (char) (word & 0xff);
				}
				tp[2] = (char) token_length;
				tp[3] = (char) (token - cbuf);

				/* Step to next token position and count the word */

				tp += 4;
				words++;
			} else {

				/* Moan if token buffer space exhausted */

				output_string
				    ("Too many words typed, discarding: ");
				output_line (token);
			}
		}
	} while (token_length);

	/* Store word count */

	tbuf[1] = (char) words;

}



/*
 * next_token
 *
 * Find next token in a string. The token (word) is delimited by a statically
 * defined and a game specific set of word separators. The game specific set
 * of separators look like real word separators, but the parser wants to know
 * about them. An example would be: 'grue, take the axe. go north'. The
 * parser wants to know about the comma and the period so that it can correctly
 * parse the line. The 'interesting' word separators normally appear at the
 * start of the dictionary, and are also put in a separate list in the game
 * file.
 *
 */

static const char *
next_token (const char *s, const char **token, int *length,
	    const char *punctuation)
{
	int     i;

	/* Set the token length to zero */

	*length = 0;

	/* Step through the string looking for separators */

	for (; *s; s++) {

		/* Look for game specific word separators first */

		for (i = 0; punctuation[i] && *s != punctuation[i]; i++);

		/* If a separator is found then return the information */

		if (punctuation[i]) {

			/* If length has been set then just return the word position */

			if (*length)
				return (s);
			else {

				/* End of word, so set length, token pointer and return string */

				(*length)++;
				*token = s;
				return (++s);
			}
		}

		/* Look for statically defined separators last */

		for (i = 0; separators[i] && *s != separators[i]; i++);

		/* If a separator is found then return the information */

		if (separators[i]) {

			/* If length has been set then just return the word position */

			if (*length)
				return (++s);
		} else {

			/* If first token character then remember its position */

			if (*length == 0)
				*token = s;
			(*length)++;
		}
	}

	return (s);

}



/*
 * find_word
 *
 * Search the dictionary for a word. Just encode the word and binary chop the
 * dictionary looking for it.
 *
 */

static  zword_t
find_word (int len, const char *cp, long chop)
{
	short int word[3];
	long    word_index, offset, status;

	/* Don't look up the word if there are no dictionary entries */

	if (dictionary_size == 0)
		return (0);

	/* Encode target word */

	encode_text (len, cp, word);

	/* Do a binary chop search on the main dictionary, otherwise do
	   a linear search */

	word_index = chop - 1;

	if (dictionary_size > 0) {

		/* Binary chop until the word is found */

		while (chop) {

			chop /= 2;

			/* Calculate dictionary offset */

			if (word_index > (dictionary_size - 1))
				word_index = dictionary_size - 1;

			offset = dictionary_offset + (word_index * entry_size);

			/* If word matches then return dictionary offset */

			if ((status =
			     word[0] - (short) get_word (offset + 0)) == 0 &&
			    (status =
			     word[1] - (short) get_word (offset + 2)) == 0 &&
			    (h_type < V4 ||
			     (status =
			      word[2] - (short) get_word (offset + 4)) == 0))
				return ((zword_t) offset);

			/* Set next position depending on direction of overshoot */

			if (status > 0) {
				word_index += chop;

				/* Deal with end of dictionary case */

				if (word_index >= (int) dictionary_size)
					word_index = dictionary_size - 1;
			} else {
				word_index -= chop;

				/* Deal with start of dictionary case */

				if (word_index < 0)
					word_index = 0;
			}
		}
	} else {

		for (word_index = 0; word_index < -dictionary_size;
		     word_index++) {

			/* Calculate dictionary offset */

			offset = dictionary_offset + (word_index * entry_size);

			/* If word matches then return dictionary offset */

			if ((status =
			     word[0] - (short) get_word (offset + 0)) == 0 &&
			    (status =
			     word[1] - (short) get_word (offset + 2)) == 0 &&
			    (h_type < V4 ||
			     (status =
			      word[2] - (short) get_word (offset + 4)) == 0))
				return ((zword_t) offset);
		}
	}

	return (0);

}



/*
 * tokenise
 *
 *    argv[0] = character buffer address
 *    argv[1] = token buffer address
 *    argv[2] = alternate vocabulary table
 *    argv[3] = ignore unknown words flag
 *
 */

void
tokenise (int argc, zword_t * argv)
{

	/* Supply default parameters */

	if (argc < 4)
		argv[3] = 0;
	if (argc < 3)
		argv[2] = h_words_offset;

	/* Convert the line to tokens */

	tokenise_line (argv[0], argv[1], argv[2], argv[3]);
}


/* End of File */
