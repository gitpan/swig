all:
	g++ main.cxx lang.cxx -I../../Include -L../.. -lswig -o myswig

simple:
	g++ main.cxx mylang.cxx -I../../Include -L../.. -lswig -o myswig

test:
	./myswig -ltcl/tclsh.i example.i 
	gcc example.c example_wrap.c -I/usr/local/include -L/usr/local/include -ltcl -lm -o mytclsh

clean:
	rm -f myswig *_wrap* *.o *~ mytclsh

