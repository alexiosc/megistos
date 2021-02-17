# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:54 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:54  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.6  2004/02/29 12:46:15  alexios
# Switched to the 'module-like' template to avoid confusion with actual
# modules.
#
# Revision 1.5  2003/12/23 08:00:06  alexios
# Renamed gcs to gcs_go for consistency.
#
# Revision 1.4  2003/12/23 07:35:16  alexios
# Split into subdirectories.
#
# Revision 1.3  2003/12/23 07:20:54  alexios
# One more slight modification to the template used.
#
# Revision 1.2  2003/12/23 07:11:33  alexios
# Modified to build the /go GCS as a shared object.
#
# Revision 1.1  2003/12/22 17:22:59  alexios
# Initial revision.
#

SUBDIRS = gcs_go mkmtree

PROGNAMES = menuman
menuman_SOURCES = menuman.c

include $(top_srcdir)/templates/module-like

# End of file
