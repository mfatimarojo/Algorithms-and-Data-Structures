#include <iostream>
#include <string>
#include "lista.h"
#include "Arbin.h"
#include "pila.h"
#include "cola.h"
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
	cout << "\n";

	l.invierte();

	cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << "\n";
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

template <typename T>
bool coinciden(const Arbin<T> &a, const Lista<T> &pre, typename Lista<T>::ConstIterator &cit) {
	bool coin, coincidenIz, coincidenDer;

	if (a.esVacio()) return true;
	if (cit == pre.cend()) return false;
	
	coin = (a.raiz() == cit.elem());
	cit.next();
	coincidenIz = coinciden(a.hijoIz(), pre, cit);
	coincidenDer = coinciden(a.hijoDer(), pre, cit);

	return (coin && coincidenIz && coincidenDer);
}

template <typename T>
bool coinciden(const Arbin<T> &a, const Lista<T> &pre) {
	Lista<T>::ConstIterator cit = pre.cbegin();
	if (a.esVacio() && pre.esVacia()) return true;
	if ((a.esVacio() && !pre.esVacia()) || (!a.esVacio() && pre.esVacia())) return false;
	return coinciden(a, pre, cit);
}

void ejercicio2() {
	Lista<int> pre;
	//1, 2, 4, 5, 8, 3, 6, 9, 7
	pre.pon_final(1);
	pre.pon_final(2);
	pre.pon_final(4);
	pre.pon_final(5);
	pre.pon_final(8);
	pre.pon_final(3);
	pre.pon_final(6);
	pre.pon_final(9);
	pre.pon_final(7);

	Arbin<int> a;
	while (cin.peek() != EOF) {
		cout << coinciden(leeArbol(cin), pre);
		string restoLinea;
		getline(cin, restoLinea);
		if (cin.peek() != EOF) cout << endl;
	}

}

template <typename T>
void invierteBase(Pila<T> &p, int n) {
	if (p.esVacia()) throw "Es vacia";
	Lista<T> l1, l2;
	int i = 0;
	while (!p.esVacia() && i < n) {
		l1.pon_ppio(p.cima());
		p.desapila();
		i++;
	}
	while (!p.esVacia()) {
		l2.pon_final(p.cima());
		p.desapila();
	}

	while (!l2.esVacia()) {
		p.apila(l2.primero());
		l2.quita_ppio();
	}

	while (!l1.esVacia()) {
		p.apila(l1.primero());
		l1.quita_ppio();
	}
	
}

void ejercicio3() {
	Pila<int> p;
	p.apila(1);
	p.apila(2);
	p.apila(3);
	p.apila(4);
	p.apila(5);
	p.apila(6);

	invierteBase(p, 3);

	while (!p.esVacia()) {
		cout << p.cima() << endl;
		p.desapila();
	}


}

int main() {
	ejercicio3();

	return 0;
}

