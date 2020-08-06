#include <iostream>
#include <unordered_map>

#include <NTL/ZZ.h>

#include "RSA.h"

using namespace std;
using namespace NTL;

void usage(char *progname) {
	cout << "This program returns the private exponent `d` of the "
		"public key <n, e2> given the secret key <n, e', d'>."
		<< endl;
	cout << "Usage: " << progname << " n e' d' e" << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 5) { usage(argv[0]); return 3; }

	ZZ n, e1, d1, e2, d2, phi;
	n = conv<ZZ>(argv[1]);
	e1 = conv<ZZ>(argv[2]);
	d1 = conv<ZZ>(argv[3]);
	e2 = conv<ZZ>(argv[4]);

	RSAkey k1 = RSAkey(n, e1, d1);
	phi = k1.get_param("phi");

	// d2 = e2^(-1) (mod phi)
	InvMod(d2, e2, phi);

	RSAkey k2 = RSAkey(n, e2, d2);
	cout << k2.get_param("d") << endl;
}
