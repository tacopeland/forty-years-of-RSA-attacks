#include <iostream>
#include <stdexcept>

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

void usage(char *progname) {
	cout << "This program returns the message m corresponding to "
		"two ciphertexts c1 = m^e1 (mod n), c2 = m^e2 (mod n)."
		<< endl;
	cout << "Usage: " << progname << " n e1 c1 e2 c2" << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 6) { usage(argv[0]); return 3; }

	ZZ n, e1, c1, e2, c2, m, u, v, g;
	n = conv<ZZ>(argv[1]);
	e1 = conv<ZZ>(argv[2]);
	c1 = conv<ZZ>(argv[3]);
	e2 = conv<ZZ>(argv[4]);
	c2 = conv<ZZ>(argv[5]);

	// g = u*e1 + v*e2
	XGCD(g, u, v, e1, e2);

	if(g != 1) { throw domain_error("e1 and e2 aren't coprime."); }

	if(u < 0) {
		InvMod(c1, c1, n);
		u *= -1;
	}
	if(v < 0) {
		InvMod(c2, c2, n);
		v *= -1;
	}

	MulMod(m, PowerMod(c1, u, n), PowerMod(c2, v, n), n);

	cout << m << endl;
}
