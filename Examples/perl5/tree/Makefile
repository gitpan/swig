TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = tree.c
TARGET     = Tree
INTERFACE  = tree.i
LIBS       = 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' LIBS='$(LIBS)' perl5

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='myperl' INTERFACE='$(INTERFACE)' perl5_static

clean::
	rm -f *_wrap* *.o *.pm core *~ *.so myperl .~*




