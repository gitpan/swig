TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = pde.c
TARGET     = pde
INTERFACE  = pde.i
SWIGOPT    = -c++
LIBS       = 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	LIBS='$(LIBS)' python_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' SWIGOPT='-DSTATIC $(SWIGOPT)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' python_static_cpp

ccode::
	c++ ex2.c pde.c -o a.out

clean::
	rm -f *_wrap* *.o *~ *.so mypython *.pyc .~* a.out


