CC     = gcc
SRCS   = example.c
TARGET = my_perl
IFILE  = example.i
MKDIR  = ..

perl4::
	$(MAKE) -f $(MKDIR)/Makefile SRCS='$(SRCS)' TARGET=$(TARGET) IFILE=$(IFILE) CC=$(CC)

clean::
	rm -f my_perl *~ .~* core *_wrap*
