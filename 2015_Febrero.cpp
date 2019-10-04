//============================================================================
// Name        : 2015_Febrero.cpp
// Author      : Fátima Rojo
// Version     :
// Copyright   : Fátima Rojo
// Description : EDA - Febrero 2015
//============================================================================

#include <iostream>
using namespace std;

int N = 20; 	//alimentos
float M = 40;	//Precio máximo
float Q = 2000; //Proteinas mínimo
int V = 0;

/*
 * { Pre = N>=0 ^ N=longitud(v) }
 */
int sumaProductos(int v[], int N) {
	int suma = 0;
	int i = 0;
	int j = i + 1;

	if (N == 0)
		return 0;

	/*
	 * { I = suma=(Sumatorioij: 0<=i<j<=N: v[i]*v[j]) ^ suma>=0}
	 */
	while (i < N - 1) {
		suma += v[i] * v[j];
		j++;
		if (j == N) {
			i++;
			j = i + 1;

		}
	}
	/*
	 * Cota c = N-j;
	 */

	return suma;
}
/*
 * { Pos = suma = (Sumatorioij: 0<=i<j<N: v[i]*v[j]) }
 *
 * VERIFICACIÓN
 * 1) {Pre}A{I}
 *    pmd(suma=0;i=0;j=i+1,(suma = (Sumatorioij: 0<=i<j<=N: v[i]*v[j])))
 *    (((suma = (Sumatorioij: 0<=i<j<=N: v[i]*v[j0]) ^ suma>=0) j=i+1) i=0) suma=0
 *    ((suma = (Sumatorioij: 0<=i<i+1<=N: v[i]*v[i+1]) ^ suma>=0) i= 0) suma=0
 *    (suma = (Sumatorioij: 0<=0<1<=N: v[0]*v[1]) ^ suma>=0) suma = 0;
 *    (0 = v[0]*v[1] ^ 0=0) -->
 *
 * 2) {I^B}A{I}
 *
 * 3) {I^¬B} --> Q
 * 	  Como ¬B= i>=N-1
 *
 * 4) {I^B} --> cota >= 0
 * 	  Trivial, como c= N-j y j toma el valor j=N como máximo
 * 	  N-N=0
 *
 * 5) Cota decrece {I^B^c=T}A{c < T}
 * 	  Trivial, como c=N-j y j decrece en cada vuelta de bucle, cota decrece
 *
 * Complejidad O(n) puesto que recorre el bucle una sola vez
 *
 */

/*
 * Especificar, diseñar y verificar (o derivar). Vector de n>=0 elementos. Obtener
 * la suma de todos los productos de valores situados en parejas de posiciones
 * distintas con O(n) justificado.
 */
void ejercicio1() {
	cout << "-----------\n";
	cout << "EJERCICIO 1\n\n";
	int vacio[V];
	int v[4] = { 1, 3, 5, 7 };
	int w[6] = { 6, 2, 5, 9, 1, 2 };

	cout << "vacio[] suma: " << sumaProductos(vacio, V) << "\n";
	cout << "v[] suma: " << sumaProductos(v, N) << "\n";
	cout << "w[] suma: " << sumaProductos(w, M) << "\n";
}

int contarDigitos(unsigned int n) {
	int mul = 1;
	int digitos = 0;
	if (n >= 0 && n <= 9)
		return 1;
	while (n / 10 > 0) {
		digitos++;
		if (digitos > 1)
			mul = mul * 10;
		n = n / 10;
	}
	if (n > 0) {
		digitos++;
		mul = mul * 10;
	}

	return mul;
}

/*
 * 	Recursión simple donde la llamada a la función recursiva se realiza al final,
 * 	siendo el resultado uno de los casos base.
 */
unsigned int imagenEspecularFinal(unsigned int n) {
	//Casos base
	return 0;
}

/*
 * Recursión simple donde cada caso recursivo hace sólo una llamada recursiva.
 */
unsigned int imagenEspecularNoFinal(unsigned int n, int digitos) {
	return 0;
}

