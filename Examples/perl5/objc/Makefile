# Generated automatically from Makefile.in by configure.
# ---------------------------------------------------------------
# $Header:$
# SWIG Perl5 Makefile
# 
# This file can be used to build various Perl5 extensions with SWIG.
# By default this file is set up for dynamic loading, but it can
# be easily customized for static extensions by modifying various
# portions of the file.
#
#        SRCS       = C source files
#        CXXSRCS    = C++ source files
#        OBJCSRCS   = Objective-C source files
#        OBJS       = Additional .o files (compiled previously)
#        INTERFACE  = SWIG interface file
#        TARGET     = Name of target module or executable
#
# Many portions of this file were created by the SWIG configure
# script and should already reflect your machine.
#----------------------------------------------------------------

SRCS          = 
CXXSRCS       = 
OBJCSRCS      = list.m user.m
OBJS          = 
INTERFACE     = interface.i
WRAPFILE      = $(INTERFACE:.i=_wrap.m)
WRAPOBJ       = $(INTERFACE:.i=_wrap.o)
TARGET        = list.so # Use this kind of target for dynamic loading
#TARGET        = myperl  # Use this target for static linking

prefix        = /home/beazley/Test
exec_prefix   = ${prefix}

CC            = gcc
CXX           = c++
OBJC          = gcc -Wno-import # -Wno-import needed for gcc 
CFLAGS        = 
INCLUDE       =
LIBS          = -lobjc -lgcc

# SWIG Options
#     SWIG      = location of the SWIG executable
#     SWIGOPT   = SWIG compiler options
#     SWIGCC    = Compiler used to compile the wrapper file

SWIG          = $(exec_prefix)/bin/swig 
SWIGOPT       = -perl5 -objc
SWIGCC        = $(OBJC) 

# SWIG Library files.  Uncomment this to staticly rebuild Perl
#SWIGLIB       = -static -lperlmain.i

# Rules for creating .o files from source.

COBJS         = $(SRCS:.c=.o)
CXXOBJS       = $(CXXSRCS:.cxx=.o)
OBJCOBJS      = $(OBJCSRCS:.m=.o)
ALLOBJS       = $(COBJS) $(CXXOBJS) $(OBJCOBJS) $(OBJS)

# Command that will be used to build the final extension.
BUILD         = $(SWIGCC)

# Uncomment the following if you are using dynamic loading
CCSHARED      = -fpic
BUILD         = gcc -shared

# Uncomment the following if you are using dynamic loading with C++ and
# need to provide additional link libraries (this is not always required).

#DLL_LIBS      = -L/usr/local/lib/gcc-lib/sparc-sun-solaris2.5.1/2.7.2 \
             -L/usr/local/lib -lg++ -lstdc++ -lgcc

# X11 installation (possibly needed if using Perl-Tk)

XLIB          = -L/usr/X11R6.3/lib -lX11
XINCLUDE      = -I/usr/X11R6.3/include

# Perl installation

PERL_INCLUDE  = -I/usr/lib/perl5/i386-linux/5.003/CORE
PERL_LIB      = -L/usr/lib/perl5/i386-linux/5.003/CORE -lperl 
PERL_FLAGS    = -Dbool=char -Dexplicit=

# Tcl installation.  If using Tk you might need this

TCL_INCLUDE   = -I/usr/local/include
TCL_LIB       = -L/usr/local/lib

# Build libraries (needed for static builds)

LIBM          = -lm
LIBC          = 
SYSLIBS       = $(LIBM) $(LIBC) 

# Build options (uncomment only one these)

#TK_LIB        = $(TCL_LIB) -ltcl -ltk $(XLIB)
BUILD_LIBS    = $(LIBS) # Dynamic loading
#BUILD_LIBS    = $(PERL_LIB) $(TK_LIB) $(LIBS) $(SYSLIBS)  # Static linking

# Compilation rules for non-SWIG components

.SUFFIXES: .c .cxx .m

.c.o:
	$(CC) $(CCSHARED) $(CFLAGS) $(INCLUDE) -c $<

.cxx.o:
	$(CXX) $(CCSHARED) $(CXXFLAGS) $(INCLUDE) -c $<

.m.o:
	$(OBJC) $(CCSHARED) $(CFLAGS) $(INCLUDE) -c $<


# ----------------------------------------------------------------------
# Rules for building the extension
# ----------------------------------------------------------------------

all: $(TARGET)

# Convert the wrapper file into an object file

$(WRAPOBJ) : $(WRAPFILE)
	$(SWIGCC) -c $(CCSHARED) $(CFLAGS) $(INCLUDE) $(PERL_INCLUDE) $(PERL_FLAGS) $(WRAPFILE)

$(WRAPFILE) : $(INTERFACE)
	$(SWIG) $(SWIGOPT) -o $(WRAPFILE) $(SWIGLIB) $(INTERFACE)

$(TARGET): $(WRAPOBJ) $(ALLOBJS)
	$(BUILD) $(CFLAGS) $(INCLUDE) $(PERL_INCLUDE) $(WRAPOBJ) $(ALLOBJS) $(BUILD_LIBS) -o $(TARGET)

clean:
	rm -f $(COBJS) $(CXXOBJS) $(OBJCOBJS) $(WRAPOBJ) $(WRAPFILE) $(TARGET) *.pm *_wrap* *~ 






