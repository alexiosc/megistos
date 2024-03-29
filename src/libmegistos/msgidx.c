/*****************************************************************************\
 **                                                                         **
 **  FILE:     msgutl.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: C, July 94, Version 1.99 alpha                               **
 **            D, August 96, Version 2.0                                    **
 **            E, July 97, Version 3.0  (makes better header files)         **
 **            F, December 98, Version 4.0  (added magic number)            **
 **            G, December 2000, Version 5.0  (added ID table to index)     **
 **  PURPOSE:  Compile a MajorBBS(R)-compatible message block file into a   **
 **            Megistos BBS binary, indexed prompt file + a C header file   **
 **            with prompt #defines. NB: As of Megistos 0.6,                **
 **            all semblance of MajorBBS MSG-level compatibility has been   **
 **            dropped.                                                     **
 **  NOTES:    msgidx *.msg compiles everything into *.mbk, mbk_*.h         **
 **            Input file format:                                           **
 **                                                                         **
 **            KEYWORD {prompt... blah blah blah blah ....                  **
 **            ... ... ... ... ... ... ... ... ... ... ...                  **
 **            ... ... ... ...} <FORMAT SPECIFICATION>                      **
 **            KEYWORD {...                                                 **
 **                                                                         **
 **            Format specification strings are ignored.                    **
 **            Escape char='~'. "~~"->"~", "~}"->"}"                        **
 **                                                                         **
 **            Binary output file format:                                   **
 **                                                                         **
 **            Position 0x0000: 4-byte magic number == (char*)"MMBK"        **
 **            Position 0x0004: int32_t indexsize (number of entries)      **
 **                     0x0008: int32_t idx[1] (position of message #1)    **
 **                     0x000c: int32_t idx[2] (position of message #2)    **
 **                     ... ... ... ...                                     **
 **               indexsize<<2: int32_t idx[indexsize]                     **
 **           (indexsize+1)<<2: int32_t file_size                          **
 **                     idx[1]: char msg1[] (message #1, null terminated)   **
 **                     idx[2]: char msg2[] (message #2, null terminated)   **
 **                     ... ... ... ...                                     **
 **             idx[indexsize]: char msg_indexsize[]                        **
 **                                                                         **
 **            (this format is defunct after multilingual additions)        **
 **                                                                         **
 **            REV B:                                                       **
 **                                                                         **
 **            New stuff on languages etc:                                  **
 **                                                                         **
 **            * A new directive, LANG has been introduced.                 **
 **                                                                         **
 **            HOW TO CREATE ADDITIONAL LANGUAGES:                          **
 **                                                                         **
 **            1. Update /bbs/languages with the name of the language.      **
 **            2. If the msg file does not define any add'n languages:      **
 **                 Append a LANG {} directive to the end of the msg file.  **
 **                 Copy the message blocks between LEVEL3 {} and LANG {}   **
 **                 to the end of the file.                                 **
 **               If the msg file defines more than one language:           **
 **                 Pick a language from which the new one will be derived. **
 **                 Copy the message blocks belonging to that language to   **
 **                 the end of the file, delimiting them with a LANG {}     **
 **                 directive.                                              **
 **            3. Place an LANGEND {} directive at the end of the file. Do  **
 **               Not forget this - your language prompt files will be      **
 **               truncated otherwise.                                      **
 **            4. Edit the new language. DO NOT CHANGE PROMPT NAMES! You    **
 **                 may omit prompts at will, in which case msgidx will use **
 **                 the same prompt from the previous language. YOU MAY NOT **
 **                 OMIT OR DELETE PROMPTS FROM THE DEFAULT LANGUAGE. DO    **
 **                 NOT CHANGE THE ORDER OF THE PROMPTS.                    **
 **                                                                         **
 **            NEW FORMAT OF THE LEVEL3 SECTION:                            **
 **                                                                         **
 **            LEVEL3 {}                                                    **
 **              PROMPT1 {.......} ...             |                        **
 **              PROMPT2 {.......} ...             |  Default language 1    **
 **              : : :                             |                        **
 **              PROMPT_N {.......} ...            |                        **
 **            LANG {}                                                      **
 **              PROMPT1 {.......} ...             |                        **
 **              PROMPT2 {.......} ...             |  language 2            **
 **              : : :                             |                        **
 **              PROMPT_N {.......} ...            |                        **
 **            LANG {}                                                      **
 **             : : :                                                       **
 **              : : :                                                      **
 **              PROMPT_N {.......} ...            | last prompt of last    **
 **                                                | language               **
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
 * $Id: msgidx.c,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: msgidx.c,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.3  2004/02/29 17:18:14  alexios
 * Numerous changes to the dual mode behaviour (development/instance) of
 * msgidx. The in-instance check is now performed on BBSPREFIX, not
 * BBSCODE. When running within a BBS instance, header files are no
 * longer created.
 *
 * Revision 1.2  2004/02/22 18:53:45  alexios
 * Fixed four instances of MSGSDIR (the club/email directory) appearing
 * instead of the MBKDIR, where the .mbk files should really be stored.
 *
 * Revision 1.1  2003/12/19 13:11:14  alexios
 * *** empty log message ***
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.3  1998/12/27 16:40:08  alexios
 * Added autoconf support. Added code to stamp the magic number
 * at the beginning of the object file.
 *
 * Revision 1.2  1998/07/24 10:32:55  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:19:46  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 11:34:55  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER
#define RCS_VER "$Id: msgidx.c,v 2.0 2004/09/13 19:44:34 alexios Exp $"
const char *__RCS = RCS_VER;
#endif




#define DEBUG
#define PRINT printf

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdarg.h>

#include <megistos/config.h>
#include <megistos/prompts.h>
#include <megistos/miscfx.h>

#include "version.h"

static enum {
	mode_undecided = 0,
	mode_source,
	mode_instance
} op_mode;

static char *_hdir = NULL, *_mdir = NULL;

#define HEADERDIR _hdir
#define BLOCKDIR  _mdir

#define err(...)  fprintf(stderr, __VA_ARGS__)
#define errp(s,p)  err(s,p)
#define headermessage \
        "/***********************************************************\n"\
        " **                                                       **\n"\
        " **  This header file generated by msgidx. Do not alter.  **\n"\
        " **                                                       **\n"\
        " ***********************************************************/\n"\
	"\n"\
	"#ifndef __%s_UNAMBIGUOUS__\n"
