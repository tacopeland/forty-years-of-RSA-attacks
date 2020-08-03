CXX=g++
CPPFLAGS=-I. -Wall -Werror
LDFLAGS=-lntl -lgmp -lm -L.

RM=rm -f

TSTDIR=./tests
TSTOBJS=$(TSTDIR)/RSA_key_construct.o
OBJS=RSAkey.o

all: test

test: $(TSTDIR)/test_genkey $(TSTDIR)/test_enc_dec

$(TSTDIR)/test_genkey: $(TSTDIR)/RSA_key_construct.o RSAkey.o
	$(CXX) $(LDFLAGS) $^ -o $@

$(TSTDIR)/test_enc_dec: $(TSTDIR)/RSA_encrypt_decrypt.o RSA.o RSAkey.o
	$(CXX) $(LDFLAGS) $^ -o $@

$(TSTDIR)/RSA_encrypt_decrypt.o: RSA.o RSA.h RSAkey.o RSAkey.h

$(TSTDIR)/RSA_key_construct.o: RSAkey.o RSAkey.h

RSAkey.o: RSAkey.h

clean: distclean
	$(RM) *.o tests/*.o

distclean:
	$(RM) $(TSTDIR)/test_genkey $(TSTDIR)/test_enc_dec
