# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.2  2003/12/27 12:46:19  alexios
# Moved from the mailer directory. Linked against ../db.o and
# clubhdr. Fixed issues created by megistos-config.
#
# Revision 1.1  2003/12/25 08:24:06  alexios
# Initial revision.
#

PROGNAMES = offline.bulletins

BUILT_SOURCES = mbk_offline.bulletins.h

offline_bulletins_SOURCES = \
	download.c \
	offline.bulletins.c \
	offline.bulletins.h \
	setup.c \
	upload.c

include $(top_srcdir)/templates/mailerplugin
include $(top_srcdir)/templates/clubhdr

LDADD += ../db.o

# End of file
