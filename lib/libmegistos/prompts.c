/*****************************************************************************\
 **                                                                         **
 **  FILE:     prompts.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Access and use customizable system prompts in compiled .mbk  **
 **            files.                                                       **
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
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.7  2004/05/03 05:36:12  alexios
 * Opens msg_sys whenever any other prompt block is opened, provided
 * msg_sys isn't already opened (and the prompt block being opened isn't
 * msg_sys). Fixed insidious bug in the prompt index that caused certain
 * modules to dump core when outputting the last message in certain
 * multilingual blocks. Added debugging code (#ifdef'ed out). Changed the
 * code so that (depending on preprocessor symbol MSGS_ON_DISK) prompt
 * block data lives in core, and is read from disk on startup. This makes
 * the system more resistant to cases where the blocks change mid-run
 * (e.g. due to an admin adjusting them). Added a couple of safeguards to
 * msg_close().
 *
 * Revision 1.6  2003/12/19 13:25:18  alexios
 * Updated include directives.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:01:53  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added code to recognise prompt files
 * by magic number and commit sepuku if they seem corrupted.
 *
 * Revision 0.4  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.3  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 10:58:35  alexios
 * Added a setlanguage() to opnmsg() -- possible bug there.
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
#define WANT_STRINGS_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_STAT_H 1
#include <megistos/bbsinclude.h>
#include <megistos/config.h>
#include <megistos/errors.h>
#include <megistos/useracc.h>
#include <megistos/miscfx.h>
#include <megistos/prompts.h>
#include <megistos/bbsmod.h>
#include <megistos/output.h>
#include <megistos/bots.h>


#define msg_get_nobot(num) msg_getl_bot((num),(msg_cur->language),0)



char   *msg_buffer;
promptblock_t *msg_cur = NULL;
promptblock_t *msg_last = NULL;
promptblock_t *msg_sys = NULL;

static long lastprompt;

static char postfix[80];
int     msg_numlangs;
char    msg_langnames[NUMLANGUAGES][64];


void
msg_init ()
{
	FILE   *langfp;

	msg_numlangs = 0;
	if ((langfp = fopen (mkfname (LANGUAGEFILE), "r")) != NULL) {
		while (!feof (langfp)) {
			char    line[1024];

			if (fgets (line, 1024, langfp)) {
				char   *cp = line;
				char   *nlp = strrchr (line, 10);

				if (nlp)
					*nlp = 0;
				while (*cp && isspace (*cp))
					cp++;
				if (*cp && *cp != '#')
					strcpy (msg_langnames[msg_numlangs++],
						cp);
			}
		}
		fclose (langfp);
	}
}


promptblock_t *
msg_open (char *name)
{
	char    fname[256], magic[4];
	long    result;
	struct  stat st;

	/* Also open the sysvar block by recursing here (just once). */

	if (strcmp (name, "sysvar") && (msg_sys == NULL)) {
		msg_sys = msg_open ("sysvar");
	}

	msg_last = msg_cur;
	msg_cur = (promptblock_t *) alcmem (sizeof (promptblock_t));

	sprintf (fname, "%s/%s.mbk", mkfname (MBKDIR), name);
	if (stat (fname, &st)) {
		error_fatalsys ("Unable to stat prompt file %s", fname);
	}
	if ((msg_cur->handle = fopen (fname, "r")) == NULL) {
		error_fatalsys ("Unable to open prompt file %s", fname);
	}

	if (fread (magic, sizeof (magic), 1, msg_cur->handle) != 1) {
		error_fatalsys
		    ("Unable to read magic number from prompt file %s", fname);
	}

	if (strncmp (magic, MBK_MAGIC, 4)) {
		error_fatal
		    ("Corrupted file %s. Remove it and use msgidx to recreate.",
		     fname);
	}

	if (fread (&(msg_cur->indexsize), sizeof (long), 1, msg_cur->handle) !=
	    1) {
		error_fatalsys ("Corrupted prompt file %s (indexcount)",
				fname);
	}

	if (fread (&(msg_cur->langoffs),
		   sizeof (msg_cur->langoffs), 1, msg_cur->handle) != 1) {
		error_fatalsys ("Corrupted prompt file %s (langoffs)", fname);
	}

	msg_cur->indexsize++;
	msg_cur->index =
	    (idx_t *) alcmem (msg_cur->indexsize * sizeof (idx_t));
	result =
	    fread (msg_cur->index, sizeof (idx_t), msg_cur->indexsize,
		   msg_cur->handle);
	if (result != msg_cur->indexsize) {
		error_fatal ("Corrupted prompt file %s (index)", fname);
	}
	msg_cur->index [msg_cur->indexsize - 1].offset = msg_cur->size;

	msg_cur->indexsize--;
	msg_cur->language = 0;
	sprintf (msg_cur->fname, "%s.mbk", name);
	lastprompt = -1;

	if (thisshm)
		msg_setlanguage (thisuseracc.language);

	/* Read in the messages */

	msg_cur->size = st.st_size;
	msg_cur->data = alcmem (st.st_size);
	if (fseek (msg_cur->handle, 0, SEEK_SET)) {
		error_fatalsys
			("Failed to rewind() file %s", msg_cur->fname);
	}
	if (fread (msg_cur->data, st.st_size, 1, msg_cur->handle) != 1) {
		error_fatalsys
			("Failed to fread() %d bytes from file %s", st.st_size, msg_cur->fname);
	}

