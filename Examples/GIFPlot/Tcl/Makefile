# Generated automatically from Makefile.in by configure.
# This Makefile is used to build a Tcl module from the GIFPlot library.
# Change the location of SWIG and Tcl below

CC        = gcc
SWIG      = swig
IDIR      = ../Interface
IFILE     = gifplot.i
ISRC      = $(IFILE:.i=_wrap.c)
IOBJ      = $(ISRC:.c=.o)
TARGET    = gifplot
INCLUDE   = -I../Include 
TCLINCLUDE = -I/usr/local/include
SO        = sl
LDSHARED  = gcc -shared
CCSHARED  = -fpic

all:	$(ISRC) mandel
	$(CC) $(CCSHARED) -c $(ISRC) $(INCLUDE) $(TCLINCLUDE) 
	$(LDSHARED) $(IOBJ) -L.. -lgifplot -o $(TARGET).$(SO)

$(ISRC): $(IDIR)/$(IFILE)
	$(SWIG) -tcl -dnone -o $(ISRC) $(IDIR)/$(IFILE)

mandel::
	$(SWIG) -tcl -dnone -I../Interface mandel.i
	$(CC) $(CCSHARED) -c mandel_wrap.c $(INCLUDE) $(TCLINCLUDE)
	$(LDSHARED) mandel_wrap.o -L.. -lgifplot -o mandel.$(SO)

clean:
	rm -f *.o *.so *.sl *_wrap* *~ *.gif $(IDIR)/*_wrap*



