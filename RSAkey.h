#include <utility>
#include <NTL/ZZ.h>

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
	NTL::ZZ p, q, n, e, d;

	// Construct public key
	RSAkey(NTL::ZZ n, NTL::ZZ e);
	// Construct private key from p, q and e
	RSAkey(std::pair<NTL::ZZ,NTL::ZZ> factors, NTL::ZZ e);
	// Construct private key with n, e and d
	RSAkey(NTL::ZZ n, NTL::ZZ e, NTL::ZZ d);
	bool is_private() const;
};
