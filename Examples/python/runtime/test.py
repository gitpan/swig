# Load up the modules (if available)

from base import *
from bar import *
from foo import *

print "If you have built everything correctly, this script should\n\
generate no errors.\n"

# The following should run without any type errors

b = new_Bar()
Bar_bar_method(b)
Base_base_method(b)

f = new_Foo()
Foo_foo_method(f)
Base_base_method(f)

