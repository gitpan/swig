// SWIG Module for handling some callback functions written in Python

%module callback
%{

#include "widget.h"

%}

/* These are some normal C functions for our "widget."       */
/* Note : use of a typedef for function pointers is required */

typedef double (*CALLBACK)(double, void *);
Widget *new_widget();
double  widget_op(Widget *w, double a);
void    widget_add_callback(Widget *w, CALLBACK callback, void *);

// ----------------------------------------------------------------
// Python helper functions for adding callbacks
// ----------------------------------------------------------------

%{

/* This function matches the prototype of a normal C callback
   function for our widget. However, the clientdata pointer
   actually refers to a Python callable object. */

static double PythonCallBack(double a, void *clientdata)
{
   PyObject *func, *arglist;
   PyObject *result;
   double    dres = 0;
   
   func = (PyObject *) clientdata;
   arglist = Py_BuildValue("(d)",a);
   result = PyEval_CallObject(func,arglist);
   Py_DECREF(arglist);
   if (result) {
     dres = PyFloat_AsDouble(result);
   }
   Py_XDECREF(result);
   return dres;
}

/* This function adds a new Python function object as a callback object */

static void pywidget_add_callback(Widget *w, PyObject *PyFunc) {
  widget_add_callback(w,PythonCallBack, (void *) PyFunc);
  Py_INCREF(PyFunc);
}

%}

// -------------------------------------------------------------------
// SWIG typemap allowing us to grab a Python callable object
// -------------------------------------------------------------------

%typemap(python,in) PyObject *PyFunc {
  if (!PyCallable_Check($source)) {
      PyErr_SetString(PyExc_TypeError, "Need a callable object!");
      return NULL;
  }
  $target = $source;
}

// Our new python callback registration function.  Note the use of 
// a typemap to grab a PyObject.

void pywidget_add_callback(Widget *w, PyObject *PyFunc);

// Now make a symbol for our C callback function
%{
/* Need to declare it in our file */
extern double foo(double, void *);
%}

// Create a constant 'FOO' that is the address of a C callback function
const CALLBACK FOO = foo;

// C function for filling an array
extern void fill_array(Widget *w, double *data, int nitems);

// Grab SWIG array module
%include array.i 

