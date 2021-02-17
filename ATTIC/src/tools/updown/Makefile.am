# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:54 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:54  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.4  2004/02/29 12:46:14  alexios
# Switched to the 'module-like' template to avoid confusion with actual
# modules.
#
# Revision 1.3  2003/12/25 13:37:32  alexios
# Added BUILT_SOURCES for the two message blocks.
#
# Revision 1.2  2003/12/23 23:21:20  alexios
# Minor simplifications.
#
# Revision 1.1  2003/12/23 08:33:32  alexios
# Initial revision.
#

PROGNAMES = updown

BUILT_SOURCES = mbk_updown.h mbk_archivers.h

updown_SOURCES = \
	download.c \
	parse.c \
	protocols.c \
	updown.c \
	updown.h \
	upload.c

include $(top_srcdir)/templates/module-like

# End of file
