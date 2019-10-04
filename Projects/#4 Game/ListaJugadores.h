#ifndef LISTAJUGADORES_H
#define LISTAJUGADORES_H

#include "Edificio.h"

typedef struct {
	tRegistro registro;
	tRegistro registroCopia; //Array auxiliar para conservar el original y reordenar éste por dinero o prestigio según se pida
	int cont;
	int N;
} tListaJugadores;


bool listaJugadoresLlena (tListaJugadores listaJugadores);																	//Devuelve un booleano que nos dice si la lista de jugadores esta llena (supera MaxJugadores) o no
int buscarJugador(tListaJugadores& listaJugadores, tJugador jugador);														//Devuelve un booleano indicando si se ha encontrado o no el jugador, si se encuentra nos devuelve su posición en la lista
tListaJugadores insertarJugador(tListaJugadores& listaJugadores, tJugador& jugador);										//Inserta un nuevo jugador al final de la lista
bool bajaJugador(tListaJugadores& listaJugadores, tJugador& jugador, tListaEdificios& listaEdificios, tEdificio& edificio);	//Busca el jugador a borrar y devuelve un booleano indicando si se ha borrado o no


#endif