//============================================================================
// Name        : 2014_Febrero.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Febrero 2014
//============================================================================

#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

const int N = 10;
const int M = 20;

/*
 * {Pre = N>=0 ^ N=longitud(v) ^ 0<=m<=longitud(v) ^ s = Sumi:0<=i<m:v[i]}
 */
int maximaSuma(int v[], int N, int m, int sumaMayor) {
	int i = 1, j = 1;
	int cont = 0;
	int suma = 0;

	/*
	 * {I = Maxi:0<=i<=N-m:(Sumj: i<=j<i+m : v[j]) ^ suma>=0 ^ 0<=cont<m
	 */
	while (i <= N - m) {
		suma += v[j];
		j++;
		cont++;
		if (cont == m) {
			if (suma > sumaMayor)
				sumaMayor = suma;
			i++;
			j = i;
			cont = 0;
			suma = 0;
		}
	}

	return sumaMayor;
}
/*
 * {Pos = Maxi:0<=i<N:(Sumj: i<=j<i+m : v[j])}
 */

/*
 * Especifica, diseña y verifica o especifica y deriva, un algoritmo iterativo
 * de coste lineal que dado un vector v de enteros, un valor entero positivo m
 * 0<=m<=longitud(v) y un valor s igual a la suma de las m primeras posiciones
 * del vector, devuelva el valor máximo que se puede obtener sumando m elementos
 * consecutivos del vector.
 */
void ejercicio1() {
	int N = 10;
	int v[10] = { 5, -4, 9, 7, -5, 6, -1, 10, 0, 3 };
	int m = 3;
	int s = 0;
	for (int i = 0; i < m; i++) {
		s += v[i];
	}

	cout << maximaSuma(v, N, m, s) << "\n";

}

bool esCaucasico(int ini, int fin, int v[], int N, int &pares) {
	int paresI = 0, paresD = 0;
	bool caucasico = false;

	if (ini > fin) //No hay elementos
		caucasico = true;
	if (ini == fin) { //Sólo un elemento
		if (v[ini] % 2 == 0)
			pares++;
		caucasico = true;
	} else {
		int m = (ini + fin) / 2;
		bool caucaI = esCaucasico(ini, m, v, N, paresI);
		bool caucaD = esCaucasico(m + 1, fin, v, N, paresD);
		pares = paresI + paresD;
		if (caucaI && caucaD && (abs(paresI - paresD) <= 2))
			caucasico = true;
		else
			caucasico = false;

	}

	return caucasico;
}

/*
 * Un vector de enteros mayores que 0 de longitud 2^n es caucásico si el valor
 * absoluto de la diferencia entre el nº de elementos pares de sus mitades es,
 * a lo sumo, 2 y cada mitad también es caucásica.
 */
void ejercicio2() {
	int N = 2 * 2 * 2;
	int M = 2 * 2 * 2 * 2;
	int no[8] = { 2, 4, 6, 8, 1, 3, 5, 7 };
	int si[8] = { 2, 4, 6, 8, 2, 8, 5, 10 };
	int noMitad[16] = { 2, 4, 8, 12, 3, 7, 9, 21, 10, 20, 30, 1, 3, 5, 7, 40 };

	int pares = 0;
	if (esCaucasico(0, N - 1, no, N, pares))
		cout << "no[] SI\n";
	if (esCaucasico(0, N - 1, si, N, pares))
		cout << "si[] SI\n";
	if (esCaucasico(0, M - 1, noMitad, M, pares))
		cout << "noMitad[] SI\n";
}

void inicializarSols(bool sol[], bool solMejor[], int M) {
	for (int i = 0; i < M; i++) {
		sol[i] = false;
		solMejor[i] = false;
	}
}

void inicializarVetos(bool vetos[][M], int M) {

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j)
				vetos[i][j] = false;
			else {
				vetos[i][j] = true;
				vetos[j][i] = true;
			}
		}
	}


	/*vetos[5][9] = false;
	vetos[9][5] = false;
	vetos[4][3] = false;
	vetos[3][4] = false;
	vetos[11][14] = false;
	vetos[14][11] = false;
	vetos[6][7] = false;
	vetos[7][6] = false;*/

}

void inicializarBeneficios(int beneficios[], int M) {

	for (int i = 0; i < M; i++) {
		if (i % 2 == 0)
			beneficios[i] = i;
		else
			beneficios[i] = -2;
	}

}

int inicializarBeneficioMejor(int beneficios[], int M) {
	int mejor = 0;
	for (int i =0; i < M; i++) {
		mejor += beneficios[i];
	}
	return mejor;
}

bool artistaCompatible(int k, bool sol[], bool vetos[][M], int artistas) {
	int i = 0;

	if (artistas == 0) return true;
	while (i < M) {
		if (sol[i] && (!vetos[i][k] || !vetos[k][i])) return false;
		i++;
	}

	return true;
}

