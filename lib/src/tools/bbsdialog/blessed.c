/*****************************************************************************\
 **                                                                         **
 **  FILE:     blessed.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, November 94, Version 1.1                                  **
 **            C, July 95, Version 1.2                                      **
 **  PURPOSE:  Handle linear data entry sessions.                           **
 **  NOTES:    This code has been blessed by the gods.                      **
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
 * Revision 1.4  2003/12/23 23:20:24  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 22:07:30  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.4  1998/12/27 16:30:50  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:29:41  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:02:58  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:21:38  alexios
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
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/bbsdialog.h>
#include <megistos/mbk_bbsdialog.h>


static char *endtemplate = NULL;
static char *toggles[2];


static void
listclasses ()
{
	int     i;

	prompt (CLSLSTHDR, NULL);
	for (i = 0; i < cls_count; i++)
		prompt (CLSLSTTAB, cls_classes[i].name);
	prompt (CLSLSTEND, NULL);
}


static int
getclassname (class, msg, existing, err, def, defval)
char   *class, *defval;
int     msg, existing, err, def;
{
	char    newclass[10];
	int     i, ok = 0;

	while (!ok) {
		memset (newclass, 0, 10);
		if (cnc_more ())
			strncpy (newclass, cnc_word (), 10);
		else {
			prompt (msg, NULL);
			if (def) {
				sprintf (out_buffer, msg_get (def), defval);
				print (out_buffer, NULL);
			}
			inp_get (0);
			if (margc)
				strncpy (newclass, margv[0], 10);
			else if (def && !inp_reprompt ()) {
				strncpy (class, defval, 10);
				return 1;
			} else
				cnc_end ();
		}
		if (sameas (newclass, "x"))
			return 0;
		if (newclass[0] == '?') {
			newclass[0] = 0;
			listclasses ();
			continue;
		}
		if (!newclass[0]) {
			cnc_end ();
			continue;
		}
		ok = (existing == 0);
		for (i = 0; newclass[i]; i++)
			newclass[i] = toupper (newclass[i]);
		for (i = 0; i < cls_count; i++) {
			if (sameas (newclass, cls_classes[i].name)) {
				if (existing)
					ok = 1;
				else {
					cnc_end ();
					sprintf (out_buffer, msg_get (err),
						 newclass);
					print (out_buffer, NULL);
					ok = 0;
					break;
				}
			}
		}
		if (existing && !ok) {
			sprintf (out_buffer, msg_get (err), newclass);
			print (out_buffer, NULL);
			cnc_end ();
		}
	}
	strncpy (class, newclass, 10);
	return 1;
}


static void
parsetemplate ()
{
	FILE   *data = NULL;
	unsigned char c;
	char    buffer[8192], *bp = buffer;
	char    parms[1024], *cp, *ep, dataline[257];
	int     state = 0, len = 0;
	int     quote = 0, i;
	char   *msg_buffer;

	sprintf (out_buffer, "%s\033@1;\"\007OK\"b\033@1;\"\007CANCEL\"b",
		 msg_get (ltnum));
	msg_buffer = out_buffer;

	if ((data = fopen (dfname, "r")) == NULL) {
		error_fatalsys ("Unable to open data file %s", dfname);
	}

	memset (buffer, 0, sizeof (buffer));
	while ((c = *(msg_buffer++)) != 0) {
		if (c == 13)
			continue;
		if (c == 27 && !state)
			state = 1;
		else if (c == '@' && state == 1) {
			state = 3;
			len = 0;
			parms[0] = 0;
		} else if (state == 3) {
			union object obj;

			if (isdigit (c) || c == '-' || c == ';' || c == '"' ||
			    quote) {
				if (c == '"')
					quote = !quote;
				parms[len++] = c;
				parms[len] = 0;
				parms[len + 1] = 0;
				len = len % 1021;
			} else {
				state = 0;
				quote = 0;
				memset (&obj, 0, sizeof (obj));
				switch (c) {
				case 's':
					obj.s.type = OBJ_STRING;
					if (sscanf
					    (parms, "%d;%d;%ld", &obj.s.max,
					     &obj.s.shown,
					     &obj.s.flags) == 3) {
						numobjects++;
						if ((obj.s.data =
						     alcmem (obj.s.max + 1)) ==
						    NULL ||
						    (obj.s.template =
						     alcmem (strlen (buffer) +
							     1)) == NULL ||
						    (object =
						     realloc (object,
							      sizeof (union
								      object) *
							      numobjects)) ==
						    NULL) {
							error_fatal
							    ("Unable to allocate dialog object buffers");
						}
						dataline[0] = 0;
						fgets (dataline,
						       sizeof (dataline),
						       data);
						if ((cp =
						     strchr (dataline,
							     '\n')) != NULL)
							*cp = 0;
						memset (obj.s.data, 0,
							obj.s.max + 1);
						strncpy (obj.s.data, dataline,
							 obj.s.max);
						obj.s.cp = strlen (obj.s.data);

						strcpy (obj.s.template,
							buffer);
						memset (buffer, 0,
							sizeof (buffer));
						bp = buffer;

						if (obj.s.flags & 1) {
							int     i;

							for (i = 0;
							     obj.s.data[i];
							     i++)
								obj.s.data[i] =
								    toupper
								    (obj.s.
								     data[i]);
						}
						memcpy (&object
							[numobjects - 1], &obj,
							sizeof (union object));
					}
					break;

				case 'n':
					obj.n.type = OBJ_NUM;
					if (sscanf
					    (parms, "%d;%d;%d;%ld",
					     &obj.n.shown, &obj.n.min,
					     &obj.n.max, &obj.n.flags) == 4) {
						numobjects++;
						if ((obj.n.data =
						     alcmem (obj.n.shown +
							     1)) == NULL ||
						    (obj.n.template =
						     alcmem (strlen (buffer) +
							     1)) == NULL ||
						    (object =
						     realloc (object,
							      sizeof (union
								      object) *
							      numobjects)) ==
						    NULL) {
							error_fatal
							    ("Unable to allocate dialog object buffers");
						}
						dataline[0] = 0;
						fgets (dataline,
						       sizeof (dataline),
						       data);
						if ((cp =
						     strchr (dataline,
							     '\n')) != NULL)
							*cp = 0;
						sscanf (dataline, " %s ",
							obj.n.data);
						obj.n.cp = strlen (obj.n.data);

						strcpy (obj.n.template,
							buffer);
						memset (buffer, 0,
							sizeof (buffer));
						bp = buffer;

						memcpy (&object
							[numobjects - 1], &obj,
							sizeof (union object));
					}
					break;

				case 'l':
					obj.l.type = OBJ_LIST;
					if (sscanf
					    (parms, "%d;\"%n", &obj.l.size,
					     &i) == 1) {
						numobjects++;
						cp = &parms[i];
						if ((obj.l.options =
						     alcmem (strlen (cp) +
							     1)) == NULL ||
						    (obj.l.template =
						     alcmem (strlen (buffer) +
							     1)) == NULL ||
						    (object =
						     realloc (object,
							      sizeof (union
								      object) *
							      numobjects)) ==
						    NULL) {
							error_fatal
							    ("Unable to allocate dialog object buffers");
						}
						memset (obj.l.options, 0,
							strlen (cp) + 1);
						strncpy (obj.l.options, cp,
							 strlen (cp));

						dataline[0] = 0;
						fgets (dataline,
						       sizeof (dataline),
						       data);
						if ((ep =
						     strchr (dataline,
							     '\n')) != NULL)
							*ep = 0;

						obj.l.data = obj.l.options;
						for (ep = cp, i = 0;
						     obj.l.options[i]; i++) {
							if (obj.l.options[i] ==
							    '|' ||
							    obj.l.options[i] ==
							    '"') {
								obj.l.
								    options[i]
								    = 0;
								if (!strcmp
								    (ep,
								     dataline))
									obj.l.
									    data
									    =
									    ep;
								ep = &obj.l.
								    options[i +
									    1];
							}
						}

						strcpy (obj.l.template,
							buffer);
						memset (buffer, 0,
							sizeof (buffer));
						bp = buffer;

						memcpy (&object
							[numobjects - 1], &obj,
							sizeof (union object));
					}
					break;

				case 't':
					obj.t.type = OBJ_TOGGLE;
					numobjects++;
					cp = &parms[i];
					if ((obj.t.template =
					     alcmem (strlen (buffer) + 1)) ==
					    NULL ||
					    (object =
					     realloc (object,
						      sizeof (union object) *
						      numobjects)) == NULL) {
						error_fatal
						    ("Unable to allocate dialog object buffers");
					}
					dataline[0] = 0;
					fgets (dataline, sizeof (dataline),
					       data);
					if ((ep =
					     strchr (dataline, '\n')) != NULL)
						*ep = 0;
					obj.t.data =
					    strcasecmp (dataline, "on") == 0;

					strcpy (obj.t.template, buffer);
					memset (buffer, 0, sizeof (buffer));
					bp = buffer;

					memcpy (&object[numobjects - 1], &obj,
						sizeof (union object));
					break;

				case 'b':
					obj.b.type = OBJ_BUTTON;
					if (sscanf
					    (parms, "%d;\"%n", &obj.b.size,
					     &i) == 1) {
						numobjects++;
						cp = &parms[i];
						if ((obj.b.template =
						     alcmem (strlen (buffer) +
							     1)) == NULL ||
						    (obj.b.label =
						     alcmem (strlen (cp) +
							     1)) == NULL ||
						    (object =
						     realloc (object,
							      sizeof (union
								      object) *
							      numobjects)) ==
						    NULL) {
							error_fatal
							    ("Unable to allocate dialog object buffers");
						}
						if ((ep =
						     strchr (cp, '"')) != NULL)
							*ep = 0;
						obj.b.key = *cp;
						strncpy (obj.b.label,
							 (char *) (cp + 1),
							 strlen (cp));

						dataline[0] = 0;
						fgets (dataline,
						       sizeof (dataline),
						       data);

						strcpy (obj.b.template,
							buffer);
						memset (buffer, 0,
							sizeof (buffer));
						bp = buffer;

						memcpy (&object
							[numobjects - 1], &obj,
							sizeof (union object));
					}
					break;
				}
			}
		} else if (state == 1) {
			state = 0;
			*(bp++) = 27;
			*(bp++) = c;
		} else if (!state)
			*(bp++) = c;
	}
	endtemplate = alcmem (strlen (buffer) + 1);
	strcpy (endtemplate, buffer);
	fclose (data);
}


static void
showstringfield (int i)
{
	char    meta[32], format[256];
	int     j;

	sprintf (meta, "%%-%ds", object[i].s.shown);
	if (object[i].s.shown < strlen (object[i].s.data)) {
		strncpy (format, object[i].s.data, object[i].s.shown - 3);
		if (object[i].s.flags & 1)
			for (j = 0; format[j]; j++)
				format[j] = toupper (format[j]);
		if (object[i].s.flags & 2)
			for (j = 0; format[j]; j++)
				format[j] = '*';
		strcat (format, "...");
	} else {
		strcpy (format, object[i].s.data);
		if (object[i].s.flags & 1)
			for (j = 0; format[j]; j++)
				format[j] = toupper (format[j]);
		if (object[i].s.flags & 2)
			for (j = 0; format[j]; j++)
				format[j] = '*';
	}
	print (meta, format);
}


static void
shownumfield (int i)
{
	char    meta[16];

	sprintf (meta, "%%%ds",
		 object[i].n.flags & 1 ? object[i].n.shown : -object[i].n.
		 shown);
	print (meta, object[i].n.data);
}


static void
showlistfield (int i)
{
	char    meta[32];

	sprintf (meta, "%%-%ds", object[i].l.size);
	print (meta, object[i].l.data);
}


static void
showtogglefield (int i)
{
	print ("%s", toggles[object[i].t.data & 1]);
}


static void
showmenu ()
{
	int     i;

	out_setflags (OFL_AFTERINPUT);
	for (i = 0; i < numobjects; i++) {
		print (object[i].s.template);
		switch (object[i].s.type) {
		case OBJ_STRING:
			showstringfield (i);
			break;
		case OBJ_NUM:
			shownumfield (i);
			break;
		case OBJ_LIST:
			showlistfield (i);
			break;
		case OBJ_TOGGLE:
			showtogglefield (i);
			break;
		}
	}
	print (endtemplate);
}


static void
getstringfield (int i)
{
	char    s[MAXINPLEN], *t = s;

	if (!cnc_more ()) {
		msg_set (templates);
		prompt (ltnum + 1 + i);
	}
	msg_set (msg);
	for (;;) {
		if ((!cnc_more ()) || (object[i].s.flags & 2)) {
			if (object[i].s.flags & 2)
				inp_setflags (INF_PASSWD);
			if (object[i].s.flags & 8) {
				if (!get_userid (s, FIELD, UERR, 0, 0, 0)) {
					prompt (FCAN);
					return;
					t = s;
				}
			} else if (object[i].s.flags & 16) {
				if (!getclassname (s, FIELD, 1, CERR, 0, 0)) {
					prompt (FCAN);
					return;
					t = s;
				}
			} else {
				prompt (FIELD);
				inp_get (object[i].s.max);
				cnc_begin ();
				t = cnc_nxtcmd;
			}
			inp_clearflags (INF_PASSWD);
		}
		if (sameas (t, "X")) {
			prompt (FCAN);
			return;
		} else {
			int     j;

			strncpy (object[i].s.data, t, object[i].s.max);
			if (object[i].s.flags & 1) {
				for (j = 0; object[i].s.data[j]; j++) {
					object[i].s.data[j] =
					    toupper (object[i].s.data[j]);
				}
			}
			if ((object[i].s.flags & 4) &&
			    (scandate (object[i].s.data) < 0)) {
				prompt (DERR);
				cnc_end ();
				continue;
			}
			return;
		}
	}
}


static void
getnumfield (int i)
{
	int     n;

	if (!cnc_more ()) {
		msg_set (templates);
		prompt (ltnum + 1 + i);
	}
	msg_set (msg);

	if (get_number
	    (&n, FIELD, object[i].n.min, object[i].n.max, NERR, 0, 0)) {
		sprintf (object[i].n.data, "%d", n);
	} else
		prompt (FCAN);
}


static void
getlistfield (int obj)
{
	int     shownmenu = 0;
	char    c;

	if (!cnc_more ()) {
		msg_set (templates);
		prompt (ltnum + 1 + obj);
	}
	msg_set (msg);

	for (;;) {
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return;
			c = cnc_chr ();
			shownmenu = 1;
		} else {
			if (!shownmenu) {
				int     i;
				char   *cp;

				msg_set (msg);
				prompt (LISTMHDR);
				for (i = 1, cp = object[obj].l.options; *cp;
				     cp += strlen (cp) + 1, i++) {
					prompt (LISTMENU, i, cp);
				}
				prompt (LISTMFTR);
			}
			prompt (LIST);
			inp_get (0);
			cnc_begin ();
		}
		if (!margc) {
			cnc_end ();
			continue;
		}
		if (inp_isX (margv[0])) {
			return;
		} else if (margc && sameas (margv[0], "?")) {
			shownmenu = 0;
			continue;
		} else {
			int     opt = atoi (margv[0]);

			if (opt < 1) {
				prompt (ERRSEL, margv[0]);
				cnc_end ();
				continue;
			} else {
				int     i, found = 0;
				char   *cp;

				for (i = 1, cp = object[obj].l.options; *cp;
				     cp += strlen (cp) + 1, i++)
					if (i == opt) {
						object[obj].l.data = cp;
						return;
					}
				if (!found) {
					prompt (ERRSEL, margv[0]);
					cnc_end ();
					continue;
				}
			}
		}
	}
}


static void
gettogglefield (int i)
{
	msg_set (templates);
	prompt (ltnum + 1 + i);
	object[i].t.data = !object[i].t.data;
	msg_set (msg);
	prompt (TOGON + (!object[i].t.data));
}


static void
mainloop ()
{
	int     shownmenu = 0;

	for (;;) {
		if (!shownmenu) {
			showmenu ();
			shownmenu = 1;
		}
		prompt (PROMPT);
		inp_get (0);
		cnc_begin ();
		if (!margc || inp_reprompt ())
			continue;
		else if (margc == 1 && sameas (margv[0], "?"))
			shownmenu = 0;
		else if (margc == 1 && inp_isX (margv[0])) {
			int     i;

			msg_set (msg);
			cnc_end ();
			if (get_bool (&i, CONFIRM, CONFERR, 0, 0)) {
				if (i) {
					msg_reset ();
					endsession ("Cancel");
				}
			}
			msg_reset ();
		} else if (margc == 1 && sameas (margv[0], "OK"))
			endsession ("OK");
		else {
			char   *command = cnc_word ();
			int     i, j = atoi (command), found = 0;

			for (i = 0; i < numobjects; i++) {
				if (j == i + 1 &&
				    object[i].s.type != OBJ_BUTTON) {
					found = 1;
					switch (object[i].s.type) {
					case OBJ_STRING:
						getstringfield (i);
						break;
					case OBJ_NUM:
						getnumfield (i);
						break;
					case OBJ_LIST:
						getlistfield (i);
						break;
					case OBJ_TOGGLE:
						gettogglefield (i);
						break;
					}
				} else if (strlen (command) == 1 &&
					   object[i].s.type == OBJ_BUTTON &&
					   command[0] == object[i].b.key) {
					if (sameas
					    (object[i].b.label, "Cancel")) {
						int     i;

						msg_set (msg);
						cnc_end ();
						if (get_bool
						    (&i, CONFIRM, CONFERR, 0,
						     0)) {
							if (i) {
								msg_reset ();
								endsession
								    ("Cancel");
							}
						}
						msg_reset ();
					} else
						endsession (object[i].b.label);
				}
			}
			if (!found) {
				prompt (ERRSEL, command);
				cnc_end ();
			}
		}
	}
}


void
runlinear ()
{
	msg_set (templates);
	parsetemplate ();
	msg_set (msg);
	toggles[0] = msg_string (NO);
	toggles[1] = msg_string (YES);
	mainloop ();
	endsession ("Cancel");
}


/* End of File */
