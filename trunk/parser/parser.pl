#!/usr/bin/perl

use strict;
use warnings;

my $file = "../data/query_list";
open QUERY, $file or die "FAIL TO OPEN $file";

while (<QUERY>) {
    chomp(my $tmp = $_);
    my $file = "../data/meta_data/$tmp";
    open OUTPUT, ">$file" or die "FAIL TO OPEN $file";
    foreach (0...49) {
        my $file = "../data/pages/$tmp/$_";
        open NOW, $file or die "FAIL TO OPEN $file";
        while (<NOW>) {
            while (/(\["\/imgres\?.*?""])/g) {
                my $tmp = $1;
                print "$tmp\n\n\n";
                # thumbnail
                if ($tmp =~ /" target\\x3d_blank","(.*?)".*?(http:\/\/t\d.gstatic.com\/images)/) {
                    print OUTPUT "$2?q=tbn:$1\n";
                }
				else {
					print "\n";
				}
                # img url
                if ($tmp =~ /imgurl\\x3d(.*?)\\x26/) {
                    print OUTPUT "$1\n";
                }
				else {
					print "\n";
				}
                # img ref url
                if ($tmp =~ /imgrefurl\\x3d(.*?)\\x26/) {
                    print OUTPUT "$1\n";
                }
				else {
					print "\n";
				}
                # size 
                if ($tmp =~ /" target\\x3d_blank",".*?",".*?","(.*?)","(.*?)"/) {
                    print OUTPUT "$1 $2 ";
                }
				else {
					print "\n";
				}
				# format
				if ($tmp =~ /times; \d*? - (\d*?k)","(.*?)"/) {
					print OUTPUT "$1\n$2\n";
				}
				else {
					print "\n";
				}
            }
        }
        close NOW;
    }
    close OUTPUT;
}

close QUERY;
