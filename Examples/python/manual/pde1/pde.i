%module pde
%{
#include "pde.h"
%}

%include pde.h
#ifdef STATIC
%include embed.i
#endif

