#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZX.h>
#include <NTL/ZZXFactoring.h>
#include "RSA.h"

using namespace std;
using namespace NTL;


RSA_key::RSA_key (ZZ modulus, ZZ_p pub_exp) {
	n = modulus;
	e = pub_exp;
}

// f1, f2 are the factors of the modulus
RSA_key::RSA_key (ZZ f1, ZZ f2, ZZ_p pub_exp) {
	p = f1;
	q = f2;
	n = p * q;
	e = pub_exp;

	// get phi and set it as modulus for e*d = 1 (mod phi)
	phi = (p-1) * (q-1);
	ZZ_pPush push(phi);
	d = 1/pub_exp;
}

RSA_key::RSA_key (ZZ modulus, ZZ_p pub_exp, ZZ_p priv_exp) {
	n = modulus;
	e = pub_exp;
	d = priv_exp;

	// We must calculate phi from d
	ZZ k = (conv<ZZ>(e) * conv<ZZ>(d) - 1)/n;
	phi = (conv<ZZ>(e) * conv<ZZ>(d) - 1)/k;
	while (phi * k != conv<ZZ>(e) * conv<ZZ>(d) - 1) {
		++k;
		phi = (conv<ZZ>(e) * conv<ZZ>(d) - 1)/k;
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
