TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = shapes
INTERFACE  = shapes.i
CFLAGS     = 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' CFLAGS='$(CFLAGS)' perl5_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='myperl' INTERFACE='$(INTERFACE)' perl5_static_cpp

clean::
	rm -f *_wrap* *.o core *~ *.so *.pm myperl

