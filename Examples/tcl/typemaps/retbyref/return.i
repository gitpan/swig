// This file shows how you can use a typemap to return an argument
// value in a Tcl variable.   The name of the variable is passed
// and we set its value.

%module return

// This tells SWIG to treat an double * argument with name 'outvalue' as
// an output value.  We'll return the value in a variable name that is
// provided as an argument.

%typemap(tcl,argout) double *outvalue {
	char dtemp[TCL_DOUBLE_SPACE];
	Tcl_PrintDouble(interp,*($source),dtemp);
	Tcl_SetVar(interp,$arg,dtemp,0);
}

// This tells SWIG how to handle double * for Tcl8

%typemap(tcl8,argout) double *outvalue {
	char dtemp[TCL_DOUBLE_SPACE];
	Tcl_PrintDouble(interp,*($source),dtemp);
	Tcl_SetVar(interp,$arg,dtemp,0);
}

// If we don't care what the input value, we can
// can make the typemap ignore it.

%typemap(tcl,in) double *outvalue(double junk) {
	$target = &junk;
}
// Tcl8 version
%typemap(tcl8,in) double *outvalue(double junk) {
	$target = &junk;
}

// Remap a return type of "Status" to strings instead of integers

%typemap(tcl,out) Status {
	if (!$source) $target = "OK";
	else $target = "ERROR";
}

// Tcl 8.0 Version

%typemap(tcl8,out) Status {
	if (!$source) Tcl_SetStringObj($target,"OK",-1);
	else Tcl_SetStringObj($target,"ERROR",-1);
}

%inline %{

#include <math.h>
/* This function should return both a status value and the result */

typedef int Status;

Status mypow(double a, double b, double *outvalue) {
	if ((a < 0) || (b < 0)) return -1;
	*outvalue = pow(a,b);
	return 0;
};

%}

%{

/* Returns two output values of same type */

int multout(double a, double b, double *out1, double *out2) {
	*out1 = a;
	*out2 = b;
	return 0;
};

%}

// If we name both parameters outvalue both will be output

int multout(double a, double b, double *outvalue, double *outvalue);

// If we name one parameter outvalue, only that one will be output.
// The other one must be a pointer.

%name(multout1) int multout(double a, double b, double *outvalue, double *out2);

// If we don't use outvalue, then no arguments are output
// Both must be pointers.

%name(multout2) int multout(double a, double b, double *out1, double *out2);

%include array.i

