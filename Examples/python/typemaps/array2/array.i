%module carray

// Test out a bunch of different typemaps related to different types of
// "double *" datatypes

// Generic handling of 4 element arrays 

%typemap(python,in) double[4] {
  static double temp[4];
  int i;

  if (PyTuple_Check($source)) {
	if (!PyArg_ParseTuple($source,"dddd",temp,temp+1,temp+2,temp+3)) {
	      PyErr_SetString(PyExc_TypeError,"tuple must have 4 elements");
      	      return NULL;
    }
    $target = &temp[0];
  } else {
    PyErr_SetString(PyExc_TypeError,"expected a tuple.");
    return NULL;
  }
}

// Special handling for output arrays, do nothing with this argument,
// but make sure there is some temporary storage set aside for the result

%typemap(python,in) double out[4] {
  static double outresult[4];
  $target = &outresult[0];
}   

// Return this output argument as a tuple containing 4 elements
// Since this an output argument it is really part of a list

%typemap(python,argout) double out[4] {
  int i;
  PyObject *o;

  o = PyTuple_New(4);
  for (i = 0; i < 4; i++) {
     PyTuple_SetItem(o,i,PyFloat_FromDouble($source[i]));
  }
  if (!$target) {
     $target = o;
  } else if ($target == Py_None) {
     Py_DECREF(Py_None);
     $target = o;
  } else {
     if (!PyList_Check($target)) {
        PyObject *o2 = $target;
        $target = PyList_New(0);
        PyList_Append($target,o2);
        Py_XDECREF(o2);
     }
     PyList_Append($target,o);
     Py_XDECREF(o);
  }
}

extern void add(double a[4], double b[4], double out[4]);
extern double *new_double(int n);
extern void print2d(double [4][4]);
extern void printdoubleptr(double *a);

