//============================================================================
// Name        : 2014_Junio.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Junio 2014
//============================================================================

#include <iostream>
using namespace std;

const int N = 6;	//Productos que quiere comprar
const int M = 3;		//Supermercados
const int ProdMax = 3;		//Productos máximos de cada supermercado



void inicializarMarcas(int marcas[]) {
	for (int i = 0; i < M; i++) {
		marcas[i] = 0;
	}
}

float inicializarCosteMejor(float precios[][N]) {
	float costeMejor = 0;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			costeMejor += precios[i][j];
		}
	}

	return costeMejor+1;
}

void inicializarPodas(float precios[][N], float preciosMin[]) {
	preciosMin[N-1] = precios[0][N - 1];

	for (int i = 1; i < M; i++) {
		if (precios[i][N - 1] < preciosMin[N - 1])
			preciosMin[N - 1] = precios[i][N - 1];
	}


	for (int j = N-2; j >= 0; j--) {
		for (int i=0; i < M; i++) {
			if (precios[i][j] < preciosMin[j + 1])
				preciosMin[j] = precios[i][j];
			else {
				preciosMin[j] = preciosMin[j + 1];
			}
		}
	}
}

bool esValida(int i, int marcas[],
		int k, int Nmax) {
	return (marcas[i] <= ProdMax && k < N && k < Nmax);

}

bool esSolucion(int k, int Nmax) {
	return (k == Nmax-1 || k == N-1);
}

bool esSolucionMejor(float costeAct, float costeMejor) {
	return (costeAct < costeMejor);
}

void copiarSolucion(int solMejor[], int sol[], int k) {
	for (int i = 0; i < k+1; i++) {
		solMejor[i] = sol[i];
	}
}

void tratarSolucion(int solMejor[], int k) {
	for (int i = 0; i < k+1; i++) {
		if (i == k)
			cout << solMejor[i] << "\n";
		else
			cout << solMejor[i] << ", ";
	}
}

bool quedanProductos(int k, int Nmax) {
	return (k < Nmax-1 || k < N-1);
}

bool quedanSolucionesViables(int k, float costeAct, float precioMin[],
		float costeMejor) {
	return ((costeAct + precioMin[k+1]) < costeMejor);
}

void compra(int k, float precios[][N], int marcas[], int sol[],
		float costeAct, int solMejor[], float &costeMejor,
		float preciosMin[], int Nmax) {

	for (int i = 0; i < M; i++) { //Recorro cada supermercado
		sol[k] = i;	//Cojo el producto k en el mercado i
		costeAct += precios[i][k];
		marcas[i]++; //Marco el producto como comprado
		if (esValida(i, marcas, k, Nmax)) {
			if (esSolucion(k, Nmax)) {
				if (esSolucionMejor(costeAct, costeMejor)) {
					costeMejor = costeAct;
					copiarSolucion(solMejor, sol, k);
					//tratarSolucion(solMejor, k);
				}
			} else {
				if (quedanProductos(k, Nmax)) {
					if (quedanSolucionesViables(k, costeAct, preciosMin,
							costeMejor)) {
						compra(k + 1, precios, marcas, sol,
								costeAct, solMejor, costeMejor, preciosMin, Nmax);
					}
				}
			}
		}
		//sol[k] = false;
		costeAct -= precios[i][k];
		marcas[i]--;
		/*if (quedanProductos(k, Nmax)) {
			if (quedanSolucionesViables(k, costeAct, preciosMin, costeMejor)) {
				compra(k + 1, precios, marcas, sol, costeAct,
						solMejor, costeMejor, preciosMin,
						prodSuperMax, Nmax);
			}
		}*/

	}

}

/*
 * Compra. N productos quiere comprar. Hay M supermercados que tienen esos
 * productos.  Máximo 3 productos por supermercado (n<=3m). Dispone de una
 * lista de precios de los productos en cada uno de los supermercados.
 * Comprar todo lo que necesita con un coste total mínimo.
 */
void ejercicio1() {
	int Nmax = ProdMax * M; 	//Productos máximos a comprar
	float precios[M][N] = { {3,3,3,3,100,20}, {500,500,500,5,5,5}, {100,50,70,0,0,0} }; //Precios de cada producto en cada supermercado
	float preciosMin[N];		//Para guardar el precio minimo de un producto
	float costeAct = 0;
	int sol[N];					//Productos cogidos
	int solMejor[N]; 			//Solución mejor
	int marcas[M];				//Para marcar los cuantos productos comprados por Supermercado
	int k = 0;

	float costeMejor = inicializarCosteMejor(precios);
	inicializarMarcas(marcas);
	inicializarPodas(precios, preciosMin);
	compra(k, precios, marcas, sol, costeAct, solMejor,
			costeMejor, preciosMin, Nmax);

	tratarSolucion(solMejor, N-1);

}

int main() {
	ejercicio1();
	return 0;
}
