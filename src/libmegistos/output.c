/*****************************************************************************\
 **                                                                         **
 **  FILE:     output.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: C, June 94                                                   **
 **  PURPOSE:  Output message blocks et al                                  **
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
 * $Id: output.c,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: output.c,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.8  2004/05/03 05:32:21  alexios
 * Made sure msg_sys isn't opened multiple times by checking its handle.
 *
 * Revision 1.7  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.6  2003/12/19 13:25:18  alexios
 * Updated include directives.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:14:04  alexios
 * Rationalised the RCS/CVS ident(1) strings. Fixed issues with
 * relatively recent versions of the stdarg.h header file that caused
 * syntax errors.
 *
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.10  2000/01/06 10:56:23  alexios
 * Changed calls to write(2) to send_out(). Added send_out(),
 * which writes a buffer to a file just like write(2), but
 * checks for overruns if non-blocking I/O is enabled. If an
 * overrun is about to happen (i.e. write(2) returns without
 * having written all of the buffer), send_out() waits a bit
 * then tries to send the rest of the buffer. This solves
 * problems with, eg, the Bulletin reader, where a long full
 * list caused ugly overruns.
 *
 * Revision 0.9  1999/08/07 02:16:34  alexios
 * Fixed bug involving protectvars in printfile().
 *
 * Revision 0.8  1999/07/28 23:06:34  alexios
 * Fixed slight bug with screen clearing while waittoclear is
 * off.
 *
 * Revision 0.7  1999/07/18 21:01:53  alexios
 * Altered error_fatal() calls to error_fatalsys() where needed. Fixed a
 * sneaky bug in the list of substitution variables.
 *
 * Revision 0.6  1998/12/27 14:31:16  alexios
 * Added autoconf support. Minor fixes. Added code to enable
 * or disable automatic translation so that binary protocols
 * can work unhindered by emud.
 *
 * Revision 0.5  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.4  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/03 00:34:41  alexios
 * Cosmetic changes. Removed code to handle hardwired translation
 * tables. Changed setxlationtable() to register the new table
 * with emud, which now performs all translations. Commented out
 * xlwrite() since it should not be used anymore. Changed all
 * calls to xlwrite() to write() for the same reason.
 *
 * Revision 0.2  1997/09/12 12:52:28  alexios
 * Minor cosmetic changes and one slight code correction (no bug,
 * just making it better).
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: output.c,v 2.0 2004/09/13 19:44:34 alexios Exp $";



#define OUTPUT_O

#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_ERRNO_H 1
#define WANT_VARARGS_H 1
#define WANT_SYS_SHM_H 1
#include <megistos/bbsinclude.h>
#include <megistos/config.h>
#include <megistos/prompts.h>
#include <megistos/sysstruct.h>
#include <megistos/bbsmod.h>
#include <megistos/useracc.h>
#include <megistos/miscfx.h>
#include <megistos/timedate.h>
#include <megistos/format.h>
#include <megistos/input.h>
#include <megistos/errors.h>
#include <megistos/ttynum.h>
#include <megistos/output.h>
#include <megistos/channels.h>
#include <megistos/systemversion.h>
#include <megistos/bots.h>
#include <megistos/useracc.h>

#include <mbk/mbk_sysvar.h>

char    out_buffer[8192];
uint32  out_flags = OFL_WAITTOCLEAR | OFL_ANSIENABLE;


#define IS_BOT (out_flags&OFL_ISBOT)


struct substvar *substvars = NULL, *lastsubstvar = NULL;


static int translation;



static int
isvarchar (char c)
{
	if (out_flags & OFL_PROTECTVARS)
		return c == _VARCHAR;
	else
		return c == _VARCHAR || c == _ASCIIVARCHAR;
}


void
out_init ()
{
	if (msg_sys == NULL) msg_sys = msg_open ("sysvar");

	out_initsubstvars ();
	out_setwaittoclear (1);
	fmt_setpausetext (msg_string (PAUSE));
	out_clearflags (OFL_INHIBITVARS);
	out_setflags (OFL_PROTECTVARS);
}


void
out_done ()
{
	fflush (stdout);
}


void
out_setxlation (int i)
{
	FILE   *fp;
	char    fname[256];
	int     shmid;
	struct emuqueue *emuq;
	static int oldxlation = -1;

	/* This is going to be tedious. Ok, here goes. */
	/* Get the shared memory ID of our emud's emuqueue */

	sprintf (fname, "%s/.shmid-%s", mkfname (EMULOGDIR),
		 getenv ("CHANNEL"));

	if ((fp = fopen (fname, "r")) == NULL) {
		error_fatalsys ("Unable to open %s", fname);
	}
	if (!fscanf (fp, "%d", &shmid)) {
		error_fatalsys ("Unable to read %s", fname);
	}
	fclose (fp);


	/* Attach to the shared memory block */

	if ((emuq = (struct emuqueue *) shmat (shmid, NULL, 0)) == NULL) {
		error_fatalsys ("Error attaching to emulation shared memory");
	}


	/* Finally, set the translation (or enable/disable it) */

	if (i == XLATION_OFF) {
		if (oldxlation < 0) {
			oldxlation = emuq->xlation;
			emuq->xlation = -1;
		}
	} else if (i == XLATION_ON) {
		if (oldxlation >= 0) {
			emuq->xlation = oldxlation;
		}
	} else {
		emuq->xlation = i;
		oldxlation = -1;
	}


	/* Detach the shared memory */

	shmdt ((char *) emuq);


	/* Set the user's online record */

	if (thisshm)
		usr_setoxlation (thisuseronl, i);
	translation = i;
}


