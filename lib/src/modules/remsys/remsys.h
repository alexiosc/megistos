/*****************************************************************************\
 **                                                                         **
 **  FILE:     remsys.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  External definitions for the Remote Sysop menu               **
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
 * Revision 1.5  2003/12/24 21:53:13  alexios
 * Removed rcsinfo.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  2000/01/06 11:42:07  alexios
 * Added variable pgstmo to denote the length of time after a
 * user's page to the system console that the event stays flagged
 * in the channel list and the main console itself.
 *
 * Revision 0.5  1998/07/24 10:23:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/06 16:59:23  alexios
 * Prototypes for new functions rsys_pageaudit(), rsys_security(),
 * rsys_signups and rsys_filtaud().
 *
 * Revision 0.2  1997/09/12 13:24:18  alexios
 * Added KEYCHU, DFWARN and DFCRIT options.
 *
 * Revision 0.1  1997/08/28 11:05:52  alexios
 * First registered revision. Adequate.
 *
 *
 */


#define A(x)        (a[x]?stron:stroff)
#define HASAXS(a,x) (a[x/32]&(1<<(x%32)))

struct rsysopt {
	char    command[16];
	int     group;
	long    accessflag;
	void    (*action) (void);
};

extern int COMMANDS;
extern promptblock_t *msg;
extern struct rsysopt commands[];


extern char *unixsh;
extern char *sxfdesc;
extern int keychu;
extern int kydnam;
extern int kydcom;
extern int kydadr;
extern int kydpho;
extern int kydage;
extern int kydsex;
extern int kydpss;
extern int hidepass;
extern int dfwarn;
extern int dfcrit;
extern int pgstmo;

extern void rsys_change ();
extern void rsys_emulate ();
extern void rsys_monitor ();
extern void rsys_send ();

extern void rsys_delete ();
extern void rsys_exempt ();
extern void rsys_post ();
extern void rsys_hangup ();
extern void rsys_suspend ();
extern void rsys_detail ();
extern void rsys_search ();

extern void rsys_classed ();
extern void rsys_class ();
extern void rsys_keys ();

extern void rsys_event ();
extern void rsys_transfer ();
extern void rsys_pageaudit ();
extern void rsys_invis ();
extern void rsys_gdet ();
extern void rsys_sysop ();
extern void rsys_audit ();
extern void rsys_cleanup ();
extern void rsys_logon ();
extern void rsys_security ();
extern void rsys_filtaud ();
extern void rsys_signups ();

extern void rsys_agestats ();
extern void rsys_clsstats ();
extern void rsys_modstats ();
extern void rsys_systats ();
extern void rsys_linstats ();
extern void rsys_genstats ();
extern void rsys_top ();

extern void rsys_type ();
extern void rsys_copy ();
extern void rsys_ren ();
extern void rsys_dir ();
extern void rsys_del ();
extern void rsys_sys ();
extern void rsys_editor ();
extern void rsys_shell ();


extern int runcommand (char *s);
extern int getchanname (char *dev, int msg, int all);



/* End of File */
