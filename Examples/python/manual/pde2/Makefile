TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = pde.c
TARGET     = pdec
INTERFACE  = pde.i
SWIGOPT    = -c++ -shadow 
LIBS       = 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	LIBS='$(LIBS)' python_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' SWIGOPT='-DSTATIC $(SWIGOPT)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' python_static_cpp

ccode::
	c++ pde.c ex4.c -o a.out

clean::
	rm -f *_wrap* *.o *~ *.so mypython *.pyc pde.py .~* Dat* a.out


