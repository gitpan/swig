all::
	@echo "Type 'make' in each example's subdirectory to build."

nuke::
	cd tcl; make clean
	cd perl5; make clean
	cd python; make clean
	cd perl4; make clean
	cd guile; make clean
	cd GIFPlot; make clean
	cd OpenGL; make clean
	cd MATLAB; make clean
	find . \( -name '*~' \
		-o -name '*.pyc' \
		-o -name 'core' \
		-o -name '#*' \
		-o -name '*.o' \
		-o -name '*.so' \
		-o -name '*.sl' \
		-o -name '*_wrap*' \
		-o -name 'my_tclsh' \
		-o -name 'myperl' \
		-o -name 'mypython' \
		\) -exec rm {} \;

