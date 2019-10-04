//============================================================================
// Name        : 2013_Junio.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Junio 2013
//============================================================================

#include <iostream>
using namespace std;
const int N = 5;

int polinomio(int a[], int N, int x) {
	int suma = 0;
	int i = 0;
	int potencia = 1;

	while (i < N) {
		if (i != 0) { // i = 1 ... N
			potencia *= x;
		}

		suma += a[i]*potencia;
		i++;
	}

	return suma;
}

/*
 * Se tiene un vector a[] de N>=0 enteros que representa los coefincientes de
 * un polinomio. Especificar y derivar, o diseñar y verificar una función
 * iterativa que dado un vector de coeficiente sy un valor de X, devuelva la
 * evaluacion del polinomio. Coste lineal y justificado.
 * Aplicar Reglas de Horner: p(x)= a0 + a1(..an-3 + (an-2 + an-1x)x...)x
 */
void ejercicio1() {
	int a[N]= {2,1,4,3,1};
	int vacio[0];
	int x;
	cout << "x = ";
	cin >> x;

	cout << "Polinomio a[] = " << polinomio(a, N, x) << "\n";
	cout << "Polinomio vacio[] = " << polinomio(vacio, 0, x) << "\n";

}

int inversiones(int ini, int fin, int a[], int N, int &inversiones) {
	if (ini == fin+1) {
		if (v)
	}
}

/*
 * Sea un array de enteros a[], dos números producen inversion si ai > aj
 * pero i < j.  Algoritmo eficiente que calcule el número de inversiones que
 * existen en el array (como mucho O(nlogn)).
 */
void ejercicio3() {
	int vacio[0];
	int uno[1] = {1};
	int cero[10] = {1,2,3,4,5,6,7,8,9,10};
	int a[10] = {1,2,3,5,4,6,7,9,8,10}; //2

	cout << "Inversiones vacio: " << inversiones(vacio,0) << "\n";
	cout << "Inversiones uno: " << inversiones(uno,1) << "\n";
	cout << "Inversiones cero: " << inversiones(cero,10) << "\n";
	cout << "Inversiones a: " << inversiones(a, 10) << "\n";

}

int main() {
	ejercicio1();
	//ejercicio2(); TAD
	ejercicio3();
	return 0;
}
