TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = my_tclsh
DLTARGET   = return
INTERFACE  = return.i

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(DLTARGET)' INTERFACE='$(INTERFACE)' tcldl

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh

clean::
	rm -f *_wrap* *.o my_tclsh *~ core *.so *.sl


