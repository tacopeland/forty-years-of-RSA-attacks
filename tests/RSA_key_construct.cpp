#include "RSAkey.h"

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


	// Test multiprime key
	ZZ mp_n, mp_e, mp_d;
	vector<ZZ> mp_factors =
		{ conv<ZZ>("249865244393411314234791423742541805187"),
		conv<ZZ>("309967212964580479417663683172660732009"),
		conv<ZZ>("301737532791554850228004586774223060371"),
		conv<ZZ>("312052391054074278147971316298809925703"),
		conv<ZZ>("218660873147927218425085262778129431531"),
		conv<ZZ>("248965425646809640951629022899521547497"),
		conv<ZZ>("306141915423507907143676073932826591737"),
		conv<ZZ>("335859616843551599331414013633639745393") };
	mp_n = conv<ZZ>("40819639062101631588694143678246914514489668029094746381933377804693715827874234988862201862604222401582538865467384551249021821438262867745473692818524218485533483750359641615877985712440623031092705879337345135074136038900217975042537211482586644833695000425543568699528079213315992395305542710539566890973");
	mp_e = conv<ZZ>("831967");
	mp_d = conv<ZZ>("7758099741669602508353691176082415067755885434610790979934889033828896208962881363480631546893399228720072273965873160745299524739277374159352394228102035924151505153527262855324474930253653568576885858653818113713496950740814870901899703226228524724854960738317867675412369910142650722255396895273769257503");
	// mp_phi = 40819639062101631588694143678246914513323008419934202319749875569544562377671807334405652509924366477280532560646624732331899480772836032602888487173014296060690829157641670962647433211686807645287853664680696516688866303341619292063348492897988053716518935509139154679992683858233836489815811770469839667200


	cout << "Testing RSA public key construction." << endl;
	RSAkey pubkey = RSAkey(n, e);
	cout << "Pubkey params:\nn = " << pubkey.get_param("n") << endl
		<< "e = " << pubkey.get_param("e") << endl;

	cout << "Testing RSA private key construction given"
		"p, q and e." << endl;
	RSAkey privkey = RSAkey(vector<ZZ>{p, q}, e);
	cout << "Privkey params:" << endl;
	cout << "Factors:" << endl;
	vector<ZZ> factors = privkey.get_factors();
	vector<ZZ>::iterator iter;
	for(iter = factors.begin(); iter < factors.end(); iter++)
		cout << (*iter) << endl;
	cout << "n = " << privkey.get_param("n") << endl;
	cout << "e = " << privkey.get_param("e") << endl;
	cout << "d = " << privkey.get_param("d") << endl;
	
	cout << "Testing RSA private key construction given "
		"n, e and d." << endl;
	privkey = RSAkey(n, e, d);
	cout << "Privkey params:" << endl;
	factors = privkey.get_factors();
	for(iter = factors.begin(); iter < factors.end(); iter++)
		cout << (*iter) << endl;
	cout << "n = " << privkey.get_param("n") << endl;
	cout << "e = " << privkey.get_param("e") << endl;
	cout << "d = " << privkey.get_param("d") << endl;


	cout << "Testing multiprime RSA private key construction "
		"given factors and a public exponent." << endl;
	privkey = RSAkey(mp_factors, mp_e);
	cout << "Privkey params:" << endl;
	factors = privkey.get_factors();
	for(iter = factors.begin(); iter < factors.end(); iter++)
		cout << (*iter) << endl;
	cout << "n = " << privkey.get_param("n") << endl;
	cout << "e = " << privkey.get_param("e") << endl;
	cout << "d = " << privkey.get_param("d") << endl;

	cout << "Testing multiprime RSA private key construction "
		"given n, e and d." << endl;
	privkey = RSAkey(mp_n, mp_e, mp_d);
	cout << "Privkey params:" << endl;
	factors = privkey.get_factors();
	for(iter = factors.begin(); iter < factors.end(); iter++)
		cout << (*iter) << endl;
	cout << "n = " << privkey.get_param("n") << endl;
	cout << "e = " << privkey.get_param("e") << endl;
	cout << "d = " << privkey.get_param("d") << endl;

}
