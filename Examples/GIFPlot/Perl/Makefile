# Generated automatically from Makefile.in by configure.
# This Makefile is used to build a Perl module from the GIFPlot library.
# Change the location of SWIG and Perl below

CC        = gcc
SWIG      = swig
IDIR      = ../Interface
IFILE     = gifplot.i
ISRC      = $(IFILE:.i=_wrap.c)
IOBJ      = $(ISRC:.c=.o)
TARGET    = gifplot
INCLUDE   = -I../Include 
PERLINCLUDE = /usr/lib/perl5/i386-linux/5.003/CORE
SO        = .so
LDSHARED  = gcc -shared
CCSHARED  = -fpic

all:	$(ISRC)
	$(CC) $(CCSHARED) -c $(ISRC) $(INCLUDE) -I$(PERLINCLUDE) -Dbool=char 
	$(LDSHARED) $(IOBJ) -L.. -lgifplot -o $(TARGET)$(SO)

$(ISRC): $(IDIR)/$(IFILE)
	$(SWIG) -perl5 -shadow -dnone -o $(ISRC) $(IDIR)/$(IFILE)

clean:
	rm -f *.o *.so *_wrap* *.pm *~ *.gif $(IDIR)/*_wrap*








