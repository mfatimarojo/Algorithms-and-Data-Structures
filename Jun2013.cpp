#include <iostream>
#include "Arbin.h"
using namespace std;

int esEquilibrado(const Arbin<int> &a, bool &equilibrado) {
	int tallaI, tallaD;
	if (a.esVacio()) {
		equilibrado = true;
		return 0;
	}
	if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) {
		equilibrado = true;
		return 1;
	}

	tallaI = esEquilibrado(a.hijoIz(), equilibrado);
	tallaD = esEquilibrado(a.hijoDer(), equilibrado);
	if ((tallaI-tallaD > 1) || (tallaD-tallaI > 1))
		equilibrado = false;
	else equilibrado = true;
	if (tallaI >= tallaD) return tallaI+1;
	else return tallaD+1;
}

bool esEquilibrado(const Arbin<int> &a) {
	bool equilibrado = true;
	esEquilibrado(a, equilibrado);
	return equilibrado;
}

Arbin<int> lee() {
	int r;
	cin >> r;

	if (r == -1)
		return Arbin<int>();

	else {
		Arbin<int> iz = lee();
		Arbin<int> dr = lee();
		return Arbin<int>(iz, r, dr);
	}
}

void ejercicio2() {

	char c;
	cin >> c;
	while (c != 'x') {
		Arbin<int> a = lee();
		if (esEquilibrado(a)) cout << "SI\n";
		else cout << "NO\n";
		cin >> c;
	}
}

int main() {
	ejercicio2();
}
