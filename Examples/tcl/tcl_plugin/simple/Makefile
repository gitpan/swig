TOP       = ../../../..
SWIG      = $(TOP)/swig
SRCS      = example.c
TARGET    = example
PLUG      = $(HOME)/.netscape/plugins/libtclplugin.so
LIBS      = $(PLUG) 
INTERFACE = example.i
SWIGOPT   = -plugin

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	LIBS='$(LIBS)' tcldl

clean::
	rm -f *.o *.so *_wrap* *~
