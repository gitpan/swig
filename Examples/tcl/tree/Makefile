TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = tree.c
TARGET     = tree
INTERFACE  = tree.i

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tcldl

tcl8::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-tcl8' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tcldl

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh

static8::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-tcl8' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh

clean::
	rm -f *_wrap* *.o tree *~ *.so *.sl

