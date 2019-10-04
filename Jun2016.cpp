#include <iostream>
#include <string>
#include "Arbin.h"
#include "lista.h"
using namespace std;

int numeroTramosNavegables(const Arbin<int>& cuenca, int &tramos) {
	int caudal, caudalIz, caudalDer;

	if (cuenca.esVacio()) return 0;
	if (cuenca.hijoIz().esVacio() && cuenca.hijoDer().esVacio()) return 1;

	caudalIz = numeroTramosNavegables(cuenca.hijoIz(), tramos);
	caudalDer = numeroTramosNavegables(cuenca.hijoDer(), tramos);

	if (caudalIz >= 3) tramos++;
	if (caudalDer >= 3) tramos++;

	caudal = caudalIz + caudalDer + cuenca.raiz();

	if (caudal < 0) caudal = 0;
	
	return caudal;
}

int numeroTramosNavegables(const Arbin<int>& cuenca) {
	int tramos = 0;
	numeroTramosNavegables(cuenca, tramos);
	return tramos-1;
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

void ejercicio1() {
	Arbin<int> cuenca;
	while (cin.peek() != EOF) {
		cout << numeroTramosNavegables(leeArbol(cin));
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}
}

void ejercicio2() { //FALTAN CASOS BASE
	Lista<int> l;
	l.pon_final(12);
	l.pon_final(15);
	l.pon_final(15);
	l.pon_final(15);
	l.pon_final(16);

	Lista<int>::ConstIterator cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << endl;
	l.sumarUno(1);
	cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	
}

int main() {
	//ejercicio2();
	return 0;
}