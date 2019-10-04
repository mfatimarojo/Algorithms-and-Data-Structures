//============================================================================
// Name        : 2012_Febrero.cpp
// Author      : F�tima Rojo
// Version     :
// Copyright   : F�tima Rojo
// Description : EDA - Febrero 2012
//============================================================================

#include <iostream>
using namespace std;

/*
 * El algoritmo A tarda 207 + 4n^2 segundos en resolver un problema de tama�o n,
 * mientras que el algoritmo B lo resuleve en 3n^4 segundos. Razonar para qu�
 * valores de n es mejor cada uno de ellos.
 */
void ejercicio1() {
	/* 3n^4 = 4n^2 + 207
	 * 3n^4 - 4n^2 - 207 = 0
	 * z = n^2 --> 3z^2 - 4z - 207 = 0;
	 * z = (-b +/- Raiz2(b^2 - 4ac))/2a
	 * z = (4 +/- Raiz2(16 + 2484))/6
	 * z = (4 +/- 50)/6
	 * z = 54/6 = 9 --> z = 9 --> n^2 = 9 --> n = 3
	 * z = -46/6 = -7'666 --> n^2 = -7'666 --> NO ES SOLUCI�N
	 *
	 * n = 3
	 * 207 + 4n^2 = 207 + 4*9 = 243
	 * 3n^4 = 3*81 = 243
	 * Por tanto, para valores n>3 ser� mejor el algoritmo A y para valores
	 * n<3 ser� mejor el algoritmo B.
	 */
}

/*
 * Compara las clases de complejidad O y 0 de las siguientes parejas de funciones
 * 1) nlog(n) y nRaiz2(n)
 * 2) (n+1)^2 y (n-1)^2
 * 3) (n+1)! y n!
 * 4) n^a y a^n, con a perteneciente R+, a>1
 */
void ejercicio2() {
	//NO ENTRA
}

/*
 * Calcula el n�mero exacto de veces que se ejecuta A. Si A pertenece a O(n),
 * indiciar tambi�n cu�l es la complejidad asint�tica del algoritmo
 */
void ejercicio3(int n) {
	//NO ENTRA, a�n as� --> n*n veces --> n^2 --> O(n^2) --> Orden cuadr�tico
	/*
	 for (int i=0; i<n; i++) {
	 for (int j=0; j<n; j++) {
	 {A};
	 }
	 }
	 */
}

/*
 * Los dos algoritmos reciben un vector de enteros con n>=2 elementos. Escribe
 * sus postcondiciones
 * 1) Devuelve booleano b que indica si hay exactamente una posici�n cuyo contenido
 *    vale el triple de su �ndice.
 * 2) Devuelve un entero s que es el mayor valor que es posible conseguir sumando
 *    dos elementos del vector que contengan valores distintos.
 */
void ejercicio4() {

	//1) P = {b = (#k: (Ei; 0<=i<N; v[i] = 3*i) = 1)}
	//2) P = {s = (AiAj: 0 <= i < j < N: v[i] != v[j] ^ (max =}
	int v[10] = { 1, 3, 4, 8, 2, 2, 5, 7, 0, 1 };
	int suma = 0;
	int sumaMayor = v[0] + v[1];
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (v[i] != v[j])
				suma = v[i] + v[j];
			if (suma > sumaMayor)
				sumaMayor = suma;
		}
	}

	cout << sumaMayor << endl;
}

bool esMontana(int v[], int N) {
	bool crece = true;
	bool esMontana = true;

	for (int i = 0; i < N - 1; i++) {
		if ((v[i] < v[i + 1]) && !crece) {
			return false;
		}
		if (v[i] > v[i + 1])
			crece = false;
	}

	return esMontana;
}

