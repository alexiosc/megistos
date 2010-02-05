#!/usr/bin/perl -w

while (<>) {
    foreach $i (split /\033/) {
	next unless $i =~ /\[([0-9;]+m)/;
	print "$1\n";
    }
}
