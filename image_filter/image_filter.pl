#!/usr/bin/perl

use strict;
use warnings;

my $file = "../data/query_list";
open QUERY, $file or die "FAIL TO OPEN $file";

while (<QUERY>) {
	chomp();
	my $real_id = 0;
	my $meta_data = "../data/meta_data/$_";
	open METADATA, "$meta_data" or die "FAIL TO OPEN $meta_data";
	open TMP, ">$meta_data"."_tmp" or die "FAIL TO OPEN $meta_data"."_tmp";
	for (my $var = 0; $var < 1000; $var++) {
		$file = "../data/images/$_/$var";
		my $file2 = "../data/images/$_/real$real_id";
		if (-e "$file") {
			my $size = -s "$file";
			if ($size != 0) {
				rename("$file", "$file2");
				for (my $var2 = 0; $var2 < 4; $var2++) {
					my $line = <METADATA>;
					print TMP "$line";
				}
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
	rename("$meta_data"."_tmp", "$meta_data");
	close TMP;
	close METADATA;
}

close QUERY;
