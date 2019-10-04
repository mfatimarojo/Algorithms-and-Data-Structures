#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include <iomanip>
#include "Jugador.h"
#include "ListaEdificios.h"




tJugador nuevoJugador() {

	tJugador jugador;


	cout << "Introduce el usuario: ";
	cin >> jugador.usuario;
	cout << "Introduce la contraseña: ";
	cin >> jugador.contraseña;
	cout << "Introduce el nombre de la empresa: ";
	cin >> jugador.universidad;
	jugador.dinero = 3000;
	jugador.prestigio = 0;
	jugador.contComprados = 0;
	jugador.comprados[0] = -1;
	

	return jugador;

}
void mostrarJugador(tJugador jugador, tEdificio edificio, tListaEdificios listaEdificios){

	
	int posEdificio;

	cout << "==================================================" << endl;
	cout << setw(13) << "Usuario: " << jugador.usuario << " (" << jugador.universidad << ")" << endl;
	cout << setw(13) << "Dinero: " << jugador.dinero << endl;
	cout << setw(13) << "Prestigio: " << jugador.prestigio << endl;
	cout << setw(13) << "Edificios: " << jugador.contComprados << endl;
	for (int j = 0; j < jugador.contComprados; j++){
		edificio.codigo =  jugador.comprados[j];
		if (edificio.codigo != -1){
			posEdificio = buscarEdificio(listaEdificios, edificio, 0, listaEdificios.cont);
			if(posEdificio != -2)
				edificio = listaEdificios.registro[posEdificio];
			cout << setw(23) << "Edificio #" << j+1 << " - " << edificio.nombre << " -D: "  << edificio.dinero << " -P: " << edificio.prestigio <<endl;
		}
	}
}
bool comprarEdificio(tJugador& jugador, tEdificio& edificio, tListaEdificios& listaEdificios){

	bool comprado = false;

	int posEdificio;

	if(listaCompradosLlena(jugador)){
		cout << "ERROR. No puedes comprar mas edificios. " << endl;
		comprado = false;
	} 
	else{
		posEdificio = buscarEdificio(listaEdificios, edificio, 0, listaEdificios.cont);
		if(posEdificio == -2){
			cout << "Código no válido." << endl;
			comprado = false;
		}
		else {
			edificio = listaEdificios.registro[posEdificio];
			if(edificio.estado != 0){
				cout << "Edificio no disponible. " << endl;
				comprado = false;
			}
			else if(jugador.dinero < edificio.precio){
				cout << "No posees suficiente dinero. " << endl;
				comprado = false;
			}
			else {
				jugador.dinero = jugador.dinero - edificio.precio;
				jugador.comprados[jugador.contComprados] = edificio.codigo;
				jugador.contComprados++;
				jugador.comprados[jugador.contComprados] = -1;
				edificio.estado = 1;
				listaEdificios.registro[posEdificio] = edificio;
				comprado = true;
			}
		}
	}

	return comprado;

}
bool listaCompradosLlena(tJugador jugador){

	bool lleno = false;

	if(jugador.contComprados >= MaxComprados){
		cout << "ERROR. Tu lista de edificios comprados esta llena. " << endl;
		lleno = true;
	}
	else lleno = false;

	return lleno;
}