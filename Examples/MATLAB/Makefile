# Generated automatically from Makefile.in by configure.
CXX= c++
SWIG = ../../swig
SWIGLIB = -L../..
SWIGINCLUDE = -I../../Include

all:
	$(CXX) main.cxx matlab.cxx $(SWIGINCLUDE) $(SWIGLIB) -lswig -o swigmatlab

# Note : This has not been tested under Unix
test:
	swigmatlab example.i
	mex example.c example_wrap.c

clean:
	rm -f swigmatlab *_wrap* *.o *~ 

