// This file tests the "ignore" typemap.  This can be used to set a
// a default argument, but not have it show up in an interface.

%module ignore

%typemap(python,ignore) int OMIT {
	$target = -1;
}

%pragma make_default

%inline %{

void omit_last(int a, int b, int OMIT) {
	printf("Received : %d, %d, %d\n", a,b,OMIT);
}
void omit_first(int OMIT, int b, int c) {
	printf("Received : %d, %d, %d\n", OMIT,b,c);
}

void omit_opt(int a, int b = 4, int OMIT = 0, int c = 5) {
	printf("Received : %d, %d, %d, %d\n", a,b,OMIT,c);	
}

class Foo {
public:

void omit_last(int a, int b, int OMIT) {
	printf("Received : %d, %d, %d\n", a,b,OMIT);
}
void omit_first(int OMIT, int b, int c) {
	printf("Received : %d, %d, %d\n", OMIT,b,c);
}
void omit_opt(int a, int b = 4, int OMIT = 0, int c = 5) {
	printf("Received : %d, %d, %d, %d\n", a,b,OMIT,c);	
}
};

%}
	
