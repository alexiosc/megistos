# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:51  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.1  2003/12/31 06:57:53  alexios
# Initial revision.
#

PROGNAMES = gsc

gsc_SOURCES = \
	analyze.c \
	compiler.c \
	glps-bcc.h \
	gsc.c \
	gsc.h \
	io-bcc.c \
	io.c

include $(top_srcdir)/templates/program
CFLAGS+=-I.. -D__GSC__

# End of file
