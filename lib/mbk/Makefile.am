# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.1  2003/12/22 21:52:43  alexios
# Initial revision.
#

EXTRA_DIST = \
	mbk_login.h \
	mbk_menuman.h \
	mbk_metabbs.h \
	mbk_signup.h \
	mbk_sysvar.h

MEGISTOS_CONFIG=@top_builddir@/libmegistos/megistos-config
MSGIDX = VIRGINDIR=`/bin/sh $(MEGISTOS_CONFIG) --virgin-src` ../libmegistos/msgidx

all-local:	$(EXTRA_DIST)

# Generate msg dependencies

.dep:

# Compile msgs

#mbk_%.mbk:			%.msg
#				$(MSGIDX) $<


include .dep

# End of file.
