# $Id$
#
# $Log$
# Revision 1.1  2003/12/14 18:45:36  alexios
# Initial revision.
#


pkgdatadir = @PKGDATADIR@
pkglibdir = @PKGLIBDIR@
pkgincludedir = @PKGINCLUDEDIR@

DEFS = @DEFS@
CFLAGS = @CFLAGS@ \
	-I $(top_srcdir)/@LIBMEGISTOS@ \
	-I GLOBAL_INCLUDE_DIR=\"@PKGINCLUDEDIR\"
LDFLAGS = -L$(top_srcdir)/@LIBMEGISTOS@ @LDFLAGS@

bin_PROGRAMS = msgidx

bbsd_LDADD = -lmegistos
