# Makefile is set up for Linux!

TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = base_wrap.c foo_wrap.c bar_wrap.c 
TARGET     = myperl
DLTARGET   = package
INTERFACE  = package.i
SWIGOPT    = -c # -shadow

# You will need to modify this line for your machine

LIBS       = -L/usr/local/lib -lswigpl -Xlinker -rpath /usr/local/lib

# Produce a bunch of dynamic modules

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='base' INTERFACE='base.i' perl5_cpp
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='foo' INTERFACE='foo.i' perl5_cpp
	$(MAKE) -f $(TOP)/Makefile.template SRCS='' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='bar' INTERFACE='bar.i' perl5_cpp

# Produce a static executable

static::
	$(SWIG) $(SWIGOPT) -c++ -perl5 -static base.i
	$(SWIG) $(SWIGOPT) -c++ -perl5 -static foo.i
	$(SWIG) $(SWIGOPT) -c++ -perl5 -static bar.i
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' LIBS='$(LIBS)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' perl5_static_cpp

clean::
	rm -f *_wrap* *.o myperl *~ .~* core *.so *.sl *.pm


