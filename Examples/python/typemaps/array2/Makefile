TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = array.c
TARGET     = carray
INTERFACE  = array.i

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' python

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' python_static

clean::
	rm -f *_wrap* *.o *~ *.so mypython *.pyc .~* core

