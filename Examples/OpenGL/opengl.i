%module opengl

// Grab a typemap for Tcl mode

%include typemap.i

// Remap a few datatypes that will appear in other files

%typemap(tcl,in) GLenum, GLbitfield = int;
%typemap(tcl,const) GLenum, GLbitfield = int;

%include gl.i
%include glu.i
%include help.i
%include glaux.i
%include carray.i
