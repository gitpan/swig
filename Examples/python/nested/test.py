from nested import *

# Create a new nested object

n = new_value(0)

# Print out some values

print "n.dataType = ",n.dataType
print "n.u.intval = ",n.u.intval
print "n.u.doubleval = ",n.u.doubleval
print "n.u.ptrvalue = ",n.u.ptrvalue
print "n.u.longval = ",n.u.longval

# Now go one more level

print "n.u.v.i = ",n.u.v.i
print "n.u.v.f = ",n.u.v.f
print "n.u.v.v = ",n.u.v.v

# Use our set method on name
n.u.v.name = "SPAM"
print "n.u.v.name = ",n.u.v.name
