# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:50  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.3  2003/12/29 07:52:41  alexios
# Removed dump_ihave from the bbsmail objects and compiled it as a
# separate tool (which it was, anyway).
#
# Revision 1.2  2003/12/23 23:21:20  alexios
# Minor simplifications.
#
# Revision 1.1  2003/12/23 08:33:32  alexios
# Initial revision.
#

PROGNAMES = bbsmail dump-ihave

bbsmail_SOURCES = \
	bbsmail.c \
	bbsmail.h \
	bbsmail_run.c \
	database.c \
	msghdr.c \
	msgnum.c \
	netmail.c \
	resolve.c \
	utils.c

 #	test.c

include $(top_srcdir)/templates/program
include $(top_srcdir)/templates/typhoon

# End of file
