# Test our C callback module

from callback import *

def bar():
	print "I'm a python function"

my_set_callback(bar)           # Register the Python function with C
test()                         # Test the C function


