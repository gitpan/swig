TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = my_tclsh
DLTARGET   = inherit
INTERFACE  = inherit.i


all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(DLTARGET)' INTERFACE='$(INTERFACE)' tcldl_cpp

tcl8::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-tcl8' TARGET='$(DLTARGET)' INTERFACE='$(INTERFACE)' tcldl_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh_cpp

static8::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-tcl8' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh_cpp


clean::
	rm -f .~* *_wrap* *.o my_tclsh *~ core *.so *.sl

