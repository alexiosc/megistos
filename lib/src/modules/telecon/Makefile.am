# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:53  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.4  2004/07/15 14:47:00  alexios
# Changed instances of CFLAGS to AM_CFLAGS so as not to override user
# settings.
#
# Revision 1.3  2003/12/29 07:54:09  alexios
# Included the typhoon template. It's necessary to link against clubhdr.
#
# Revision 1.2  2003/12/25 18:10:07  alexios
# Split off much of the telecon functionality into a shared/convenience
# library to be used by teleconference plugins (and, of course, this
# module). Made use of the libmegistos_clubhdr convenience library
# exported by emailclubs.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

SUBDIRS = mkaction mkplugin . plugins

PROGNAMES = telecon

lib_LTLIBRARIES = libmegistos_teleconplugin.la
libmegistos_teleconplugin_la_LDFLAGS = @LDFLAGS@ -version-info @SOVERSION@
libmegistos_teleconplugin_la_SOURCES = \
	accesses.c \
	broadcast.c \
	channel.c \
	chanusr.c \
	init.c \
	misc.c \
	plugins.c \
	scan.c \
	usr.c \
	utils.c

BUILT_SOURCES = mbk_telecon.h

pkginclude_HEADERS = \
	telecon.h \
	teleconplugins.h

telecon_SOURCES = \
	actions.c \
	actions.h \
	chat.c \
	editprefs.c \
	invitations.c \
	substvars.c \
	talk.c \
	telecon.c

include $(top_srcdir)/templates/module
include $(top_srcdir)/templates/typhoon
include $(top_srcdir)/templates/clubhdr

AM_CFLAGS += -I../emailclubs

telecon_LDADD = $(LDADD) libmegistos_teleconplugin.la

# End of file
