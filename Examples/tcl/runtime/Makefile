# Makefile is set up for Linux!

TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = base_wrap.c foo_wrap.c bar_wrap.c 
TARGET     = my_tclsh
DLTARGET   = package
INTERFACE  = package.i
SWIGOPT    = -c

# You will need to modify this line for your machine

LIBS       = -L/r1/scratch/lib -lswigtcl -Xlinker -rpath /r1/scratch/lib

# Produce a bunch of dynamic modules

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='base' INTERFACE='base.i' tcldl_cpp
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='foo' INTERFACE='foo.i' tcldl_cpp
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='bar' INTERFACE='bar.i' tcldl_cpp

# Produce a static executable

static::
	$(SWIG) -c -c++ -tcl base.i
	$(SWIG) -c -c++ -tcl foo.i
	$(SWIG) -c -c++ -tcl bar.i
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh_cpp

clean::
	rm -f *_wrap* *.o my_tclsh *~ .~* core *.so *.sl

