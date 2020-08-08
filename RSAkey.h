#include <string>
#include <utility>
#include <vector>

#include <NTL/ZZ.h>

class RSAkey {
protected:
	// The order of Z/nZ, where n is this key's modulus
	NTL::ZZ phi;	

	/*
	 * f: factors of modulus n
	 * n: modulus of RSA key
	 * e: public exponent
	 * d: private exponent
	 */
	std::vector<NTL::ZZ> f;
	NTL::ZZ n, e, d;
public:
	// Construct public key
	RSAkey(NTL::ZZ n, NTL::ZZ e);
	// Construct private key from p, q and e
	RSAkey(std::vector<NTL::ZZ> factors, NTL::ZZ e);
	// Construct private key with n, e and d
	RSAkey(NTL::ZZ n, NTL::ZZ e, NTL::ZZ d);
	bool is_private() const;
	NTL::ZZ get_param(std::string param) const;
	std::vector<NTL::ZZ> get_factors() const;
};
