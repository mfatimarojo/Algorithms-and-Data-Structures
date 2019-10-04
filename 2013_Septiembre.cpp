//============================================================================
// Name        : 2013_Septiembre.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Septiembre 2013
//============================================================================

#include <iostream>
using namespace std;

bool contiene(int B[], int A[], int N, int M) {

	int i = 0;
	int j = 0;

	while(i<N && j<M) {
		if (B[i] == A[j]) {
			i++;
			j++;
		}
		else i++;
	}

	if (j==M) return true;
	else return false;
}

/*
 * Especifica y deriva o diseña y verifica una funcion iterativo que dados dos
 * arrays A y B, de longitud N y M (N <= M), ordenados estrictamente creciente,
 * determine si todos los elementos de A aparecen en B.
 */
void ejercicio1() {
	int N = 5;
	int M = 7;
	int A[N] = {5,6,7,8,9};
	int B[M] = {3,4,5,6,7,8,9};

	if (contiene(B, A, N, M)) {
		cout << "B contiene todos los elementos de A" << endl;
	}
}

int main() {
	ejercicio1();

	return 0;
}
