TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = nestedc
INTERFACE  = nested.i
SWIGOPT    = -shadow

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' SWIGOPT='$(SWIGOPT)' python

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' SWIGOPT='$(SWIGOPT)' python_static

clean::
	rm -f *_wrap* *.o *~ *.so mypython nested.py* .~* core

