/* File : example.i */
%module example
%{
/* Put headers and other declarations here */
%}


extern double My_variable;
extern int    fact(int);
%name(mod) extern int    my_mod(int n, int m);
extern char   *get_time();

#define FOO 32
#define BAR 42
#define PI  3.14159

%name(newname) %new char *foobar(long);




