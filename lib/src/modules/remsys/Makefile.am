# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.2  2003/12/24 21:53:45  alexios
# Moved the GCS into its own directory; added the msg file.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

SUBDIRS = . gcs_remsys

PROGNAMES = remsys

BUILT_SOURCES = mbk_remsys.h

remsys_SOURCES = \
	channels.c \
	classkey.c \
	filing.c \
	miscfuncs.c \
	remsys.c \
	remsys.h \
	statistics.c \
	users.c

include $(top_srcdir)/templates/module

# End of file
