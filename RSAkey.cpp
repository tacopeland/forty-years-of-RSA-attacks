#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
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
RSAkey::RSAkey (pair<ZZ,ZZ> factors, ZZ pub_exp) {
	p = factors.first;
	q = factors.second;
	n = p * q;
	e = pub_exp;

	// get phi and set it as modulus for e*d = 1 (mod phi)
	phi = (p-1) * (q-1);
	ZZ_pPush push(phi);
	d = conv<ZZ>(1/conv<ZZ_p>(pub_exp));
}

// Create RSA private key from modulus, public exponent and private exponent
RSAkey::RSAkey (ZZ modulus, ZZ pub_exp, ZZ priv_exp) {
	n = modulus;
	e = pub_exp;
	d = priv_exp;


	// Calculate p and q from d
	// Based on Pycryptodome's implementation, which is based on Rabin 1979:
	// https://github.com/Legrandin/pycryptodome/blob/master/lib/Crypto/PublicKey/RSA.py
	ZZ x, t, p, q, g, cand;
	x = e * d - 1;
	g = 2;

	t = x;
	while(t % 2 == 0) t/=2;

	bool spotted = false;
	while(!spotted && g < 100) {
		ZZ k = t;
		while(k < x) {
			PowerMod(cand, g, k, n);
			if(cand != 1 && cand != (n - 1) && SqrMod(cand, n) == 1) {
				p = GCD(cand + 1, n);
				spotted = true;
				break;
			}
			k*=2;
		}
		g += 2;
	}
	if(!spotted) throw domain_error("Unable to compute p and q from d.");

	q = n / p;
	// phi = (p-1)*(q-1)
	mul(phi, p-1, q-1);
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
		case 'p':
			return p;
			break;
		case 'q':
			return q;
			break;
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
