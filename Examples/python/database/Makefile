TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = db.c
TARGET     = db
INTERFACE  = db.i
SWIGOPT    = 

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	python

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' SWIGOPT='$(SWIGOPT)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' python_static

clean::
	rm -f *_wrap* *.o *~ *.so mypython *.pyc 


