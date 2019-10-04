#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include <iomanip>
#include "Edificio.h"
#include "ListaEdificios.h"
#include "Jugador.h"
#include "ListaJugadores.h"

bool cargarEdificios(tEdificio& edificio, tListaEdificios& listaEdificios);
bool cargarJugadores(tJugador& jugador, tListaJugadores& listaJugadores);
bool logIn (tJugador jugador, tListaJugadores listaJugadores);
bool logInAdmin();
int logInUser(tCadena usuario, tJugador& jugador, tListaJugadores listaJugadores);
int menuAdministracion();
int menuJuego();

int main() {
	tEdificio edificio;
	tListaEdificios listaEdificios;
	tJugador jugador;
	tListaJugadores listaJugadores;
	int centinelaEdif = -1;

	if ((cargarEdificios(edificio, listaEdificios)) || (cargarJugadores(jugador, listaJugadores))) {
		cout << "Empezamos con listas vacias." << endl;
		listaEdificios.cont = 0;
		listaJugadores.cont = 0;
	}
	else cout << "Listas cargadas." << endl;

	cout << "BIENVENIDO A CAMPUS VILLE" << endl;
	cout << "=========================\n" << endl;
	cout << "Escribe 'salir' o 's' para cerrar el programa... << endl;

	
	
	system("pause");
}

bool cargarEdificios(tEdificio& edificio, tListaEdificios& listaEdificios){
	bool error = false;
	int centinelaEdif = -1;
	listaEdificios.cont = 0;

	ifstream fIn;
	fIn.open("edificios.txt");
	if(!fIn.is_open()) error = true;
	else {
		fIn >> edificio.codigo;
		while ((edificio.codigo != centinelaEdif) && (!error)) {
			if (edificio.codigo < 0) {
				cout << "ERROR con la carga de archivos. Codigo de edificio ambiguo." << endl;
				error = true;
			}
			else {
				fIn.ignore();
				fIn.getline (edificio.nombre, 50);
				fIn >> edificio.precio;
				if (edificio.precio < 0) {
					cout << "ERROR con la carga de archivos. Precio de edificio ambiguo." << endl;
					error = true;
				}
				else {
					fIn >> edificio.dinero;
					fIn >> edificio.prestigio;
					fIn >> edificio.estado;
					if ((edificio.estado != 0) && (edificio.estado != 1) && (edificio.estado != 2)) {
						cout << "ERROR con la carga de archivos. Estado de edificio ambiguo." << endl;
						error = true;
					}
					else {
						listaEdificios.registro[listaEdificios.cont] = edificio;
						listaEdificios.cont++;
						fIn >> edificio.codigo;
					}
				}
			}
		}	
	}	
	fIn.close();
	return error;
}
bool cargarJugadores (tJugador& jugador, tListaJugadores& listaJugadores) {
	bool error = false;
	listaJugadores.cont = 0;
	jugador.contComprados = 0;

	ifstream fIn;
	fIn.open("jugadores.txt");
	if (!fIn.is_open()) error = true;
	else {
		fIn >> jugador.usuario;
		while ((strcmp (jugador.usuario, "X")) && (!error)) {
			if ((!strcmp (jugador.usuario, "admin")) || (!strcmp(jugador.usuario, "salir"))) {
				cout << "ERROR con la carga de archivos.  Usuario ambiguo." << endl;
				error = true;
			}
			else {
				fIn >> jugador.contraseña;
				fIn.ignore();
				fIn.getline(jugador.universidad, 50);
				fIn >> jugador.dinero;
				if (jugador.dinero < 0) {
					cout << "ERROR con la carga de achivos.  Dinero de jugador ambiguo." << endl;
					error = true;
				}
				else {
					fIn >> jugador.prestigio;
					fIn >> jugador.comprados[jugador.contComprados];
					while ((jugador.comprados[jugador.contComprados] != -1) && (!error) && (jugador.contComprados <= MaxEdificios)){
						if (jugador.comprados[jugador.contComprados] < -1) {
							cout << "ERROR con la carga de archivos. Codigo de edificio comprados ambiguo." << endl;
							error = true;
						}
						else {
							jugador.contComprados++;
							fIn >> jugador.comprados[jugador.contComprados];
						}
					}
					if (jugador.comprados[jugador.contComprados] == -1) {
						listaJugadores.registro[listaJugadores.cont] = jugador;
						listaJugadores.cont++;
						fIn >> jugador.usuario;		
					}
				}
			}
		}
	}
	fIn.close();
	return error;
}
bool logIn (tJugador jugador, tListaJugadores listaJugadores) {
	bool salir = false;
	bool logIn = false;
	tCadena usuario;
	int intentos = 3;

	do{
		cout << "Usuario: ";
		cin >> usuario;
		if (!strcmp(usuario, "admin")) {
			if (!logInAdmin()) 	logIn = false;
			else logIn = true;
		}
		else {
			//logInUser
		}
	} while (((strcmp(usuario, "salir")) || (strcmp(usuario, "s"))) && (!logIn));
	
	if ((!strcmp(usuario, "salir")) || (!strcmp(usuario, "s"))) {
		logIn = false;
		salir = true;	
	}

	return logIn;
}

