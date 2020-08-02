CXX=g++
CPPFLAGS=-I.
LDFLAGS=-lntl -lgmp -lm

RM=rm -f

TSTDIR=./tests
TSTOBJS=$(TSTDIR)/RSA_key_construct.o
OBJS=RSAkey.o

all: test

test: $(TSTDIR)/test_genkey

$(TSTDIR)/test_genkey: $(TSTDIR)/RSA_key_construct.o RSAkey.o RSAkey.h
	$(CXX) $(LDFLAGS) $^ -o $@

$(TSTDIR)/RSA_key_construct.o: RSAkey.o RSAkey.h

RSAkey.o: RSAkey.h

clean: distclean
	$(RM) *.o tests/*.o

distclean:
	$(RM) tests/test_genkey
