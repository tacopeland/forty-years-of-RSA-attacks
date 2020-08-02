#include "RSAkey.h"

using namespace std;
using namespace NTL;

int main() {
	// Test key
	ZZ p, q, n;
	ZZ_p e, d;
	p = conv<ZZ>("56244518227433");
	q = conv<ZZ>("22208577958531841");
	n = conv<ZZ>("1249110767794010895540410194153");
	// Apply modulus for params in ZZ(n)
	ZZ_pPush push(n);
	e = conv<ZZ_p>("65537");
	d = conv<ZZ_p>("205119704640110252892051812353");

	cout << "Testing RSA public key construction." << endl;
	RSAkey pubkey = RSAkey(n, e);
	cout << "Pubkey params:\nn = " << pubkey.n << "\ne = " <<
		pubkey.e << endl;
	
	cout << "Testing RSA private key construction given"
		"p, q and e." << endl;
	RSAkey privkey = RSAkey(p, q, e);
	cout << "Privkey params:" << endl;
	cout << "p = " << privkey.p << endl;
	cout << "q = " << privkey.q << endl;
	cout << "n = " << privkey.n << endl;
	cout << "e = " << privkey.e << endl;
	cout << "d = " << privkey.d << endl;

	cout << "Testing RSA private key construction given"
		"n, e and d." << endl;
	privkey = RSAkey(n, e, d);
	cout << "Privkey params:" << endl;
	cout << "p = " << privkey.p << endl;
	cout << "q = " << privkey.q << endl;
	cout << "n = " << privkey.n << endl;
	cout << "e = " << privkey.e << endl;
	cout << "d = " << privkey.d << endl;
}
