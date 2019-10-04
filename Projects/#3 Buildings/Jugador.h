#ifndef JUGADOR_H
#define JUGADOR_H

#include <cstring>
#include "ListaEdificios.h"
#include "Edificio.h"

const int MaxJugadores = 20;
typedef char tCadena[50];

typedef struct {
	tCadena usuario; //Sin espacios
	tCadena contraseña; //sin espacios
	tCadena universidad; //con espacios
	int dinero;
	int prestigio;
	int comprados[MaxEdificios];
	int contComprados;
}tJugador;
typedef tJugador tRegJugador[MaxJugadores];

//tJugador nuevoJugador();
//void mostrarJugador(tListaEdificios listaEdificios, tJugador jugador);
//bool listaCompradosLlena(tJugador jugador);
//void comprarEdificio(tListaEdificios listaEdificios, tJugador jugador, tEdificio edificio);

#endif