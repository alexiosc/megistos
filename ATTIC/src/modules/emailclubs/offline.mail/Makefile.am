# -*- Makefile -*-
#
# $Id: Makefile.am,v 2.0 2004/09/13 19:44:51 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.0  2004/09/13 19:44:51  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.2  2003/12/27 12:50:58  alexios
# Used the mailer plugin helper library.
#
# Revision 1.1  2003/12/25 08:24:06  alexios
# Initial revision.
#

PROGNAMES = offline.mail

BUILT_SOURCES = mbk_offline.mail.h

offline_mail_SOURCES = \
	attachments.c \
	clubid.c \
	controlmsg.c \
	download.c \
	funcs.c \
	offline.mail.c \
	offline.mail.h \
	qsc.c \
	qwkout.c \
	reqman.c \
	setup.c \
	upload.c

#	clubhdr.c


include $(top_srcdir)/templates/mailerplugin
include $(top_srcdir)/templates/clubhdr

# End of file
