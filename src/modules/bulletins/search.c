/*****************************************************************************\
 **                                                                         **
 **  FILE:     search.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.5                                    **
 **  PURPOSE:  Search for keywords                                          **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id: search.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: search.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: search.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


#define KEYSCAN  "\000\055\055\055\055\055\055\055"  /* 0-7              */ \
                 "\055\055\055\055\055\055\055\055"  /* 8-15             */ \
                 "\055\055\055\055\055\055\055\055"  /* 16-23            */ \
                 "\055\055\055\055\055\055\055\055"  /* 24-31            */ \
                 "\055\055\055\055\055\055\055\055"  /* 32-39    !"#$%&' */ \
                 "\055\055\055\055\055\055\055\055"  /* 40-47   ()*+,-./ */ \
                 "\060\061\062\063\064\065\066\067"  /* 48-55   01234567 */ \
                 "\070\071\055\055\055\055\055\055"  /* 56-63   89:;<=>? */ \
                 "\055\101\102\103\104\105\106\107"  /* 64-71   @ABCDEFG */ \
                 "\110\111\112\113\114\115\116\117"  /* 72-79   HIJKLMNO */ \
                 "\120\121\122\123\124\125\126\127"  /* 80-87   PQRSTUVW */ \
                 "\130\131\132\055\055\055\055\055"  /* 88-95   XYZ[\]^_ */ \
                 "\055ABCDEFG"                       /* 96-103  `abcdefg */ \
                 "HIJKLMNO"                          /* 104-111 hijklmno */ \
                 "PQRSTUVW"                          /* 112-119 pqrstuvw */ \
                 "XYZ\055\055\055\055\055"           /* 120-127 xyz{|}~  */ \
                 "ABGDEZIT"                          /* 128-135 ABGDEZHU */ \
                 "IKLMNXOP"                          /* 136-143 IKLMNJOP */ \
                 "RSTYFXCO"                          /* 144-151 RSTYFXCV */ \
                 "ABGDEZIT"                          /* 152-159 abgdezhu */ \
                 "IKLMNXOP"                          /* 160-167 iklmnjop */ \
                 "RSSTYFXC"                          /* 168-175 rsstyfxc */ \
                 "\055\055\055\055\055\055\055\055"  /* 176-183 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 184-191 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 192-199 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 200-207 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 208-215 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 216-223 graphics */ \
                 "OAEIIIOY"                          /* 224-231 waehiioy */ \
                 "YO\055\055\055\055\055"            /* 232-239 yv       */ \
                 "\055\055\055\055\055\055\055\055"  /* 240-247 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 248-255 graphics */



static char *keywords[128];
static char *phonetic[128];
static int oldverticalformat;
static int numkeys = 0;
static int indworking = 0;	/* Progress indicator working */
static int ind = 0;		/* Current indicator frame */
static int lastkey = -1;	/* Last key compared */





static void
startind ()
{
	oldverticalformat = fmt_verticalformat;
	if (!indsel)
		return;
	fmt_setverticalformat (0);
	if (!indworking) {
		prompt (KSIND0);
		indworking++;
		ind = 0;
	}
}


static void
progressind (int i)
{
	if (!indsel)
		return;
	if (indworking > 0) {
		prompt (KSIND1 + ind, i);
		ind = (ind + 1) % 8;
	}
}


static void
endind ()
{
	if (!indsel)
		return;
	indworking--;
	if (!indworking) {
		fmt_setverticalformat (oldverticalformat);
		prompt (KSINDE);
	}
}


static int
keycmp (char *s)
{
	stgxlate (s, KEYSCAN);
	for (lastkey = 0; lastkey < numkeys; lastkey++)
		if (strstr (s, phonetic[lastkey])) {
			return 1;
		}
	return 0;
}


static void
showkeywords ()
{
	int     i;

	if (numkeys == 1)
		prompt (KSCAN1, keywords[0]);
	else {
		prompt (KSCAN2, keywords[0]);
		for (i = 1; i < numkeys - 1; i++)
			prompt (KSCAN3, keywords[i]);
		prompt (KSCAN4, keywords[numkeys - 1]);
	}
}


