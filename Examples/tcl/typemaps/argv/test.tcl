# This function passes a Tcl list to a C function
# as a char **

catch {load ./argv.so argv}
catch {load ./argv.dll argv}

print_args {John Guido Larry}

# This function returns a char ** as a Tcl list

puts [get_args]

# This function extracts the value of a global variable

puts [args_get]
