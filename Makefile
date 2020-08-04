CXX=g++
CPPFLAGS=-I. -Wall -Werror
LDFLAGS=-lntl -lgmp -lgmpxx -lm -lstdc++ -L.

RM=rm -f

TSTDIR=./tests
TSTOBJS=$(TSTDIR)/RSA_key_construct.o
OBJS=RSAkey.o
ATTACKS=integer_root

all: integer_root

integer_root: integer_root.o

integer_root.o: integer_root.cpp


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
	$(RM) $(ATTACKS) $(TSTDIR)/test_genkey $(TSTDIR)/test_enc_dec
