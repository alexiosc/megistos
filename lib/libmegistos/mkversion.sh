#!/bin/sh

# $Id$
#
# $Log$
# Revision 1.3  2003/08/15 18:12:38  alexios
# Modernised the script (only slightly).
#

v=$1
v1=`echo $v | cut -d. -f1`
v2=`echo $v | cut -d. -f2`
v3=`echo $v | cut -d. -f3`

if [ ! -e version.mk ]; then
    echo 0 >version.mk
fi

# Step the build number
ver=1
if [ -r version.mk ]; then
    ver=$[ `head -1 version.mk` + 1 ]
    oldv=`tail -1 version.mk`

    if [ "$oldv" != "$v" ]; then
	ver=1
    fi
fi
echo $ver >version.mk
echo $v >>version.mk

# Generate version.h
cat <<EOF >version.h
/* Automatically generated, do NOT edit. */
#define __MAJORVERSION "$v1"
#define __MINORVERSION "$v2"
#define __PATCHLEVEL   "$v3"
#define __COMPILED_BY  "`whoami`@`hostname`"
#define __MAKE_NUMBER  "$ver"
#define __DATE         "`date '+%Y-%m-%d %H:%m:%S %z'`"
EOF

# End of file.