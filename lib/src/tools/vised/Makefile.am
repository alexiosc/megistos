# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:54  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.4  2004/02/29 12:46:14  alexios
# Switched to the 'module-like' template to avoid confusion with actual
# modules.
#
# Revision 1.3  2003/12/24 19:44:00  alexios
# Linked against curses; added message block.
#
# Revision 1.2  2003/12/23 23:21:20  alexios
# Minor simplifications.
#
# Revision 1.1  2003/12/23 08:33:32  alexios
# Initial revision.
#

PROGNAMES = vised

BUILT_SOURCES = mbk_vised.h

vised_SOURCES = \
	blocks.c \
	display.c \
	edit.c \
	exit.c \
	find.c \
	format.c \
	utils.c \
	vised.c \
	vised.h

include $(top_srcdir)/templates/module-like
include $(top_srcdir)/templates/curses

# End of file
