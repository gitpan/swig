// A derived class

%module foo
%{
#include "foo.h"
%}

%import base.i         // Grab base class definitions
%include foo.h

