#!/usr/bin/perl

$file = "../data/query_list";
$tmp_file = "../data/query_list_tmp";

open IN, $file or die "FAIL TO OPEN FILE $file";
open TMP, ">$tmp_file" or die "FAIL TO OPEN FILE $tmp_file";

while (<IN>) {
	print TMP lc;
}
rename($tmp_file, $file);

close TMP;
close IN;
