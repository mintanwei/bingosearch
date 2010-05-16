#!/usr/bin/perl

&move("data/index/", "front_end/index/");
&move("data/index_sift/", "front_end/index_sift/");
&move_dir("data/images/", "front_end/images/");

sub move
{
	$from_dir = $_[0];
	$to_dir = $_[1];
	$file = "data/query_list";
	open QUERY, $file or die "FAIL TO OPEN $file";
	while (<QUERY>) {
		chomp;
		print "sudo cp $from_dir$_ $to_dir$_\n";
		system("sudo cp $from_dir$_ $to_dir$_");
	}
	close QUERY;
}

sub move_dir
{
	$from_dir = $_[0];
	$to_dir = $_[1];
	$file = "data/query_list";
	open QUERY, $file or die "FAIL TO OPEN $file";
	while (<QUERY>) {
		chomp;
		print "sudo rm -r $to_dir$_";
		print "sudo cp -r $from_dir$_ $to_dir$_\n";
		system("sudo rm -r $to_dir$_");
		system("sudo cp -r $from_dir$_ $to_dir$_");
	}
}

