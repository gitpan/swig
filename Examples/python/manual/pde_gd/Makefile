TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = pde.c 
TARGET     = pdec
INTERFACE  = pde.i
SWIGOPT    = -c++ -shadow
LIBS       = -lgd

# Build two dynamically loadable modules

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='pdec' INTERFACE='pde.i' python_cpp
	$(MAKE) -f $(TOP)/Makefile.template SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='gdc' INTERFACE='gd.i' \
	LIBS='$(LIBS)' python_cpp

static::
	$(SWIG) -python -shadow gd.i
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS) gd_wrap.c' SWIG='$(SWIG)' SWIGOPT='-DSTATIC $(SWIGOPT)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' LIBS='$(LIBS)' python_static_cpp

clean::
	rm -f *_wrap* *.o *~ *.so mypython *.pyc pde.py gd.py *.gif Dat* .~*


