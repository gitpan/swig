TOP        = ../../..
SWIG       = $(TOP)/swig 
SRCS       = list.c
TARGET     = my_tclsh
DLTARGET   = list
INTERFACE  = list.i
SWIGOPT    = -noobject

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(DLTARGET)' INTERFACE='$(INTERFACE)' tcldl_cpp

tcl8::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-tcl8 $(SWIGOPT)' TARGET='$(DLTARGET)' INTERFACE='$(INTERFACE)' tcldl_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh_cpp

static8::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-tcl8 $(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh_cpp


clean::
	rm -f *_wrap* *.o my_tclsh *~ .~* core *.so *.sl

