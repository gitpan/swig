TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = native.c
TARGET     = spam
INTERFACE  = native.i

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' python

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' python_static

clean::
	rm -f *_wrap* *.o *~ *.so mypython *.pyc .~*

