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

	// We must calculate phi from d
	ZZ k = (e*d - 1)/n;
	phi = (e*d - 1)/k;
	while (phi*k != e*d - 1) {
		++k;
		phi = (e*d - 1)/k;
	}

	// From d and phi we can calculate p and q
	// x^2 - ((n - phi) + 1)*x + n == 0 => x=p || x=q
	ZZX pol;
	Vec< Pair< ZZX, long > > factors;

	SetCoeff(pol, 2, 1);
	SetCoeff(pol, 1, (n - phi) + 1);
	SetCoeff(pol, 0, n);

	ZZ c;
	factor(c, factors, pol);
	p = factors[0].a[0];
	q = factors[1].a[0];
}

bool RSAkey::is_private() const {
	if (!IsZero(phi)) {
		return true;
	} else {
		return false;
	}
}
