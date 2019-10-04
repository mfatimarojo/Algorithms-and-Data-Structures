#include <iostream>
#include <cstring>
using namespace std;
#include <iomanip>
#include "Edificio.h"
#include "ListaEdificios.h"




bool listaEdificiosLlena(tListaEdificios listaEdificios){
	bool llena = false;

	if (listaEdificios.cont >= listaEdificios.N) llena = true;
	else llena = false;

	return llena;
}
int buscarEdificio(tListaEdificios listaEdificios, tEdificio edificio, int ini, int fin) {


	bool encontrado = false;
	int posEdificio = -2;
	
	if (ini <= fin) {
		int mitad = (ini + fin) / 2;
		if (edificio.codigo == listaEdificios.registro[mitad].codigo) {
			posEdificio = mitad;
			encontrado = true;		
		}
		else {
			if (edificio.codigo < listaEdificios.registro[mitad].codigo) 
				posEdificio = buscarEdificio(listaEdificios, edificio, ini, mitad - 1);  //Aplicamos recursividad
			else posEdificio = buscarEdificio(listaEdificios, edificio, mitad + 1, fin);
			
			encontrado = false;
		}

	
	}
	return posEdificio;
}
tListaEdificios insertarEdificio(tListaEdificios& listaEdificios, tEdificio edificio){

		int i = 0;
		while ((i < listaEdificios.cont) && (listaEdificios.registro[i].codigo < edificio.codigo)) 
			i++; 
		for (int j = listaEdificios.cont; j > i; j--)
			listaEdificios.registro[j] = listaEdificios.registro[j -1];
		listaEdificios.registro[i] = edificio;
		listaEdificios.cont++;

	return listaEdificios;
}
bool bajaEdificio(tListaEdificios& listaEdificios, tEdificio& edificio) {

	int posEdificio;
	bool borrado = false;


	posEdificio = buscarEdificio(listaEdificios, edificio, 0, listaEdificios.cont);
	if (posEdificio != -2) {
		edificio = listaEdificios.registro[posEdificio];
		if (edificio.estado == 0){
			edificio.estado = 2;
			borrado = true;
			listaEdificios.registro[posEdificio] = edificio;
		}
		else borrado = false;
	}
	else
		borrado = false;

	return borrado;

}
