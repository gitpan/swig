# Load up the modules (if available)

print "If you have built everything correctly, this script should
generate no errors.\n\n";

use base;
use foo;
use bar;

# The following should run without any type errors

$b = bar::new_Bar();
bar::Bar_bar_method($b);
base::Base_base_method($b);

$f = foo::new_Foo();
foo::Foo_foo_method($f);
base::Base_base_method($f);
