#include <exception>
#include <NTL/ZZ.h>
#include "RSAkey.h"

// Encrypt/decrypt RSA integer-encoded messages
void encrypt(NTL::ZZ& c, const NTL::ZZ& m, const RSAkey& key);
void decrypt(NTL::ZZ& m, const NTL::ZZ& c, const RSAkey& key);

class KeyError : public std::exception {
public:
	const char * what ();
};
