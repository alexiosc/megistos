# $Id$
#
# $Log$
# Revision 1.2  2003/12/23 06:44:22  alexios
# Added conditional compilation of MetaBBS components.
#
# Revision 1.1  2003/09/30 15:02:25  alexios
# Initial revision.
#

if HAVE_METABBS
METABBS = metabbs
else !HAVE_METABBS
METABBS =
endif !HAVE_METABBS

SUBDIRS = \
	bbsgetty \
	bbslogin \
	bbslogout \
	daemons \
	menuman \
	$(METABBS)
	protocols \
	signup