static int
getkeywords ()
{
	char   *i;
	char    tmp[MAXINPLEN];
	int     n;

	for (;;) {
		if (cnc_more ()) {
			i = cnc_nxtcmd;
			strcpy (tmp, cnc_nxtcmd);
			strcpy (inp_buffer, cnc_nxtcmd);
			inp_parsin ();
		} else {
			prompt (SRCHBLT);
			inp_get (0);
			if (!margc)
				continue;
		}
		i = margv[0];

		if (!i[0])
			continue;
		else if (inp_isX (i))
			return 0;
		else if (sameas ("?", i)) {
			prompt (SRCHHLP);
			cnc_end ();
			continue;
		} else {
			char    s[256], *cp;

			memset (keywords, 0, sizeof (keywords));
			for (numkeys = 0, n = 0; n < margc && n < 128;
			     n++, numkeys++) {
				strncpy (s, margv[n], sizeof (s));
				while (s[strlen (s) - 1] == 32)
					s[strlen (s) - 1] = 0;
				for (cp = s; *cp && (*cp == 32); cp++);
				keywords[n] = alcmem (strlen (cp) + 1);
				strcpy (keywords[n], cp);
				phonetic[n] = alcmem (strlen (cp) + 1);
				strcpy (phonetic[n], stgxlate (cp, KEYSCAN));
			}
			break;
		}
	}
	return 1;
}


static void
freekeys ()
{
	int     n;

	for (n = 0; n < numkeys; n++)
		if (keywords[n]) {
			free (keywords[n]);
			free (phonetic[n]);
			keywords[n] = NULL;
		}
	numkeys = 0;
}


static void
doscan ()
{
	struct bltidx blt, tmpblt;
	char    oldclub[16] = { 0 };
	int     found = 0;

	if (!(club[0] ? dblistfind (club, 1) : dblistfirst ())) {
		if (!club[0])
			prompt (BLTNOBT);
		else
			prompt (CLBNOBT, club);
		return;
	}

	inp_nonblock ();
	do {
		char    c;

		dbget (&blt);
		memcpy (&tmpblt, &blt, sizeof (tmpblt));

		if (club[0] && strcmp (blt.area, club))
			break;

		if (strcmp (oldclub, blt.area)) {
			prompt (CURAREA, blt.area);
			strcpy (oldclub, blt.area);
		}
		if (read (0, &c, 1))
			if (c == 13 || c == 10 || c == 27 || c == 15 || c == 3) {
				prompt (LSTCAN);
				return;
			}
		if (fmt_lastresult == PAUSE_QUIT) {
			prompt (LSTCAN);
			return;
		}

		prompt (CURBLT, blt.num, blt.descr);

		found = 0;
		if (keycmp (tmpblt.fname))
			found = 1;
		else if (keycmp (tmpblt.area))
			found = 1;
		else if (keycmp (tmpblt.author))
			found = 1;
		else if (keycmp (tmpblt.descr))
			found = 1;
		else {
			int     lines = 0;
			FILE   *fp;
			char    fname[256], line[1024], c;

			strcpy (fname,
				mkfname (MSGSDIR "/%s/%s/%s", blt.area,
					 MSGBLTDIR, blt.fname));
			startind ();
			if ((fp = fopen (fname, "r")) != NULL) {
				while (fgets (line, sizeof (line), fp)) {
					if ((lines++) % indspd == 0)
						progressind (lines);
					if (keycmp (line)) {
						found = 2;
						break;
					}
					if ((read (fileno (stdin), &c, 1) &&
					     ((c == 13) || (c == 10) ||
					      (c == 27) || (c == 15) ||
					      (c == 3)))
					    || (fmt_lastresult == PAUSE_QUIT)) {
						endind ();
						prompt (ABORT);
						inp_block ();
						return;
					}
				}
				fclose (fp);
				endind ();
				prompt (SCNENDBLT);
			} else {
				endind ();
				prompt (SCNENDBLT);
				prompt (PANIC2);
			}
		}

		if (found) {
			int     yes;

			inp_block ();
			prompt (SCANFND, keywords[lastkey]);
			if (found == 1)
				prompt (SCNENDBLT);
			bltinfo (&blt);

			if (!get_bool
			    (&yes, ASKREAD, YNHUH, DEFLTC,
			     askdef ? 'Y' : 'N')) {
				prompt (ABORT);
				return;
			} else if (yes == 0) {
				inp_nonblock ();
				showkeywords ();
			} else {
				showblt (&blt);
				fmt_lastresult = PAUSE_CONTINUE;
				inp_nonblock ();
				showkeywords ();
			}
		}
	} while (dblistnext ());

	inp_block ();
	prompt (SCNEND);
}


void
keysearch ()
{
	if (!getkeywords ())
		return;
	showkeywords ();
	doscan ();
	freekeys ();
}


/* End of File */
