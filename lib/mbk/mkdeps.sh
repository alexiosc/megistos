#!/bin/sh

# $Id$
#
# $Log$
# Revision 1.1  2003/12/22 21:52:07  alexios
# Initial revision.
#

(
    for a in `find ../src ../libmegistos -name '*msg' -a -type f`; do
	echo -e `basename $a | sed 's/^\(.*\)\.msg$/mbk_\1.h $(MBKDIR)\/\1.msg/'`": "$a"\n\t\$(MSGIDX) $<\n"
    done
) >.dep
