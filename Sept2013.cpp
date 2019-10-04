#include <iostream>
#include "Arbin.h"
#include "DiccionarioHash.h"
using namespace std;

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


int esZurdo(const Arbin<int> &a, bool &zurdo) {
	bool zI, zD;
	int hI, hD, hmin;

	if (a.esVacio()) {
		zurdo = true;
		return 0;
	}
	if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) {
		zurdo = true;
		return 1;
	}

	hI = esZurdo(a.hijoIz(), zurdo);
	hD = esZurdo(a.hijoDer(), zurdo);

	if (hI < hD) {
		hmin = hI + 1;
		zurdo = false;
	}
	else {
		hmin = hD + 1;
		zurdo = true;
	}

	return hmin;
}

bool esZurdo(const Arbin<int> &a) {
	bool zurdo = true;
	esZurdo(a, zurdo);
	return zurdo;
}

void ejercicio2() {
	Arbin<int> a = lee();

	if (esZurdo(a)) cout << "SI\n";
	else cout << "NO\n";
}


int main() {
	char c;
	cin >> c;
	while (c != 'x') {
		ejercicio2();
		cin >> c;
	}
	return 0;
}