/*  xlwrite is obsoleted since emud does all the translations now.

int
xlwrite(int fd, const char *s, int count)
{
  const unsigned char *buf=s;
  char b[1024];
  int retval=0;
  register int i=0;
  register int bc=0;
  
  for(i=0;i<count;){
    b[bc++]=xlation_table[(int)buf[i++]];
    if(bc==sizeof(b))if(write(fd,b,sizeof(b))!=sizeof(b)){
      retval=-1;
      bc=0;
      break;
    } else bc=0;
  }
  if(bc)retval=write(fd,b,bc);
  if(retval!=-1)retval=count;
  return retval;
}
*/


#warning "Rewrite this using writev()"

int
out_send (int fd, const char *s, int count)
{
	register int offs = 0;
	int     retval = count;

	/* If non-blocking I/O is used, excessive output may overrun the OS output
	   buffer. Under Linux, this is 4 kbytes, a fact that can account for long
	   listings getting garbled. So we loop, trying to write as much of the
	   string as we can, waiting a bit between writes -- but only if the entire
	   string couldn't be sent. The performance impact should be minimal, as the
	   bottleneck is likely to be the user's bandwidth anyway. */

	while (count > 0) {
		register int i = write (fd, &s[offs], count);

		if (i < 0)
			return i;

		offs += i;
		count -= i;

		/* Wait for the output buffer to have some more space, unless of course
		   we've managed to send the whole string. This depends on bandwidth. It
		   doesn't need to be big for the Linux console. Modems can send out less
		   information, so we have to wait more. To cover all cases, we wait for a
		   pretty long time. This might produce slightly jerky output on the
		   console (though I personally can't detect it), but won't easily be
		   detectable on a modem. */

		if (count > 0)
			usleep (500 * 1000);	/* 500ms */
	}

	return retval;
}



