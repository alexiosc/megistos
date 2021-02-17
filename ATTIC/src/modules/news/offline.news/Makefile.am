# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:52 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:52  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.2  2003/12/27 12:56:43  alexios
# Moved from the mailer/plugins directory.
#
# Revision 1.1  2003/12/25 08:24:06  alexios
# Initial revision.
#

PROGNAMES = offline.news

BUILT_SOURCES = mbk_offline.news.h

offline_news_SOURCES = \
	download.c \
	offline.news.c \
	offline.news.h \
	setup.c

include $(top_srcdir)/templates/mailerplugin

# End of file
