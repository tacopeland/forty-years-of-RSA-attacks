CXX=g++
CPPFLAGS=-I. -g -Wall -Werror
LDFLAGS=-lntl -lgmp -lgmpxx -lm -lstdc++ -L.

RM=rm -f

TSTDIR=./tests
TSTOBJS=$(TSTDIR)/RSA_key_construct.o $(TSTDIR)/RSA_encrypt_decrypt.o
ATTACKS=integer_root common_modulus blinding

all: $(ATTACKS)
.PHONY: all

blinding: blinding.o

blinding.o: blinding.cpp

integer_root: integer_root.o

integer_root.o: integer_root.cpp

common_modulus: common_modulus.o RSA.o RSAkey.o

common_modulus.o: common_modulus.cpp

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
