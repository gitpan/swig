// SWIG interface for our widget
%module plotwidget

%{
#include "widget.h"
%}


// Type mapping for grabbing a Python object (needed later)

%typemap(python,in) PyObject *pyfunc {
  if (!PyCallable_Check($source)) {
      PyErr_SetString(PyExc_TypeError, "Need a callable object!");
      return NULL;
  }
  $target = $source;
}

// Type mapping for grabbing a FILE * from Python

%typemap(python,in) FILE * {
  if (!PyFile_Check($source)) {
      PyErr_SetString(PyExc_TypeError, "Need a file!");
      return NULL;
  }
  $target = PyFile_AsFile($source);
}

// Grab the class definition

%include widget.h

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

%}

// Attach a new method to our plot widget 

%addmethods PlotWidget {
   // Set a Python function object as a callback function
   void set_pymethod(PyObject *pyfunc) {
     self->set_method(PythonCallBack, (void *) pyfunc);
     Py_INCREF(pyfunc);
   }
}

#ifdef STATIC
%include embed.i
#endif
