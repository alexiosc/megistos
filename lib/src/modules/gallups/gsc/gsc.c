/*****************************************************************************\
 **                                                                         **
 **  FILE:      gsc.c                                                       **
 **  AUTHORS:   Antonis Stamboulis (Xplosion), Vangelis Rokas (Valis)       **
 **  PURPOSE:   Gallups Script Compiler                                     **
 **  NOTES:     This was originally in the gallups.c                        **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.3  2000/09/30 09:25:13  bbs
 * changed gsc version to 2.4
 * changed gallup script format version to 4.1
 *
 * Revision 1.2  2000/09/27 18:35:06  bbs
 * gsc version advanced from 1.1 to 2.3
 * various new command line arguments added (see source)
 * removed option to install. Gallups are now installed from
 *   the gallups module
 * output is a file specified in command line
 *
 * Revision 1.1  2000/09/21 18:15:54  bbs
 * the universal gallup script compiler
 * support for GNU C and Borland C
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


/* To build the GSC you need the following files:
 * gallup.c
 * compiler.c
 * gsc.c
 * analyze.c
 *
 * When compiling define __GSC__ so the correct source code will be included
 *
 */

#if !defined(__GSC__)
#error Macro __GSC__ is not defined. Recompile all files with -D__GSC__
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct version {
	unsigned char cmaj;		// compiler major version
	unsigned char cmin;		// compiler minor version
	unsigned char smaj;		// script revision major version
	unsigned char smin;		// script revision minor version
} VERSION = {	2, 4,	4, 1 };

#include "gsc.h"

#if defined(__BORLANDC__)
#include "glps-bcc.h"
#else

#include "gallups.h"
#endif

int gscflags=0;

#ifdef __BORLANDC__
#  define show		if(!(gscflags&QUIET))printf
#else
#  define show(f...)	if(!(gscflags&QUIET))printf(##f)
#endif

#define showinfo(flag)	if(gflgs(ginfo) & flag)show("%s ", #flag)


struct gallup *ginfo;


struct gallup gallupsinfo;


/* In GNU C a simple backslash would be enough, but in Borland C it doesn't */
const char helpmsg[]="\n\
Syntax:\n\
	%s [-qvyiz?] [-{no}<name>] [-malt] [-c<userid>] [-xN] [-e{td}#] script\n\
\n\
\n\
   compiler options\n\
	-q	quiet execution\n\
	-v	compiler version and script revision\n\
	-d	print lots of debug information\n\
	-?	this help\n\
\n\
   script options\n\
	-y	do not save, just do syntax processing\n\
	-i	show information about gallup\n\
	-z	analyze script data file\n\
	-n<name> set gallup name to <name>\n\
	-o<name> output file\n\
\n\
   gallup options\n\
	-m	allow multiple submits\n\
	-a	allow all users to view results\n\
	-l	log user ids\n\
	-t	time the gallup (only in quiz)\n\
	-c<id>	the creator's userid\n\
	-xN	extra checking on quizzes to leven N :\n\
			0: relaxed (default)\n\
			1: strict, prompt for last question\n\
			2: very strict, prompt for next question\n\
	-et#	set gallup time to N (N is a longint)\n\
	-ed#	set gallup date to N (N is a longint)\n\
\n\
\n";


char filename[128]="";
char gallupname[128]="";
char outname[128]="";

