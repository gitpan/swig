# Generated automatically from Makefile.in by configure.
# This Makefile is used to build a Python module from the GIFPlot library.
# Change the location of SWIG and Python below

CC        = gcc
SWIG      = ../../../swig
IDIR      = ../Interface
IFILE     = gifplot.i
ISRC      = $(IFILE:.i=_wrap.c)
IOBJ      = $(ISRC:.c=.o)
TARGET    = gifplotc
INCLUDE   = -I../Include 
PYINCLUDE = -I/usr/local/include/python1.5 -I/usr/local/lib/python1.5/config
SO        = .so
LDSHARED  = gcc -shared
CCSHARED  = -fpic

all:	$(ISRC)
	$(CC) $(CCSHARED) -c $(ISRC) $(INCLUDE) $(PYINCLUDE) -DHAVE_CONFIG_H
	$(LDSHARED) $(IOBJ) -L.. -lgifplot -o $(TARGET)module$(SO)

$(ISRC): $(IDIR)/$(IFILE)
	$(SWIG) -python -shadow -dnone -o $(ISRC) $(IDIR)/$(IFILE)

clean:
	rm -f *.o *.so *_wrap* *.pyc *~ gifplot.py *.gif $(IDIR)/*_wrap*



