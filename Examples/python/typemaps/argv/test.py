# This function passes a python list to a C function
# as a char **

from argv import *

print_args(["John","Guido","Larry"]);

# This function returns a char ** as a Tcl list

a = get_args();
print a

# This function extracts the value of a global variable

print cvar.args
