TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = gdc
INTERFACE  = gd.i
SWIGOPT    = -shadow 
LIBS       = -lgd

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	LIBS='$(LIBS)' python

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' SWIGOPT='-DSTATIC $(SWIGOPT)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' LIBS='$(LIBS)' python_static

clean::
	rm -f *_wrap* *.o *~ *.so mypython gd.py* *.gif *.pyc .~*


