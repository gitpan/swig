// This file shows how one can use typemaps to encode a return
// value.  This can be done using a naming convention rather
// that explicitly specifying output arguments in the interface
// file.

%module retval

// This tells SWIG to treat an double * argument with name 'outvalue' as
// an output value.  

%typemap(perl5,ignore) double *outvalue(double temp) {
	temp = 0.0;
	$target = &temp;
}
	
%typemap(perl5,argout) double *outvalue {
	$target = sv_newmortal();
	sv_setnv($target, *$source);
	argvi++;                     /* Increment return count */
}

// If we don't care what the input value, we can
// can make the typemap ignore it.

%typemap(perl5,in) double *outvalue {
	static double junk;  // Static needed so temporary variable doesn't disappear
	$target = &junk;
}

// Remap a return type of "Status" to strings instead of integers

%typemap(perl5,out) Status {
	$target = sv_newmortal();
	if (!$source)
	    sv_setpv((SV*)$target,"OK");
        else
            sv_setpv((SV*)$target,"ERROR");
	argvi++;
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

