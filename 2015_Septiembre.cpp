//============================================================================
// Name        : 2015_Septiembre.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Septiembre 2015
//============================================================================

#include <iostream>
using namespace std;

typedef struct {
	int i;
	int j;
} Posicion;

/*
 * n	0	1	2	3	4	5	6	7
 * 		0	1	1	3	5	11	21	43
 *
 */

int Jacobsthal(int n) {
	int x = 0;
	int i = 0;
	int v[n];

	while (i <= n) {
		if (i == 0 || i == 1) {
			v[i] = i;
			x = i;
		} else {
			v[i] = v[i - 1] + 2 * v[i - 2];
			x = v[i];
		}

		i++;
	}

	return x;
}

/*
 * Diseñar y verificar (o derivar) un algoritmo iterativo que dado un n>=0
 * calcule J(n) en tiempo O(n). Justificar el coste
 * J(0) = 0
 * J(1) = 1
 * J(n) = J(n-1) + 2*J(n-2) si n>1
 */
void ejercicio1() {
	int n;
	cin >> n;

	cout << Jacobsthal(n) << endl;
}

Posicion encuentraPosicion(int matriz[][4], int iniN, int finN, int iniM,
		int finM) {
	Posicion p;

	int mN = (iniN + finN) / 2;
	int mM = (iniM + finM) / 2;

	if (matriz[mN][mM] == 0) {
		encuentraPosicion(matriz, mN, finN, mM + 1, finM);
		encuentraPosicion(matriz, mN + 1, finN, mM, finM);
	} else {
		encuentraPosicion(matriz, iniN, mN, iniM, mM-1);
		encuentraPosicion(matriz, iniN, mN-1, iniM, mM);
	}

	return p;
}

/*
 * Matriz NxM. Hay un rectángulo de 1s a partir de una posición desconocida
 * hasta la posición (N-1,M-1). El resto son 0s. Implementa un algoritmo
 * eficiente que encuentre dicha posición.
 */
void ejercicio2() {
	int N = 5;
	int M = 4;
	int matriz[5][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 1,
			1, 1 }, { 0, 1, 1, 1 } };
	int iniN = 0, finN = N - 1;
	int iniM = 0, finM = M - 1;
	Posicion p = encuentraPosicion(matriz, iniN, finN, iniM, finM, N, M);
}

int main() {
	ejercicio1();
	ejercicio2();
	return 0;
}
