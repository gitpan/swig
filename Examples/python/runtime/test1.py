# Load up the modules (if available)

from base import *
from bar import *
from foo import *

print "If you have built everything correctly, this script should\n\
generate no errors.\n"

# The following should run without any type errors

b = Bar()
b.bar_method()
b.base_method()

f = Foo()
f.foo_method()
f.base_method()

