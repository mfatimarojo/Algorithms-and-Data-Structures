#include <iostream>
#include <string>
#include "lista.h"
#include "Arbin.h"
using namespace std;


class ENaveExiste {};



void ejercicio1() {
	Lista<int> l;
	l.pon_final(1);
	l.pon_final(2);
	l.pon_final(3);
	l.pon_final(4);
	l.pon_final(5);

	l.inserta(10, 4);

	Lista<int>::ConstIterator cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << endl;

	l.inserta(10, 0);
	cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << endl;

	l.inserta(10, 7);
	cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << endl;

	Lista<int> l2;
	l2.inserta(10, 0);
	cit = l2.cbegin();
	while (cit != l2.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << endl;

}

Arbin<char> lee() {
	int r;
	cin >> r;

	if (r == '#')
		return Arbin<char>();

	else {
		Arbin<char> iz = lee();
		Arbin<char> dr = lee();
		return Arbin<char>(iz, r, dr);
	}
}

/*int dragones(const Arbin<char> &a, int drag, char id, char &idF) {
	int dragI, dragD, idI, idD;

	if (a.esVacio()) return drag;
	if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) {
		idF = a.raiz();
		return drag;
	}

	if (a.raiz() == 'D') drag++;
	dragI = dragones(a.hijoIz(), drag, idI, idF);
	dragD = dragones(a.hijoDer(), drag, idD, idF);

	if (dragI <= dragD) {
		idF = idI;
		return dragI;
	}
	else {
		idF = idD;
		return dragD;
	}
	
	

	return drag;

}


char dragones(const Arbin<char> &a) {
	char id;

	return id;
}

void ejercicio2() {
	Arbin<char> a = lee();

	cout << dragones(a) << endl;
}*/




int main() {
	//ejercicio1();
	
	return 0;
}

