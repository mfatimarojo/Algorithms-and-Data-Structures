#ifndef JUGADOR_H
#define JUGADOR_H

#include <cstring>
#include "Edificio.h"
#include  "ListaEdificios.h"
using namespace std;

const int MaxComprados = 50;

typedef char tCadenaJugador[50];

typedef struct {
	tCadenaJugador usuario, contraseña, universidad;
	int dinero;
	int prestigio;
	int contComprados;
	int comprados[MaxComprados];
} tJugador;

typedef tJugador *tRegistro;		 //Puntero a array dinámico
typedef tJugador *tRegistroCopia;	 //Puntero a array dinámico



tJugador nuevoJugador();																			//Lee los datos de un jugador y devuelve el struct tJugador
void mostrarJugador (tJugador jugador, tEdificio edificio, tListaEdificios listaEdificios);			//Muestra en pantalla los datos del jugador
bool listaCompradosLlena(tJugador jugador);															//Devuelve un booleano indicando si la lista de edificios comprados está llena (supera MaxComprados) o no
bool comprarEdificio(tJugador& jugador, tEdificio& edificio, tListaEdificios& listaEdificios);		//Devuelve un booleano indicando si se ha podido realizar la compra dependiendo de si el edificio
																									//existe, se encuentra disponible y si el jugador dispone de dinero


#endif