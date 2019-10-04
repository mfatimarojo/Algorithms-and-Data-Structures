#include <iostream>
#include "lista.h"
using namespace std;

int main() {
	Lista<int> l;
	l.pon_final(1);
	l.pon_final(2);
	l.pon_final(3);
	l.pon_final(5);
	l.pon_final(6);

	l.inserta(0, 9);

	Lista<int>::ConstIterator cit = l.cbegin();
	while (cit != l.cend()) {
		cout << cit.elem() << " ";
		cit.next();
	}

	system("PAUSE");
	return 0;
}