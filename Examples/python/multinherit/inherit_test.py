from inherit import *

d = D()

print "x = ",d.x,"(should be 1.0)"
print "y = ",d.y,"(should be 2.0)"
print "z = ",d.z,"(should be 3.0)"
print "a = ",d.a,"(should be 7)"
print "b = ",d.b,"(should be 2.81828)"
print "ptr = ",d.ptr,"(should be _4d2_void_p)"
print "Trying some member functions";
d.foo()
d.bar()
d.grok()
print "Looks okay."

del d


