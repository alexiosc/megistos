#!/bin/sh
#
# $Id$
#
# $Log$
# Revision 1.2  2003/09/28 13:14:56  alexios
# Added autopoint support and generalised for arbitrary versions of GNU
# automake and autoconf.
#
# Revision 1.1  2003/08/15 18:06:56  alexios
# Initial revision.
#

# Partially (and shamelessly) stolen from XMMS

# Automake version. Do NOT remove the dash
amver=-1.6
# Autoconf version. No dash here.
acver=2.50


echo We will use GNU automake $amver and GNU autoconf $acver. Change $0
echo to select different versions.

(automake${amver} --version) < /dev/null > /dev/null 2>&1 || {
	echo;
	echo "You must have automake${amver} installed";
	echo;
	exit;
}

(autoconf${acver} --version) < /dev/null > /dev/null 2>&1 || {
	echo;
	echo "You must have autoconf${acver} installed";
	echo;
	exit;
}

echo "Generating configuration files, please wait...."
echo;

autopoint
aclocal${amver} $ACLOCAL_FLAGS -I m4
autoheader${acver};
automake${amver} --add-missing;
autoconf${acver};

echo "Running configure $@"
echo;

./configure $@
