#!/bin/sh

# $Id: mkdeps.sh,v 2.0 2004/09/13 19:44:39 alexios Exp $
#
# $Log: mkdeps.sh,v $
# Revision 2.0  2004/09/13 19:44:39  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.2  2004/02/29 18:31:09  alexios
# Rewrote yet again for the new infrastructure.
#
# Revision 1.1  2003/12/22 21:52:07  alexios
# Initial revision.
#

for a in `find ../src ../libmegistos -name '*msg' -a -type f`; do
    echo -e `basename $a | sed 's/^\(.*\)\.msg$/mbk_\1.h $(MBKDIR)\/\1.msg/'`": "$a"\n\t\$(MSGIDX) $<\n"
done

#echo -n "ALL_HEADERS= "
#for a in `find ../src ../libmegistos -name '*msg' -a -type f`; do
#    echo -ne '\\\n\t'`basename $a | sed 's/^\(.*\)\.msg$/mbk_\1.h/'`" "
#done
#echo
