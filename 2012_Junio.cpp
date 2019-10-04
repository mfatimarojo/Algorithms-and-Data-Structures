//============================================================================
// Name        : 2012_Junio.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Junio 2012
//============================================================================

#include <iostream>
using namespace std;

typedef struct {
	int i;
	int j;
} Casilla;

const int L = 5;
const int M = 8;
char lab[L][M];
char palabara[3] = {'E','D','A'};
/*
 * { Pre = 1 <= n <= longitud(v) }
 */
int longitud(int v[], int N) {
	int i = 0;
	int cont = 0;
	int contMayor = 0;

	while (i < N-1) {
		if (v[i] <= v[i+1]) cont++;
		else if (v[i] > v[i+1]) {
			if (cont > contMayor) contMayor = cont+1;
			cont = 0;
		}
		i++;

	}

	return contMayor;
}
/*
 * { Pos =
 */

/*
 * Especificar y derivar formalmente, o diseñar y verificar, un algoritmo
 * iterativo eficiente que dado un vector n>=1 enteros obtenga la longitud
 * del segmento más largo de elementos consecutivos ordenados crecientemente <=
 * Calcular coste
 */
void ejercicio1() {
	int N = 10;

	int v[10] = {1,2,3,4,3,2,1,0,-1,-2}; //4
	int w[10] = {1,2,3,4,5,4,3,2,3,2}; //5
	int x[10] = {10,9,8,7,7,8,9,1,0,1}; //4
	int y[10] = {10,9,8,7,6,5,4,3,2,1}; //0
	int z[1] = {0};

	cout << longitud(v, N) << endl;
	cout << longitud(w, N) << endl;
	cout << longitud(x, N) << endl;
	cout << longitud(y, N) << endl;
	cout << longitud(z, 1) << endl;



}

void inicializarLab() {
	lab[0][0] = 'M';
	lab[0][1] = 'D';
	lab[0][2] = 'A';
	lab[0][3] = 'A';
	lab[0][4] = 'E';
	lab[0][5] = 'E';
	lab[0][6] = 'D';
	lab[0][7] = 'A';
	lab[1][0] = 'A';
	lab[1][1] = 'E';
	lab[1][2] = 'E';
	lab[1][3] = 'D';
	lab[1][4] = 'D';
	lab[1][5] = 'A';
	lab[1][6] = 'N';
	lab[1][7] = 'D';
	lab[2][0] = 'D';
	lab[2][1] = 'B';
	lab[2][2] = 'D';
	lab[2][3] = 'X';
	lab[2][4] = 'E';
	lab[2][5] = 'D';
	lab[2][6] = 'A';
	lab[2][7] = 'E';
	lab[3][0] = 'E';
	lab[3][1] = 'A';
	lab[3][2] = 'E';
	lab[3][3] = 'D';
	lab[3][4] = 'A';
	lab[3][5] = 'R';
	lab[3][6] = 'T';
	lab[3][7] = 'D';
	lab[4][0] = 'E';
	lab[4][1] = 'D';
	lab[4][2] = 'M';
	lab[4][3] = 'P';
	lab[4][4] = 'L';
	lab[4][5] = 'E';
	lab[4][6] = 'D';
	lab[4][7] = 'A';
}

void inicializarMarcas(bool marcas[][M]) {
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < M; j++) {
			marcas[i][j] = false;
		}
	}
}

Casilla siguienteCasilla(Casilla actual, int dir) {
	Casilla siguiente;
	siguiente.i = actual.i;
	siguiente.j = actual.j;

	switch(dir) {
		case 0:
			siguiente.i = actual.i--;
			break;
		case 1:
			siguiente.i = actual.i++;
			break;
		case 2:
			siguiente.j = siguiente.j++;
			break;
		case 3:
			siguiente.j = siguiente.j--;
			break;
	}

	return siguiente;
}

char tocaLetra(Casilla origen) {
	if (lab[origen.i][origen.j] == 'E') return 'D';
	else if (lab[origen.i][origen.j] == 'D') return 'A';
	else if (lab[origen.i][origen.j] == 'A') return 'E';
	else return NULL;
}

bool esValida(Casilla siguiente, char toca) {
	return (siguiente.i>= 0 && siguiente.i<L &&
			siguiente.j>= 0 && siguiente.j < M &&
			lab[siguiente.i][siguiente.j] == toca);
}

bool esSolucion(Casilla siguiente, Casilla destino) {
	return (siguiente.i == destino.i &&
			siguiente.j == destino.j);
}

bool esSolucionMejor(int casillas, int casillasMejor) {
	return (casillas<casillasMejor);
}

void copiarSolucion(Casilla solMejor[], Casilla sol[], int casillas) {
	for (int i = 0; i < casillas; i++) {
		solMejor[i] = sol[i];
	}
}

void tratarSolucion(Casilla sol[], int casillas) {
	for (int i = 0; i < casillas; i++) {
		if (i==casillas-1) cout << "(" << sol[i].i << "," << sol[i].j << ")\n";
		else cout << "(" << sol[i].i << "," << sol[i].j << "), ";
	}
}

bool quedanCasillas(int casillas) {
	return(casillas < (L*M)-1);
}

void camino(int k, Casilla sol[], Casilla solMejor[], bool marcas[][M], Casilla origen, Casilla destino, int casillas, int casillasMejor) {

	int dir = 0;

	while (dir < 4) { //0=N, 1=S, 2=E, 3=O
		Casilla siguiente = siguienteCasilla(origen,dir);
		char toca = tocaLetra(origen);
		sol[k] = siguiente;
		marcas[siguiente.i][siguiente.j] = true;
		casillas++;
		if(esValida(siguiente, toca)) {
			if (esSolucion(siguiente,destino)) {
				if (esSolucionMejor(casillas, casillasMejor)) {
					casillasMejor = casillas;
					copiarSolucion(solMejor, sol, casillas);
				}
				tratarSolucion(solMejor, casillas);
			}
			else {
				if (quedanCasillas(casillas)) {
					if (quedanSolucionesViables) {
						recursion();
					}
				}
			}
		}
		sol[k] = NULL;
		marcas[siguiente.i][siguiente.j] = false;
		casillas--;
		if (quedanCasillas(casillas)) {
			if (quedanSolucionesViables) {
				recursion();
			}
		}
		dir++;
	}

}

/*
 * Función que encuentra la forma más rápida (mejor sol) de viajar de una casilla a otra.
 * Cada casilla es una letra, de forma que en el camino se forma de forma
 * cíclica una palabra dada.
 */
void ejercicio3() {
	int k = 0;
	bool marcas[L][M];
	inicializarLab();
	inicializarMarcas(marcas);
	Casilla origen, destino;
	origen.i=0;
	origen.j=4;
	destino.i=7;
	destino.i=0;
	int casillasAct = 0;
	int casillasMejor = L*M;



	camino(k, marcas, origen, destino, casillasAct, casillasMejor);

}

int main() {
	ejercicio1();
	//ejercicio2(); --> Árboles
	ejercicio3();
	return 0;
}
