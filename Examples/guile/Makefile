# Makefile for Guile.  Used by all of the example programs
#

GUILE_INCLUDE  = -I/home/beazley/Packages/include -I/home/beazley/Packages/include/guile
GUILE_LIB      = -L/home/beazley/Packages/lib

LFLAGS      = -lgh -lguile -lm
WRAP        = $(IFILE:.i=_wrap.c)

all::	
	../../../swig -guile $(IFILE)
	$(CC) $(SRCS) $(WRAP) $(GUILE_INCLUDE) $(GUILE_LIB) $(LFLAGS) -o $(TARGET)

clean::
	cd simple; make clean
	cd matrix; make clean
	rm -f *~ .~* 

