# Makefile for Perl4.  Used by all of the example programs
#

#PERL4_INCLUDE = /usr/local/include/perl
PERL4_INCLUDE = /home/beazley/Packages/perl-4.036
PERL4_UPERL   = uperl.o
LFLAGS      =  -lndbm -lm -lbsd  
WRAP        = $(IFILE:.i=_wrap.c)

all::	
	../../../swig -perl4 $(IFILE)
	$(CC) $(SRCS) $(WRAP) $(PERL4_INCLUDE)/$(PERL4_UPERL) -I$(PERL4_INCLUDE) $(LFLAGS) -o $(TARGET)

clean::
	cd matrix; make clean
	cd simple; make clean
	cd tree; make clean
	rm -f *~ .~* 
