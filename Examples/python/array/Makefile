TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = darrayc
INTERFACE  = array.i
SWIGOPT    = -shadow 
CFLAGS     = -fhandle-exceptions    # This is needed for g++
LIBS       = -lg++ 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' CFLAGS='$(CFLAGS)' \
	LIBS='$(LIBS)' SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' python_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' SWIGOPT='$(SWIGOPT)' \
	CFLAGS='$(CFLAGS)' TARGET='mypython' INTERFACE='$(INTERFACE)' python_static_cpp

clean::
	rm -f *_wrap* *.o *~ *.so darray.py mypython *.pyc .~*

