# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:53 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:53  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.3  2004/02/29 12:46:15  alexios
# Switched to the 'module-like' template to avoid confusion with actual
# modules.
#
# Revision 1.2  2003/12/27 12:58:38  alexios
# Fixed msg support.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

PROGNAMES = stats

BUILT_SOURCES = mbk_stats.h

stats_SOURCES = \
	cleanup.c \
	stats.c \
	stats.h

include $(top_srcdir)/templates/module-like

# End of file
