#include <iostream>
#include "Arbin.h"
#include "lista.h"
#include "pila.h"
#include "dcola.h"
using namespace std;


template <typename T>
bool coinciden(const Arbin<T> &a, const Lista<T> &pre, typename Lista<T>::Iterator & it) {
	bool coincideR, coindiceI, coindiceD;

	//Casos base
	if (pos == pre.longitud()) return false;
	if (a.esVacio() && pre.esVacia()) return true;
	if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) {
		if (v[pos] == a.raiz())
			return true;
		else return false;
	}
	it.next();
	coincidenR = (a.raiz() == v[pos]);
	coincidenI = coindicen(a.hijoIz(), pre, it);
	coincidenD = coindicen(a.hijoDer(), pre, it);

	return (coincidenR && coincidenI && coincidenD);	
}

template <typename T>
bool coinciden(const Arbin<T> &a, const Lista<T> &pre) {
	int v[1000];
	int i = 0;
	Lista<T>::ConstIterator cit = pre.cbegin();
	while (cit != pre.cend()) {
		v[i] = cit.elem();
		i++;
		cit.next();
	}
	return true;
}

void ejercicio2() {
	Lista<int> pre;
	pre.pon_final(1);
	pre.pon_final(2);
	pre.pon_final(4);
	pre.pon_final(5);
	pre.pon_final(8);
	pre.pon_final(3);
	pre.pon_final(6);
	pre.pon_final(9);
	pre.pon_final(7);

	Arbin<int> a = Arbin<int>(Arbin<int>(4, 2, Arbin<int>(8, 5, NULL)), 1, Arbin<int>(Arbin<int>(9, 6, NULL), 3, 7));
	if (coinciden(a, pre))
		cout << "COINCIDEN\n";
	else cout << "NO COINCIDEN\n";
}

template <typename T>
void invierteBase(Pila<T> &p, int n) {
	int i = 0;
	DCola<T> c1, c2;
	while (i < n) {
		c1.pon_ppio(p.cima());
		p.desapila();
		i++;
	}
	while (!p.esVacia()) {
		c2.pon_final(p.cima());
		p.desapila();
	}

	while (!c2.esVacia()) {
		p.apila(c2.primero());
		c2.quita_ppio();
	}
	while (!c1.esVacia()) {
		p.apila(c1.primero());
		c1.quita_ppio();
	}
}


void ejercicio3() {
	Pila<int> p;
	for (int i = 9; i >= 1; i--) {
		p.apila(i);
	}

	invierteBase(p, 4);

	while (!p.esVacia()) {
		cout << p.cima() << ", ";
		p.desapila();
	}

	cout << "\n";
}

int main() {
	//ejercicio2();
	//ejercicio3();
	system("PAUSE");
	return 0;
}