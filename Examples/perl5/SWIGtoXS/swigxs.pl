#!/usr/local/bin/perl5.003

use produce;
use consume;

print "Creating an double * array using a xsubpp function\n";
$a = produce::create(10);
produce::print_array($a,10);
print "\nNegating it with a SWIG function.\n";
$b = consume::negate($a,10);
produce::print_array($b,10);

