from carray import *

# Call our C function. Should return a list/tuple

a = add((1,2,3,4),(5,6,7,8),None)

print "This should be a list containing a tuple : ",a

b = new_double(16)

print "This should be a pointer : ",b

c = print2d(b)

# Check for memory leaks

#i = 0
#while i < 500000:
#	a = add((1,2,3,4),(5,6,7,8),None)
#	i = i + 1




