# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:50 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:50  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.8  2004/07/15 14:50:34  alexios
# Changed instances of CFLAGS to AM_CFLAGS so as not to override user
# settings.
#
# Revision 1.7  2004/02/29 18:07:39  alexios
# Added mailfixup.
#
# Revision 1.6  2003/12/27 13:16:53  alexios
# Moved the netclub tool here, compiled if MetaBBS is enabled.
#
# Revision 1.5  2003/12/27 13:07:09  alexios
# Moved bbsmail as a subdirectory of this one.
#
# Revision 1.4  2003/12/27 12:50:31  alexios
# Moved numerous objects from the program build to the library. Realised
# that clubs needs to be compiled with -DCLUBS, and added declarations
# to that effect.
#
# Revision 1.3  2003/12/25 18:04:44  alexios
# Split off clubhdr into a separate convenience library, as it is used
# by numerous other modules and programs throughout the system.
#
# Revision 1.2  2003/12/25 13:34:01  alexios
# Structured properly to generate both club and email modules and to
# include typhoon support.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

if HAVE_METABBS
METABBS = netclub
else !HAVE_METABBS
METABBS =
endif !HAVE_METABBS

SUBDIRS = . bbsmail $(METABBS) offline.mail mailfixup

PROGNAMES = email clubs

BUILT_SOURCES = ecdb.h   ihavedb.h   mbk_emailclubs.h 
EXTRA_DIST    = ecdb.ddl ihavedb.ddl
CLEANFILES    = ecdb.dbd ihavedb.dbd

lib_LTLIBRARIES = libmegistos_clubhdr.la
libmegistos_clubhdr_la_LDFLAGS = @LDFLAGS@ -version-info @SOVERSION@
libmegistos_clubhdr_la_SOURCES =		\
	clubhdr.c				\
	database.c				\
	dbnum.c					\
	dbto.c					\
	dbfrom.c				\
	dbsubj.c				\
	funcs.c

pkginclude_HEADERS = ecdb.h ihavedb.h

COMMON =					\
	clubfx.c				\
	clublist.c				\
	clubop.c				\
	clubread.c				\
	clubscan.c				\
	distlist.c				\
	download.c				\
	misc.c					\
	modify.c				\
	operations.c				\
	read.c					\
	receipt.c				\
	reply.c					\
	substvars.c				\
	write.c

email_SOURCES =					\
	$(COMMON)				\
	clubcleanup.c				\
	email.c					\
	email.h					\
	mailcleanup.c				\
	mailcleanup.h				\
	prefs.c					\
	qsc.c					\
	reindex.c

clubs_SOURCES =					\
	$(COMMON)				\
	clubs.c					\
	clubs.h					\
	clubwrite.c				\
	networking.c				\
	qsc.c

include $(top_srcdir)/templates/module
include $(top_srcdir)/templates/typhoon

email_LDADD = $(LDADD) libmegistos_clubhdr.la
clubs_LDADD = $(LDADD) libmegistos_clubhdr.la
clubs_CFLAGS = $(AM_CFLAGS) $(CFLAGS) -DCLUBS

# End of file
