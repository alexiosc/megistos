# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.3  2003/12/27 12:43:25  alexios
# Yet more additions.
#
# Revision 1.2  2003/12/24 18:19:45  alexios
# Added more system-wide msg files. Started using the Automake template
# infrastructure to compile mbk files.
#
# Revision 1.1  2003/12/22 21:52:43  alexios
# Initial revision.
#

EXTRA_DIST = \
	mbk_archivers.h \
	mbk_emailclubs.h \
	mbk_login.h \
	mbk_mailer.h \
	mbk_menuman.h \
	mbk_metabbs-client.h \
	mbk_metabbs.h \
	mbk_signup.h \
	mbk_sysvar.h \
	mbk_updown.h

include $(top_srcdir)/templates/msg

all-local:	$(EXTRA_DIST)

.dep:
		/bin/sh ./mkdeps.sh >.deps

include .dep

# End of file.
