TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = argv
INTERFACE  = argv.i
SWIGOPT    = -shadow
all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' perl5_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='myperl' INTERFACE='$(INTERFACE)' perl5_static_cpp

clean::
	rm -f *_wrap* *.o myperl *~ core *.pm .~*


