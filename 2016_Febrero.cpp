//============================================================================
// Name        : 2016_Febrero.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Febrero 2016
//============================================================================

#include <iostream>
#include <cmath>
using namespace std;

typedef struct{
	int i;
	int j;
} Casilla;

const int N = 3;

int parImpar(int v[], int N) {
	int p = 0;
	int i = 0;
	int j = i+1;

	if (N==0) return p;

	/*
	 * {I = (p = #i,j: 0<=j<j<=N: v[i]%2=0 ^v[j]%2 = 1) ^ p>=0}
	 */
	while (i < N-1) {
		if (v[i]%2 == 0 && j<N) {
			if(v[j]%2 != 0) p++;
			j++;
		}
		else {
			i++;
			j=i+1;
		}

	}
	/*
	 * c = N-j
	 */

	return p;
}
/*
 * VERIFICACIÓN
 * 1) {Pre}A{I}
 *    pmd(p=0,i=0,j=i+1,((p = #i,j: 0<=j<j<=N: v[i]%2=0 ^v[j]%2 = 1) ^ p>=0))
 *    ((((p = #i,j: 0<=i<j<=N: v[i]%2=0 ^v[j]%2 = 1) ^ p>=0)j=i+1)i=0)p=0
 *    (((0= #i,j: 0<=i<j<=N: v[i]%2=0 ^v[j]%2 = 1) ^ true)j=i+1)i=0
 *    ((0= #i,i+1: 0<=i<i+1<=N: v[i]%2=0 ^v[i+1]%2=1)i=0
 *    (0 = #0,1: 0<1<=N: v[0]%2=0 ^v[1]%2=1)
 *
 * 2) {I^B}A{I}
 *
 * 3) {I^¬B} --> Q
 * 	  Trivial pues el invariante con ¬B (i>=N-1) es más fuerte que la post
 *
 * 4) {I^B} --> c>=0
 * 	  Trivial puesto que j=N como mucho y N-j=N-N = 0
 *
 * 5) {I^B^c=T} A {c<T}
 * 	  Trivial puesto que j aumenta en cada vuelta de bucle y portant N-j disminuye
 */

/*
 * Diseñar y verificar o derivar un algoritmo iterativo eficiente y justificar
 * la complejidad del algoritmo:
 * {0<=n<=longitud(v) ^ Ak:0<=k<n:v[k]>=0}
 * fun parImpar(int v[], int n) return int p
 * {p = #i,j:0<=i<j<n:v[i]%2=0 ^ v[j]%2=1}
 */
void ejercicio1() {
	/* La entrada tiene que ser un vector de n>=0 enteros positivos
	 * La salida devuelve el nº de veces que aparece un nº par seguido de uno impar
	 * o bien el nº de veces que aparece un impar después de un par
	 * Supongo la segunda opción
	 */
	int vacio[0];
	int v[10] = {0,1,3,4,7,8,10,11,16,20};
	//La función debería devolver 0 para el primero, 8 para el segundo
	cout << "vacio[] " << parImpar(vacio, 0) << "\n";
	cout << "v[] " << parImpar(v, 10) << "\n";

}

long long contDigitos(long long n) {
	int cont = 0;
	if (n>= 0 && n<= 9) return 1;
	while (n > 0) {
		cont++;
		n=n/10;
	}

	return cont;
}

int digitoControl(long long n, int digitos, int &suma) {
	if (digitos == 1) {
		 suma += (n%10)*1;
		return 10-(suma%10);
	}
	else {
		if (digitos%2==0) suma += (n%10)*3;
		else suma += (n%10)*1;
		return digitoControl(n/10, digitos-1, suma);
	}

}

/*
 * d1*1 + d2*3 + d3*1 + d4*3 + ... + d12*3 + (d13) = x*10
 * Diseñar algoritmo recursivo eficiente que calcule d13 con cualquier nº de
 * digitos. Indicar y justificar complejidad
 */
void ejercicio2() {
	//Es decir, el d13 será 10-resultado%10
	long long n;
	cout << "Introduce ISBN: ";
	cin >> n;
	int digitos = contDigitos(n);
	int suma = 0;
	cout << digitos << endl;
	cout << "Digito control: " << digitoControl(n, digitos, suma) << endl;

}

void inicializarMatriz(int M[][N]) {
	M[0][0] = 0;
	M[0][1] = 3;
	M[0][2] = 4;
	M[1][0] = 1;
	M[1][1] = 2;
	M[1][2] = 3;
	M[2][0] = 1;
	M[2][1] = 1;
	M[2][2] = 1;
}

void inicializarMarcas(bool marcas[][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			marcas[i][j] = false;
		}
	}
}

