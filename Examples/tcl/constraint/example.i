// This file demonstrates how to apply constraints to function
// arguments.  Relys upon the SWIG library file 'constraints.i'

%module example
%include constraints.i


%{
#include <math.h>
double inv(double x) {
	return 1.0/x;
}

int fact(int n) {
	if (n <= 1) return 1;
	else return n*fact(n-1);
}

void set_double(double *a, double v) {
	*a = v;
}

%}

// Now wrap a few functions from the math library

double exp(double);               // Accepts any value
double log(double POSITIVE);      // Only accepts positive values
double inv(double NONZERO);       // Only accepts nonzero values
double sqrt(double NONNEGATIVE);  // Accepts non-negative values

// This applies a constraint to a different argument name

%apply Number NONNEGATIVE { int n };

int fact(int n);         // int n will be nonnegative since we 
                         // applied NONNEGATIVE to it above.

// A few memory management functions

%apply Pointer NONNULL {void *};         // Make void * arguments check for NULL
%apply Number  POSITIVE {int size};      // Make size a positive integer

void *malloc(int size);
void free(void *);

%apply Pointer ALIGN8 {double *ptr};     // Forces ptr to be a 8-byte aligned pointer   

void set_double(double *ptr, double value);




