# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:53  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.2  2004/07/15 14:46:03  alexios
# Changed instances of CFLAGS to AM_CFLAGS so as not to override user
# settings.
#
# Revision 1.1  2004/02/29 16:32:19  alexios
# Initial revision.
#

PROGNAMES = msgd

msgd_SOURCES = \
	msgd.c \
	msgd.h \
	netmail.c \
	reindex.c \
	rfc822.c

include $(top_srcdir)/templates/daemon
#include $(top_srcdir)/templates/clubhdr
include $(top_srcdir)/templates/typhoon

# Stolen from templates/clubhdr
AM_CFLAGS += -I$(top_builddir)/src/modules/emailclubs

# End of file