#if 0
	{
		int i;
		fprintf(stderr,"INDEX FOR %s:\n", msg_cur->fname);
		for (i=0; i<msg_cur->indexsize; i++) {
			fprintf(stderr,"%3d. ofs %5d name %s\n", i, msg_cur->index[i].offset, msg_cur->index[i].id);
		}
		printf(stderr,"--------------------------------------------------------\n");
	}
#endif

	return msg_cur;
}


void
msg_set (promptblock_t * blk)
{
	msg_last = msg_cur;
	msg_cur = blk;
	lastprompt = -1;
}


void
msg_reset ()
{
	if (msg_last == NULL)
		return;
	msg_cur = msg_last;
	lastprompt = -1;
}



static char *
msg_botprocess (char *id, int num, int lang, char *s)
{
	static char *botbuf = NULL;
	char    tmp[80];
	char   *cp = s;
	int     count = 0;

	if (botbuf == NULL) {
		botbuf = alcmem (256 << 10);	/* 256k, allocated on demand only */
	}

	bzero (botbuf, sizeof (botbuf));

	/* xxx will be updated later */
	sprintf (botbuf, "%03d xxx %s %s %d %d\n",
		 BTS_PROMPT_STARTS, msg_cur->fname, id, num, lang);

	bot_escape (s);		/* Escape result code-like sequences */

	for (cp = s; *cp; cp++) {
		if (*cp == '%') {	/* Escape format specifiers */
			char   *sp = cp;

			if (*(cp + 1) == '%') {
				cp++;
				continue;
			}

			for (cp++; (*cp) && strcspn (cp, "diouxXeEfgcspn");
			     cp++);

			if (*cp) {
				count++;
				sprintf (tmp, "%03d ", BTS_PROMPT_ARGUMENT);
				strcat (botbuf, tmp);
				strncat (botbuf, sp, cp - sp + 1);
				strcat (botbuf, "\n");
			}

			*sp = 1;	/* 'mark' the original format specifier */
		}
	}

	sprintf (tmp, "%03d %03d", BTS_PROMPT_STARTS, count);
	memcpy (botbuf, tmp, strlen (tmp));	/* Copy just the "601 xxx" part */
	sprintf (tmp, "%03d ", BTS_PROMPT_TEXT);
	strcat (botbuf, tmp);
	strcat (botbuf, s);
	sprintf (tmp, "\n%03d\n", BTS_PROMPT_ENDS);
	strcat (botbuf, tmp);

	return botbuf;
}


