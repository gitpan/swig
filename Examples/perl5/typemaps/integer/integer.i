// This file shows how a typemap can be used to change the
// processing of a SWIG built-in type
//

%module itest

%typemap(perl5,in) int {
	$target = ($type) SvIV($source);
	printf("Received a ($type) = %d\n",$target);
}

// Copy the integer mapping to a few other types

%typemap(perl5,in) short = int;
%typemap(perl5,in) long = int;
%typemap(perl5,in) unsigned char = int;

// Now try it out in a few functions
		
%inline %{

int sumint(int a, int b) {
	return a+b;
}

short sumshort(short a, short b) {
	return a+b;
}

long sumlong(long a, long b) {
	return a+b;
}

unsigned char sumuchar(unsigned char a, unsigned char b) {
	return a+b;
}
%}
