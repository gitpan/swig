/* File : example.i */
%module example
%{
/* Put headers and other declarations here */
%}

#ifdef ISH
%include ish.i
#endif
#ifdef IWISH
%include iwish.i
#endif
#ifdef ITCLSH
%include itclsh.i
#endif
#ifdef ITKWISH
%include itkwish.i
#endif

extern double My_variable;
extern int    fact(int);
extern int    mod(int n, int m);
extern char  *get_time();

