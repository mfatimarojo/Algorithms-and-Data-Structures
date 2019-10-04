//============================================================================
// Name        : 2012_Septiembre.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Septiembre 2012
//============================================================================

#include <iostream>
using namespace std;

/*
 * { Pre = 0<N<=longitud(v) }
 */
int repeticionesMinimo(int v[], int N) {
	int menor = v[0];
	int cont = 1;
	int i  = 1;

	/*
	 * { I = cont = #i: 1<=i<=N: v[i] = minimo(v,N)
	 */
	while (i < N) {
		if (v[i] == menor) cont++;
		else if (v[i] < menor) {
			menor = v[i];
			cont = 1;
		}
		i++;
	}

	return cont;
}
/*
 *  minimo(v,N) = Min i: 0<=i<N: v[i]
 * { cont = #i: 0<=i<N: v[i] = minimo(v,N) }
 */

/*
 * Especificar y deriviar o diseñar y verificar algoritmo iterativo de coste
 * lineal, que reciba un vector no vacío de enteros que calcule en una sola
 * pasada el número de veces que aparece repetido su elemento menor.
 */
void ejercicio1() {
	int v[10] = {5,7,6,3,1,10,1,1,2,10};
	int N = 10;

	cout << repeticionesMinimo(v,N) << endl;
}

int main() {
	ejercicio1();
	return 0;
}
