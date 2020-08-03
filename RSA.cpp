#include <exception>
#include <NTL/ZZ.h>
#include "RSA.h"

const char *KeyError::what() {
	return "Tried to decrypt using a public key.";
}


// Input: m, integer representation of plaintext
// key, the RSA public key
// Output: c, integer representation of ciphertext
void encrypt(NTL::ZZ& c, const NTL::ZZ& m, const RSAkey& key) {
	PowerMod(c, m, key.e, key.n);
}

// Input: c, integer representation of ciphertext
// key, the RSA private key
// Output: m, integer representation of plaintext
void decrypt(NTL::ZZ& m, const NTL::ZZ& c, const RSAkey& key) {
	if(key.is_private()) {
		PowerMod(m, c, key.d, key.n);
	} else {
		throw KeyError();
	}
}
