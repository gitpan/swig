TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = graph.c location.c
TARGET     = graph
INTERFACE  = graph.i
LIBS       = -lgd -lm
SWIGOPT    = -shadow 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' LIBS='$(LIBS)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' perl5

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' LIBS='$(LIBS)' TARGET='myperl' INTERFACE='$(INTERFACE)' perl5_static

clean::
	rm -f *_wrap* *.o core *~ *.so *.pm myperl *.gif

