from arraymember import *

# Create a struct foo

f = bar(20)

# Now go set some array values

for i in range(0,f.a):
	f.b[i] = 4*i

# Now print out the array values

for i in range(0,f.a):
	print "f.b[%d] = %d" % (i, f.b[i])