static void
printexpand (buf, parmlist)
char   *buf;
void   *parmlist;
{
	char   *p1 = buf, format[16384] = { 0 }, newbuf[16384] = {
	0};
	int     count = 0, found, ansistate = 0;
	char   *bufptr;

	while (*p1 && count < 16383) {
		while (*p1 && !isvarchar (*p1)) {
			format[count] = *p1;
			if (!(out_flags & OFL_ANSIENABLE)) {
				if (!ansistate && *p1 == 27 &&
				    *(p1 + 1) != '!')
					ansistate = 1;
				else if ((ansistate == 1) && (*p1 == '['))
					ansistate = 2;
				else if ((ansistate == 2) &&
					 (isdigit (*p1) || (*p1 == ';')));
				else if (ansistate == 2) {
					char    ansicommands[16];

					strcpy (ansicommands, "ABCDHJKmsu");
					ansistate = 0;
					if (!strchr (ansicommands, *p1))
						count++;
					if (*p1 == 'J')
						format[count - 1] = 12;
				} else {
					ansistate = 0;
					count++;
				}
			} else
				count++;
			p1++;
		}
		format[count] = 0;
		if (out_flags & OFL_INHIBITVARS)
			break;
		if (!(*p1))
			break;

		if (isvarchar (*(p1 + 1))) {
			p1 += 2;
			format[count++] = '@';
		} else {
			struct substvar *svp = substvars;
			char    tmp[256], *tp;

			strcpy (tmp, p1);
			found = 0;
			tmp[0] = _VARCHAR;
			for (tp = tmp + 1; *tp; tp++)
				if (*tp == '@') {
					*tp = _VARCHAR;
					break;
				}
			while (!found && svp) {
				if (sameto (svp->varname, tmp)) {
					char   *subst =
					    (char *) (*svp->varcalc) ();
					count += strlen (subst);
					p1 += strlen (svp->varname);
					found = 1;
					strcat (format, subst);
				}
				svp = svp->next;
			}
			if (!found) {
				char    undefd[32];

				strcpy (undefd, "[UNKNOWN VARIABLE NAME]");
				strcat (format, undefd);
				count += strlen (undefd);
				p1++;
			}
		}
	}

	vsprintf (newbuf, format, parmlist);

	bufptr = newbuf;
	if ((!IS_BOT) && (out_flags & OFL_WAITTOCLEAR))
		while (*bufptr) {
			char   *clp = strstr (bufptr, "\033[2J");
			int     len = clp - bufptr;

			if (!clp)
				break;

			if (strlen (clp) >= 4 && clp[3] != 'J')
				break;

			if (len) {
				char    c = bufptr[len];

				bufptr[len] = 0;
				fmt_output (bufptr);
				bufptr[len] = c;
				out_clearflags (OFL_AFTERINPUT);
			}

			bufptr += len;

			if (!(out_flags & OFL_AFTERINPUT)) {
				char    c, *msgp;
				char    clrscr[32] = "\033[2J\033[1;1H\0";

				bufptr += 4;

				msg_set (msg_sys);
				msgp = msg_get (W2CLR);
				out_send (fileno (stdout), msgp,
					  strlen (msgp));
				msg_reset ();

				read (0, &c, 1);
				inp_resetidle ();
				if (!(out_flags & OFL_ANSIENABLE)) {
					c = 12;
					out_send (fileno (stdout), &c, 1);
				} else {
					out_send (fileno (stdout), clrscr,
						  strlen (clrscr));
				}
			} else {
				char    homestg[10] = "\033[1;1H\0";

				out_send (fileno (stdout), bufptr, 4);
				out_send (fileno (stdout), homestg,
					  strlen (homestg));
				bufptr += 4;
			}
			fmt_resetvpos (0);
	} else {
		char    homestg[20] = "\033[2J\033[1;1H\0";

		while (*bufptr) {
			char   *clp = strstr (bufptr, "\033[2J");
			int     len = clp - bufptr;

			if (!clp)
				break;

			if (strlen (clp) >= 4 && clp[3] != 'J')
				break;

			if (len) {
				char    c = bufptr[len];

				bufptr[len] = 0;
				fmt_output (bufptr);
				bufptr[len] = c;
				out_clearflags (OFL_AFTERINPUT);
			}
			out_send (fileno (stdout), bufptr, 4);
			out_send (fileno (stdout), homestg, strlen (homestg));
			bufptr += 4 + len;
		}
	}
	if (strlen (bufptr)) {
		fmt_output (bufptr);
		out_clearflags (OFL_AFTERINPUT);
	}
}