int main(int argc, char *argv[])
{
  int i=0;

	if(argc<2 || !strcmp(argv[1], "-?")) {
		printf("Gallup Script Compiler\n");
		printf(helpmsg,
#ifdef __BORLANDC__
		strrchr(argv[0], '\\')?(strrchr(argv[0], '\\')+1):argv[0]);
#else
		strrchr(argv[0], '/')?(strrchr(argv[0], '/')+1):argv[0]);
#endif

		exit(1);
	}

	ginfo = &gallupsinfo;
	gflgs(ginfo) = 0;
	memset(gauth(ginfo), 0, sizeof(gauth(ginfo)));

	for(i=1;i<argc;i++) {
		if(argv[i][0] == '-') {
			switch(argv[i][1]) {
				case '1':
					printf("sizeof(struct gallup) = %i\n", sizeof(struct gallup));
					exit(0);
					break;
	
				case 'm': gflgs(ginfo) |= GF_MULTISUBMIT; break;
				case 'a': gflgs(ginfo) |= GF_VIEWRESALL; break;
				case 'l': gflgs(ginfo) |= GF_LOGUSERID; break;
				case 't': gflgs(ginfo) |= GF_TIMED; break;
				case 'c': strcpy(gauth(ginfo), &argv[i][2]); break;
				case 'x':
					switch(argv[i][2]) {
						case '1': gflgs(ginfo) |= GF_EXTRA; break;
						case '2': gflgs(ginfo) |= GF_EXTRA | GF_GONEXT; break;
						default: gflgs(ginfo) &= ~(GF_EXTRA | GF_GONEXT); break;
					}
					break;
				case 'e':
					switch(argv[i][2]) {
						case 't': gtset(ginfo) = atoi(&argv[i][3]); break;
						case 'd': gdset(ginfo) = atoi(&argv[i][3]); break;
					}
					break;
					
				case 'y': gscflags |= SYNTAX; break;
				case 'd': gscflags |= VERBOSE; break;
				case 'i': gscflags |= INFO; break;
				case 'q': gscflags |= QUIET; break;
				case 'z': gscflags |= ANALYZE; break;
				case 'n': strcpy(gallupname, &argv[i][2]); break;
				case 'o': strcpy(outname, &argv[i][2]); break;
				case 'v': {
					printf("%i.%i %i.%i\n", VERSION.cmaj, VERSION.cmin, VERSION.smaj, VERSION.smin);
					exit(0);
				}

				default:
					printf("unknown command line argument\n");
					exit(2);

			}
		} else {
			strcpy(filename, argv[i]);
		}
	}

	if(!filename[0]) {
		printf("no script file given\n");
		exit(2);
	}

	if(gscflags & ANALYZE) {
		analyze(filename);
		exit(0);
	}

	if(gallupname[0])strcpy(gfnam(ginfo), gallupname);
	else {
		if(strrchr(filename, '/'))strcpy( gallupname, strrchr(filename, '/')+1);
		else strcpy(gallupname, filename);
		strcpy(gfnam(ginfo), filename);
	}

	if(strchr(gallupname, ' ') || strchr(gallupname, '\t')) {
		printf("Invalid characters in gallup name\n");
		exit(1);
	}

	strcpy(gfnam(ginfo), gallupname);
	
	printf("Compiling script %s with name %s\n", filename, gallupname);
//	exit(0);
	
	if(scriptcompiler(filename)) {


		if(gscflags & INFO) {
#if 1
			show("Flags : ");
			showinfo(GF_POLL);
			showinfo(GF_QUIZ);
			showinfo(GF_MULTISUBMIT);
			showinfo(GF_LOGUSERID);
			showinfo(GF_VIEWRESALL);
			showinfo(GF_TIMED);
			showinfo(GF_EXTRA);
			showinfo(GF_GONEXT);
			show("\n");
#else
			if(gcrtr(ginfo)[0])show("Author: %s\n", gcrtr(ginfo));
			show("User ID's will %s logged\n", (gflgs(ginfo) & GF_LOGUSERID)?"be":"not be");
			show("Users can submit gallup %s once\n", (gflgs(ginfo) & GF_MULTISUBMIT)?"more than":"only");
			show("The results are available to %s\n", (gflgs(ginfo) & GF_VIEWRESALL)?"all users":"sysops only");
			show("The game will %s timed\n", (gflgs(ginfo) & GF_TIMED)?"be":"not be");
#endif

		}

		printf("Success\n");
		return 0;
	} else {
		printf("Script compilation failed.\n");
		return 1;
	}

  return 1;
}

