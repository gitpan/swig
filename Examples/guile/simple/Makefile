CC     = gcc
SRCS   = example.c
TARGET = my_guile
IFILE  = example.i
MKDIR  = ..

all::
	$(MAKE) -f $(MKDIR)/Makefile SRCS='$(SRCS)' TARGET=$(TARGET) IFILE=$(IFILE) CC=$(CC)

clean::
	rm -f *_wrap* my_guile *~ .~* core


