TOP        = ../../../..
SWIG       = $(TOP)/swig
SRCS       = widget.cxx
TARGET     = plotwidgetc
INTERFACE  = widget.i
SWIGOPT    = -shadow -c++
LIBS       = -lgd -lm

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='$(SWIGOPT)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' \
	LIBS='$(LIBS)' python_cpp

static::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' SWIGOPT='-DSTATIC $(SWIGOPT)' \
	TARGET='mypython' INTERFACE='$(INTERFACE)' LIBS='$(LIBS)' python_static_cpp

ccode::
	c++ widget.cxx main.cxx -I/usr/local/include -L/usr/local/lib $(LIBS) -o cplot

clean::
	rm -f *_wrap* *.o *~ *.so mypython plotwidget.py cplot *.gif *.pyc .~*


