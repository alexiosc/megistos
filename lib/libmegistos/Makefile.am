# Process this file with automake to produce Makefile.in
#
# $Id$
#
# $Log$
# Revision 1.5  2003/09/28 22:26:52  alexios
# Added DEFS and fixed gcc command-line arguments.
#
# Revision 1.4  2003/08/15 20:40:04  alexios
# Fixed slight dependency bug.
#
# Revision 1.3  2003/08/15 20:25:15  alexios
# Added version.h to the list of distclean files. Added configure.in to
# its dependencies to ensure it's recreated when the version changes
# (among other reasons).
#
# Revision 1.2  2003/08/15 20:09:00  alexios
# Added enough information and variables for megistos-config.
#
# Revision 1.1  2003/08/15 18:05:34  alexios
# Initial revision.
#

pkgdatadir = @PKGDATADIR@
pkglibdir = @PKGLIBDIR@
pkgincludedir = @PKGINCLUDEDIR@

DEFS = @DEFS@

lib_LTLIBRARIES = libmegistos.la

HDR =						\
	audit.h					\
	bbs.h					\
	bbsmod.h				\
	bots.h					\
	channels.h				\
	config.h				\
	dialog.h				\
	errorprompts.h				\
	errors.h				\
	filexfer.h				\
	format.h				\
	globalcmd.h				\
	input.h					\
	lock.h					\
	mail.h					\
	menuman.h				\
	miscfx.h				\
	output.h				\
	prompts.h				\
	security.h				\
	sysstruct.h				\
	systemversion.h				\
	timedate.h				\
	ttynum.h				\
	useracc.h				\
	ver.h					\
	version.h

libmegistos_la_SOURCES =						    \
	audit.c channels.c format.c input.c output.c timedate.c		    \
	version.c bbsmod.c errors.c gcs_builtin.c lock.c prompts.c ttynum.c \
	bots.c filexfer.c globalcmd.c miscfx.c security.c useracc.c	    \
	$(HDR)

pkginclude_HEADERS = $(HDR)

noinst_HEADERS = mbk_sysvar.h

libmegistos_la_LDFLAGS = @LDFLAGS@ -version-info 3:5:1
libmegistos_la_CFLAGS = @CFLAGS@ -Wall

bin_SCRIPTS = megistos-config

DISTCLEANFILES = version.mk

version.mk \
version.h:	version.mk $(libmegistos_la_SOURCES) ../configure.in
		./mkversion.sh $(VERSION)
