/* File : example.i */
%init Example_Init
%{
/* Put headers and other declarations here */
%}

%include userinit.i

extern double My_variable;
extern int    fact(int);
extern int    mod(int n, int m);
extern char   *get_time();