// { Pre: 1 <= n <= longitud(v) ^ esMontaña(v, n)}
int cumbre(int v[], int N) {
	int i = 0;
	int cumbre = i;

	/* ¿Qué es lo que siempre cumple el bucle? Que la parte analizada (bucle) del vector siempre
	 * es creciente.
	 * {I = Ai: 0 <= i < N-1: v[i] < v[i+1] ^ 0 <= cumbre <= i+1 }
	 *
	 */
	while (v[i] < v[i+1] && i < N-1) {
		cumbre = i+1;
		i++;
	}
	/*
	 * { Cota = N-1-i }
	 */

	return cumbre;
}
/* { Post: 	(0 <= cumbre < N) ^
 *			(Ai: 0<=i<cumbre: v[i] < v[i+1]) ^
 *			(Aj: cumbre<=j<N-1: v[j] > v[j+1])
 * }
 *
 * VERIFICACIÓN:
 * 1) {Pre} Inicialización {I}
 * 	  pmd(i=0;cumbre=i, (Ai: 0<=i<N-1:v[i]<v[i+1] ^ 0<=cumbre<=i+1))
 * 	  ((Ai: 0<=i<N-1:v[i]<v[i+1] ^ 0<=cumbre<=i+1)cumbre=i)i=0
 * 	  (Ai: 0<=i<N-1:v[i]<v[i+1] ^ 0<=i<=i+1)i=0
 * 	  (A0: 0<=0<N-1:v[0]<v[1] ^ 0<=0 <=1) --> true ^ true --> true
 *
 * 2) {I^B} A {I}
 *    pmd(cumbre = i+1; i=i+1, (Ai: 0<=i<N-1:v[i]<v[i+1] ^ 0<=cumbre<=i+1))
 *    ((Ai: 0<=i<N-1:v[i]<v[i+1] ^ 0<=cumbre<=i+1)i=i+1)cumbre=i+1
 *    (Ai+1: 0<=i+1<N-1:v[i+1]<v[i+2] ^ 0<= cumbre <= i+2)cumbre=i+1
 *    Ai+1: 0<=i+1<N-1:v[i+1]<v[i+2] ^ 0<=i+1<=i+2 --> true
 *
 * 3) {I^¬B} --> {Q}
 * 	  I ^ (v[i]>v[i+1] v i >= N-1) --> Post
 * 	  ???
 *
 * 4) Cota >= 0  {I ^ B} --> c>=0
 * 	  I ^(v[i]<v[i+1] ^ i < N-1) --> N-i-1 >= 0
 * 	  Trivial, en cada vuelta de bucle i aumenta en 1 por lo que
 * 	  N-i-1 siempre decrecerá y como i < N-1, máximo i= N-2 por tanto
 * 	  N-(N-2)-1 = N-N+2-1 = 1 >= 0
 *
 * 5) Cota decrece {I^B^c=T} Bucle {c < T}
 */

/* Un vector de n enteros con n >= 1 diremos que es monta�a si sus valores crecen
 * estrictamente hasta cierta cumbre y a partir de �l decrecen estrictamente. La
 * cumbre puede ser el primero o �ltimo �ndice. Especificar, dise�ar, verificar y
 * razonar el coste de un algoritmo iterativo que devuelva su cumbre.
 */
void ejercicio5() {
	int N = 10;
	int crece[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; //Cumbre �timo �ndice
	int decrece[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }; //Cumbre primer �ndice
	int v[10] = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
	int w[10] = { 1, 2, 3, 4, 5, 4, 3, 4, 3 };

	if (esMontana(crece, N)) {
		cout << "crece[] es monta�a.\n";
		cout << "Cumbre crece[]: " << cumbre(crece, N) << "\n";
	}
	if (esMontana(decrece, N)) {
		cout << "decrece[] es monta�a.\n";
		cout << "Cumbre decrece[]: " << cumbre(decrece, N) << "\n";
	}
	if (esMontana(v, N)) {
		cout << "v[] es monta�a.\n";
		cout << "Cumbre v[]: " << cumbre(v, N) << "\n";
	}
	if (esMontana(w, N)) {
		cout << "w[] es monta�a.\n";
		cout << "Cumbre w[]: " << cumbre(w, N) << "\n";
	}
}

bool esCreciente(int v[], int N) {
	bool creciente = true;
	int i = 0;
	while (v[i] < v[i+1] && i < N-1) {
		i++;
	}
	if (i < N-1) creciente = false;

	return creciente;
}

/*
 * {Pre = 0 <= n <= longitud(v) ^ creciente(v)
 */
int coincide(int ini, int fin, int v[], int N) {
	//Divide y vencerás
	int r = r;
	if (ini == fin || N == 0) {
		r = ini-1;
	}
	else {
		int m = (ini+fin)/2;
		if (v[m] <= m) r = coincide(m+1, fin, v, N);
		else  r = coincide(ini, m,v,N);
	}

	return r;
}
/*
 * {Post = r = (Ei:0<=i<N:v[i] = i)}
 */

/*
 * Especificar, diseñar, verificar y razonar el coste de un algoritmo recursivo
 * que, dado un vector de n>=0 enteros estrictamente creciente, determine en tiempo
 * logarítmico si alguno de sus elementos coincide con el valor de su índice.
 */
void ejercicio6() {
	int N = 10;
	int crece[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int coincideI[10] = { -33, -11, 1, 2, 3, 5, 7, 8, 9, 10 };
	int decrece[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int v[10] = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };

	if (esCreciente(crece, N)) {
		int r = coincide(0, N-1, crece, N);
		if (r != -1) cout << "crece " << r << "\n";
		else cout << "crece NO\n";
	}
	if (esCreciente(crece, N)) {
		int r = coincide(0, N-1, coincideI, N);
		if (r != -1) cout << "coincideI " << r << "\n";
		else cout << "coincideI NO\n";
	}
	if (esCreciente(decrece, N)) {
		int r = coincide(0, N-1, decrece, N);
		if (r != -1) cout << "decrede " << r << "\n";
		else cout << "decrece NO\n";
	}
	if (esCreciente(v, N)) {
		int r = coincide(0, N-1, v, N);
		if (r != -1) cout << "v " << r << "\n";
		else cout << "v NO\n";

	}
}
int main() {
	ejercicio4();
	ejercicio5();
	ejercicio6();
	return 0;
}
