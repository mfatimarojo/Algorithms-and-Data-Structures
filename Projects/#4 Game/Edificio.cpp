#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#include <iomanip>
#include "Edificio.h"
#include "ListaEdificios.h"



tEdificio nuevoEdificio() {

	tEdificio edificio;
	
	do {
		cout << "\nIdentificador: ";
		cin >> edificio.codigo;
	} while (edificio.codigo < 0);
	cin.ignore();
	cout << "Nombre del edificio: ";
	cin.getline(edificio.nombre, 60);
	do {
		cout << "Precio de compra: ";
		cin >> edificio.precio;
	} while (edificio.precio < 0);
	cin.ignore();
	cout << "Prestigio por turno: ";
	cin >> edificio.prestigio;
	cout << "Dinero por turno: ";
	cin >> edificio.dinero;
	edificio.estado = 0;

	return edificio;

}
void mostrarEdificio(tEdificio edificio){


	typedef char tCadenaEstado[20];
	tCadenaEstado estadoEdificio;

	if (edificio.estado == 0) {
		strcpy(estadoEdificio, "DISPONIBLE" );
	}
	else if (edificio.estado == 1) {
		strcpy(estadoEdificio, "COMPRADO");
	}
	else if (edificio.estado == 2) {
		strcpy(estadoEdificio, "BORRADO");	
	}

	for (int i = 0; i < 40; i++)
		cout << "=";
	cout << endl;

	cout << setw(23) << "Identificador: " << edificio.codigo << endl;
	cout << setw(23) << "Nombre: " << edificio.nombre << endl;
	cout << setw(23) << "Precio de compra: " << edificio.precio << endl;
	cout << setw(23) << "Dinero por turno: " << edificio.dinero << endl;
	cout << setw(23) << "Prestigio por turno: " << edificio.prestigio << endl;
	cout << setw(23) << "Estado: " << estadoEdificio << endl;
}
