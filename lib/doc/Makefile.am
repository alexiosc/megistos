# Process this file with automake to produce Makefile.in
#
# $Id$
#
# $Log$
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

doc-stamp:	Doxyfile ../lib/*.[ch]
		$(DOXYGEN) Doxyfile && touch doc-stamp
