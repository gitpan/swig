from darray import *

d = DoubleArray(1000)

print len(d)
for i in range(0,len(d)):
	d[i] = 0.25*i

sum = 0.0
for n in d:
	sum = sum + n

print "sum[0:1000] = ",sum

# Make a slice

sum = 0.0
for n in d[500:1000]:
	sum = sum + n

print "sum[500:1000] = ",sum

del d

