# Makefile is set up for Linux!

TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = base_wrap.c foo_wrap.c bar_wrap.c 
TARGET     = mypython
DLTARGET   = package
INTERFACE  = package.i
SWIGOPT    = -c

# You will need to modify this line for your machine

LIBS       = -L/usr/local/lib -lswigpy -Xlinker -rpath /usr/local/lib

# Produce a bunch of dynamic modules

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='base' INTERFACE='base.i' python_cpp
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='foo' INTERFACE='foo.i' python_cpp
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='bar' INTERFACE='bar.i' python_cpp


shadow::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='-shadow $(SWIGOPT)' TARGET='basec' INTERFACE='base.i' python_cpp
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='-shadow $(SWIGOPT)' TARGET='fooc' INTERFACE='foo.i' python_cpp
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='-shadow $(SWIGOPT)' TARGET='barc' INTERFACE='bar.i' python_cpp

# Produce a static executable

static::
	$(SWIG) $(SWIGOPT) -c++ -python base.i
	$(SWIG) $(SWIGOPT) -c++ -python foo.i
	$(SWIG) $(SWIGOPT) -c++ -python bar.i
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' python_static_cpp

clean::
	rm -f *_wrap* *.o mypython *~ .~* core *.so *.sl *.pm foo.py bar.py base.py *.pyc


