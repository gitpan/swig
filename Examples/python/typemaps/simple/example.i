/* File : example.i */
%module example

/* Just a simple test showing how you can remap a Python datatype */

%typemap(python,in) int {
	if (PyInt_Check($source)) {
		$target = ($type) PyInt_AsLong($source);
		printf("Received an integer %d\n",$target);
	} else {
		PyErr_SetString(PyExc_TypeError,"not an integer");
		return NULL;
        }
}

extern double My_variable;
extern int    fact(int);
extern int    mod(int n, int m);
extern char   *get_time();
