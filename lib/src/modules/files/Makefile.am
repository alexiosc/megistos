# -*- Makefile -*-
#
# $Id$
#
# $Log$
# Revision 1.2  2003/12/27 09:01:28  alexios
# Added mbk and typhoon rules; removed libcnv files.
#
# Revision 1.1  2003/12/24 20:11:27  alexios
# Initial revision.
#

PROGNAMES = files

BUILT_SOURCES = dbfile.h   dbkey.h   dblib.h   mbk_files.h 
EXTRA_DIST    = dbfile.ddl dbkey.ddl dblib.ddl 
CLEANFILES    = dbfile.dbd dbkey.dbd dblib.dbd

files_SOURCES = \
	access.c \
	cache.c \
	cleanup.c \
	dbfile.c \
	dbfile.h \
	dbkey.c \
	dbkey.h \
	dblib.c \
	dblib.h \
	download.c \
	filearray.c \
	fileops.c \
	files.c \
	files.h \
	list.c \
	misc.c \
	mklib.c \
	opaccess.c \
	opaddtree.c \
	opapprove.c \
	opcache.c \
	opcharges.c \
	opcopy.c \
	opcreate.c \
	opdel.c \
	opdelete.c \
	opdeltree.c \
	opdescr.c \
	opdisapp.c \
	opedit.c \
	operations.c \
	opfiles.c \
	opkeywords.c \
	oplibren.c \
	oplimits.c \
	opls.c \
	opmisc.c \
	opmove.c \
	opoptions.c \
	opunapp.c \
	search.c \
	select.c \
	sublib.c \
	substvars.c \
	upload.c

#	cnvutils.c \
#	cnvutils.h \
#	libfil.c \
#	libcnv.c \
#	libcnv.h \
#	libkey.c \
#	libsig.c


include $(top_srcdir)/templates/module
include $(top_srcdir)/templates/typhoon
include $(top_srcdir)/templates/clubhdr


# End of file
