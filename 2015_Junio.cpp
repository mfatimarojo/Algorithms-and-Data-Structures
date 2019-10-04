//============================================================================
// Name        : 2015_Junio.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Junio 2015
//============================================================================

#include <iostream>
using namespace std;

typedef struct {
	int c;
	int f;
} Intervalo;

const int N = 5;

int bucle1(int v[], int n) {
	int p = 0;
	int i = n;
	int s = 0;

	while (i > 0) {
		p += v[i-1]*s;
		s += v[i-1];
		i--;
	}

	return p;
}

int bucle2(int v[], int n) {
	int p = 0;
	int i = 0;
	int s = 0;

	while (i < n) {
		p = p + v[i]*s;
		s = s + v[i];
		i++;
	}

	return p;
}

/*
 * Vector de n>=0 eementos. Obtener la suma de todos los productos de valores
 * situados en parejas de posiciones distintas con complejidad O(n). Escribe
 * los invariantes para cada bucle
 * { pre = 0<=n<longitud(v) }
 * fun sumaProductos(int v[], int n) return int p
 * { post = Sumatorio i,j: 0<=i<j<n: v[i]*v[j] }
 */
void ejercicio1() {
	int v[10];
	int n = 10;
	bucle1(v, n);
	bucle2(v, n);
}

void inicializarActividades(Intervalo a[]) {
	/*Si 0 --> (1,5),(10,15)
	 * 		   (1,5),(13,16)
	 *
	 *Si 1 --> (2,4),(5,8)
	 *		   (2,4),(5,8),(10,15)
	 *		   (2,4),(5,8),(13,16)
	 *		   (2,4),(10,15)
	 *		   (2,4),(13,16)
	 *
	 *Si 2 --> (5,8),(10,15)
	 *		   (5,8),(13,16)
	 *
	 * */

	a[0].c = 1;
	a[0].f = 5;
	a[1].c = 2;
	a[1].f = 4;
	a[2].c = 5;
	a[2].f = 8;
	a[3].c = 10;
	a[3].f = 15;
	a[4].c = 13;
	a[4].f = 16;
}

bool esValida(int ini, int fin) {
	return (ini > fin);
}

bool esSolucion(int k) {
	return (k == N-1);
}

void tratarSolucion(Intervalo sol[], int r) {
	for (int i = 0; i < r; i++) {
		if (i==r-1) cout << "(" << sol[i].c << "," << sol[i].f << ")\n";
		else cout << "(" << sol[i].c << "," << sol[i].f << "), ";
	}
}

bool quedanActividades(int k) {
	return (k < N-1);
}

void actividades(int k, Intervalo a[], Intervalo sol[], Intervalo solMejor[], int r, int &finAnterior) {

	if (k == N) return;

	int aux;
	if (esValida(a[k].c, finAnterior)) {
		sol[r] = a[k];
		r++;
		aux = finAnterior;
		finAnterior = a[k].f;
		if (esSolucion(k)) {
			tratarSolucion(sol, r);
		}
		else {
			/*if (quedanActividades(k))
				actividades(k+1, a, sol, solMejor, r, finAnterior);
			 */
				actividades(k+1, a, sol, solMejor, r, finAnterior);
		}
		r--;
		finAnterior = aux;

	}
	actividades(k+1, a, sol, solMejor, r, finAnterior);

}

/*
 * N actividades con comienco Ci y fin Fi.  Diseñar un algoritmo de vuelta atrás
 * que imprima todos los subconjuntos con r o más actividades que no solapen entre
 * sí. Los intervalos de actividades vienen dados en un vector a[] de parejas de
 * enteros ordenado crecientemente por instante de comienzo.
 */
void ejercicio2() {
	Intervalo a[N];
	inicializarActividades(a);
	int r = 0;	//Actividades no solapadas de cada subconjunto
	Intervalo sol[N];
	Intervalo solMejor[N];
	int k = 0;
	int finAnterior = -1;

	actividades(k, a, sol, solMejor, r, finAnterior);

}


int main() {
	//ejercicio1();
	ejercicio2();
	return 0;
}
