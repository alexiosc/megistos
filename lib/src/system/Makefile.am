# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:53  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.6  2004/05/22 19:28:33  alexios
# Added bbsdeluser.
#
# Revision 1.5  2004/05/21 20:14:32  alexios
# Added bbscleanup.
#
# Revision 1.4  2004/02/29 18:12:48  alexios
# Added the missing backslash that precluded some directories from being
# built.
#
# Revision 1.3  2003/12/25 18:19:20  alexios
# Added events subdirectory.
#
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
	bbscleanup \
	bbsdeluser \
	bbsgetty \
	bbslogin \
	bbslogout \
	daemons \
	events \
	menuman \
	$(METABBS) \
	protocols \
	signup

# End of file.
