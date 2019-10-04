#include <iostream>
#include "Arbin.h"
using namespace std;

bool arbolGenealogicoCorrecto(const Arbin<int> &a, int &generaciones) {
	bool correcto = true;
	bool coincideI, coincideD;
	if (a.esVacio()) return true;
	else if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) {
		return true;
	}
	else if (!a.hijoIz().esVacio() && !a.hijoDer().esVacio()) {
		if ((a.raiz() >= a.hijoIz().raiz() + 18) &&
			(a.hijoIz().raiz() >= a.hijoDer().raiz() + 2))
			correcto = true;
		else correcto = false;
		generaciones++;
	}
	
	coincideI = arbolGenealogicoCorrecto(a.hijoIz(), generaciones);
	coincideD = arbolGenealogicoCorrecto(a.hijoDer(), generaciones);
	
	return correcto &&coincideI && coincideD;

}

int arbolGenealogicoCorrecto(const Arbin<int> &a) {
	if (a.esVacio()) return 0;
	else if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) return 1;
	else {
		int generaciones = 0;
		if (arbolGenealogicoCorrecto(a, generaciones)) return generaciones;
		else return -1;
	}
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

void ejercicio1() {
	//Probar Arbol
	//...
	Arbin<int> a = lee();
	int result = arbolGenealogicoCorrecto(a);
	if (result != -1) cout << "Arbol genealogico correcto " << result << " generaciones\n";
	else cout << "Arbol genealogico incorrecto\n";

}

int main() {
	ejercicio1();
	return 0;
}




