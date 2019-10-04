//============================================================================
// Name        : 2016_Junio.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Junio 2016
//============================================================================

#include <iostream>
using namespace std;

const int N = 6;
const int M = 4;

/*
 * {Pre = 0<=N<=longitud(v)=longitud(w) ^ N/2<=M<=N ^ esCrecience(v) ^ esCreciente(w)}
 */
bool contiene(int v[], int w[]) {
	int i = 0;
	int j = 0;
	int b = false;

	/*
	 * { I = b = (Aj: 0<=j<=m: w[j], Ei: 0<=i<=n: v[i]=w[j])
	 */
	while (j < M && i < N && w[j] >= v[i]) {
		if (w[j] == v[i]) {
			i++;
			j++;
		}
		else i++;
	}

	if (j == M) b = true;
	else b= false;

	return b;
}
/*
 * {Pos = b = (Aj: 0<=j<m: w[j], Ei: 0<=i<n: v[i]=w[j]) }
 */

/*
 * Array v y w ordenados estrictamente creciente, y n y m tal que n/2 <= m <= n
 * Determinar si todos los elementos d w entre 0 y m-1 están contenidos en las
 * posiciones 0...n-1 de v. Especificar, diseñar + ivariante. Indicar el coste
 */
void ejercicio1() {
	int v[N] = { 1, 2, 3, 4, 5, 6 };
	int w[N] = { 1, 3, 5, 6, 8, 10 };
	int si[N] = { 3, 4, 5, 6, 15, 16 };
	int no[N] = { 1, 3, 7, 8, 9, 10 };
	int tmp[N] = { 7, 8, 9, 10, 11, 12 };

	if (contiene(v, w)) {
		cout << "v contiene los M-1 elementos de w\n";
	}
	if (contiene(v, si)) {
			cout << "v contiene los M-1 elementos de si\n";
	}
	if (contiene(v, no)) {
		cout << "v contiene los M-1 elementos de no\n";
	}
	if (contiene(v, tmp)) {
		cout << "v contiene los M-1 elementos de tmp\n";
	}

}

int terminoPerdido(int ini, int fin, int v[], int d) {
	int m = (ini+fin)/2;
	int toca = v[0] + m*d; //pos = 2 --> v[pos]==6

	if (ini == fin) return toca;
	else {
		if (toca < v[m]) {
			return terminoPerdido(ini, m, v, d);
		}
		else return terminoPerdido(m+1, fin, v, d);
	}
	//Coste O(log n) ya que recorre el vector por mitades
}

/*
 * Un vector contiene n>=2 términos de una progresión artimética de diferendia d
 * dada desde el primero en adelante, pero uno de llos falta. Implementar algoritmo
 * eficiente que encuentre el término perdido. Ej. 2,4,8,10,12,14 con d=2, falta 6
 * El primer y último elementos de la progresión nunca son los que se han perdido.
 * ai = a1 + (i-1)*d
 */
void ejercicio2() {
	int v[N] = {2,4,8,10,12,14};
	int d = 2;

	cout << terminoPerdido(0, N-1, v, d);
}

int main() {
	//ejercicio1();
	ejercicio2();
	return 0;
}
