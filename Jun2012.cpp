#include <iostream>
#include "diccionario.h"
using namespace std;

int main() {
	Diccionario<int, int> arbol;
	arbol.inserta(10, 0);
	arbol.inserta(20, 0);
	arbol.inserta(5, 0);
	arbol.inserta(1, 0);
	arbol.inserta(7, 0);
	arbol.inserta(15, 0);
	arbol.inserta(19, 0);
	arbol.inserta(25, 0);
	arbol.inserta(22, 0);
	arbol.inserta(30, 0);
	arbol.inserta(18, 0);

	int n = arbol.siguienteMayor(20);
	cout << n << endl;
	return 0;
}