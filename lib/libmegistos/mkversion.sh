#!/bin/sh

 #############################################################################
 ##                                                                         ##
 ##  FILE:     mkversion.sh                                                 ##
 ##  AUTHORS:  Alexios                                                      ##
 ##  PURPOSE:  Create the version.h file.                                   ##
 ##  NOTES:                                                                 ##
 ##  LEGALESE:                                                              ##
 ##                                                                         ##
 ##  This program is free software; you  can redistribute it and/or modify  ##
 ##  it under the terms of the GNU  General Public License as published by  ##
 ##  the Free Software Foundation; either version 2 of the License, or (at  ##
 ##  your option) any later version.                                        ##
 ##                                                                         ##
 ##  This program is distributed  in the hope  that it will be useful, but  ##
 ##  WITHOUT    ANY WARRANTY;   without  even  the    implied warranty  of  ##
 ##  MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.   See the GNU  ##
 ##  General Public License for more details.                               ##
 ##                                                                         ##
 ##  You  should have received a copy   of the GNU  General Public License  ##
 ##  along with    this program;  if   not, write  to  the   Free Software  ##
 ##  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              ##
 #############################################################################

# $Id$
#
# $Log$
# Revision 1.4  2003/12/19 13:27:42  alexios
# Added conditional (include-once) directives to the header file output
# by the script. Added banner and test harness. Also included build
# directory structure (thanks to megistos-config).
#
# Revision 1.3  2003/08/15 18:12:38  alexios
# Modernised the script (only slightly).
#

# Uncomment this for testing (does not increment build counter)
#test=1

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
    [ x$test = x ] && ver=$[ `head -1 version.mk` + 1 ]
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
#ifndef __VERSION_H
#define __VERSION_H

#define __MAJORVERSION "$v1"
#define __MINORVERSION "$v2"
#define __PATCHLEVEL   "$v3"
#define __COMPILED_BY  "`whoami`@`hostname`"
#define __MAKE_NUMBER  "$ver"
#define __DATE         "`date '+%Y-%m-%d %H:%m:%S %z'`"
`/bin/sh ./megistos-config --header`
#endif /* __VERSION_H */
EOF

echo 

# End of file.