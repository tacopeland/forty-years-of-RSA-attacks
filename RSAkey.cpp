#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include <NTL/ZZXFactoring.h>

#include "RSAkey.h"

using namespace std;
using namespace NTL;


// Create RSA public key from modulus and public exponent
RSAkey::RSAkey (ZZ modulus, ZZ pub_exp) {
	n = modulus;
	e = pub_exp;
}

// Create RSA private key from modulus' factors and public exponent
RSAkey::RSAkey (vector<ZZ> factors, ZZ pub_exp) {
	vector<ZZ>::iterator iter;

	f = factors;
	n = 1;
	for(iter = f.begin(); iter != f.end(); iter++)
		n *= (*iter);

	e = pub_exp;

	// get phi and set it as modulus for e*d = 1 (mod phi)
	phi = 1;
	for(iter = f.begin(); iter != f.end(); iter++)
		phi *= ((*iter) - 1);
	InvMod(d, pub_exp, phi);
}

// Create RSA private key from modulus, public exponent and private exponent
RSAkey::RSAkey (ZZ modulus, ZZ pub_exp, ZZ priv_exp) {
	n = modulus;
	e = pub_exp;
	d = priv_exp;


	// Calculate factors from d
	// Based on a generalization of pycryptodome's implementation:
	// https://github.com/Legrandin/pycryptodome/blob/master/lib/Crypto/PublicKey/RSA.py
	ZZ x, t, g, cand, fac, r;
	vector<ZZ>::iterator iter;
	x = e * d - 1;
	g = 2;

	t = x;
	while(t % 2 == 0) t/=2;

	// r: remaining composite factors
	r = n;

	while(!ProbPrime(r) && g < 100) {
		ZZ k = t;
		while(k < x) {
			PowerMod(cand, g, k, r);
			if(cand != 1 && cand != (r - 1) && SqrMod(cand, r) == 1) {
				fac = GCD(cand + 1, r);
				if(ProbPrime(fac)) {
					f.push_back(fac);
					r = r / fac;
					g = 2;
					break;
				}
			}
			k*=2;
		}
		g += 2;
	}
	if(!ProbPrime(r)) throw domain_error("Unable to compute p and q from d.");

	f.push_back(r);

	// phi = (f1 - 1)*(f2 - 1)*...*(fk - 1) for all k factors of n
	phi = 1;
	for(iter = f.begin(); iter < f.end(); iter++)
		mul(phi, phi, (*iter) - 1);
}

bool RSAkey::is_private() const {
	if (!IsZero(phi)) {
		return true;
	} else {
		return false;
	}
}

ZZ RSAkey::get_param(string param) const {
	char ch = param[0];
	if(param == "phi") {
		// o for order
		ch = 'o';
	}

	switch(ch) {
		case 'n':
			return n;
			break;
		case 'e':
			return e;
			break;
		case 'd':
			return d;
			break;
		case 'o':
			return phi;
			break;
	}
	throw domain_error("Invalid RSA parameter specified!");
}


vector<ZZ> RSAkey::get_factors() const {
	return f;
}
