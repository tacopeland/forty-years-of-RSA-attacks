#include <iostream>

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

/*
 * This program calculates a blinded message from m and from its
 * signature S' calculates S, the signature of m.
 */

int main() {
	ZZ m, e, n, blind_m, blind_S, S, r;
	r = 2;

	cout << "m> ";
	cin >> m;
	cout << "e> ";
	cin >> e;
	cout << "n> ";
	cin >> n;

	// m' = m*r^e (mod n)
	mul(blind_m, m, PowerMod(r, e, n));
	cout << "m': " << blind_m << endl << endl;

	cout << "S'> ";
	cin >> blind_S;

	// S = S' * r^(-1)
	MulMod(S, blind_S, InvMod(r, n), n);

	cout << "S: " << S << endl;
}