#define elsemessage "#else\n"
#define footermessage "#endif /* __%s_UNAMBIGUOUS__ */\n"
#define headerentry "#define\t%s %d\n"


void
help ()
{
	err ("\nMSGIDX\n\n");
	err ("Syntax: msgidx message-block-file ...\n\n");
	
	if (op_mode == mode_source) {
		err ("Running within a source tree.\n\n");
		err ("  Target .h directory:   %s\n", HEADERDIR);
		err ("  Target .mbk directory: %s\n", BLOCKDIR);
	} else if (op_mode == mode_instance) {
		err ("Running within a BBS instance.\n\n");
		err ("  BBS prefix (BBSPREFIX):  %s\n", getenv ("BBSPREFIX"));
		err ("  Target .h directory:     %s\n", HEADERDIR);
		err ("  Target .mbk directory:   %s\n", BLOCKDIR);
	}

	exit(1);
}


int
special (char *s)
{
	int     value;

	value = (strlen (s) == 6) && (strstr (s, "LEVEL") == s) && isdigit (s[5]);
	value |= (strlen (s) == 7) && (strstr (s, "LEVEL") == s) &&
	    isdigit (s[5]) && isdigit (s[6]);
	value |= (!strcmp (s, "LANG"));
	return value;
}


void
adjustindex (FILE * fp, int32_t from)
{
	struct stat s;
	int32_t     i;
	idx_t       idx;

	fflush (fp);
	fstat (fileno (fp), &s);
	fseek (fp, from, SEEK_SET);
	for (i = from; i < s.st_size; i += sizeof (idx)) {
#ifdef DEBUG
		PRINT("Reading index i=%d, tell=%ld\n", i, ftell(fp));
#endif // DEBUG
		if (fread(&idx, sizeof(idx), 1, fp) != 1) {
			perror("msgidx: fread()ing index");
			//exit(1);
		}

		/* Nota Bene: Kludge city. The +sizeof(idx)-sizeof(idx.offset)
		   is there to adjust the indices so they account for an
		   off-by-28 bug. I can't find where it is, but I can always
		   adjust it here. :-) */

		idx.offset += s.st_size + sizeof (idx) - sizeof (idx.offset);
		fseek (fp, i, SEEK_SET);
		fwrite (&idx, sizeof (idx), 1, fp);
	}
}


