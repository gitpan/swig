/* File : example.i */
%module Example
%{

/* This definition is always needed for building plug-in modules */

#define SAFE_SWIG

/* Put headers and other declarations here */
%}

extern double My_variable;
extern int    fact(int);
extern int    mod(int n, int m);
extern char  *get_time();
