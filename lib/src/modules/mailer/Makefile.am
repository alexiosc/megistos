# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:52  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.2  2003/12/27 12:53:52  alexios
# Major changes. Part of the mailer is now built as a library against
# which all mailer modules are linked. To do so, the offline request
# code that resided in offline.mail was moved here, and the Makefile was
# updated to reflect this. To this end, typhoon declarations were also
# added.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

SUBDIRS = . plugins

BUILT_SOURCES = request.h   mbk_mailer.h 
EXTRA_DIST    = request.ddl
CLEANFILES    = request.dbd

pkginclude_HEADERS = mailerplugins.h

lib_LTLIBRARIES = libmegistos_mailerplugin.la
libmegistos_mailerplugin_la_LDFLAGS = @LDFLAGS@ -version-info @SOVERSION@
libmegistos_mailerplugin_la_SOURCES = \
	cksum.c \
	request.c \
	usr.c \
	xlate.c

PROGNAMES = mailer

mailer_SOURCES = \
	download.c \
	mailer.c \
	mailer.h \
	plugindef.c \
	setup.c \
	upload.c

include $(top_srcdir)/templates/module
include $(top_srcdir)/templates/typhoon

mailer_LDADD = $(LDADD) $(lib_LTLIBRARIES)


# End of file
