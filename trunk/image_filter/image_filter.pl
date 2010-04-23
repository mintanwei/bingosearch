#!/usr/bin/perl

use strict;
use warnings;

my $file = "../data/query_list";
open QUERY, $file or die "FAIL TO OPEN $file";

while (<QUERY>) {
	chomp();
	my $real_id = 0;
	for (my $var = 0; $var < 1000; $var++) {
		$file = "../data/images/$_/$var";
		my $file2 = "../data/images/$_/real$real_id";
		if (-e "$file") {
			my $size = -s "$file";
			if ($size != 0) {
				rename("$file", "$file2");
				++ $real_id;
			}
			else {
				unlink("$file");
			}
		}
	}
	for (my $var = 0; $var < $real_id; $var++) {
		$file = "../data/images/$_/real$var";
		my $file2 = "../data/images/$_/$var";
		rename("$file", "$file2");
	}
}

close QUERY;
