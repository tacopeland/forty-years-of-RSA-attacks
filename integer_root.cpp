#include <iostream>
#include <stdlib.h>

#include <gmpxx.h>
#include <NTL/ZZ.h>

using namespace std;

void usage(char *progname) {
	cout << "This program finds m given m^e and e, as long as "
		"m^e < n." << endl;
	cout << "Usage: " << progname << " c e" << endl;
}


int main(int argc, char *argv[]) {
	if (argc != 3) { usage(argv[0]); return 3; }

	// NTL doesn't provide an integer root function, so we
	// have to use GMP integers
	mpz_class c, root;
	mpz_t r;
	mpz_init(r);
	if(c.set_str(argv[1],0)) {
		cerr << "Invalid message: " << argv[1] << endl;
		return 2;
	}

	unsigned long e;
	if(!(e = strtoul(argv[2], NULL, 0))) {
		cerr << "Invalid public exponent: " << argv[2] << endl;
		return 2;
	}

	
	// Find c^(1/e)
	if(!mpz_root(r, c.get_mpz_t(), e)) {
		cerr << "Error: m^e is greater than n!" << endl;
		return 1;
	} else {
		cout << mpz_class(r) << endl;
	}
}
