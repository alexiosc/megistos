# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.2  2003/12/27 13:00:06  alexios
# Compiled this by defining appropriate preprocessor symbols.
#
# Revision 1.1  2003/12/25 08:24:06  alexios
# Initial revision.
#

PROGNAMES = bjack

BUILT_SOURCES = mbk_bjack.h

bjack_SOURCES = \
	bjack.c \
	bjack.h \
	bjcmd.c \
	bjconf.h \
	bjglob.c \
	bjintrfc.c \
	bjintrfc.h \
	bjutil.c \
	bjver.h \
	cards.c \
	cards.h \
	wdog.c \
	wdog.h

include $(top_srcdir)/templates/teleconplugin

CFLAGS += -DMEGISTOS_BBS -DBBSPROMPTS

# End of file