/*
 * Implementa dos algoritmos recursivos, uno final y otro no final, que calculen
 * la imagen especular de un número natural unsigned int. Justifica el coste.
 */
void ejercicio2() {
	cout << "-----------\n";
	cout << "EJERCICIO 2\n\n";

	unsigned int n;
	cout << "Introduce número: ";
	cin >> n;

	//int digitos = contarDigitos(n);
	/*unsigned int imagenFinal = imagenEspecularFinal(n);
	 cout << "Imagen especular final: " << imagenFinal << "\n";
	 unsigned int imagenNoFinal = imagenEspecularNoFinal(n);
	 cout << "Imagen especular no final: " << imagenNoFinal<< "\n";
	 */
}

void inicializarSol(bool sol[], bool solMejor[]) {
	for (int i = 0; i < N; i++) {
		sol[i] = false;
		solMejor[i] = false;
	}
}

void inicializarPrecios(float precios[], int N) {
	for (int i = 0; i < (N / 2); i++) {
		if (i % 2 == 0)
			precios[i] = 2 * i;
		else
			precios[i] = 2;
	}

	for (int i = (N / 2); i < N; i++) {
		if (i % 2 == 0)
			precios[i] = 2;
		else
			precios[i] = i / 2;
	}
}

void inicializarProteinas(float proteinas[], int N) {
	for (int i = 0; i < (N / 2); i++) {
		if (i % 2 == 0)
			proteinas[i] = 100 * i;
		else
			proteinas[i] = 20;
	}

	for (int i = (N / 2); i < N; i++) {
		if (i % 2 == 0)
			proteinas[i] = 20;
		else
			proteinas[i] = (100 * i) / 2;
	}
}

void inicializarCalorias(float calorias[], int N) {
	for (int i = 0; i < (N / 2); i++) {
		if (i % 2 == 0)
			calorias[i] = 100 * i;
		else
			calorias[i] = 20;
	}

	for (int i = (N / 2); i < N; i++) {
		if (i % 2 == 0)
			calorias[i] = 20;
		else
			calorias[i] = (100 * i) / 2;
	}
}
/*
 bool esValida(float precio, float proteinas) {
 return (precio <= M && proteinas >= Q);
 }
 */

bool esSolucion(float precio, float proteinas) {
	return (precio <= M && proteinas >= Q);
}

bool esSolucionMejor(float calorias, float caloriasMejor) {
	return (calorias < caloriasMejor);
}

void copiarSolucion(bool solMejor[], bool sol[]) {
	for (int i = 0; i < N; i++) {
		solMejor[i] = sol[i];
	}
}

void tratarSolucion(bool sol[], int alimentos) {
	int cont = 0;
	for (int i = 0; i < N; i++) {
		if (sol[i] && cont == 0) {
			cout << "{" << i << ", ";
			cont++;
		}
		if (sol[i] && cont > 0 && cont < alimentos - 1) {
			cout << i << ", ";
			cont++;
		}
		if (sol[i] && cont == alimentos - 1) {
			cout << i << "}\n";
			cont++;
		}
	}
}

bool quedanAlimentos(int k) {
	return (k < (N - 1));
}

bool quedanSolucionesViables(int k, float precios, float proteinas,
		float calorias, float minPrecios[], float maxProteinas[],
		float minCalorias[], float caloriasMejor) {

	bool precioSi = false, proteinaSi = false, caloriaSi = false;
	if ((precios + minPrecios[k + 1]) <= M)
		precioSi = true;
	if ((proteinas + maxProteinas[k + 1]) >= Q)
		proteinaSi = true;
	if ((calorias + minCalorias[k + 1]) < caloriasMejor)
		caloriaSi = true;

	return (precioSi && proteinaSi && caloriaSi);
}

