# Pointer example

use example;

# Allocate some memory
print "Allocating memory...\n";
$a = example::malloc(20000);
print $a,"\n";
print "Freeing memory...\n";
example::free($a);
print "Done.\n\n";

print "Generating NULL pointer...\n";
$a = undef;
print "This will generate an error\n";
print "Freeing memory...\n";
example::free($a);


