
/* This file has a native Python wrapper function in it.
   We'll use SWIG to add it */

#include "Python.h"

PyObject *spam_system(PyObject *self, PyObject *args) {
  char *command;
  int   sts;
  if (!PyArg_ParseTuple(args,"s",&command))
    return NULL;
  sts = system(command);
  return Py_BuildValue("i",sts);
}


