# $Id$
#
# $Log$
# Revision 1.1  2003/09/30 14:53:05  alexios
# Initial revision.
#

pkgdatadir = @PKGDATADIR@
pkglibdir = @PKGLIBDIR@
pkgincludedir = @PKGINCLUDEDIR@

DEFS = @DEFS@
CFLAGS = @CFLAGS@ -I $(top_srcdir)/@LIBMEGISTOS@
LDFLAGS = -L$(top_srcdir)/@LIBMEGISTOS@ @LDFLAGS@

bin_PROGRAMS = bbsinit
bbsinit_SOURCES = bbsinit.c
bbsinit_LDADD = -lmegistos
