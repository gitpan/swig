from ignore import *

print "\nShould get (2,3,-1)..."
omit_last(2,3)

print "\nShould get (-1,3,4)..."
omit_first(3,4)

print "\nShould get (2,4,-1,5)..."
omit_opt(2)         # Rest of arguments are optional/ignored

f = Foo()

print "\nShould get (10,11,-1)"
f.omit_last(10,11)

print "\nShould get (-1,11,12)"
f.omit_first(11,12)

print "\nShould get (10,4,-1,5)"
f.omit_opt(10)


