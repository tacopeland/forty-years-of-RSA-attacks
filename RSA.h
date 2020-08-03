#include <exception>
#include <NTL/ZZ.h>
#include "RSAkey.h"

using namespace std;
using namespace NTL;

// Encrypt/decrypt RSA integer-encoded messages
void encrypt(ZZ& c, const ZZ& m, const RSAkey& key);
void decrypt(ZZ& m, const ZZ& c, const RSAkey& key);

class KeyError : public exception {
public:
	const char * what ();
};
