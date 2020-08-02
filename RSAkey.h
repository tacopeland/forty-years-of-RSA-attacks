#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

class RSAkey {
	// The order of Z/nZ, where n is this key's modulus
	NTL::ZZ phi;	
public:
	/*
	 * p, q: factors of modulus n
	 * n: modulus of RSA key
	 * e: public exponent
	 * d: private exponent
	 */
	NTL::ZZ_p e, d;
	NTL::ZZ p, q, n;

	// Construct public key
	RSAkey(NTL::ZZ n, NTL::ZZ_p e);
	// Construct private key from p, q and e
	RSAkey(NTL::ZZ p, NTL::ZZ q, NTL::ZZ_p e);
	// Construct private key with n, e and d
	RSAkey(NTL::ZZ n, NTL::ZZ_p e, NTL::ZZ_p d);
};

