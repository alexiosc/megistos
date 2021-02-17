# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:51 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:51  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

SUBDIRS = gsc gstat

PROGNAMES = gallups

BUILT_SOURCES = mbk_gallups.h

gallups_SOURCES = \
	crc.c \
	crc.h \
	gallups.c \
	gallups.h \
	io.c

# The file below ends abruptly. Let's hope it's okay.
#	quiz.c

include $(top_srcdir)/templates/module

# End of file
