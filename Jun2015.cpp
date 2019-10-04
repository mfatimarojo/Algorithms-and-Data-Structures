#include <iostream>
#include "lista.h"
#include "Arbin.h"
#include "Faltas.h"
using namespace std;

void ejercicio1() {
	Lista<int> l;
	l.pon_final(1);
	l.pon_final(2);
	l.pon_final(3);
	l.pon_final(4);
	l.pon_final(5);

	Lista<int>::ConstIterator cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << endl;

	l.intercalar();

	cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << endl;
}

int tiempoAyuda(const Arbin<char> &a, int altura) {
	if (a.esVacio()) return 0;

	int tiempoR, tiempoI, tiempoD;

	if (a.raiz() == 'X') tiempoR = 2 * altura;
	else tiempoR = 0;
	
	tiempoI = tiempoAyuda(a.hijoIz(), altura+1);
	tiempoD = tiempoAyuda(a.hijoDer(), altura+1);
	
	return tiempoR + tiempoI + tiempoD;
}

int tiempoAyuda(const Arbin<char> &a) {
	int altura = 0;
	return tiempoAyuda(a, altura);
}

void ejercicio2() {
	//Probar árbol
}

int main() {
	
	return 0;
}