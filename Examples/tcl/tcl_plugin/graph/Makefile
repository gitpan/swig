TOP       = ../../../..
SWIG      = $(TOP)/swig
SRCS      = graph.c
TARGET    = graph
PLUG      = $(HOME)/.netscape/plugins/libtclplugin.so
LIBS      = $(PLUG) 
INTERFACE = graph.i
SWIGOPT   = -plugin

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	LIBS='$(LIBS)' tcldl

clean::
	rm -f *.o *.so *_wrap* *~