void inicializarPodas(float precios[], float proteinas[], float calorias[],
		float minPrecios[], float maxProteinas[], float minCalorias[]) {

	minPrecios[N - 1] = precios[N - 1];
	for (int i = N - 2; i >= 0; i--) {
		if (precios[i] < minPrecios[i + 1])
			minPrecios[i] = precios[i];
		else
			minPrecios[i] = minPrecios[i + 1];
	}

	maxProteinas[N - 1] = proteinas[N - 1];
	for (int i = N - 2; i >= 0; i--) {
		maxProteinas[i] = proteinas[i] + maxProteinas[i + 1];
	}

	minCalorias[N - 1] = calorias[N - 1];
	for (int i = N - 2; i >= 0; i--) {
		if (calorias[i] < minCalorias[i + 1])
			minCalorias[i] = calorias[i];
		else
			minCalorias[i] = minCalorias[i + 1];
	}

}

void dieta(int k, bool sol[], bool solMejor[], int alimentos, float precios[],
		float proteinas[], float calorias[], float precioTotal,
		float proteinasTotal, float caloriasTotal, float minPrecios[],
		float maxProteinas[], float minCalorias[], float caloriasMejor) {

	//Primero lo cojo
	sol[k] = true;
	alimentos++;
	precioTotal += precios[k];
	proteinasTotal += proteinas[k];
	caloriasTotal += calorias[k];

	//esValido
	//if (esValida(precioTotal, proteinasTotal)) { //Todos son válidos, o lo cojo o no
	if (esSolucion(precioTotal, proteinasTotal)) {//Es solución si precio<=M y proteinas>=Q
		if (esSolucionMejor(caloriasTotal, caloriasMejor)) {
			caloriasMejor = caloriasTotal;
			copiarSolucion(solMejor, sol);
		}
		tratarSolucion(solMejor, alimentos);
	} else {
		if (quedanAlimentos(k)) {
			if (quedanSolucionesViables(k, precioTotal, proteinasTotal,
					caloriasTotal, minPrecios, maxProteinas, minCalorias,
					caloriasMejor)) {
				dieta(k + 1, sol, solMejor, alimentos, precios, proteinas,
						calorias, precioTotal, proteinasTotal, caloriasTotal,
						minPrecios, maxProteinas, minCalorias, caloriasMejor);

			}
		}
	}
//	}
	sol[k] = false;
	alimentos--;
	precioTotal -= precios[k];
	proteinasTotal -= proteinas[k];
	caloriasTotal -= calorias[k];
	if (quedanAlimentos(k)) {
		if (quedanSolucionesViables(k, precioTotal, proteinasTotal,
				caloriasTotal, minPrecios, maxProteinas, minCalorias,
				caloriasMejor)) {
			dieta(k + 1, sol, solMejor, alimentos, precios, proteinas, calorias,
					precioTotal, proteinasTotal, caloriasTotal, minPrecios,
					maxProteinas, minCalorias, caloriasMejor);

		}
	}

}

/*
 * N alimentos alimenticios, precios[], proteinas[], calorias[]. Seleccionar
 * alimentos de froma que precioTotal <= M, proteinasTotal >= Q y minimizar
 * caloriasTotal. Encontrar solución mejor.
 */
void ejercicio3() {
	float precios[N], proteinas[N], calorias[N];
	float minPrecios[N], maxProteinas[N], minCalorias[N], caloriasMejor = 100000;
	float precioTotal = 0, proteinasTotal = 0, caloriasTotal = 0;

	int alimentos = 0;
	bool sol[N]; //alimentos escogidos
	bool solMejor[N];
	int k = 0;

	inicializarPrecios(precios, N);
	inicializarProteinas(proteinas, N);
	inicializarCalorias(calorias, N);
	inicializarPodas(precios, proteinas, calorias, minPrecios, maxProteinas,
			minCalorias);

	dieta(k, sol, solMejor, alimentos, precios, proteinas, calorias,
			precioTotal, proteinasTotal, caloriasTotal, minPrecios,
			maxProteinas, minCalorias, caloriasMejor);
}

int main() {
//ejercicio1();
//ejercicio2();
	ejercicio3();
	return 0;
}
