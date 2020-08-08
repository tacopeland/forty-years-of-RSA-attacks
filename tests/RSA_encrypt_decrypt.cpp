#include "RSA.h"

using namespace std;
using namespace NTL;

bool test_enc(RSAkey k, ZZ m, ZZ c) {
	ZZ c_test;
	try {
		encrypt(c_test, m, k);
		if(c_test == c) {
			return true;
		} else {
			return false;
		}
	} catch (KeyError &e) {
		cerr << "FAILURE" << endl;
		return false;
	}
}

bool test_dec(RSAkey k, ZZ c, ZZ m) {
	ZZ m_test;
	try {
		decrypt(m_test, c, k);
		if(m_test == m) {
			return true;
		} else {
			return false;
		}
	} catch (KeyError &e) {
		cerr << "FAILURE" << endl;
		return false;
	}
}


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

	// Test key for multiprime RSA
	ZZ mp_n, mp_e, mp_d;
	mp_n = conv<ZZ>("40819639062101631588694143678246914514489668029094746381933377804693715827874234988862201862604222401582538865467384551249021821438262867745473692818524218485533483750359641615877985712440623031092705879337345135074136038900217975042537211482586644833695000425543568699528079213315992395305542710539566890973");
        mp_e = conv<ZZ>("831967");
        mp_d = conv<ZZ>("7758099741669602508353691176082415067755885434610790979934889033828896208962881363480631546893399228720072273965873160745299524739277374159352394228102035924151505153527262855324474930253653568576885858653818113713496950740814870901899703226228524724854960738317867675412369910142650722255396895273769257503");

	ZZ mp_m = conv<ZZ>("99999999999999999999999999999999999999");
	ZZ mp_c = conv<ZZ>("30110887348948624559096951728105256050873638945388716556918163236340102214334341209407368539781661176811725420581845727513324373142023343653578761852407155716040581193717100421952411166431747958344179762583335852405981466953140306277583550182944114085448166492161621495319330453684755050920140150202205645519");


	cout << "[*] Test encryption given RSA public key:" << endl;
	RSAkey pubkey {n, e};
	if(test_enc(pubkey, m, c)) {
		cout << "SUCCESS" << endl;
	}

	cout << "[*] Test decryption given RSA public key "
		"(shouldn't work):" << endl;
	if(test_dec(pubkey, c, m)) {
		cout << "SUCCESS" << endl;
	}
	cout << endl;


	cout << "[*] Test decryption given RSA private key:" << endl;
	RSAkey privkey {n, e, d};
	if(test_dec(privkey, c, m)) {
		cout << "SUCCESS" << endl;
	}
	cout << endl;


	cout << "[*] Test encryption given multiprime RSA public key:" << endl;
	pubkey = {mp_n, mp_e};
	if(test_enc(pubkey, mp_m, mp_c)) {
		cout << "SUCCESS" << endl;
	}

	cout << "[*] Test decryption given multiprime RSA private key:" << endl;
	privkey = {mp_n, mp_e, mp_d};
	if(test_dec(privkey, mp_c, mp_m)) {
		cout << "SUCCESS" << endl;
	}

	cout << "[*] Test decryption given multiprime RSA public key "
		"(shouldn't work):" << endl;
	privkey = {mp_n, mp_e};
	if(test_dec(privkey, mp_c, mp_m)) {
		cout << "SUCCESS" << endl;
	}
}
