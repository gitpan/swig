# Pointer example

from example import *

# Allocate some memory
print "Allocating memory..."
a = malloc(20000)
print a
print "Freeing memory..."
free(a)
print "Done.\n"

print "Generating NULL pointer..."
a = "NULL"
print a
print "This will generate an error"
print "Freeing memory..."
free(a)
