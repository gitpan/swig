/* This file shows how constants can be turned into a hash table */

%module example

%{
double darray[100];
%}

%include consthash.i

#define      FOO      42
#define      PI4      0.78539815
#define      STR      "Hello world"
const double *dptr = darray;

%inline %{
void printi(int a) {
	printf("%d\n",a);
}
void printd(double d) {
        printf("%g\n",d);
}
void prints(char *s) {
        printf("%s\n",s);
}
%}
