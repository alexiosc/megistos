# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:38  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.4  2004/02/29 18:30:17  alexios
# Added target to build and install all the msg files into the virgin instance.
#
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

install-data-local:
		for a in $(shell find ../src ../libmegistos -name '*msg' -a -type f); do \
			$(MSGIDX) $$a; \
			cp $$a ../virgin/etc/prompts; \
		done

include .dep

# End of file.