void    print (char *buf, ...);


static void
sprintexpand (stg, buf, parmlist)
char   *stg;
char   *buf;
void   *parmlist;
{
	char   *p1 = buf, format[16384] = { 0 };
	int     count = 0, found;

	while (*p1 && count < 16383) {
		while (*p1 && !isvarchar (*p1)) {
			format[count] = *p1;
			count++;
			p1++;
		}

		format[count] = 0;

		if (!(*p1))
			break;	/* End of the format string? */
		else if (isvarchar (*(p1 + 1))) {	/* No, just another variable */
			p1 += 2;
			format[count++] = '@';
		} else {
			struct substvar *svp = substvars;

			found = 0;
			while (!found && svp) {
				if (sameto (svp->varname, p1)) {
					char   *subst =
					    (char *) (*svp->varcalc) ();
					count += strlen (subst);
					p1 += strlen (svp->varname);
					found = 1;
					strcat (format, subst);
				}
				svp = svp->next;
			}
			if (!found) {
				char    undefd[32];

				strcpy (undefd, "[UNKNOWN VARIABLE NAME]");
				strcat (format, undefd);
				count += strlen (undefd);
				p1++;
			}
		}
	}

	vsprintf (stg, format, parmlist);
}


void
print (char *buf, ...)
{
	va_list args;

	va_start (args, buf);
	printexpand (buf, args);
	va_end (args);
}


void
sprint (char *stg, char *buf, ...)
{
	va_list args;

	va_start (args, buf);
	sprintexpand (stg, buf, args);
	va_end (args);
}



void
prompt (int num, ...)
{
	va_list args;
	char   *s = msg_getl_bot (num, (msg_cur->language), 1);

	va_start (args, num);
	printexpand (s, args);
	va_end (args);
}


void
sprompt (char *stg, int num, ...)
{
	va_list args;
	char   *s = msg_getl_bot (num, (msg_cur->language), 1);

	inp_acceptinjoth ();
	va_start (args, num);
	sprintexpand (stg, s, args);
	va_end (args);
}


char   *
sprompt_other (struct shmuserrec *ushm, char *stg, int num, ...)
{
	va_list args;
	char   *s;
	uint32  old_flags = out_flags;

	if (ushm->onl.flags & OLF_ISBOT)
		out_flags |= OFL_ISBOT;
	else
		out_flags &= ~OFL_ISBOT;

	s = msg_getl_bot (num, ushm->acc.language - 1, 1);
	va_start (args, num);
	sprintexpand (stg, s, args);
	va_end (args);
	out_flags = old_flags;

	return stg;
}


int
out_printfile (char *fname)
{
	FILE   *fp;

	if ((fp = fopen (fname, "r")) != NULL) {
		int     oldprotect = out_flags & OFL_PROTECTVARS;

		out_clearflags (OFL_PROTECTVARS);

		if (IS_BOT)
			print ("\n%03d\n", BTS_FILE_STARTS);

		while (!feof (fp)) {
			char    line[MSGBUFSIZE];
			int     num = fread (line, 1, sizeof (line) - 1, fp);

			line[num] = 0;
			if (num)
				print (line);
			if (fmt_lastresult == PAUSE_QUIT)
				break;
		}
		oldprotect ? out_setflags (OFL_PROTECTVARS) :
		    out_clearflags (OFL_PROTECTVARS);
		fclose (fp);

		if (IS_BOT)
			print ("\n%03d\n", BTS_FILE_ENDS);

		return 1;
	} else
		return 0;
}


int
out_catfile (char *fname)
{
	FILE   *fp;

	if ((fp = fopen (fname, "r")) != NULL) {
		if (IS_BOT)
			print ("\n%03d\n", BTS_FILE_STARTS);

		while (!feof (fp)) {
			char    line[MSGBUFSIZE];

			if (fgets (line, 1024, fp)) {
				if (fmt_screenpause () == PAUSE_QUIT)
					return 1;
				out_send (fileno (stdout), line,
					  strlen (line));
			}
		}

		if (IS_BOT)
			print ("\n%03d\n", BTS_FILE_ENDS);

		fclose (fp);
		return 1;
	} else
		return 0;
}


