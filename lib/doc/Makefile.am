# Process this file with automake to produce Makefile.in
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:29  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.4  2004/02/29 16:42:05  alexios
# Fixed the source directory.
#
# Revision 1.3  2003/09/30 15:24:17  alexios
# Hacked dependencies to exclude version.h, which is regenerated every
# build. This caused the API documentation to rebuild every time the
# system is recompiled, regardless of whether the rest of the source has
# changed.
#
# Revision 1.2  2003/09/29 21:37:49  alexios
# Renamed src/ directory to lib/ to accommodate more source code in this
# tree.
#
# Revision 1.1  2003/09/28 22:24:56  alexios
# Initial revision.
#

EXTRA_DIST = Doxyfile examples html man

DISTCLEANFILES = warnings.log

noinst_DATA = doc-stamp

doc-stamp:	Doxyfile $(shell ls ../libmegistos/*.[ch] | fgrep -v version.h)
		$(DOXYGEN) Doxyfile && touch doc-stamp
