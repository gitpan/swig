use passref;

$a = 4;
$b = 5;
$c = 0;

passref::add(\$a,\$b,\$c);
print "Should get 9\n";
print $c,"\n";

passref::negate(\$c);
print "\nShould get -9\n";
print $c,"\n";




