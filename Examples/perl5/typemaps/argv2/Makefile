TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = argv
INTERFACE  = argv.i

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' perl5

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='myperl' INTERFACE='$(INTERFACE)' perl5_static

clean::
	rm -f *_wrap* *.o myperl *~ core *.pm .~*


