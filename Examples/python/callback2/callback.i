// An entirely different mechanism for handling a callback

%module callback
%{
typedef void (*CALLBACK)(void);
%}

%include foo.c

%{

static PyObject *my_pycallback = NULL;
static void PythonCallBack(void)
{
   PyObject *func, *arglist;
   PyObject *result;

   func = my_pycallback;	 /* This is the function .... */
   arglist = Py_BuildValue("()");  /* No arguments needed */
   result =  PyEval_CallObject(func, arglist);
   Py_DECREF(arglist);
   Py_XDECREF(result);
   return /*void*/;
}

void
my_set_callback(PyObject *PyFunc)
{
	Py_XDECREF(my_pycallback);	        /* Dispose of previous callback */
	Py_XINCREF(PyFunc);			/* Add a reference to new callback */
	my_pycallback = PyFunc;			/* Remember new callback */
	set_callback(PythonCallBack);
}

%}

%typemap(python,in) PyObject *PyFunc {
  if (!PyCallable_Check($source)) {
      PyErr_SetString(PyExc_TypeError, "Need a callable object!");
      return NULL;
  }
  $target = $source;
}

void my_set_callback(PyObject *PyFunc);



