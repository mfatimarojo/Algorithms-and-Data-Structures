#ifndef EDIFICIO_H
#define EDIFICIO_H

#include <cstring>

const int MaxEdificios = 50;
typedef char tCadena[50];

typedef struct {
	int codigo;
	tCadena nombre; //Con espacios
	int precio;
	int dinero;
	int prestigio;
	int estado;
}tEdificio;

typedef tEdificio tRegEdificio[MaxEdificios];

//tEdificio nuevoEdificio();
//void mostrarEdificio(tEdificio edificio);

#endif