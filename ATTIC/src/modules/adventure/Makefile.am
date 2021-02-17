# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:49 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:49  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.3  2004/02/29 12:23:25  alexios
# Split into two subprojects; the module proper and the Infocom
# interpreter.
#
# Revision 1.2  2003/12/24 20:30:57  alexios
# Fixed the makefile (adventure was really two binaries).
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

# Both of these are compiled with the `module' template. Although only
# adventure is an actual Megistos module, infoint also uses the very
# same infrastructure (minus the module declaration).

SUBDIRS = infoint

PROGNAMES = adventure

BUILT_SOURCES = mbk_adventure.h

adventure_SOURCES = adventure.c

include $(top_srcdir)/templates/module

# End of file
