TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = graph.c
TARGET     = graph
INTERFACE  = graph.i

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tcldl

tcl8::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-tcl8' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' tcldl

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' wish

static8::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-tcl8' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' wish

clean::
	rm -f *_wrap* *.o $(TARGET) *~ *.so *.sl

