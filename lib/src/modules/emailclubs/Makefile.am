# -*- Makefile -*-
#
# $Id$
#
# $Log$
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

LDFLAGS_EXTRA =

PROGNAMES = email clubs

BUILT_SOURCES = ecdb.h   ihavedb.h   mbk_emailclubs.h 
EXTRA_DIST    = ecdb.ddl ihavedb.ddl
CLEANFILES    = ecdb.dbd ihavedb.dbd

lib_LTLIBRARIES = libmegistos_clubhdr.la
libmegistos_clubhdr_la_LDFLAGS = @LDFLAGS@ -version-info @SOVERSION@
libmegistos_clubhdr_la_SOURCES = clubhdr.c

COMMON =					\
	clubfx.c				\
	clublist.c				\
	clubop.c				\
	clubread.c				\
	clubscan.c				\
	database.c				\
	dbfrom.c				\
	dbnum.c					\
	dbsubj.c				\
	dbto.c					\
	distlist.c				\
	download.c				\
	funcs.c					\
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

# End of file
