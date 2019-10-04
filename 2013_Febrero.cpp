//============================================================================
// Name        : 2013_Febrero.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Febrero 2013
//============================================================================

#include <iostream>
using namespace std;

/*
 * {Pre = 0 <= N <= longitud(v) ^ cerosUnos(v, N) }
 */
bool seCumple(int v[], int N) {
	bool unos = true;
	int i = 0;

	/*
	 * {I = Ec: 0<=c<=N(Ai: 0<=i<c; v[i]==1 ^ Aj; c<=j<N: v[j] == 0)
	 */
	while (i < N) {
		if (v[i] == 1 && !unos)
			return false;
		if (v[i] == 0)
			unos = false;

		i++;
	}
	/*
	 * Cota = N-i;
	 */
	return true;

}
/*
 * {Post = Ec: 0<=c<N(Ai: 0<=i<c; v[i]==1 ^ Aj; c<=j<N: v[j] == 0)}
 *
 * VERIFICACIÓN
 * 1) {Pre} A {I}
 *    pmd(i=0, Ec: 0<=c<=N(Ai: 0<=i<c; v[i]==1 ^ Aj; c<=j<N: v[j] == 0))
 *    (Ec: 0<=c<=N(Ai: 0<=i<c; v[i]==1 ^ Aj; c<=j<N: v[j] == 0))i=0
 *    Ec: 0<=c<=N(A0: 0<c; v[0]==1 ^ Aj; c<=j<N: v[j] == 0)
 *    Ec: 0<=c<=N(true ^ Aj; c<=j<N: v[j] == 0)
 *
 * 2) {I^B} A {I}
 *
 * 3) {I^¬B} --> Q
 * 	  Trivial, pues ¬B= i >= N
 *
 * 4) {I^B} --> cota >= 0
 *    Trivial, en cada vuelta de bucle i aumenta por lo que cota disminuye
 *    y como i=N-1 como máximo N-i >= 0 --> N-(N-1) >= --> 1 >= 0
 *
 * 5) Cota disminuye en cada vuelta de bucle (Paso 4)
 *
 */

bool cerosUnos(int v[], int N) {
	int i = 0;
	while ((v[i] == 0 || v[i] == 1) && (i < N))
		i++;
	if (i < N)
		return false;
	else
		return true;
}

/*
 * Especificar, diseñar, verificar y calcular el coste de un algoritmo que,
 * dado un vector de enteros de n>=0 y que tan solo puede contener valores
 * 0 y 1, devuelva un booleno que indique si el vector tiene la forma
 * 1 1 ... 1 1 0 0 ... 0 0 donde cada zona puede tener cualquier longitud
 */
void ejercicio1() {
	int v[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int w[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int yes[10] = { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 };
	int no[10] = { 1, 1, 1, 1, 0, 0, 1, 0, 0, 0 };

	if (seCumple(v, 10))
		cout << "v SI\n";
	else
		cout << "v NO\n";
	if (seCumple(w, 10))
		cout << "w SI\n";
	else
		cout << "w NO\n";
	if (seCumple(yes, 10))
		cout << "yes SI\n";
	else
		cout << "yes NO\n";
	if (seCumple(no, 10))
		cout << "no SI\n";
	else
		cout << "no NO\n";

}

/*
 * {Pre = 0<=N<=longitud(v)=longitud(w)}
 */
void histograma(int v[], int N, int w[], int k, int sumaP) {

	if (N==0 || k==N) return;
	else {
		w[k] = v[k] + sumaP;
		histograma(v,N,w,k+1,sumaP+v[k]);
	}
}
/*
 * {Post = Ai: 0<=i<N: w[i] = (Sumj: 0<=j<=i<N: v[j])}
 */

/*
 * Especificar, diseñar, demostrar correción y calcular el coste de un algoritmo
 * recursivo, lo más eficiente posible, que dado un vector de enteros que puede
 * ser vacío, devuelva su histograma
 */
void ejercicio2() {
	int N = 5;
	int v[5] = {1,2,4,3,-2};
	int w[5];
	int sumaP= 0;
	histograma(v, N, w, 0, sumaP);

	for (int i = 0; i < N; i++) {
		if (i == 0) cout << "{" << w[i] << ", ";
		else if (i == N-1) cout << w[i] << "}\n";
		else cout << w[i] << ", ";
	}
}

int main() {
	ejercicio1();
	ejercicio2();
	return 0;
}
