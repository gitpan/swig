// 
// This example shows how you can easily manage input/output
// parameters as pointers using the SWIG typemaps.i library.

%module output

%include typemaps.i

// Make parameters 'a' and 'b' input parameters
%apply double *INPUT {double *a, double *b}; 

// Make 'result' a Perl reference parameter
%apply double *REFERENCE {double *result};

// Make 'x' a Perl reference parameter
%apply double *REFERENCE {double *x};

extern void add(double *a, double *b, double *result);
extern void sub(double *a, double *b, double *result);
extern void mul(double *a, double *b, double *result);
extern void fdiv(double *a, double *b, double *result);
extern void neg(double *x);

%apply int *REFERENCE {int *f1, int *f2};

extern void factor(int n, int *f1, int *f2);

