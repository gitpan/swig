/* File : example.i */
%module example
%{
/* Put headers and other declarations here */
%}

// Define a constrained function input

%typemap(tcl,check) int posint {
	if ($target < 0) {
	    interp->result = "Error. Positive integer required.\n";
	    return TCL_ERROR;
        }
}

extern int    fact(int posint);

