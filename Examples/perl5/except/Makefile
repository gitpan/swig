TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = 
TARGET     = darray
INTERFACE  = array.i
CFLAGS     = -fhandle-exceptions   # This is needed for g++
SWIGOPT    = -shadow

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' CFLAGS='$(CFLAGS)' perl5_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='myperl' INTERFACE='$(INTERFACE)' CFLAGS='$(CFLAGS)' perl5_static_cpp

clean::
	rm -f *_wrap* *.o core *~ *.so *.pm myperl

