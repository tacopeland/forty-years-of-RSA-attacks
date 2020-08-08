#include <iostream>

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

void usage(char *progname) {
	cout << "This program returns the factors p and q of "
		"n if p - q < n^(1/4)."
		<< endl;
	cout << "Usage: " << progname << " n" << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 2) { usage(argv[0]); return 3; }

	ZZ n, a, b, p, q;
	n = conv<ZZ>(argv[1]);

	// p = floor(SqrRoot(n))
	SqrRoot(a, n);
	// q = p*p - n
	sqr(b, a);
	b -= n;

	while(b < 0 || sqr(SqrRoot(b)) != b) {
		a++;
		sqr(b, a);
		b -= n;
	}

	p = a - SqrRoot(b);
	q = n / p;

	cout << p << endl << q << endl;
}
