//============================================================================
// Name        : 2014_Septiembre.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Septiembre 2014
//============================================================================

#include <iostream>
using namespace std;

int minimo(int ini, int fin, int v[]) {
	int dcha, izda;

	if (ini == fin) return v[ini];
	int m = (ini+fin)/2;

	if (v[m]>v[m-1]) return v[m-1];
	else {
		dcha = minimo(m+1,fin,v);
		izda = minimo(ini, m, v);
		if (dcha < izda) return dcha;
		else return izda;
	}
}

/*
 * Vector de N>0 elementos, cuyos valores se han obtenido aplicando una rotación
 * sobre un vector ordenado escrictamente decreciente. Algoritmo que calcule el
 * mínimo del vector con O(log n).  El nº de elementos sobre los que se aplica
 * la rotación para obtener el vector de entrada cumple 0<=elementos rotados<N
 * y no se conoce.
 * Ej.: Vector entrada: 70 55 13 4 100 80 obtenido desplazando los dos primeros
 *      Vector desplazado: 100 80 70 55 13 4
 */
void ejercicio1() {
	//Nos interesa conocer el vector original para tenerlo ordenado y aplciar
	//divide y vencerás
	int v[6] = {70,55,13,4,100,80};
	int w[6] = {4,100,80,70,55,13};
	int N = 6;

	cout << minimo(0,N-1,v) << endl;
	cout << minimo(0,N-1,w) << endl;
}

float sumaNprimeros(int n, float x) {
	int i = 1;
	float suma = 0;
	float potencia = 1;

	while (i < 2*n) {

		suma += potencia*x/i;
		potencia *= x;
		i+=2;
	}

	return suma;

}

/*
 * Sea x un numero real |x|<1 y un entero n>=0, especifica, diseña y verifica o
 * especifica y deriva un algoritmo de O(n) para calcular la suma de los n primeros
 * términos de la serie. Justifica el coste
 */
void ejercicio2() {
	float x;
	int n;

}
int main() {
	ejercicio1();
	ejercicio2();
	return 0;
}
