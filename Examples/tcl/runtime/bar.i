// A derived class

%module bar
%{
#include "bar.h"
%}

%import base.i         // Grab base class definitions
%include bar.h

