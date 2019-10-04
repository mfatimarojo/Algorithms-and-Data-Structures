//============================================================================
// Name        : 2016_Septiembre.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Septiembre 2016
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

bool esBinario(int i, int v[], int N) {

	if (N==0 || N==1) return true;
	if (N==2) {
		if (v[i] > v[i+1]) return true;
	}
	if (N>2) {
		if(v[i] > v[i+1] && v[i] < v[i+2]) return true;

	}
	return false;
}


/*
 * Vector de enteros con el recorrido en preorden (RID) de un arbol de n>=1
 * niveles. Diseñar funcion boolean recursiva que determine si el árbol es
 * un árbol binario de búsqueda
 */
void ejercicio1() {
	int vacio[0];
	int uno[1];
	int dos[2];
	int tres[3];
	int cuatro[4];

	int i = 0;
	if (esBinario(i, vacio, 0)) cout << "vacio es binario" << endl;
	if (esBinario(i, uno, 1)) cout << "uno es binario" << endl;
	if (esBinario(i, dos, 2)) cout <<"dos es binario" << endl;
	if (esBinario(i, tres, 3)) cout << "tres es binario" << endl;
	if (esBinario(i, cuatro, 4)) cout << "cuatro es binario" << endl;
}

int inicializarValorMejor(int v[], int N) {
	int valorMejor = 0;
	for (int i = 0; i < N; i++) {
		valorMejor += v[i];
	}

	return valorMejor+1;
}

void inicializarPodas(int valorMaximo[], int v[], int N) {
	valorMaximo[N-1] = v[N-1];

	for (int i = N-2; i >= 0; i--) {
		valorMaximo[i] += valorMaximo[i+1];
	}
}

bool esValida(float peso1, float peso2, float pesoAct) {
	float porcentaje = pesoAct*(0.05);

	return (abs(peso1 - peso2) <= porcentaje);
}

bool esSolucion(int k, int N) {
	return (k==N-1);
}

bool esSolucionMejor(int valorAct, int valorMejor) {
	return (valorAct > valorMejor);
}

void copiarSolucion(int solMejor[], int sol[], int k) {
	for (int i = 0; i <= k; i++) {
		solMejor[i] = sol[i];
	}
}

void tratarSolucion(int solMejor[], int k) {
	for (int i = 0; i <= k; i++) {
		if (i==k) cout << solMejor[i] << "\n";
		else cout << solMejor[i] << ", ";
	}
}

bool quedanObjetos(int k, int N) {
	return (k < N-1);
}

bool quedanSolucionesOptimas(int k, int valorMaximo[], int valorAct, int valorMejor) {
	return ((valorAct+valorMaximo[k+1]) < valorMejor);
}

void camello(int k, int v[], float w[], int N,
			int sol[], int solMejor[], float pesoAct, float peso1, float peso2, int valorAct,
			int &valorMejor, int valorMaximo[]) {

	//Lo cojo en una
	sol[k] = 1;
	valorAct += v[k];
	peso1 += w[k];
	pesoAct += w[k];

	if (esValida(peso1, peso2, pesoAct)) {
		if (esSolucion(k, N)) {
			if (esSolucionMejor(valorAct, valorMejor)) {
				copiarSolucion(solMejor, sol, k);
				valorMejor = valorAct;
				tratarSolucion(solMejor, k);
			}
		}
		else {
			if (quedanObjetos(k, N)) {
				if (quedanSolucionesOptimas(k, valorMaximo, valorAct, valorMejor)) {
					camello(k+1,v,w,N,
							sol, solMejor, pesoAct, peso1, peso2, valorAct,
							valorMejor, valorMaximo);
				}
			}
		}
	}

	//Lo cojo en otra
	peso1 -= w[k];
	pesoAct -= w[k];
	sol[k] = 2;
	peso2 += w[k];
	pesoAct += w[k];
	if (esValida(peso1, peso2, pesoAct)) {
		if (esSolucion(k, N)) {
			if (esSolucionMejor(valorAct, valorMejor)) {
				copiarSolucion(solMejor, sol,k);
				tratarSolucion(solMejor, k);
			}
		}
		else {
			if (quedanObjetos(k, N)) {
				if (quedanSolucionesOptimas(k, valorMaximo, valorAct, valorMejor)) {
					camello(k+1,v,w,N,
							sol, solMejor, pesoAct, peso1, peso2, valorAct,
							valorMejor, valorMaximo);
				}
			}
		}
	}

	//No lo cojo
	peso2 -= w[k];
	pesoAct -= peso2;
	valorAct -= v[k];
	sol[k] = 0;
	if (quedanObjetos(k,N)) {
		if (quedanSolucionesOptimas(k, valorMaximo, valorAct, valorMejor)) {
			camello(k+1,v,w,N,
					sol, solMejor, pesoAct, peso1, peso2, valorAct,
					valorMejor, valorMaximo);
		}
	}
}

/*
 * Un camello transporta mercancias en dos alforjas cuya capacidad en peso es
 * p1, p2, conocidos. Cargar el camello de forma que se maximice el valor de
 * los objetos.  vi valor de los objetos y wi el peso del objeto.
 * El camello debe ir equilibrado por lo que la diferencia de peso entre alforjas
 * no debe superar el 5% del peso total.
 */
void ejercicio2() {
	int N = 7;
	int v[7] = {100,200,50,30,250,300,500};//Valor de los objetos
	float w[7] = {1, 0.3, 0.5, 2, 1, 0.7, 2}; //Peso de los objetos
	float pesoAct = 0;
	float peso1 = 0;
	float peso2 = 0;
	int valorAct = 0;
	int valorMejor = inicializarValorMejor(v,N);
	int valorMaximo[N];
	inicializarPodas(valorMaximo, v, N);
	int k = 0;
	int sol[N];
	int solMejor[N];

	camello(k, v, w, N,
			sol, solMejor, pesoAct, peso1, peso2, valorAct,
			valorMejor, valorMaximo);

}

int main() {
	//ejercicio1();
	ejercicio2();
	return 0;
}
