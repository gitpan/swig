// FILE : package.i
// See the SWIG users manual

%title "Matrix and vector package"
%init Package
%{
#include <math.h>
%}

%include userinit.i
%include matrix.i
%include vector.i

// Include the math library so we can get some random numbers and
// other stuff

%include math.i

extern double drand48();