bool esValida(int artistas, int N) {
	return (artistas <= N);
}

bool esSolucion(int artistas, int N) {
	return (artistas == N);
}

bool esSolucionMejor(int beneficios, int beneficioMejor) {
	return (beneficios > beneficioMejor);
}

void copiarSolucion(bool solMejor[], bool sol[], int M) {
	for (int i = 0; i < M; i++) {
		solMejor[i] = sol[i];
	}
}

void tratarSolucion(bool sol[], int M, int N, int beneficioAct, int beneficioMejor) {
	int artistas = 0;
	for (int i = 0; i < M && artistas < N; i++) {
		if (sol[i] && artistas==0) {
			cout << "{" << i << ", ";
			artistas++;
		}
		else if (sol[i] && artistas < N-1){
			cout << i << ", ";
			artistas++;
		}
		else if (sol[i] && (artistas==N-1)){
			cout << i << "}\n";
			artistas++;
		}
	}
	cout << "Beneficio: " << beneficioAct << "\n";
	cout << "Beneficio mejor: " << beneficioMejor << "\n";
}

bool quedanArtistas(int k, int M) {
	return (k < M);
}

bool quedanSolucionesViables(int k, int M, int artistas, int beneficio,
		int beneficioMejor, int beneficios[]) {

	int beneficioEstimado = beneficio;
	//int quedan = M - artistas; //Porque si son N = 10 artistas , podemos coger hasta X más
	for (int i = k+1; i < M; i++) {
		beneficioEstimado += beneficios[i];
	}
	return (beneficioEstimado > beneficioMejor);
}

void festival(int k, int artistasAct, int beneficioAct, bool sol[],
		bool solMejor[], int &beneficioMejor, int beneficios[], bool vetos[][M]) {
	if (artistaCompatible(k, sol, vetos, M)) {
		sol[k] = true;	//Cojo la solución
		artistasAct++;
		beneficioAct += beneficios[k];
		if (esValida(artistasAct, N)) {	//Es válida si no nos pasamos de artistas
			if (esSolucion(artistasAct, N)) { //Es solución si ya tenemos N artistas
				cout << "Hay solución ";
				if (esSolucionMejor(beneficioAct, beneficioMejor)) {//Es solución mejor si tenemos mayor beneficios
					copiarSolucion(solMejor, sol, M);
					beneficioMejor = beneficioAct;
					cout << "y es solución mejor.\n";
				}
				else cout << "y no es solución mejor.\n";
				tratarSolucion(sol, M, N, beneficioAct, beneficioMejor);
			} else { //NO ES SOLUCIÓN, SOLUCIÓN PARCIAL --> artistasAct < N
				if (quedanArtistas(k, M)) { //Quedan artistas si k < M
					if (quedanSolucionesViables(k, M, artistasAct, beneficioAct,
							beneficioMejor, beneficios)) { //Si beneficioEstimado > beneficioMejor
						festival(k+1, artistasAct, beneficioAct, sol,
								solMejor, beneficioMejor, beneficios, vetos);
					}
				}
			}
		}
		sol[k]=false;
		artistasAct--;
		beneficioAct -= beneficios[k];
		if (quedanArtistas(k, M)) { //Quedan artistas si k < M
			if (quedanSolucionesViables(k, M, artistasAct, beneficioAct,
					beneficioMejor, beneficios)) { //Si beneficioEstimado > beneficioMejor
				festival(k + 1, artistasAct, beneficioAct, sol,
						solMejor, beneficioMejor, beneficios, vetos);
			}
		}
	}

}

/*
 * Festival de rock. N artistas, M disponibles (N<M). Conocemos vetos entre
 * artistas y beneficio de cada uno. Planificar el festival que maximice la
 * suma de los beneficios de los artistas participantes.
 */
void ejercicio3() {
	bool sol[M]; //Contiene los artistas del fest
	bool solMejor[M]; //Contiene los artistas del fest con mejor beneficio
	int artistasAct = 0; //Número de artistas contratados hasta ahora
	int beneficioAct = 0; //Beneficio obtenido hasta ahora
	int beneficios[M]; //Contiene los beneficios/pérdidas de cada artista
	bool vetos[M][M]; //Matriz entre artistas que actuan o no juntos.
	int k = 0;

	inicializarSols(sol, solMejor, M);
	inicializarVetos(vetos, M);
	inicializarBeneficios(beneficios, M);
	int beneficioMejor = 0; //inicializarBeneficioMejor(beneficios, M);

	festival(k, artistasAct, beneficioAct, sol, solMejor, beneficioMejor, beneficios, vetos);

}

int main() {
	ejercicio1();
	ejercicio2();
	ejercicio3();
	return 0;
}
