# $Id$
#
# $Log$
# Revision 1.2  2003/12/25 18:19:41  alexios
# Netclub now compiles conditionally (on HAVE_METABBS).
#
# Revision 1.1  2003/12/23 08:32:26  alexios
# Initial revision.
#

if HAVE_METABBS
METABBS = netclub
else !HAVE_METABBS
METABBS =
endif !HAVE_METABBS

SUBDIRS = \
	bbsdialog \
	bbsmail \
	checksup \
	lined \
	$(METABBS) \
	updown \
	vised
