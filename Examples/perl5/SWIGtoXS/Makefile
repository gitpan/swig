TOP        = ../../..
SWIG       = $(TOP)/swig
XSSRCS     = produce.c
XSTARGET   = produce
SRCS       = 
TARGET     = consume
INTERFACE  = consume.i

all::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(XSSRCS)' \
	TARGET='$(XSTARGET)' perl5_xs
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	INTERFACE='$(INTERFACE)' TARGET='$(TARGET)' perl5

clean::
	rm -f *_wrap* *.o *~ consume.pm *.so myperl

