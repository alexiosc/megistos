#!/bin/sh

status='*** '"$*"' ***'

tput rev
echo -e '\n'$status'\n'
tput sgr0