int
out_printlongfile (char *fname)
{
	FILE   *fp;
	char    c;

	if ((fp = fopen (fname, "r")) != NULL) {
		int     oldprotect = out_flags & OFL_PROTECTVARS;

		if (IS_BOT)
			print ("\n%03d\n", BTS_FILE_STARTS);

		inp_nonblock ();
		while (!feof (fp)) {
			char    line[MSGBUFSIZE];

			if (read (fileno (stdin), &c, 1) &&
			    ((c == 13) || (c == 10) || (c == 27) || (c == 15)
			     || (c == 3))) {
				fmt_lastresult = PAUSE_QUIT;
				break;
			}
			if (fgets (line, 1024, fp)) {
				if (fmt_screenpause () == PAUSE_QUIT)
					return 1;
				out_send (fileno (stdout), line,
					  strlen (line));
			}
		}
		inp_resetblocking ();
		oldprotect ? out_setflags (OFL_PROTECTVARS) :
		    out_clearflags (OFL_PROTECTVARS);

		if (IS_BOT)
			print ("\n%03d\n", BTS_FILE_ENDS);

		fclose (fp);
		return 1;
	} else
		return 0;
}


void
out_addsubstvar (name, varcalc)
char   *name;
char   *(*varcalc) (void);
{
	struct substvar *new = alcmem (sizeof (struct substvar));
	char   *cp, *tp, temp[64];

	cp = name;
	tp = temp;
	if (*cp != _ASCIIVARCHAR)
		*tp++ = _ASCIIVARCHAR;
	for (; *cp; cp++, tp++) {
		*tp = ((*cp) == _ASCIIVARCHAR ? _VARCHAR : (*cp));
	}
	if (*(tp - 1) != _VARCHAR)
		*tp++ = _VARCHAR;
	*tp = 0;
	new->varname = (char *) alcmem (strlen (name) + 1);
	strcpy (new->varname, temp);
	new->varcalc = varcalc;
	new->next = NULL;
	if (!substvars)
		substvars = new;
	if (lastsubstvar)
		lastsubstvar->next = new;
	lastsubstvar = new;
}


char   *
sv_bbstitle ()
{
	return sysvar->bbstitle;
}


char   *
sv_company ()
{
	return sysvar->company;
}


char   *
sv_address1 ()
{
	return sysvar->address1;
}


char   *
sv_address2 ()
{
	return sysvar->address2;
}


char   *
sv_city ()
{
	return sysvar->city;
}


char   *
sv_dataphone ()
{
	return sysvar->dataphone;
}


char   *
sv_voicephone ()
{
	return sysvar->voicephone;
}


char   *
sv_livephone ()
{
	return sysvar->livephone;
}


char   *
sv_charge ()
{
	static char conv[32];

	sprintf (conv, "%.2f",
		 (float) ((float) thisuseronl.credspermin / 100.0));
	return conv;
}


char   *
sv_chargehour ()
{
	return sysvar->chargehour;
}


char   *
sv_mincredits ()
{
	return sysvar->mincredits;
}


char   *
sv_minmoney ()
{
	return sysvar->minmoney;
}


char   *
sv_version ()
{
	static char s[256];

	strcpy (s, bbs_systemversion);
	return s;
}


char   *
sv_shortversion ()
{
	static char s[256];

	strcpy (s, bbs_shortversion);
	return s;
}


char   *
sv_baudrate ()
{
	char   *s = channel_baudstg (atoi (getenv ("BAUD")));

	return s ? s : "";
}


char   *
sv_time ()
{
	return strtime (now (), 0);
}


char   *
sv_timesec ()
{
	return strtime (now (), 1);
}


char   *
sv_date ()
{
	char   *s = strdate (today ());

	return s;
}


char   *
sv_passexp ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->pswexpiry);
	return conv;
}


char   *
sv_userid ()
{
	return thisuseracc.userid;
}