char   *
msg_getl_bot (int num, int language, int checkbot)
{
	long    offset = 0, size;
	int     oldnum;
	char   *id = NULL;

	language = language % (NUMLANGUAGES);

	if (!msg_cur)
		return NULL;
	oldnum = num;
	num += msg_cur->langoffs[language];

	if (num == lastprompt)
		return msg_buffer;
	if (!msg_buffer)
		msg_buffer = alcmem (MSGBUFSIZE);

	if (num < 0 || num > msg_cur->indexsize) {
		error_fatal
		    ("Prompt %s (lang %d, index %d) out of range (1-%d) in %s",
		     id, num, language, msg_cur->indexsize, msg_cur->fname);
	}

	id = msg_cur->index[num - 1].id;
	offset = msg_cur->index[num - 1].offset;
#ifdef MSGS_ON_DISK
	if (fseek (msg_cur->handle, offset, SEEK_SET)) {
		error_fatalsys
		    ("Failed to fseek() prompt %s (#%d) location %ld in %s",
		     id, oldnum, offset, msg_cur->fname);
	}
#endif /* MSGS_ON_DISK */

	size = msg_cur->index[num].offset - offset;

	if (size < 0) size = msg_cur->size - offset - 1;

	if (offset >= msg_cur->size) {
		error_fatal
			("Prompt offset %d is out of limits (max %d) for prompt %s (#%d) in file %s",
			 offset, msg_cur->size, id, num, msg_cur->fname);
	}

	if ((offset + size) >= msg_cur->size) {
		error_fatal
			("Prompt offset %d + size %d past end of file (size %d) for prompt %s (#%d) in file %s",
			 offset, size, msg_cur->size, id, num, msg_cur->fname);
	}

	if (size >= MSGBUFSIZE) size = MSGBUFSIZE - 1;

#ifdef MSGS_ON_DISK 
	if (fread (msg_buffer, size, 1, msg_cur->handle) != 1) {
#if 0
		error_fatal
		    ("Error reading prompt %s (index %d, lang %d) in %s (s=%ld i=%ld o=%ld)",
		     msg_cur->index[num].id, oldnum, language, msg_cur->fname,
		     (void *) size, msg_cur->index[num].offset, offset);
#endif
	}
#else

	/*fprintf(stderr,"(fname=\"%s\",ofs=%d,size=%d)\n", msg_cur->fname,offset,size);*/
	memcpy (msg_buffer, &msg_cur->data [offset], size);

#endif /* MSGS_ON_DISK */

	lastprompt = num;

	/* If this is a bot, format the prompt for it. */

	if (checkbot && (out_flags & OFL_ISBOT)) {
		lastprompt = -1;
		return msg_botprocess (id, num, language, msg_buffer);
	}

	return msg_buffer;
}


char   *
msg_getunitl (int num, int value, int language)
{
	long    offset, size;
	char   *id = NULL;

	postfix[0] = 0;
	num += (value != 1) + msg_cur->langoffs[language];
	if (num < 1 || num > msg_cur->indexsize) {
		error_fatal ("Prompt %s (#%d) out of range (1-%d) in file %s",
			     id, num, msg_cur->indexsize, msg_cur->fname, 0, 0,
			     0);
	}
	offset = msg_cur->index[num - 1].offset;
	if ((size = msg_cur->index[num].offset - offset) > 79)
		return postfix;

#ifdef MSGS_ON_DISK
	if (fseek (msg_cur->handle, offset, SEEK_SET)) {
		error_fatalsys
		    ("Failed to fseek() prompt %s location %ld in file %s",
		     msg_cur->index[num].id, offset, msg_cur->fname);
	}
	if (fread (postfix, size, 1, msg_cur->handle) != 1) {
		error_fatalsys
		    ("Error reading prompt %s (#%d) in file %s %d %d %d",
		     msg_cur->index[num].id, num, msg_cur->fname, size,
		     msg_cur->index[num].offset, offset, 0);
	}
#else
	memcpy (postfix, &msg_cur->data [offset], size);
#endif /* MSGS_ON_DISK */

	return postfix;
}


