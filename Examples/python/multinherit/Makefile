TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = inheritc
INTERFACE  = inherit.i
SWIGOPT    = -shadow 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	python_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
        SWIGOPT='$(SWIGOPT)' TARGET='mypython' INTERFACE='$(INTERFACE)' python_static_cpp

clean::
	rm -f *_wrap* *.o *~ *.so mypython *.pyc inherit.py .~*


