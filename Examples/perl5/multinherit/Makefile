TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = inherit
INTERFACE  = inherit.i
CFLAGS     = 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-shadow' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' CFLAGS='$(CFLAGS)' perl5_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-shadow' TARGET='myperl' INTERFACE='$(INTERFACE)' perl5_static_cpp

clean::
	rm -f *_wrap* *.o core *~ *.so *.pm myperl .~*

