#include "Arbin.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int tramosNavegables(const Arbin<int> &arbol, int &tramos) {
	int caudal = 0, caudalIz = 0, caudalDr = 0;

	if (arbol.esVacio())
		return 0;
	if (arbol.hijoIz().esVacio() && arbol.hijoDer().esVacio())
		return 1;

	caudalIz += tramosNavegables(arbol.hijoIz(), tramos);
	caudalDr += tramosNavegables(arbol.hijoDer(), tramos);
	caudal += caudalIz + caudalDr + arbol.raiz();

	if (caudal >= 3) tramos++;
	else if (caudal < 0) caudal = 0;

	return caudal;

}

int numeroTramosNavegables(const Arbin<int>& cuenca) {
	int tramos = 0;
	tramosNavegables(cuenca, tramos);
	return (tramos-1);
}

Arbin<int> leeArbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = leeArbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = leeArbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

int main() {
	Arbin<int> cuenca;
	while (cin.peek() != EOF) {
		cout << numeroTramosNavegables(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}



