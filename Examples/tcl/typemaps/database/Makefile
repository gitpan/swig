TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = db.c
TARGET     = my_tclsh
DLTARGET   = db
INTERFACE  = db.i

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(DLTARGET)' INTERFACE='$(INTERFACE)' tcldl

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tclsh

clean::
	rm -f *_wrap* *.o my_tclsh *~ core *. .~* *.so *.sl



