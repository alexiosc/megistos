# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.2  2003/12/27 12:45:15  alexios
# Added typhoon, clubhdr, and mailer plugin support, including all bells
# and whistles.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

SUBDIRS = . offline.bulletins

PROGNAMES = bulletins

BUILT_SOURCES = bltidx.h   mbk_bulletins.h 
EXTRA_DIST    = bltidx.ddl
CLEANFILES    = bltidx.dbd

bulletins_SOURCES = \
	autoins.c \
	bltidx.h \
	bulletins.c \
	bulletins.h \
	cleanup.c \
	clubs.c \
	db.c \
	delete.c \
	edit.c \
	insert.c \
	list.c \
	login.c \
	misc.c \
	read.c \
	search.c \
	substvars.c

#	bltcnv.c


include $(top_srcdir)/templates/module
include $(top_srcdir)/templates/typhoon
include $(top_srcdir)/templates/clubhdr

# End of file
