# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:54 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:54  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.4  2004/02/29 12:46:15  alexios
# Switched to the 'module-like' template to avoid confusion with actual
# modules.
#
# Revision 1.3  2003/12/24 18:30:55  alexios
# Removed a '0' that sneaked past the previous checkin and wrecked this
# file; linked against the Curses library (or equivalent), using the
# 'curses' Automake template; added the message block file.
#
# Revision 1.2  2003/12/23 23:21:20  alexios
# Minor simplifications.
#
# Revision 1.1  2003/12/23 08:33:32  alexios
# Initial revision.
#

PROGNAMES = bbsdialog

BUILT_SOURCES = mbk_bbsdialog.h

bbsdialog_SOURCES = \
	bbsdialog.c \
	bbsdialog.h \
	blessed.c \
	cursed.c \
	help.c

include $(top_srcdir)/templates/module-like
include $(top_srcdir)/templates/curses

# End of file
