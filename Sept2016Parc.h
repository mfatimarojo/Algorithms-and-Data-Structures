#pragma once

#ifndef __PEDIDOS_H
#define __PEDIDOS_H

#include <string>
#include "DiccionarioHash.h"
#include "diccionario.h"
#include "lista.h"

using namespace std;

typedef string Objeto;

typedef struct {
	float precio;
	float peso;
	int numUnidades;
} InfoObjeto;

typedef int Fecha;

typedef string Direccion;

class Pedidos {
public: 
	void nuevoPedido(const Lista<Objeto> &l, const Fecha &f, const Direccion &d) {
		
	}
private:
	DiccionarioHash<Objeto, InfoObjeto> _objetos;
	Diccionario<Fecha, Lista<Objeto>> _pedidos;

};

#endif