void
parse (char *filename)
{
	FILE    *inp_buffer, *header1, *header2, *index, *output, *dict;
	char     rawname[64], *cp, symbol[64];
	char     hdrname[256], hdrtname[256], outname[256], idxname[256], tmpoutname[256];
	char     keyword[64];
	int      mode, i, curlang;
	int32_t  indexsize = 0;
	int32_t  langoffs[NUMLANGUAGES] = { 0 };
	int32_t  sourceidx = strlen (MBK_MAGIC) + sizeof (indexsize) + sizeof (langoffs);

	/* Open files, calculate names */

	if ((inp_buffer = fopen (filename, "r")) == NULL) {
		errp ("msgidx: unable to open %s", filename);
		perror ("");
		exit(1);
	}

	if ((cp = strrchr (filename, '/')) == 0)
		cp = filename;
	else
		cp++;
	strcpy (rawname, cp);
	if ((cp = strstr (rawname, ".msg")) != 0)
		*cp = 0;

	/* Create the symbol name from the raw name */

	bzero (symbol, sizeof (symbol));
	for (i = 0; rawname[i]; i++) {
		if (isalpha (rawname[i]))
			symbol[i] = toupper (rawname[i]);
		else if (isdigit (rawname[i]))
			symbol[i] = rawname[i];
		else
			symbol[i] = '_';
	}

	/* Create C header file */

	if (op_mode == mode_instance) {
		sprintf (hdrname, "/dev/null");
		sprintf (hdrtname, "/dev/null");
	} else {
		sprintf (hdrname, "%s/mbk_%s.h", HEADERDIR, rawname);
		sprintf (hdrtname, "%s/mbk_%s.h1~", HEADERDIR, rawname);
	}
	if ((header1 = fopen (hdrtname, "w")) == NULL) {
		errp ("msgidx: Unable to open %s", hdrtname);
		perror ("");
		exit(1);
	}

	if (op_mode != mode_instance)
		sprintf (hdrtname, "%s/mbk_%s.h2~", HEADERDIR, rawname);

	if ((header2 = fopen (hdrtname, "w")) == NULL) {
		errp ("msgidx: Unable to open %s", hdrtname);
		perror ("");
		exit(1);
	}
	
	fprintf (header1, headermessage, symbol);
	fprintf (header2, elsemessage);


	/* Create output binary file and temporary index file */

	sprintf (outname, "%s/%s.mbk", _mdir, rawname);
	sprintf (tmpoutname, "%s/%s.tmp", TMPDIR, rawname);
	if ((output = fopen (tmpoutname, "w+")) == NULL) {
		errp ("msgidx: Unable to open temporary file %s", tmpoutname);
		perror ("");
		exit(1);
	}


	/* Create temporary dictionary file */

	if ((dict = tmpfile ()) == NULL) {
		err ("msgidx: Unable to open temporary dictionary file.\n");
		exit(1);
	}

	sprintf (idxname, "%s/%s.idx", TMPDIR, rawname);
	if ((index = fopen (idxname, "w+")) == NULL) {
		errp ("msgidx: Unable to open %s", outname);
		perror ("");
		exit(1);
	}

	/* Print information */

	printf ("%s -> %s ", filename, outname);
	fflush (stdout);

	/* Initialise variables */

	mode = 0;
	curlang = 0;
	strcpy (keyword, "");

	/* Store a zero as the size of the index. Also, store zeroes as the */
	/* offsets to different language subsections.                       */

	fwrite (MBK_MAGIC, strlen (MBK_MAGIC), 1, index);
	indexsize = 0;
	memset (langoffs, 0, sizeof (langoffs));
	fwrite (&indexsize, sizeof (indexsize), 1, index);
	fwrite (langoffs, sizeof (langoffs), 1, index);

	while (!feof (inp_buffer)) {
		char    line[1024], xlated[1024], text[16384];
		char   *cp;
		int     escape;

		if (!fgets (line, 1024, inp_buffer))
			continue;

		switch (mode) {
		case 0:

			/* Find keyword and start of text block */

			cp = (char *) strchr (line, '{');
			if (cp) {
				char   *kp = line;

				mode = 1;
				while (isspace (*kp) && (*kp))
					kp++;
				strncpy (keyword, kp, 64);
				for (kp = keyword; *kp; kp++)
					if (isspace (*kp)) {
						*kp = 0;
						break;
					}

				/* Dump name and value of text block to header file */

				if (!special (keyword)) {
					if (!curlang) {
						char    sym[256];

						sprintf (sym, "%s_%s", symbol, keyword);
						fprintf (header1, headerentry,
							 keyword, ++indexsize);
						fprintf (header2, headerentry, sym, indexsize);
						fprintf (dict, "%s\n", keyword);
					} else {
						while (!feof (dict)) {
							char    shouldbe[256];
							char   *nlp;

							/* Get a line from the dict, strip newline */

							if (!fgets (shouldbe, 256, dict))
								continue;
							for (nlp = shouldbe; *nlp; nlp++)
								if (*nlp == 10 || *nlp == 13) {
									*nlp = 0;
									break;
								}
#ifdef DEBUG
							PRINT
							    ("GOT: %s   EXPECTING: %s",
							     keyword, shouldbe);
#endif

							/* If different keywords, just copy the indices */

							if (strcmp (shouldbe, keyword)) {
								idx_t   idx;

								fseek (index, sourceidx, SEEK_SET);
								fread (&idx,
								       sizeof (idx), 1, index);
								fseek (index, 0, SEEK_END);
								fwrite (&idx,
									sizeof (idx), 1, index);

#ifdef DEBUG
								// PRINT
								//     ("  SRC=%d  L=%d\n",
								//      sourceidx, l);
#endif

								sourceidx += sizeof (idx);
								indexsize++;
							} else {
								indexsize++;

#ifdef DEBUG
								PRINT (". INDEX DIFFERS, indexsize now %d\n", indexsize);
#endif
								break;
							}
						}
					}
				} else if (!strcmp ("LANG", keyword)) {

					/* Dump the rest of the dictionary */

					if (curlang)
						while (!feof (dict)) {
							char    shouldbe[256];
							char   *nlp;
							idx_t   idx;

							if (!fgets (shouldbe, 256, dict))
								continue;
							for (nlp = shouldbe; *nlp; nlp++)
								if (*nlp == 10 || *nlp == 13) {
									*nlp = 0;
									break;
								}
#ifdef DEBUG
							PRINT
							    ("GOT: %s   EXPECTING: %s  (FLUSH)\n",
							     keyword, shouldbe);
#endif

							fseek (index, sourceidx, SEEK_SET);
							fread (&idx, sizeof (idx), 1, index);
							fseek (index, 0, SEEK_END);
							fwrite (&idx, sizeof (idx), 1, index);
							sourceidx += sizeof (idx);
							indexsize++;
						}

					/* Start next language */

					if (!curlang) {
						sourceidx =
						    strlen (MBK_MAGIC) +
						    sizeof (indexsize) + sizeof (langoffs);
					}
					rewind (dict);
					langoffs [++curlang] = ++indexsize - curlang;

#ifdef DEBUG
					PRINT
					    ("Language %d starts at value offset %d\n\n",
					     curlang, indexsize);
#endif

				};

				/* Add an index entry pointing to start of text block */

				if (!special (keyword)) {
					idx_t   idx;

#ifdef DEBUG
					PRINT
					    ("KEYWORD %s  IDX=%ld  OUT=%ld  SRC=%d\n",
					     keyword, ftell (index), ftell (output), sourceidx);
#endif

					bzero (&idx, sizeof (idx));
					strncpy (idx.id, keyword, sizeof (idx.id) - 1);
					idx.id[sizeof (idx.id) - 1] = 0;
					idx.offset = ftell (output);

					sourceidx += sizeof (idx);
					fseek (index, 0, SEEK_END);
					fwrite (&idx, sizeof (idx), 1, index);
				}

				/* Begin reading text block */

				strcpy (xlated, ++cp);
				strcpy (line, xlated);
			} else
				break;

		case 1:

			/* Translate escape sequences */

			strcpy (xlated, line);
			for (cp = xlated, escape = 0, i = 0; *cp; cp++) {
				if ((*cp == '@') && ((cp == xlated) || (*(cp - 1) != 27)))
					line[i++] = 0x7f;
				else if ((*cp == 0x7e) && (!escape))
					escape = 1;
				else if ((*cp == 0x7d) && (!escape))
					line[i++] = '\377';
				else {
					escape = 0;
					line[i++] = *cp;
				}
			}
			line[i] = 0;
			cp = (char *) strchr (line, 0xff);

			/* Check for end of text block */

			if (cp) {
				char   *kp;

				strcpy (text, line);
				kp = (char *) strchr (line, 0xff);
				*kp = 0;

				mode = 0;
			}

			/* Output text block */

			if (!special (keyword)) {
				fwrite (line, strlen (line), 1, output);
				if (!mode) {
					char    c = 0;

					fwrite (&c, 1, 1, output);
				}
			}
			break;
		}
	}

	/* Update the language table & index */

	fseek (index, 0, SEEK_SET);
	fwrite (MBK_MAGIC, strlen (MBK_MAGIC), 1, index);
	fwrite (&indexsize, sizeof (indexsize), 1, index);
	fwrite (langoffs, sizeof (langoffs), 1, index);

	/* Add a dummy index entry pointing to the end of the file */

	{
		idx_t   idx;

		bzero (&idx, sizeof (idx));
		fseek (output, 0, SEEK_END);
		idx.offset = ftell (output);
		fseek (index, strlen (MBK_MAGIC), SEEK_END);
		fwrite (&idx, sizeof (idx), 1, index);
	}

	/*  Adjust index for concatenation with output file */

	adjustindex (index, strlen (MBK_MAGIC) + sizeof (indexsize) + sizeof (langoffs));


	fprintf (header2, footermessage, symbol);
	fclose (header1);
	fclose (header2);

	/* Concatenate the two halves of the header file */

	if (op_mode != mode_instance) {
		char    *command;
		char    *fname1;
		char    *fname2;
		
		sprintf (hdrtname, "%s/mbk_%s.h~", HEADERDIR, rawname);
		if (asprintf (&fname1, "%s/mbk_%s.h1~", HEADERDIR, rawname) < 0) {
			perror("msgidx: asprintf(fname1)");
			exit(1);
		}
		if (asprintf (&fname2, "%s/mbk_%s.h2~", HEADERDIR, rawname) < 0) {
			perror("msgidx: asprintf(fname2)");
			exit(1);
		}
		if (asprintf (&command, "cat %s %s >%s", fname1, fname2, hdrtname) < 0) {
			perror("msgidx: asprintf(command)");
			exit(1);
		}
		if (system (command)) {
			err ("msgidx: Unable to open temporary dictionary file.\n");
			perror("");
			exit(1);
		}
		unlink (fname1);
		unlink (fname2);

		free(command);
		free(fname1);
		free(fname2);
	}

	fclose (output);
	fclose (inp_buffer);
	fclose (index);
	fclose (dict);

	/* Now concatenate index and output file */

	{
		char    *command;

		if (asprintf (&command, "cat %s %s >%s", idxname, tmpoutname, outname) < 0){
			perror("msgidx: asprintf(command)");
			exit(1);
		}

#ifdef DEBUG
		PRINT ("%s\n", command);
#endif

		system (command);
		unlink (idxname);
		unlink (tmpoutname);

		free(command);

		/* And move the header file to the right place IF it's new */

		if (op_mode != mode_instance) {
			struct stat st;
			char    fname[256];

			sprintf (fname, "%s/diff%d", TMPDIR, getpid ());
			sprintf (command, "diff %s %s 2>%s >%s", hdrname, hdrtname, fname, fname);
			system (command);
			if (stat (fname, &st) || st.st_size) {
				rename (hdrtname, hdrname);
				printf ("+ %s\n", hdrname);
			} else
				printf ("\n");
			unlink (fname);
			unlink (hdrtname);
		} else printf ("\n");
	}
}


