# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.3  2003/12/23 07:20:54  alexios
# One more slight modification to the template used.
#
# Revision 1.2  2003/12/23 07:11:33  alexios
# Modified to build the /go GCS as a shared object.
#
# Revision 1.1  2003/12/22 17:22:59  alexios
# Initial revision.
#

PROGNAMES = menuman
menuman_SOURCES = menuman.c

GCS = libgcs_go.la
libgcs_go_la_SOURCES = gcs_go.c

include $(top_srcdir)/templates/module-with-gcs

# End of file
