# Causes a index exception

from darray import *

d = DoubleArray(100)

print "\nPerforming an out-of-bounds array access...\n\n"
d[200] = 3.4