int
main (int argc, char **argv)
{
	int    i;
	char * s;

	/* Detect mode of operation */

	op_mode = mode_undecided;
	if ((s = getenv ("BUILDDIR")) != NULL) {
		struct stat st;
		if (stat (s, &st) == 0 && S_ISDIR (st.st_mode)) {
			op_mode = mode_source;
			
			_hdir = ".";

			/* enough space for the two strings, a separating slash
			 * and terminating NUL. */

			if (asprintf(&_mdir, "%s/%s", s, MBKDIR) < 0) {
				perror("msdidx: malloc()");
				exit(1);
			}
			if (stat (_mdir, &st) || (!S_ISDIR (st.st_mode))) {
				perror (_mdir);
				exit (1);
			}
		} else {
			perror (s);
			exit (1);
		}
	}

	if ((s = getenv ("BBSPREFIX")) != NULL) {
		op_mode = mode_instance;

		_hdir = MBKINCLUDEDIR;
		_mdir = (char *) malloc (/*strlen (__INSTANCEDIR) + 1 +*/
					 strlen (s) + 1 +
					 strlen (MBKDIR) + 1);
		if (_mdir == NULL) perror ("malloc()");
		/*sprintf (_mdir, __INSTANCEDIR"/%s/"MBKDIR, s);*/
		sprintf (_mdir, "%s/%s", s, MBKDIR);
	}

	if (op_mode == mode_undecided) {
		err ("Unable to detect if I'm being called in a source tree ");
		err ("or a BBS configuration directory. Bailing out.\n");
		exit (1);

	} else if (argc == 1) help ();

	for (i = 1; i < argc; i++) parse (argv[i]);

	if (_mdir) free(_mdir);
	if (_hdir) free(_hdir);

	return 0;
}
