# Pass a message to a function.  Tcl_Interp * and clientData are passed
# implicitly.

catch {load ./interp.so interp}
catch {load ./interp.dll interp}

print_args {Hello World}






