#include <exception>
#include <NTL/ZZ.h>
#include "RSAkey.h"

using namespace std;
using namespace NTL;

// Encrypt/decrypt RSA integer-encoded messages
void encrypt(ZZ& c, const ZZ& m, const RSAkey& key);
void decrypt(ZZ& m, const ZZ& c, const RSAkey& key);

// Encrypt/decrypt as hex-encoded strings
std::string encrypt(std::string pt, RSAkey key);
std::string decrypt(std::string ct, RSAkey key);

class KeyError : public exception {
public:
	const char * what ();
};
