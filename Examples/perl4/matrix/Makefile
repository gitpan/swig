CC     = gcc
SRCS   = matrix.c vector.c
TARGET = matrix
IFILE  = package.i
MKDIR  = ..

all::
	$(MAKE) -f $(MKDIR)/Makefile SRCS='$(SRCS)' TARGET=$(TARGET) IFILE=$(IFILE) CC=$(CC)

clean::
	rm -f matrix *.o *~ .~* core *_wrap* 


