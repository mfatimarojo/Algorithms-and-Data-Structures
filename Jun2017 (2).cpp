#include <iostream>
#include "lista.h"
#include "Arbin.h"
using namespace std;

void ejercicio1() {
	Lista<int> l, l2;
	l.pon_final(1);
	l.pon_final(2);


	l2.pon_final(1);
	l2.pon_final(2);
	l2.pon_final(3);

	l.diferencia(l2);

	Lista<int>::ConstIterator cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
}

void whiteJacket(Arbin<int> a, int puntuacion, int &mejorPuntuacion, int jugadas, Lista<bool> secuencia, Lista<bool> &mejorJugada) {

	if (a.esVacio()) return;
	
	puntuacion += a.raiz() - jugadas;
	jugadas++;

	if (puntuacion > mejorPuntuacion) {
		mejorPuntuacion = puntuacion;
		mejorJugada = secuencia;
	}
	if (!a.hijoIz().esVacio()) {
		secuencia.pon_final(false);
		whiteJacket(a.hijoIz(), puntuacion, mejorPuntuacion, jugadas, secuencia, mejorJugada);
		secuencia.quita_final();
	}
	if (!a.hijoDer().esVacio()) {
		secuencia.pon_final(true);
		whiteJacket(a.hijoDer(), puntuacion, mejorPuntuacion, jugadas, secuencia, mejorJugada);
		secuencia.quita_final();
	}

}

Lista<bool> mejorPuntuacionSecuencia(const Arbin<int> &a) {
	int jugadas = 0;
	int puntuacion = 0;
	int mejorPuntuacion = 0;
	Lista<bool> secuencia;
	Lista<bool> mejorJugada;
	whiteJacket(a, puntuacion, mejorPuntuacion, jugadas, secuencia, mejorJugada);
	return mejorJugada;
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
	
	Arbin<int> a = lee();
	Lista<bool> lista = mejorPuntuacionSecuencia(a);
	Lista<bool>::ConstIterator cit = lista.cbegin();

	while (cit != lista.cend()) {
		if (cit.elem()) cout << "true, ";
		else cout << "false, ";
		cit.next();
	}

}

int main() {
	ejercicio2();
	return 0;
}