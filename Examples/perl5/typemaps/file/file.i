// This file shows how you can take a Perl FILE handle and pass it in
// as a C FILE *

%module fileout

%typemap(perl5,in) FILE * {
	$target = IoIFP(sv_2io($source));
}
		
%inline %{

void print_count(FILE *f, int n) {
    int i;
    for (i = 0; i < n; i++) {
	fprintf(f,"%d\n",i);
    }
}

%}

