# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.2  2003/12/25 13:34:01  alexios
# Structured properly to generate both club and email modules and to
# include typhoon support.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

PROGNAMES = email clubs

BUILT_SOURCES = ecdb.h   ihavedb.h   mbk_emailclubs.h 
EXTRA_DIST    = ecdb.ddl ihavedb.ddl
CLEANFILES    = ecdb.dbd ihavedb.dbd

COMMON =					\
	clubfx.c				\
	clubhdr.c				\
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

# End of file
