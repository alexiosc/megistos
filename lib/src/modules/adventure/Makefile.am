# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.2  2003/12/24 20:30:57  alexios
# Fixed the makefile (adventure was really two binaries).
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

# Both of these are compiled with the `module' template. Although only
# adventure is an actual Megistos module, infoint also uses the very
# same infrastructure (minus the module declaration).

PROGNAMES = adventure infoint

BUILT_SOURCES = mbk_adventure.h

adventure_SOURCES = adventure.c

infoint_SOURCES = \
	control.c \
	extern.c \
	fileio.c \
	input.c \
	interpre.c \
	math.c \
	memory.c \
	object.c \
	operand.c \
	osdepend.c \
	property.c \
	screen.c \
	text.c \
	unixio.c \
	variable.c \
	zip.c \
	ztypes.h

include $(top_srcdir)/templates/module

# End of file
