# Load up the modules (if available)

print "If you have built everything correctly, this script should
generate no errors.\n\n";

use base;
use foo;
use bar;

# The following should run without any type errors

$b = new Bar;
$b->bar_method();
$b->base_method();

$f = new Foo;
$f->foo_method();
$f->base_method();
