# Python script showing some output arguments

from retval import *
a = double_array(1)

# Power function with a status value

r = mypow(2,3)
print "pow(2,3) = ",r
r = mypow(-1,3)
print "pow(-1,3) = ",r

# Some output functions

r = multout(7,13)
print "multout 7 13 = ",r
r = multout1(7,13,a)
print "multout1 7 13 = ",r
r = multout2(7,13,a,a)
print "multout2 7 13 = ",r

# Check for memory leaks

#i = 0
#while i < 500000:
#      r = multout(i,i,None,None)
#      i = i + 1


