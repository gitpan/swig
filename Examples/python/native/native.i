// Swig file that adds an already existing Python wrapper function

%module spam

%native(system) extern PyObject *spam_system(PyObject *, PyObject *);

