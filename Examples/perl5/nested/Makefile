TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = nested
INTERFACE  = nested.i
SWIGOPT    = -shadow

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' SWIGOPT='$(SWIGOPT)' perl5

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' SWIGOPT='$(SWIGOPT)' \
	TARGET='myperl' INTERFACE='$(INTERFACE)' perl5_static

clean::
	rm -f *_wrap* *.o *~ *.so myperl nested.pm* .~* core