char   *
sv_username ()
{
	return thisuseracc.username;
}


char   *
sv_usercomp ()
{
	return thisuseracc.company;
}


char   *
sv_useraddr1 ()
{
	return thisuseracc.address1;
}


char   *
sv_useraddr2 ()
{
	return thisuseracc.address2;
}


char   *
sv_userphone ()
{
	return thisuseracc.phone;
}


char   *
sv_userage ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.age);
	return conv;
}


char   *
sv_usersex ()
{
	static char conv[32];

	sprintf (conv, "%c", thisuseracc.sex);
	return conv;
}


char   *
sv_userlang ()
{
	return msg_langnames[(int) thisuseracc.language];
}


char   *
sv_scnwidth ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.scnwidth);
	return conv;
}


char   *
sv_scnheight ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.scnheight);
	return conv;
}


char   *
sv_datecre ()
{
	char   *s = strdate (thisuseracc.datecre);

	return s;
}


char   *
sv_datelast ()
{
	char   *s = strdate (thisuseracc.datelast);

	return s;
}


char   *
sv_userclass ()
{
	return thisuseracc.curclss;
}


char   *
sv_credstdy ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.timetdy);
	return conv;
}


char   *
sv_classdays ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.classdays);
	return conv;
}


char   *
sv_credits ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.credits);
	return conv;
}


char   *
sv_totcreds ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.totcreds);
	return conv;
}


char   *
sv_totpaid ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.totpaid);
	return conv;
}


char   *
sv_curpage ()
{
	return thisuseronl.curpage;
}


char   *
sv_lastpage ()
{
	return thisuseronl.prevpage;
}


char   *
sv_online ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseronl.onlinetime);
	return conv;
}


char   *
sv_numconns ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.connections);
	return conv;
}


char   *
sv_credsever ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.credsever);
	return conv;
}


char   *
sv_timever ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.timever);
	return conv;
}


char   *
sv_filesdnl ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.filesdnl);
	return conv;
}


char   *
sv_kbsdnl ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.bytesdnl >> 10);
	return conv;
}


char   *
sv_filesupl ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.filesupl);
	return conv;
}


char   *
sv_kbsupl ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.bytesupl >> 10);
	return conv;
}


char   *
sv_tnlnum ()
{
	static char conv[32];

	sprintf (conv, "%d", chan_telnetlinecount ());
	return conv;
}


char   *
sv_tnlmax ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->tnlmax);
	return conv;
}


char   *
sv_upassexp ()
{
	static char conv[32];

	sprintf (conv, "%d", thisuseracc.passexp);
	return conv;
}


char   *
sv_tcredspaid ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->tcredspaid);
	return conv;
}


char   *
sv_tcreds ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->tcreds);
	return conv;
}


char   *
sv_ttimever ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->timever);
	return conv;
}


char   *
sv_tfilesupl ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->filesupl);
	return conv;
}


char   *
sv_tfilesdnl ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->filesdnl);
	return conv;
}


char   *
sv_tbytesupl ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->bytesupl);
	return conv;
}


char   *
sv_tbytesdnl ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->bytesdnl);
	return conv;
}


char   *
sv_sigmsgs ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->sigmessages);
	return conv;
}


char   *
sv_emsgs ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->emessages);
	return conv;
}


char   *
sv_nmsgs ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->nmessages);
	return conv;
}


char   *
sv_tconns ()
{
	static char conv[32];

	sprintf (conv, "%d", sysvar->connections);
	return conv;
}


