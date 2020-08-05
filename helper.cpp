#include "helper.h"

using namespace std;
using namespace NTL;

ZZ phi_from_params(ZZ n, ZZ e, ZZ d) {
	// We must calculate phi from d
	ZZ k, phi;
	div(k, e*d - 1, n);
	div(phi, e*d - 1, k);
	while (phi*k != e*d - 1) {
		++k;
		div(phi, e*d - 1, k);
	}

	// TODO
	// Now we have a multiple of phi, we must reduce it to phi

	return phi;
}
