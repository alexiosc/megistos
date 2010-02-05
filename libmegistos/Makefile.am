# Process this file with automake to produce Makefile.in
#
# $Id: Makefile.am,v 2.1 2004/12/05 12:27:52 alexios Exp $
#
# $Log: Makefile.am,v $
# Revision 2.1  2004/12/05 12:27:52  alexios
# Removed a minor dependence on the Debian build infrastructure.
#
# Revision 2.0  2004/09/13 19:44:34  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.13  2004/02/29 17:00:20  alexios
# Moved the gcs_builtin code to a subdirectory, so it can compile as a
# shared object. This allows other global command servers to override
# its commands, if necessary.
#
# Revision 1.12  2004/02/22 18:54:14  alexios
# Moved msgidx and mksysvar to the right place, under
# ${prefix}/lib/megistos/bin.
#
# Revision 1.11  2003/12/27 12:44:03  alexios
# Moved the shared object versioning info to configure.in, using the
# SOVERSION Autoconf variable instead.
#
# Revision 1.10  2003/12/20 18:20:22  alexios
# Added the mbk_*h files to the cleaned file list. Minor dependency fixes.
#
# Revision 1.9  2003/12/20 10:18:56  alexios
# Added more MSG files needed to build the base system.
#
# Revision 1.8  2003/12/19 13:22:17  alexios
# Numerous changes to incorporate new scripts and the inclusion of
# msgidx and mksysvar into this directory (they are both needed to
# bootstrap the library build).
#
# Revision 1.7  2003/09/30 15:07:50  alexios
# Added megistos-config and its manpage to the distribution.
#
# Revision 1.6  2003/09/29 21:38:01  alexios
# Renamed src/ directory to lib/ to accommodate more source code in this
# tree.
#
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

MSGIDX = VIRGINDIR=`/bin/sh ./megistos-config --virgin-src` ./msgidx
pkgdatadir = @PKGDATADIR@
pkglibdir = @PKGLIBDIR@
pkgincludedir = @PKGINCLUDEDIR@

SUBDIRS = . gcs_builtin

# The Megistos library

DEFS = @DEFS@ -DLOCALEDIR=\"@LOCALEDIR@\"

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
	version.h				\
	../bbsconfig.h

libmegistos_la_SOURCES =						    \
	audit.c channels.c format.c input.c output.c timedate.c		    \
	version.c bbsmod.c errors.c lock.c prompts.c ttynum.c \
	bots.c filexfer.c globalcmd.c miscfx.c security.c useracc.c	    \
	$(HDR)

pkginclude_HEADERS = $(HDR)

noinst_HEADERS = mbk_sysvar.h mbk_metabbs.h mbk_signup.h
CLEANFILES     = mbk_sysvar.h mbk_metabbs.h mbk_signup.h

libmegistos_la_LDFLAGS = @LDFLAGS@ -version-info @SOVERSION@
libmegistos_la_CFLAGS = @CFLAGS@ -Wall


# Scripts

bin_SCRIPTS = megistos-config
man_MANS = megistos-config.1


# Versioning

DISTCLEANFILES = version.mk

EXTRA_DIST = mkversion.sh sysvar.msg

version.h version.mk:	$(filter-out $(libmegistos_la_SOURCES),version.h) ../stamp-h1 megistos-config mkversion.sh
			./mkversion.sh $(VERSION)
			touch version.c

# Build bootstrap programs 

megistosbindir = $(pkglibdir)/bin
megistosbin_PROGRAMS = msgidx mksysvar
mksysvar_LDADD = -lmegistos


# Compile base msgs

sysvar.mbk mbk_sysvar.h:	megistos-config msgidx sysvar.msg
				$(MSGIDX) sysvar.msg

mbk_%.h:			%.msg
				$(MSGIDX) $<

# End of file
