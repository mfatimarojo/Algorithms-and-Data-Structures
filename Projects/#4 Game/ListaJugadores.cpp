#include <iostream>
#include <cstring>
#include "Jugador.h"
#include "ListaJugadores.h"
using namespace std;





bool listaJugadoresLlena(tListaJugadores listaJugadores){
	bool llena = false;

	if (listaJugadores.cont >= listaJugadores.N) llena = true;
	else llena = false;

	return llena;
}
int buscarJugador(tListaJugadores& listaJugadores, tJugador jugador){

	bool encontrado = false;
	int posJugador = -2;

	for(int i = 0; i < listaJugadores.cont && !encontrado; i++)
		if (!(strcmp(jugador.usuario, listaJugadores.registro[i].usuario))){
			posJugador = i;
			encontrado = true;
		}

	return posJugador;

}
tListaJugadores insertarJugador(tListaJugadores& listaJugadores, tJugador& jugador){

	listaJugadores.registro[listaJugadores.cont] = jugador;
	listaJugadores.cont++;
	
	return listaJugadores;
}
bool bajaJugador(tListaJugadores& listaJugadores, tJugador& jugador, tListaEdificios& listaEdificios, tEdificio& edificio) {

	int posEdificio;
	int posJugador;

	bool borrado = false;


	posJugador = buscarJugador(listaJugadores, jugador);
	if (posJugador != -2) {
		jugador = listaJugadores.registro[posJugador];
		for (int j = 0; j <= jugador.contComprados; j++){
			if (jugador.comprados[j] != -1){
				edificio.codigo = jugador.comprados[j];
				posEdificio = buscarEdificio(listaEdificios, edificio, 0, listaEdificios.cont);
				edificio = listaEdificios.registro[posEdificio];
				edificio.estado = 0;
				listaEdificios.registro[posEdificio] = edificio;
			}
		}
		for (int i = posJugador + 1; i < listaJugadores.cont; i++) { 
			listaJugadores.registro[i-1] = listaJugadores.registro[i];
		}
		listaJugadores.cont--;
		borrado = true;
	}
	else borrado = false;

	return borrado;

}