int inicializarLongitudMejor(int M[][N]) {
	int longitudMejor = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			longitudMejor += M[i][j];
		}
	}

	return longitudMejor;
}

Casilla siguienteCasilla(int M[][N], int direccion, Casilla actual) {
	Casilla siguiente;
	siguiente.i = actual.i;
	siguiente.j = actual.j;

	switch(direccion) {
		case 0: //Arriba
			siguiente.i = actual.i--;
			break;
		case 1: //Abajo
			siguiente.i = actual.i++;
			break;
		case 2: //Izquierda
			siguiente.j = actual.j--;
			break;
		case 3: //Derecha
			siguiente.j = actual.j++;
			break;
	}

	return siguiente;
}

bool esValida(int M[][N], bool marcas[][N], Casilla actual, Casilla siguiente, int hmax) {
	return (!marcas[siguiente.i][siguiente.j] &&
			siguiente.i >= 0 && siguiente.i < N &&
			siguiente.j >= 0 && siguiente.j < N &&
			(abs(M[actual.i][actual.j] - M[siguiente.i][siguiente.j]) <= hmax));
}

bool esSolucion(Casilla siguiente, Casilla destino) {
	return (siguiente.i == destino.i && siguiente.j == destino.j);
}

bool esSolucionMejor(int longitud, int longitudMejor) {
	return (longitud < longitudMejor);
}

void copiarSolucion(Casilla solMejor[], Casilla sol[], int casillas) {
	for (int i = 0; i < casillas; i++) {
		solMejor[i] = sol[i];
	}
}

void tratarSolucion(Casilla sol[], int casillas) {
	for (int i = 0; i < casillas; i++) {
		if (i == casillas) cout << "(" << sol->i << "," << sol->j << ")\n";
		else cout << "(" << sol->i << "," << sol->j << "), ";

	}
}

bool quedanCasillas(int casillas) {
	return (casillas < (N*N));
}

bool quedanSolucionesViables() {
	return false;
}

void carretera(int M[][N], Casilla origen, Casilla destino, int hmax,
		Casilla sol[], Casilla solMejor[], bool marcas[][N], int k,
		int longitudAct, int &longitudMejor, int casillas) {

	int direccion = 0;
	while (direccion < 4) {
		cout << "ENTRO" << endl;
		Casilla siguiente = siguienteCasilla(M, direccion, origen);
		if (esValida(M, marcas, origen, siguiente, hmax)) { //Si no se pasa de rango dif <= hmax
			cout << "VALIDA" << endl;
			sol[k] = siguiente;
			marcas[siguiente.i][siguiente.j] = true;
			longitudAct++;
			if (esSolucion(siguiente, destino)) { //sol[k] = destino
				if (esSolucionMejor(longitudAct, longitudMejor)) {
					longitudMejor = longitudAct;
					copiarSolucion(solMejor, sol, longitudAct);
				}
				tratarSolucion(solMejor, longitudAct);
			}
			else {
				if (quedanCasillas(casillas)) {
					//if(quedanSolucionesViables) {
						carretera(M, siguiente, destino, hmax, sol, solMejor, marcas, k+1, longitudAct, longitudMejor, casillas);
						//PODAR SI DESDE DONDE ESTOY HASTA EL DESTINICO, DISTNACIA MINIMA SI ESO SUMADO A LOD E AHORA ES MEJOR QUE LA MEJOR SOLUCION
					//}
				}
			}
			marcas[siguiente.i][siguiente.j] = false;
			longitudAct--;
			//carretera(M, origen, destino, hmax, sol, solMejor, marcas, k+1, longitudAct, longitudMejor, casillas);
		}

		direccion++;
	}

}

/*
 * Matriz M de NxN numeros reales, donde M[i][j] es la altura media de la casilla.
 * Se desea construir una carretera entre dos puntos dados pasando por casillas
 * adyacentes cuya diferencia entre sus alguras no supera hmax:
 * |M[a][b] - M[c][d]| <= hmax
 *
 */
void ejercicio3() {
	int M[N][N];
	bool marcas[N][N];
	int hmax = 2;
	Casilla origen, destino;
	origen.i = 0;
	origen.j = 1;
	destino.i = 0;
	destino.j = 0;
	Casilla sol[N*N];
	Casilla solMejor[N*N];
	int casillasAct = 0;
	int casillasMejor;
	int k = 0;

	inicializarMatriz(M);
	inicializarMarcas(marcas);
	casillasMejor = inicializarLongitudMejor(M);


	carretera(M, origen, destino, hmax, sol, solMejor, marcas, k, longitudAct, longitudMejor, casillas);

}


int main() {
	//ejercicio1();
	//ejercicio2();
	ejercicio3();
	return 0;
}
