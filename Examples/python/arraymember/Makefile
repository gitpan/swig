TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = arraymemberc
INTERFACE  = arraymember.i
SWIGOPT    = -shadow 
LIBS       = 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	LIBS='$(LIBS)' python

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
        SWIGOPT='$(SWIGOPT)' TARGET='mypython' INTERFACE='$(INTERFACE)' python_static

clean::
	rm -f *_wrap* *.o *~ *.so mypython arraymember.py* .~*


