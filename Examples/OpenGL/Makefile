TOP        = ../..
MESA       = /usr/local/src/Mesa-2.5
SWIG       = $(TOP)/swig
INTERFACE  = opengl.i
LIBS       = -L$(MESA)/lib -lMesaaux -lMesatk -lMesaGLU -lMesaGL -lXext
XLIBS      = -L/usr/X11R6/lib -lX11
INCLUDE    = -I$(MESA)/include -I/usr/X11R6/include

# Build a Tcl OpenGL extension

tcl::
	$(MAKE) -f $(TOP)/Makefile.template INTERFACE='$(INTERFACE)' \
	SWIG='$(SWIG)' INCLUDE='$(INCLUDE)' LIBS='$(LIBS)' TARGET='Tcl/glwish' wish

# Build a Python dynamic module
python::
	$(MAKE) -f $(TOP)/Makefile.template INTERFACE='$(INTERFACE)' \
	SWIG='$(SWIG)' INCLUDE='$(INCLUDE)' LIBS='$(LIBS) $(XLIBS)' TARGET='Python/opengl' \
	python

# Build a Perl dynamic module
perl::
	$(MAKE) -f $(TOP)/Makefile.template INTERFACE='$(INTERFACE)' \
	SWIG='$(SWIG)' INCLUDE='$(INCLUDE)' LIBS='$(LIBS) $(XLIBS)' TARGET='Perl/opengl' \
	perl5
	cp opengl.pm Perl


clean::
	rm -f *_wrap* *.so Tcl/glwish Python/*.so Perl/*.so Perl/*.pm *~ .~* *.pm Tcl/*~ Perl/*~ Python/*~


