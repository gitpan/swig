# Check out our multiple inheritance script
use inherit;

$d = new D;
$x = $d->{x};
$y = $d->{y};
$z = $d->{z};
$a = $d->{a};
$b = $d->{b};
$ptr = $d->{ptr};

print "x = $x  (should be 1.0)\n";
print "y = $y  (should be 2.0)\n";
print "z = $z  (should be 3.0)\n";
print "a = $a  (should be 7)\n";
print "b = $b  (should be 2.81828)\n";
print "ptr = $$ptr (should be 1234)\n";

print "Trying some member functions\n";
$d->foo();
$d->bar();
$d->grok();
print "Looks okay.\n";


