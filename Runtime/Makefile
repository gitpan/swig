# Generated automatically from Makefile.in by configure.
# Makefile for producing SWIG runtime libraries. 
#
# The SWIG runtime library consists of the pointer-type checker
# and other support functions.  Multi-file SWIG modules 
# generally link with these libraries.
#
# By default, the installation processs will attempt to 
# build shared libraries.  If that doesn't work, a static
# library is built instead.

prefix      = /home/beazley/scratch
exec_prefix = ${prefix}
CC          = gcc
AR          = ar
RANLIB      = ranlib
SO          = .so
CCSHARED    = -fpic
LDSHARED    = gcc -shared
LIBS        = libswigtcl.a libswigpl.a libswigpy.a libswigtcl$(SO) libswigpl$(SO) libswigpy$(SO)
LIB_DIR     = $(exec_prefix)/lib

INSTALL_DATA = ../install-sh -c -m 644

all:
	@sh make.sh


install:
	@echo "Installing runtime libraries"
	@for i in $(LIBS); \
	do \
	if [ -f $$i ]; then \
	   echo "Installing $$i in $(LIB_DIR)/$$i"; \
	   $(INSTALL_DATA) $$i $(LIB_DIR)/$$i; \
        fi; \
	done;

clean::
	rm -rf *.o *.a *$(SO) *.c *.swg *~ core

# ----------------------------------------------------------------------
# Tcl runtime library
# ----------------------------------------------------------------------

TCL_INCLUDE = -I/usr/local/include
TCL_LIB     = -L/usr/local/lib

# Tcl 7.x shared

tcl_shared:
	../swig -tcl -co -o libtcl.c -I../swig_lib swigptr.swg
	$(CC) $(CCSHARED) -c -DSWIG_GLOBAL libtcl.c
	$(LDSHARED) libtcl.o -o libswigtcl$(SO)

# Tcl 7.x library

tcl_lib:
	../swig -tcl -co -o libtcl.c -I../swig_lib swigptr.swg
	$(CC) -c -DSWIG_GLOBAL libtcl.c
	$(AR) cr libswigtcl.a libtcl.o

# Tcl 8.x shared

tcl8_shared:
	../swig -tcl -co -o libtcl8.c -I../swig_lib tcl8ptr.swg
	$(CC) $(CCSHARED) -c -DSWIG_GLOBAL $(TCL_INCLUDE) libtcl8.c
	$(LDSHARED) libtcl8.o -o libswigtcl8$(SO)

tcl8_lib:
	../swig -tcl -co -o libtcl8.c -I../swig_lib tcl8ptr.swg
	$(CC) -c -DSWIG_GLOBAL $(TCL_INCLUDE) libtcl8.c
	$(AR) cr libswigtcl8.a libtcl8.o

# ----------------------------------------------------------------------
# Python run-time library
# ----------------------------------------------------------------------

PYTHON_INCLUDE= -DHAVE_CONFIG_H -I/home/beazley/scratch/include/python1.4 -I/home/beazley/scratch/lib/python1.4/config
PYTHON_LIB    = /home/beazley/scratch/lib/python1.4/config

# Python shared

py_shared:
	../swig -python -co -o libpy.c -I../swig_lib python.swg
	../swig -python -co -o libptr.c -I../swig_lib swigptr.swg
	$(CC) $(CCSHARED) -c -DSWIG_GLOBAL $(PYTHON_INCLUDE) libpy.c libptr.c
	$(LDSHARED) libpy.o libptr.o -o libswigpy$(SO)

# Python library

py_lib:
	../swig -python -co -o libpy.c -I../swig_lib python.swg
	../swig -python -co -o libptr.c -I../swig_lib swigptr.swg
	$(CC) -c -DSWIG_GLOBAL $(PYTHON_INCLUDE) libpy.c libptr.c
	$(AR) cr libswigpy.a libpy.o libptr.o

# ----------------------------------------------------------------------
# Perl run-time library
# ----------------------------------------------------------------------

PERL5_INCLUDE= -I/usr/lib/perl5/i386-linux/5.003/CORE

# Perl shared

perl_shared:
	rm -f libperl.c libperl.swg
	../swig -perl5 -co -o libperl.c -I../swig_lib perl5.swg
	../swig -perl5 -co -o libperl.swg -I../swig_lib perl5ptr.swg
	cat perlrun.h >> libperl.c
	cat libperl.swg >> libperl.c
	$(CC) $(CCSHARED) -c -Dexplicit= -Dbool=char -DSWIG_GLOBAL $(PERL5_INCLUDE) libperl.c
	$(LDSHARED) libperl.o -o libswigpl$(SO)

# Perl library

perl_lib:
	rm -f libperl.c libperl.swg
	../swig -perl5 -co -o libperl.c -I../swig_lib perl5.swg
	../swig -perl5 -co -o libperl.swg -I../swig_lib perl5ptr.swg
	cat perlrun.h >> libperl.c
	cat libperl.swg >> libperl.c
	$(CC) -c -Dexplicit= -Dbool=char -DSWIG_GLOBAL $(PERL5_INCLUDE) libperl.c
	$(AR) cr libswigpl.a libperl.o 
