# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 2.0  2004/09/13 19:44:54  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.2  2003/12/23 08:20:57  alexios
# One minor fix.
#
# Revision 1.1  2003/12/22 22:35:19  alexios
# Initial revision.
#

SUBDIRS = . client server

PROGNAMES = rpc.metabbs

rpc_metabbs_SOURCES = \
	distclub.c \
	main.c \
	metabbs.h \
	metaservices.h \
	metaservices_clnt.c \
	metaservices_svc.c \
	metaservices_xdr.c \
	parallelism.h \
	register.c \
	register_non_megistos.c \
	request_ihave_list.c \
	request_info.c \
	request_message.c

EXTRA_DIST = metaservices.x

metaservices.h metaservices_clnt.c metaservices_svc.c metaservices_xdr.c: metaservices.x
	rpcgen $<

include $(top_srcdir)/templates/daemon

# End of file
