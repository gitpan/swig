// This example shows how you can hide the Tcl_Interp and ClientData
// variables using typemaps.

%module interp

typedef void *ClientData;
// Tell SWIG to simply grab interp from the wrapper code, not
// as an argument.

%typemap(tcl,ignore) Tcl_Interp * {
	$target = interp;
}

// Grab ClientData from the wrapper function as well

%typemap(tcl,ignore) ClientData {
	$target = clientData;
}

// Now a function to test this out		
%inline %{

void print_args(Tcl_Interp *interp, ClientData c, char *message) {
	printf("interp = %x, ClientData = %d, message = %s\n", interp, (int) c,
		message);
}
%}

	
