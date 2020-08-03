#include "RSA.h"

using namespace std;
using namespace NTL;

int main() {
	// Test key
	ZZ p, q, n, e, d;
	p = conv<ZZ>("56244518227433");
	q = conv<ZZ>("22208577958531841");
	n = conv<ZZ>("1249110767794010895540410194153");
	e = conv<ZZ>("65537");
	d = conv<ZZ>("205119704640110252892051812353");

	ZZ m = conv<ZZ>("3735928559");
	ZZ c = conv<ZZ>("691735209687311506784722696250");

	cout << "[*] Test encryption given RSA public key:" << endl;
	RSAkey pubkey {n, e};
	ZZ c_test;
	encrypt(c_test, m, pubkey);
	cout << "Actual ciphertext: " << c << endl;
	cout << "Calculated ciphertext: " << c_test << endl << endl;

	cout << "[*] Test decryption given RSA public key"
		"(shouldn't work):" << endl;
	ZZ m_test;
	try {
		decrypt(m_test, c, pubkey);
	} catch (KeyError &e) {
		cerr << "[!!] Error: " << e.what() << endl;
	}
	cout << endl;

	cout << "[*] Test decryption given RSA private key:" << endl;
	m_test = 0;
	RSAkey privkey {n, e, d};
	try {
		decrypt(m_test, c, privkey);
		cout << "Actual plaintext: " << m << endl;
		cout << "Calculated plaintext: " << m_test << endl;
	} catch (KeyError &e) {
		cerr << "[!!] Error: " << e.what() << endl;
	}

}