void
out_initsubstvars ()
{
	struct substvar table[] = {
		{"@BBS@", sv_bbstitle, NULL},
		{"@COMPANY@", sv_company, NULL},
		{"@ADDRESS1@", sv_address1, NULL},
		{"@ADDRESS2@", sv_address2, NULL},
		{"@CITY@", sv_city, NULL},
		{"@DATAPH@", sv_dataphone, NULL},
		{"@VOICEPH@", sv_voicephone, NULL},
		{"@LIVEPH@", sv_livephone, NULL},
		{"@CHARGE@", sv_charge, NULL},
		{"@CHRGEHOUR@", sv_chargehour, NULL},
		{"@MINCREDITS@", sv_mincredits, NULL},
		{"@MINMONEY@", sv_minmoney, NULL},
		{"@VERSION@", sv_version, NULL},
		{"@SHORTVERSION@", sv_shortversion, NULL},
		{"@BAUD@", sv_baudrate, NULL},
		{"@TIME@", sv_time, NULL},
		{"@TIMESEC@", sv_timesec, NULL},
		{"@DATE@", sv_date, NULL},
		{"@PASSEXP@", sv_passexp, NULL},
		{"@USERID@", sv_userid, NULL},
		{"@USERNAME@", sv_username, NULL},
		{"@USERCOMP@", sv_usercomp, NULL},
		{"@USERADDR1@", sv_useraddr1, NULL},
		{"@USERADDR2@", sv_useraddr2, NULL},
		{"@USERPHONE@", sv_userphone, NULL},
		{"@USERAGE@", sv_userage, NULL},
		{"@USERSEX@", sv_usersex, NULL},
		{"@USERLANG@", sv_userlang, NULL},
		{"@SCNWIDTH@", sv_scnwidth, NULL},
		{"@SCNHEIGHT@", sv_scnheight, NULL},
		{"@DATECRE@", sv_datecre, NULL},
		{"@DATELAST@", sv_datelast, NULL},
		{"@USERCLASS@", sv_userclass, NULL},
		{"@CREDSTDY@", sv_credstdy, NULL},
		{"@CLASSDAYS@", sv_classdays, NULL},
		{"@CREDITS@", sv_credits, NULL},
		{"@TOTCREDS@", sv_totcreds, NULL},
		{"@TOTPAID@", sv_totpaid, NULL},
		{"@PAGE@", sv_curpage, NULL},
		{"@LASTPAGE@", sv_lastpage, NULL},
		{"@ONLINE@", sv_online, NULL},
		{"@NUMCONNS@", sv_numconns, NULL},
		{"@CREDSEVER@", sv_credsever, NULL},
		{"@TIMEVER@", sv_timever, NULL},
		{"@FILESDNL@", sv_filesdnl, NULL},
		{"@KBSDNL@", sv_kbsdnl, NULL},
		{"@FILESUPL@", sv_filesupl, NULL},
		{"@KBSUPL@", sv_kbsupl, NULL},
		{"@TNLNUM@", sv_tnlnum, NULL},
		{"@TNLMAX@", sv_tnlmax, NULL},
		{"@UPASSEXP@", sv_upassexp, NULL},
		{"@TCREDSPAID@", sv_tcredspaid, NULL},
		{"@TCREDS@", sv_tcreds, NULL},
		{"@TTIMEVER@", sv_ttimever, NULL},
		{"@TFILESUPL@", sv_tfilesupl, NULL},
		{"@TFILESDNL@", sv_tfilesdnl, NULL},
		{"@TBYTESUPL@", sv_tbytesupl, NULL},
		{"@TBYTESDNL@", sv_tbytesdnl, NULL},
		{"@SIGMSGS@", sv_sigmsgs, NULL},
		{"@EMSGS@", sv_emsgs, NULL},
		{"@NMSGS@", sv_nmsgs, NULL},
		{"@TCONNS@", sv_tconns, NULL},
		{"", NULL, NULL}
	};

	int     i = 0;

	while (table[i].varname[0]) {
		out_addsubstvar (table[i].varname, table[i].varcalc);
		i++;
	}
}


void
__out_setclear (int set, uint32 f)
{
	if (set) {
		out_flags |= f;
	} else
		out_flags &= ~f;

	if (thisshm != NULL && f & OFL_AFTERINPUT) {
		if (out_flags & OFL_AFTERINPUT)
			thisuseronl.flags |= OLF_AFTERINP;
		else
			thisuseronl.flags &= ~OLF_AFTERINP;
	}
}
