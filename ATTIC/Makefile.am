# $Id: Makefile.am,v 2.0 2004/09/13 19:44:25 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:25  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.8  2004/05/21 20:14:57  alexios
# Excluded .cvsignore from the virgin instance to comply with lintian(1).
#
# Revision 1.7  2004/05/03 05:24:59  alexios
# Added code to install the virgin instance, even its empty directories
# (which Debian leaves out by default).
#
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

#SUBDIRS = po intl m4 $(DOCDIR) libltdl libmegistos mbk src
SUBDIRS = po intl $(DOCDIR) libltdl libmegistos mbk src

# ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath autogen.sh

install-data-local:
	-mkdir $(DESTDIR)$(VIRGININSTANCE)
	(cd virgin; for a in `find . -type d -and -not -name CVS`; do touch $$a/.remove-before-flight; done)
	(cd virgin; tar --exclude CVS -cf - .) | (cd $(DESTDIR)$(VIRGININSTANCE); umask 000; tar --exclude .cvsignore -xvf -)
	find $(DESTDIR)$(pkglibdir)/gcs/* -not -name 'libgcs[0-9][0-9]_*.so.[0-9].*' -print | xargs rm
