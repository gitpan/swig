// This is the same as the argv example except we are
// returning a char ** as a comma separated string instead
//

%module argv

// This tells SWIG to treat char ** as a special case

%typemap(perl5,in) char ** {
	AV *tempav;
	I32 len;
	int i;
	SV  **tv;

	if (!SvROK($source))
	    croak("$source is not an array.");
        if (SvTYPE(SvRV($source)) != SVt_PVAV)
	    croak("$source is not an array.");
        tempav = (AV*)SvRV($source);
	len = av_len(tempav);
	$target = (char **) malloc((len+2)*sizeof(char *));
	for (i = 0; i <= len; i++) {
	    tv = av_fetch(tempav, i, 0);	
	    $target[i] = (char *) SvPV(*tv,na);
        }
	$target[i] = 0;
};

// This cleans up our char ** array after the function call

%typemap(perl5,freearg) char ** {
	free($source);
}

// Creates a new Perl string containing values of a char **

%typemap(perl5,out) char ** {
	int i = 0;
	$target = sv_newmortal();
	sv_setpv((SV *) $target,"");
	while ($source[i]) {
	   sv_catpv((SV *) $target,$source[i]);
	   sv_catpv((SV *) $target,",");
           i++;
        }
	argvi++;
}

		
%inline %{

int print_args(char **argv) {
    int i = 0;
    while (argv[i]) {
         printf("argv[%d] = %s\n", i,argv[i]);
         i++;
    }
    return i;
}

/* Returns a char ** list  */

char **get_args() {
    static char *values[] = { "Dave", "Mike", "Susan", "John", "Michelle", 0};
    return &values[0];
}

%}
