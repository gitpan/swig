# Generated automatically from Makefile.in by configure.
# ---------------------------------------------------------------
# $Header:$
# SWIG Tcl/Tk Makefile
# 
# This file can be used to build various Tcl extensions with SWIG.
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
# script and should already reflect your machine. However, you
# may need to modify the Makefile to reflect your specific
# application.
#----------------------------------------------------------------

SRCS          = 
CXXSRCS       = 
OBJCSRCS      = 
OBJS          = 
INTERFACE     = 
WRAPFILE      = $(INTERFACE:.i=_wrap.c)
WRAPOBJ       = $(INTERFACE:.i=_wrap.o)
TARGET        = module.so # Use this kind of target for dynamic loading
#TARGET        = my_tclsh  # Use this target for static linking

prefix        = /home/beazley/scratch
exec_prefix   = ${prefix}

CC            = gcc
CXX           = c++
OBJC          = gcc -Wno-import # -Wno-import needed for gcc 
CFLAGS        = 
INCLUDE       =
LIBS          =

# SWIG Options
#     SWIG      = location of the SWIG executable
#     SWIGOPT   = SWIG compiler options
#     SWIGCC    = Compiler used to compile the wrapper file

SWIG          = $(exec_prefix)/bin/swig 
SWIGOPT       = -tcl # use -tcl8 for Tcl 8.0
SWIGCC        = $(CC) 

# SWIG Library files.  Uncomment one of these for rebuilding tclsh or wish
#SWIGLIB       = -ltclsh.i
#SWIGLIB       = -lwish.i

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

# X11 installation (needed to rebuild Tk extensions)

XLIB          = -L/usr/X11R6/lib -lX11
XINCLUDE      = -I/usr/X11R6/include

# Tcl installation (where is Tcl/Tk located)

TCL_INCLUDE   = -I/usr/local/include
TCL_LIB       = -L/usr/local/lib

# Build libraries (needed for static builds)

LIBM          = -lm
LIBC          = 
SYSLIBS       = $(LIBM) $(LIBC) -ldl 

# Build options (uncomment only one these)

BUILD_LIBS    = $(LIBS) # Dynamic loading
#BUILD_LIBS    = $(TCL_LIB) -ltcl $(LIBS) $(SYSLIBS) # tclsh  
#BUILD_LIBS    = $(TCL_LIB) -ltk -ltcl $(XLIB) $(LIBS) $(SYSLIBS) # wish

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
	$(SWIGCC) -c $(CCSHARED) $(CFLAGS) $(WRAPFILE) $(INCLUDE) $(TCL_INCLUDE) 

$(WRAPFILE) : $(INTERFACE)
	$(SWIG) $(SWIGOPT) -o $(WRAPFILE) $(SWIGLIB) $(INTERFACE)

$(TARGET): $(WRAPOBJ) $(ALLOBJS)
	$(BUILD) $(WRAPOBJ) $(ALLOBJS) $(BUILD_LIBS) -o $(TARGET)

clean:
	rm -f $(COBJS) $(CXXOBJS) $(OBJCOBJS) $(WRAPOBJ) $(WRAPFILE) $(TARGET)




