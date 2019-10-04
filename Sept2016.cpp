#include <iostream>
#include "lista.h"
using namespace std;

void ejercicio1() {
	//Faltan casos base: si v1 = ultimo, si v2 = primero, si v3 = ultimo...
	Lista<char> l1, l2;
	l1.pon_final('A');
	l1.pon_final('B');
	l1.pon_final('C');
	l1.pon_final('D');

	l2.pon_final('Z');
	l2.pon_final('Y');
	l2.pon_final('M');
	l2.pon_final('N');
	l2.pon_final('T');
	l2.pon_final('H');
	l2.pon_final('L');
	l2.pon_final('J');

	l1.splice(l2, 'D', 'N', 'H');

	Lista<char>::ConstIterator cit = l1.cbegin();
	while (cit != l1.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
	cout << "\n";

	cit = l2.cbegin();
	while (cit != l2.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}
}

void ejercicio2() {

}

int main() {
	ejercicio2();

	return 0;
}