// 
// This example shows how you can easily manage input/output
// parameters as pointers using the SWIG library.

%module output

%include typemaps.i

// Make parameters 'a' and 'b' input parameters
%apply double *INPUT {double *a, double *b}; 

// Make 'result' an output parameter
%apply double *OUTPUT {double *result};

// Make 'x' and input/output parameter
%apply double *BOTH {double *x};

extern void add(double *a, double *b, double *result);
extern void sub(double *a, double *b, double *result);
extern void mul(double *a, double *b, double *result);
extern void fdiv(double *a, double *b, double *result);
extern void neg(double *x);

extern double modf(double, double *OUTPUT);
