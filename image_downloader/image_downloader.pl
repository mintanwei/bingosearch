#!/usr/bin/perl

use strict;
use warnings;

my $file = "../data/query_list";
open QUERY, $file or die "FAIL TO OPEN $file";

while (<QUERY>) {
    chomp(my $tmp = $_);
	print "$tmp\n";
    my $file = "../data/meta_data/$tmp";
    open IN, $file or die "FAIL TO OPEN $file";
    $file = "../data/images/$tmp";
    mkdir $file;
    my $cnt = 0;
    while (<IN>) {
        if ($cnt % 5) {
            ++ $cnt;
            next;
        }
        my $id = $cnt / 5;
        chomp(my $url = $_);
        my $file = "../data/images/$tmp/$id";
        system("wget '$url' -O $file -t 2 -T 16");
        ++$cnt;
    }
    close IN;
}

close QUERY;
