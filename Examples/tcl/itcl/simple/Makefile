# Check to make sure we can actually make ish,iwish,itclsh,itkwish

TOP        = ../../..
SWIG       = $(TOP)/swig
SRCS       = example.c
TARGET     = my_tclsh
INTERFACE  = example.i
SWIGOPT    = -namespace 

all:	ish iwish itclsh itkwish

ish::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-DISH $(SWIGOPT)' TARGET='my_ish' INTERFACE='$(INTERFACE)' ish
iwish::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-DIWISH $(SWIGOPT)' TARGET='my_iwish' INTERFACE='$(INTERFACE)' iwish
itclsh::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-DITCLSH $(SWIGOPT)' TARGET='my_itclsh' INTERFACE='$(INTERFACE)' itclsh
itkwish::
	$(MAKE) -f $(TOP)/Makefile.template SRCS='$(SRCS)' SWIG='$(SWIG)' \
	SWIGOPT='-DITKWISH $(SWIGOPT)' TARGET='my_itkwish' INTERFACE='$(INTERFACE)' itkwish

clean::
	rm -f *_wrap* *.o my_ish my_iwish my_itclsh my_itkwish *~ core