bool logInAdmin() {
	bool logIn = false;
	int intentos = 3;
	tCadena contraseña;

	cout << "Contrasena (" << intentos << " intentos): ";
	cin >> contraseña;
	while ((strcmp(contraseña, "12345")) && (intentos > 0)) {
		intentos--;
		cout << "Contrasena (" << intentos << " intentos). ";
		cin >> contraseña;
	}
	if (intentos <= 0) {
		cout << "ERROR. Contrasena incorrecta." << endl;
		logIn = false;
	}
	if (!strcmp(contraseña, "12345")) logIn = true;

	return logIn;
}
int logInUser(tCadena usuario, tJugador& jugador, tListaJugadores listaJugadores) {
	int posUser = 0;
	int postUserReal = -2;
	bool encontrado = false;

	jugador = listaJugadores.registro[posUser];
	while ((strcmp(usuario, jugador.usuario)) && (!encontrado) && (posUser < listaJugadores.cont)) {
		encontrado = false;
		posUser++;
		jugador = listaJugadores.registro[posUser];
		encontrado = false;
	}
	if (!strcmp(usuario, jugador.usuario)) {
		posUserReal = posUser;
		encontrado = true;
	}

	return posUserReal;
}
int menuAdministracion() {
	int opcion;

	cout << "\n\nMENU DE ADMINISTRACION" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
	cout << "1. - Ver el listado de edificios" << endl;
	cout << "2. - Nuevo edificio" << endl;
	cout << "3. - Borrar edificio" << endl;
	cout << "4. - Ver el listado de jugadores" << endl;
	cout << "5. - Nuevo jugador" << endl;
	cout << "6. - Borrar un jugador" << endl;
	cout << "7. - Ejecutar un turno" << endl;
	cout << "8. - Ver la clasificacin" << endl;
	cout << "0. - Cerrar la sesion" << endl;
	cout << "Opcion: ";
	do {
		cin >> opcion;
		if ((opcion < 0) || (opcion > 8)) cout << "ERROR. Opcion no valida, pruebe de nuevo: ";
	} while ((opcion < 0) || (opcion > 8));

	return opcion;
}
int menuJuego() {
	int opcion;

	cout << "\n\nMENU DE JUEGO" << endl;
	cout << "~~~~~~~~~~~~~\n" << endl;
	cout << "1. - Ver mis edificios" << endl;
	cout << "2. - Ver los edificios disponibles" << endl;
	cout << "3. - Comprar un edificio" << endl;
	cout << "4. - Ver la clasificacion (ordenada por dinero)" << endl;
	cout << "5. - Ver la clasificacion (ordenada por prestigio)" << endl;
	cout << "0. - Cerrar la sesion" << endl;
	cout << "Opcion: ";
	do {
		cin >> opcion;
		if ((opcion < 0) || (opcion > 5)) cout << "ERROR. Opcion no valida, pruebe de nuevo: ";
	} while ((opcion < 0) || (opcion > 5));

	return opcion;

}
