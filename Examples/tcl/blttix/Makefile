TOP        = ../../..
SWIG       = $(TOP)/swig
TARGET     = my_wish
SRCS       = 
INTERFACE  = example.i
LIBS       = -ltix-tk4.1 -L/usr/local/blt/lib -lBLT -lX11

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	LIBS='$(LIBS)' TARGET='$(TARGET)' INTERFACE='$(INTERFACE)' wish

clean::
	rm -f .~* *_wrap* *.o my_wish *~ core #*


