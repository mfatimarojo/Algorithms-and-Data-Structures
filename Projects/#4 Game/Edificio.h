#ifndef EDIFICIO_H
#define EDIFICIO_H

#include <cstring>
using namespace std;


typedef char tCadenaEdificio[50];


typedef struct {
	int codigo;
	tCadenaEdificio nombre;
	int precio;
	int dinero;
	int prestigio;
	int estado;
} tEdificio;

typedef tEdificio *tRegPtr; //Puntero a array dinámico



tEdificio nuevoEdificio();						//Pide al usuario los datos de un edificios y devuelve como salida el struct tEdificio
void mostrarEdificio(tEdificio edificio);		//Muestra todos los datos del edificio en pantalla
 

#endif
