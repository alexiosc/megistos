# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:52  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.2  2003/12/27 12:57:24  alexios
# Moved gcs_registry to its own directory to isolate its build infrastructure.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

SUBDIRS = . gcs_registry

PROGNAMES = registry

BUILT_SOURCES = mbk_registry.h

registry_SOURCES = \
	registry.c \
	registry.h

include $(top_srcdir)/templates/module

# End of file