void
msg_close (promptblock_t * blk)
{
	if (!msg_cur) return;
	if (blk && blk->fname[0]) {
		fclose (blk->handle);
		if (blk->index != NULL) free (blk->index);
		if (blk->data != NULL) free (blk->data);
		blk->fname[0] = 0;
		free (blk);
		blk = NULL;
		if (msg_buffer) {
			free (msg_buffer);
			msg_buffer = NULL;
		}
	}
}


static char *
lastwd (char *s)
{
	char   *cp;

	if (!s || !(*s))
		return (s);
	for (cp = s + strlen (s) - 1; cp >= s && isspace (*cp); cp--) {
		if (cp == s)
			return (cp);
	}
	for (; cp >= s && !isspace (*cp); cp--) {
		if (cp == s)
			return (cp);
	}
	return (cp + 1);
}


long
msg_long (int num, long floor, long ceiling)
{
	long    temp;
	char   *id;

	id = msg_cur->index[num].id;
	if (sscanf (lastwd (msg_get_nobot (num)), "%ld", &temp)) {
		if (temp >= floor && temp <= ceiling)
			return (temp);
		error_fatal
		    ("Long numeric option %s (#%d) in file %s is out of range",
		     id, num, msg_cur->fname);
	}
	error_fatal ("Long numeric option %s (#%d) in file %s has bad value",
		     id, num, msg_cur->fname);
	return -1;
}


unsigned
msg_hex (int num, unsigned floor, unsigned ceiling)
{
	long    temp;
	char   *id;

	id = msg_cur->index[num].id;
	if (sscanf (lastwd (msg_get_nobot (num)), "%lx", &temp)) {
		if (temp >= floor && temp <= ceiling)
			return ((unsigned) temp);
		error_fatal
		    ("Hex numeric option %s (#%d) in file %s is out of range",
		     id, num, msg_cur->fname);
	}
	error_fatal ("Hex numeric option %s (#%d) in file %s has bad value",
		     id, num, msg_cur->fname);
	return -1;
}


int
msg_int (int num, int floor, int ceiling)
{
	return ((int) msg_long (num, floor + 0L, ceiling + 0L));
}


int
msg_bool (int num)
{
	int     rc = 0;
	char   *id;

	id = msg_cur->index[num].id;
	switch (toupper (*lastwd (msg_get_nobot (num)))) {
	case 'Y':
		rc = 1;
	case 'N':
		return (rc);
	}
	error_fatal ("Yes/No option %s (#%d) in file %s has bad value",
		     id, num, msg_cur->fname, 0, 0, 0, 0);
	return -1;
}


char
msg_char (int num)
{
	return (*lastwd (msg_get_nobot (num)));
}


char   *
msg_string (int msgnum)
{
	char   *cp, *mp;

	cp = alcmem (strlen (mp = msg_get_nobot (msgnum)) + 1);
	strcpy (cp, mp);
	return (cp);
}


int
msg_token (int msgnum, char *toklst, ...)
{
	char  **ppt, *token;
	int     i;

	token = lastwd (msg_get_nobot (msgnum));
	for (ppt = &toklst, i = 1; *ppt != NULL; ppt++, i++) {
		if (strcmp (token, *ppt) == 0)
			return i;
	}
	return (0);
}


void
msg_setlanguage (int l)
{
	if (!msg_cur)
		return;
	msg_cur->language = (l - 1) % (NUMLANGUAGES);
	msg_sys->language = (l - 1) % (NUMLANGUAGES);
	lastprompt = -1;
}
