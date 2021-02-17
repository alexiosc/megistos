# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:52 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:52  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.4  2004/02/29 16:58:26  alexios
# Moved the (rudimentary) BBS console to a subdirectory. It used some of
# the remsys code anyway.
#
# Revision 1.3  2003/12/27 12:58:27  alexios
# Moved some of the tools (namely, classed and eventman) from the old
# ADMIN subdirectory to this one. These modules are mostly called by
# remsys anyway.
#
# Revision 1.2  2003/12/24 21:53:45  alexios
# Moved the GCS into its own directory; added the msg file.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

SUBDIRS = . gcs_remsys classed eventman console

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
