// This file shows how one can tell SWIG to remap a data-type and
// process it as a special case

%module argv

// This tells SWIG to treat char ** as a special case

%typemap(python,in) char ** {
	
  /* Check if is a list */
  if (PyList_Check($source)) {
    int size = PyList_Size($source);
    int i = 0;
    $target = (char **) malloc((size+1)*sizeof(char *));
    for (i = 0; i < size; i++) {
      PyObject *o = PyList_GetItem($source,i);
      if (PyString_Check(o))
	$target[i] = PyString_AsString(PyList_GetItem($source,i));
      else {
	PyErr_SetString(PyExc_TypeError,"list must contain strings");
	free($target);
	return NULL;
      }
    }
    $target[i] = 0;
  } else {
    PyErr_SetString(PyExc_TypeError,"not a list");
    return NULL;
  }
}

// This gives SWIG some cleanup code that will get inserted after the function call 

%typemap(python,freearg) char ** {
  free((char *) $source);
}

%typemap(python,out) char ** {
  int len,i;
  len = 0;
  while ($source[len]) len++;
  $target = PyList_New(len);
  for (i = 0; i < len; i++) {
    PyList_SetItem($target,i,PyString_FromString($source[i]));
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

/* Returns a char ** list  */

char **get_args() {
    static char *values[] = { "Dave", "Mike", "Susan", "John", "Michelle", 0};
    return &values[0];
}

char *args[] = { "123", "54", "-2", "0", "NULL", 0 };

%}
	
