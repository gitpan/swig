%module consume
%{

double *negate(double *a, int nitems) {
    double *b;
    int i;
    
    b = (double *) malloc(nitems*sizeof(double));
    for (i = 0; i < nitems; i++)
	b[i] = -a[i];
    return b;
}

%}

double *negate(double *a, int nitems);

	
