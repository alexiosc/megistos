# $Id$
#
# $Log$
# Revision 1.6  2003/12/24 18:39:40  alexios
# Added mkb subdirectory.
#
# Revision 1.5  2003/09/30 15:14:30  alexios
# Updated SUBDIRS for new directory structure.
#
# Revision 1.4  2003/09/29 21:37:22  alexios
# Renamed src/ directory to lib/ to accommodate more source code in this
# tree.
#
# Revision 1.3  2003/09/28 22:23:24  alexios
# Added conditional generation of documentation.
#
# Revision 1.2  2003/09/28 13:15:08  alexios
# Added gettext support.
#
# Revision 1.1  2003/08/15 18:06:56  alexios
# Initial revision.
#

if HAVE_DOXYGEN
DOCDIR = doc
else !HAVE_DOXYGEN
DOCDIR = 
endif !HAVE_DOXYGEN

SUBDIRS = po intl m4 $(DOCDIR) libltdl libmegistos mbk src

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath autogen.sh
