// This file shows how one can tell SWIG to remap a data-type and
// process it as a special case

%module argv

// This tells SWIG to treat char ** as a special case

%typemap(tcl,in) char ** {
	int tempc;
	if (Tcl_SplitList(interp,$source,&tempc,&$target) == TCL_ERROR) return TCL_ERROR;
}

// This gives SWIG some cleanup code that will get inserted after the function call 

%typemap(tcl,freearg) char ** {
	free((char *) $source);
}

// Return a char ** as a Tcl list

%typemap(tcl,out) char ** {
	int i = 0;
	while ($source[i]) {
	     Tcl_AppendElement(interp,$source[i]);
	     i++;
        }
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

/* Returns a char ** list */

char **get_args() {
    static char *values[] = { "Dave", "Mike", "Susan", "John", "Michelle", 0};
    return &values[0];
}

char *args[] = { "123", "54", "-2", "0", "NULL", 0 };

%}


	