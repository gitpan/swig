# Test some out some of our math functions

use example;

print example::exp(-2.5),"\n";
print example::log(2),"\n";
print example::inv(0.25),"\n";
print example::sqrt(0),"\n";

# Now generate an exception

print "This will generate an error.";

print example::log(0);

